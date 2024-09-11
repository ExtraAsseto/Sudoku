/**
Save Load function:
a) to save puzzle as a file I use function SavePuzzle, where I declare a new file called "savePuzzle" in the text format
("txt") for writing only. Then through the loop, I use fprintf and the values of gameBoard to write inside the file. Each row
is separated by new line using the fprintf(filepointer, "\n"). The next loop will copy the values of the solution by
going through the same mechanism. Then the result of the file will be the saved gameBoard values with solution values both
separated by the new line.
As for load option,
b) before the game mode selection, the code asks whether the user wants to load the saved puzzle. In case no, the game will simply
read from the text file that contains the original puzzle. In case yes, the game will use loadPuzzle function. The function
will check if there exists a file which is savePuzzle: in case not, it terminates the program. The loop will use fscanf to
scan each value of the gameBoard values into the myPuzzle from the text file savePuzzle which was created by the savePuzzle
function. To omit new lines, I declared a new character variable called new line,
which will read the new line, thus, omitting it. The same procedure goes with the solution. Then the file is closed.

c) Yes, as long as the text file contains the integer values and the new lines, similar to the text file "savePuzzle", otherwise
there might be problems with data types or incomplete array (in case not enough values are stored inside that text file).
But in general, any text file might be used inside the function loadPuzzle


Locked Block Checker:
a) in the isLockBoard, the function uses nested loop to go through all the empty cells left on the game Board, then with the
given x,y coordinates of the empty cells it calls the function checkFillable.
In checkFillable, to check to possible answers left for the specific empty cell, we first count the frequency of each
value in the row,column and subgrid that the cell is located in by declaring 3 arrays: column, row, sub, all of length 10;
then through the loop, it counts the frequency of each value occuring in column, row, subgrid.
Then I declare the variable countFillable to count how many numbers are there that the empty cell can take in by checking whether
there is any common value in all three categories(row, column, subgrid) whose frequency equals to 0, meaning the value hasn't
been used yet. This would help to find out whether the set of possible answers is zero; in this case, there are no other values
that the cell can take inside to complete the puzzle and the game stops.
b) When checkFillable function checks if the cell is locked or not, it will return 0 if the cell is locked and 1 otherwise. Then
by being called in the function isLockBoard, it will control the flow of the code and stop the game in case any cell is locked.
CheckFillable function helps to easily check each empty cell of being locked or not by iterating through the loop inside the
isLockBoard function.




**/
#include <stdio.h>



void initGameBoard(int gameBoard[][9], int puzzle[][9]) {

   
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            gameBoard[i][j] = puzzle[i][j];
        }
    }
}


void printGameBoard(int gameBoard[][9]) {
    
    printf("  012 345 678 \n");
    printf(" +---+---+---+\n");
    for(int i = 0; i<3;i++){
        printf("%d|",i);
        for(int j = 0; j<9;j++){
            if(j==3 || j==6){
                printf("|");
            }
            if(gameBoard[i][j]==0){
                printf(" ");
            }
            else if(gameBoard[i][j] == 10) printf("X");
            else printf("%d",gameBoard[i][j]);
        }
        printf("|");
        printf("\n");

    }
    printf(" +---+---+---+\n");
    for(int i = 3; i<6;i++){
        printf("%d|",i);
        for(int j = 0; j<9;j++){
            if(j==3 || j==6){
                printf("|");
            }
            if(gameBoard[i][j]==0){
                printf(" ");
            }
            else if(gameBoard[i][j] == 10) printf("X");
            else printf("%d",gameBoard[i][j]);
        }
        printf("|");
        printf("\n");

    }
    printf(" +---+---+---+\n");
    for(int i = 6; i<9;i++){
        printf("%d|",i);
        for(int j = 0; j<9;j++){
            if(j==3 || j==6){
                printf("|");
            }
            if(gameBoard[i][j]==0){
                printf(" ");
            }
            else if(gameBoard[i][j] == 10) printf("X");
            else printf("%d",gameBoard[i][j]);
        }
        printf("|");
        printf("\n");

    }
    printf(" +---+---+---+\n");

}


int inputBoard(int gameBoard[][9], int x, int y, int sol[][9], int gameMode){
    // TODO: Complete this part
    char input;
    printf("Input a number [or H: hint]: ");
    scanf(" %c", &input);
    if(input == 'S') {
            savePuzzle(gameBoard, sol, x, y);
            printf("Game saved.\n");
            exit(0);
    }
    if(input == 'H') {
        if(gameMode == 1){
            printf("No hint in Hard mode\n");
            gameBoard[x][y] = '\0';
            return -1;
        }
        else  return 1;
    }

    else if(input <= '9' && input >= '1')
    {
        gameBoard[x][y] = (int)(input - 48);
        return 0;
    }
    else {printf("Invalid input.\n"); gameBoard[x][y] = '\0'; return -1;}
}






