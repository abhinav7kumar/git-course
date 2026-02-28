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


def create_scene_interactively():
    title = input("Scene title: ")
    duration = int(input("Duration (seconds): "))
    scene = Scene(title, duration)

    description = input("Scene description: ")
    scene.set_description(description)

    while True:
        add = input("Add dialogue? (y/n): ").lower()
        if add != "y":
            break
        character = input("Character name: ")
        line = input("Dialogue line: ")
        scene.add_dialogue(character, line)

    return scene


def main():
    episode_title = input("Enter episode title: ")
    episode = Episode(episode_title)

    while True:
        print("\n1. Add Scene")
        print("2. Save Episode")
        print("3. Export Script")
        print("4. Exit")

        choice = input("Choose option: ")

        if choice == "1":
            scene = create_scene_interactively()
            episode.add_scene(scene)

        elif choice == "2":
            filename = input("Enter JSON filename: ")
            episode.save_to_json(filename)

        elif choice == "3":
            filename = input("Enter TXT filename: ")
            episode.export_to_file(filename)

        elif choice == "4":
            break

        else:
            print("Invalid choice.")


if __name__ == "__main__":
    main()