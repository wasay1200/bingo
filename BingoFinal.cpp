#include <iostream>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <ctime>
#include <iomanip>
#include <conio.h>
#include <dos.h>           
#include <stdio.h>
#include <time.h>
#include <windows.h>
//#include <mmsystem.h>
#include<string>
#include<fstream>

#pragma comment(lib,"winmm.lib")
using namespace std;
int cont;
string GameInstructions, HighScores;
ifstream ReadGameInstructions("HowToPlay.txt");
ifstream ReadHighScore("HighScore.txt");
string HighName[100] = { " " };
int HighScore[100] = { 0 };
int dimension, pts1 = 0, pts2 = 0, gameNID, tossTemp, win;
string won;
void displayHighScore() {
    ifstream ReadHighScore("HighScore.txt");
    cout << " This is the High Score LeaderBoard!" << endl;
    if (!ReadHighScore.is_open()) {
        cout << "Invalid File name or the file is not opened!";
    }
    else {
        // Check for file read error
        if (ReadHighScore.fail()) {
            cout << "Error reading file or File is Empty!";
        }
        else {
            cout << "\n   Name\tScore" << endl;
            cout << "______________________________\n";
            // Read line by line until end of file
            while (getline(ReadHighScore, HighScores)) {
                cout << HighScores << endl;
            }
        }
    }
    ReadHighScore.close();
}

void contGame(int& ID, string& player1, string& player2, int& tossTemp, int& dimensions, int card1[][25], int card2[][25]) {
    ofstream writeContinue("ResumeGame.txt");
    if (!writeContinue.is_open()) {
        cout << "Unable to open file for writing." << endl;
        return;
    }

    writeContinue << ID << endl;
    writeContinue << dimensions << endl;
    writeContinue << player1 << "," << player2 << endl;
    writeContinue << tossTemp << endl;

    for (int x = 0; x < dimensions; x++) {
        for (int y = 0; y < dimensions; y++) {
            writeContinue << card1[x][y] << ",";
        }
        writeContinue << endl;
    }

    for (int x = 0; x < dimensions; x++) {
        for (int y = 0; y < dimensions; y++) {
            writeContinue << card2[x][y] << ",";

        }
        writeContinue << endl;
    }

    writeContinue.close();
}

void saveGameHistory(int gameID, string won, string p1, string p2, int pts1, int pts2) {
    ofstream outputFile("GameHistory.txt", ios::app);
    if (outputFile.is_open()) {
        cout << endl;
        outputFile << "----------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        outputFile << "GameID: " << gameID << endl;
        outputFile << "Player1: " << p1 << endl;
        outputFile << "Player2: " << p2 << endl;
        outputFile << "Player1 Points: " << pts1 << endl;
        outputFile << "Player2 Points: " << pts2 << endl;
        outputFile << "Winner: " << won << endl;
        outputFile << "----------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        outputFile.close();
        cout << "Game History has been saved successfully." << endl;
    }
    else
        cout << "unable to open the file." << endl;
}
void displayGameHistory(const string& outputFile) {
    ifstream inputFile("GameHistory.txt");
    if (inputFile.is_open()) {
        string gameID, player1Name, player2Name, player1Score, player2Score, winner;
        while (inputFile >> gameID) {
            getline(inputFile, player1Name, ',');
            getline(inputFile, player2Name, ',');
            inputFile >> player1Score >> player2Score >> winner;
            cout << gameID << endl << player1Name << endl << player2Name
                << endl << player1Score << endl << player2Score << endl << winner << endl;
        }
        inputFile.close();
    }
    else {
        cout << "Unable to open the file." << endl;
    }
}
void ScoreFile(string name, int HighScore[], string HighName[]) {
    // Initialize variables
    bool found = false;
    int index = -1;

    // Search for the name in existing HighName array
    for (int i = 0; i < 10; ++i) {
        if (HighName[i] == name) {
            found = true;
            index = i;
            break;
        }
        else if (HighName[i] == " " && index == -1) {
            // Save the first empty slot
            index = i;
        }
    }

    // Update score or add new entry
    if (found) {
        HighScore[index]++;
    }
    else {
        HighName[index] = name;
        HighScore[index]++;
    }

    // Sort arrays based on scores
    for (int x = 0; x < 10; ++x) {
        for (int y = x + 1; y < 10; ++y) {
            if (HighScore[x] < HighScore[y]) {
                // Swap elements
                swap(HighScore[x], HighScore[y]);
                swap(HighName[x], HighName[y]);
            }
        }
    }

    // Write sorted data to HighScore.txt

    ofstream WriteHighScore("HighScore.txt");
    for (int i = 0; i < 10; ++i) {
        if (HighName[i] != " ") {
            WriteHighScore << "\t" << i + 1 << ". " << HighName[i] << "\t" << HighScore[i] << "\n";
        }
        else {
            break;
        }
    }
    WriteHighScore.close();
}


