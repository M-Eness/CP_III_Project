//
// Created by Mehmet Enes on 7.12.2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Proje1.h";

int calisanDiziBoyut = 0; // Tüm çalışanları tutacağım dizinin boyut kontrolü için oluşturuldu.
int birimDiziBoyut = 0; // Tüm birimleri tutacağım dizinin boyut kontrolü için oluşturuldu.
#define MAX_NAME_LENGTH  30

//1.
Birim* birimOlustur(const char* birimAdi, unsigned short int birimKodu) {
    Birim* birim = malloc(sizeof(Birim));
    birim->birimAdi = strdup(birimAdi); // strdup ile bellekten yer ayırıyorum.
    birim->birimKodu = birimKodu;
    birim->birimCalisanlar = NULL;
    birim->calisanSayisi = 0;
    return birim;
}

//1.1
void calisaniBirimeEkle(Birim* birim, Calisan* calisan) {
    int calisanMevcutMu = 1;
    // Çalışanın zaten birimde olup olmadığını kontrol et.
    for (size_t j = 0; j < birim->calisanSayisi; j++) {
        if (birim->birimCalisanlar != NULL) {
            if (strcmp(birim->birimCalisanlar[j]->calisanAdi, calisan->calisanAdi) == 0 && // Ad soyad kontorolü
                strcmp(birim->birimCalisanlar[j]->calisanSoyadi, calisan->calisanSoyadi) == 0) {
                calisanMevcutMu = 0; // Çalışan zaten mevcut
                printf("%s %s, adlı çalışan zaten birimde bulunuyor!\n", calisan->calisanAdi, calisan->calisanSoyadi);
                break;
            }
        }
    }
    // Eğer çalışan birimde mevcut değilse ve birim kodu uyuşuyorsa birime ekle.
    if (calisanMevcutMu && birim->birimKodu == calisan->birimKodu) {
        if (birim->birimCalisanlar == NULL) {
            birim->birimCalisanlar = (Calisan**)malloc(sizeof(Calisan*));
        }
        else {
            birim->birimCalisanlar = (Calisan**)realloc(birim->birimCalisanlar,(birim->calisanSayisi + 1) * sizeof(Calisan*));
        }
        birim->birimCalisanlar[birim->calisanSayisi] = calisan;
        birim->calisanSayisi++;
    }else
        printf("Çalışan mevcut veya birim kodları uyuşmuyor kontrol edin!\n");
}

//2.
Calisan* calisanOlustur(const char* calisanAdi, const char* calisanSoyadi, unsigned short int birimKodu, float maas, int girisYil) {
    Calisan* calisan = malloc(sizeof(Calisan));
    calisan->calisanAdi = strdup(calisanAdi); // strdup ile bellekten yer ayırıyorum.
    calisan->calisanSoyadi = strdup(calisanSoyadi); // strdup ile bellekten yer ayırıyorum.
    calisan->birimKodu = birimKodu;
    calisan->maas = maas;
    calisan->girisYili = girisYil;
    return calisan;
}

//3.
void calisanlarıDiziyeEkle(Calisan*** calisanlar, Calisan* calisan) { // Parametre olarak Calianlar dizisinin adresini ve calisan* alınıyor.
    if (*calisanlar == NULL) { // İlk kez ekleniyor
        *calisanlar = (Calisan**)malloc(sizeof(Calisan*));
        if (*calisanlar == NULL) {
            printf("Bellek ayırma başarısız!\n");
            exit(1);
        }
        (*calisanlar)[0] = calisan;
        calisanDiziBoyut = 0; // İlk eklenen çalışan için
    }
    else {
        int calisanMevcutMu = 1;
        for (size_t i = 0; i < calisanDiziBoyut + 1; i++) {
            // Çalışan zaten dizide varsa tekrar ekleme.
            if (strcmp((*calisanlar)[i]->calisanAdi, calisan->calisanAdi) == 0 &&
                strcmp((*calisanlar)[i]->calisanSoyadi, calisan->calisanSoyadi) == 0) {
                calisanMevcutMu = 0; // Çalışan zaten mevcut
                printf("%s %s, adlı çalışan zaten dizide bulunuyor!\n", calisan->calisanAdi, calisan->calisanSoyadi);
                break;
            }
        }
        if (calisanMevcutMu) {
            calisanDiziBoyut++; // Çalışan sayısını artır
            *calisanlar = (Calisan**)realloc(*calisanlar, (calisanDiziBoyut + 1) * sizeof(Calisan*));
            if (**calisanlar == NULL) {
                printf("Bellek genişletme başarısız!\n");
                free(calisan->calisanAdi);
                // realoc'un başarısız olması durumunda calisani serbest bırakmak gerekmekte yoksa sızıntı meydana gelir.
                free(calisan->calisanSoyadi);
                free(calisan);
                calisanDiziBoyut--;
                exit(1);
            }
            (*calisanlar)[calisanDiziBoyut] = calisan; // Yeni çalışanı ekle
        }
    }
}

