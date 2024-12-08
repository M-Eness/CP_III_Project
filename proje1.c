//
// Created by Mehmet Enes on 7.12.2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Proje1.h";

static int calisanDiziBoyut = 0; // Tüm çalışanları tutacağım dizinin boyut kontrolü için oluşturuldu.
static int birimDiziBoyut = 0;

//1.
Birim birimOlustur(char* birimAdi, unsigned short int birimKodu, Calisan* birimCalisanlar) { // Tüm çalışanları bir diziden alıyorum diğer fonksiyonlarda birim kodu kontrolü yapıyorum.
        Birim birim;                                                     // Halbuki burada birim kodu kontrolü yapıp yeni bir dizi oluşturup birim çalışanlarını ayırmayı deneyebilirim.
        birim.birimAdi = birimAdi;
        birim.birimKodu = birimKodu;
        birim.birimCalisanlar = birimCalisanlar;
        return birim;
}

//2.
Calisan calisanOlustur(char* calisanAdi, char* calisanSoyadi, unsigned short int birimKodu, float maas, int girisYil) {
        Calisan calisan;
        calisan.calisanAdi = calisanAdi;
        calisan.calisanSoyadi = calisanSoyadi;
        calisan.birimKodu = birimKodu;
        calisan.maas = maas;
        calisan.girisYili = girisYil;
        return calisan;
}

//3.
void calisanlarıDiziyeEkle(Calisan** calisanlar, Calisan calisan) {
    if (*calisanlar == NULL) { // İlk kez ekleniyor
        *calisanlar = (Calisan*)malloc(sizeof(Calisan));
        if (*calisanlar == NULL) {
            printf("Bellek ayırma başarısız!\n");
            exit(1);
        }
        // İlk çalışanı ekleyin
        (*calisanlar)[0] = calisan;
        calisanDiziBoyut = 0; // İlk eklenen çalışan için
    } else {
        calisanDiziBoyut++; // Çalışan sayısını artır
        *calisanlar = (Calisan*)realloc(*calisanlar, (calisanDiziBoyut + 1) * sizeof(Calisan));
        if (*calisanlar == NULL) {
            printf("Bellek genişletme başarısız!\n");
            exit(1);
        }
        (*calisanlar)[calisanDiziBoyut] = calisan; // Yeni çalışanı ekle
    }
}

//3.1
void birimleriDiziyeEkle(Birim** birimler, Birim birim) {
        if(*birimler == NULL) {
                *birimler = (Birim*)malloc(sizeof(Birim)); // Calisanlar dizisi başlangıçta NULL olacağı için başlangıçta Calisan boyutunda bellkete yer ayrıldı.
                if(*birimler == NULL) {
                        printf("Bellek ayırma başarısız!\n");
                        exit(1);
                }
        }else {
                birimDiziBoyut++; // Birim sayısı arttırıldı.
                *birimler = (Birim*)realloc(*birimler, (birimDiziBoyut + 1) * sizeof(Birim)); // Index 0'dan başladığı için birimDiziBoyut + 1 ile realloc işlemi yapıldı.
        }
        (*birimler)[birimDiziBoyut] = birim;
}


//4.
void calisanYazdir(Calisan calisan) {
        printf("Calisan Adi: %s\n", calisan.calisanAdi);
        printf("Calisan Soyadi: %s\n", calisan.calisanSoyadi);
        printf("Calisan Birim Kodu: %d\n", calisan.birimKodu);
        printf("Calisan Maasi: %.2f\n", calisan.maas);
        printf("Calisan Giris Yili: %d\n", calisan.girisYili);
}

//5.
void birimYazdir(Birim birim) {
        printf("Birim Adi: %s\n", birim.birimAdi);
        printf("Birim Kodu: %d\n", birim.birimKodu);
        for (int i = 0; i < calisanDiziBoyut + 1; i++) { // Index hesaplaması nedeniyle +1.
                if(birim.birimCalisanlar[i].birimKodu == birim.birimKodu) { // Her birimin kendi çalışanlarını yazdır.
                        printf("Calisanlarin Adi Soyadi: %s %s\n", birim.birimCalisanlar[i].calisanAdi, birim.birimCalisanlar[i].calisanSoyadi);

                }
        }
}

