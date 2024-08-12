//********************************** */
//                                   *
//         Connor Churcott           *
//                                   *
//                                   *
//         Order and Chaos           *
//                                   *
//                                   *
//********************************** */




#include <iostream>
#include <vector> 
#include <string>
#include <ctime> 
#include <cstdlib>

using namespace std;
class Board; 
class Player; 
string checkPlayerCoordinates(int boardSize, Board& gameBoard, bool& resign);


class Board{
private: 
    vector<vector<char>> board; 

public: 
    //default constructor
    Board()
    : board{7, vector<char>(7, '.')}
    { 
        //row labels
        for(int i = 1; i <= 6; i++){
            board[i][0] = '`' + i; 
        }

        //column labels
        for(int j = 1; j <= 6; j++){
            board[0][j] = '0' + j; 
        }

        board[0][0] = ' '; 
    }

    //boardsize constructor (static cast to avoid narrowing conversion)
    Board(int size)
    : board{static_cast<size_t>(size + 1), vector<char>(size + 1, '.')}
    {
        //row labels
        for(int i = 1; i <= size; i++){
            board[i][0] = '`' + i; 
        }

        //column labels
        for(int j = 1; j <= size; j++){
            board[0][j] = '0' + j; 
        }

        board[0][0] = ' '; 
    }

    //destructor
    ~Board()
    { }

    //setters
    void setPoint(int i, int j, char c){ board[i][j] = c; } 

    //getters 
    char getPoint(int i, int j) const { return board[i][j]; }

    //methods 
    void print(){
        for(int i = 0; i < board.size(); i++){
            for(int j = 0; j < board[i].size(); j++){
                cout << board[i][j] << ' '; 
            }
            cout << endl; 
        }
    }

    void setSymbol(string s){
        //converts string into index values 
        char cRow = s[0]; 
        int nRow = (int)cRow; 
        int row = -96 + nRow; 

        char cCol = s[1]; 
        int col = cCol - '0'; 

        char sym = s[2]; 

        //checks if resigned
        if(s == "resign"){
            return; 
        }

        //checks if position has already been played
        if(board[row][col] != '.'){
            cout << "Position Already Played" << endl; 
            return; 
        }




        //changes point = to the symbol then prints
        this->setPoint(row, col, sym);  
        this->print(); 
    }
}; //class board


class Player{
private:  
    bool human; 
    bool order;
    bool first; 
    int wins; 


public: 
    //default constructor
    Player()
    : human{true}, order{false}, first{false}, wins{0}
    { }

    ~Player()
    { }

    //getters
    bool getHuman() const { return human; }
    bool getOrder() const { return order; }
    bool getFirst() const { return first; }
    int getWins() const { return wins; }

    //setters
    void setHuman(bool x) { human = x; }
    void setOrder(bool x) { order = x; }
    void setFirst(bool x) { first = x; }
    void setWins(int i) { wins = i; }

    //methods
    string roleTitleConversion(){
        if(this->getOrder()){
            return "Order"; 
        }
        else{
            return "Chaos"; 
        }
    }

    string humanTitleConversion(){
        if(this->getHuman()){
            return "User"; 
        }
        else{
            return "Comp"; 
        }
    }

    void randAssignRole(){
        order = rand() % 2; 

        if(order){
            cout << "You Will Play As Order: " << endl; 
        }

        if(!order){
            cout << "You Will Play As Chaos: " << endl; 
        }
    }

    void randAssignFirst(){
        first = rand() % 2;

        if(first){
            cout << "You Will Play First: " << endl; 
        }

        if(!first){
            cout << "You Will Play Second: " << endl; 
        }
        cout << endl; 
    }

    void humanPlayTurn(int& boardSize, Board& gameBoard, bool& resign){
        string turn = checkPlayerCoordinates(boardSize, gameBoard, resign); 
        cout << "You (" << roleTitleConversion() << ") have moved: " << endl; 
        gameBoard.setSymbol(turn); 
    }

