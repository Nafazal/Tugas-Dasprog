#include <stdio.h>

/* ============================================================
   RUMUS KONDUKSI PANAS:   H = k * A * (T2 - T1) / X

   H  = laju perpindahan panas (watt)
   k  = koefisien konduktivitas termal (W/m-K)
   A  = luas penampang (m^2)
   T2 = suhu di satu sisi (K)
   T1 = suhu di sisi lain (K)
   X  = tebal penghantar (m)

   CATATAN POINTER
   - Tanda & mengambil ALAMAT sebuah variabel.
   - Tanda * pada pointer mengambil/mengubah ISI variabel yang ditunjuk.
   - Fungsi calc_... di bawah mengirim hasil hitungannya lewat pointer
     (parameter "hasil"), dan mengembalikan angka 1 jika berhasil
     atau 0 jika terjadi pembagian dengan nol.
   ============================================================ */

/* Nomor urut (indeks) tiap besaran di dalam array */
#define IDX_H   0
#define IDX_K   1
#define IDX_A   2
#define IDX_T2  3
#define IDX_T1  4
#define IDX_X   5
#define JUMLAH  6


/* ------------------------------------------------------------
   calc_h : menghitung laju perpindahan panas H
   Rumus  : H = k * A * (T2 - T1) / X
   ------------------------------------------------------------ */
int calc_h(double k, double a, double t2, double t1, double x, double *hasil)
{
    if (x == 0)
        return 0;                       /* tidak boleh dibagi nol */
    *hasil = k * a * (t2 - t1) / x;     /* simpan ke variabel yang ditunjuk */
    return 1;
}

/* ------------------------------------------------------------
   calc_k : menghitung koefisien konduktivitas termal k
   Rumus  : k = H * X / (A * (T2 - T1))
   ------------------------------------------------------------ */
int calc_k(double h, double a, double t2, double t1, double x, double *hasil)
{
    if (a * (t2 - t1) == 0)
        return 0;
    *hasil = h * x / (a * (t2 - t1));
    return 1;
}

/* ------------------------------------------------------------
   calc_a : menghitung luas penampang A
   Rumus  : A = H * X / (k * (T2 - T1))
   ------------------------------------------------------------ */
int calc_a(double h, double k, double t2, double t1, double x, double *hasil)
{
    if (k * (t2 - t1) == 0)
        return 0;
    *hasil = h * x / (k * (t2 - t1));
    return 1;
}

/* ------------------------------------------------------------
   calc_t2 : menghitung suhu T2
   Rumus   : T2 = T1 + H * X / (k * A)
   ------------------------------------------------------------ */
int calc_t2(double h, double k, double a, double t1, double x, double *hasil)
{
    if (k * a == 0)
        return 0;
    *hasil = t1 + h * x / (k * a);
    return 1;
}

/* ------------------------------------------------------------
   calc_t1 : menghitung suhu T1
   Rumus   : T1 = T2 - H * X / (k * A)
   ------------------------------------------------------------ */
int calc_t1(double h, double k, double a, double t2, double x, double *hasil)
{
    if (k * a == 0)
        return 0;
    *hasil = t2 - h * x / (k * a);
    return 1;
}

/* ------------------------------------------------------------
   calc_x : menghitung tebal penghantar X
   Rumus  : X = k * A * (T2 - T1) / H
   ------------------------------------------------------------ */
int calc_x(double h, double k, double a, double t2, double t1, double *hasil)
{
    if (h == 0)
        return 0;
    *hasil = k * a * (t2 - t1) / h;
    return 1;
}


/* ------------------------------------------------------------
   baca_nilai
   Fungsi: menampilkan pertanyaan lalu membaca satu nilai.
           Jika pengguna mengetik tanda tanya (?), berarti besaran
           itu yang tidak diketahui.
   Parameter:
     pertanyaan       -> teks pertanyaan yang ditampilkan
     nilai            -> pointer: tempat menyimpan angka yang dibaca
     tidak_diketahui  -> pointer: diisi 1 jika pengguna mengetik '?',
                         diisi 0 jika pengguna mengetik angka
   Petunjuk: saat yang diketik '?', scanf("%lf") mengembalikan 0
   (gagal membaca angka). Karena itu '?' harus dibaca lagi sebagai
   karakter memakai scanf(" %c").
   ------------------------------------------------------------ */
void baca_nilai(const char *pertanyaan, double *nilai, int *tidak_diketahui)
{
    int hasil_scanf;
    char karakter = ' ';
    int selesai = 0;

    while (selesai == 0) {
        printf("%s >> ", pertanyaan);
        hasil_scanf = scanf("%lf", nilai);

        if (hasil_scanf == 1) {
            *tidak_diketahui = 0;       /* berhasil membaca angka */
            selesai = 1;
        } else if (hasil_scanf == EOF) {
            *tidak_diketahui = 1;       /* input habis, hentikan loop */
            selesai = 1;
        } else {
            scanf(" %c", &karakter);    /* baca karakter yang bukan angka */
            if (karakter == '?') {
                *tidak_diketahui = 1;
                selesai = 1;
            } else {
                printf("Input salah, ketik angka atau tanda tanya (?).\n");
            }
        }
    }
}


