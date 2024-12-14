//
// Created by Mehmet Enes on 7.12.2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Proje1.h";

int calisanDiziBoyut = 0; // Tüm çalışanları tutacağım dizinin boyut kontrolü için oluşturuldu.
int birimDiziBoyut = 0;

//1.
Birim* birimOlustur(char* birimAdi, unsigned short int birimKodu) {
        Birim* birim = NULL;
        birim = malloc(sizeof(Birim));
        birim->birimAdi = birimAdi;
        birim->birimKodu = birimKodu;
        birim->birimCalisanlar = NULL;
        birim->calisanSayisi = 0;
        return birim;
}

//1.1
void birimCalisanlariDüzenle(Birim* birim, Calisan** birimCalisanlar) {
        Calisan** yeniCalisanlar = NULL;
        for(size_t i = 0; i < calisanDiziBoyut + 1; i++) { // Index hesaplaması nedeniyle +1.
                if ((*birimCalisanlar)[i].birimKodu == birim->birimKodu) {
                        if(yeniCalisanlar == NULL) {
                                yeniCalisanlar = (Calisan**)malloc(sizeof(Calisan*));
                                yeniCalisanlar[birim->calisanSayisi] = birimCalisanlar[i];
                        }else {
                                yeniCalisanlar = (Calisan**)realloc(yeniCalisanlar, (birim->calisanSayisi + 1) * sizeof(Calisan*));
                                yeniCalisanlar[birim->calisanSayisi] = birimCalisanlar[i];
                        }
                        birim->calisanSayisi++;
                }
        }
        birim->birimCalisanlar = yeniCalisanlar;


}

//2.
Calisan* calisanOlustur(char* calisanAdi, char* calisanSoyadi, unsigned short int birimKodu, float maas, int girisYil) {
        Calisan* calisan = NULL;
        calisan = malloc(sizeof(Calisan));
        calisan->calisanAdi = calisanAdi;
        calisan->calisanSoyadi = calisanSoyadi;
        calisan->birimKodu = birimKodu;
        calisan->maas = maas;
        calisan->girisYili = girisYil;
        return calisan;
}

//3.
void calisanlarıDiziyeEkle(Calisan*** calisanlar, Calisan* calisan) {
    if (*calisanlar == NULL) { // İlk kez ekleniyor
        *calisanlar = (Calisan**)malloc(sizeof(Calisan*));
        if (*calisanlar == NULL) {
            printf("Bellek ayırma başarısız!\n");
            exit(1);
        }
        (*calisanlar)[0] = calisan;
        calisanDiziBoyut = 0; // İlk eklenen çalışan için
    } else {
        calisanDiziBoyut++; // Çalışan sayısını artır
        *calisanlar = (Calisan**)realloc(*calisanlar, (calisanDiziBoyut + 1) * sizeof(Calisan*));
        if (**calisanlar == NULL) {
            printf("Bellek genişletme başarısız!\n");
            exit(1);
        }
        (*calisanlar)[calisanDiziBoyut] = calisan; // Yeni çalışanı ekle
    }
}

//3.1
void birimleriDiziyeEkle(Birim*** birimler, Birim* birim) {
        if (*birimler == NULL) { // İlk kez ekleniyor
                *birimler = (Birim**)malloc(sizeof(Birim*));
                if (*birimler == NULL) {
                        printf("Bellek ayırma başarısız!\n");
                        exit(1);
                }
                (*birimler)[0] = birim;
                birimDiziBoyut = 0; // İlk eklenen çalışan için
        } else {
                birimDiziBoyut++; // Birim sayısını artır
                *birimler = (Birim**)realloc(*birimler, (birimDiziBoyut + 1) * sizeof(Birim*));
                if (*birimler == NULL) {
                        printf("Bellek genişletme başarısız!\n");
                        exit(1);
                }
                (*birimler)[birimDiziBoyut] = birim; // Yeni birim ekle
        }
}
//4.
void calisanYazdir(Calisan* calisan) {
        printf("Calisan Adi: %s\n", calisan->calisanAdi);
        printf("Calisan Soyadi: %s\n", calisan->calisanSoyadi);
        printf("Calisan Birim Kodu: %d\n", calisan->birimKodu);
        printf("Calisan Maasi: %.2f\n", calisan->maas);
        printf("Calisan Giris Yili: %d\n", calisan->girisYili);
}

