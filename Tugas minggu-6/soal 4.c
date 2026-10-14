#include <stdio.h>

int get_problem(void)
{
    int pilihan = 0;

    printf("Select the form that you would like to convert to slope-intercept\n");
    printf("form:\n");
    printf("1) Two-point form (you know two points on the line)\n");
    printf("2) Point-slope form (you know the line's slope and one point)\n");
    printf("=> ");
    scanf("%d", &pilihan);   /* &pilihan = alamat variabel pilihan */

    return pilihan;
}


/* ------------------------------------------------------------
   get2_pt
   Fungsi: meminta koordinat dua titik, lalu mengirimkan keempat
           nilainya kembali ke pemanggil lewat pointer.
   Parameter (semuanya pointer / output parameter):
     x1, y1 -> tempat menyimpan koordinat titik pertama
     x2, y2 -> tempat menyimpan koordinat titik kedua
   ------------------------------------------------------------ */
void get2_pt(double *x1, double *y1, double *x2, double *y2)
{
    printf("Enter the x-y coordinates of the first point separated by a\n");
    printf("space=> ");
    /* x1 dan y1 sudah berupa alamat, jadi tidak perlu tanda & lagi */
    scanf("%lf %lf", x1, y1);

    printf("Enter the x-y coordinates of the second point separated by a\n");
    printf("space=> ");
    scanf("%lf %lf", x2, y2);
}


/* ------------------------------------------------------------
   get_pt_slope
   Fungsi: meminta kemiringan (slope) dan satu titik, lalu
           mengirimkan ketiga nilainya ke pemanggil lewat pointer.
   Parameter (output parameter):
     m      -> tempat menyimpan kemiringan
     x1, y1 -> tempat menyimpan koordinat titik
   ------------------------------------------------------------ */
void get_pt_slope(double *m, double *x1, double *y1)
{
    printf("Enter the slope=> ");
    scanf("%lf", m);

    printf("Enter the x-y coordinates of the point separated by a space=> ");
    scanf("%lf %lf", x1, y1);
}


/* ------------------------------------------------------------
   slope_intcpt_from2_pt
   Fungsi: menghitung kemiringan (m) dan titik potong sumbu y (b)
           dari dua titik.
   Parameter masukan (nilai biasa): x1, y1, x2, y2
   Parameter keluaran (pointer)   : m dan b
   Rumus: m = (y2 - y1) / (x2 - x1)
          b = y1 - m * x1
   Catatan: x1 dan x2 tidak boleh sama (garis vertikal); itu
            diperiksa di fungsi main sebelum fungsi ini dipanggil.
   ------------------------------------------------------------ */
void slope_intcpt_from2_pt(double x1, double y1, double x2, double y2,
                           double *m, double *b)
{
    *m = (y2 - y1) / (x2 - x1);   /* isi variabel yang ditunjuk m */
    *b = y1 - (*m) * x1;          /* (*m) = nilai kemiringan yang baru dihitung */
}


/* ------------------------------------------------------------
   intcpt_from_pt_slope
   Fungsi: menghitung titik potong sumbu y (b) dari satu titik
           dan kemiringan.
   Parameter masukan: x1, y1 (titik) dan m (kemiringan)
   Nilai kembali    : nilai b
   Rumus: b = y1 - m * x1
   ------------------------------------------------------------ */
double intcpt_from_pt_slope(double x1, double y1, double m)
{
    double b;

    b = y1 - m * x1;
    return b;
}


/* ------------------------------------------------------------
   display2_pt
   Fungsi: menampilkan persamaan bentuk dua titik (two-point form).
   Parameter masukan: x1, y1, x2, y2
   ------------------------------------------------------------ */
void display2_pt(double x1, double y1, double x2, double y2)
{
    printf("Two-point form\n");
    printf("      (%.2f - %.2f)\n", y2, y1);
    printf("m = --------------\n");
    printf("      (%.2f - %.2f)\n", x2, x1);
}


/* ------------------------------------------------------------
   display_pt_slope
   Fungsi: menampilkan persamaan bentuk titik-kemiringan
           (point-slope form): y - y1 = m(x - x1)
   Parameter masukan: x1, y1 (titik) dan m (kemiringan)
   Jika y1 atau x1 negatif, tanda "-" diganti "+" agar tidak
   tertulis "- -2.00".
   ------------------------------------------------------------ */
void display_pt_slope(double x1, double y1, double m)
{
    printf("Point-slope form\n");

    printf("y ");
    if (y1 >= 0)
        printf("- %.2f", y1);
    else
        printf("+ %.2f", -y1);

    printf(" = %.2f(x ", m);
    if (x1 >= 0)
        printf("- %.2f", x1);
    else
        printf("+ %.2f", -x1);
    printf(")\n");
}


/* ------------------------------------------------------------
   display_slope_intcpt
   Fungsi: menampilkan persamaan bentuk kemiringan-potong
           (slope-intercept form): y = mx + b
   Parameter masukan: m (kemiringan) dan b (titik potong sumbu y)
   ------------------------------------------------------------ */
void display_slope_intcpt(double m, double b)
{
    printf("Slope-intercept form\n");
    printf("y = %.2fx ", m);
    if (b >= 0)
        printf("+ %.2f\n", b);
    else
        printf("- %.2f\n", -b);
}


/* ------------------------------------------------------------
   main
   Mengatur jalannya program: menampilkan menu, memanggil fungsi
   yang sesuai, lalu menanyakan apakah ingin konversi lagi.
   ------------------------------------------------------------ */
int main(void)
{
    int pilihan;
    double x1 = 0, y1 = 0, x2 = 0, y2 = 0;   /* koordinat titik */
    double m = 0, b = 0;                      /* kemiringan dan titik potong */
    char ulang = 'N';

    do {
        pilihan = get_problem();

        if (pilihan == 1) {
            /* &x1 dst. = mengirim ALAMAT variabel agar bisa diisi oleh fungsi */
            get2_pt(&x1, &y1, &x2, &y2);
            display2_pt(x1, y1, x2, y2);

            if (x1 == x2) {
                printf("Garis vertikal (x1 = x2), tidak punya bentuk slope-intercept.\n");
            } else {
                slope_intcpt_from2_pt(x1, y1, x2, y2, &m, &b);
                display_slope_intcpt(m, b);
            }
        } else if (pilihan == 2) {
            get_pt_slope(&m, &x1, &y1);
            display_pt_slope(x1, y1, m);

            b = intcpt_from_pt_slope(x1, y1, m);
            display_slope_intcpt(m, b);
        } else {
            printf("Pilihan tidak valid, masukkan 1 atau 2.\n");
        }

        printf("Do another conversion (Y or N)=> ");
        scanf(" %c", &ulang);   /* spasi sebelum %c melewati karakter enter */
    } while (ulang == 'Y' || ulang == 'y');

    return 0;
}
