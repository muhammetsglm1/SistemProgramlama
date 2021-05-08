#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "fields.h"

void kilitAgaciniOlustur(char *dosyaAdi, JRB kilitTree, JRB pNode);

void dosyaOku(char *dosyaAdi, JRB kilitTree, char *cikisDosyasi, int encrypt);

void dosyaOkuDec(char *dosyaAdi, JRB kilitTree, char *cikisDosyasi);

char *kelimeler(char *dong, char *word, int *flag);

char *intKelimeler(char *dong, char *word, int *flag);

char *getKelime(char *word, JRB b);

int revcomp(Jval k1, Jval k2) {
    return -strcmp(k1.s, k2.s);
}


int main(int argc, char *argv[]) {

    JRB bn;
    JRB enc = make_jrb();
    JRB dec = make_jrb();
    kilitAgaciniOlustur(".kilit", enc, dec);

//    jrb_traverse(bn, dec) {
//        printf("%-20s %s ", jval_s(bn->key), jval_s(bn->val));
//        printf("\n");
//    }

    if (strcmp(argv[1], "-e") == 0) {
        dosyaOku(argv[2], enc, argv[3], 1);
    } else {
        dosyaOkuDec(argv[2], dec, argv[3]);
    }


    return 0;
}

void kilitAgaciniOlustur(char *dosyaAdi, JRB kilitTree, JRB decKilitTree) {
    IS is;
    is = new_inputstruct(dosyaAdi);
    int nsize, i, deger;
    char *gelenKelime;
    while (get_line(is) >= 0) {
        if (is->NF > 1) {
            nsize = strlen(is->fields[1]);
            for (i = 1; i < is->NF - 1; i++) nsize += (strlen(is->fields[i]) + 1);

            char *lineWithoutQuotes = (char *) malloc(sizeof(char) * (nsize + 1));
            char *lineWithoutQuotes1 = (char *) malloc(sizeof(char) * (nsize + 1));
            char *lineWithoutQuotes3 = (char *) malloc(sizeof(char) * (nsize + 1));
            char *degerStr = (char *) malloc(sizeof(char) * (nsize + 1));
            strcpy(lineWithoutQuotes, is->fields[is->NF - 1]);
            int i, j;

            for (i = j = 0; i < strlen(is->fields[is->NF - 1]); i++) {
                if (lineWithoutQuotes[i] >= '0' && lineWithoutQuotes[i] <= '9'){
                    lineWithoutQuotes1[j] = lineWithoutQuotes[i];
                    lineWithoutQuotes3[j++] = lineWithoutQuotes[i];
                }
            }
            strcpy(degerStr, lineWithoutQuotes3);
            deger = atoi(lineWithoutQuotes1);
//                  printf("lineWithoutQuotes3: %s\n", lineWithoutQuotes3);
            //---------------------------------------------------------------------------

            nsize = strlen(is->fields[0]);
            for (i = 1; i < is->NF - 1; i++) nsize += (strlen(is->fields[i]) + 1);
            gelenKelime = (char *) malloc(sizeof(char) * (nsize + 1));
            strcpy(gelenKelime, is->fields[0]);
            char *lineWithoutQuotes2 = (char *) malloc(sizeof(char) * (nsize + 1));
            for (i = j = 0; i < nsize; i++) {
                if (gelenKelime[i] >= 'a' && gelenKelime[i] <= 'z')
                    lineWithoutQuotes2[j++] = gelenKelime[i];
            }
            strcpy(gelenKelime, lineWithoutQuotes2);

            (void) jrb_insert_gen(kilitTree, new_jval_s(gelenKelime), new_jval_i(deger), revcomp);
//            printf("Eklenen: %s -> %s\n", degerStr, gelenKelime);
            (void) jrb_insert_gen(decKilitTree, new_jval_s(degerStr), new_jval_s(gelenKelime), revcomp);

//            printf("Ekleme anahtar: %s deger: %d\n", gelenKelime, deger);
//            printf("gelen 111: %s\n",getKelime("111",decKilitTree));
        }
    }
}

