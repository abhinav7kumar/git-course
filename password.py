passwords = []

def main():
    print("Simple Password Manager")

    while True:
        print("\nOptions:")
        print("1 Add Password")
        print("2 View Passwords")
        print("3 Exit")

        choice = input("Select option: ")

        if choice == "1":
            print("Add password feature coming soon.")
        elif choice == "2":
            print("View password feature coming soon.")
        elif choice == "3":
            print("Exiting...")
            break
        else:
            print("Invalid option.")

if __name__ == "__main__":
    main()