int checkFinish(int gameBoard[][9], int sol[][9]){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(gameBoard[i][j] != sol[i][j]) return 0;
        }
    }
   

    return 1;

}




int checkSolutionDetail(int gameBoard[][9], int x, int y){
    // TODO: Complete this part
    int countColumn1 = 0;
    int countRow1 = 0;
    int countSub1 = 0;
    int countRow[10] = {0};
    int countColumn[10] = {0};
    int countSub[10] = {0};
        for(int j = 0; j< 9; j++){
            countRow[gameBoard[x][j]]++;
            }
        for(int j = 0; j < 9; j++){
            countColumn[gameBoard[j][y]]++;
        }
    int regionX = x/3; int regionY = y/3;
    if(regionX == 0) {regionX = 0; }
    else if(regionX == 1) {regionX = 3; }
    else if(regionX == 2) {regionX = 6;}


    if(regionY == 0) {regionY = 0; }
    else if(regionY == 1) {regionY = 3; }
    else if(regionY == 2) {regionY = 6;}

    for(int i = regionX; i<regionX+3; i++){
        for(int j = regionY; j<regionY+3; j++){
            countSub[gameBoard[i][j]]++;
        }
    }

    for(int i = 1; i < 10; i++){
        if(countColumn[i] > 1){
            countColumn1++;
        }
        if(countRow[i] > 1){
            countRow1++;
        }
        if(countSub[i] > 1){
            countSub1++;
        }
    }
    if(countRow1 >=1){
        printf("Check again the numbers in the row %d.\n", x);
    }
    if(countColumn1 >= 1){
        printf("Check again the numbers in the column %d.\n", y);}

    if(countSub1 >=1){
        printf("Check again the numbers in the subgrid where (%d, %d) is at.\n", x,y);
            return 1;
                   }

        else if(countColumn1 == 0 && countRow1 == 0 && countSub1 == 0)
        return 0;
    return 1;
}


int checkFillable(int gameBoard[][9], int x, int y){
    // TODO: Complete this part
    int column[10] = {0};
    int row[10] = {0};
    int sub[10] = {0};

    for(int i = 0; i < 9; i++){
        column[gameBoard[i][y]]++;
    }
    for(int i = 0; i < 9; i++){
        column[gameBoard[x][i]]++;
    }
    int regionX = x/3; int regionY = y/3;
    if(regionX == 0) {regionX = 0; }
    else if(regionX == 1) {regionX = 3; }
    else if(regionX == 2) {regionX = 6;}


    if(regionY == 0) {regionY = 0; }
    else if(regionY == 1) {regionY = 3; }
    else if(regionY == 2) {regionY = 6;}

    for(int i = regionX; i<regionX+3; i++){
        for(int j = regionY; j<regionY+3; j++){
            sub[gameBoard[i][j]]++;
        }
    }



    int countFillable = 0;
    for(int i = 1; i<10; i++){
        if(sub[i] == 0 && column[i] == 0 && row[i] == 0){
            countFillable++;
        }
    }
    if(countFillable == 0) {return 0; }
    else return 1;

}


int isLockBoard(int gameBoard[][9]){
    // TODO: Complete this part
    int ifFillable = 0;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j <9; j++){
            if(gameBoard[i][j] == '\0'){
                ifFillable = checkFillable(gameBoard, i, j);
                if(ifFillable == 0){
                    printf("Cell (%d, %d) is locked.\n", i, j);
                    return 1;
                }
                else continue;
            }
        }
    }
    return 0;
}


int savePuzzle(int gameBoard[][9], int sol[][9], int x, int y){
    // TODO: Complete this part
    FILE *fptr;
    fptr = fopen("savePuzzle.txt", "w");
    gameBoard[x][y] = '\0';
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){


            fprintf(fptr, "%d ", gameBoard[i][j]);
        }
        fprintf(fptr, "\n");
    }
    fprintf(fptr, "\n");
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            fprintf(fptr, "%d ", sol[i][j]);

        }
        fprintf(fptr, "\n");
    }
    fclose(fptr);
    return 1;
}


int loadPuzzle(int gameBoard[][9], int sol[][9]){
    FILE *fptr;
    char newline;
    fptr = fopen("savePuzzle.txt", "r");
    if(fptr == NULL) exit(0);
    for(int i = 0; i < 9; i++){
        for(int j =0; j <9; j++){
            fscanf(fptr, "%d", &gameBoard[i][j]);
        }
        fscanf(fptr, "%c", &newline);

    }
    fscanf(fptr, "%c", &newline);
    for(int i = 0; i < 9; i++){
        for(int j =0; j<9; j++){
            fscanf(fptr, "%d", &sol[i][j]);
        }
        fscanf(fptr, "%c", &newline);
    }
    fclose(fptr);

    return 1;

    // TODO: Complete this part

}

