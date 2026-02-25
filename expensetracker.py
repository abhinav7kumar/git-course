import json

def save_to_file():
    data = [e.__dict__ for e in expenses]
    with open("expenses.json", "w") as f:
        json.dump(data, f)
def menu():
    print("\n==== Expense Tracker ====")
    print("1. Add Expense")
    print("2. View Expenses")
    print("3. Exit")
class Expense:
    def __init__(self, amount, category, description):
        self.amount = amount
        self.category = category
        self.description = description
expenses = []

def add_expense():
    amount = float(input("Amount: "))
    category = input("Category: ")
    description = input("Description: ")

    expense = Expense(amount, category, description)
    expenses.append(expense)
    print("Expense added successfully.")
def view_expenses():
    for i, e in enumerate(expenses):
        print(f"{i+1}. {e.amount} | {e.category} | {e.description}")
def main():
    while True:
        menu()
        choice = input("Enter choice: ")

        if choice == "3":
            break

if __name__ == "__main__":
    main()