char *getKelime(char *word, JRB b) {
//    printf("Aranan: %s\n", word);
    JRB pNode = jrb_find_str(b, strdup(word));
    if (pNode != NULL) {
//        printf("bulundu: jrb_find_str -> %s \n", pNode->val.s);
        return pNode->val.s;
    }

    JRB pJrbNode = jrb_find_gen(b, new_jval_s(word), revcomp);
    if (pJrbNode != NULL) {
//        printf("bulundu: jrb_find_gen -> %s \n", pJrbNode->val.s);
        return pJrbNode->val.s;
    }
}

int getSifre(char *word, JRB b) {
    // printf("Aranan: %s\n", word);
    JRB pNode = jrb_find_str(b, strdup(word));
    if (pNode != NULL) {
        //   printf("bulundu: jrb_find_str -> %d \n",pNode->val.i);
        return pNode->val.i;
    }

    JRB pJrbNode = jrb_find_gen(b, new_jval_s(word), revcomp);
    if (pJrbNode != NULL) {
        return pJrbNode->val.i;
    }

    return -1;
}

void dosyaOku(char *dosyaAdi, JRB kilitTree, char *cikisDosyasi, int encrypt) {
    FILE *fPtr;
    fPtr = fopen(cikisDosyasi, "a");


    FILE *fin = fopen(dosyaAdi, "r");
    char dong[1000] = {};
    char *s = NULL;
    int flag = 0;
    int nline = 1;

    while (fgets(dong, sizeof(dong), fin) != NULL) {

        s = dong;
        while (s != NULL) {
            char word[100] = {};
            char info[100] = {};
            s = kelimeler(s, word, &flag);

            if (flag == 0) {
                if ((word[0] <= 'Z' && word[0] >= 'A') || word[0] == '\0')
                    continue;
            } else {
                if (word[0] == '\0')
                    continue;
            }
            //printf("islenecek kelime: %s -> %d\n", word, getSifre(word, kilitTree));

            if (encrypt == 1) {
                char buffer[16] = {0};
                int sifre = getSifre(word, kilitTree);

                if (sifre > -1) {
                    sprintf(buffer, "%d", sifre);
                    fputs(buffer, fPtr);
                } else {
                    fputs(word, fPtr);
                }


            } else {
                char *kelime = getKelime(word, kilitTree);
                if (kelime == NULL) {
                    fputs(word, fPtr);
                } else {
                    fputs(kelime, fPtr);
                }
            }
            fputs(" ", fPtr);
        }
        nline++;
    }

    fclose(fPtr);
}

void dosyaOkuDec(char *dosyaAdi, JRB kilitTree, char *cikisDosyasi) {
//    printf("dec okuma basladi\n");
    FILE *fPtr;
    fPtr = fopen(cikisDosyasi, "a");


    FILE *fin = fopen(dosyaAdi, "r");
    char dong[1000] = {};
    char *s = NULL;
    int flag = 0;
    int nline = 1;

    while (fgets(dong, sizeof(dong), fin) != NULL) {

        s = dong;
//        printf("s: %s\n", s);
        while (s != NULL) {
            char word[100] = {};
            s = intKelimeler(s, word, &flag);
//            printf("islenecek kelime: %s -> %d\n", word, getKelime(word, kilitTree));
            if (flag == 0) {
                if (word[0] == '\0')
                    continue;
            } else {
                if (word[0] == '\0')
                    continue;
            }


            char *kelime = getKelime(word, kilitTree);
            if (kelime == NULL) {
                fputs(word, fPtr);
            } else {
                fputs(kelime, fPtr);
            }
            fputs(" ", fPtr);
        }
        nline++;
    }

    fclose(fPtr);
}

char *kelimeler(char *dong, char *word, int *flag) {
    int i = 0;
    char c;
    while ((c = *dong) && ((c > 'z' || c < 'a') && (c > 'Z' || c < 'A'))) {
        if (c == '.') {
            *flag = 1;
        }
        ++dong;
    }

    if (c == '\0') {
        return NULL;
    }

    do {
        word[i++] = c;
        ++dong;
    } while ((c = *dong) && ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A')));
    return dong;
}

char *intKelimeler(char *dong, char *word, int *flag) {
    int i = 0;
    char c;
    while ((c = *dong) && ((c > '9' || c < '0'))) {
        if (c == '.') {
            *flag = 1;
        }
        ++dong;
    }

    if (c == '\0') {
        return NULL;
    }

    do {
        word[i++] = c;
        ++dong;
    } while ((c = *dong) && ((c <= '9' && c >= '0')));
    return dong;
}