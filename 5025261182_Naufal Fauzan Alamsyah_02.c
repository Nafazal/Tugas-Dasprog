#include<stdio.h>

int main(){ 
    //soal nomor 2
    int massa_air;
    double tinggi,volume,gravity,efisiensi;
    gravity = 9.8;
    massa_air = 1000;
    efisiensi = 0.9;    
    scanf("%lf %lf",&tinggi,&volume);

    double massa = massa_air * volume;
    double usaha = massa * gravity * tinggi;
    double daya = usaha * efisiensi;
    double daya_megawatt = daya / 1000000;
    printf("Daya yang dihasilkan oleh bendungan adalah: %.2f MW\n",daya_megawatt);

    //soal nomor 5
    int durasi_menit;
    double volume_kantong;
    scanf("%lf %d",&volume_kantong,&durasi_menit);
    double VTBI = volume_kantong / durasi_menit;
    printf("Volume yang akan diinfuskan: %.2f mL/menit\n",VTBI);

    //soal nomor 8
    int ntoilet, populasi;
    int ratarata = 15;
    int modelhemat = 2;
    int penggunaanharian = 14;
    scanf("%d", &populasi);
    ntoilet = populasi/3;
    int hematair = ratarata - modelhemat;
    int hemat_air_perhari = ntoilet * hematair * penggunaanharian;
    int biaya = ntoilet * 150;
    printf("Estimasi hemat air perhari: %d liter\nbiaya penghematan: Rp %d", hemat_air_perhari, biaya);
    return 0;
}

