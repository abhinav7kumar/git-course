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
def main():
    while True:
        menu()
        choice = input("Enter choice: ")

        if choice == "3":
            break

if __name__ == "__main__":
    main()