    void computerPlayTurn(int boardSize, Board& gameBoard){
        int row = 0;  
        int col = 0;  
        char sym; 
        bool validMove = false; 

        while(!validMove){
            //selects row and collum 
            row = rand() % boardSize + 1; 
            col = rand() % boardSize + 1;

            if(row == 0){
                row++;
            }
            if(col == 0){
                col++; 
            }

            //selects symbol
            if(rand() % 2 == 0){
                sym = 'x'; 
            }
            else{
                sym = 'o'; 
            }

            //checks if random point is valid 
            if(gameBoard.getPoint(row, col) == '.'){
                validMove = true; 
            }
        }
        cout << "The computer (" << roleTitleConversion() << ") has moved: " << endl; 
        gameBoard.setPoint(row, col, sym); 
        gameBoard.print(); 
    }
}; //class Player 


void printTitle(){
    cout << "----------------------------------------" << endl; 
    cout << "|             ~ welcome to ~           |" << endl; 
    cout << "|    *ORDER*       and       *CHAOS*   |" << endl; 
    cout << "----------------------------------------" << endl; 
    cout << endl; 
}
void printRules(){


    cout << "Order: wins if they make five in a row of either 'x' or 'o'. " << endl
         << "       the row can be horizontaly, vertically, or diagonally." << endl << endl

         << "Chaos: wins by ensuring Order cannot make five in a row. " << endl
         << "       i.e there are no more moves left on the board" << endl << endl

         << "Valid Moves Examples: 'a3x'  'g6o'  'c4o'  'resign'  ." << endl 
         << "       Only 'x' and 'o' are valid pieces, location depends on board size." << endl
         << "       You can resign on any turn regardless of role." << endl << endl;  
}


int getBS(){
    int bs = 0; 
    cout << "Select Board Size (6-9): "; 
    cin >> bs; 

    //checks if input is not an int
    while(!cin.good()){

        //tells user error
        cout << "Please Enter a number" << endl;; 

        //clears the stream
        cin.clear();  
        cin.ignore(INT_FAST64_MAX, '\n'); 

        //gets another input 
        cout << "Select Board Size (6-9): "; 
        cin >> bs; 
    }
    return bs;
}
int selectBoardSize(){
    while(true){
        int i = getBS(); 

        if(i > 9 || i < 6){
            cout << "Invalid Size" << endl; 
        }
        else{
            return i; 
        }
    }
}


string getCord(){
    string cord; 
    cout << "Enter Valid Position: "; 
    cin >> cord; 

    //checks if input is not an int
    while(!cin.good()){

        //tells user error
        cout << "Please Enter a string" << endl;

        //clears the stream
        cin.clear();  
        cin.ignore(INT_FAST64_MAX, '\n'); 

        //gets another input 
        cout << "Enter Valid Position: "; 
        cin >> cord; 
    }
    return cord;
}
string checkPlayerCoordinates(int boardSize, Board& gameBoard, bool& resign){
    while(true){
        string cord = getCord(); 

        //converts string into index values 
        int row = cord[0] - 'a' + 1;
        int col = cord[1] - '0';

        //checks resign 
        if(cord == "resign" || cord == "Resign"){
            resign = true; 
            return "resign"; 
        }
        
        //checks if row and col are valid
        if (row < 0 || row > boardSize || col < 0 || col > boardSize) {
            cout << "Invalid Position" << endl;
        }

        //checks if the position is already played
        if(gameBoard.getPoint(row, col) != '.'){
            cout << "Position Already Played" << endl; 
        }

        //checks if it is 3 letters long 
        else if(cord.size() != 3){
            cout << "Invalid Position" << endl; 
        }

        //checks third letter (symbol)
        else if(cord[2] != 'x' && cord[2] != 'X' && cord[2] != 'o' && cord[2] != 'O'){
            cout << "Invalid Position" << endl; 
        }

        else{
            return cord; 
        }
    }
}


