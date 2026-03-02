import json


class Character:
    def __init__(self, name, age=None, role=None):
        self.name = name
        self.age = age
        self.role = role

    def to_dict(self):
        return {
            "name": self.name,
            "age": self.age,
            "role": self.role
        }

    @staticmethod
    def from_dict(data):
        return Character(data["name"], data.get("age"), data.get("role"))


class Scene:
    def __init__(self, title, duration_seconds):
        self.title = title
        self.duration_seconds = duration_seconds
        self.description = ""
        self.dialogues = []

    def set_description(self, text):
        self.description = text

    def add_dialogue(self, character_name, line):
        self.dialogues.append((character_name, line))

    def to_dict(self):
        return {
            "title": self.title,
            "duration_seconds": self.duration_seconds,
            "description": self.description,
            "dialogues": self.dialogues,
        }

    @staticmethod
    def from_dict(data):
        scene = Scene(data["title"], data["duration_seconds"])
        scene.description = data["description"]
        scene.dialogues = data["dialogues"]
        return scene


class Episode:
    def __init__(self, title):
        self.title = title
        self.scenes = []
        self.characters = {}

    def add_character(self, character):
        self.characters[character.name] = character

    def list_characters(self):
        for name, char in self.characters.items():
            print(f"- {name} ({char.role})")

    def add_scene(self, scene):
        self.scenes.append(scene)

    def save_to_json(self, filename):
        with open(filename, "w", encoding="utf-8") as f:
            json.dump(self.to_dict(), f, indent=4)

    def to_dict(self):
        return {
            "title": self.title,
            "characters": {name: c.to_dict() for name, c in self.characters.items()},
            "scenes": [scene.to_dict() for scene in self.scenes],
        }


def main():
    episode = Episode(input("Episode title: "))

    while True:
        print("\n1. Add Character")
        print("2. List Characters")
        print("3. Exit")

        choice = input("Choose: ")

        if choice == "1":
            name = input("Name: ")
            age = input("Age: ")
            role = input("Role: ")
            episode.add_character(Character(name, age, role))

        elif choice == "2":
            episode.list_characters()

        elif choice == "3":
            break


if __name__ == "__main__":
    main()