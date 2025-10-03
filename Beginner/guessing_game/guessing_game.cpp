#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <vector>
#include <algorithm>

using namespace std;

class AdvancedGuessingGame {
private:
    int secretNumber;
    int maxAttempts;
    int attempts;
    int totalScore;
    int maxRange;
    int gamesPlayed;
    int gamesWon;
    vector<int> guessHistory;
    
    enum GameMode {
        CLASSIC,
        TIMED,
        REVERSE,
        MULTIPLAYER
    };
    
public:
    AdvancedGuessingGame() : totalScore(0), gamesPlayed(0), gamesWon(0), maxRange(100) {}
    
    void displayMainMenu();
    void setDifficulty();
    void setGameMode();
    void generateSecretNumber();
    void playClassicMode();
    void playTimedMode();
    void playReverseMode();
    void playMultiplayerMode();
    void displayHint(int guess);
    void displayStats();
    void saveGuess(int guess);
    void displayGuessHistory();
    void clearScreen();
    int getRandomNumber(int min, int max);
    bool playAgain();
};

void AdvancedGuessingGame::displayMainMenu() {
    cout << "=====================================" << endl;
    cout << "       ADVANCED NUMBER GUESSING" << endl;
    cout << "              GAME!" << endl;
    cout << "=====================================" << endl;
    cout << "Games Played: " << gamesPlayed << endl;
    cout << "Games Won: " << gamesWon << endl;
    cout << "Total Score: " << totalScore << endl;
    cout << "=====================================" << endl;
}

void AdvancedGuessingGame::setDifficulty() {
    int choice;
    
    cout << "\n=== SELECT DIFFICULTY ===" << endl;
    cout << "1. Easy (12 attempts, range 1-50)" << endl;
    cout << "2. Medium (8 attempts, range 1-100)" << endl;
    cout << "3. Hard (6 attempts, range 1-200)" << endl;
    cout << "4. Expert (4 attempts, range 1-500)" << endl;
    cout << "5. Impossible (3 attempts, range 1-1000)" << endl;
    cout << "Enter your choice (1-5): ";
    
    while (!(cin >> choice) || choice < 1 || choice > 5) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter 1-5: ";
    }
    
    switch (choice) {
        case 1:
            maxAttempts = 12;
            maxRange = 50;
            break;
        case 2:
            maxAttempts = 8;
            maxRange = 100;
            break;
        case 3:
            maxAttempts = 6;
            maxRange = 200;
            break;
        case 4:
            maxAttempts = 4;
            maxRange = 500;
            break;
        case 5:
            maxAttempts = 3;
            maxRange = 1000;
            break;
    }
}

void AdvancedGuessingGame::setGameMode() {
    int choice;
    
    cout << "\n=== SELECT GAME MODE ===" << endl;
    cout << "1. Classic Mode" << endl;
    cout << "2. Timed Mode (Coming Soon)" << endl;
    cout << "3. Reverse Mode" << endl;
    cout << "4. Multiplayer Mode" << endl;
    cout << "Enter your choice (1-4): ";
    
    while (!(cin >> choice) || choice < 1 || choice > 4) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter 1-4: ";
    }
    
    switch (choice) {
        case 1:
            playClassicMode();
            break;
        case 2:
            cout << "Timed mode coming in next version!" << endl;
            playClassicMode();
            break;
        case 3:
            playReverseMode();
            break;
        case 4:
            playMultiplayerMode();
            break;
    }
}

int AdvancedGuessingGame::getRandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void AdvancedGuessingGame::generateSecretNumber() {
    secretNumber = getRandomNumber(1, maxRange);
    attempts = 0;
    guessHistory.clear();
}

void AdvancedGuessingGame::saveGuess(int guess) {
    guessHistory.push_back(guess);
}

void AdvancedGuessingGame::displayGuessHistory() {
    if (guessHistory.empty()) return;
    
    cout << "\nYour guesses: ";
    for (size_t i = 0; i < guessHistory.size(); ++i) {
        cout << guessHistory[i];
        if (i < guessHistory.size() - 1) cout << ", ";
    }
    cout << endl;
}