void playerAndComputerSetup(Player& user, Player& comp){
    user.randAssignRole();
    user.randAssignFirst(); 
    comp.setHuman(false); 
    comp.setOrder(!user.getOrder()); 
    comp.setFirst(!user.getFirst()); 
}


bool checkOrderWin(int boardSize, Board& gameBoard){

    //check horizontal connections 
    for(int i = 1; i <= boardSize; i++){
        for(int j = 1; j <= boardSize - 4; j++){
            char sym = gameBoard.getPoint(i, j); 
            if(sym != '.' && 
                sym == gameBoard.getPoint(i, j+1) &&
                sym == gameBoard.getPoint(i, j+2) && 
                sym == gameBoard.getPoint(i, j+3) &&
                sym == gameBoard.getPoint(i, j+4)){
                return true; 
            }
        }
    }

    //check vertical connections 
    for (int i = 1; i <= boardSize; i++) {
        for (int j = 1; j <= boardSize; j++) {
            char sym = gameBoard.getPoint(i, j); 
            if (i <= boardSize - 4) {
                if (sym != '.' && 
                    sym == gameBoard.getPoint(i+1, j) &&
                    sym == gameBoard.getPoint(i+2, j) && 
                    sym == gameBoard.getPoint(i+3, j) &&
                    sym == gameBoard.getPoint(i+4, j)) {
                    return true; 
                }
            }
        }
    }

    // Check diagonal connections
    for (int i = 1; i <= boardSize - 4; i++) {
        for (int j = 1; j <= boardSize - 4; j++) {
            char sym = gameBoard.getPoint(i, j);
            if (sym != '.' && sym == gameBoard.getPoint(i+1, j+1) &&
                sym == gameBoard.getPoint(i+2, j+2) &&
                sym == gameBoard.getPoint(i+3, j+3) &&
                sym == gameBoard.getPoint(i+4, j+4)) {
                return true;
            }
            sym = gameBoard.getPoint(i+4, j);
            if (sym != '.' && sym == gameBoard.getPoint(i+3, j+1) &&
                sym == gameBoard.getPoint(i+2, j+2) &&
                sym == gameBoard.getPoint(i+1, j+3) &&
                sym == gameBoard.getPoint(i, j+4)) {
                return true;
            }
        }
    }
    return false;
}
bool checkChaosWin(int boardSize, Board& gameBoard){
    //returns false when there are still moves to be played
        for(int i = 1; i <= boardSize; i++){
            for(int j = 1; j <= boardSize; j++){
                if(gameBoard.getPoint(i, j) == '.'){
                    return false; 
                }
        }
    }
    return true; 
}
void checkResign(Player& user, bool& resign, bool& oWin, bool& cWin){
    if(resign){
        //sets the opposite to what the user is to true; 
        if(user.getOrder()){
            cWin = true; 
        }
        else{
            oWin = true; 
        }
    }
}


void mainGameplayLoop(int boardSize, Board& gameBoard, Player& user, Player& comp, bool& resign){

        //checks to see who is playing first
        bool firstTurn = true; 
        if(firstTurn){
            if(user.getFirst()){
                user.humanPlayTurn(boardSize, gameBoard, resign); 
                cout << endl; 
            }
            else{
                comp.computerPlayTurn(boardSize, gameBoard); 
                cout << endl; 
            }
            firstTurn = false; 
        }

        // checks who went first and who should go after
        if(user.getFirst()){
            comp.computerPlayTurn(boardSize, gameBoard); 
            cout << endl; 
        }
        else{
            user.humanPlayTurn(boardSize, gameBoard, resign); 
            cout << endl; 
        }
}
void setScore(Player& user, Player& comp, bool oWin, bool cWin){
    if(oWin){
        //adds 1 to the win count 
        if(user.getOrder()){
            user.setWins(user.getWins() + 1); 
        } 
        else{
            comp.setWins(comp.getWins() + 1); 
        }
    }

    if(cWin){
        //adds 1 to the win count 
        if(!user.getOrder()){
            user.setWins(user.getWins() + 1); 
        } 
        else{
            comp.setWins(comp.getWins() + 1); 
        }
    }
}


