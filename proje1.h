//
// Created by Mehmet Enes on 7.12.2024.
//
#ifndef PROJE1_H
#define PROJE1_H
#include <stdio.h>

int calisanDiziBoyut; // Tüm çalışanları sayısı tutuluyor.
int birimDiziBoyut;

typedef struct {
    char *calisanAdi;
    char *calisanSoyadi;
    unsigned short int birimKodu;
    float maas;
    int girisYili;
} Calisan;

typedef struct {
    char *birimAdi;
    unsigned short int birimKodu;
    Calisan** birimCalisanlar;
    int calisanSayisi;
} Birim;

// 1. İlgili değerleri alıp bir Birim struct döndüren bir fonksiyon.
Birim* birimOlustur(const char* birimAdi, unsigned short int birimKodu);
//1.1 Parametre olarak çalışan dizisi alıp birime ekleyen fonksiyon.
void calisaniBirimeEkle(Birim* birim, Calisan* calisan);
// 2. İlgili değerleri alıp bir Calisan struct döndüren fonksiyon.
Calisan* calisanOlustur(const char* calisanAdi, const char* calisanSoyadi, unsigned short int birimKodu, float maas, int girisYil);
// 3. Oluşturulan yeni struct yapılarını diziye ekleyen fonksiyon.
void calisanlarıDiziyeEkle(Calisan*** calisanlar, Calisan* calisan);
//3.1
void birimleriDiziyeEkle(Birim*** birimler, Birim* birim);
// 4. Parametre olarak Calisan türünden değişken alıp bilgilerini yazdıran bir fonksiyon.
void calisanYazdir(Calisan* calisan);
// 5. Parametre olarak Birim türünden değişken alıp bilgilerini yazdıran bir fonksiyon.
void birimYazdir(Birim* birim);
// 6. Parametre olarak Birim türünden dinamik bir dizi alıp bilgilerini yazdıran bir fonksiyon.
void birimleriYazdir(Birim** birimler);
// 7. Parametre olarak aldığı birimin çalışanlarının maaş ortalamasını hesaplayan bir fonksiyon yazınız.
float birimOrtMaas(Birim* birim);
// 8. Parametre olarak aldığı birimde ortalama maaş üzerinde maaş alan çalışanları listeleyen bir fonksiyon.
void yüksekMaasAlanlar(Birim* birim);
// 9. Her birimin ayrı ayrı en yüksek maaş alan çalışanını yazdıran fonksiyon.
void enZenginler(Birim** birimler);
// 10. Parametre olarak bir maaş değeri alıp, 10 yıldan fazla çalışanlar bu maaştan az alıyor ise maaşlarını parametre olarak verilen maaşa eşitleyen fonksiyon.
void minimumMaas(float maas, Calisan** calisanlar);
// 11. Tüm Birim ve Calisan bilgilerini bir dosyaya yazan bir fonksiyon.
void dısaAktarBirim(Birim** birimler, const char* dosyaAdi);
//11.1
void dısaAktarCalisan(Calisan** calisanlar, const char* dosyaAdi);
//12. Tüm Birim ve Calisan bilgilerini dosyadan diziye aktaran bir fonksiyon.
void iceAktarBirim(const char* dosyaAdi, Birim*** birimler);
//12.1
void iceAktarCalisan(const char* dosyaAdi, Calisan*** calisanlar, Birim*** birimler);
//13. Bellek alanlarını serbest bırakan fonksiyon.
void tumVeriyiSerbestBirak(Birim** birimDizi, int birimSayisi);
#endif //PROJE1_H
