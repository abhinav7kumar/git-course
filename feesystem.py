tudents = {}

def add_student():
    student_id = input("Enter Student ID: ")
    name = input("Enter Student Name: ")
    students[student_id] = {
        "name": name,
        "fees_paid": 0
    }
    print("Student added successfully!")

def view_students():
    if not students:
        print("No students found.")
        return

    for sid, data in students.items():
        print(f"ID: {sid}, Name: {data['name']}, Fees Paid: {data['fees_paid']}")

def main():
    while True:
        print("\n===== FEES MANAGEMENT SYSTEM =====")
        print("1. Add Student")
        print("2. View Students")
        print("3. Exit")

        choice = input("Enter choice: ")

        if choice == "1":
            add_student()
        elif choice == "2":
            view_students()
        elif choice == "3":
            print("Exiting...")
            break
        else:
            print("Invalid choice!")

if __name__ == "__main__":
    main()