char getReplay(){
    char c; 
    cout << "Would You Like To Play Again (y/n): "; 
    cin >> c; 

    //checks if input is not an int
    while(c != 'y' && c != 'Y' && c != 'n' && c != 'N'){

        //tells user error
        cout << "Please Enter y/n" << endl;

        //clears the stream
        cin.clear();  
        cin.ignore(INT_FAST64_MAX, '\n'); 

        //gets another input 
        cout << "Would You Like To Play Again (y/n): "; 
        cin >> c; 
    }
    return c; 
}
bool replay(){
    while(true){
        char replay = getReplay(); 

        if(replay == 'y' || replay == 'Y'){
            return true; 
        }

        else if(replay == 'n' || replay == 'N'){
            return false; 
        }
    }
}
void displayEndUse(Player& user, Player& comp){
        cout << "Thanks For Playing!" << endl; 
        cout << "User Wins: " << user.getWins() << endl; 
        cout << "Comp Wins: " << comp.getWins() << endl; 
        exit(EXIT_SUCCESS); 
}


int main(){
    srand(time(NULL)); 
    printTitle(); 
    printRules(); 

    //sets the game up 
    restart:; 
    int boardSize = selectBoardSize(); 
    Board gameBoard(boardSize); 
    Player user; 
    Player comp; 
    bool oWin = false; 
    bool cWin = false;
    bool resign = false; 
    playerAndComputerSetup(user, comp); 

    //goes until order or chaos wins
    while(!oWin && !cWin){
        mainGameplayLoop(boardSize, gameBoard, user, comp, resign);  
        oWin = checkOrderWin(boardSize, gameBoard); 
        cWin = checkChaosWin(boardSize, gameBoard); 
        checkResign(user, resign, oWin, cWin); 
    }

    setScore(user, comp, oWin, cWin); 
    
    //order wins
    if(oWin){
        cout << "ORDER WINS!" << endl;
        bool oReplay = replay(); 

        //restart
        if(oReplay){
            // goto jumps to wherever the marker is 
            goto restart; 
        }
        //display wins and exit 
        else{
            displayEndUse(user, comp); 
        }
    }

    //chaos wins 
    else{
        cout << "CHAOS WINS!" << endl;
        bool cReplay = replay(); 

        //restart
        if(cReplay){
            //goto jumps to where the marker is
            goto restart; 
        }
        //display wins and exit 
        else{
            displayEndUse(user, comp); 
        }
    }
} // main


/*
Assignment 5 Report
===================

Description of Computers Playing Strategy
-----------------------------------------
Completly random. No special strategy just randomly chooses a valid place on the grid
and place a random piece there. 

Extra Features
--------------
I added the win counter per session for both the computer and the user
when you choose to not replay it will display the total wins for the computer
and user for the entire session. Right now there is a bug that makes it so it 
does not work on replay however.  
Also, none of it is hardcoded so it should be able to play
on bigger size grids if I removed the 6-9 cap. 

Known Bugs and Limitations
--------------------------
To my knowledge, my program is unlimited and should pass any situation thrown at it. 
Further, if I remove the cap for the 9 grid it should be able to play on any size grid, 
assuming there are enough characters to represent positions on the grid. The only bug is the 
bug with the implementation of the total win counter not working after selecting replay



----------------------------
(Cite all websites, books, people, etc. that you got help from, including what
sort of help you got. Each citation should be about 1 to 2 lines long.)
*/

//https://openai.com/blog/chatgpt for debugging
//https://www.youtube.com/watch?v=h5S1h8PWCm8 to better understand vector<vector<>> 
//https://www.youtube.com/watch?v=F_npoo9AEKU to understand how to display a grid 
//Toby Donaldson's method of checking for a win as displayed in class. 