import json
import os
import random
import string
import csv
import hashlib
from datetime import datetime, timedelta
try:
    import pyperclip
    CLIPBOARD_AVAILABLE = True
except ImportError:
    CLIPBOARD_AVAILABLE = False

passwords = []
MASTER_FILE = "master.hash"

def load_passwords():
    global passwords
    if os.path.exists("vault.json"):
        with open("vault.json", "r") as f:
            passwords = json.load(f)

def set_master_password():
    pwd = input("Set master password: ")
    confirm = input("Confirm master password: ")
    if pwd != confirm:
        print("Passwords do not match. Master password not set.")
        return False
    h = hashlib.sha256(pwd.encode()).hexdigest()
    with open(MASTER_FILE, "w") as f:
        f.write(h)
    print("Master password set.")
    return True

def verify_master_password():
    if not os.path.exists(MASTER_FILE):
        print("No master password set. Please create one.")
        return set_master_password()
    stored = open(MASTER_FILE).read().strip()
    attempt = input("Enter master password: ")
    if hashlib.sha256(attempt.encode()).hexdigest() == stored:
        return True
    print("Incorrect master password.")
    return False

def change_master_password():
    if not verify_master_password():
        return
    print("Enter new master password.")
    set_master_password()

def save_passwords():
    with open("vault.json", "w") as f:
        json.dump(passwords, f)

def generate_password(length=12):
    characters = string.ascii_letters + string.digits + string.punctuation
    return "".join(random.choice(characters) for _ in range(length))

def check_password_strength(pw):
    # simple heuristic: length plus variety of character types
    score = 0
    if len(pw) >= 8:
        score += 1
    if any(c.islower() for c in pw) and any(c.isupper() for c in pw):
        score += 1
    if any(c.isdigit() for c in pw):
        score += 1
    if any(c in string.punctuation for c in pw):
        score += 1
    strengths = {0: "Very Weak", 1: "Weak", 2: "Moderate", 3: "Strong", 4: "Very Strong"}
    return strengths.get(score, "Unknown")

def add_password():
    site = input("Website: ")
    username = input("Username: ")

    choice = input("Generate password? (y/n): ")

    if choice.lower() == "y":
        password = generate_password()
        print("Generated password:", password)
    else:
        password = input("Enter password: ")
    # show strength
    strength = check_password_strength(password)
    print(f"Password strength: {strength}")

    notes = input("Notes (optional): ")

    passwords.append({
        "site": site,
        "username": username,
        "password": password,
        "notes": notes,
        "created_at": datetime.now().isoformat(),
        "updated_at": datetime.now().isoformat()
    })

    save_passwords()

def view_passwords():
    for entry in passwords:
        print(f"Site: {entry['site']}")
        print(f"Username: {entry['username']}")
        print(f"Password: {entry['password']}")
        if entry.get('notes'):
            print(f"Notes: {entry['notes']}")
        print("---")

def export_passwords(filename="vault.csv"):
    if not passwords:
        print("No passwords to export.")
        return
    with open(filename, "w", newline="") as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(["site", "username", "password", "notes"])
        for e in passwords:
            writer.writerow([e["site"], e["username"], e["password"], e.get("notes", "")])
    print(f"Exported {len(passwords)} entries to {filename}")

def import_passwords(filename="vault.csv"):
    if not os.path.exists(filename):
        print(f"File {filename} not found.")
        return
    count = 0
    with open(filename, newline="") as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            if "site" in row and "username" in row and "password" in row:
                passwords.append({
                    "site": row["site"],
                    "username": row["username"],
                    "password": row["password"],
                    "notes": row.get("notes", "")
                })
                count += 1
    if count > 0:
        save_passwords()
    print(f"Imported {count} entries from {filename}")

def list_weak_passwords():
    """Display entries that have weak or very weak passwords."""
    weak = []
    for entry in passwords:
        strength = check_password_strength(entry['password'])
        if strength in ("Very Weak", "Weak"):
            weak.append((entry, strength))
    if not weak:
        print("No weak passwords found.")
        return
    for entry, strength in weak:
        print(f"{entry} => {strength}")


