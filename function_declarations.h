
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdbool.h>
#include<math.h>
void startGame();
void generateNewGame();
void generateOldGame();
void getLeaderBoard();
void printGame(char[], int, int, int **);
void getName(char[]);
void playGame(char[], int **, int, int);
void generateOneRandomly(int **, int);
bool won(int **, int);
bool furtherMovePossible(int **, int);
int** getDetailsFromUser(char[], int *);
char* getDate(char[]);
void storeUser(char[], int **, int, int);


void downMove(int **, int);
void shiftdown(int **, int, int, int, int);
void upMove(int **, int);
void shiftUp(int **, int, int, int, int);
void leftMove(int **, int);
void shiftLeft(int **, int, int, int, int);
void rightMove(int **, int);
void shiftRight(int **, int, int, int, int);
int handleInputs(char[], int, int, int **);
void removeZeroesOfColumnsForDownMove(int **, int);
void removeZeroesOfColumnsForUpMove(int **, int);
void removeZeroesOfaRowRightMove(int **, int);
void removeZeroesOfaRowLeftMove(int **, int);


bool checkIfNameExists(FILE *, char[]);
void storeInFile(char[], int, int, char[]);
void storeNumberInFile(FILE *, int, int, int);
void insertToFileFromThatPos(FILE *, char[], int, int, char[]);
void saveStateToFile(char[], int, int, int **);
int** getStateFromFile(char[], int *, int *);
int getANumberFromFile(FILE *);
int no_of_digits(int);
void removeContentsOfResumeGame();
void getNameFromFile(FILE *, char[]);


bool isMergeble(int, int);
bool isFibonacci(int);
bool isPerfectSquare(int);
