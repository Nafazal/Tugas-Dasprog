#include <stdio.h>

/* ---------- Bagian 1: subset rekursif ---------- */

/* Semua subset 1 elemen */
void one_ele_subs(const char *set)
{
    if (*set == '\0')               /* kasus dasar: himpunan habis */
        return;
    printf("{%c}\n", *set);
    one_ele_subs(set + 1);
}

/* Pasangkan huruf a dengan setiap huruf di rest */
void pair_with(char a, const char *rest)
{
    if (*rest == '\0')
        return;
    printf("{%c, %c}\n", a, *rest);
    pair_with(a, rest + 1);
}

/* Semua subset 2 elemen */
void two_ele_subs(const char *set)
{
    if (*set == '\0')
        return;
    pair_with(set[0], set + 1);     /* subset yang memuat huruf pertama */
    two_ele_subs(set + 1);          /* subset tanpa huruf pertama */
}

/* Lengkapi pasangan (a, b) dengan setiap huruf di rest */
void triple_with(char a, char b, const char *rest)
{
    if (*rest == '\0')
        return;
    printf("{%c, %c, %c}\n", a, b, *rest);
    triple_with(a, b, rest + 1);
}

/* Pilih huruf kedua dari rest, lalu lengkapi huruf ketiga */
void pairs_then_third(char a, const char *rest)
{
    if (*rest == '\0')
        return;
    triple_with(a, rest[0], rest + 1);
    pairs_then_third(a, rest + 1);
}

/* Semua subset 3 elemen */
void three_ele_subs(const char *set)
{
    if (*set == '\0')
        return;
    pairs_then_third(set[0], set + 1);  /* subset yang memuat huruf pertama */
    three_ele_subs(set + 1);            /* subset tanpa huruf pertama */
}

/* ---------- Bagian 2: binary search rekursif ---------- */

/*
 * Mencari target di arr[lo..hi] (arr terurut naik).
 * Mengembalikan indeks target, atau -1 jika tidak ada.
 */
int binary_srch(const int arr[], int lo, int hi, int target)
{
    int mid;

    if (lo > hi)                    /* kasus dasar 1: rentang kosong */
        return -1;

    mid = lo + (hi - lo) / 2;       /* hindari overflow (lo + hi) */

    if (arr[mid] == target)         /* kasus dasar 2: ketemu */
        return mid;
    if (target < arr[mid])
        return binary_srch(arr, lo, mid - 1, target);
    return binary_srch(arr, mid + 1, hi, target);
}

int main(void)
{
    const char *set = "ACEG";
    int data[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int n = sizeof(data) / sizeof(data[0]);
    int tests[] = {23, 2, 91, 7, 100, -4};
    int i, idx;

    printf("Subset 1 elemen dari \"%s\":\n", set);
    one_ele_subs(set);
    printf("\nSubset 2 elemen:\n");
    two_ele_subs(set);
    printf("\nSubset 3 elemen:\n");
    three_ele_subs(set);

    printf("\nBinary search pada array terurut:\n");
    for (i = 0; i < (int)(sizeof(tests) / sizeof(tests[0])); i++) {
        idx = binary_srch(data, 0, n - 1, tests[i]);
        if (idx >= 0)
            printf("%4d ditemukan di indeks %d\n", tests[i], idx);
        else
            printf("%4d tidak ditemukan\n", tests[i]);
    }
    return 0;
}