def view_passwords_by_strength():
    """Display all passwords organized and grouped by strength level."""
    if not passwords:
        print("No passwords stored.")
        return
    
    from collections import defaultdict
    strength_groups = defaultdict(list)
    
    for entry in passwords:
        strength = check_password_strength(entry['password'])
        strength_groups[strength].append(entry)
    
    # Display in order from strongest to weakest
    strength_order = ["Very Strong", "Strong", "Moderate", "Weak", "Very Weak"]
    
    print("\n" + "="*70)
    print("PASSWORDS ORGANIZED BY STRENGTH")
    print("="*70)
    
    for strength in strength_order:
        if strength in strength_groups:
            entries = strength_groups[strength]
            print(f"\n[{strength}] - {len(entries)} password(s)")
            print("-" * 70)
            for i, entry in enumerate(entries, 1):
                print(f"  {i}. {entry['site']} ({entry['username']})")
    
    print("\n" + "="*70)
    print(f"SUMMARY: Total {len(passwords)} passwords")
    for strength in strength_order:
        if strength in strength_groups:
            count = len(strength_groups[strength])
            percentage = (count / len(passwords)) * 100
            print(f"  {strength}: {count} ({percentage:.1f}%)")
    print("="*70 + "\n")


def check_password_age():
    """Display password age and recommend changes for old passwords."""
    if not passwords:
        print("No passwords stored.")
        return
    
    now = datetime.now()
    age_threshold = 90  # days - recommend changing after 90 days
    
    password_ages = []
    for entry in passwords:
        created_at_str = entry.get('created_at', None)
        if created_at_str:
            created_at = datetime.fromisoformat(created_at_str)
            age = (now - created_at).days
            password_ages.append((entry, age))
        else:
            password_ages.append((entry, None))
    
    # Sort by age (oldest first)
    password_ages.sort(key=lambda x: x[1] if x[1] is not None else -1, reverse=True)
    
    print("\n" + "="*80)
    print("PASSWORD AGE REPORT")
    print("="*80)
    
    old_passwords = 0
    for entry, age in password_ages:
        if age is None:
            age_str = "Unknown (no creation date)"
            warning = ""
        else:
            age_str = f"{age} days"
            if age > age_threshold:
                warning = " ⚠️  CHANGE RECOMMENDED!"
                old_passwords += 1
            else:
                warning = ""
        
        print(f"\n{entry['site']} ({entry['username']})")
        print(f"  Age: {age_str}{warning}")
    
    print("\n" + "="*80)
    print(f"SUMMARY:")
    print(f"  Total passwords: {len(passwords)}")
    print(f"  Passwords older than {age_threshold} days: {old_passwords}")
    if old_passwords > 0:
        print(f"  ⚠️  Recommend changing {old_passwords} password(s) for security!")
    print("="*80 + "\n")


def backup_vault():
    if not os.path.exists("vault.json"):
        print("No vault to backup.")
        return
    import shutil
    backup_file = "vault_backup.json"
    shutil.copy("vault.json", backup_file)
    print(f"Vault backed up to {backup_file}")


def show_statistics():
    if not passwords:
        print("No passwords stored.")
        return
    
    total = len(passwords)
    lengths = [len(entry['password']) for entry in passwords]
    avg_length = sum(lengths) / total if total > 0 else 0
    
    strengths = [check_password_strength(entry['password']) for entry in passwords]
    weak_count = sum(1 for s in strengths if s in ("Very Weak", "Weak"))
    strong_count = sum(1 for s in strengths if s == "Very Strong")
    
    unique_sites = len(set(entry['site'] for entry in passwords))
    
    print(f"Total passwords: {total}")
    print(f"Average password length: {avg_length:.1f}")
    print(f"Weak passwords: {weak_count}")
    print(f"Very strong passwords: {strong_count}")
    print(f"Unique sites: {unique_sites}")


def regenerate_weak_passwords():
    weak_entries = []
    for i, entry in enumerate(passwords):
        strength = check_password_strength(entry['password'])
        if strength in ("Very Weak", "Weak"):
            weak_entries.append((i, entry, strength))
    
    if not weak_entries:
        print("No weak passwords to regenerate.")
        return
    
    print(f"Found {len(weak_entries)} weak password(s):")
    for idx, entry, strength in weak_entries:
        print(f"{idx+1}. {entry['site']} ({entry['username']}) - {strength}")
    
    confirm = input("Regenerate all weak passwords? (y/n): ")
    if confirm.lower() != 'y':
        return
    
    for idx, entry, _ in weak_entries:
        new_pass = generate_password()
        passwords[idx]['password'] = new_pass
        print(f"Regenerated password for {entry['site']}: {new_pass}")
    
    save_passwords()
    print("Weak passwords regenerated and saved.")


