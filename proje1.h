//
// Created by Mehmet Enes on 7.12.2024.
//
#ifndef PROJE1_H
#define PROJE1_H
#include <stdio.h>

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
    Calisan* birimCalisanlar;
} Birim;

// 1. İlgili değerleri alıp bir Birim struct döndüren bir fonksiyon.
Birim birimOlustur(char* birimAdi, unsigned short int birimKodu);
//Birim birimOlustur2(char* birimAdi, unsigned short int birimKodu);
void birimCalisanlariDüzenle(Birim* birim, Calisan* birimCalisanlar);
// 2. İlgili değerleri alıp bir Calisan struct döndüren fonksiyon.
Calisan* calisanOlustur(char* calisanAdi, char* calisanSoyadi, unsigned short int birimKodu, float maas, int girisYil);
// 3. Oluşturulan yeni struct yapılarını diziye ekleyen fonksiyon.
void calisanlarıDiziyeEkle(Calisan*** calisanlar, Calisan* calisan);
//3.1
void birimleriDiziyeEkle(Birim** birimler, Birim birim);
// 4. Parametre olarak Calisan türünden değişken alıp bilgilerini yazdıran bir fonksiyon.
void calisanYazdir(Calisan* calisan);
// 5. Parametre olarak Birim türünden değişken alıp bilgilerini yazdıran bir fonksiyon.
void birimYazdir(Birim birim);
// 6. Parametre olarak Birim türünden dinamik bir dizi alıp bilgilerini yazdıran bir fonksiyon.
void birimleriYazdir(Birim* birimler);
// 7. Parametre olarak aldığı birimin çalışanlarının maaş ortalamasını hesaplayan bir fonksiyon yazınız.
float birimOrtMaas(Birim birim);
// 8. Parametre olarak aldığı birimde ortalama maaş üzerinde maaş alan çalışanları listeleyen bir fonksiyon.
void yüksekMaasAlanlar(Birim birim);
// 9. Her birimin ayrı ayrı en yüksek maaş alan çalışanını yazdıran fonksiyon.
void enZenginler(Birim* birimler);
// 10. Parametre olarak bir maaş değeri alıp, 10 yıldan fazla çalışanlar bu maaştan az alıyor ise maaşlarını parametre olarak verilen maaşa eşitleyen fonksiyon.
void minimumMaas(float maas, Calisan* calisanlar);
// 11. Tüm Birim ve Calisan bilgilerini bir dosyaya yazan bir fonksiyon.
void dısaAktaBirimr(Birim* birimler);
void dısaAktarCalisan(Calisan* calisanlar);
// 12. Tüm Birim ve Calisan bilgilerini dosyadan diziye aktaran bir fonksiyon.
void iceAktar(FILE* dosya);


#endif //PROJE1_H
