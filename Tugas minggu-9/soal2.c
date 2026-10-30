#include <stdio.h>
#include <string.h>

#define NUM_COLORS 10

/* Mengembalikan indeks target di dalam list, atau -1 jika tidak ada */
int search(const char list[][7], int n, const char *target)
{
    int i;
    for (i = 0; i < n; i++) {
        if (strcmp(list[i], target) == 0)
            return i;
    }
    return -1;
}

void print_table(void)
{
    printf("Color Codes for Resistors*\n");
    printf("Color   Value as Digit   Value as Multiplier\n");
    printf("Black   0                1\n");
    printf("Brown   1                10\n");
    printf("Red     2                10^2\n");
    printf("Orange  3                10^3\n");
    printf("Yellow  4                10^4\n");
    printf("Green   5                10^5\n");
    printf("Blue    6                10^6\n");
    printf("Violet  7                10^7\n");
    printf("Gray    8                10^8\n");
    printf("White   9                10^9\n");
    printf("*Adapted from Sears and Zemansky's University Physics, 10th ed.\n\n");
}

int main(void)
{
    char COLOR_CODES[NUM_COLORS][7] = {"black", "brown", "red", "orange",
                                       "yellow", "green", "blue", "violet",
                                       "gray", "white"};
    char band[3][20];
    char again[20];
    int idx[3];
    int i, valid;
    double ohm, kilo;

    do {
        printf("Enter the colors of the resistor's three bands, beginning with\n");
        printf("the band nearest the end. Type the colors in lowercase letters\n");
        printf("only, NO CAPS.\n\n");
        print_table();

        valid = 1;
        for (i = 0; i < 3 && valid; i++) {
            printf("Band %d => ", i + 1);
            scanf("%19s", band[i]);
            idx[i] = search(COLOR_CODES, NUM_COLORS, band[i]);
            if (idx[i] == -1) {
                printf("Invalid color: %s\n", band[i]);
                valid = 0;
            }
        }

        if (valid) {
            ohm = idx[0] * 10 + idx[1];
            for (i = 0; i < idx[2]; i++)   /* kalikan 10 sebanyak nilai band 3 */
                ohm *= 10;
            kilo = ohm / 1000.0;
            printf("Resistance value: %g kilo-ohms\n", kilo);
        }

        printf("Do you want to decode another resistor?\n=> ");
        scanf("%19s", again);
        printf("\n");
    } while (again[0] == 'y' || again[0] == 'Y');

    return 0;
}