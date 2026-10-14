#include <stdio.h>
#define TAHUN_DASAR 1990
#define MAKS_TAHUN  300     

double annual_revenue(int t)
{
    double faktor = 1.0;
    int i;

    for (i = 0; i < t; i++) {
        faktor = faktor * 1.063;
    }

    return 471.621 * faktor;
}

int predict_year(double target)
{
    int t = 0;

    while (annual_revenue(t) < target) {
        t++;
    }

    return TAHUN_DASAR + t;
}

void isi_tabel(double *tabel, int jumlah)
{
    int i;

    for (i = 0; i < jumlah; i++) {
        *(tabel + i) = annual_revenue(i);   /* sama dengan tabel[i] = ... */
    }
}

int main(void)
{
    double tabel[MAKS_TAHUN];   /* menyimpan pendapatan tiap tahun */
    double *p;                  /* pointer untuk menelusuri tabel */
    FILE *berkas;               /* pointer ke file output */
    int tahun_target;
    int jumlah;
    int i;

    tahun_target = predict_year(1000000.0);
    jumlah = tahun_target - TAHUN_DASAR + 1;   /* banyak baris tabel */

    if (jumlah > MAKS_TAHUN) {
        printf("Jumlah tahun melebihi ukuran array.\n");
        return 1;
    }

    isi_tabel(tabel, jumlah);   /* tabel = alamat elemen pertama array */

    berkas = fopen("revenue.txt", "w");
    if (berkas == NULL) {
        printf("Gagal membuat file revenue.txt\n");
        return 1;
    }

    fprintf(berkas, "Year   Revenue (thousands of dollars)\n");
    fprintf(berkas, "----   ------------------------------\n");

    p = tabel;                  /* p menunjuk elemen pertama */
    for (i = 0; i < jumlah; i++) {
        fprintf(berkas, "%d   %.3f\n", TAHUN_DASAR + i, *p);
        p++;                    /* pindah ke elemen berikutnya */
    }

    fclose(berkas);

    printf("Pendapatan diperkirakan melebihi $1 miliar pada tahun %d.\n", tahun_target);
    printf("Tabel disimpan di revenue.txt (%d baris).\n", jumlah);

    return 0;
}
