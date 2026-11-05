#include<stdio.h>
#include<string.h>

#define N 6
#define NAME_LEN 30

/* Mencetak daftar nama dan umur */
void print_list(char names[][NAME_LEN], int ages[], int n)
{
    int i;
    printf("-----------------------------\n");
    for (i = 0; i < n; i++)
        printf("%-25s %d\n", names[i], ages[i]);
    printf("\n");
}

/* Selection sort pada nama; umur ikut ditukar agar tetap berpasangan */
void sort_lists(char names[][NAME_LEN], int ages[], int n)
{
    int i, j, min_idx, temp_age;
    char temp_name[NAME_LEN];

    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (strcmp(names[j], names[min_idx]) < 0)
                min_idx = j;
        }
        if (min_idx != i) {
            strcpy(temp_name, names[i]);
            strcpy(names[i], names[min_idx]);
            strcpy(names[min_idx], temp_name);

            temp_age = ages[i];
            ages[i] = ages[min_idx];
            ages[min_idx] = temp_age;
        }
    }
}

int main(void)
{
    char names[N][NAME_LEN] = {
        "Ryan, Elizabeth",
        "McIntyre, Osborne",
        "DuMond, Kristin",
        "Larson, Lois",
        "Thorpe, Trinity",
        "Ruiz, Pedro"
    };
    int ages[N] = {62, 84, 18, 42, 15, 35};

    printf("Original list\n");
    print_list(names, ages, N);

    sort_lists(names, ages, N);

    printf("Alphabetized list\n");
    print_list(names, ages, N);

    return 0;
}