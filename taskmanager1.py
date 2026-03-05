import json
import os
from datetime import datetime


class Task:
    def __init__(self, title, description="", due_date="", priority="Medium"):
        self.title = title
        self.description = description
        self.due_date = due_date
        self.priority = priority
        self.completed = False
        self.created_date = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

    def mark_complete(self):
        self.completed = True

    def mark_incomplete(self):
        self.completed = False

    def to_dict(self):
        return {
            "title": self.title,
            "description": self.description,
            "due_date": self.due_date,
            "priority": self.priority,
            "completed": self.completed,
            "created_date": self.created_date
        }

    def __str__(self):
        status = "✓" if self.completed else "✗"
        return f"[{status}] {self.title} | Priority: {self.priority} | Due: {self.due_date if self.due_date else 'N/A'}"


class TaskManager:
    def __init__(self, filename="tasks.json"):
        self.filename = filename
        self.tasks = []
        self.load_tasks()

    def add_task(self, title, description="", due_date="", priority="Medium"):
        task = Task(title, description, due_date, priority)
        self.tasks.append(task)
        self.save_tasks()
        return task

    def remove_task(self, title):
        self.tasks = [task for task in self.tasks if task.title != title]
        self.save_tasks()

    def mark_task_complete(self, title):
        for task in self.tasks:
            if task.title == title:
                task.mark_complete()
                self.save_tasks()
                return True
        return False

    def mark_task_incomplete(self, title):
        for task in self.tasks:
            if task.title == title:
                task.mark_incomplete()
                self.save_tasks()
                return True
        return False

    def get_all_tasks(self):
        return self.tasks

    def get_pending_tasks(self):
        return [task for task in self.tasks if not task.completed]

    def get_completed_tasks(self):
        return [task for task in self.tasks if task.completed]

    def get_task_by_priority(self, priority):
        return [task for task in self.tasks if task.priority == priority]

    def display_tasks(self, tasks):
        if not tasks:
            print("No tasks to display.")
            return
        print("\n" + "="*80)
        for idx, task in enumerate(tasks, 1):
            print(f"{idx}. {task}")
            if task.description:
                print(f"   Description: {task.description}")
        print("="*80 + "\n")

    def save_tasks(self):
        data = [task.to_dict() for task in self.tasks]
        with open(self.filename, 'w') as f:
            json.dump(data, f, indent=4)

    def load_tasks(self):
        if os.path.exists(self.filename):
            try:
                with open(self.filename, 'r') as f:
                    data = json.load(f)
                    self.tasks = []
                    for item in data:
                        task = Task(
                            item["title"],
                            item.get("description", ""),
                            item.get("due_date", ""),
                            item.get("priority", "Medium")
                        )
                        task.completed = item.get("completed", False)
                        task.created_date = item.get("created_date", "")
                        self.tasks.append(task)
            except json.JSONDecodeError:
                self.tasks = []


def display_menu():
    print("\n" + "="*50)
    print("   TASK MANAGER APPLICATION")
    print("="*50)
    print("1. Add a new task")
    print("2. View all tasks")
    print("3. View pending tasks")
    print("4. View completed tasks")
    print("5. Mark task as complete")
    print("6. Mark task as incomplete")
    print("7. Remove a task")
    print("8. View tasks by priority")
    print("9. Exit")
    print("="*50)


def get_task_choice(manager):
    tasks = manager.get_all_tasks()
    if not tasks:
        print("No tasks available.")
        return None
    
    manager.display_tasks(tasks)
    try:
        choice = int(input("Enter task number: ")) - 1
        if 0 <= choice < len(tasks):
            return tasks[choice].title
        else:
            print("Invalid choice.")
            return None
    except ValueError:
        print("Invalid input.")
        return None


def main():
    manager = TaskManager()
    
    while True:
        display_menu()
        choice = input("Enter your choice (1-9): ").strip()
        
        if choice == "1":
            title = input("Enter task title: ").strip()
            if not title:
                print("Title cannot be empty.")
                continue
            description = input("Enter description (optional): ").strip()
            due_date = input("Enter due date (optional, YYYY-MM-DD): ").strip()
            print("Priority levels: Low, Medium, High")
            priority = input("Enter priority (default: Medium): ").strip() or "Medium"
            
            manager.add_task(title, description, due_date, priority)
            print(f"✓ Task '{title}' added successfully!")
        
        elif choice == "2":
            print("\nAll Tasks:")
            manager.display_tasks(manager.get_all_tasks())
        
        elif choice == "3":
            print("\nPending Tasks:")
            manager.display_tasks(manager.get_pending_tasks())
        
        elif choice == "4":
            print("\nCompleted Tasks:")
            manager.display_tasks(manager.get_completed_tasks())
        
        elif choice == "5":
            title = get_task_choice(manager)
            if title and manager.mark_task_complete(title):
                print(f"✓ Task '{title}' marked as complete!")
        
        elif choice == "6":
            title = get_task_choice(manager)
            if title and manager.mark_task_incomplete(title):
                print(f"✓ Task '{title}' marked as incomplete!")
        
        elif choice == "7":
            title = get_task_choice(manager)
            if title:
                manager.remove_task(title)
                print(f"✓ Task '{title}' removed successfully!")
        
        elif choice == "8":
            print("Priority levels: Low, Medium, High")
            priority = input("Enter priority to filter: ").strip()
            tasks = manager.get_task_by_priority(priority)
            print(f"\nTasks with '{priority}' priority:")
            manager.display_tasks(tasks)
        
        elif choice == "9":
            print("Thank you for using Task Manager. Goodbye!")
            break
        
        else:
            print("Invalid choice. Please try again.")


if __name__ == "__main__":
    main()