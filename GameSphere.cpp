#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

// Function to get initials with input validation
void getInitials(char initials[3]);

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
    srand(time(0));

    vector<string> wordList = {
        "code", "game", "play", "java", "loop",
        "data", "node", "disk", "math", "byte"
    };

    char playAgain;
    int score = 0;

    do {

        cout << "=========================\n";
        cout << "   4-Letter Hangman\n";
        cout << "=========================\n";

        for (int round = 1; round <= 3; round++) {

            string word = wordList[rand() % wordList.size()];
            string guessed = "____";
            int attempts = 6;
            char guess;

            vector<char> guessedLetters; // stores all guessed letters

            cout << "\n=== Round " << round << " ===\n";

            while (attempts > 0 && guessed != word) {

                drawHangman(attempts);

                cout << "Word: " << guessed << endl;
                cout << "Attempts left: " << attempts << endl;

                // Display guessed letters
                cout << "Guessed letters: ";
                for (char c : guessedLetters) {
                    cout << c << " ";
                }
                cout << endl;

                cout << "Guess a letter: ";
                cin >> guess;

                // Check if letter was already guessed
                bool alreadyGuessed = false;
                for (char c : guessedLetters) {
                    if (c == guess) {
                        alreadyGuessed = true;
                        break;
                    }
                }

                if (alreadyGuessed) {
                    cout << "You already guessed that letter!\n";
                    continue; // skip rest of loop
                }

                // Add to guessed letters
                guessedLetters.push_back(guess);

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

            if (guessed == word) {
                cout << "You guessed it! The word was: " << word << endl;
                cout << "+5000 points!\n";
                addPoints(&score);
            }
            else {
                drawHangman(0);
                cout << "You lost! The word was: " << word << endl;
            }
        }

        cout << "\n=== Game Over ===\n";
        cout << "Final Score: " << score << endl;

        cout << "\nPlay again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "Thanks for playing!\n";

    return score;
}


int cardDraw(); // Using an int to get the drawn card
int playerAceCheck(int card); // This gives the option for users to determine if an ace is worth 1 or 11 points.
int dealerAceCheck(int card, int dealerTotal); // This gives the dealer the option to detmerine if an ace is worth 1 or 11 points.
int getValidatedInt(int min, int max); // This is an input validation loop to not accept junk data and inputs.
void showCard(int card); // This shows the card drawn.


//Blackjack function - made by Colin
int blackJack() {
    int score = 0;
    bool playAgain = true;
    cout << "=== BLACKJACK ===" << endl;

    while (playAgain && score < 99999) {
        cout << "\n=====================\n";
        cout << "      NEW ROUND      \n";
        cout << "=====================\n\n";

        int playerTotal = 0;
        int dealerTotal = 0;
        int card1, card2, dealerCard1;
        bool playOn = true;

        // Checks if the player or dealer drew aces and totals the scores.
        card1 = cardDraw();
        showCard(card1);
        card1 = playerAceCheck(card1);
        card2 = cardDraw();
        showCard(card2);
        card2 = playerAceCheck(card2);
        playerTotal = card1 + card2;
        dealerCard1 = cardDraw();
        dealerCard1 = dealerAceCheck(dealerCard1, dealerTotal);
        dealerTotal += dealerCard1;

        cout << "Dealer shows: " << dealerTotal << endl;
        cout << "Your hand total: " << playerTotal << endl;

        while (playOn) {
            if (playerTotal > 21) {
                cout << "Bust! You went over 21." << endl;
                break;
            }
            cout << "1 = Hit, 0 = Stand: ";
            int userChoice = getValidatedInt(0, 1);
            if (userChoice == 1) {
                int card = cardDraw();
                showCard(card);
                card = playerAceCheck(card);
                playerTotal += card;
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
                showCard(card);
                card = dealerAceCheck(card, dealerTotal);
                dealerTotal += card;
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

        // Limits the score to 99999
        if (score >= 99999) {
            score = 99999;
            cout << "YOU GOT A PERFECT SCORE!\n";
            playAgain = false;
        }
        else {
            cout << "\nScore so far: " << score << "\n";
            cout << "Play another round? 1 = Yes, 0 = No: ";
            int again = getValidatedInt(0, 1);
            cout << endl;
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

// This function lets players determine what an ace should be worth.
int playerAceCheck(int card) {
    if (card == 1) {
        cout << "ces are either worth 1 or 11 points. \nInput 1 for 1 point or 0 for 11 points: ";
        int aceChoice = getValidatedInt(0, 1);
        if (aceChoice == 0) {
            card = 11;
        }
        else {
            card = 1;
        }
    }
    return card;
}

// This function automatically decides what is best for the dealer with aces.
int dealerAceCheck(int card, int dealerTotal) {
    if (card == 1) {
        if (dealerTotal <= 10) {
            card = 11;
        }
        else {
            card = 1;
        }
    }

    return card;
}

// Input validation loop to not accept junk input
int getValidatedInt(int min, int max) {
    int value;
    while (!(cin >> value) || value < min || value > max) {
        cout << "Invalid input. Enter a number between "
            << min << " and " << max << ": ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    return value;
}

// This function shows the card drawn
void showCard(int card) {
    if (card == 1) {
        cout << "You drew an Ace!" << endl;
    }
    else {
        cout << "You drew a " << card << "!" << endl;
    }
}


//Game #3 Rock Paper Scissors - by ...
int rps() {

    int userChoice, computerChoice;
    int score = 0;


    cout << "=== Rock Paper Scissors ===\n";
    cout << "0 = Rock, 1 = Paper, 2 = Scissors\n";

    for (int i = 1; i <= 3; i++) {
        cout << "\nRound " << i << ": ";
        userChoice = getValidatedInt(0, 2);

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
            guess = getValidatedInt(0, 250);

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

//Search & Rescue

//Global scope variables
const int ROW = 4;
const int COL = 4;

//Function Prototypes
void boardSetup(char[ROW][COL]); //Sets up x-board where player guesses.
int findDiver(int, int, int[][COL]); //Checks if player guess is correct by comparing it to boolArray, which has diver location.

int searchRescue()
{
    //Sample Array
    int boolArray[ROW][COL] = { {0,0,0,0},
                              {0,1,0,0},
                              {0,0,0,0},
                              {0,0,0,0} };
    //
    char charArray[ROW][COL] = { ' ','1','2','3',
                               '1','~','~','~',
                               '2','~','~','~',
                               '3','~','~','~' };
    //Main Game intro
    cout << "Welcome to Search And Rescue!\n";
    cout << "The main goal of the game is to find a diver missing at sea.\n";
    cout << "However, you have limited 'energy' to find said diver, so be quick!";
    cout << endl << endl;
    //Main Board Setup
    /* Pseudocode
    While diver is NOT found AND turn number of user is less than ARRAY - 1
        Ask user for co-ordinates
        Check coordinates against boolArray
        if coordinates == 1(diver location)
            congratulate player!
        else
            Try again!
    End of while loop
    If diver is NOT found after turn used up
        Print out message, you lose.
    */

    bool diverFound = false;
    int userTurn = 0;
    int totalTurns = 3;
    int xCoord, yCoord;
    int score = 5000;

    cout << "Please type in the coordinates you think the diver is at.\n";
    while (!diverFound && (userTurn < totalTurns))
    {
        boardSetup(charArray);//prints out board, and updates it as necessary
        cout << "Enter the x coordinate (1-3): ";
        xCoord = getValidatedInt(1, 3);
        cout << "Enter the y coordinate (1-3): ";
        yCoord = getValidatedInt(1, 3);
        int userFoundDiver = findDiver(xCoord, yCoord, boolArray);//Function that checks if user input is correct
        if (userFoundDiver == 1)
        {
            cout << "Congrats, you found the diver!\n";
            charArray[yCoord][xCoord] = 'o';//Replaces '~' with 'o', marking a where diver is.
            boardSetup(charArray);//prints out board, and updates it as necessary
            diverFound = true;
        }
        else //runs if (findDiver == false/0)
        {
            cout << "Sorry, but diver was not found. Try again" << endl;
            charArray[yCoord][xCoord] = 'x';//Replaces '~' with 'x', marking a missed spot diver is not at.
            userTurn++;
            score -= 500;
        }
    }
    if (userTurn == totalTurns)
    {
        cout << "You have used up all your energy. The diver is lost forever. \nGame Over";
    }


    addPoints(&score);
    return score;
}

int findDiver(int x, int y, int boolArray[ROW][COL])
{
    if (boolArray[y][x] == 1)//Diver value initiated to 1.
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void boardSetup(char mainArray[ROW][COL]) //Will print out x-board array.
{
    int x, y;
    for (y = 0; y < COL; y++)
    {
        for (x = 0; x < ROW; x++)
        {
            cout << setw(4) << mainArray[y][x] << " ";
        }
        cout << endl;
    }
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
    cout << "Welcome to the Game Sphere\nPress Enter to continue" << endl;
    cin.get();
    cout << "Would You like to Upload Scores?" << endl;
    cout << "1.) Upload \n2.) Skip" << endl;
    menuSelect = getValidatedInt(1, 2); // Input validation for menu selection
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
    menuSelect = 0;
    while (menuSelect != 7) {
        cout << "\nPlease Select a Game to play" << endl;
        cout << "1) Hangman \n2) BlackJack \n3) Rock Paper Scissors \n4) Number Guesser \n5) Search and Rescue \n6) High Scores \n7) Quit\n" << endl;
        menuSelect = getValidatedInt(1, 7);;
        if (menuSelect <= 0 || menuSelect > 7) {
            cout << "You must select a menu number between 1 and 7" << endl;
            //High Scores

        }
        else if (menuSelect == 6) {
            do {
                cout << "Which game high scores do you want to look at?" << endl;
                cout << "1) Hangman \n2) Blackjack \n3) Rock Paper Scissors \n4) Number Guesser \n5) Search and Rescue \n6) Return To Menu" << endl;
                menuSelect = getValidatedInt(1, 6);
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
                getInitials(nameTemp);

                scoreSort(scoreData, gameName, nameTemp, scoreTemp, menuSelect);
                scoreTemp = 0;
                break;
            case 2:
                //BLACKJACK LAUNCH
                scoreTemp = blackJack();
                cout << "Please input your initials!" << endl; //Initials input (Make sure to validate)
                getInitials(nameTemp);

                scoreSort(scoreData, gameName, nameTemp, scoreTemp, menuSelect);
                scoreTemp = 0;
                break;
            case 3:
                scoreTemp = rps();
                cout << "Please input your initials!" << endl; //Initials input (Make sure to validate)
                getInitials(nameTemp);

                scoreSort(scoreData, gameName, nameTemp, scoreTemp, menuSelect);
                scoreTemp = 0;
                break;
            case 4:
                scoreTemp = numGuess();
                cout << "Please input your initials!" << endl; //Initials input (Make sure to validate)
                getInitials(nameTemp);

                scoreSort(scoreData, gameName, nameTemp, scoreTemp, menuSelect);
                scoreTemp = 0;
                break;
            case 5:
                scoreTemp = searchRescue();
                cout << "Please input your initials!" << endl; //Initials input (Make sure to validate)
                getInitials(nameTemp);

                scoreSort(scoreData, gameName, nameTemp, scoreTemp, menuSelect);
                scoreTemp = 0;
                break;
            }
        }
    }
    cout << "Would you like to save your scores?\n1.Yes\n2.No" << endl;
	menuSelect = getValidatedInt(1, 2); // Input validation for menu selection
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

// Input validation for initials
void getInitials(char initials[3]) {
    string input;

    while (true) {
        cout << "Enter your 3 initials: ";
        cin >> input;

        if (input.length() == 3) {
            initials[0] = input[0];
            initials[1] = input[1];
            initials[2] = input[2];
            return;
        }

        cout << "Please enter exactly 3 characters.\n";
    }
}