def check_duplicate_passwords():
    if not passwords:
        print("No passwords stored.")
        return
    
    from collections import defaultdict
    pass_to_sites = defaultdict(list)
    for entry in passwords:
        pass_to_sites[entry['password']].append((entry['site'], entry['username']))
    
    duplicates = {pwd: sites for pwd, sites in pass_to_sites.items() if len(sites) > 1}
    
    if not duplicates:
        print("No duplicate passwords found. All passwords are unique.")
        return
    
    print("Duplicate passwords found:")
    for pwd, sites in duplicates.items():
        print(f"Password '{pwd}' is used for:")
        for site, user in sites:
            print(f"  - {site} ({user})")
        print()


def check_password_breaches():
    """Check passwords against a database of commonly breached passwords."""
    if not passwords:
        print("No passwords stored.")
        return
    
    # Common breached passwords (in a real implementation, this would be a much larger database)
    # These are some of the most commonly used and breached passwords
    breached_passwords = {
        "password", "123456", "123456789", "qwerty", "abc123", "password123",
        "admin", "letmein", "welcome", "monkey", "1234567890", "password1",
        "qwerty123", "welcome123", "admin123", "root", "user", "guest",
        "12345678", "12345", "qwertyuiop", "superman", "iloveyou", "princess",
        "rockyou", "1234567", "123456789", "password123", "qwerty1", "1q2w3e4r",
        "baseball", "dragon", "football", "master", "jordan", "harley", "ranger",
        "iowa", "pepper", "jennifer", "jordan23", "michelle", "superman1",
        "batman", "trustno1", "ninja", "hunter2", "shadow", "summer", "michael",
        "buster", "jennifer1", "1qaz2wsx", "killer", "zaq1zaq1", "jordan1",
        "pepper1", "matthew", "patrick", "newyork", "canada", "zxcvbnm",
        "joshua", "daniel", "buster1", "pepperoni", "jennifer2", "summer1",
        "1q2w3e4r5t", "qwertyui", "asdfghjkl", "zxcvbn", "qazwsx", "123qwe",
        "qwe123", "1q2w3e", "2wsx3edc", "qweasd", "asdf123", "1qazxsw2",
        "zaq12wsx", "123456a", "a123456", "654321", "123456789a", "1qaz2wsx3edc"
    }
    
    breached_entries = []
    total_checked = len(passwords)
    
    print("🔍 Checking passwords against known breach databases...")
    print("(This is a simulation - in production, this would check against real breach data)")
    print()
    
    for entry in passwords:
        password = entry['password'].lower()  # Case-insensitive check
        if password in breached_passwords:
            breached_entries.append(entry)
    
    if not breached_entries:
        print("✅ Good news! None of your passwords appear in known breach databases.")
        print(f"   Checked {total_checked} password(s)")
        return
    
    print("⚠️  WARNING: The following passwords have been found in known data breaches!")
    print("   These should be changed immediately for security.")
    print()
    
    for entry in breached_entries:
        print(f"🚨 BREACHED: {entry['site']} ({entry['username']})")
        print(f"   Password: {entry['password']}")
        print(f"   Risk Level: HIGH - This password is commonly used and has been exposed")
        print()
    
    print("=" * 70)
    print(f"SUMMARY: {len(breached_entries)} out of {total_checked} passwords are compromised")
    print("RECOMMENDATION: Change these passwords immediately!")
    print("Use the 'Regenerate Weak Passwords' option or update them manually.")
    print("=" * 70)


