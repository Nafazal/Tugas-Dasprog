#include <stdio.h>

void soal3() {
    double P, annualRate, i, payment, factor, power;
    double interest, princPart, balance, finalPayment;
    int n, k;

    printf("Jumlah pinjaman (principal): ");
    scanf("%lf", &P);
    printf("Suku bunga tahunan (%%): ");
    scanf("%lf", &annualRate);
    printf("Jumlah pembayaran (n): ");
    scanf("%d", &n);

    if (P <= 0 || n <= 0 || annualRate < 0) {
        printf("Input tidak valid.\n");
        return;
    }

    i = annualRate / 100.0 / 12.0;   /* bunga bulanan = 1/12 bunga tahunan */

    /* payment = iP / (1 - (1+i)^-n) */
    if (i == 0) {
        payment = P / n;
    } else {
        power = 1.0;                 /* power = (1+i)^n */
        for (k = 0; k < n; k++) {
            power *= (1.0 + i);
        }
        factor = 1.0 / power;        /* factor = (1+i)^-n */
        payment = (i * P) / (1.0 - factor);
    }
    payment = (long)(payment * 100 + 0.5) / 100.0;   /* bulatkan ke sen */

    printf("\nPrincipal      : $%.2f\n", P);
    printf("Annual interest: %.1f%%\n", annualRate);
    printf("Payment        : $%.2f\n", payment);
    printf("Term           : %d months\n\n", n);
    printf("%-8s %10s %12s %18s\n",
           "Payment", "Interest", "Principal", "Principal Balance");

    balance = P;
    finalPayment = payment;

    for (k = 1; k <= n; k++) {
        interest = (long)(balance * i * 100 + 0.5) / 100.0;

        if (k < n) {
            princPart = payment - interest;
            balance = (long)((balance - princPart) * 100 + 0.5) / 100.0;
        } else {
            /* pembayaran terakhir = bunga terakhir + sisa pokok */
            princPart = balance;
            balance = 0.0;
            finalPayment = interest + princPart;
        }

        printf("%-8d %10.2f %12.2f %18.2f\n",
               k, interest, princPart, balance);
    }

    printf("\nFinal payment: $%.2f\n", finalPayment);
}

void soal5() {
    int a, b, big, small, quotient, rem;

    printf("Masukkan dua bilangan bulat: ");
    scanf("%d %d", &a, &b);

    /* pakai nilai absolut */
    if (a < 0) a = -a;
    if (b < 0) b = -b;

    if (a == 0 && b == 0) {
        printf("GCD tidak terdefinisi untuk 0 dan 0.\n");
        return;
    }

    if (a >= b) { big = a; small = b; }
    else        { big = b; small = a; }

    while (small != 0) {
        quotient = big / small;
        rem = big % small;
        printf("%d / %d = %d sisa %d\n", big, small, quotient, rem);
        big = small;
        small = rem;
    }

    printf("GCD = %d\n", big);
}

void soal12() {
    /* batas panjang gelombang terpanjang tiap wilayah (meter) */
    double limit[6] = {3E-11, 3E-9, 4E-7, 7E-7, 1.4E-5, 1.0E-1};
    char region[7][12] = {"gamma ray", "X-ray", "ultraviolet",
                          "visible", "infrared", "microwave", "radio wave"};
    double wavelength;
    int i, found;

    while (1) {
        printf("Masukkan panjang gelombang (notasi ilmiah, 0 untuk berhenti): ");
        scanf("%lf", &wavelength);

        if (wavelength == 0) {
            break;   /* sentinel */
        }
        if (wavelength < 0) {
            printf("Panjang gelombang tidak boleh negatif.\n");
            continue;
        }

        found = 6;   /* default: radio wave */
        for (i = 0; i < 6; i++) {
            if (wavelength <= limit[i]) {
                found = i;
                break;
            }
        }

        printf("Panjang gelombang: %e m -> %s\n", wavelength, region[found]);
    }
}

int main() {
    int pilihan;
    prinf("Pilih soal (3/5/12):");
    scanf("%d", pilihan);

    if (pilihan == 3){
        soal3();
    }   else if (pilihan == 5){
        soal5();
    } else if (pilihan == 12){
        soal12();
    } else {
        pilihan == 3;
    }

    return 0;
}