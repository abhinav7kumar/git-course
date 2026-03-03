students = {}

def main():
    while True:
        print("\n===== FEES MANAGEMENT SYSTEM =====")
        print("1. Add Student")
        print("2. Exit")

        choice = input("Enter choice: ")

        if choice == "1":
            student_id = input("Enter Student ID: ")
            name = input("Enter Student Name: ")
            students[student_id] = {
                "name": name,
                "fees_paid": 0
            }
            print("Student added successfully!")
        elif choice == "2":
            print("Exiting...")
            break
        else:
            print("Invalid choice!")

if __name__ == "__main__":
    main()