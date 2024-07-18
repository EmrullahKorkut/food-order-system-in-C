#include <stdio.h>
#include <string.h>
#include <time.h>

void printOncekiSiparis();
void printSiparis();
void Arama();
void Kayit();
void Giris();
void menuFiltre();
void Menu();
void anaMenu();
void Siparis();
char kullaniciAdi[64] = {};

int main(){

anaMenu();

}

void Arama(char fileName[], char kategori[], char aranan[], char* returner){    //ARAMA FONK.

//Dosyadaki her satiri dolasarak belirli bir kategori ve deseni iceren satiri bulur. Bulunan verileri ‘‘returner’’ stringine aktarir.​


    FILE* fptr;
    fptr = fopen(fileName, "r");
    char str[256];
    if (fptr == NULL) {printf("FILE LOAD FAILED."); return;}

    int flag = 0;
    char RESULT[256] = {};
    strcat(RESULT, aranan);
    strcat(RESULT, ": \"%[^\"]\"");
    while (fgets(str, sizeof(str), fptr)!= NULL) {
        if (strstr(str, kategori) != NULL) {
            flag = 1;
        }
        if (flag == 1 && strstr(str, aranan) != NULL) {
            sscanf(str, RESULT, returner);
            fclose(fptr);
            break; }
    }
    return;

}

void Kayit(char fileName[]){                                                    //KAYIT FONK.

//Kullanicidan alinan bilgileri dosyaya ekler ve kayit isleminin basarili oldugunu kullaniciya bildirir.​


    FILE* fptr;
    fptr = fopen(fileName, "a");
    char name[64], password[64];

    printf("\nKullanici Adi:  ");
    scanf("%s", name);
    printf("\nSifre: ");
    scanf("%s", password);
    strcat(kullaniciAdi, name);

    fprintf(fptr, "\nkullaniciadi:  \"%s\"", name);
    fprintf(fptr, "\nSifre: \"%s\"", password);

    printf("Kayit basarili. ");
    fclose(fptr);
}

void Giris() {                                                                  //GIRIS FONK.

//Kullanicidan kullanici adi ve sifre bilgisini alir, bu bilgileri kayit dosyasinda arar ve dogrulama yapar.
//Giris basariliysa kullaniciyi sistemde oturum acmıs olarak kabul eder.​

    printf("\nGiris yap\n\n");

    while(1){

        char isim[64], kullanici_adi[64], sifre[64];

        printf("Kullanici adi: ");
        scanf("%s", kullanici_adi);

        printf("Sifre: ");
        scanf("%s", sifre);

        Arama("kayit.txt", kullanici_adi, "Sifre", isim);
        int strcmp(sifre, isim);

        if(strcmp(isim, sifre)==0){
            printf("Giris basarili. ");
            strcat(kullaniciAdi, kullanici_adi);
            break;
        }
        else{
            printf("\n\nKullanici adi ve/veya sifre hatali. Tekrar deneyiniz...\n\n");
        }
    }
}

void menuFiltre(char* fileName, char* filtre, char* beklenen_deger) {           //MENU FILTRELEME FONK.

//Dosyadaki menu ögelerini belirli bir kritere gore filtreler ve eslesen ögeleri ekrana yazdirir.

    FILE* file = fopen(fileName, "r");
    char str[256];
    char simdiki_yemek[256] = "";
    char simdiki_fiyat[256] = "";
    char simdiki_sure[256] = "";
    char simdiki_deger[256] = "";

    while (fgets(str, sizeof(str), file)) {
        char* part = strtok(str, ":");
        char* deger = strtok(NULL, " \n");

        if (strcmp(part, "yemek_adi") == 0) {
            strcpy(simdiki_yemek, deger);
        } else if (strcmp(part, "fiyat") == 0) {
            strcpy(simdiki_fiyat, deger);
        } else if (strcmp(part, "sure") == 0) {
            strcpy(simdiki_sure, deger);
        } else if (strcmp(part, filtre) == 0) {
            strcpy(simdiki_deger, deger);
            if (strcmp(simdiki_deger, beklenen_deger) == 0) {
                printf("\nyemek_adi: %s, fiyat: %s TL, sure: %s Dakika\n", simdiki_yemek, simdiki_fiyat, simdiki_sure);
            }
        }
    }
    fclose(file);
}