int checkRow(int Card1[][25]) //checking if all numbers in a row are zero
{
    int count = 0;
    for (int i = 0; i < dimension; i++)
    {
        bool isZero = true;
        for (int j = 0; j < dimension; j++)
        {
            if (Card1[i][j] != 0)
            {
                isZero = false;
                break;
            }
        }
        if (isZero)
        {
            count++;
        }
    }
    return count;
}
int checkColumn(int Card1[][25]) //checking if all numbers in a column are zero
{
    int count = 0;
    for (int j = 0; j < dimension; j++)
    {
        bool isZero = true;
        for (int i = 0; i < dimension; i++)
        {
            if (Card1[i][j] != 0)
            {
                isZero = false;
                break;
            }
        }
        if (isZero)
        {
            count++;
        }
    }
    return count;
}
int checkDiagonal(int Card1[][25]) //checking if all numbers in a diagonal are zero
{
    int count = 0;
    bool isZero1 = true;
    for (int i = 0; i < dimension; i++)
    {
        if (Card1[i][i] != 0)
        {
            isZero1 = false;
            break;
        }
    }
    if (isZero1)
    {
        count++;
    }
    bool isZero2 = true;
    for (int i = 0; i < dimension; i++)
    {
        if (Card1[i][dimension - 1 - i] != 0)
        {
            isZero2 = false;
            break;
        }
    }
    if (isZero2)
    {
        count++;
    }

    return count;
}
void player1Score(int card1[][25]) { // keeping track of player1 current score 
    pts1 = checkDiagonal(card1) + checkColumn(card1) + checkRow(card1);
    cout << "Player 1 current points: " << pts1;
}
void player2Score(int card2[][25]) { // keeping track of player2 current score 
    pts2 = checkDiagonal(card2) + checkColumn(card2) + checkRow(card2);
    cout << "Player 2 current points: " << pts2;
}
int player1Win(int card1[][25]) // checking if player 1 completed all winning conditions
{
    int total = 0;
    total = total + checkRow(card1) + checkColumn(card1) + checkDiagonal(card1);
    return total;
}
int player2Win(int card2[][25]) // checking if player 2 completed all winning conditions
{
    int total = 0;
    total = total + checkRow(card2) + checkColumn(card2) + checkDiagonal(card2);
    return total;
}
void displayCard1(int card[][25], string p1) // displays card of player1
{
    system("Color 0D");
    cout << p1 << "'s Card:" << endl;
    int leftMargin = (80 - 6 * dimension) / 2;
    for (int i = 0; i < dimension; ++i)
    {
        cout << setw(leftMargin) << "";
        for (int j = 0; j < dimension; ++j)
        {
            cout << "+-----";
        }
        cout << "+" << endl;
        cout << setw(leftMargin) << "";
        for (int j = 0; j < dimension; j++)
        {
            cout << "| " << setw(3) << card[i][j] << " ";
        }
        cout << "|" << endl;
    }

    cout << setw(leftMargin) << "";

    for (int j = 0; j < dimension; ++j)
    {
        cout << "+-----";
    }
    cout << "+" << endl;
}
bool isDrawnPresentInCard(int card[][25], int value) // checks if number drawn by user is present in card
{
    for (int x = 0; x < dimension; x++)
    {
        for (int y = 0; y < dimension; y++)
        {
            if (card[x][y] == value)
            {
                return true;
            }
        }
    }
    return false;
}
bool toss() // Randomly chooses the first turn of player 1 or player 2 
{
    return ((rand() % (10) + 1) % 2);
}
int playerTurn() // keeps track of player who ended up getting first turn 
{
    int prevPlayer = toss();
    return prevPlayer;
}

