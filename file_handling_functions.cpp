#include "function_declarations.h"

void removeContentsOfResumeGame() { //used just to remove data of resume game
	FILE *fp = fopen("fib_state.txt", "w");
}

void getNameFromFile(FILE *fp, char name[]) { //stores the string from current fp position to name
	int k = 0;
	char c;
	//fseek(fp, 21, SEEK_CUR);
	c = fgetc(fp);
	while (c != ' ') {
		name[k++] = c;
		c = fgetc(fp);
	}
	name[k] = '\0';
}

bool checkIfNameExists(FILE *fp, char name[]) {
	char t_name[20];
	char c;
	char temp[100]; // this is used with fgets to move file pointer to next line
	while (true) {
		getNameFromFile(fp, t_name);
		if (!strcmp(t_name, name))
			return 1;
		fgets(temp, 100, fp);
		c = fgetc(fp);
		if (c == EOF)
			break;
		else fseek(fp, -1, SEEK_CUR);
	}
	return 0;
}

void storeInFile(char name[], int moves, int board, char date[]) { //stores details of player if wins in sorted way
	FILE *fp;
	if (!(fp = fopen("fib_leaderboard.txt", "r+"))) { //this is true only for the first time the file gets created
		fp = fopen("fib_leaderboard.txt", "w");
	}
	else {
		int t_moves;
		char c, temp[100];
		while (true) {
			fseek(fp, 32, SEEK_CUR);
			t_moves = getANumberFromFile(fp);
			if (t_moves>moves) { //this is true when we reach a row that has greater moves value than currect moves
				fseek(fp, -36, SEEK_CUR);
				break;
			}
			fgets(temp, 100, fp);
			c = fgetc(fp);
			if (c == EOF)
				break;
			else fseek(fp, -1, SEEK_CUR);
		}
	}
	insertToFileFromThatPos(fp, name, moves, board, date);
}

void storeNumberInFile(FILE *fp, int m, int ten_pow, int n) {
	while (n--) {
		if (ten_pow) {
			fputc(((m / ten_pow) % 10) + 48, fp);
			ten_pow /= 10;
		}
		else fputc(' ', fp);
	}
}

void storeStringInFile(FILE *fp, int n, char str[]) {
	int k = 0;
	while (n--) {
		if (str[k] != '\0') {
			fputc(str[k++], fp);
		}
		else fputc(' ', fp);
	}
}

int no_of_digits(int n) {
	if (n<10)
		return 1;
	return 1 + no_of_digits(n / 10);
}

void insertToFileFromThatPos(FILE *fp, char name[], int moves, int board, char date[]) {
	FILE *t = fp;
	char arr[10000];	//this is used to store rest of file from fp pos
	char c = fgetc(fp);
	int n, k = 0;
	if (c == EOF)
		arr[0] = '\0';
	else while (c != EOF) {
		arr[k++] = c;
		c = fgetc(fp);
	}
	fseek(fp, -(k + 1), SEEK_CUR);
	storeStringInFile(fp, 21, name); 
	storeStringInFile(fp, 21, date);
	storeNumberInFile(fp, moves, pow(10, no_of_digits(moves) - 1), 4);
	storeNumberInFile(fp, board, pow(10, no_of_digits(board) - 1), 3);
	fputc('\n', fp);
	fputs(arr, fp);
	fclose(fp);
}

void saveStateToFile(char name[], int moves, int board, int **a) {
	moves--;
	FILE *fp = fopen("fib_state.txt", "w");
	int k = 0;
	while (name[k] != '\0') {
		fputc(name[k++], fp);
	}
	fputc(' ', fp);
	k = no_of_digits(moves);
	storeNumberInFile(fp, moves, pow(10, k - 1), k);
	fputc(' ', fp);
	k = no_of_digits(board);
	storeNumberInFile(fp, board, pow(10, k - 1), k);
	fputc(' ', fp);
	for (int i = 0; i<board; i++) {
		for (int j = 0; j<board; j++) {
			fputc(a[i][j] + 48, fp);
			fputc(' ', fp);
		}
	}
	fclose(fp);
}

int** getStateFromFile(char name[], int *moves, int *board) {
	FILE *fp;
	int **a = NULL;
	char c;
	if (!(fp = fopen("fib_state.txt", "r"))) {
		*moves = -1;
	}
	c = fgetc(fp);
	if (c == EOF)
		*moves = -1;
	else {
		int k = 0;
		while (c != ' ') {
			name[k++] = c;
			c = fgetc(fp);
		}
		name[k] = '\0';
		*moves = getANumberFromFile(fp);
		*board = getANumberFromFile(fp);
		int t = *board;
		a = (int **)calloc(t, sizeof(int*));
		for (int i = 0; i<t; i++) {
			a[i] = (int *)calloc(t, sizeof(int));
			for (int j = 0; j<t; j++) {
				c = fgetc(fp);
				a[i][j] = c - 48;
				c = fgetc(fp);
				printf("%c ",c);
			}
		}
	}
	return a;
}

int getANumberFromFile(FILE *fp) { //gets a number from fp position
	int n = 0;
	char c = fgetc(fp);
	while (c != ' ') {
		n = n * 10;
		n += (c - 48);
		c = fgetc(fp);
	}
	while (c == ' ') { //this loop is moving fp to a point after spaces..this is for other task in storeInFilefunction
		c = fgetc(fp);
	}
	fseek(fp, -1, SEEK_CUR);
	return n;
}