#include<stdio.h>
#include<string.h>
#define SIZE 5      /* grid SIZE x SIZE */
#define EMPTY 0
#define FILLED 1

/*
 * Mengembalikan jumlah sel dalam blob yang memuat sel (x, y).
 * grid[x][y]: x = kolom (0..SIZE-1), y = baris (0..SIZE-1, 4 di atas pada gambar).
 * Sel yang sudah dihitung ditandai kosong agar tidak dihitung dua kali,
 * sehingga isi grid BERUBAH setelah pemanggilan.
 */
int blob_check(int grid[SIZE][SIZE], int x, int y)
{
    int dx, dy;
    int count;

    /* Kasus sederhana 1: di luar grid */
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE)
        return 0;

    /* Kasus sederhana 2: sel kosong */
    if (grid[x][y] == EMPTY)
        return 0;

    /* Sel terisi: hitung 1, tandai kosong, lalu jumlahkan blob 8 tetangga */
    count = 1;
    grid[x][y] = EMPTY;

    for (dx = -1; dx <= 1; dx++)
        for (dy = -1; dy <= 1; dy++)
            if (dx != 0 || dy != 0)
                count += blob_check(grid, x + dx, y + dy);

    return count;
}

int main(void)
{
    /* Figure 9.27. Ditulis per baris dari y = 4 (atas) ke y = 0 (bawah),
       lalu dipindahkan ke grid[x][y]. */
    int picture[SIZE][SIZE] = {
        /* x:  0  1  2  3  4 */
        {1, 1, 0, 0, 0},   /* y = 4 */
        {0, 1, 1, 0, 0},   /* y = 3 */
        {0, 0, 1, 0, 1},   /* y = 2 */
        {1, 0, 0, 0, 1},   /* y = 1 */
        {0, 1, 0, 1, 1}    /* y = 0 */
    };
    int grid[SIZE][SIZE];
    int x, y, size, blobs = 0;

    for (y = 0; y < SIZE; y++)
        for (x = 0; x < SIZE; x++)
            grid[x][y] = picture[SIZE - 1 - y][x];

    /* Telusuri seluruh grid; tiap sel terisi yang ditemukan = blob baru */
    for (y = SIZE - 1; y >= 0; y--) {
        for (x = 0; x < SIZE; x++) {
            size = blob_check(grid, x, y);
            if (size > 0) {
                blobs++;
                printf("Blob %d (ditemukan di (%d, %d)): %d sel\n",
                       blobs, x, y, size);
            }
        }
    }
    printf("Total blob: %d\n", blobs);

    /* Uji kasus sederhana */
    printf("Di luar grid (7, 7): %d\n", blob_check(grid, 7, 7));
    printf("Sel kosong (2, 4)  : %d\n", blob_check(grid, 2, 4));

    return 0;
}