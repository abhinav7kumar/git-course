import json
import os
import random
import string
import csv

passwords = []

def load_passwords():
    global passwords
    if os.path.exists("vault.json"):
        with open("vault.json", "r") as f:
            passwords = json.load(f)

def save_passwords():
    with open("vault.json", "w") as f:
        json.dump(passwords, f)

def generate_password(length=12):
    characters = string.ascii_letters + string.digits + string.punctuation
    return "".join(random.choice(characters) for _ in range(length))

def add_password():
    site = input("Website: ")
    username = input("Username: ")

    choice = input("Generate password? (y/n): ")

    if choice.lower() == "y":
        password = generate_password()
        print("Generated password:", password)
    else:
        password = input("Enter password: ")

    passwords.append({
        "site": site,
        "username": username,
        "password": password
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

    if new_site:
        entry['site'] = new_site
    if new_user:
        entry['username'] = new_user
    entry['password'] = new_pass

    save_passwords()
    print("Entry updated.")


def main():
    load_passwords()

    while True:
        print("\n1 Add Password")
        print("2 View Passwords")
        print("3 Search Passwords")
        print("4 Update Password")
        print("5 Delete Password")
        print("6 Export to CSV")
        print("7 Exit")

        c = input("Choice: ")

        if c == "1":
            add_password()
        elif c == "2":
            view_passwords()
        elif c == "3":
            search_passwords()
        elif c == "4":
            update_password()
        elif c == "5":
            delete_password()
        elif c == "6":
            export_passwords()
        elif c == "7":
            break

if __name__ == "__main__":
    main()