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
        Birim* birim = malloc(sizeof(Birim));
        birim->birimAdi = strdup(birimAdi);
        birim->birimKodu = birimKodu;
        birim->birimCalisanlar = NULL;
        birim->calisanSayisi = 0;
        return birim;
}

//1.1
void birimCalisanlariDüzenle(Birim* birim, Calisan* calisan) {
        //Calisan** yeniCalisanlar = NULL;
        int calisanMevcutMu = 1;

        // Çalışanın zaten birimde olup olmadığını kontrol et
        for(size_t j = 0; j < birim->calisanSayisi; j++) {
                if (birim->birimCalisanlar != NULL) {
                        if (birim->birimCalisanlar[j]->calisanAdi == calisan->calisanAdi &&
                            birim->birimCalisanlar[j]->calisanSoyadi == calisan->calisanSoyadi) {
                                calisanMevcutMu = 0;  // Çalışan zaten mevcut
                                break;
                            }
                }
        }

        // Eğer çalışan birimde mevcut değilse, birime ekle
        if (calisanMevcutMu) {
                if (birim->birimCalisanlar == NULL) {
                        birim->birimCalisanlar = (Calisan**)malloc(sizeof(Calisan*));
                } else {
                        birim->birimCalisanlar = (Calisan**)realloc(birim->birimCalisanlar, (birim->calisanSayisi + 1) * sizeof(Calisan*));
                }
                birim->birimCalisanlar[birim->calisanSayisi] = calisan;
                birim->calisanSayisi++;
        }

}

