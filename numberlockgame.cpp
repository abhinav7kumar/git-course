#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <vector>
using namespace std;

int main() {
    srand((unsigned int) time(nullptr));
    cout << "Welcome to the Number Lock Puzzle!" << endl;
    cout << "You can choose difficulty and use one hint during the game." << endl;

    int highScore = 0;
    int bestStreak = 0;
    int gamesPlayed = 0;
    int wins = 0;

    {
        ifstream inFile("highscore.txt");
        if (inFile >> highScore) {
            cout << "Current high score: " << highScore << "\n";
        } else {
            cout << "No high score yet. Be the first!\n";
            highScore = 0;
        }
    }

    {
        ifstream inFile("beststreak.txt");
        if (inFile >> bestStreak) {
            cout << "Best win streak: " << bestStreak << "\n";
        } else {
            cout << "No streak recorded yet. Start one now!\n";
            bestStreak = 0;
        }
    }

    {
        ifstream inFile("stats.txt");
        if (inFile >> gamesPlayed >> wins) {
            cout << "Total games: " << gamesPlayed << ", total wins: " << wins << " (" << (gamesPlayed > 0 ? (wins * 100 / gamesPlayed) : 0) << "% win rate)\n";
        } else {
            cout << "No stats yet. Play to build your record!\n";
            gamesPlayed = 0;
            wins = 0;
        }
    }

    int currentStreak = 0;

    while (true) {
        int choice;
        int maxAttempts;
        int maxNumber;

        do {
            cout << "Select difficulty: 1) Easy (1-10, 8 attempts) 2) Medium (1-20, 6 attempts) 3) Hard (1-50, 4 attempts)\n";
            cout << "4) Show current stats 5) Reset all stats\n";
            cout << "Enter 1, 2, 3, 4 or 5: ";
            cin >> choice;

            if (choice == 4) {
                cout << "\n=== Current Stats ===\n";
                cout << "High score: " << highScore << "\n";
                cout << "Best streak: " << bestStreak << "\n";
                cout << "Games played: " << gamesPlayed << "\n";
                cout << "Wins: " << wins << "\n";
                cout << "Win rate: " << (gamesPlayed > 0 ? (wins * 100 / gamesPlayed) : 0) << "%\n";
                cout << "Current streak: " << currentStreak << "\n";
                cout << "======================\n\n";
                continue;
            }

            if (choice == 5) {
                cout << "\nResetting all stats...\n";
                highScore = 0;
                bestStreak = 0;
                gamesPlayed = 0;
                wins = 0;
                currentStreak = 0;

                ofstream out1("highscore.txt");
                if (out1) out1 << highScore;
                ofstream out2("beststreak.txt");
                if (out2) out2 << bestStreak;
                ofstream out3("stats.txt");
                if (out3) out3 << gamesPlayed << " " << wins;

                cout << "All stats reset.\n\n";
                continue;
            }

            if (choice < 1 || choice > 3) {
                cout << "Invalid option. Please enter 1, 2, 3, 4, or 5.\n";
            }
        } while (choice < 1 || choice > 3);

        if (choice == 1) { maxNumber = 10; maxAttempts = 8; }
        else if (choice == 2) { maxNumber = 20; maxAttempts = 6; }
        else { maxNumber = 50; maxAttempts = 4; }

        int secret = rand() % maxNumber + 1;
        int attemptsLeft = maxAttempts;
        bool usedHint = false;
        vector<int> guessHistory;

        cout << "Guess the secret number in range 1 to " << maxNumber << ".\n";
        cout << "Tip: enter 0 to unlock one bonus hint (odd/even)." << endl;

        bool solved = false;
        int finalScore = 0;

        while (attemptsLeft > 0) {
            int guess;
            cout << "Attempts left: " << attemptsLeft << ". Enter your guess: ";
            cin >> guess;

            if (guess == 0) {
                if (!usedHint) {
                    usedHint = true;
                    cout << "Hint: The secret number is " << (secret % 2 == 0 ? "even" : "odd") << "." << endl;
                    continue;
                } else {
                    cout << "Hint already used. No extra hints available." << endl;
                    continue;
                }
            }

            if (guess < 1 || guess > maxNumber) {
                cout << "Invalid guess. Enter a number between 1 and " << maxNumber << "." << endl;
                continue;
            }

            guessHistory.push_back(guess);

            if (guess == secret) {
                solved = true;
                finalScore = attemptsLeft * 10;
                if (usedHint) finalScore = max(0, finalScore - 15);

                cout << "Correct! Puzzle unlocked." << endl;
                cout << "Your score: " << finalScore << " (" << (usedHint ? "hint used" : "no hint") << ")" << endl;
                cout << "Guess history: ";
                for (size_t i = 0; i < guessHistory.size(); ++i) {
                    cout << guessHistory[i] << (i + 1 < guessHistory.size() ? ", " : "\n");
                }

                if (finalScore > highScore) {
                    highScore = finalScore;
                    ofstream outFile("highscore.txt");
                    if (outFile) outFile << highScore;
                    cout << "New high score! " << highScore << " saved." << endl;
                } else {
                    cout << "High score stays: " << highScore << "." << endl;
                }

                currentStreak++;
                wins++;
                gamesPlayed++;
                cout << "Current win streak: " << currentStreak << "\n";
                if (currentStreak > bestStreak) {
                    bestStreak = currentStreak;
                    ofstream streakOut("beststreak.txt");
                    if (streakOut) streakOut << bestStreak;
                    cout << "New best streak! " << bestStreak << " saved." << endl;
                } else {
                    cout << "Best streak remains: " << bestStreak << "." << endl;
                }

                {
                    ofstream statsOut("stats.txt");
                    if (statsOut) statsOut << gamesPlayed << " " << wins;
                }
                break;
            }

            attemptsLeft--;

            if (guess < secret)
                cout << "Too low!" << endl;
            else
                cout << "Too high!" << endl;

            if (attemptsLeft > 0) {
                cout << "Try again.\n";
            }
        }

        if (!solved) {
            gamesPlayed++;
            cout << "Game over. You failed to unlock the puzzle." << endl;
            cout << "Secret number was " << secret << "." << endl;
            cout << "Your guesses: ";
            for (size_t i = 0; i < guessHistory.size(); ++i) {
                cout << guessHistory[i] << (i + 1 < guessHistory.size() ? ", " : "\n");
            }
            if (guessHistory.empty()) {
                cout << "(No valid guesses entered this round)\n";
            }
            cout << "Your score: 0" << endl;
            cout << "High score remains: " << highScore << "." << endl;

            currentStreak = 0;
            cout << "Win streak reset to 0." << endl;

            cout << "Lock cooldown engaged for 5 seconds..." << endl;
            this_thread::sleep_for(chrono::seconds(5));
            cout << "You can retry after cooldown." << endl;
        }

        char playAgain;
        cout << "Do you want to play another round? (y/n): ";
        cin >> playAgain;
        if (playAgain != 'y' && playAgain != 'Y') {
            cout << "Thanks for playing! Final high score: " << highScore << ", best streak: " << bestStreak << ".\n";
            break;
        }
    }

    return 0;
}