void AdvancedGuessingGame::displayHint(int guess) {
    int difference = abs(guess - secretNumber);
    
    if (difference == 0) return;
    
    cout << "💡 Hint: ";
    
    if (difference <= maxRange * 0.05) { // 5% of range
        cout << "🔥 VERY HOT! ";
    } else if (difference <= maxRange * 0.1) { // 10% of range
        cout << "🔥 Hot! ";
    } else if (difference <= maxRange * 0.2) { // 20% of range
        cout << "🌡️  Warm ";
    } else if (difference <= maxRange * 0.4) { // 40% of range
        cout << "💨 Cool ";
    } else {
        cout << "❄️  Cold ";
    }
    
    if (guess < secretNumber) {
        cout << "Try a HIGHER number." << endl;
    } else {
        cout << "Try a LOWER number." << endl;
    }
}

void AdvancedGuessingGame::playClassicMode() {
    int guess;
    bool won = false;
    
    generateSecretNumber();
    gamesPlayed++;
    
    cout << "\n🎮 CLASSIC MODE" << endl;
    cout << "Range: 1 to " << maxRange << endl;
    cout << "Attempts allowed: " << maxAttempts << endl;
    cout << "Good luck!\n" << endl;
    
    while (attempts < maxAttempts) {
        cout << "Attempt " << (attempts + 1) << "/" << maxAttempts << endl;
        cout << "Enter your guess: ";
        
        while (!(cin >> guess)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number: ";
        }
        
        attempts++;
        saveGuess(guess);
        
        if (guess == secretNumber) {
            won = true;
            break;
        }
        
        if (guess < 1 || guess > maxRange) {
            cout << "Please guess between 1 and " << maxRange << "!" << endl;
            continue;
        }
        
        displayHint(guess);
        displayGuessHistory();
        cout << "Attempts remaining: " << (maxAttempts - attempts) << "\n" << endl;
    }
    
    // Game result
    cout << "\n" << string(50, '=') << endl;
    if (won) {
        gamesWon++;
        int basePoints = 100;
        int difficultyBonus = (maxRange / 50) * 25;
        int efficiencyBonus = (maxAttempts - attempts + 1) * 20;
        int points = basePoints + difficultyBonus + efficiencyBonus;
        totalScore += points;
        
        cout << "🎉 CONGRATULATIONS! 🎉" << endl;
        cout << "You guessed " << secretNumber << " in " << attempts << " attempt(s)!" << endl;
        cout << "Base Points: " << basePoints << endl;
        cout << "Difficulty Bonus: +" << difficultyBonus << endl;
        cout << "Efficiency Bonus: +" << efficiencyBonus << endl;
        cout << "TOTAL POINTS: " << points << " 🏆" << endl;
    } else {
        cout << "💀 GAME OVER! 💀" << endl;
        cout << "The secret number was: " << secretNumber << endl;
        cout << "Your guesses: ";
        displayGuessHistory();
    }
    cout << string(50, '=') << endl;
}

