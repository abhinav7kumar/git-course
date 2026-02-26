tasks = []

def add_task():
    title = input("Enter task title: ")
    tasks.append({"title": title})
    print("Task added.")

def view_tasks():
    for i, task in enumerate(tasks):
        print(f"{i+1}. {task['title']}")

def menu():
    print("\n==== TASK MANAGER ====")
    print("1. Add Task")
    print("2. View Tasks")
    print("3. Exit")

def main():
    while True:
        menu()
        choice = input("Enter choice: ")

        if choice == "1":
            add_task()
        elif choice == "2":
            view_tasks()
        elif choice == "3":
            print("Goodbye!")
            break

if __name__ == "__main__":
    main()