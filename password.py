passwords = []

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
    print("Password saved.")

def view_passwords():
    if not passwords:
        print("No passwords stored.")
        return

    print("\nSaved Passwords:")
    for i, entry in enumerate(passwords, start=1):
        print(f"{i}. {entry['site']} | {entry['username']} | {entry['password']}")

def main():
    print("Simple Password Manager")

    while True:
        print("\nOptions:")
        print("1 Add Password")
        print("2 View Passwords")
        print("3 Exit")

        choice = input("Select option: ")

        if choice == "1":
            add_password()
        elif choice == "2":
            view_passwords()
        elif choice == "3":
            print("Exiting...")
            break
        else:
            print("Invalid option.")

if __name__ == "__main__":
    main()