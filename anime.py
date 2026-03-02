import json


class Character:
    def __init__(self, name, age=None, role=None):
        self.name = name
        self.age = age
        self.role = role

    def to_dict(self):
        return {"name": self.name, "age": self.age, "role": self.role}


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


class Episode:
    def __init__(self, title):
        self.title = title
        self.scenes = []
        self.characters = {}

    def add_character(self, character):
        self.characters[character.name] = character

    def add_scene(self, scene):
        self.scenes.append(scene)

    def list_scenes(self):
        for i, scene in enumerate(self.scenes):
            print(f"{i + 1}. {scene.title} ({scene.duration_seconds} sec)")

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
        print("2. Add Scene")
        print("3. List Scenes")
        print("4. Exit")

        choice = input("Choose: ")

        if choice == "1":
            name = input("Name: ")
            age = input("Age: ")
            role = input("Role: ")
            episode.add_character(Character(name, age, role))

        elif choice == "2":
            title = input("Scene title: ")
            duration = int(input("Duration (seconds): "))
            description = input("Description: ")

            scene = Scene(title, duration)
            scene.set_description(description)
            episode.add_scene(scene)

        elif choice == "3":
            episode.list_scenes()

        elif choice == "4":
            break


if __name__ == "__main__":
    main()