//2.
Calisan* calisanOlustur(char* calisanAdi, char* calisanSoyadi, unsigned short int birimKodu, float maas, int girisYil) {
        Calisan* calisan = malloc(sizeof(Calisan));
        calisan->calisanAdi = strdup(calisanAdi);
        calisan->calisanSoyadi = strdup(calisanSoyadi);
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
                free(calisan->calisanAdi); // realoc'un başarısız olması durumunda calisani serbest bırakmak gerekmekte yoksa sızıntı meydana gelir.
                free(calisan->calisanSoyadi);
                free(calisan);
                calisanDiziBoyut--;
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
                        free(birim->birimAdi); // realloc başarısız olduğu durumda birimi serbest bırakmak gerekmekte yoksa sızıntı meydana gelir.
                        free(birim);
                        birimDiziBoyut--;
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
                printf("Calisanlarin Adi Soyadi: %s %s\nMaaşı: %f\n", birim->birimCalisanlar[i]->calisanAdi, birim->birimCalisanlar[i]->calisanSoyadi, birim->birimCalisanlar[i]->maas);
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
void minimumMaas(float maas, Calisan** calisanlar) {
        for (size_t i = 0; i < calisanDiziBoyut + 1; i++) { // Index hesabı nedeniyle +1
                if(calisanlar[i]->maas < maas && 2024-calisanlar[i]->girisYili > 10) {
                        calisanlar[i]->maas = maas;
                        printf("%s yeni maaşı: %.2f\n", calisanlar[i]->calisanAdi, calisanlar[i]->maas);
                }
        }
}

//11.
void dısaAktarBirim(Birim** birimler, const char* dosyaAdi) {
        FILE* dosya = fopen(dosyaAdi, "w");
        if (dosya == NULL) {
                printf("Dosya açılamadı!\n");
                return;
        }

        for (int i = 0; i < birimDiziBoyut + 1; i++) {
                Birim* birim = birimler[i];
                fprintf(dosya, "Birim Adı: %s\nBirim Kodu: %d\nBirim Çalışan Sayısı:%d\n\n", birim->birimAdi, birim->birimKodu, birim->calisanSayisi);

                for (int j = 0; j < birim->calisanSayisi; j++) {
                        Calisan* calisan = birim->birimCalisanlar[j];
                        fprintf(dosya, "Çalışan Adı: %s\nÇalışan Soyadı: %s\nÇalışsan Birim Kodu: %d\nÇalışan Maaşı: %.2f\nÇalışan Giriş Yılı: %d\n\n", calisan->calisanAdi, calisan->calisanSoyadi,
                                calisan->birimKodu, calisan->maas, calisan->girisYili);
                }
                fprintf(dosya, "----------------------------------------------------\n\n");
        }

        fclose(dosya);
        printf("Birim bilgileri başarıyla dosyaya yazıldı.\n");
}

//11.1
void dısaAktarCalisan(Calisan** calisanlar, const char* dosyaAdi) {
        FILE* dosya = fopen(dosyaAdi, "w");
        if (dosya == NULL) {
                printf("Dosya açılamadı!\n");
                return;
        }
        if (calisanlar == NULL) {
                printf("Çalışan dizisi NULL!\n");
                fclose(dosya); // Dosya açıldıysa kapat
                return;
        }
        for (int i = 0; i < calisanDiziBoyut + 1; i++) {
                fprintf(dosya, "Çalışan Adı: %s\nÇalışan Soyadı: %s\nÇalışsan Birim Kodu: %d\nÇalışan Maaşı: %.2f\nÇalışan Giriş Yılı: %d\n\n", calisanlar[i]->calisanAdi, calisanlar[i]->calisanSoyadi,
                        calisanlar[i]->birimKodu, calisanlar[i]->maas, calisanlar[i]->girisYili);
        }
        fprintf(dosya, "----------------------------------------------------\n\n");
        fclose(dosya);
        printf("Çalışan bilgileri başarıyla dosyaya yazıldı.\n");

}


//12.
void iceAktarBirim(const char* dosyaAdi, Birim*** birimler) { // Sıkıntı
        FILE* dosya = fopen(dosyaAdi, "r");
        if (dosya == NULL) {
                printf("Dosya açılamadı!\n");
                return;
        }
        char satir[256]; // Her satırı okuyacağımız tampon.
        while (fgets(satir, sizeof(satir), dosya)) {
                char birimAdi[100];
                unsigned short int birimKodu;
                int calisanSayisi;

                if (sscanf(satir, "%[^;];%hu;%d", birimAdi, &birimKodu, &calisanSayisi) == 3) {
                        Birim* yeniBirim = birimOlustur(birimAdi, birimKodu);
                        yeniBirim->calisanSayisi = calisanSayisi; // Çalışan sayısını ayarla
                        birimleriDiziyeEkle(birimler, yeniBirim);
                } else {
                        printf("Satır formatı hatalı: %s\n", satir);
                }
        }
        printf("Birimler içe aktarıldı");
        fclose(dosya); // Dosyayı kapat.

}

//12.1
void iceAktarCalisan(const char* dosyaAdi, Calisan*** calisanlar, Birim*** birimler) {

        FILE* dosya = fopen(dosyaAdi, "r");
        if (dosya == NULL) {
                printf("Dosya açılamadı!\n");
                return;
        }
        char satir[256]; // Her satırı okuyacağımız tampon.
        while (fgets(satir, sizeof(satir), dosya)) {
                char calisanAdi[50];
                char calisanSoyadi[50];
                unsigned short int birimKodu;
                float maas;
                int girisYili;

                if (sscanf(satir, "%[^;];%[^;];%hu;%f;%d", calisanAdi, calisanSoyadi, &birimKodu, &maas, &girisYili) == 5) {
                        Calisan* yeniCalisan = calisanOlustur(calisanAdi, calisanSoyadi, birimKodu, maas, girisYili);
                        calisanlarıDiziyeEkle(calisanlar, yeniCalisan);
                        for(size_t i = 0; i < birimDiziBoyut + 1; i++) {
                                if((*birimler)[i]->birimKodu == yeniCalisan->birimKodu) {
                                        birimCalisanlariDüzenle((*birimler)[i], yeniCalisan); // tek tek birime çalışan eklesek dizi vermek yerine?
                                }
                        }
                } else {
                        printf("Satır formatı hatalı: %s\n", satir);
                }
        }

        fclose(dosya); // Dosyayı kapat.

}

//13.
void tumVeriyiSerbestBirak(Birim** birimDizi, int birimSayisi) {
        if (birimDizi == NULL) return;

        for (int i = 0; i < birimSayisi + 1; i++) {
                if (birimDizi[i] != NULL) {
                        free(birimDizi[i]->birimAdi);

                        if (birimDizi[i]->birimCalisanlar != NULL) {
                                for(int j=0; j< birimDizi[i]->calisanSayisi; j++){
                                        if(birimDizi[i]->birimCalisanlar[j]!=NULL){
                                                free(birimDizi[i]->birimCalisanlar[j]->calisanAdi);
                                                birimDizi[i]->birimCalisanlar[j]->calisanAdi = NULL;
                                                free(birimDizi[i]->birimCalisanlar[j]->calisanSoyadi);
                                                birimDizi[i]->birimCalisanlar[j]->calisanSoyadi = NULL;
                                                free(birimDizi[i]->birimCalisanlar[j]);
                                                birimDizi[i]->birimCalisanlar[j]=NULL;
                                        }
                                }
                                free(birimDizi[i]->birimCalisanlar);
                                birimDizi[i]->birimCalisanlar=NULL;
                                birimDizi[i]->calisanSayisi=0;
                        }

                        free(birimDizi[i]);
                        birimDizi[i] = NULL;
                }
        }
        free(birimDizi);
}



