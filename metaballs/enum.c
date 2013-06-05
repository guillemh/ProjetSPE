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
        printf("Cube %i :\n", s);
        printf("\n");
        printf("          ^\n");
        printf("          |\n");
        printf("         (%i)------4-------(%i)\n", (s >> 3) & 1, (s >> 2) & 1);
        printf("         /|              / |\n");
        printf("        / |             /  |\n");
        printf("       7  8            5   9\n");
        printf("      /   |           /    |\n");
        printf("     /    |          /     |\n");
        printf("    (%i)------6------(%i)    |\n", s & 1, (s >> 1) & 1);
        printf("    |    (%i)------0--|----(%i)----> y\n", (s >> 7) & 1, (s >> 6) & 1);
        printf("    |    /           |    /\n");
        printf("   11   /           10   /\n");
        printf("    |  3             |  1\n");
        printf("    | /              | /\n");
        printf("    |/               |/\n");
        printf("    (%i)------2------(%i)\n", (s >> 4) & 1, (s >> 5) & 1);
        printf("   /\n");
        printf("   v\n");
    }
}