//3.1
void birimleriDiziyeEkle(Birim*** birimler, Birim* birim) { // Parametre olarak birimler dizisinin adresini ve birim* alınıyor.
    if (birim != NULL) { // Verilen birim null olmamalı.
        if (*birimler == NULL) { // İlk kez ekleniyor
            *birimler = (Birim**)malloc(sizeof(Birim*));
            if (*birimler == NULL) {
                printf("Bellek ayırma başarısız!\n");
                exit(1);
            }
            (*birimler)[0] = birim;
            birimDiziBoyut = 0; // İlk eklenen çalışan için
        }
        else {
            birimDiziBoyut++; // Birim sayısını artır
            *birimler = (Birim**)realloc(*birimler, (birimDiziBoyut + 1) * sizeof(Birim*));
            if (*birimler == NULL) {
                printf("Bellek genişletme başarısız!\n");
                free(birim->birimAdi);
                // realloc başarısız olduğu durumda birimi serbest bırakmak gerekmekte yoksa sızıntı meydana gelir.
                free(birim);
                birimDiziBoyut--;
                exit(1);
            }
            (*birimler)[birimDiziBoyut] = birim; // Yeni birim ekle
        }
    }else
    printf("Geçersiz birim girildi!\n");
}

//4.
void calisanYazdir(Calisan* calisan) { // Çalışan Bilgilerini Yazdır.
    printf("Calisan Adi: %s\n", calisan->calisanAdi);
    printf("Calisan Soyadi: %s\n", calisan->calisanSoyadi);
    printf("Calisan Birim Kodu: %d\n", calisan->birimKodu);
    printf("Calisan Maasi: %.2f\n", calisan->maas);
    printf("Calisan Giris Yili: %d\n", calisan->girisYili);
    printf("-------------------------------\n");
}

//5.
void birimYazdir(Birim* birim) { // Birim Bilgilerini Yazdır.
    printf("Birim Adi: %s\n", birim->birimAdi);
    printf("Birim Kodu: %d\n", birim->birimKodu);
    for (int i = 0; i < birim->calisanSayisi; i++) { // Birimdeki çalışanların bilgileri.
        printf("Calisanlarin Adi Soyadi: %s %s\nMaaşı: %f\n----------------------\n",
               birim->birimCalisanlar[i]->calisanAdi,
               birim->birimCalisanlar[i]->calisanSoyadi, birim->birimCalisanlar[i]->maas);
    }
}

//6.
void birimleriYazdir(Birim** birimler) { // Birimlerin bilgilerini yazdır.
    printf("BİRİMLER YAZIDIRILIYOR\n");
    for (size_t i = 0; i < birimDiziBoyut + 1; i++) { // Index hesaplaması nedeniyle +1.
        birimYazdir(birimler[i]);
    }
}

//7.
float birimOrtMaas(Birim* birim) { // Verilen birimin ortalama maaşını hesaplar.
    int calisanSayisi = 0;
    float toplamMaas = 0;
    for (int i = 0; i < birim->calisanSayisi; i++) {
        toplamMaas += birim->birimCalisanlar[i]->maas;
        calisanSayisi++;
    }
    float ortMaas = toplamMaas / calisanSayisi;
    return ortMaas;
}

