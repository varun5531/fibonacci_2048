#include "function_declarations.h"

bool isMergeble(int i, int j) {
	if (j == 0)
		return true;
	if (isFibonacci(i + j))
		return true;
	return false;
}

bool isFibonacci(int n) {
	return isPerfectSquare(5 * n * n + 4) || isPerfectSquare(5 * n * n - 4);
}

bool isPerfectSquare(int x) {
	int s = sqrt(x);
	return (s * s == x);
}