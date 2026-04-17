#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;
//Game #1 Hangman By Sam
// Draw hangman
void drawHangman(int attempts) {
    switch (attempts) {
    case 6: cout << "\n\n\n\n\n"; break;
    case 5: cout << "  O\n\n\n\n\n"; break;
    case 4: cout << "  O\n  |\n\n\n\n"; break;
    case 3: cout << "  O\n /|\n\n\n\n"; break;
    case 2: cout << "  O\n /|\\\n\n\n\n"; break;
    case 1: cout << "  O\n /|\\\n / \n\n\n"; break;
    case 0: cout << "  O\n /|\\\n / \\\n\n\n"; break;
    }
}

// Pointer function to add points
void addPoints(int* score) {
    *score += 5000;
}

int hangman() {

    // Word list using vector
    vector<string> wordList = {
        "code", "game", "play", "java", "loop",
        "data", "node", "disk", "math", "byte"
    };

    char playAgain;
    int score;
    do {
        score = 0; // reset score each game

        // Title
        cout << "=========================\n";
        cout << "   4-Letter Hangman\n";
        cout << "=========================\n";

        // 3 rounds per game
        for (int round = 1; round <= 3; round++) {

            string word = wordList[rand() % wordList.size()];
            string guessed = "____";
            int attempts = 6;
            char guess;

            cout << "\n=== Round " << round << " ===\n";

            while (attempts > 0 && guessed != word) {

                drawHangman(attempts);

                cout << "Word: " << guessed << endl;
                cout << "Attempts left: " << attempts << endl;
                cout << "Guess a letter: ";
                cin >> guess;

                bool correct = false;

                for (int i = 0; i < 4; i++) {
                    if (word[i] == guess && guessed[i] == '_') {
                        guessed[i] = guess;
                        correct = true;
                    }
                }

                if (!correct) {
                    attempts--;
                    cout << "Wrong!\n";
                }
                else {
                    cout << "Correct!\n";
                }
            }

            // Round result
            if (guessed == word) {
                cout << "You guessed it! The word was: " << word << endl;
                cout << "+5000 points!\n";
                addPoints(&score); // pointer used here
            }
            else {
                drawHangman(0);
                cout << "You lost! The word was: " << word << endl;
            }
        }

        // End of game
        cout << "\n=== Game Over ===\n";
        cout << "Final Score: " << score << endl;

        // Play again prompt
        cout << "\nPlay again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "Thanks for playing!\n";

    return score;
}

//Game #2 Blackjack - by Colin

using namespace std;

// Feel free to change the names etc. Any advice is appreciated

int blackJack(); // Using an int to return the score.
int cardDraw(); // Using an int to get the drawn card

//Blackjack function - made by Colin
int blackJack() {
    int score = 0;
    bool playAgain = true;
    cout << "=== BLACKJACK ===" << endl;

    while (playAgain && score < 99999) {  // Stop loop if perfect score reached. Added play Again to add a user inputted stop
        int playerTotal = 0;
        int dealerTotal = 0;
        bool playOn = true;

        playerTotal = playerTotal + cardDraw();
        playerTotal = playerTotal + cardDraw();
        dealerTotal = dealerTotal + cardDraw();

        cout << "Dealer shows: " << dealerTotal << endl;
        cout << "Your hand total: " << playerTotal << endl;

        while (playOn) {
            if (playerTotal > 21) {
                cout << "Bust! You went over 21." << endl;
                break;
            }
            cout << "1 = Hit, 0 = Stand: ";
            int userChoice;
            cin >> userChoice;
            if (userChoice == 1) {
                int card = cardDraw();
                playerTotal = playerTotal + card;
                cout << "\nYou drew: " << card << " | Your total: " << playerTotal << endl;
            }
            else {
                playOn = false;
            }
        }

        if (playerTotal <= 21) {
            cout << "Dealer's turn..." << endl;
            while (dealerTotal < 17) {
                int card = cardDraw();
                dealerTotal = dealerTotal + card;
                cout << "Dealer drew: " << card << " | Dealer total: " << dealerTotal << endl;
            }
            cout << "\n--- RESULT ---" << endl;
            cout << "Your total: " << playerTotal << endl;
            cout << "Dealer total: " << dealerTotal << endl;

            if (dealerTotal > 21) {
                cout << "Dealer busts! You win!" << endl;
                score = score + 5000;
            }
            else if (playerTotal > dealerTotal) {
                cout << "You win!" << endl;
                score = score + 5000;
            }
            else if (playerTotal == dealerTotal) {
                cout << "Push! It's a tie." << endl;
                score = score + 1000;
            }
            else {
                cout << "Dealer wins." << endl;
            }
        }

        if (playerTotal == 21) {
            cout << "Blackjack bonus!" << endl;
            score = score + 10000;
        }

        // Limits the score to 99999 as Jared requested
        if (score >= 99999) {
            score = 99999;
            cout << "YOU GOT A PERFECT SCORE!\n";
            playAgain = false;
        }
        else {
            cout << "\nScore so far: " << score << "\n";
            cout << "Play another round? 1 = Yes, 0 = No: ";
            int again;
            cin >> again;
            if (again != 1) playAgain = false;
        }
    }
    cout << "Final score: " << score << endl;
    return score;
}

int cardDraw() {
    int card = rand() % 10 + 1; // Facecards are 10 in Blackjack so I thought I could save some lines of code here
    return card;
}
//Game #3 Rock Paper Scissors - by ...
int rps() {

    int userChoice, computerChoice;
    int score = 0;


    cout << "=== Rock Paper Scissors ===\n";
    cout << "0 = Rock, 1 = Paper, 2 = Scissors\n";

    for (int i = 1; i <= 3; i++) {
        cout << "\nRound " << i << ": ";
        cin >> userChoice;

        computerChoice = rand() % 3;

        cout << "Computer chose: " << computerChoice << endl;

        if (userChoice == computerChoice) {
            cout << "Tie!\n";
        }
        else if ((userChoice == 0 && computerChoice == 2) ||
            (userChoice == 1 && computerChoice == 0) ||
            (userChoice == 2 && computerChoice == 1)) {
            cout << "You win this round!\n";
            score += 10;
        }
        else {
            cout << "You lose this round!\n";
        }
    }

    return score;
}
//Game #4 NumberGuesser - by ...
int numGuess() {
    int ranNumb, guess;
    int points = 0;
    int wins = 0;
    char contPlay;

    do {
        ranNumb = rand() % 251;
        cout << "Guess the number I am thinking of (0-250): ";

        while (true) {
            cin >> guess;

            if (guess < 0 || guess > 250) {
                cout << "Error, please make sure number is between 0 and 250: ";
                continue;
            }

            if (guess < ranNumb) {
                if (ranNumb - guess <= 10 && ranNumb - guess > 5) {
                    cout << "Close, aim a little higher." << endl;
                }
                else {
                    cout << "Guess is too low." << endl;
                }
            }
            else if (guess > ranNumb) {
                if (guess - ranNumb <= 10 && guess - ranNumb > 5) {
                    cout << "Close, aim a little lower." << endl;
                }
                else {
                    cout << "Guess is too high." << endl;
                }
            }
            else {
                cout << "Awesome, you got the right number. +5 points!" << endl;
                points += 5;
                wins++;
                break;
            }
            cout << "Nope! Try again: ";
        }

        cout << "Current points: " << points << endl;

        cout << "Would you like to play again? (y/n): ";
        cin >> contPlay;

    } while (contPlay == 'y' || contPlay == 'Y');

    cout << "You finished with  " << points << " total points!" << endl;
    cout << "You finished " << wins << " total win(s)!" << endl;
    cout << "Play again soon!" << endl;

    return points;
}
void swapper(int& x, int& y) {
    int temp;
    temp = x;
    x = y;
    y = temp;
}
void charSwapper(char& x, char& y) {
    char temp;
    temp = x;
    x = y;
    y = temp;
}
//Score Sorting - By Jared
void scoreSort(int scoreData[10][5], char gameName[4][10][5], char nameTemp[4], int scoreTemp, int menuSelect) {
    int g = menuSelect - 1;
    if (scoreTemp > scoreData[9][g]) {
        scoreData[9][g] = scoreTemp;
        gameName[0][9][g] = nameTemp[0];
        gameName[1][9][g] = nameTemp[1];
        gameName[2][9][g] = nameTemp[2];
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 9 - i; j++) {
                if (scoreData[j][g] < scoreData[j + 1][g]) {
                    swapper(scoreData[j][g], scoreData[j + 1][g]);
                    charSwapper(gameName[0][j][g], gameName[0][j + 1][g]);
                    charSwapper(gameName[1][j][g], gameName[1][j + 1][g]);
                    charSwapper(gameName[2][j][g], gameName[2][j + 1][g]);
                }
            }
        }
    }
    else {
        cout << "You didnt make the scoreboard!" << endl;
    }
}
//Main - By Jared
int main() {
    srand(time(NULL));
    int scoreData[10][5] = {};
    int scoreTemp;
    char gameName[4][10][5] = { '-' };
    char nameTemp[4];
    int menuSelect = 0;
    cout << "Welcome to the Game Sphere\nPress any button to continue" << endl;
    cin.get();
    cout << "Would You like to Upload Scores?" << endl;
    cout << "1.) Upload \n2.) Skip" << endl;
    cin >> menuSelect;
    if (menuSelect == 1) {
        ifstream inFile("scores.txt");
        if (inFile.is_open()) {
            // This nested loop matches your 10x5 score table
            for (int g = 0; g < 5; g++) {
                for (int i = 0; i < 10; i++) {
                    // Read: Score, then Initial 1, 2, and 3
                    inFile >> scoreData[i][g];
                    inFile >> gameName[0][i][g] >> gameName[1][i][g] >> gameName[2][i][g];
                }
            }
            inFile.close();
            cout << "Scores uploaded successfully!" << endl;
        }
        else {
            cout << "No save file found, starting fresh." << endl;
        }
    }
    else if (menuSelect == 2) {
        cout << "\n" << endl;
    }
    else {
        cout << "Something went wrong Please restart the game" << endl;
        return 0;
    }
    menuSelect = 0;
    while (menuSelect != 7) {
        cout << "\nPlease Select a Game to play" << endl;
        cout << "1) Hangman \n2) BlackJack \n3) Rock Paper Scissors \n4) Number Guesser \n5)Search and Rescue \n6)High Scores \n7)Quit\n" << endl;
        cin >> menuSelect;
        if (menuSelect <= 0 || menuSelect > 7) {
            cout << "You must select a menu number between 1 and 7" << endl;
            //High Scores

        }
        else if (menuSelect == 6) {
            do {
                cout << "Which game high scores do you want to look at?" << endl;
                cout << "1)Hangman\n2)Blackjack\n3)Rock Paper Scissors\n4)Number Guesser \n5)Search and Rescue\n6)Return To Menu" << endl;
                cin >> menuSelect;
                if (menuSelect <= 0 || menuSelect >= 7) {
                    cout << "Please select a number between 1 and 6" << endl;
                }
                else {
                    cout << "High Scores\n---------------------------\n" << endl;
                    for (int i = 0; i < 10; i++) {
                        cout << "#" << i + 1 << ":  " << gameName[0][i][menuSelect - 1] << gameName[1][i][menuSelect - 1] << gameName[2][i][menuSelect - 1] << "---------------" << scoreData[i][menuSelect - 1] << endl;
                    }
                }

            } while (menuSelect != 6);

            //high scores
        }
        else if (menuSelect == 7) {
            break;
        }
        else {
            switch (menuSelect) { //YOUR GAMES WILL BE SELECTED FROM THIS MENU!
            case 1:
                //HANGMAN LAUNCH
                scoreTemp = hangman();
                cout << "Please input your initials!" << endl; //Initials input (Make sure to validate)
                cin >> nameTemp[0] >> nameTemp[1] >> nameTemp[2];

                scoreSort(scoreData, gameName, nameTemp, scoreTemp, menuSelect);
                scoreTemp = 0;
                break;
            case 2:
                //BLACKJACK LAUNCH
                scoreTemp = blackJack();
                cout << "Please input your initials!" << endl; //Initials input (Make sure to validate)
                cin >> nameTemp[0] >> nameTemp[1] >> nameTemp[2];

                scoreSort(scoreData, gameName, nameTemp, scoreTemp, menuSelect);
                scoreTemp = 0;
                break;
            case 3:
                scoreTemp = rps();
                cout << "Please input your initials!" << endl; //Initials input (Make sure to validate)
                cin >> nameTemp[0] >> nameTemp[1] >> nameTemp[2];

                scoreSort(scoreData, gameName, nameTemp, scoreTemp, menuSelect);
                scoreTemp = 0;
                break;
            case 4:
                scoreTemp = numGuess();
                cout << "Please input your initials!" << endl; //Initials input (Make sure to validate)
                cin >> nameTemp[0] >> nameTemp[1] >> nameTemp[2];

                scoreSort(scoreData, gameName, nameTemp, scoreTemp, menuSelect);
                scoreTemp = 0;
                break;
            case 5:
                scoreTemp = 10000 + rand() % 90000;
                cout << "Please input your initials!" << endl; //Initials input (Make sure to validate)
                cin >> nameTemp[0] >> nameTemp[1] >> nameTemp[2];

                scoreSort(scoreData, gameName, nameTemp, scoreTemp, menuSelect);
                scoreTemp = 0;
                break;
            }
        }
    }
    cout << "Would you like to save your scores?\n1.Yes\n2.No" << endl;
    cin >> menuSelect;
    if (menuSelect == 1) {
        ofstream outFile("scores.txt");
        if (outFile.is_open()) {
            for (int g = 0; g < 5; g++) {
                for (int i = 0; i < 10; i++) {
                    // We save them in the exact same format we read them
                    outFile << scoreData[i][g] << " "
                        << gameName[0][i][g] << " "
                        << gameName[1][i][g] << " "
                        << gameName[2][i][g] << "\n";
                }
            }
            outFile.close();
            cout << "Scores saved!" << endl;
        }
        else {
            cout << "Error: Could not save scores." << endl;
        }
    }
    cout << "Thanks for playing!" << endl;
}
