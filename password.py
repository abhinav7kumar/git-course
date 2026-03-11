import json
import os
import random
import string

passwords = []

def load_passwords():
    global passwords
    if os.path.exists("vault.json"):
        with open("vault.json", "r") as f:
            passwords = json.load(f)

def save_passwords():
    with open("vault.json", "w") as f:
        json.dump(passwords, f)

def add_password():
    site = input("Enter website/app name: ")
    username = input("Enter username: ")
    password = input("Enter password: ")

    entry = {
        "site": site,
        "username": username,
        "password": password
    }

    passwords.append(entry)
    save_passwords()
    print("Password saved.")

def view_passwords():
    if not passwords:
        print("No passwords stored.")
        return

    for i, entry in enumerate(passwords, start=1):
        print(f"{i}. {entry['site']} | {entry['username']} | {entry['password']}")

def delete_password():
    view_passwords()
    index = int(input("Enter number to delete: ")) - 1

    if 0 <= index < len(passwords):
        removed = passwords.pop(index)
        save_passwords()
        print(f"Deleted entry for {removed['site']}")
    else:
        print("Invalid number.")

def main():
    load_passwords()

    while True:
        print("\n1 Add Password")
        print("2 View Passwords")
        print("3 Delete Password")
        print("4 Exit")

        choice = input("Select option: ")

        if choice == "1":
            add_password()
        elif choice == "2":
            view_passwords()
        elif choice == "3":
            delete_password()
        elif choice == "4":
            break

if __name__ == "__main__":
    main()