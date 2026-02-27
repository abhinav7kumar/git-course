class Character:
    def __init__(self, name, age, role):
        self.name = name
        self.age = age
        self.role = role

    def describe(self):
        return f"{self.name} ({self.role}), Age: {self.age}"


def main():
    print("Whispers of Summer - Production Manager")

    haruto = Character("Haruto", 16, "Protagonist")
    aoi = Character("Aoi", 16, "Female Lead")
    sachiko = Character("Sachiko", 70, "Grandmother")

    print(haruto.describe())
    print(aoi.describe())
    print(sachiko.describe())


if __name__ == "__main__":
    main()