void displayCard2(int card[][25], string p2) // displays card of player2
{
    system("Color 0B");
    cout << p2 << "'s Card:" << endl;
    int leftMargin = (80 - 6 * dimension) / 2;

    for (int i = 0; i < dimension; ++i)
    {

        cout << setw(leftMargin) << "";

        for (int j = 0; j < dimension; ++j)
        {
            cout << "+-----";
        }
        cout << "+" << endl;

        cout << setw(leftMargin) << "";

        for (int j = 0; j < dimension; j++)
        {
            cout << "| " << setw(3) << card[i][j] << " ";
        }
        cout << "|" << endl;
    }

    cout << setw(leftMargin) << "";
    for (int j = 0; j < dimension; ++j)
    {
        cout << "+-----";
    }
    cout << "+" << endl;
}

void player2Bingo(int card1[][25], int card2[][25], string p2, string p1) // Allows player 2 to play the game in their turn
{
    int card;
    tossTemp = 1;
    system("CLS");
    cout << "Game ID: " << gameNID << endl;
    cout << p2 << "'s Turn" << endl;
    displayCard2(card2, p2);
    player2Score(card2);
    cout << endl;
    cout << "Draw a card: " << endl;
    cout << "Enter -99 to exit to main menu" << endl;
    do
    {
        try
        {
            cin >> card;
            if (card == -99) {
                contGame(gameNID, p1, p2, tossTemp, dimension, card1, card2);
                exit(0);
            }
            if (cin.fail() || card < 1 || card > dimension * dimension || !isDrawnPresentInCard(card2, card))
            {
                throw "Invalid input. Please enter a valid number";
            }
        }
        catch (const char* message)
        {
            cout << message << endl;
            cin.clear();
            while (cin.get() != '\n')
            {
                continue;
            }

            continue;
        }
    } while (cin.fail() || card < 1 || card > dimension * dimension || !isDrawnPresentInCard(card2, card));

    for (int x = 0; x < dimension; x++)
    {
        for (int y = 0; y < dimension; y++)
        {
            if (card2[x][y] == card)
            {
                card2[x][y] = 0;
            }
        }
    }
    for (int x = 0; x < dimension; x++)
    {
        for (int y = 0; y < dimension; y++)
        {
            if (card1[x][y] == card)
            {
                card1[x][y] = 0;
            }
        }
    }
}