//8.
void yüksekMaasAlanlar(Birim* birim) { // Verilen birimde ortalamadan yüksek maaş alanları yazdır.
    float ortMaas = birimOrtMaas(birim);
    for (int i = 0; i < birim->calisanSayisi; i++) {
        if (birim->birimCalisanlar[i]->maas > ortMaas) {
            printf("-> %s %s, %s biriminde ortalamadan yüksek maaş almaktadır.\n-----------------------------\n",
                   birim->birimCalisanlar[i]->calisanAdi,
                   birim->birimCalisanlar[i]->calisanSoyadi, birim->birimAdi);
        }
    }
}

//9.
void enZenginler(Birim** birimler) { // Her birimdeki en yüksek maaşı alan çalışanı yazdırır.
    float enYuksekMaas = 0;
    for (size_t i = 0; i < birimDiziBoyut + 1; i++) { // Index hesaplaması nedeniyle +1.
        char enZenginAdSoyad[100] = "";
        for (size_t j = 0; j < birimler[i]->calisanSayisi; j++) {
            if (birimler[i]->birimCalisanlar[j]->maas > enYuksekMaas) {
                strcpy(enZenginAdSoyad, "");
                enYuksekMaas = birimler[i]->birimCalisanlar[j]->maas;
                strcpy(enZenginAdSoyad, birimler[i]->birimCalisanlar[j]->calisanAdi);
                strcat(enZenginAdSoyad, " ");
                strcat(enZenginAdSoyad, birimler[i]->birimCalisanlar[j]->calisanSoyadi);
            }
        }
        printf("-> %s, biriminin en yüksek maaş alan calisani: %s\n\n", birimler[i]->birimAdi, enZenginAdSoyad);
        enYuksekMaas = 0;
    }
}

//10.
void minimumMaas(float maas, Calisan** calisanlar) {
    // 10 yıldan uzun süredir çalışan ve belirtilen maaşın altında maaş alanların maaşı güncellenir.
    for (size_t i = 0; i < calisanDiziBoyut + 1; i++) { // Index hesabı nedeniyle +1
        if (calisanlar[i]->maas < maas && 2024 - calisanlar[i]->girisYili > 10) {
            calisanlar[i]->maas = maas;
            printf("%s adlı çalışanın maaşı güncellendi yeni maaşı: %.2f\n--------------------------\n",
                   calisanlar[i]->calisanAdi, calisanlar[i]->maas);
        }
    }
}

//11.
void dısaAktarBirim(Birim** birimler, const char* dosyaAdi) { // Birim bilgilerini dosyaya yaz.
    FILE* dosya = fopen(dosyaAdi, "w");
    if (dosya == NULL) {
        printf("Dosya açılamadı!\n");
        return;
    }
    if (birimler == NULL) {
        printf("Çalışan dizisi NULL!\n");
        fclose(dosya); // Dosya açıldıysa kapat
        return;
    }
    for (int i = 0; i < birimDiziBoyut + 1; i++) { // Birim bilgilerini yaz.
        Birim* birim = birimler[i];
        fprintf(dosya, "Birim Adı: %s\nBirim Kodu: %d\nBirim Çalışan Sayısı:%d\n\n", birim->birimAdi, birim->birimKodu,
                birim->calisanSayisi);

        for (int j = 0; j < birim->calisanSayisi; j++) { // Birimin içindeki çalışan bilgilerini yaz.
            Calisan* calisan = birim->birimCalisanlar[j];
            fprintf(dosya,
                    "\t-> Çalışan Adı: %s\n\t-> Çalışan Soyadı: %s\n\t-> Çalışsan Birim Kodu: %d\n\t-> Çalışan Maaşı: %.2f\n\t-> Çalışan Giriş Yılı: %d\n\n",
                    calisan->calisanAdi, calisan->calisanSoyadi,
                    calisan->birimKodu, calisan->maas, calisan->girisYili);
        }
        fprintf(dosya, "----------------------------------------------------\n\n");
    }

    fclose(dosya);
    printf("Birim bilgileri başarıyla dosyaya yazıldı.\n");
}

//11.1
void dısaAktarCalisan(Calisan** calisanlar, const char* dosyaAdi) { // Çalışan bilgilerini dosyaya yaz.
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
        fprintf(dosya,
                "Çalışan Adı: %s\nÇalışan Soyadı: %s\nÇalışsan Birim Kodu: %d\nÇalışan Maaşı: %.2f\nÇalışan Giriş Yılı: %d\n\n",
                calisanlar[i]->calisanAdi, calisanlar[i]->calisanSoyadi,
                calisanlar[i]->birimKodu, calisanlar[i]->maas, calisanlar[i]->girisYili);
    }
    fprintf(dosya, "----------------------------------------------------\n\n");
    fclose(dosya);
    printf("Çalışan bilgileri başarıyla dosyaya yazıldı.\n");
}


