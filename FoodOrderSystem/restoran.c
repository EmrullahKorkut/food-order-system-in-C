#include <stdio.h>
#include <string.h>
#include <time.h>

int menu = 0;
void anaMenu();
void yemekEkle();
void siparisOnay();
void gunlukRapor();
void asciYonetim();
void Arama(char fileName[], char kategori[], char aranan[], char* returner);
void menuPrintle(char fileName[]);
void yemekListesiEkle(char fileName[]);
void yemekListesiGuncelle(char fileName[]);
void yemekListesiSil(char fileName[]);
void printSiparis(char filename[]);
void siparisDurumGuncelle(char fileName[], char sip_id[], char degisen[], char degisecek[]);
void gunlukRaporAl();
void gunlukRaporGoruntule();

int main() {
    anaMenu();

    while (1) {
        switch (menu) {
        case 1:
            yemekEkle();
            break;
        case 2:
            siparisOnay();
            break;
        case 3:
            gunlukRapor();
            break;
        case 5:
            asciYonetim();
            break;
        default:
            anaMenu();
            break;
        }
    }
}

// Ana menuyu printleyen fonksiyon
void anaMenu() {
    system("cls");
    printf("\nYemek Sepeti: Restoran Kontrol Programi\n=======================================\n");
    printf("Gitmek istediginiz menuyu seciniz\n\n1- Yemek Ekle/Guncelle/Sil\n");
    printf("2- Yeni Siparis Onay/Red\n3- Gunluk Raporlar\n4- Analizler\n");
    printf("5- Asci Yonetimi\n\n> ");
    scanf("%d", &menu);
}

/*Yemek adlarini fiyatlarini vs. alir ve ekler*/
void yemekEkle() {
    int mod = 0;
    system("cls");

    printf("\nYEMEK YONETIMI\n===============\nMEVCUT MENU:\n\n");
    menuPrintle("yemeklistesi.txt");
    printf("\n\n1- Yemek Ekle\n2- Yemek Guncelle\n3- Yemek Sil\n4- Geri\n\n> ");
    scanf("%d", &mod);

    if (mod == 1) {
        yemekListesiEkle("yemeklistesi.txt");
        yemekEkle();
    }
    else if (mod == 2) {
        yemekListesiGuncelle("yemeklistesi.txt");
        yemekEkle();
    }
    else if (mod == 3) {
        yemekListesiSil("yemeklistesi.txt");
        yemekEkle();
    }
    else {
        menu = 0;
    }
}

void siparisOnay() {
    system("cls");
    char id[32] = "0";
    int mod = 0;
    printf("\nBEKLEYEN SIPARISLER:\n\n");
    printSiparis("siparisler.txt");

    printf("\n1- Onayla\n2- Reddet\n3- Geri\n> ");
    scanf("%d", &mod);
    if (mod == 1) {
        printf("Onaylanacak ID'yi giriniz: ");
        scanf("%s", id);
        siparisDurumGuncelle("siparisler.txt", id, "durum", "2");
        siparisOnay();
    }
    else if (mod == 2) {
        printf("Reddedilecek ID'yi giriniz: ");
        scanf("%s", id);
        siparisDurumGuncelle("siparisler.txt", id, "durum", "1");
        siparisOnay();
    }
    else {
        anaMenu();
    }
}

void gunlukRapor() {
    system("cls");
    int mod = 0;
    char line[128];
    printf("\nGUNLUK RAPOR\n=================\n");


    printf("\n1- Gunluk Rapor Al\n2- Rapor Goruntule\n3- Bugunku Siparisleri Goster\n4- Geri\n\n>");
    scanf("%d", &mod);
    if (mod == 1) {
        gunlukRaporAl();
        gunlukRapor();
    }
    else if (mod == 2) {
        gunlukRaporGoruntule();
        gunlukRapor();
    }
    else if (mod == 3) {
        system("cls");
        printf("BUGUNKU SIPARISLER:\n\n");
        FILE* fptr = fopen("siparisler.txt", "r");
        while (fgets(line, sizeof(line), fptr) != NULL) {
            printf("%s", line);
        } fclose(fptr);
        printf("\nDevam etmek icin herhangi bir sayi girin: ");
        scanf("%d", &mod);
        gunlukRapor();
    }
    else {
        anaMenu();
    }
}