//6.
void birimleriYazdir(Birim* birimler) {
        printf("BİRİMLER YAZIDIRILIYOR\n");
        for(size_t i = 0; i < birimDiziBoyut + 1; i++ ) { // Index hesaplaması nedeniyle +1.
                if(birimler[i].birimAdi != NULL) { // İlgili birimin içinin boş olup olmadığının kontrolü ????
                        birimYazdir(birimler[i]);
                        printf("////////////////////////\n");
                }
        }
}

//7.
float birimOrtMaas(Birim birim) {
        int calisanSayisi = 0;
        float toplamMaas = 0;
        float ortMaas = 0;
        for (int i = 0; i < calisanDiziBoyut + 1; i++){ // Index hesaplaması nedeniyle +1.
                if(birim.birimCalisanlar[i].birimKodu == birim.birimKodu) { // Her birimin kendi çalışanlarını yazdır.
                        toplamMaas += birim.birimCalisanlar[i].maas;
                        calisanSayisi++;
                }
        }
        ortMaas = toplamMaas / calisanSayisi;
        return ortMaas;
}

//8.
void yüksekMaasAlanlar(Birim birim) {
        float ortMaas = birimOrtMaas(birim);
        printf("Ortalmadan Yüksek Maas Alanlar Yazdiriliyor.\n");
        for (int i = 0; i < calisanDiziBoyut + 1; i++){ // Index hesaplaması nedeniyle +1.
                if(birim.birimCalisanlar[i].birimKodu == birim.birimKodu) { // Her birimin kendi çalışanlarını yazdır.
                        if(birim.birimCalisanlar[i].maas > ortMaas) {
                                printf("%s %s, %s biriminde ortalamadan yüksek maaş almaktadır.\n", birim.birimCalisanlar[i].calisanAdi,
                                                                                                    birim.birimCalisanlar[i].calisanSoyadi,
                                                                                                    birim.birimAdi);
                        }
                }
        }
}

//9.
void enZenginler(Birim* birimler) {
        float enYuksekMaas = 0;
        for(size_t i = 0; i < birimDiziBoyut + 1; i++ ) { // Index hesaplaması nedeniyle +1.
                if(birimler[i].birimAdi != NULL) { // İlgili birimin içinin boş olup olmadığının kontrolü ???? BU KONTROL GEREKLİ OLMAYABİLİR.
                        char enZenginAdSoyad[100] = "";
                        for (size_t j = 0; j < calisanDiziBoyut + 1; j++){ // Index hesaplaması nedeniyle +1.
                                if(birimler[i].birimCalisanlar[j].birimKodu == birimler[i].birimKodu) { // Her birimin kendi çalışanlarını al.
                                        if(birimler[i].birimCalisanlar[j].maas > enYuksekMaas) {
                                                strcpy(enZenginAdSoyad, "");
                                                enYuksekMaas = birimler[i].birimCalisanlar[j].maas;
                                                strcpy(enZenginAdSoyad, birimler[i].birimCalisanlar[j].calisanAdi);
                                                strcat(enZenginAdSoyad, " ");
                                                strcat(enZenginAdSoyad, birimler[i].birimCalisanlar[j].calisanSoyadi);
                                        }
                                }
                        }
                        printf("%s biriminin en yüksek maaş alan calisani: %s\n", birimler[i].birimAdi, enZenginAdSoyad);
                }
                enYuksekMaas = 0;
        }
}

//10.
void minimumMaas(float maas) {
        int calismaYili = 0;
        for (size_t i = 0; i < calisanDiziBoyut; i++) {
                // CALIŞANLARA NASIL ERİŞECEĞİM??
        }
}

//11.
void dısaAktar(Birim* birimler) {

}

//12.
void iceAktar(FILE* dosya) {

}