//12.
void iceAktarBirim(const char* dosyaAdi, Birim*** birimler) { // Birim bilgilerini uygun formattaki dosyadan oku.
    FILE* dosya = fopen(dosyaAdi, "r");
    if (dosya == NULL) {
        printf("Dosya açılamadı!\n");
        return;
    }
    char satir[256]; // Her satırı okumak için tampon.
    while (fgets(satir, sizeof(satir), dosya)) {
        char* birimAdi = malloc(sizeof(char) * MAX_NAME_LENGTH);
        unsigned short int birimKodu;

        if (sscanf(satir, "%[^;];%hu", birimAdi, &birimKodu) == 2) { //BirimAdi;BirimKodu
            Birim* yeniBirim = birimOlustur(birimAdi, birimKodu);
            birimleriDiziyeEkle(birimler, yeniBirim);
        }
        else {
            printf("Satır formatı hatalı! (Boş satır eklenmiş olabilir.): %s\n", satir);
        }
        free(birimAdi);
        birimAdi = NULL;
    }

    printf("Birimler içe aktarıldı\n");
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
        char* calisanAdi = malloc(sizeof(char) * MAX_NAME_LENGTH);
        char* calisanSoyadi = malloc(sizeof(char) * MAX_NAME_LENGTH);
        unsigned short int birimKodu;
        float maas;
        int girisYili;

        if (sscanf(satir, "%[^;];%[^;];%hu;%f;%d", calisanAdi, calisanSoyadi, &birimKodu, &maas, &girisYili) == 5) { // Ad;Soyad;BirimKodu;Maas;GirisYili
            Calisan* yeniCalisan = calisanOlustur(calisanAdi, calisanSoyadi, birimKodu, maas, girisYili);
            calisanlarıDiziyeEkle(calisanlar, yeniCalisan);
            for (size_t i = 0; i < birimDiziBoyut + 1; i++) {
                if ((*birimler)[i]->birimKodu == yeniCalisan->birimKodu) { // Burada boşuna iterasyon yapmamak için kontrol yapıyorum.
                    calisaniBirimeEkle((*birimler)[i], yeniCalisan);
                    break;
                }
            }
        }
        else {
            printf("Satır formatı hatalı! (Boş satır eklenmiş olabilir.): %s\n", satir);
        }
        free(calisanAdi);
        free(calisanSoyadi);
        calisanAdi = NULL;
        calisanSoyadi = NULL;
    }
    printf("Çalışanlar içe aktarıldı\n");
    fclose(dosya); // Dosyayı kapat.
}

//13.
void tumVeriyiSerbestBirak(Birim** birimDizi, int birimSayisi) { // Dinamik olarak ayrılan bellek bölümlerini serbest bırakır.
    if (birimDizi == NULL)
        return;

    for (int i = 0; i < birimSayisi + 1; i++) {
        if (birimDizi[i] != NULL) {
            free(birimDizi[i]->birimAdi);

            if (birimDizi[i]->birimCalisanlar != NULL) {
                for (int j = 0; j < birimDizi[i]->calisanSayisi; j++) {
                    if (birimDizi[i]->birimCalisanlar[j] != NULL) {
                        free(birimDizi[i]->birimCalisanlar[j]->calisanAdi);
                        birimDizi[i]->birimCalisanlar[j]->calisanAdi = NULL;
                        free(birimDizi[i]->birimCalisanlar[j]->calisanSoyadi);
                        birimDizi[i]->birimCalisanlar[j]->calisanSoyadi = NULL;
                        free(birimDizi[i]->birimCalisanlar[j]);
                        birimDizi[i]->birimCalisanlar[j] = NULL;
                    }
                }
                free(birimDizi[i]->birimCalisanlar);
                birimDizi[i]->birimCalisanlar = NULL;
                birimDizi[i]->calisanSayisi = 0;
            }

            free(birimDizi[i]);
            birimDizi[i] = NULL;
        }
    }
    free(birimDizi);
}
