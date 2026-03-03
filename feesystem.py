students = {}

def add_student():
    student_id = input("Enter Student ID: ")
    name = input("Enter Student Name: ")
    total_fees = float(input("Enter Total Fees: "))

    students[student_id] = {
        "name": name,
        "total_fees": total_fees,
        "fees_paid": 0
    }
    print("Student added successfully!")

def pay_fees():
    student_id = input("Enter Student ID: ")

    if student_id in students:
        amount = float(input("Enter Amount to Pay: "))
        students[student_id]["fees_paid"] += amount
        print("Payment successful!")
    else:
        print("Student not found!")

def view_students():
    if not students:
        print("No students found.")
        return

    for sid, data in students.items():
        pending = data["total_fees"] - data["fees_paid"]
        print(f"ID: {sid}, Name: {data['name']}, Paid: {data['fees_paid']}, Pending: {pending}")

def main():
    while True:
        print("\n===== FEES MANAGEMENT SYSTEM =====")
        print("1. Add Student")
        print("2. Pay Fees")
        print("3. View Students")
        print("4. Exit")

        choice = input("Enter choice: ")

        if choice == "1":
            add_student()
        elif choice == "2":
            pay_fees()
        elif choice == "3":
            view_students()
        elif choice == "4":
            break
        else:
            print("Invalid choice!")

if __name__ == "__main__":
    main()