void player1Bingo(int card1[][25], int card2[][25], string p1, string p2)  // Allows player 1 to play the game in their turn
{
    int card;
    tossTemp = 0;
    cout << endl;
    system("CLS");
    cout << "Game ID: " << gameNID << endl;
    cout << p1 << "'s Turn" << endl;
    displayCard1(card1, p1);
    player1Score(card1);
    cout << endl;
    cout << "Draw a card: " << endl;
    cout << "Enter -99 to exit to main menu" << endl;
    do
    {
        try
        {
            cin >> card;
            if (card == -99) {
                contGame(gameNID, p1, p2, tossTemp, dimension, card1, card2);
                exit(0);
            }
            if (cin.fail() || card < 1 || card > dimension * dimension || !isDrawnPresentInCard(card1, card))
            {
                throw "Invalid input. Please enter a valid number";
            }
        }
        catch (const char* message)
        {
            cout << message << endl;
            cin.clear();
            while (cin.get() != '\n')
            {
                continue;
            }
            continue;
        }
    } while (cin.fail() || card < 1 || card > dimension * dimension || !isDrawnPresentInCard(card1, card));

    for (int x = 0; x < dimension; x++)
    {
        for (int y = 0; y < dimension; y++)
        {
            if (card2[x][y] == card)
            {
                card2[x][y] = 0;
            }
        }
    }
    for (int x = 0; x < dimension; x++)
    {
        for (int y = 0; y < dimension; y++)
        {
            if (card1[x][y] == card)
            {
                card1[x][y] = 0;
            }
        }
    }
}
int gameID() // Generates a random gameID
{
    srand(time(NULL));
    int gameID = rand() % 9000 + 1000;
    return gameID;
}
bool isValueInCard(int arr[][25], int value) // checks if value is already present in card or not 
{
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            if (arr[i][j] == value)
            {
                return true;
            }
        }
    }
    return false;
}
void randCard(int card1[][25], int card2[][25]) //Generates random unique values for card1 and card2
{
    for (int x = 0; x < dimension; x++)
    {
        for (int j = 0; j < dimension; j++)
        {
            int rvalue;
            rvalue = rand() % (dimension * dimension) + 1;
            while ((isValueInCard(card1, rvalue) == true))
            {
                rvalue = rand() % (dimension * dimension) + 1;
            }
            card1[x][j] = rvalue;
        }
    }

    for (int x = 0; x < dimension; x++)
    {
        for (int j = 0; j < dimension; j++)
        {
            int rvalue;
            rvalue = rand() % (dimension * dimension) + 1;
            while ((isValueInCard(card2, rvalue) == true) || rvalue == card1[x][j])
            {
                rvalue = rand() % (dimension * dimension) + 1;
            }
            card2[x][j] = rvalue;
        }
    }
}
string namePlayer1() // Allows player 1 to enter their name 
{
    string p1;
    cout << "Player 1,Enter your name: ";
    cin.ignore();
    getline(cin, p1);
    return p1;
}