void asciYonetim() {
    char ascinum[32] = "0";
    int menu = 0;
    char line[128];
    FILE* fptr = fopen("ascisayisi.txt", "r");
    while(fgets(line, sizeof(line), fptr) != NULL) {
        sscanf(line, "asci_sayisi: \"%[^\"]\"", ascinum);
    }
    fclose(fptr);
    system("cls");
    printf("\nMevcut asci sayisi: %s", ascinum);
    printf("\n1- Asci Sayisi Degistir\n2- Geri\n\n>");
    scanf("%d", &menu);

    if (menu == 1) {
        printf("Degisecek asci sayisi: ");
        scanf("%s", ascinum);
        FILE* fptr2 = fopen("ascisayisi.txt", "w");
        fprintf(fptr2, "asci_sayisi: \"%s\"", ascinum);
        fclose(fptr2);
        asciYonetim();
    }
    else {
        anaMenu();
    }
}

void Arama(char fileName[], char kategori[], char aranan[], char* returner) {
    FILE* fptr;
    fptr = fopen(fileName, "r");
    char str[128];
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

void yemekListesiEkle(char fileName[]) {
    FILE* fptr;
    fptr = fopen(fileName, "a");
    char isim[32];
    int fiyat, sure, mevcut;

    printf("\nYemek adi: ");
    scanf("%s", isim);
    printf("\nFiyat: ");
    scanf("%d", &fiyat);
    printf("\nSure: ");
    scanf("%d", &sure);
    printf("\nMevcudiyet: ");
    scanf("%d", &mevcut);

    fprintf(fptr, "\n\nyemek_adi: \"%s\"", isim);
    fprintf(fptr, "\nfiyat: \"%d\"", fiyat);
    fprintf(fptr, "\nsure: \"%d\"", sure);
    fprintf(fptr, "\nmevcut: \"%d\"", mevcut);

    fclose(fptr);
}

/*Fonksiyon tarafindan degistirilmek istenen adi sorulur, ve bunun ardindan ad, fiyat, sure ve mevcudiyet ile guncellenir*/
void yemekListesiGuncelle(char fileName[]) {
    FILE* fptr, *fptr2;
    fptr = fopen(fileName, "r");
    char str[64], degisenYemek[32], isim[32];
    int searched_line = 0;
    int fiyat, sure, mevcut;
    int temp = 1;

    printf("\nDegistirmek istediginiz yemek: ");
    scanf("%s", degisenYemek);
    printf("\nYeni ad: ");
    scanf("%s", isim);
    printf("\nYeni fiyat: ");
    scanf("%d", &fiyat);
    printf("\nYeni sure: ");
    scanf("%d", &sure);
    printf("\nYeni mevcudiyet: ");
    scanf("%d", &mevcut);

    while(fgets(str, 64, fptr) != NULL) {
            if (strstr(str, degisenYemek) != NULL) {
                    break;
            }
            else {searched_line++;}
    }

    fptr2 = fopen("temp.c", "w");
    rewind(fptr);

    while(fgets(str, 64, fptr) != NULL) {
        if (temp == searched_line) {
            fprintf(fptr2, "\nyemek_adi: \"%s\"", isim);
            fprintf(fptr2, "\nfiyat: \"%d\"", fiyat);
            fprintf(fptr2, "\nsure: \"%d\"", sure);
            fprintf(fptr2, "\nmevcut: \"%d\"\n", mevcut);
            temp++;
        }
        else if (temp > searched_line && temp <= (searched_line+4)) {temp++;}
        else {
            fprintf(fptr2, str);
            temp++;
        }
    }
    fclose(fptr);
    fclose(fptr2);
    remove(fileName);
    rename("temp.c", fileName);
}

/* Fonksiyon icinde adi sorulan bir yemegi kaldirir */
void yemekListesiSil(char fileName[]) {
    FILE* fptr, *fptr2;
    fptr = fopen(fileName, "r");
    char str[64], degisenYemek[32];
    int searched_line = 0;
    int temp = 1;

    printf("Silinecek yemegi giriniz: ");
    scanf("%s", degisenYemek);

    while(fgets(str, 64, fptr) != NULL) {
            if (strstr(str, degisenYemek) != NULL) {
                    break;
            }
            else {searched_line++;}}

    fptr2 = fopen("temp.c", "w");
    rewind(fptr);
    while(fgets(str, 64, fptr) != NULL) {
        if (temp >= searched_line && temp <= (searched_line+4)) {
            temp++;
            continue;
        }
        else {
            fprintf(fptr2, str);
            temp++;
        }
    }
    fclose(fptr); fclose(fptr2);
    remove(fileName);
    rename("temp.c", fileName);
}

void menuPrintle(char fileName[]) {
    FILE* fptr;
    fptr = fopen(fileName, "r");
    char isim[32];
    char str[64];
    int fiyat, sure, mevcut;

    while (fgets(str, sizeof(str), fptr) != NULL) {
        if (strstr(str, "yemek_adi: ") != NULL) {
            sscanf(str, "yemek_adi: \"%[^\"]\"", isim);
            printf("%s", isim);
        } else if (strstr(str, "fiyat: ") != NULL) {
            sscanf(str, "fiyat: \"%d\"", &fiyat);
            printf(" - %d TL", fiyat);
        } else if (strstr(str, "sure: ") != NULL) {
            sscanf(str, "sure: \"%d\"", &sure);
            printf(" - %d dk", sure);
        } else if (strstr(str, "mevcut: ") != NULL) {
            sscanf(str, "mevcut: \"%d\"", &mevcut);
            printf(" - %d\n", mevcut);
        }
    }

    fclose(fptr);
}

void menuFiltrePrintle(char* fileName, char* attribute, char* expected_value) {
    FILE* file = fopen(fileName, "r");
    char line[256];
    char current_item[256] = "";
    char current_fiyat[256] = "";
    char current_sure[256] = "";
    char current_value[256] = "";

    while (fgets(line, sizeof(line), file)) {
        char* key = strtok(line, ":");
        char* value = strtok(NULL, "\n");

        if (strcmp(key, "yemek_adi") == 0) {
            strcpy(current_item, value);
        } else if (strcmp(key, "fiyat") == 0) {
            strcpy(current_fiyat, value);
        } else if (strcmp(key, "sure") == 0) {
            strcpy(current_sure, value);
        } else if (strcmp(key, attribute) == 0) {
            strcpy(current_value, value);
            if (strcmp(current_value, expected_value) == 0) {
                printf("yemek_adi: %s, fiyat: %s, sure: %s\n", current_item, current_fiyat, current_sure);
            }
        }
    }
    fclose(file);
}

void printSiparis(char filename[]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Cannot open file\n");
        return;
    }

    char kullanici[50], siparis_yemek[50], zaman[50], hazirlanma[50];
    int siparis_id, fiyat, asci, durum;
    //int same_siparis_id = -1;

    while (1) {
        if (fscanf(file, "kullanici: \"%[^\"]\"\n", kullanici) != 1) break;
        fscanf(file, "siparis_id: \"%d\"\n", &siparis_id);
        fscanf(file, "siparis_yemek: \"%[^\"]\"\n", siparis_yemek);
        fscanf(file, "fiyat: \"%d\"\n", &fiyat);
        fscanf(file, "zaman: \"%[^\"]\"\n", zaman);
        fscanf(file, "hazirlanma: \"%[^\"]\"\n", hazirlanma);
        fscanf(file, "asci: \"%d\"\n", &asci);
        fscanf(file, "durum: \"%d\"\n", &durum);

        if (durum == 0/* && (same_siparis_id == -1 || same_siparis_id == siparis_id)*/) {
            printf("Kullanici: %s\n", kullanici);
            printf("Siparis ID: %d\n", siparis_id);
            printf("Siparis Yemek: %s\n", siparis_yemek);
            printf("Fiyat: %d\n", fiyat);
            printf("Zaman: %s\n", zaman);
            printf("\n");

            //same_siparis_id = siparis_id;
        }
    }

    fclose(file);
}

