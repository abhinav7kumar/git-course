class Character:
    def __init__(self, name, age, role):
        self.name = name
        self.age = age
        self.role = role

    def describe(self):
        return f"{self.name} ({self.role}), Age: {self.age}"


class Scene:
    def __init__(self, title, duration_seconds):
        self.title = title
        self.duration_seconds = duration_seconds
        self.description = ""

    def set_description(self, text):
        self.description = text

    def info(self):
        return f"Scene: {self.title} ({self.duration_seconds} sec)"


def main():
    print("Whispers of Summer - Production Manager")

    scene1 = Scene("Morning Field", 40)
    scene1.set_description("Haruto watering rice fields while Sachiko watches.")

    print(scene1.info())


if __name__ == "__main__":
    main()