void AdvancedGuessingGame::playReverseMode() {
    cout << "\n🔄 REVERSE MODE" << endl;
    cout << "You think of a number between 1 and " << maxRange << endl;
    cout << "I'll try to guess it! Give me hints with:" << endl;
    cout << "(h)igher, (l)ower, or (c)orrect" << endl;
    
    int min = 1;
    int max = maxRange;
    int computerGuess;
    char response;
    int computerAttempts = 0;
    const int maxComputerAttempts = 15;
    
    cout << "\nThink of a number and press Enter when ready...";
    cin.ignore();
    cin.get();
    
    while (computerAttempts < maxComputerAttempts) {
        computerAttempts++;
        computerGuess = (min + max) / 2;
        
        cout << "\nAttempt " << computerAttempts << ": Is it " << computerGuess << "?" << endl;
        cout << "(h)igher, (l)ower, or (c)orrect: ";
        cin >> response;
        
        if (response == 'c' || response == 'C') {
            cout << "\n🎯 I guessed your number " << computerGuess << " in " << computerAttempts << " attempts!" << endl;
            totalScore += (maxComputerAttempts - computerAttempts + 1) * 10;
            return;
        } else if (response == 'h' || response == 'H') {
            min = computerGuess + 1;
        } else if (response == 'l' || response == 'L') {
            max = computerGuess - 1;
        } else {
            cout << "Please enter h, l, or c!" << endl;
            computerAttempts--;
            continue;
        }
        
        if (min > max) {
            cout << "\n🤔 Hmm... I think you might have changed your number!" << endl;
            break;
        }
    }
    
    if (computerAttempts >= maxComputerAttempts) {
        cout << "\n🤖 I give up! You win!" << endl;
    }
}

void AdvancedGuessingGame::playMultiplayerMode() {
    cout << "\n👥 MULTIPLAYER MODE" << endl;
    cout << "Two players will take turns guessing!" << endl;
    
    generateSecretNumber();
    gamesPlayed++;
    
    int currentPlayer = 1;
    int guess;
    bool won = false;
    
    cout << "Secret number has been generated between 1 and " << maxRange << endl;
    cout << "Players take turns guessing. Good luck!\n" << endl;
    
    while (attempts < maxAttempts) {
        cout << "=== Player " << currentPlayer << "'s turn ===" << endl;
        cout << "Attempt " << (attempts + 1) << "/" << maxAttempts << endl;
        cout << "Enter your guess: ";
        
        while (!(cin >> guess)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number: ";
        }
        
        attempts++;
        saveGuess(guess);
        
        if (guess == secretNumber) {
            won = true;
            break;
        }
        
        if (guess < 1 || guess > maxRange) {
            cout << "Please guess between 1 and " << maxRange << "!" << endl;
            continue;
        }
        
        displayHint(guess);
        displayGuessHistory();
        cout << "Attempts remaining: " << (maxAttempts - attempts) << "\n" << endl;
        
        // Switch players
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }
    
    cout << "\n" << string(50, '=') << endl;
    if (won) {
        gamesWon++;
        cout << "🎉 PLAYER " << currentPlayer << " WINS! 🎉" << endl;
        cout << "The number was " << secretNumber << endl;
        cout << "Guessed in " << attempts << " attempts!" << endl;
        totalScore += 150;
    } else {
        cout << "💀 BOTH PLAYERS LOSE! 💀" << endl;
        cout << "The secret number was: " << secretNumber << endl;
    }
    cout << string(50, '=') << endl;
}

void AdvancedGuessingGame::displayStats() {
    double winRate = (gamesPlayed > 0) ? (static_cast<double>(gamesWon) / gamesPlayed) * 100 : 0;
    
    cout << "\n=== PLAYER STATISTICS ===" << endl;
    cout << "Games Played: " << gamesPlayed << endl;
    cout << "Games Won: " << gamesWon << endl;
    cout << "Win Rate: " << winRate << "%" << endl;
    cout << "Total Score: " << totalScore << " 🏆" << endl;
    cout << "========================" << endl;
}

void AdvancedGuessingGame::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

bool AdvancedGuessingGame::playAgain() {
    char choice;
    cout << "\nWould you like to play again? (y/n): ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return (choice == 'y' || choice == 'Y');
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    
    AdvancedGuessingGame game;
    
    cout << "🎮 ADVANCED NUMBER GUESSING GAME 🎮" << endl;
    
    do {
        game.clearScreen();
        game.displayMainMenu();
        game.setDifficulty();
        game.setGameMode();
        game.displayStats();
    } while (game.playAgain());
    
    cout << "\nThanks for playing! Final statistics:" << endl;
    game.displayStats();
    cout << "Goodbye! 👋" << endl;
    
    return 0;
}