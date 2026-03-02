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

    def format_scene(self):
        output = f"\nScene: {self.title} ({self.duration_seconds} sec)\n"
        output += self.description + "\n"
        for speaker, line in self.dialogues:
            output += f"{speaker}: {line}\n"
        return output


class Episode:
    def __init__(self, title):
        self.title = title
        self.scenes = []
        self.characters = {}

    def add_character(self, character):
        self.characters[character.name] = character

    def add_scene(self, scene):
        self.scenes.append(scene)

    def total_duration(self):
        return sum(scene.duration_seconds for scene in self.scenes)

    def to_dict(self):
        return {
            "title": self.title,
            "characters": {name: c.to_dict() for name, c in self.characters.items()},
            "scenes": [scene.to_dict() for scene in self.scenes],
        }

    def save_to_json(self, filename):
        with open(filename, "w", encoding="utf-8") as f:
            json.dump(self.to_dict(), f, indent=4)

    @staticmethod
    def load_from_json(filename):
        with open(filename, "r", encoding="utf-8") as f:
            data = json.load(f)

        episode = Episode(data["title"])

        for name, char_data in data.get("characters", {}).items():
            episode.add_character(Character.from_dict(char_data))

        for scene_data in data["scenes"]:
            episode.add_scene(Scene.from_dict(scene_data))

        return episode


def main():
    episode = Episode("The Quiet Summer")

    haruto = Character("Haruto", 16, "Protagonist")
    episode.add_character(haruto)

    scene = Scene("Morning Field", 40)
    scene.set_description("Haruto watering crops.")
    scene.add_dialogue("Haruto", "They look thirsty.")

    episode.add_scene(scene)

    episode.save_to_json("episode.json")


if __name__ == "__main__":
    main()