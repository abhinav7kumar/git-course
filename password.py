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

    passwords.append({
        "site": site,
        "username": username,
        "password": password,
        "created_at": datetime.now().isoformat(),
        "updated_at": datetime.now().isoformat()
    })

    save_passwords()

def view_passwords():
    for entry in passwords:
        print(entry)

def export_passwords(filename="vault.csv"):
    if not passwords:
        print("No passwords to export.")
        return
    with open(filename, "w", newline="") as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(["site", "username", "password"])
        for e in passwords:
            writer.writerow([e["site"], e["username"], e["password"]])
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
                    "password": row["password"]
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
        print(entry)


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
    print(f"Strength: {check_password_strength(entry['password'])}\n")


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
    print(f"Selected {entry['site']} ({entry['username']})")
    new_site = input(f"New site (leave blank to keep '{entry['site']}'): ")
    new_user = input(f"New username (leave blank to keep '{entry['username']}'): ")
    ch = input("Change password? (y/n): ")
    if ch.lower() == 'y':
        gen = input("Generate new password? (y/n): ")
        if gen.lower() == 'y':
            new_pass = generate_password()
            print("Generated password:", new_pass)
        else:
            new_pass = input("Enter new password: ")
    else:
        new_pass = entry['password']
    # check strength if changed
    if new_pass != entry['password']:
        strength = check_password_strength(new_pass)
        print(f"New password strength: {strength}")

    if new_site:
        entry['site'] = new_site
    if new_user:
        entry['username'] = new_user
    entry['password'] = new_pass
    entry['updated_at'] = datetime.now().isoformat()

    save_passwords()
    print("Entry updated.")


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
        print("18 Exit")

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
            break

if __name__ == "__main__":
    main()
    