void printSolution(int puzzle[][9],int solution[][9]){
    FILE *fp;
    fp = fopen("textInput.txt", "w");
    if (fp == NULL) {printf("Error in writing file."); return;}

    fprintf(fp,"0\n"); // Change to 1 if runns in Hard mode
    for(int i=0; i<9; i++)
    for (int j=0; j<9; j++){
        if (puzzle[i][j]==0){
            fprintf(fp, "%d %d\n", i, j);
            fprintf(fp, "%d\n", solution[i][j]);
        }
    }
    fclose(fp);
}


int main(void)
{
    debug, e.g., replace some entries of the solution by 0
    int myPuzzle[9][9]={
        0
    };
   
    int mySolution[9][9] = {
        0
    };

    
    char newline;
    int gameBoard[9][9];
    char load;
    while(1){
        printf("Load the saved game (y/n)? ");
        scanf(" %c", &load);
        if(load == 'y') {
            loadPuzzle(myPuzzle, mySolution); break;
            }



        else if(load == 'n') {
            FILE *fin;
            fin = fopen("puzzle.txt", "r");

            for(int i = 0; i < 9; i++)
            {
                for(int j = 0; j <  9; j++){
                    fscanf(fin, "%d", &myPuzzle[i][j]);
                }
                fscanf(fin, "%c", &newline);
            }
            fscanf(fin, "%c", &newline);
            for(int i = 0; i < 9; i++){
                for(int j =0; j<9; j++){
                    fscanf(fin, "%d", &mySolution[i][j]);
                }
                fscanf(fin, "%c", &newline);
            }
            fclose(fin); break;
        }
        else continue;
    }



    
   
    int gameMode, chances = 3, hintCount = 0;

   
    int x, y;

   
    int number;

    
    int win = 0, validIn = 0, inputValid = 1;
    int check = 1;
    int checkSolution;
    
    while(1){
        printf("Enter the game mode [0: Easy. 1: Hard]: ");
        scanf("%d", &gameMode);
        if(gameMode == 0){
            printf("You have selected Easy mode.\n");
            break;
        }
        else if(gameMode == 1){
            printf("You have selected Hard mode.\n");
            break;
        }
        else {
            printf("Invalid Input.\n");

        }
    }

    

    initGameBoard(gameBoard, myPuzzle);
    printGameBoard(gameBoard);

    
    while(1){
        check = checkFinish(gameBoard, mySolution);
        if(check == 1){
            break;
        }
            printf("Select a row and column: ");
            scanf("%d%d", &x,&y);
        if((x >= 0 && x <= 8) && (y>=0 && y <=8)){
            if(gameBoard[x][y] == '\0'){
                gameBoard[x][y] = 10;
                printGameBoard(gameBoard);
                if(gameMode == 0){
                    inputValid = inputBoard(gameBoard, x, y, mySolution, gameMode);



                    if(inputValid == 0) {
                        if(gameBoard[x][y] == mySolution[x][y]){
                            printGameBoard(gameBoard);}
                        else {
                            printf("Sorry %d should not be placed at (%d, %d).\n", gameBoard[x][y],x,y);
                            gameBoard[x][y] = '\0';
                        }
                    }

                    else if(inputValid == 1) {
                        gameBoard[x][y] = mySolution[x][y];
                        hintCount++;
                        printGameBoard(gameBoard);


                    }
                    else if(inputValid == -1) {printGameBoard(gameBoard); continue;}

                }

                else if(gameMode == 1){
                    inputValid = inputBoard(gameBoard, x, y, mySolution, gameMode);
                    if(inputValid == -1) { printGameBoard(gameBoard); continue;}
                    else if(inputValid == 0){
                        if(isLockBoard(gameBoard) == 1) {
                            printf("Board is locked.\n");
                            win = 0;
                            break;
                        }
                        checkSolution = checkSolutionDetail(gameBoard, x, y);
                        if(checkSolution == 1){ chances--;
                            if(chances >0){
                                printf("You have %d chances left.\n", chances); gameBoard[x][y] = '\0';
                                printGameBoard(gameBoard);
                            }
                            if(chances == 0) {win = 0; break;}}

                        else {printGameBoard(gameBoard);continue;}
                    }

                }
            }

            else {printf("Occupied.\n"); continue;}
        }
            else { printf("Out of bound. Input Again.\n");
                continue; }

        }


    if(win == 1){
        if(gameMode == 0){
            printf("Congratulations! You have finished a puzzle in easy mode and used %d hints.", hintCount);
            return 0;}
        else if(gameMode == 1){
            printf("Congratulations! You have finished a puzzle in hard mode with %d chances left.", chances);
            return 0;
        }
    }

    else {
        printf("You lose.\n");
    }


    return 0;
}



