#include <stdio.h>
#include <math.h>

/*
 * find_root: pencarian akar rekursif dengan metode bisection.
 * Prasyarat: f(x_left) dan f(x_right) berbeda tanda, sehingga interval
 * pasti memuat akar dalam jumlah ganjil. f_left = f(x_left) dibawa
 * sebagai parameter agar tidak dihitung ulang.
 */
double find_root(double f(double x),
                 double x_left, double x_right,
                 double epsilon, double f_left)
{
    double x_mid = (x_left + x_right) / 2.0;
    double f_mid = f(x_mid);

    if (f_mid == 0.0)                        /* kasus (a): tepat di akar */
        return x_mid;
    if (x_right - x_left < epsilon)          /* kasus (b): interval cukup kecil */
        return x_mid;

    /* Kasus rekursif: pilih setengah interval yang masih memuat akar */
    if (f_left * f_mid < 0.0)
        return find_root(f, x_left, x_mid, epsilon, f_left);
    else
        return find_root(f, x_mid, x_right, epsilon, f_mid);
}

/*
 * bisect: while loop diganti satu panggilan find_root.
 * Mengembalikan akar lewat *root dan status lewat *error (1 = interval salah).
 */
void bisect(double f(double x),
            double x_left, double x_right, double epsilon,
            double *root, int *error)
{
    double f_left = f(x_left);
    double f_right = f(x_right);

    if (f_left * f_right > 0.0) {            /* tanda sama: tidak dijamin ada akar */
        *error = 1;
        *root = 0.0;
        return;
    }
    if (f_left == 0.0) {                     /* ujung kiri sudah akar */
        *error = 0;
        *root = x_left;
        return;
    }
    if (f_right == 0.0) {                    /* ujung kanan sudah akar */
        *error = 0;
        *root = x_right;
        return;
    }

    *error = 0;
    *root = find_root(f, x_left, x_right, epsilon, f_left);
}

/* Fungsi uji */
double f1(double x) { return x * x * x - x - 2.0; }   /* akar sekitar 1.5214 */
double f2(double x) { return cos(x) - x; }            /* akar sekitar 0.7391 */
double f3(double x) { return x * x - 4.0; }           /* akar 2 (di [0, 5]) */

int main(void)
{
    double root;
    int error;
    double eps = 1e-6;

    bisect(f1, 1.0, 2.0, eps, &root, &error);
    if (!error) printf("x^3 - x - 2 pada [1, 2]   : akar = %.6f\n", root);

    bisect(f2, 0.0, 1.0, eps, &root, &error);
    if (!error) printf("cos(x) - x pada [0, 1]    : akar = %.6f\n", root);

    bisect(f3, 0.0, 5.0, eps, &root, &error);
    if (!error) printf("x^2 - 4 pada [0, 5]       : akar = %.6f\n", root);

    bisect(f3, 3.0, 5.0, eps, &root, &error);  /* uji kasus error */
    if (error) printf("x^2 - 4 pada [3, 5]       : tanda sama, tidak dijamin ada akar\n");

    return 0;
}