void printSiparis(char filename[]) {                                            //ALINAN SIPARIS FONK.

// Dosyadaki devam eden siparisleri kullaniciya sunar.​

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("FILE READ FAIL.\n");
        return;
    }

    char kullanici[50], siparis_yemek[50], zaman[50], hazirlanma[50];
    int siparis_id, fiyat, asci, durum;

    while (1) {
        if (fscanf(file, "kullanici: \"%[^\"]\"\n", kullanici) != 1) break;
        fscanf(file, "siparis_id: \"%d\"\n", &siparis_id);
        fscanf(file, "siparis_yemek: \"%[^\"]\"\n", siparis_yemek);
        fscanf(file, "fiyat: \"%d\"\n", &fiyat);
        fscanf(file, "zaman: \"%[^\"]\"\n", zaman);
        fscanf(file, "hazirlanma: \"%[^\"]\"\n", hazirlanma);
        fscanf(file, "asci: \"%d\"\n", &asci);
        fscanf(file, "durum: \"%d\"\n", &durum);

        if ((durum != 1 && durum != 4) && (strcmp(kullanici, kullaniciAdi) == 0)) {
            printf("Kullanici: %s\n", kullanici);
            printf("Siparis ID: %d\n", siparis_id);
            printf("Siparis Yemek: %s\n", siparis_yemek);
            printf("Fiyat: %d TL\n", fiyat);
            printf("Siparis Tarihi: %s\n", zaman);
            if(durum == 0){
                printf("Onay bekliyor.\n");
            }
            else if(durum == 2){
                printf("Onaylandi.\n");
            }
            else if(durum == 3){
                printf("Hazirlaniyor.\n");
            }

            printf("\n");
        }
    }

    fclose(file);
    return;
}

void Siparis(const char *fileName){                                             //SPARIS ALMA FONK.

//Kullanicidan siparis bilgilerini alir ve dosyaya yeni bir siparis ekler.​

    char isim[64];
    char fiyat[64];

    int siparis_id;
    char yemek_secimi[64] = "";

    printf("\n\nYemek listesi:\n\n");
    menuFiltre("yemeklistesi.txt", "mevcut", "\"1\"");

    printf("\nYemek adi ile sipraisinizi seciniz. \n\n");
    scanf("\n%s", yemek_secimi);

    FILE* fptr2 = fopen(fileName, "r");
    char enbuyukid[16] = "0";
    char line[128];
    char simdikiID[32];
    while (fgets(line, sizeof(line), fptr2) != NULL) {
        if (strstr(line, "siparis_id: ") != NULL) {
            sscanf(line, "siparis_id: \"%[^\"]\"", simdikiID);
            if (atoi(simdikiID) > atoi(enbuyukid)) {
                strcpy(enbuyukid, simdikiID);
            }
        }
    }

    Arama("yemeklistesi.txt", yemek_secimi, "yemek_adi", isim);
    Arama("yemeklistesi.txt", yemek_secimi, "fiyat", fiyat);

    FILE* fptr;
    fptr = fopen(fileName, "a");
    struct tm tm = *localtime(&(time_t){ time(NULL) });
    char *foo = asctime(&tm);
    foo[strlen(foo)-1] = 0;

    fprintf(fptr, "\n\nkullanici: \"%s\"", kullaniciAdi);
    fprintf(fptr, "\nsiparis_id: \"%d\"", (atoi(enbuyukid)+1));
    fprintf(fptr, "\nsiparis_yemek:  \"%s\"", yemek_secimi);
    fprintf(fptr, "\nfiyat: \"%s\"", fiyat);
    fprintf(fptr, "\nzaman: \"%s\"", foo);
    fprintf(fptr, "\nhazirlanma: \"%s\"", "asd");
    fprintf(fptr, "\nasci: \"%s\"", "3");
    fprintf(fptr, "\ndurum: \"%s\"", "0");

    printf("\nSiparisiniz onay beklemede. \n\n");

    fclose(fptr);
}

void Mevcut_Siparis(const char *fileName){                                      //MEVCUT SIPARIS GORUNTULEME FONK.

//Kullanicinin devam eden siparislerini kontrol eder ve eger varsa ekrana yazdirir.​

    char isim[64];
    char mevcut_durum[64];

    FILE* fptr;
    fptr = fopen(fileName, "r");

    Arama("siparisler.txt", "0", "durum", mevcut_durum);
    Arama("siparisler.txt", kullaniciAdi, "kullanici", isim);

    if((strcmp(mevcut_durum, "0") == 0) && (strcmp(isim, kullaniciAdi) == 0)){
        printSiparis("siparisler.txt");
    }
    else{
        printf("Mevcut siparisiniz yoktur. ");
    }
    fclose(fptr);
}