string namePlayer2() // Allows player 2 to enter their name 
{
    string p2;
    cout << "Player 2,Enter your name: ";
    getline(cin, p2);
    return p2;
}
void resumeGame(int& ID, string& Player1, string& player2, int& toss, int& dimension, int card1[][25], int card2[][25]) {
    string val, temp, str;
    string player1Name, player2Name;
    fstream readContinue("ResumeGame.txt", ios::in);
    if (!readContinue.is_open()) {
        cout << "Unable to open file for reading." << endl;
    }
    else {
        readContinue >> temp;
        readContinue.ignore();
        ID = stoi(temp);
        readContinue >> temp;
        readContinue.ignore();
        dimension = stoi(temp);
        cout << ID << endl << dimension << endl;
        getline(readContinue, player1Name, ',');
        getline(readContinue, player2Name);
        //cin.get();
        cout << "Player 1: " << player1Name << endl;
        cout << "Player 2: " << player2Name << endl;
        readContinue >> temp;
        readContinue.ignore();
        toss = stoi(temp);
        cout << "Toss: " << toss << endl;
        //// Read card data
        cout << "Card 1 values:" << endl;
        for (int x = 0; x < dimension; ++x) {
            for (int y = 0; y < dimension; ++y) {
                getline(readContinue, val, ',');
                //readContinue >> card1[x][y];
                card1[x][y] = stoi(val);
                cout << card1[x][y] << " ";
            }
            cout << endl;
        }

        cout << "Card 2 values:" << endl;
        for (int x = 0; x < dimension; ++x) {
            for (int y = 0; y < dimension; ++y) {
                getline(readContinue, val, ',');
                //readContinue >> card1[x][y];
                card2[x][y] = stoi(val);
                cout << card2[x][y] << " ";
            }
            cout << endl;
        }

        // Close the file
        readContinue.close();
        system("pause");
    }
    if (toss == 1)
    {
        while (player2Win(card2) < 5 || player1Win(card1) < 5)
        {
            player2Bingo(card1, card2, player2Name, player1Name);

            if (player2Win(card2) >= 5)
            {
                win = 1;
                break;
            }
            player1Bingo(card1, card2, player1Name, player2Name);
            if (player1Win(card1) >= 5)
            {
                win = 0;
                break;
            }
        }
    }
    else
    {
        while (player2Win(card2) < 5 || player1Win(card1) < 5)
        {
            player1Bingo(card1, card2, player1Name,player2Name);
            if (player1Win(card1) >= 5)
            {
                win = 0;
                break;
            }
            player2Bingo(card1, card2,player2Name,player1Name);

            if (player2Win(card2) >= 5)
            {
                win = 1;
                break;
            }
        }
    }
    if (win == 1)
    {
        cout << player2Name << " WINS!" << endl;
        won = player2Name;
        ScoreFile(player2Name, HighScore, HighName);
        PlaySound(TEXT("Win.wav"), NULL, SND_FILENAME | SND_SYNC);
    }
    else if (win == 0)
    {
        cout << player1Name << " WINS!" << endl;
        won = player1Name;
        ScoreFile(player1Name, HighScore, HighName);
        PlaySound(TEXT("Win.wav"), NULL, SND_FILENAME | SND_SYNC);
    }
    cout << endl;
    // system("CLS");
    displayCard1(card1, player1Name);
    displayCard2(card2, player2Name);
    cout << endl;
    cout << "********   ***    *     * *******  ***** *           * ******   *****   \n";
    cout << "*      *  *   *   **   ** *       *     * *         *  *        *  *      \n";
    cout << "*         *   *   * * * * *       *     *  *       *   *        * *           \n";
    cout << "*    ***  * * *   *  *  * * ***** *     *   *     *    ******   **  \n";
    cout << "*      *  *   *   *     * *       *     *    *   *     *        * *      \n";
    cout << "*      *  *   *   *     * *       *     *     * *      *        *  *   \n";
    cout << "********  *   *   *     * *******  *****       *       *******  *   *  \n";
    saveGameHistory(gameNID, won, player1Name, player2Name, pts1, pts2);
    for (int x = 0; x <= 5; x++) {
        cout << " " << endl;
    }
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    PlaySound(TEXT("GameOver.wav"), NULL, SND_FILENAME | SND_SYNC);
}
void main_Menu() {  // displays main menu with various options
    string p1, p2, player1Name, player2Name, str, nameP;
    int choice, card1[25][25] = { 0 }, card2[25][25] = { 0 }, continueGame, prevToss, winner, score1 = 0, score2 = 0;
    char input, chr;
    system("Color 06");
    cout << "                                                           *****  *  *   *  *****  *****  \n";
    cout << "                                                           *   *  *  **  *  *      *   *   \n";
    cout << "                                                           ****   *  * * *  * ***  *   * \n";
    cout << "                                                           *   *  *  *  **  *   *  *   *  \n";
    cout << "                                                           *****  *  *   *  *****  *****      \n";
    cout << "WELCOME TO THE BINGO GAME!" << endl;
    cout << endl;
    cout << "Menu" << endl
        << "1. Play Game" << endl
        << "2. Game History" << endl
        << "3. View High Score" << endl
        << "4. How to Play" << endl
        << "5. Exit" << endl
        << endl;
    cout << "Enter your choice:" << endl;

    cin >> input;

    switch (input)
    {
    case '1':
        cout << "Enter -99 to continue , or 1 to play new game" << endl;
        cin >> continueGame;
        if (continueGame == -99) {
            resumeGame(gameNID, player1Name, player2Name, prevToss, dimension, card1, card2);
            main_Menu();
        }
        else if (continueGame == 1) {
            cout << endl;
            system("Color 06");
            player1Name = namePlayer1();
            cout << "Welcome " << player1Name << "!" << endl;
            PlaySound(TEXT("Power.wav"), NULL, SND_FILENAME | SND_SYNC);
            player2Name = namePlayer2();
            cout << "Welcome " << player2Name << "!" << endl;
            PlaySound(TEXT("Power.wav"), NULL, SND_FILENAME | SND_SYNC);

            cout << "Enter dimensions of card (5-25): ";
            do
            {
                try
                {
                    cin >> dimension;
                    // Check if the input is an integer and within the range [5, 25]
                    if (cin.fail() || dimension < 5 || dimension > 25)
                    {
                        throw "Invalid input. Please enter a valid number between 5 and 25.";
                    }
                }
                catch (const char* message)
                {
                    cout << message << endl;
                    cin.clear(); // Clear the input buffer after invalid input
                    while (cin.get() != '\n')
                    {
                        continue;
                    }
                    continue; // Restart the loop
                }
            } while (cin.fail() || dimension < 5 || dimension > 25);
            gameNID = gameID();
            randCard(card1, card2);
            cout << endl;
            displayCard1(card1, player1Name);
            cout << endl;
            displayCard2(card2, player2Name);
            prevToss = toss();
            if (prevToss == 0)
            {
                displayCard1(card1, player1Name);
                player1Bingo(card1, card2, player1Name, player2Name);
            }
            else
            {
                displayCard2(card2, player2Name);
                player2Bingo(card1, card2, player2Name, player1Name);
            }

            if (prevToss == 0)
            {
                while (player2Win(card2) < 5 || player1Win(card1) < 5)
                {
                    player2Bingo(card1, card2, player2Name, player1Name);

                    if (player2Win(card2) >= 5)
                    {
                        winner = 1;
                        break;
                    }

                    player1Bingo(card1, card2, player1Name, player2Name);
                    if (player1Win(card1) >= 5)
                    {
                        winner = 0;
                        break;
                    }
                }
            }
            else
            {
                while (player2Win(card2) < 5 || player1Win(card1) < 5)
                {

                    player1Bingo(card1, card2, player1Name, player2Name);
                    if (player1Win(card1) >= 5)
                    {
                        winner = 0;
                        break;
                    }

                    player2Bingo(card1, card2, player2Name, player1Name);

                    if (player2Win(card2) >= 5)
                    {
                        winner = 1;
                        break;
                    }
                }
            }
            if (winner == 1)
            {
                cout << player2Name << " WINS!" << endl;

                PlaySound(TEXT("Win.wav"), NULL, SND_FILENAME | SND_SYNC);
            }
            else if (winner == 0)
            {
                cout << player1Name << " WINS!" << endl;

                PlaySound(TEXT("Win.wav"), NULL, SND_FILENAME | SND_SYNC);
            }
            cout << endl;
            system("CLS");
            cout << "RESULT : " << endl;
            if (winner == 1)
            {
                cout << player2Name << " WINS!" << endl;
                won = player2Name;
                ScoreFile(player2Name, HighScore, HighName);
            }
            else if (winner == 0)
            {
                cout << player1Name << " WINS!" << endl;
                won = player1Name;
                ScoreFile(player1Name, HighScore, HighName);
            }
            displayCard1(card1, player1Name);
            displayCard2(card2, player2Name);
            cout << endl;
            cout << "********   ***    *     * *******  ***** *           * ******   *****   \n";
            cout << "*      *  *   *   **   ** *       *     * *         *  *        *  *      \n";
            cout << "*         *   *   * * * * *       *     *  *       *   *        * *           \n";
            cout << "*    ***  * * *   *  *  * * ***** *     *   *     *    ******   **  \n";
            cout << "*      *  *   *   *     * *       *     *    *   *     *        * *      \n";
            cout << "*      *  *   *   *     * *       *     *     * *      *        *  *   \n";
            cout << "********  *   *   *     * *******  *****       *       *******  *   *  \n";
            player1Score(card1);
            player2Score(card2);
            saveGameHistory(gameNID, won, player1Name, player2Name, pts1, pts2);
            for (int x = 0; x <= 5; x++) {
                cout << " " << endl;
            }
            cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
            PlaySound(TEXT("GameOver.wav"), NULL, SND_FILENAME | SND_SYNC);
            cout << "Press any button to move past the result screen" << endl;
            cin.get();
            getline(cin, str);
            system("CLS");
            main_Menu();
        }
        else {
            cout << "Invalid Input!";
            cout << "Press Enter to continue......\n";
            cin.get(chr);
            if (chr == '\n') {
                cin.ignore();
                system("CLS");
                main_Menu();
            }

        }
        break;
    case '2':
        system("CLS");
        displayGameHistory("GameHistory.txt");
        cout << "\nPress Enter key to continue....." << endl;
        cin.get(chr);
        do {
            if (chr == '\n') {
                cin.ignore();
                system("CLS");
                main_Menu();
            }
        } while (chr != '\n');
        main_Menu();
        break;
    case '3':
        system("CLS");
        system("Color 0B");
        displayHighScore();
        cout << "\nPress Enter key to continue....." << endl;
        cin.get(chr);
        do {
            if (chr == '\n') {
                cin.ignore();
                system("CLS");
                main_Menu();
            }

        } while (chr != '\n');

        break;
    case '4':
        system("CLS");
        system("Color 0B");
        if (!ReadGameInstructions.is_open()) {
            cout << "Invalid File name or the file is not opened!";
        }
        else {
            // Check for file read error
            if (ReadGameInstructions.fail()) {
                cout << "Error reading file!";
            }
            else {
                // Read line by line until end of file
                while (getline(ReadGameInstructions, GameInstructions)) {
                    cout << GameInstructions << endl;
                }
            }
        }
        ReadGameInstructions.close();
        cout << "\nPress Enter key to continue....." << endl;
        cin.get(chr);
        do {
            if (chr == '\n') {
                cin.ignore();
                system("CLS");
                main_Menu();
            }

        } while (chr != '\n');



        break;
    case '5':
        cout <<" *******  ****** ****** *****   ******  *       * ******** \n"
            << " *        *    * *    * *     * *    *   *     *  *        \n"
            << " *   ***  *    * *    * *     * *****     *   *   ******  \n"
            << " *     *  *    * *    * *     * *    *      *     *         \n"
            << " *******  ****** ****** *****   ******      *     ********  \n"
            ;
        exit(0);
    default:
        cout << "Invalid option. Please enter a valid choice." << endl;
        system("CLS");
        main_Menu();
    }
}
unsigned char B[15] = { 205,218,196,191,179,195,180,194,193,217,192,220,223,219 };

