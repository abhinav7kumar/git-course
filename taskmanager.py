def menu():
    print("\n==== TASK MANAGER ====")
    print("1. Add Task")
    print("2. View Tasks")
    print("3. Exit")

def main():
    while True:
        menu()
        choice = input("Enter choice: ")

        if choice == "3":
            print("Goodbye!")
            break

if __name__ == "__main__":
    main()