//5.
void birimYazdir(Birim* birim) {
        printf("Birim Adi: %s\n", birim->birimAdi);
        printf("Birim Kodu: %d\n", birim->birimKodu);
        for (int i = 0; i < birim->calisanSayisi; i++) {
                printf("Calisanlarin Adi Soyadi: %s %s\n Maaşı: %f\n", birim->birimCalisanlar[i]->calisanAdi, birim->birimCalisanlar[i]->calisanSoyadi, birim->birimCalisanlar[i]->maas);
        }
}

//6.
void birimleriYazdir(Birim** birimler) {
        printf("BİRİMLER YAZIDIRILIYOR\n");
        for(size_t i = 0; i < birimDiziBoyut + 1; i++ ) { // Index hesaplaması nedeniyle +1.
                birimYazdir(birimler[i]);
                printf("////////////////////////\n");
        }
}

//7.
float birimOrtMaas(Birim* birim) {
        int calisanSayisi = 0;
        float toplamMaas = 0;
        for (int i = 0; i < birim->calisanSayisi; i++){
                        toplamMaas += birim->birimCalisanlar[i]->maas;
                        calisanSayisi++;
        }
        float ortMaas = toplamMaas / calisanSayisi;
        return ortMaas;
}

//8.
void yüksekMaasAlanlar(Birim* birim) {
        float ortMaas = birimOrtMaas(birim);
        printf("Ortalmadan Yüksek Maas Alanlar Yazdiriliyor.\n");
        for (int i = 0; i < birim->calisanSayisi; i++){
                if(birim->birimCalisanlar[i]->maas > ortMaas) {
                        printf("%s %s, %s biriminde ortalamadan yüksek maaş almaktadır.\n", birim->birimCalisanlar[i]->calisanAdi, birim->birimCalisanlar[i]->calisanSoyadi,birim->birimAdi);
                }
        }
}

//9.
void enZenginler(Birim** birimler) {
        float enYuksekMaas = 0;
        for(size_t i = 0; i < birimDiziBoyut + 1; i++ ) { // Index hesaplaması nedeniyle +1.
                        char enZenginAdSoyad[100] = "";
                        for (size_t j = 0; j < birimler[i]->calisanSayisi; j++){
                                        if(birimler[i]->birimCalisanlar[j]->maas > enYuksekMaas) {
                                                strcpy(enZenginAdSoyad, "");
                                                enYuksekMaas = birimler[i]->birimCalisanlar[j]->maas;
                                                strcpy(enZenginAdSoyad, birimler[i]->birimCalisanlar[j]->calisanAdi);
                                                strcat(enZenginAdSoyad, " ");
                                                strcat(enZenginAdSoyad, birimler[i]->birimCalisanlar[j]->calisanSoyadi);
                                        }
                        }
                printf("%s biriminin en yüksek maaş alan calisani: %s\n", birimler[i]->birimAdi, enZenginAdSoyad);
                enYuksekMaas = 0;
        }
}

//10.
void minimumMaas(float maas, Calisan* calisanlar) {
        for (size_t i = 0; i < calisanDiziBoyut + 1; i++) { // Index hesabı nedeniyle +1
                if(calisanlar[i].maas < maas && 2024-calisanlar[i].girisYili > 10) {
                        calisanlar[i].maas = maas;
                        printf("%s yeni maaşı: %.2f\n", calisanlar[i].calisanAdi, calisanlar[i].maas);
                }
        }
}

//11.
void dısaAktarBirim(Birim* birimler) {

}

//11.1
void dısaAktarCalisan(Calisan* calisanlar) {

}


//12.
void iceAktarBirim(FILE* dosya) {

}

//12.1
void iceAktarCalisan(FILE* dosya) {

}

//13.
void birimleriSerbestBirak(Birim** birimler) {
        for (size_t i = 0; i < birimDiziBoyut; i++) {
                if (birimler[i] != NULL) {
                        free(birimler[i]->birimCalisanlar); // Çalışanlara malloc ile yer ayırdığım için free yapıyorum.
                        free(birimler[i]);
                        birimler[i] = NULL;
                }
        }
        free(birimler);
}

//13.1
void calisanlariSerbestBirak(Calisan** calisanlar) {
        for (size_t i = 0; i < calisanDiziBoyut; i++) {
                if (calisanlar[i] != NULL) {
                        free(calisanlar[i]);
                        calisanlar[i] = NULL;
                }
        }
        free(calisanlar);
}



