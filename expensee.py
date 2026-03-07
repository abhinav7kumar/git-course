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
    category = input("Enter category: ")

    expense = {
        "name": name,
        "amount": amount,
        "category": category
    }

    expenses.append(expense)

def view_expenses():
    for i, e in enumerate(expenses, start=1):
        print(f"{i}. {e['name']} | ₹{e['amount']} | {e['category']}")

def delete_expense():
    view_expenses()
    index = int(input("Delete number: ")) - 1
    expenses.pop(index)

def show_summary():
    total = sum(e["amount"] for e in expenses)
    print("Total:", total)

def category_summary():
    summary = {}

    for e in expenses:
        cat = e["category"]
        summary[cat] = summary.get(cat, 0) + e["amount"]

    print("\nCategory Summary:")
    for k, v in summary.items():
        print(k, ":", v)

def main():
    load_expenses()

    while True:
        print("\n1 Add")
        print("2 View")
        print("3 Delete")
        print("4 Total Summary")
        print("5 Category Summary")
        print("6 Exit")

        choice = input("Choice: ")

        if choice == "1":
            add_expense()
        elif choice == "2":
            view_expenses()
        elif choice == "3":
            delete_expense()
        elif choice == "4":
            show_summary()
        elif choice == "5":
            category_summary()
        elif choice == "6":
            save_expenses()
            break

if __name__ == "__main__":
    main()