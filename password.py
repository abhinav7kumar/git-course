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

    passwords.append({
        "site": site,
        "username": username,
        "password": password
    })

    save_passwords()

def view_passwords():
    for i, entry in enumerate(passwords, start=1):
        print(f"{i}. {entry['site']} | {entry['username']} | {entry['password']}")

def delete_password():
    view_passwords()
    index = int(input("Delete number: ")) - 1

    if 0 <= index < len(passwords):
        passwords.pop(index)
        save_passwords()

def search_password():
    site = input("Enter website to search: ")

    for entry in passwords:
        if entry["site"].lower() == site.lower():
            print(entry)

def main():
    load_passwords()

    while True:
        print("\n1 Add")
        print("2 View")
        print("3 Delete")
        print("4 Search")
        print("5 Exit")

        c = input("Choice: ")

        if c == "1":
            add_password()
        elif c == "2":
            view_passwords()
        elif c == "3":
            delete_password()
        elif c == "4":
            search_password()
        elif c == "5":
            break

if __name__ == "__main__":
    main()