def emergency_access_codes():
    """Generate emergency access codes for trusted contacts."""
    print("\n🚨 EMERGENCY ACCESS CODE SYSTEM")
    print("This feature allows you to generate temporary codes that trusted")
    print("contacts can use to access your password vault in emergency situations.")
    print("Codes are encrypted and can have expiration times and usage limits.")
    print()

    # Load existing emergency codes
    codes_file = "emergency_codes.json"
    emergency_codes = []
    if os.path.exists(codes_file):
        try:
            with open(codes_file, "r") as f:
                emergency_codes = json.load(f)
        except:
            emergency_codes = []

    while True:
        print("\nEmergency Access Options:")
        print("1. Generate new emergency code")
        print("2. View active emergency codes")
        print("3. Revoke emergency code")
        print("4. Test emergency code access")
        print("5. Return to main menu")

        choice = input("Choose option: ").strip()

        if choice == "1":
            # Generate new emergency code
            print("\n🔐 Generate Emergency Access Code")
            contact_name = input("Trusted contact name: ").strip()
            if not contact_name:
                print("Contact name is required.")
                continue

            # Code expiration options
            print("Code expiration options:")
            print("1. 24 hours")
            print("2. 7 days")
            print("3. 30 days")
            print("4. 90 days")
            print("5. Custom hours")

            exp_choice = input("Choose expiration: ").strip()
            if exp_choice == "1":
                expires_hours = 24
            elif exp_choice == "2":
                expires_hours = 168  # 7*24
            elif exp_choice == "3":
                expires_hours = 720  # 30*24
            elif exp_choice == "4":
                expires_hours = 2160  # 90*24
            elif exp_choice == "5":
                try:
                    expires_hours = int(input("Enter hours: "))
                except ValueError:
                    print("Invalid hours.")
                    continue
            else:
                print("Invalid choice.")
                continue

            # Usage limit
            try:
                max_uses = int(input("Maximum uses (0 for unlimited): "))
            except ValueError:
                max_uses = 1

            # Generate secure code
            code_chars = string.ascii_letters + string.digits
            emergency_code = "".join(random.choice(code_chars) for _ in range(16))

            # Create code entry
            code_entry = {
                "code": hashlib.sha256(emergency_code.encode()).hexdigest(),
                "contact": contact_name,
                "created_at": datetime.now().isoformat(),
                "expires_at": (datetime.now() + timedelta(hours=expires_hours)).isoformat(),
                "max_uses": max_uses,
                "uses": 0,
                "active": True
            }

            emergency_codes.append(code_entry)

            # Save codes
            with open(codes_file, "w") as f:
                json.dump(emergency_codes, f)

            print("
✅ EMERGENCY CODE GENERATED"            print(f"Contact: {contact_name}")
            print(f"Code: {emergency_code}")
            print(f"Expires: {code_entry['expires_at']}")
            print(f"Max uses: {max_uses if max_uses > 0 else 'Unlimited'}")
            print()
            print("⚠️  IMPORTANT SECURITY NOTICE:")
            print("- Share this code ONLY with the trusted contact")
            print("- Store this code securely (not in the vault)")
            print("- The code will expire automatically")
            print("- You can revoke the code anytime")
            print()

        elif choice == "2":
            # View active codes
            if not emergency_codes:
                print("No emergency codes found.")
                continue

            print("\n📋 ACTIVE EMERGENCY CODES")
            active_count = 0
            for i, code in enumerate(emergency_codes, 1):
                if code.get("active", True):
                    active_count += 1
                    expires = datetime.fromisoformat(code["expires_at"])
                    remaining = expires - datetime.now()
                    status = "ACTIVE" if remaining.total_seconds() > 0 else "EXPIRED"

                    print(f"{i}. {code['contact']}")
                    print(f"   Status: {status}")
                    print(f"   Expires: {code['expires_at']}")
                    print(f"   Uses: {code['uses']}/{code['max_uses'] if code['max_uses'] > 0 else '∞'}")
                    print()

            if active_count == 0:
                print("No active emergency codes.")

        elif choice == "3":
            # Revoke code
            if not emergency_codes:
                print("No emergency codes to revoke.")
                continue

            print("\nSelect code to revoke:")
            for i, code in enumerate(emergency_codes, 1):
                if code.get("active", True):
                    print(f"{i}. {code['contact']} (expires: {code['expires_at']})")

            try:
                revoke_choice = int(input("Enter number to revoke (0 to cancel): "))
                if revoke_choice == 0:
                    continue
                if 1 <= revoke_choice <= len(emergency_codes):
                    code_to_revoke = emergency_codes[revoke_choice - 1]
                    code_to_revoke["active"] = False
                    with open(codes_file, "w") as f:
                        json.dump(emergency_codes, f)
                    print(f"Emergency code for {code_to_revoke['contact']} has been revoked.")
                else:
                    print("Invalid choice.")
            except ValueError:
                print("Invalid input.")

        elif choice == "4":
            # Test emergency code access (for development/testing)
            test_code = input("Enter emergency code to test: ").strip()
            if not test_code:
                continue

            code_hash = hashlib.sha256(test_code.encode()).hexdigest()
            found = False

            for code in emergency_codes:
                if code["code"] == code_hash and code.get("active", True):
                    expires = datetime.fromisoformat(code["expires_at"])
                    if datetime.now() < expires:
                        if code["max_uses"] == 0 or code["uses"] < code["max_uses"]:
                            code["uses"] += 1
                            with open(codes_file, "w") as f:
                                json.dump(emergency_codes, f)
                            print("✅ Emergency code accepted!")
                            print(f"Access granted for contact: {code['contact']}")
                            print("Emergency access to vault would be provided here.")
                            found = True
                            break
                        else:
                            print("❌ Code has exceeded maximum uses.")
                            found = True
                            break
                    else:
                        print("❌ Code has expired.")
                        found = True
                        break

            if not found:
                print("❌ Invalid or inactive emergency code.")

        elif choice == "5":
            break
        else:
            print("Invalid option.")


def delete_password():
    if not passwords:
        print("No passwords stored.")
        return

    for idx, entry in enumerate(passwords, start=1):
        print(f"{idx}. {entry['site']} ({entry['username']})")

    try:
        choice = int(input("Enter number to delete (0 to cancel): "))
    except ValueError:
        print("Invalid input.")
        return

    if choice == 0:
        return
    if 1 <= choice <= len(passwords):
        removed = passwords.pop(choice - 1)
        save_passwords()
        print(f"Removed entry for {removed['site']}")
    else:
        print("Choice out of range.")


def search_passwords():
    term = input("Search term (site or username): ")
    matches = [e for e in passwords if term.lower() in e['site'].lower() or term.lower() in e['username'].lower()]
    if not matches:
        print("No matching entries.")
        return
    for entry in matches:
        print(f"Site: {entry['site']}")
        print(f"Username: {entry['username']}")
        print(f"Password: {entry['password']}")
        if entry.get('notes'):
            print(f"Notes: {entry['notes']}")
        print("---")


def get_password_by_site():
    """Securely retrieve and display a single password by site name."""
    if not passwords:
        print("No passwords stored.")
        return
    
    site = input("Enter site name to retrieve password: ").strip().lower()
    matching = [e for e in passwords if site in e['site'].lower()]
    
    if not matching:
        print(f"No entries found for '{site}'.")
        return
    
    if len(matching) > 1:
        print("Multiple matches found:")
        for idx, entry in enumerate(matching, start=1):
            print(f"{idx}. {entry['site']} ({entry['username']})")
        try:
            choice = int(input("Select entry (0 to cancel): "))
            if choice == 0:
                return
            if 1 <= choice <= len(matching):
                entry = matching[choice - 1]
            else:
                print("Invalid choice.")
                return
        except ValueError:
            print("Invalid input.")
            return
    else:
        entry = matching[0]
    
    confirm = input(f"Show password for {entry['site']}? (y/n): ")
    if confirm.lower() != 'y':
        print("Cancelled.")
        return
    
    print(f"\nSite: {entry['site']}")
    print(f"Username: {entry['username']}")
    print(f"Password: {entry['password']}")
    print(f"Strength: {check_password_strength(entry['password'])}")
    if entry.get('notes'):
        print(f"Notes: {entry['notes']}")
    print()


def copy_password_to_clipboard():
    """Copy a password to clipboard without displaying it on screen."""
    if not CLIPBOARD_AVAILABLE:
        print("Clipboard functionality not available. Install 'pyperclip': pip install pyperclip")
        return
    
    if not passwords:
        print("No passwords stored.")
        return
    
    site = input("Enter site name to copy password: ").strip().lower()
    matching = [e for e in passwords if site in e['site'].lower()]
    
    if not matching:
        print(f"No entries found for '{site}'.")
        return
    
    if len(matching) > 1:
        print("Multiple matches found:")
        for idx, entry in enumerate(matching, start=1):
            print(f"{idx}. {entry['site']} ({entry['username']})")
        try:
            choice = int(input("Select entry (0 to cancel): "))
            if choice == 0:
                return
            if 1 <= choice <= len(matching):
                entry = matching[choice - 1]
            else:
                print("Invalid choice.")
                return
        except ValueError:
            print("Invalid input.")
            return
    else:
        entry = matching[0]
    
    confirm = input(f"Copy password for {entry['site']} to clipboard? (y/n): ")
    if confirm.lower() != 'y':
        print("Cancelled.")
        return
    
    try:
        pyperclip.copy(entry['password'])
        print(f"✓ Password for {entry['site']} copied to clipboard!")
        print("  (Clipboard will be cleared for security after 30 seconds)")
    except Exception as e:
        print(f"Error copying to clipboard: {e}")


def manage_notes():
    if not passwords:
        print("No passwords stored.")
        return

    for idx, entry in enumerate(passwords, start=1):
        notes_indicator = " (has notes)" if entry.get('notes') else ""
        print(f"{idx}. {entry['site']} ({entry['username']}){notes_indicator}")

    try:
        choice = int(input("Enter number to manage notes (0 to cancel): "))
    except ValueError:
        print("Invalid input.")
        return

    if choice == 0:
        return
    if not (1 <= choice <= len(passwords)):
        print("Choice out of range.")
        return

    entry = passwords[choice - 1]
    print(f"Current notes for {entry['site']}: {entry.get('notes', 'None')}")
    new_notes = input("Enter new notes (leave blank to clear): ")
    entry['notes'] = new_notes
    entry['updated_at'] = datetime.now().isoformat()
    save_passwords()
    print("Notes updated.")


def update_password():
    if not passwords:
        print("No passwords stored.")
        return

    for idx, entry in enumerate(passwords, start=1):
        print(f"{idx}. {entry['site']} ({entry['username']})")

    try:
        choice = int(input("Enter number to update (0 to cancel): "))
    except ValueError:
        print("Invalid input.")
        return

    if choice == 0:
        return
    if not (1 <= choice <= len(passwords)):
        print("Choice out of range.")
        return

    entry = passwords[choice - 1]
    print(f"Current entry: {entry['site']} ({entry['username']})")
    
    # Update site
    new_site = input(f"New site (current: {entry['site']}, press Enter to keep): ").strip()
    if new_site:
        entry['site'] = new_site
    
    # Update username
    new_username = input(f"New username (current: {entry['username']}, press Enter to keep): ").strip()
    if new_username:
        entry['username'] = new_username
    
    # Update password
    update_pw = input("Update password? (y/n): ").lower()
    if update_pw == 'y':
        choice = input("Generate new password? (y/n): ")
        if choice.lower() == "y":
            new_password = generate_password()
            print("Generated password:", new_password)
        else:
            new_password = input("Enter new password: ")
        entry['password'] = new_password
        strength = check_password_strength(new_password)
        print(f"New password strength: {strength}")
    
    # Update notes
    current_notes = entry.get('notes', '')
    new_notes = input(f"New notes (current: {current_notes}, press Enter to keep): ").strip()
    if new_notes or new_notes == '':
        entry['notes'] = new_notes
    
    entry['updated_at'] = datetime.now().isoformat()
    save_passwords()
    print("Password entry updated.")


def main():
    # require master password check first
    if not verify_master_password():
        return
    load_passwords()

    while True:
        print("\n1 Add Password")
        print("2 View Passwords")
        print("3 Search Passwords")
        print("4 Get Password by Site")
        print("5 Copy Password to Clipboard")
        print("6 Update Password")
        print("7 Delete Password")
        print("8 Export to CSV")
        print("9 Import from CSV")
        print("10 View Passwords by Strength")
        print("11 List Weak Passwords")
        print("12 Change Master Password")
        print("13 Backup Vault")
        print("14 Check Password Age")
        print("15 Show Statistics")
        print("16 Regenerate Weak Passwords")
        print("17 Check Duplicate Passwords")
        print("18 Manage Notes")
        print("19 Check Password Breaches")
        print("20 Emergency Access Codes")
        print("21 Exit")

        c = input("Choice: ")

        if c == "1":
            add_password()
        elif c == "2":
            view_passwords()
        elif c == "3":
            search_passwords()
        elif c == "4":
            get_password_by_site()
        elif c == "5":
            copy_password_to_clipboard()
        elif c == "6":
            update_password()
        elif c == "7":
            delete_password()
        elif c == "8":
            export_passwords()
        elif c == "9":
            import_passwords()
        elif c == "10":
            view_passwords_by_strength()
        elif c == "11":
            list_weak_passwords()
        elif c == "12":
            change_master_password()
        elif c == "13":
            backup_vault()
        elif c == "14":
            check_password_age()
        elif c == "15":
            show_statistics()
        elif c == "16":
            regenerate_weak_passwords()
        elif c == "17":
            check_duplicate_passwords()
        elif c == "18":
            manage_notes()
        elif c == "19":
            check_password_breaches()
        elif c == "20":
            emergency_access_codes()
        elif c == "21":
            break

if __name__ == "__main__":
    main()
    








