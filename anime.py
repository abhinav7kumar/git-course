import json


class Character:
    def __init__(self, name, age, role):
        self.name = name
        self.age = age
        self.role = role


class Scene:
    def __init__(self, title, duration_seconds):
        self.title = title
        self.duration_seconds = duration_seconds
        self.description = ""
        self.dialogues = []

    def set_description(self, text):
        self.description = text

    def add_dialogue(self, character, line):
        self.dialogues.append((character.name, line))

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

    def add_scene(self, scene):
        self.scenes.append(scene)

    def total_duration(self):
        return sum(scene.duration_seconds for scene in self.scenes)

    def export_to_file(self, filename):
        with open(filename, "w", encoding="utf-8") as f:
            f.write(f"Episode: {self.title}\n")
            f.write(f"Total Duration: {self.total_duration()} sec\n")
            for scene in self.scenes:
                f.write(scene.format_scene())

    def save_to_json(self, filename):
        data = {
            "title": self.title,
            "scenes": [scene.to_dict() for scene in self.scenes],
        }
        with open(filename, "w", encoding="utf-8") as f:
            json.dump(data, f, indent=4)

    @staticmethod
    def load_from_json(filename):
        with open(filename, "r", encoding="utf-8") as f:
            data = json.load(f)

        episode = Episode(data["title"])
        for scene_data in data["scenes"]:
            episode.add_scene(Scene.from_dict(scene_data))
        return episode


def main():
    haruto = Character("Haruto", 16, "Protagonist")
    sachiko = Character("Sachiko", 70, "Grandmother")

    episode1 = Episode("The Quiet Summer")

    scene1 = Scene("Morning Field", 40)
    scene1.set_description("Haruto watering crops while Sachiko watches.")
    scene1.add_dialogue(sachiko, "You're giving them too much water.")
    scene1.add_dialogue(haruto, "They look thirsty.")

    episode1.add_scene(scene1)

    episode1.save_to_json("episode1.json")
    episode1.export_to_file("episode1.txt")


if __name__ == "__main__":
    main()