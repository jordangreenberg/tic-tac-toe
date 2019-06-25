#include <stdio.h>
#include <stdbool.h>

/**
 * Call this function to display the game board on the terminal.
 *
 * @param board An array that represents the current state of the game.
 * @param playerA A number that represents Player A.
 * @param playerB A number that represents Player B.
 */
void printBoard(int board[], int playerA, int playerB) {    
    printf("\n");
    
    //Prints all 3 rows
    for (int i = 0; i < 9; i += 3) {
    
        //Prints one row
        for (int j = i; j < i + 3; j++) {
            if (board[j] == playerA) {
               printf(" A"); 
            }
            else if (board[j] == playerB) {
                printf(" B");
            }
            else {
                printf(" %d", board[j]);
            }
        }
        printf("\n");
    }
    printf("\n");
    
}

/**
 * Call this function to accept valid input from the user via the keyboard.
 *
 * Valid input from the user is a number between 1 and 9, which represents
 * a location on the game board. In addition, that location must not have
 * already been claimed by Player A or Player B.
 *
 * This function will only return once valid input has been entered by the
 * user.
 *
 * @param board An array that represents the current state of the game.
 * @param playerA A number that represents Player A.
 * @param playerB A number that represents Player B.
 *
 * @return An index to the array that is valid.
 */
int requestValidInput(int board[], int playerA, int playerB) {
    int userInput = 0;
    
    //Request input from user
    do {
        scanf("%d", &userInput);
        
        //Validate input
        if (userInput < 1 || userInput > 9) {
            printf("Invalid input, please try again.\n");
        }
        
        //Check to see if spot has already been played
        else if (board[userInput - 1] == playerA || board[userInput - 1] == playerB) {
            printf("That position has already been played, please try again.\n");
        }
        
        //If input is valid, return index of board position played
        else {
            return (userInput - 1);
        }
    }while(true);

}

/**
 * Call this function when it has been determined a player has won the game
 * This function determines who the winner is
 * 
 * @param index A number representing one of the winning positions on the board\
 * @param board An array representing the game board
 * @param playerA A number representing player A
 * @param playerB A number representing player B
 * @return winner A number representing the winning player
 */
 int winningPlayer(int index, int board[], int playerA, int playerB) {
     if (board[index] == playerA) {
            return playerA;
        }
        else {
            return playerB;
        }
 }

/**
 * Call this function to check who, if anyone, has won the game.
 *
 * @param board An array that represents the current state of the game.
 * @param playerA A number that represents Player A.
 * @param playerB A number that represents Player B.
 *
 * @return 0 if neither Player A nor Player B has won the game. Otherwise,
 *         the function will return the player who has won.
 */
int checkForWinner(int board[], int playerA, int playerB) {
    
    //Check all possible horizontal combinations
    if (board[0] == board[1] && board[0] == board[2]) {
        return (winningPlayer(0, board, playerA, playerB));
    }
    else if (board[3] == board[4] && board[3] == board[5]) {
        return (winningPlayer(3, board, playerA, playerB));
    }
    else if (board[6] == board[7] && board[6] == board[8]) {
        return (winningPlayer(6, board, playerA, playerB));
    }
    
    //Check all possible vertical combinations
    else if (board[0] == board[3] && board[0] == board[6]) {
        return (winningPlayer(0, board, playerA, playerB));
    }
    else if (board[1] == board[4] && board[1] == board[7]) {
        return (winningPlayer(1, board, playerA, playerB));
    }
    else if (board[2] == board[5] && board[2] == board[8]) {
        return (winningPlayer(2, board, playerA, playerB));
    }
    
    //Check all possible diagonal combinations
    else if (board[0] == board[4] && board[0] == board[8]) {
        return (winningPlayer(0, board, playerA, playerB));
    }
    else if (board[2] == board[4] && board[2] == board[6]) {
        return (winningPlayer(2, board, playerA, playerB));
    }

    //If no player has won, return 0
    else {
       return 0; 
    }
}
 
 /**
  * Call this function to check if the game has ended in a draw
  * @param board An array that represents the game board
  * @return true if game has ended in a draw, false if not
  */
bool checkForDraw(int board[]) {
    for (int i = 0; i < 9; i++) {
        if (board[i] == (i + 1)) {
            return false;
        }
    }
    return true;
}

int main(void) {
    //Initialize game board and player's unique integer identifiers
    int board [] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    const int PLAYER_A = 12;
    const int PLAYER_B = 14;
    bool gameOver = false;
    int winner = 0;
    
    //Game starts with Player A
    int currentPlayer = PLAYER_A;
    
    //Start the game loop
    while (!gameOver) {
        //Print the current state of the game
        printf("The current state of the Tic-tac-toe Board:\n");
        printBoard(board, PLAYER_A, PLAYER_B);
        
        //Print whoever's turn it is
        if (currentPlayer == PLAYER_A) {
            printf("It is Player A's turn.\n");
        }
        else {
            printf("It is Player B's turn.\n");
        }
        
        //Get user's input
        printf("Please enter a valid position to play.\n");
        int inputIndex = requestValidInput(board, PLAYER_A, PLAYER_B);
        
        //Update game state
        board[inputIndex] = currentPlayer;
        
        //Switch turns
        if (currentPlayer == PLAYER_A) {
            currentPlayer = PLAYER_B;
        }
        else {
            currentPlayer = PLAYER_A;
        }
        
        //Check if a player has won the game
        winner = checkForWinner(board, PLAYER_A, PLAYER_B);
        if (winner != 0) {
            gameOver = true;
        }
        
        //Check for a draw
        else if (checkForDraw(board)) {
            gameOver = true;
        }
    }
    
    //Print results of game
    if (winner == PLAYER_A) {
        printf("Player A wins!\n");
    }
    else if (winner == PLAYER_B) {
        printf("Player B wins!\n");
    }
    else {
        printf("It's a draw!\n");
    }
    
    //Print Board
    printBoard(board, PLAYER_A, PLAYER_B);

    return 0;
}
