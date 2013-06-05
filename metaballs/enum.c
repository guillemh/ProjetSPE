#include <stdio.h>

//   0 -- 0
//  /|   /|
// 0 -- 0 |
// | 0  | 0
// |/   |/
// 0 -- 0
//
int main () {
    for (int s = 0 ; s < 256 ; s++) {
	printf("Cube %i : \n", s);
	printf("\n");
	printf("  %i -- %i\n", (s >> 3) & 1, (s >> 2) & 1);
	printf(" /|   /|\n");
	printf("%i -- %i |\n", s & 1, (s >> 1) & 1);
	printf("| %i  | %i\n", (s >> 7) & 1, (s >> 6) & 1);
	printf("|/   |/\n");
	printf("%i -- %i\n", (s >> 4) & 1, (s >> 5) & 1);
	printf("\n");
    }
}
