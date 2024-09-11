/**
checkSolutionDetail:
For row collision, I declared the array of countRow of length 10: it will contain frequency
of each value(from 0 to 9) appearance in the given row [x][j] where j is changing variable from
0 to 8, since the sudoku board is 9x9. It will take the value of gameBoard[x][j] which varies from 0 to 9 and
store it inside its array.
Then it will iterate once again from 1 to 9(since 0 is an empty space so it doesn't count) and then with a newly declared
variable countRow1 it will increment countRow1 everytime when there is a frequency higher than 1, such as that there is
a duplicate value. In case countRow1 is non-zero value, it means there is a duplicate, thus there is a collision
For column collision, idea the same as for row collision. The array of countColumn of a length of 10 will track the frequency of
each value occurence in the given column [j][y], where j is a varying value from 0 to 8. Then with countColumn1, it will count the
number of times, when there was a frequency of each value more than 1 time. If the countColumn1 is more than 0, it means
there is a collision in the column.
For subgrid collision, I've noticed that the integer division by 3 might help me find each subgrid the x,y is located in. Such as
if I divide x/3 and the answer is 0, it means that the subgrid is located in the upper bound(row from 0 to 2)
or if I divide y/3 and get 2, it means the y is located in the lower bound(column from 6 to 8). So if x/3 and y/3 are 0 and 2
respectively, it means the subgrid is located on the row from 0 to 2, and the column is from 6 to 8. Thus, for the tracking
purpose I declared the regionX and regionY variable to store the result of integer division.
If the division result is 0, I set the value of regionX/regionY to 0
if the result is 1, I set them to 3
if the result if 2, I set to 6
Then just like in row and column, i run through the nested loop(where the incrementation happens 3 times only), and store the
frequency of values inside the array countSub. Then through another loop from 1 to 9, I find if there is any value whose frequency
is more than 1 and if yes, print collision.
In case all there counts have zero duplicate frequencies, I return 1 which means there are no collision



**/

#include <stdio.h>

void initGameBoard(int gameBoard[][9], int puzzle[][9]) {

   // TODO: Complete this part
   // Hint: Copies the content of puzzle to gameBoard
   for(int i=0;i<9;i++){
       for(int j=0;j<9;j++){
           gameBoard[i][j] = puzzle[i][j];
       }
   }
}


void printGameBoard(int gameBoard[][9]) {
   // TODO: Complete this part
   // Hint:
   // 1. First, try to prints the content of gameBoard
   // 2. Use conditional statement to print ' ' or 'X' for the two cases (empty or selected cell).
   // 3. Add the borders, col/row numbers
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
   if(input == 'H') {
       if(gameMode == 1){
           printf("No hint in Hard mode.\n"); gameBoard[x][y] = '\0'; return -1;
       }
       else  return 1;
   }

   else if(input <= '9' && input >= '1')
   {
       gameBoard[x][y] = (int)(input - 48);
       return 0;
   }
   else { printf("Invalid input.\n"); gameBoard[x][y] = '\0';
       return -1;
   }
}






int checkFinish(int gameBoard[][9], int sol[][9]){
   for(int i = 0; i < 9; i++){
       for(int j = 0; j < 9; j++){
           if(gameBoard[i][j] != sol[i][j]) return 0;
       }
   }
   // TODO: Complete this part

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
    printf("Check again the numbers in the column %d.\n", y);

}
          if(countSub1 >=1){
              printf("Check again the numbers in the subgrid where (%d, %d) is at.\n", x,y);
       }
   if(countSub1 == 0 && countColumn1 == 0 && countRow1 == 0) return 0;

   return 1;
}


int checkFillable(int gameBoard[][9], int x, int y){
   // TODO: Complete this part

   return 0;
}


int isLockBoard(int gameBoard[][9]){
   // TODO: Complete this part
   return 0;
}



int savePuzzle(int gameBoard[][9], int sol[][9]){
  
   return 0;
}


int loadPuzzle(int gameBoard[][9], int sol[][9]){
   return 0;
  
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
           fprintf(fp, "%d\n", solution[i][j]); // You may print a character to test Hint/Save-load function.
       }
   }
   fclose(fp);
}


int main(void)
{
   
   int myPuzzle[9][9]={
       {5,0,0,0,6,3,4,0,0},
       {0,0,0,7,0,0,0,0,0},
       {1,0,0,0,5,0,8,3,0},
       {0,0,0,0,1,8,0,0,7},
       {0,0,6,9,0,0,0,0,0},
       {0,4,3,0,0,0,9,0,0},
       {0,0,0,0,0,0,0,0,0},
       {0,0,0,0,7,0,0,2,0},
       {3,2,0,6,4,0,5,0,0}
   };
  
   int mySolution[9][9] = {
       {5,9,8,1,6,3,4,7,2},
       {6,3,2,7,8,4,1,5,9},
       {1,7,4,2,5,9,8,3,6},
       {2,5,9,4,1,8,3,6,7},
       {8,1,6,9,3,7,2,4,5},
       {7,4,3,5,2,6,9,8,1},
       {4,6,5,8,9,2,7,1,3},
       {9,8,1,3,7,5,6,2,4},
       {3,2,7,6,4,1,5,9,8}
   };
   
   int gameBoard[9][9];

   
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
           win = 1;
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
                   if(inputValid == -1) {printGameBoard(gameBoard);  continue;}
               }

               else if(gameMode == 1){
                   inputValid = inputBoard(gameBoard, x, y, mySolution, gameMode);
                   if(inputValid == -1) { printGameBoard(gameBoard); continue;}
                   else if(inputValid == 0){
                       checkSolution = checkSolutionDetail(gameBoard, x, y);
                       if(checkSolution == 1){ chances--;
                           if(chances > 0){
                               printf("You have %d chances left.\n", chances); gameBoard[x][y] = '\0';
                               printGameBoard(gameBoard);}

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


