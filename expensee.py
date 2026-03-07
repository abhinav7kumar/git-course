import json
import os
from datetime import datetime

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
    name = input("Expense name: ")
    amount = float(input("Amount: "))
    category = input("Category: ")

    expenses.append({
        "name": name,
        "amount": amount,
        "category": category,
        "date": datetime.now().strftime("%Y-%m-%d")
    })

def view_expenses():
    for i, e in enumerate(expenses, start=1):
        print(f"{i}. {e['name']} | ₹{e['amount']} | {e['category']} | {e['date']}")

def filter_category():
    cat = input("Enter category: ")

    for e in expenses:
        if e["category"] == cat:
            print(e)

def main():
    load_expenses()

    while True:
        print("\n1 Add")
        print("2 View")
        print("3 Filter Category")
        print("4 Exit")

        c = input("Choice: ")

        if c == "1":
            add_expense()
        elif c == "2":
            view_expenses()
        elif c == "3":
            filter_category()
        elif c == "4":
            save_expenses()
            break

if __name__ == "__main__":
    main()