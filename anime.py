# anime_project.py

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
        self.dialogues = []

    def set_description(self, text):
        self.description = text

    def add_dialogue(self, character, line):
        self.dialogues.append((character.name, line))

    def info(self):
        return f"{self.title} ({self.duration_seconds} sec)"

    def print_scene(self):
        print(f"\nScene: {self.title}")
        print(self.description)
        for speaker, line in self.dialogues:
            print(f"{speaker}: {line}")


class Episode:
    def __init__(self, title):
        self.title = title
        self.scenes = []

    def add_scene(self, scene):
        self.scenes.append(scene)

    def total_duration(self):
        return sum(scene.duration_seconds for scene in self.scenes)

    def summary(self):
        print(f"\nEpisode: {self.title}")
        for scene in self.scenes:
            print("-", scene.info())
        print("Total Duration:", self.total_duration(), "seconds")

    def play(self):
        for scene in self.scenes:
            scene.print_scene()


def main():
    haruto = Character("Haruto", 16, "Protagonist")
    sachiko = Character("Sachiko", 70, "Grandmother")

    episode1 = Episode("The Quiet Summer")

    scene1 = Scene("Morning Field", 40)
    scene1.set_description("Haruto watering crops while Sachiko watches.")
    scene1.add_dialogue(sachiko, "You're giving them too much water.")
    scene1.add_dialogue(haruto, "They look thirsty.")

    episode1.add_scene(scene1)
    episode1.play()


if __name__ == "__main__":
    main()