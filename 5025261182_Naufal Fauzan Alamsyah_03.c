#include<stdio.h>

int main(){
    //soal nomor 5
    int pendapatan_jam, nilai_bayar;
    printf("Masukkan pendapatan per jam dan nilai bayar: ");
    scanf("%d %d",&pendapatan_jam, &nilai_bayar);
    double jamkerja = nilai_bayar / pendapatan_jam;
    printf("Waktu yang dibutuhkan untuk mencapai target: %.2f jam\n",jamkerja);

    //soal nomor 8
    double speed_awal = 200, speed_akhir = 150, waktu_menit = 1;
    double waktu_jam = waktu_menit / 60.0;
    double a = (speed_akhir - speed_awal) / waktu_jam;
    int speed_berhenti = 0;
    double waktu_berhenti_total = (speed_berhenti - speed_awal) / a;
    printf("Waktu yang dibutuhkan untuk berhenti total: %.2f jam\nPercepatan konstan kereta: %.2f mil/jam\n", a, waktu_berhenti_total);
    
    //soal nomor 13
    int tahun;
    printf("Masukkan tahun: ");
    scanf("%d",&tahun);
    if (tahun < 1990){
        printf("Tahun tidak valid");
    } else {
        int t = tahun - 1990;
        int populasi = 52966 + (t*2184);
        printf("Populasi pada tahun %d adalah: %d",tahun, populasi);
    }

    return 0;
}