void siparisDurumGuncelle(char fileName[], char sip_id[], char degisen[], char degisecek[]) {
    FILE *fptr = fopen(fileName, "r");
    if (fptr == NULL) {
        printf("Can't open file.");
        return;
    }

    char simdikiID[32] = "";
    char fullDegisen[128] = {};
    strcat(fullDegisen, degisen);
    strcat(fullDegisen, ": ");
    char line[256];
    int flag = 0, first_line = 0, line_num = 0, occur = 0;

    while (fgets(line, sizeof(line), fptr) != NULL) {
        if (strstr(line, "siparis_id: ") != NULL) {
            sscanf(line, "siparis_id: \"%[^\"]\"", simdikiID);
            if (strcmp(simdikiID, sip_id) == 0) {
                flag = 1;
            }
        }
        if ((flag == 1) && (strstr(line, fullDegisen) != NULL)) {
            if (first_line == 0) {
                first_line = line_num;
            }
            occur++;
            flag = 0;
        }
        line_num++;
    }

    int temp = 0;
    FILE* fptr2 = fopen("temp.c", "w");
    rewind(fptr);
    strcat(fullDegisen, "\"%s\"\n");

    while(fgets(line, sizeof(line), fptr) != NULL) {
        if ((((temp - first_line) % 9) == 0) && (occur != 0) && ((temp-first_line) >= 0)) {
            fprintf(fptr2, fullDegisen, degisecek);
            temp++; occur--;
        }
        else {
            fprintf(fptr2, line);
            temp++;
        }
    }
    fclose(fptr);
    fclose(fptr2);
    remove(fileName);
    rename("temp.c", fileName);
    return;
}

