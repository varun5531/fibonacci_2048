#include "function_declarations.h"

int main()
{
	startGame();
	return 0;
}

void startGame() {
	int c;
	printf("\nenter 1 - new game / 2 - resume game / 3 - leaderboard / any key to exit\n: ");
	scanf("%d", &c);
	switch (c) {
	case 1:
		generateNewGame();
		break;
	case 2:
		generateOldGame();
		break;
	case 3:
		getLeaderBoard();
		break;
	}
}

int** getDetailsFromUser(char name[], int *n) {
	getName(name);
	printf("enter 2 - 2x2 game / 4 - 4x4 game / enter size(3 for 3x3)\n: ");
	scanf("%d", n);
	int t = *n;
	int **a = (int **)calloc(t, sizeof(int *));
	for (int i = 0; i < t; i++) {
		a[i] = (int *)calloc(t, sizeof(int));
	}
	return a;
}

void generateNewGame() { //when a user looses and wants to play once again then we send some char c( other than '\0') so that his name wont be asked once again
	char name[20];
	int n, **a;
	a = getDetailsFromUser(name, &n);
	printGame(name, 0, n, a);
	generateOneRandomly(a, n);
	generateOneRandomly(a, n);
	playGame(name, a, 0, n); //initially moves are 0 so sending 0
}

void generateOldGame() {
	char name[20];
	int **a, moves, n;
	a = getStateFromFile(name, &moves, &n);
	if (moves == -1) {
		printf("\nno game is saved till now\nplease play a game and then save\n");
		startGame();
	}
	else
		playGame(name, a, moves, n);
}

void getLeaderBoard() {
	FILE *fp = fopen("fib_leaderboard.txt", "r");
	char arr[100];
	char c;
	int t = 1; //t used to print SNO
	printf("\nSNO\tDATE\t\t    NAME\t\t  MOVES BOARD(n=n*n)\n\n");
	c = fgetc(fp);
	while (c != EOF && t <= 20) {
		printf("%d  \t", t++);
		fseek(fp, -1, SEEK_CUR);
		fgets(arr, 100, fp);
		printf("%s", arr);
		c = fgetc(fp);
	}
	fclose(fp);
	startGame();
}

void printGame(char name[], int moves, int n, int **a) {
	printf("\n\n\t\t");
	printf("name : %s\t\ttype of board : %d x %d\n\n\t\t", name, n, n);
	printf("moves : %d\n\n\t\t\t\t", moves);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d\t", a[i][j]);
		}
		printf("\n\t\t\t\t");
	}
	printf("\n");
}


void getName(char name[]) { //this reads the name from user until the name entered is not already taken
	printf("enter nick-name: ");
	scanf("%s", name);
	int k = 0;
	FILE *fp;
	while (true) {
		k = 0;
		if (fp = fopen("fib_leaderboard.txt", "r")) {
			if (checkIfNameExists(fp, name))
				k = 1;
			fclose(fp);
		}
		if (k == 0) {
			if (fp = fopen("fib_state.txt", "r")) {
				char c = fgetc(fp);
				if (c != EOF) {
					fseek(fp, -1, SEEK_CUR);
					if (checkIfNameExists(fp, name))
						k = 1;
				}
				fclose(fp);
			}
		}
		if (k == 0)
			break;
		printf("name is already taken choose other name: ");
		scanf("%s", name);
	}
}

char* getDate(char *date) {
	time_t t;
	time(&t);
	date = ctime(&t);
	*(date + 0) = *(date + 8);
	*(date + 1) = *(date + 9);
	*(date + 2) = '-';
	*(date + 3) = *(date + 4);
	*(date + 4) = *(date + 5);
	*(date + 5) = *(date + 6);
	*(date + 6) = '-';
	*(date + 7) = *(date + 20);
	*(date + 8) = *(date + 21);
	*(date + 9) = *(date + 22);
	*(date + 10) = *(date + 23);
	*(date + 11) = '\0';
	return date;
}

void storeUser(char name[], int **a, int moves, int board) {
	char *date = NULL;
	date = getDate(date);
	storeInFile(name, moves, board, date);
	removeContentsOfResumeGame();
	printf("\t\twoo-ohh congrats you have won the game in %d moves\n", moves);
}

void playGame(char name[], int **a, int moves, int n) {
	int c;
	while (true) {
		system("cls");
		printGame(name, moves, n, a);
		if (won(a, n)) {
			storeUser(name, a, moves, n);
			startGame();
			break;
		}
		if (furtherMovePossible(a, n) == false) {
			printf("\n\t\tGame Over - you've lost in %d moves\n", moves);
			removeContentsOfResumeGame();
			startGame();
			break;
		}
		moves++;
		saveStateToFile(name, moves, n, a);
		if ((c = handleInputs(name, moves, n, a)) == 1) {
			startGame();
			break;
		}
		generateOneRandomly(a, n);
	}
}

void generateOneRandomly(int **a, int n) { //generates 1 at a random position
	srand(time(0));
	int i = rand() % n, j = rand() % n;
	while (a[i][j] != 0) {
		i = rand() % n;
		j = rand() % n;
	}
	a[i][j] = 1;
}

bool won(int **a, int n) {
	int win = 2 * n * n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (a[i][j] == win) {
				return true;
			}
		}
	}
	return false;
}

bool mergebleByElementRightToCurrentEle(int **a, int n, int i, int j) {
	if (j != n - 1 && isMergeble(a[i][j], a[i][j + 1]))
		return true;
	return false;
}

bool mergebleByElementDownToCurrentEle(int **a, int n, int i, int j) {
	if (i != n - 1 && isMergeble(a[i][j], a[i + 1][j]))
		return true;
	return false;
}

bool furtherMovePossible(int **a, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (a[i][j] == 0)  //this is if atleast one 0 is there then a move is possible so return true
				return true;
			else if (i == n - 1 && j == n - 1)
				return false;
			else if (mergebleByElementRightToCurrentEle(a, n, i, j) || mergebleByElementDownToCurrentEle(a, n, i, j))
				return true;
		}
	}
}
