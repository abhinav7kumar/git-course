def menu():
    print("\n==== Expense Tracker ====")
    print("1. Add Expense")
    print("2. View Expenses")
    print("3. Exit")

def main():
    while True:
        menu()
        choice = input("Enter choice: ")

        if choice == "3":
            break

if __name__ == "__main__":
    main()