void gunlukRaporAl() {
    FILE* fptr = fopen("siparisler.txt", "r");
    FILE* fptr2 = fopen("temp.c", "w");
    char line[128];

    while(fgets(line, sizeof(line), fptr) != NULL) {
        fprintf(fptr2, line);
    }

    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    char name[32] = {};
    int days = timeinfo->tm_mday;
    int months = timeinfo->tm_mon;
    int years = timeinfo->tm_year;
    sprintf(name, "%d_%d_%d.txt",  days, (months+1), (years-100));

    fclose(fptr); fclose(fptr2);
    remove("siparisler.txt");
    rename("temp.c", name);

    FILE* file = fopen("siparisler.txt", "w");
    fclose(file);

    system("cls");
    printf("\nGUNLUK RAPOR BASARIYLA \"%d_%d_%d.txt\" OLARAK ALINDI.", days, (months+1), (years-100));
    sleep(3);

    return;
}

void gunlukRaporGoruntule() {
    int gun, ay, yil;
    char isim[64] = {};
    char line[128];

    printf("Goruntulemek istediginiz raporu \"d m yy\" formatinda giriniz: ");
    scanf("%d %d %d", &gun, &ay, &yil);

    sprintf(isim, "%d_%d_%d.txt", gun, ay, yil);

    FILE* fptr = fopen(isim, "r");
    if (fptr == NULL) {
        printf("Boyle bir dosya bulunamadi.");
        sleep(2);
        return;
    }

    printf("\n\n%d/%d/%d TARIHLI GUNLUK RAPOR:\n\n", gun, ay, yil);
    while(fgets(line, sizeof(line), fptr) != NULL) {
        printf("%s", line);
    }
    fclose(fptr);
    printf("\nDevam etmek icin herhangi bir sayi girin: ");
    scanf("%d", &gun);
    return;
}
