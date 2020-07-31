#include "function_declarations.h"

int handleInputs(char name[], int moves, int n, int **a) {
	char c;
	printf("enter w - UP / s - DOWN / d - RIGHT / a - LEFT\n\t\t\t any key to exit \n\t\t\tgame is saved automatically Don't worry \n: ");
	scanf(" %c", &c);
	if (c == 'w')
		upMove(a, n);
	else if (c == 's')
		downMove(a, n);
	else if (c == 'd')
		rightMove(a, n);
	else if (c == 'a')
		leftMove(a, n);
	else return 1;
	return 0;
}

void removeZeroesOfColumnsForDownMove(int **a, int n) {
	int j = n - 1;
	for (int k = 0; k<n; k++) { //this gives a coloumn number in every iteration
		j = n - 1;
		for (int i = n - 1; i >= 0; i--) { //this is for row index
			if (a[i][j] != 0) {
				a[j][k] = a[i][k];
				j--;
			}
		}
		while (j >= 0) {
			a[j][k] = 0;
			j--;
		}
	}
}

void removeZeroesOfColumnsForUpMove(int **a, int n) {
	int j = 0;
	for (int k = 0; k<n; k++) { //this gives a coloumn number in every iteration
		j = 0;
		for (int i = 0; i<n; i++) { //this is for row index
			if (a[i][k] != 0) {
				a[j][k] = a[i][k];
				j++;
			}
		}
		while (j<n) {
			a[j][k] = 0;
			j++;
		}
	}
}

void removeZeroesOfaRowLeftMove(int **a, int n) {
	int j = 0;
	for (int k = 0; k<n; k++) {		//this gives a coloumn number in every iteration
		j = 0;
		for (int i = 0; i<n; i++) { //this is for row 
			if (a[k][i] != 0) {
				a[k][j] = a[k][i];
				j++;
			}
		}
		while (j<n) {
			a[k][j] = 0;
			j++;
		}
	}
}


void removeZeroesOfaRowRightMove(int **a, int n) {
	int j;
	for (int k = 0; k<n; k++) {		//this gives a coloumn number in every iteration
		j = n - 1;
		for (int i = n - 1; i >= 0; i--) { //this is for row 
			if (a[k][i] != 0) {
				a[k][j] = a[k][i];
				j--;
			}
		}
		while (j >= 0) {
			a[k][j] = 0;
			j--;
		}
	}
}

void downMove(int **a, int n) { // gets triggered when user choses DOWN move
	removeZeroesOfColumnsForDownMove(a, n);
	int k = n - 1, l = n - 2;
	while (l >= 0) {
		for (int i = 0; i < n; i++) {
			if (isMergeble(a[l][i], a[k][i])) {
				shiftdown(a, i, k, l, n);
			}
		}
		k--;
		l--;
	}
}

void shiftdown(int **a, int col, int k, int l, int n) { // shifts down the tiles by 1
	a[k][col] += a[l][col];
	for (int i = l; i > 0; i--) {
		a[i][col] = a[i-1][col];
	}
	a[0][col] = 0;
}

void upMove(int **a, int n) { // gets triggered when user choses UP move
	removeZeroesOfColumnsForUpMove(a, n);
	int k = 0, l = 1;
	while (l < n) {
		for (int i = 0; i < n; i++) {
			if (isMergeble(a[l][i], a[k][i])) {
				shiftUp(a, i, k, l, n);
			}
		}
		k++;
		l++;
	}
}

void shiftUp(int **a, int col, int k, int l, int n) { // shifts up the tiles by 1
	a[k][col] += a[l][col];
	for (int i = l; i < n - 1; i++) {
		a[i][col] = a[i+1][col];
	}
	a[n-1][col] = 0;
}

void leftMove(int **a, int n) {  // gets triggered when user choses LEFT move
	removeZeroesOfaRowLeftMove(a, n);
	int k = 0, l = 1;
	while (l < n) {
		for (int i = 0; i < n; i++) {
			if (isMergeble(a[i][l], a[i][k])) {
				shiftLeft(a, i, k, l, n);
			}
		}
		k++;
		l++;
	}
}

void shiftLeft(int **a, int row, int k, int l, int n) { // shifts left the tiles by 1
	a[row][k] += a[row][l];
	for (int i = l; i < n - 1; i++) {
		a[row][i] = a[row][i+1];
	}
	a[row][n-1] = 0;
}

void rightMove(int **a, int n) { // gets triggered when user choses RIGHT move
	removeZeroesOfaRowRightMove(a, n);
	int k = n - 1, l = n - 2;
	while (l >= 0) {
		for (int i = 0; i < n; i++) {
			if (isMergeble(a[i][l], a[i][k])) {
				shiftRight(a, i, k, l, n);
			}
		}
		k--;
		l--;
	}
}

void shiftRight(int **a, int row, int k, int l, int n) { // shifts right the tiles by 1
	a[row][k] += a[row][l];
	for (int i = l; i > 0; i--) {
		a[row][i] = a[row][i-1];
	}
	a[row][0] = 0;
}