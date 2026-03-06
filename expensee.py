expenses = []

def main():
    print("Simple Expense Manager")
    print("----------------------")

    while True:
        print("\nOptions:")
        print("1. Add Expense")
        print("2. View Expenses")
        print("3. Exit")

        choice = input("Choose an option: ")

        if choice == "1":
            print("Add expense feature coming soon.")
        elif choice == "2":
            print("View expenses feature coming soon.")
        elif choice == "3":
            print("Goodbye!")
            break
        else:
            print("Invalid option.")

if __name__ == "__main__":
    main()