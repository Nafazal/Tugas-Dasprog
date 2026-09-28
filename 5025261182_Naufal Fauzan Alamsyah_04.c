#include<stdio.h>


int leap(int tahun) {
    if ((tahun % 4 == 0 && tahun % 100 != 0) || (tahun % 400 == 0)) {
        return 1;
    }
    return 0;
}

void tampilkanLangkah(char nama[], int menit) {
    printf("%s selama %d menit\n", nama, menit);
}

int hitungWaktuPanggang(int waktuDasar, char ukuranDouble) {
    if (ukuranDouble == 'Y') {
        return waktuDasar + waktuDasar / 2;
    }
    return waktuDasar;
}

int hitungNomorHari(int bulan, int tanggal, int tahun) {
    int hari = tanggal;

    if (bulan > 1)  hari = hari + 31;  // Januari
    if (bulan > 2)  hari = hari + 28;  // Februari
    if (bulan > 3)  hari = hari + 31;  // Maret
    if (bulan > 4)  hari = hari + 30;  // April
    if (bulan > 5)  hari = hari + 31;  // Mei
    if (bulan > 6)  hari = hari + 30;  // Juni
    if (bulan > 7)  hari = hari + 31;  // Juli
    if (bulan > 8)  hari = hari + 31;  // Agustus
    if (bulan > 9)  hari = hari + 30;  // September
    if (bulan > 10) hari = hari + 31;  // Oktober
    if (bulan > 11) hari = hari + 30;  // November

    if (bulan > 2 && leap(tahun) == 1) {
        hari = hari + 1;
    }

    return hari;
}

int main(){
    //soal nomor 2
    double wt_lb, ht_in;
    scanf("%lf %lf",&wt_lb, &ht_in);
    double BMI=703*wt_lb/(ht_in*ht_in);

    if (BMI<18.5){
        printf("Underweight");
    } else if (BMI>=18.5 && BMI<=24.9){
        printf("Normal weight");
    } else if (BMI>=25 && BMI<=29.9){
        printf("Overweight");
    } else {
        printf("Obesity");
    }   

    //soal nomor 7
    int bulan, tanggal, tahun;
    printf("Masukkan bulan tanggal tahun: ");
    scanf("%d %d %d", &bulan, &tanggal, &tahun);

    int nomorHari = hitungNomorHari(bulan, tanggal, tahun);
    printf("Nomor hari: %d\n", nomorHari);

    //soal nomor 10
    char jenisRoti, ukuranDouble, panggangManual;
    int waktuAduk, waktuMengembang, waktuBentuk, waktuPanggangDasar;

    printf("Jenis roti (W = White, S = Sweet): ");
    scanf(" %c", &jenisRoti);
    printf("Ukuran loaf double? (Y/T): ");
    scanf(" %c", &ukuranDouble);
    printf("Pemanggangan manual? (Y/T): ");
    scanf(" %c", &panggangManual);

    if (jenisRoti == 'W') {
        waktuAduk = 15;
        waktuMengembang = 60;
        waktuBentuk = 5;
        waktuPanggangDasar = 40;
    } else if (jenisRoti == 'S') {
        waktuAduk = 20;
        waktuMengembang = 70;
        waktuBentuk = 5;
        waktuPanggangDasar = 45;
    } else {
        printf("Jenis roti tidak valid\n");
        return 0;
    }

    tampilkanLangkah("Mengaduk adonan", waktuAduk);
    tampilkanLangkah("Mengembangkan adonan", waktuMengembang);
    tampilkanLangkah("Membentuk adonan", waktuBentuk);

    if (panggangManual == 'Y') {
        printf("Silakan keluarkan adonan untuk dipanggang manual\n");
        return 0;
    }

    int waktuPanggang = hitungWaktuPanggang(waktuPanggangDasar, ukuranDouble);
    tampilkanLangkah("Memanggang roti", waktuPanggang);

    return 0;
}