import json
import os

expenses = []

def load_expenses():
    global expenses
    if os.path.exists("expenses.json"):
        with open("expenses.json", "r") as file:
            expenses = json.load(file)

def save_expenses():
    with open("expenses.json", "w") as file:
        json.dump(expenses, file)

def add_expense():
    name = input("Enter expense name: ")
    amount = float(input("Enter amount: "))
    category = input("Enter category (food/travel/etc): ")

    expense = {
        "name": name,
        "amount": amount,
        "category": category
    }

    expenses.append(expense)
    print("Expense added successfully!")

def view_expenses():
    if not expenses:
        print("No expenses recorded.")
        return

    print("\nYour Expenses:")
    for i, expense in enumerate(expenses, start=1):
        print(f"{i}. {expense['name']} | ₹{expense['amount']} | {expense['category']}")

def delete_expense():
    view_expenses()
    index = int(input("Enter expense number to delete: ")) - 1

    if 0 <= index < len(expenses):
        removed = expenses.pop(index)
        print(f"Deleted: {removed['name']}")
    else:
        print("Invalid expense number.")

def show_summary():
    total = sum(expense["amount"] for expense in expenses)
    print(f"\nTotal Expenses: ₹{total}")

def main():
    load_expenses()

    while True:
        print("\n1 Add Expense")
        print("2 View Expenses")
        print("3 Delete Expense")
        print("4 Summary")
        print("5 Exit")

        choice = input("Choose: ")

        if choice == "1":
            add_expense()
            save_expenses()
        elif choice == "2":
            view_expenses()
        elif choice == "3":
            delete_expense()
            save_expenses()
        elif choice == "4":
            show_summary()
        elif choice == "5":
            save_expenses()
            break

if __name__ == "__main__":
    main()