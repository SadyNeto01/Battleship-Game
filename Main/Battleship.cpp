#include <iostream>
#include <new>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

void mainMenu();


void cleanScreen(){
    system("CLS");
}
void startBoard(char board[10][10], char mask[10][10]){
    int i,j;
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){
            board[i][j] = 'W';
            mask[i][j] = '*';
        }
    }
}
void printIndex(){
    int j;
    //create the index of columns
    for(j=0;j<10;j++){
        if(j==0){
            cout <<"    ";
        }
        cout <<j << " ";
    }
    cout << "\n";
}
void printBoard(char board[10][10], char mask[10][10], bool showMask){
    char blue[] = { 0x1b, '[', '1', ';', '3', '4', 'm', 0 };
    char green[] = { 0x1b, '[', '1', ';', '3', '2', 'm', 0 };
    char normal[] = { 0x1b, '[', '1', ';', '3', '9', 'm', 0 };
    int i,j;
    for(i=0;i<10;i++){
        cout << i<< "->";
        for(j=0;j<10;j++){
            switch(mask[i][j]){
                case 'W':
                    cout << blue << " " <<mask[i][j] << normal;
                break;
                case 'S':
                    cout << green << " " <<mask[i][j] << normal;
                break;
                default:
                    cout << " " <<mask[i][j];
                break;
            }
        }
        cout << "\n";
    }
    if(showMask == true){
            for(i=0;i<10;i++){
                for(j=0;j<10;j++){
                    cout <<"  "<< board[i][j];
                }
            cout << "\n";
        }
    }

}

void addShip(char board[10][10], int amount){
    int i, lineShip, colShip, nShips = 0;
    //check if all the ships are placed is the same as amount because the rand can generate the same number twice
    while(nShips < amount){
            lineShip = rand()%10;
            colShip = rand()%10;
            if(board[lineShip][colShip] =='W'){
                board[lineShip][colShip] = 'S';
                nShips++;
            }
    }
}
void verifyShot(char board[10][10], int chosenLine, int chosenColumn, int *points, string *message){
    //check if a ship was hitten
    switch(board[chosenLine][chosenColumn]){
        case 'S':
            *points = *points+10;
            *message = "You've hit a ship (10pts)";
            break;
        case 'W':
            *message = "You didn't hit any ship";
            break;

    }
}

void game(string playerName){
    char board[10][10], mask[10][10];
    int chosenLine, chosenColumn, gameState = 1, amount, points =0, chances = 0, choice;
    string message;
    while(amount > 16 || amount <1){
    cout << "How many ships you wanna add(max 16): ";
    cin >> amount;
    }
    int  maxChances = amount +6;
    startBoard(board, mask);
    //add ships randomly
    addShip(board, amount);
    while(chances < maxChances){
        cleanScreen();
        printIndex();
        printBoard(board, mask,false);
        cout << message;
        chosenLine = -1;
        chosenColumn = -1;
        cout << "\nYour number of points is "<< points;
        while((chosenLine < 0 || chosenColumn <0) ||(chosenLine >9 || chosenColumn >9)) {
            cout << "\nYou have "<< maxChances - chances <<" chances remaining";
            cout << "\n"<<playerName<<", choose a line to attack: ";
            cin >> chosenLine;
            cout << playerName<<", now choose a column to attack: ";
            cin >> chosenColumn;
        }

        verifyShot(board, chosenLine, chosenColumn, &points, &message);
        //reveal what was your choice(if u hit a ship or water)
        mask[chosenLine][chosenColumn] = board[chosenLine][chosenColumn];
        chances++;
    }
    cout <<"\n"<<playerName<<" the game has finished, what would you like to do?";
    cout << "\n1- Play again";
    cout << "\n2- Go to the main menu";
    cout << "\n3- Leave the program\n";
    cin >> choice;
    switch(choice){
        case 1:
            cleanScreen();
            game(playerName);
            break;
        case 2:
            cleanScreen();
            mainMenu();
            break;

   }

}


void mainMenu(){
    int choice =0;
    string playerName;

   while (choice <1 || choice>3){
    cleanScreen();
    cout << "Welcome to the game";
    cout << "\n1 - Play";
    cout << "\n2 - About the game";
    cout << "\n3 - Leave the program";
    cout << "\nChoose an option: ";
    cin >> choice;
   }

   switch(choice){
    case 1:
        cout <<"What is your name?\n";
        cin  >> playerName;
        game(playerName);
        break;
    case 2:
        cout << "Game created on 25/05/2024 by Sady Neto during the course of C and C++ development ";
        break;
    case 3:
        cout << "Thanks for playing";
        break;

   }
}


int main(){
    srand((unsigned)time(NULL));
    mainMenu();
    return 0;
}