/* ------------------------------------------------------------
   main : fungsi utama (driver)
   ------------------------------------------------------------ */
int main(void)
{
    /* Tiap array berisi 6 besaran: H, k, A, T2, T1, X (urutan sama dengan IDX_...) */
    double nilai[JUMLAH];          /* nilai tiap besaran */
    int tidak_diketahui[JUMLAH];   /* 1 jika besaran itu bertanda '?' */

    const char *pertanyaan[JUMLAH] = {
        "Rate of heat transfer (watts)",
        "Coefficient of thermal conductivity (W/m-K)",
        "Cross-sectional area of conductor (m^2)",
        "Temperature on one side (K)",
        "Temperature on other side (K)",
        "Thickness of conductor (m)"
    };
    const char *nama[JUMLAH] = {
        "Rate of heat transfer",
        "Coefficient of thermal conductivity",
        "Cross-sectional area",
        "Temperature on one side",
        "Temperature on the other side",
        "Thickness of conductor"
    };
    const char *satuan[JUMLAH] = {"W", "W/m-K", "m^2", "K", "K", "m"};

    int i;
    int jumlah_tanya = 0;   /* berapa banyak besaran yang bertanda '?' */
    int yang_dicari = -1;   /* indeks besaran yang dicari */
    int berhasil = 0;
    double hasil = 0;

    printf("Respond to the prompts with the data known. For the\n");
    printf("unknown quantity, enter a question mark (?).\n");

    /* Baca keenam besaran. &nilai[i] = alamat elemen ke-i dari array nilai */
    for (i = 0; i < JUMLAH; i++) {
        baca_nilai(pertanyaan[i], &nilai[i], &tidak_diketahui[i]);
        if (tidak_diketahui[i] == 1) {
            jumlah_tanya++;
            yang_dicari = i;
        }
    }

    /* Harus tepat satu besaran yang dicari */
    if (jumlah_tanya != 1) {
        printf("Harus ada tepat satu besaran yang tidak diketahui (?).\n");
        return 1;
    }

    /* Pilih fungsi sesuai besaran yang dicari */
    if (yang_dicari == IDX_H)
        berhasil = calc_h(nilai[IDX_K], nilai[IDX_A], nilai[IDX_T2],
                          nilai[IDX_T1], nilai[IDX_X], &hasil);
    else if (yang_dicari == IDX_K)
        berhasil = calc_k(nilai[IDX_H], nilai[IDX_A], nilai[IDX_T2],
                          nilai[IDX_T1], nilai[IDX_X], &hasil);
    else if (yang_dicari == IDX_A)
        berhasil = calc_a(nilai[IDX_H], nilai[IDX_K], nilai[IDX_T2],
                          nilai[IDX_T1], nilai[IDX_X], &hasil);
    else if (yang_dicari == IDX_T2)
        berhasil = calc_t2(nilai[IDX_H], nilai[IDX_K], nilai[IDX_A],
                           nilai[IDX_T1], nilai[IDX_X], &hasil);
    else if (yang_dicari == IDX_T1)
        berhasil = calc_t1(nilai[IDX_H], nilai[IDX_K], nilai[IDX_A],
                           nilai[IDX_T2], nilai[IDX_X], &hasil);
    else
        berhasil = calc_x(nilai[IDX_H], nilai[IDX_K], nilai[IDX_A],
                          nilai[IDX_T2], nilai[IDX_T1], &hasil);

    if (berhasil == 0) {
        printf("Tidak dapat dihitung: terjadi pembagian dengan nol.\n");
        return 1;
    }

    nilai[yang_dicari] = hasil;   /* masukkan hasil ke besaran yang dicari */

    /* Tampilkan rumus dan hasilnya */
    printf("\n      kA (T2 - T1)\n");
    printf(" H = ---------------\n");
    printf("            X\n\n");
    printf("%s is %.3f %s.\n\n", nama[yang_dicari], nilai[yang_dicari],
           satuan[yang_dicari]);

    printf("H = %.1f W        T2 = %.1f K\n", nilai[IDX_H], nilai[IDX_T2]);
    printf("k = %.3f W/m-K    T1 = %.1f K\n", nilai[IDX_K], nilai[IDX_T1]);
    printf("A = %.3f m^2      X  = %.3f m\n", nilai[IDX_A], nilai[IDX_X]);

    return 0;
}