void gotoxy(int x, int y)
{
    static HANDLE h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h, c);
}

void wait(float seconds)
{
    clock_t endwait;
    endwait = clock() + seconds + CLOCKS_PER_SEC / 10;
    while (clock() < endwait) {}
}
void setColor(unsigned short color)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
}
void M(int n)
{
    for (int i = 1; i <= n; i++)
    {
        cout << B[2];
    }
}

int main() {
    setColor(9);
    gotoxy(16, 13); cout << B[1];  M(91); cout << B[3] << endl;
    gotoxy(16, 14); cout << B[4]; gotoxy(108, 14); cout << B[4];
    gotoxy(16, 15); cout << B[10]; M(91); cout << B[9];
    setColor(14);
    for (int i = 10; i <= 100; i++)
    {
        gotoxy(7 + i, 14); cout << B[13]; wait(0); gotoxy(109, 14); cout << ends << i << " %"; gotoxy(53, 16); cout << ". . . LOADING . . .";
        if (i == 100)
        {
            setColor(10);
            gotoxy(53, 16); cout << "  Press Enter to continue . . .";
            Beep(800, 125);
            Beep(800, 125);
        }
    }
    cin.get();
    system("CLS");
    PlaySound(TEXT("MarioOpen.wav"), NULL, SND_FILENAME | SND_SYNC);
    main_Menu();
    return 0;
}