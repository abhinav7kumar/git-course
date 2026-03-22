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
    cout << "You can choose difficulty and use up to three hints during the game." << endl;

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
            cout << "4) Show current stats 5) Reset all stats 6) Custom difficulty\n";
            cout << "Enter 1, 2, 3, 4, 5 or 6: ";
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

            if (choice < 1 || choice > 6) {
                cout << "Invalid option. Please enter 1, 2, 3, 4, 5, or 6.\n";
            }
        } while (choice < 1 || choice > 6);

        double difficultyMultiplier = 1.0;
        string difficultyName = "";
        
        if (choice == 1) { 
            maxNumber = 10; 
            maxAttempts = 8; 
            difficultyMultiplier = 1.0;
            difficultyName = "Easy";
        }
        else if (choice == 2) { 
            maxNumber = 20; 
            maxAttempts = 6; 
            difficultyMultiplier = 1.5;
            difficultyName = "Medium";
        }
        else if (choice == 3) { 
            maxNumber = 50; 
            maxAttempts = 4; 
            difficultyMultiplier = 2.0;
            difficultyName = "Hard";
        }
        else if (choice == 6) {
            cout << "Enter custom max number (5-100): ";
            cin >> maxNumber;
            if (maxNumber < 5) maxNumber = 5;
            if (maxNumber > 100) maxNumber = 100;
            cout << "Enter custom attempts (1-20): ";
            cin >> maxAttempts;
            if (maxAttempts < 1) maxAttempts = 1;
            if (maxAttempts > 20) maxAttempts = 20;
            cout << "Custom challenge set: 1 to " << maxNumber << ", " << maxAttempts << " attempts.\n";
            // Custom difficulty multiplier based on range
            difficultyMultiplier = 1.0 + (maxNumber - 5) / 95.0;
            difficultyName = "Custom";
        }
        else { 
            maxNumber = 50; 
            maxAttempts = 4; 
            difficultyMultiplier = 2.0;
            difficultyName = "Hard";
        }

        int secret = rand() % maxNumber + 1;
        int attemptsLeft = maxAttempts;
        bool usedHint = false;
        bool usedRangeHint = false;
        bool usedDivisibilityHint = false;
        vector<int> guessHistory;
        vector<int> tooLowNumbers;
        vector<int> tooHighNumbers;
        auto gameStartTime = chrono::high_resolution_clock::now();

        cout << "Guess the secret number in range 1 to " << maxNumber << ".\n";
        cout << "Tip: enter 0 to unlock one bonus hint (odd/even)." << endl;
        cout << "Tip: enter -1 to unlock a second bonus hint (range half)." << endl;
        cout << "Tip: enter -2 to unlock a third bonus hint (divisibility by 3/5)." << endl;
        cout << "Bonus: Solve faster for extra points!\n";

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
                    cout << "Hint already used. No extra hints available for odd/even.\n";
                    continue;
                }
            }

            if (guess == -1) {
                if (!usedRangeHint) {
                    usedRangeHint = true;
                    int mid = maxNumber / 2;
                    if (secret <= mid) {
                        cout << "Range hint: The number is in the lower half (1 to " << mid << ")." << endl;
                    } else {
                        cout << "Range hint: The number is in the upper half (" << (mid + 1) << " to " << maxNumber << ")." << endl;
                    }
                    continue;
                } else {
                    cout << "Range hint already used. No extra range hints available.\n";
                    continue;
                }
            }

            if (guess == -2) {
                if (!usedDivisibilityHint) {
                    usedDivisibilityHint = true;
                    bool div3 = (secret % 3 == 0);
                    bool div5 = (secret % 5 == 0);
                    cout << "Divisibility hint: " << (div3 ? "divisible by 3" : "not divisible by 3") << ", " << (div5 ? "divisible by 5" : "not divisible by 5") << "." << endl;
                    continue;
                } else {
                    cout << "Divisibility hint already used. No extra divisibility hints available.\n";
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
                auto gameEndTime = chrono::high_resolution_clock::now();
                auto elapsedSeconds = chrono::duration_cast<chrono::seconds>(gameEndTime - gameStartTime).count();
                
                int baseScore = attemptsLeft * 10;
                
                // Time-based bonus: Award points for solving quickly
                int timeBonus = 0;
                if (elapsedSeconds <= 10) {
                    timeBonus = 50;  // Solved in 10 seconds or less
                } else if (elapsedSeconds <= 30) {
                    timeBonus = 30;  // Solved in 30 seconds
                } else if (elapsedSeconds <= 60) {
                    timeBonus = 20;  // Solved in 1 minute
                } else if (elapsedSeconds <= 120) {
                    timeBonus = 10;  // Solved in 2 minutes
                }
                
                int hintPenalty = (usedHint ? 15 : 0) + (usedRangeHint ? 10 : 0) + (usedDivisibilityHint ? 10 : 0);
                int scoreBeforeMultiplier = baseScore + timeBonus - hintPenalty;
                finalScore = (int)(scoreBeforeMultiplier * difficultyMultiplier);
                finalScore = max(0, finalScore);

                cout << "Correct! Puzzle unlocked in " << elapsedSeconds << " seconds." << endl;
                int hintCount = (usedHint ? 1 : 0) + (usedRangeHint ? 1 : 0) + (usedDivisibilityHint ? 1 : 0);
                cout << "Your score: " << finalScore << " (" << difficultyName << " difficulty x" << difficultyMultiplier 
                    << " multiplier, base: " << scoreBeforeMultiplier << ", " << hintCount << " hint" 
                    << (hintCount == 1 ? "" : "s") << " used)" << endl;
                cout << "Guess history: ";
                for (size_t i = 0; i < guessHistory.size(); ++i) {
                    cout << guessHistory[i] << (i + 1 < guessHistory.size() ? ", " : "\n");
                }
                
                // Display wrong numbers summary on win
                cout << "\nWrong Numbers Summary:\n";
                if (!tooLowNumbers.empty()) {
                    cout << "Too low (" << tooLowNumbers.size() << "): ";
                    for (size_t i = 0; i < tooLowNumbers.size(); ++i) {
                        cout << tooLowNumbers[i] << (i + 1 < tooLowNumbers.size() ? ", " : "\n");
                    }
                }
                if (!tooHighNumbers.empty()) {
                    cout << "Too high (" << tooHighNumbers.size() << "): ";
                    for (size_t i = 0; i < tooHighNumbers.size(); ++i) {
                        cout << tooHighNumbers[i] << (i + 1 < tooHighNumbers.size() ? ", " : "\n");
                    }
                }
                if (tooLowNumbers.empty() && tooHighNumbers.empty()) {
                    cout << "(No wrong guesses - perfect play!)\n";
                }
                cout << "\n";

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

            if (guess < secret) {
                cout << "Too low!" << endl;
                tooLowNumbers.push_back(guess);
            }
            else {
                cout << "Too high!" << endl;
                tooHighNumbers.push_back(guess);
            }

            // Display wrong numbers tracker
            cout << "\n--- Wrong Numbers Tracker ---\n";
            if (!tooLowNumbers.empty()) {
                cout << "Too low: ";
                for (size_t i = 0; i < tooLowNumbers.size(); ++i) {
                    cout << tooLowNumbers[i] << (i + 1 < tooLowNumbers.size() ? ", " : "\n");
                }
            }
            if (!tooHighNumbers.empty()) {
                cout << "Too high: ";
                for (size_t i = 0; i < tooHighNumbers.size(); ++i) {
                    cout << tooHighNumbers[i] << (i + 1 < tooHighNumbers.size() ? ", " : "\n");
                }
            }
            cout << "-----------------------------\n\n";

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
            
            // Display wrong numbers summary on loss
            cout << "\nWrong Numbers Summary:\n";
            if (!tooLowNumbers.empty()) {
                cout << "Too low (" << tooLowNumbers.size() << "): ";
                for (size_t i = 0; i < tooLowNumbers.size(); ++i) {
                    cout << tooLowNumbers[i] << (i + 1 < tooLowNumbers.size() ? ", " : "\n");
                }
            }
            if (!tooHighNumbers.empty()) {
                cout << "Too high (" << tooHighNumbers.size() << "): ";
                for (size_t i = 0; i < tooHighNumbers.size(); ++i) {
                    cout << tooHighNumbers[i] << (i + 1 < tooHighNumbers.size() ? ", " : "\n");
                }
            }
            if (tooLowNumbers.empty() && tooHighNumbers.empty()) {
                cout << "(No guesses made before running out of attempts)\n";
            }
            cout << "\n";
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