void printOncekiSiparis(char filename[]) {                                      //ONCEKI SIPARISLERI GORUNTULEME FONK.

//Kullanicinin onceki siparislerini dosyadan okuyarak ekrana yazdirir.​


    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("FILE READ FAIL.\n");
        return;
    }

    char kullanici[50], siparis_yemek[50], zaman[50], hazirlanma[50];
    int siparis_id, fiyat, asci, durum;

    while (1) {
        if (fscanf(file, "kullanici: \"%[^\"]\"\n", kullanici) != 1) break;
        fscanf(file, "siparis_id: \"%d\"\n", &siparis_id);
        fscanf(file, "siparis_yemek: \"%[^\"]\"\n", siparis_yemek);
        fscanf(file, "fiyat: \"%d\"\n", &fiyat);
        fscanf(file, "zaman: \"%[^\"]\"\n", zaman);
        fscanf(file, "hazirlanma: \"%[^\"]\"\n", hazirlanma);
        fscanf(file, "asci: \"%d\"\n", &asci);
        fscanf(file, "durum: \"%d\"\n", &durum);

        if (durum == 4 && strcmp(kullanici, kullaniciAdi) == 0) {
            printf("Kullanici: %s\n", kullanici);
            printf("Siparis ID: %d\n", siparis_id);
            printf("Siparis Yemek: %s\n", siparis_yemek);
            printf("Fiyat: %d TL\n", fiyat);
            printf("Siparis Tarihi: %s \n", zaman);
            printf("\n");
        }
    }

    fclose(file);
    return;
}

void Menu(){                                                                    //ANAMENUDEN SONRAKI MENU SECIM EKRANI FONK.

//Kullaniciya ana menü seceneklerini sunar, secim yapmasini bekler ve secime gore ilgili islevi cagirir.​

    int islem;
    int ikinci_islem;

    system("cls");

    printf("Mevcut Kullanici: %s\n", kullaniciAdi);
    printf("Gitmek istediginiz menuyu seciniz: \n\n");
    printf("1- Yeni Siparis\n2- Mevcut Siparis Durumu\n3- Daha Onceki Siparislerim\n4- Programi Kapat\n\n=======================================\n\n");

    scanf("%d", &islem);

    switch(islem){
    case 1:
        Siparis("siparisler.txt");
        while(1){
        printf("\nIslem seciniz:\n\n1- Programi kapat.\n2- Menuye git.\n3- Tekrar siparis ver.\n\n");
        scanf("%d", &ikinci_islem);
        if(ikinci_islem == 1){
            break;
        }
        else if(ikinci_islem == 2){
            Menu();
        }
        else if(ikinci_islem == 3){
            Siparis("siparisler.txt");
        }
        }
        break;

    case 2:
        Mevcut_Siparis("siparisler.txt");
        printf("Islem seciniz.\n\n1- Programi kapat. \n2- Menuye git.\n\n");
        scanf("%d", &ikinci_islem);
        if(ikinci_islem == 1){
            break;
        }
        else if(ikinci_islem == 2){
            Menu();
        }
        break;

    case 3:
        printOncekiSiparis("siparisler.txt");
        printf("\nIslem seciniz.\n\n1- Programi kapat. \n2- Menuye git.\n\n");
        scanf("%d", &ikinci_islem);
        if(ikinci_islem == 1){
            break;
        }
        else if(ikinci_islem == 2){
            Menu();
        }
        break;
        case 4:
        break;
    default:
        Menu();
        break;
}
}

void anaMenu(){                                                                 //ANA MENU FONK.

//Kullaniciya kayit olma veya giris yapma seceneklerini sunar, secim yapmasini bekler ve ilgili islevi cagirir.​

    system("cls");
    int secim;
    printf("Yemek Sepeti: Musteri Paneli\n\n=======================================\n\n");
    printf("1- Musterimiz degilseniz --> Kayit olmak istiyorum. \n2- Musterimizseniz --> Giris Yap. \n3- Programi Kapat\n\n");

    scanf("%d", &secim);

    switch(secim){
    case 1:
        Kayit("kayit.txt");
        Menu();
        break;

    case 2:
        Giris();
        Menu();
        break;
    case 3:
        break;
    default:
        anaMenu();
        break;
}
}

