class Student:
    def __init__(self, student_id, name, total_fees):
        self.student_id = student_id
        self.name = name
        self.total_fees = total_fees
        self.fees_paid = 0

    def pay(self, amount):
        if self.fees_paid + amount > self.total_fees:
            return False
        self.fees_paid += amount
        return True

    def pending(self):
        return self.total_fees - self.fees_paid


students = {}

def add_student():
    student_id = input("Enter Student ID: ")
    name = input("Enter Student Name: ")
    total_fees = float(input("Enter Total Fees: "))
    students[student_id] = Student(student_id, name, total_fees)
    print("Student added successfully!")

def pay_fees():
    student_id = input("Enter Student ID: ")

    if student_id in students:
        amount = float(input("Enter Amount to Pay: "))
        if students[student_id].pay(amount):
            print("Payment successful!")
        else:
            print("Payment exceeds total fees!")
    else:
        print("Student not found!")

def view_students():
    for student in students.values():
        print(f"ID: {student.student_id}, Name: {student.name}, Paid: {student.fees_paid}, Pending: {student.pending()}")

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