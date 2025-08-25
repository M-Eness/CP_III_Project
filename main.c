/*
 * @file main.c
 * @description Projede kullanılan fonksiyonların denendiği C dosyası.
 * @assignment 1. Ödev
 * @date 07.12.2024
 * @author Mehmet Enes Erden | mehmetenes.erden@stu.fsm.edu.tr
 */
#include <stdio.h>
#include <stdlib.h>

#include "proje1.h"

int main(int argc, char *argv[]) {

   if (argc < 3) {
        printf("Proje: %s\n", argv[0]);
        return 1;
    }

    char *birimDosyaAdi = argv[1];
    char *calisanDosyaAdi = argv[2];

    Calisan **calisanlar = NULL;
    Birim **birimler = NULL;
    iceAktarBirim(birimDosyaAdi, &birimler);
    iceAktarCalisan(calisanDosyaAdi, &calisanlar, &birimler);
    Birim* b1 = birimOlustur("Temizlik", 4);
    birimleriDiziyeEkle(&birimler, b1);
    Calisan* c1 = calisanOlustur("Mustafa", "Sağlam", 4, 45000, 2020);
    Calisan* c2 = calisanOlustur("Hande", "Dereli", 4, 30000, 2022);
    calisanlarıDiziyeEkle(&calisanlar, c1);
    calisanlarıDiziyeEkle(&calisanlar, c2);
    calisaniBirimeEkle(b1, c1);
    calisaniBirimeEkle(b1, c2);

    for (size_t i = 0; i < calisanDiziBoyut + 1; i++ ) {
        calisanYazdir(calisanlar[i]);
    }
    birimleriYazdir(birimler);

    for(size_t i = 0; i < birimDiziBoyut + 1; i++) {
        printf("%sinin ortalama maasi: %f\n",birimler[i]->birimAdi, birimOrtMaas(birimler[i]));
    }

    for(size_t i = 0; i < birimDiziBoyut + 1; i++) {
        yüksekMaasAlanlar(birimler[i]);
    }

    minimumMaas(99999, calisanlar);

    enZenginler(birimler);

    for(size_t i = 0; i < birimDiziBoyut + 1; i++) {
        printf("%s birminin ortalama maasi: %f\n",birimler[i]->birimAdi, birimOrtMaas(birimler[i]));
    }

    dısaAktarBirim(birimler, "BirimlerYeni.txt");
    dısaAktarCalisan(calisanlar, "CalisanlarYeni.txt");
    tumVeriyiSerbestBirak(birimler, birimDiziBoyut);
    return 0;
}
