#include <stdio.h>
#include <stdlib.h>
#define RED 8
#define STU 16

unsigned int G[RED][STU] =
    {
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1},
    {0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0},
    {0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0},
    {1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1},
    {1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1},
    {0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1},
    {0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0}
    };
    
    
unsigned int G_[RED][STU] =
    {
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1},
    {0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0}
    };
    
    
unsigned int H[RED][STU] =
    {
    {0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0},
    {1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
    {1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
    };


typedef unsigned int elem;
typedef char byte;

typedef struct
    {
    char a;
    char b;
    }
twoByte;

int pomnoziMatrice (elem** prva, elem** druga, int prvaR, int prvaC, int drugaR, int drugaC, elem** rezultat);
void transponirajMatricu(elem** glavnaMatrica, int Rg, int Sg, elem** transponiranaMatrica);
void setElementMatrice(elem** matrica, int redaka, int stupaca, int R, int S, elem element);
elem getElementMatrice(elem** matrica, int redaka, int stupaca, int R, int S);
void popuniDinamickuMatricu8_16(elem** matrica, elem podaci[RED][16]);
void izmjeniPodatakMatrice(int R, int S, elem** matrica, elem value);
twoByte kodiranaInformacija(elem ** redakMatrica, int stupaca);
int definirajMatricu(elem R, elem S, elem** matrica);
void dodajRedakUMatricu(byte znak, elem** matrica);
void ispisMatrice(elem** matrica, int R, int S);
byte izRetkaMatriceUChar(elem** matrica);
void printBinary(byte podatak);


int main(int argc, char *argv[])
    {
    elem i = 0;
    elem j = 0;
    elem* matricaG  = NULL;
    elem* matricaG_ = NULL;
    elem* matricaH  = NULL;
    elem* matricaGt  = NULL;
    elem* matricaG_t = NULL;
    elem* matricaHt  = NULL;
    elem* ulazniRedak = NULL;
    elem* kodiraniRedak = NULL;
    byte ulazni;
    int ulazniInt;
    elem osnovniKod;
    long int velicinaDat = 0;
    FILE* ulaznaDatoteka;
    FILE* izlaznaDatoteka;
    byte* informacija;
    twoByte* izlaznaInformacija;
	int broj_zapisanih;
    /* ////////////////////////////////// */
    /* ////////////////////////////////// */
    /* ////////////////////////////////// */
    
    definirajMatricu(RED, STU, &matricaG);
    definirajMatricu(RED, STU, &matricaG_);
    definirajMatricu(RED, STU, &matricaH);
    definirajMatricu(STU, RED, &matricaGt);
    definirajMatricu(STU, RED, &matricaG_t);
    definirajMatricu(STU, RED, &matricaHt);
    definirajMatricu(1, RED, &ulazniRedak);
    definirajMatricu(1, STU, &kodiraniRedak);
    
    popuniDinamickuMatricu8_16(&matricaG, G);
    popuniDinamickuMatricu8_16(&matricaG_, G_);
    popuniDinamickuMatricu8_16(&matricaH, H);

    transponirajMatricu(&matricaG, RED, STU, &matricaGt);
    transponirajMatricu(&matricaG_, RED, STU, &matricaG_t);
    transponirajMatricu(&matricaH, RED, STU, &matricaHt);
    
    /*printf("G: \n");
    ispisMatrice(&matricaG, RED, STU);
    printf("G transponirano: \n");
    ispisMatrice(&matricaGt, STU, RED);
    
    printf("H: \n");
    ispisMatrice(&matricaH, RED, STU);
    printf("H: transponirano: \n");
    ispisMatrice(&matricaHt, STU, RED);
    
    printf("G_: \n");
    ispisMatrice(&matricaG_, RED, STU);
    printf("G_ transponirano: \n");
    ispisMatrice(&matricaG_t, STU, RED);*/
    
    if(argc != 3)
        {
        printf("krivi broj argumenata!\nargumenti moraju biti u obliku:\n\nprogram.exe ulazna izlazna");
        exit(-1);
        }

    ulaznaDatoteka = fopen(argv[1], "rb");
    izlaznaDatoteka = fopen(argv[2], "wb");
    
    /*ulaznaDatoteka = fopen(argv[1], "rb");
    izlaznaDatoteka = fopen(argv[2], "rb");*/
    
    if(!ulaznaDatoteka)
        {
        printf("Nije moguce ucitati ulaznu binarnu datoteku!\n");
        exit(-1);
        }
        
    if(!izlaznaDatoteka)
        {
        printf("Nije moguce pisati u izlaznu binarnu datoteku!\n");
        exit(-1);
        }

    fseek(ulaznaDatoteka, 0L, SEEK_END);
    velicinaDat = ftell(ulaznaDatoteka);
    printf("velicina ulazne datoteke: [%d]B\n", velicinaDat);
    informacija = malloc(velicinaDat);
    fseek(ulaznaDatoteka, 0L, SEEK_SET);
    
    if(informacija == NULL)
        {
        printf("nije moguce rezervirati toliko memorije za datoteku!\n");
        exit(-1);
        }

    printf("[%ld]B memorije uspjesno alocirano\n", velicinaDat);
    informacija[velicinaDat - 1] = 0x8;
    printf("uspjesno testiran range alocirane memorije\n");
    
    if(!fread(informacija, velicinaDat, 1, ulaznaDatoteka))
        {
        printf("neuspjelo citanje informacije iz datoteke!\n");
        exit(-1);
        }

    printf("ulazna datoteka ucitana u memoriju!\nzatvaram datoteku....\n");
    fclose(ulaznaDatoteka);
    printf("...uspjeh! Citam i kodiram stream...\n");
    izlaznaInformacija = (twoByte *) malloc(velicinaDat * sizeof(twoByte));
    
    if(izlaznaInformacija == NULL)
        {
        printf("nije moguce rezervirati memoriju za izlaznu datoteku!\n");
        exit(-1);
        }
    printf("rezervirano [%d]B za izlaznu datoteku\n", velicinaDat * 2);
	printf("velicina informacije za dekodiranje: [%d]B\n", sizeof(twoByte));
    /* ////////////////////////////////// */
    /* ////////////////////////////////// */
    /* ////////////////////////////////// *//* ////////////////////////////////// Tu se odvija glavni dio programa*/
    
    
    for(i = 0; i < velicinaDat; i++)
        {
		twoByte izlaz;
        ulazni = informacija[i];
        dodajRedakUMatricu(ulazni, &ulazniRedak);
		
        pomnoziMatrice(&ulazniRedak, &matricaG_, 1, RED, RED, STU, &kodiraniRedak);
		izlaz = kodiranaInformacija(&kodiraniRedak, STU);
		
		izlaznaInformacija[i] = izlaz;
        }
	
	/*printf("velicina: %d\n", velicinaDat);
	for(i = 0; i < velicinaDat; i++)
        {
		twoByte ulaz;
        ulaz = izlaznaInformacija[i];
		printf("%c %c\n", ulaz.a, ulaz.b);
        }

	printf("uspjesno kodirano, zapisivanje u izlaznu binarnu datoteku\n");*/
	broj_zapisanih = fwrite(izlaznaInformacija, sizeof(twoByte), velicinaDat, izlaznaDatoteka);
	
	if((int) broj_zapisanih != (int) velicinaDat)
		{
		printf("zapisano samo [%d] elemenata u izlaznu datoteku :( (greska!)\n", broj_zapisanih);
		exit(-1);
		}
	printf("uspjesno zapisano [%d] zapisa u datoteku!", broj_zapisanih);
	
    
    /* ////////////////////////////////// *//* ////////////////////////////////// */
    /* ////////////////////////////////// */
    /* ////////////////////////////////// */
     /*kraj*/
    printf("\n-----\n[kraj!]");
	fclose(izlaznaDatoteka);
    free(ulazniRedak);
    free(matricaG);
    free(matricaG_);
    free(matricaH);
    free(matricaGt);
	free(izlaznaInformacija);
    free(matricaG_t);
    free(matricaHt);
    free(informacija);
    return 0;
    }

/* ////////////////////////////////// *//* ////////////////////////////////// */

elem getElementMatrice(elem** matrica, int redaka, int stupaca, int R, int S)
    {
    /*ispisMatrice(matrica, redaka, stupaca);*/
    return (*matrica)[R * stupaca + S];
    }

void setElementMatrice(elem** matrica, int redaka, int stupaca, int R, int S, elem element)
    {
    (*matrica)[R * stupaca + S] = element;
    }

int definirajMatricu(elem R, elem S, elem** matrica)
    {
    *matrica = (elem *) malloc(R * S * sizeof(elem));
    if(*matrica == NULL)
        {
        printf("matrica nije uspjesno definirana\n");
        return -1;
        }
    return 1;
    }

void izmjeniPodatakMatrice(int R, int S, elem** matrica, elem value)
    {
    int i = 0;
    int j = 0;
    (*matrica)[(R * STU) + S] = value;
    return;
    }

void popuniDinamickuMatricu8_16(elem** matrica, elem podaci[RED][16])
    {
    int i = 0;
    int j = 0;
    elem podatak = 0;
    for(i = 0; i < RED; i++)
        {
        for(j = 0; j < STU; j++)
            {
            podatak = podaci[i][j];
            (*matrica)[i * STU + j] = podatak;
            }
        }
    }

void ispisMatrice(elem** matrica, int R, int S)
    {
    int i = 0;
    int j = 0;
    for(i = 0; i < R; i++)
        {
        for(j = 0; j < S; j++)
            {
            printf("%d ", (*matrica)[i * (S) + j]);
            }
        printf("\n");
        }
    printf("\n");
    }

void dodajRedakUMatricu(byte znak, elem** matrica)
    {
    int i = 0;
    for(i = 0; i < RED; i++)
        {
        elem bit = (elem)((znak >> (RED - 1 - i)) & 0x1);
        izmjeniPodatakMatrice(0, i, matrica, bit);
        }
    }

byte izRetkaMatriceUChar(elem** matrica)
    {
    byte rezultat = 0;
    int i = 0;
    for(i = 0; i < RED; i++)
        {
        elem bit = getElementMatrice(matrica, 1, RED, 0, i);
        rezultat = (rezultat << 1) | (bit & 0x1);
        }
    return rezultat;
    }

void printBinary(byte podatak)
    {
    int i = 0;
    for(i = 0; i < RED; i ++)
        {
        elem bin = (podatak >> (RED - 1 - i)) & 0x1;
        printf("%u", bin);
        }
    printf("\n");
    return;
    }

void transponirajMatricu(elem** glavnaMatrica, int Rg, int Sg, elem** transponiranaMatrica)
    {
    int i = 0;
    int j = 0;
    for(i = 0; i < Rg; i++)
        {
        for(j = 0; j < Sg; j++)
            {
            elem element = getElementMatrice(glavnaMatrica, Rg, Sg, i, j);
            setElementMatrice(transponiranaMatrica, Sg, Rg, j, i, element);
            }
        }
    return;
    }

int pomnoziMatrice (elem** prva, elem** druga, int prvaR, int prvaC, int drugaR, int drugaC, elem** rezultat)
    {
    int redak = 0;
    int stupac = 0;
    elem suma = 0;
    int zbrajalo = 0;

    /*rezultat ima dimenzije [prvaR][drugaS]*/
    if((prvaC != drugaR))
        {
        printf("dimenzije matrica se ne poklapaju!\n");
        return -1; 
        }
	/*printf("[mnozenje matrica..]\n");*/
    for(redak = 0; redak < prvaR; redak++)
        {
        for(stupac = 0; stupac < drugaC; stupac++)
            {
			suma = 0;
			elem temp = 0;
            for(zbrajalo = 0; zbrajalo < prvaC; zbrajalo++)
                {
                temp = (getElementMatrice(prva, prvaR, prvaC, redak, zbrajalo) * getElementMatrice(druga, drugaR, drugaC, zbrajalo, stupac));
				/*printf("[%d, %d]:%d * [%d, %d]:%d = [%d]\n", redak, zbrajalo,getElementMatrice(prva, prvaR, prvaC, redak, zbrajalo), zbrajalo, stupac, getElementMatrice(druga, drugaR, drugaC, zbrajalo, stupac), temp);*/
                /*suma += prva[redak][zbrajalo] * druga[zbrajalo][stupac];*/
				suma += temp;
                }
			/*printf("-----\n");*/
            setElementMatrice(rezultat, 1, STU, redak, stupac, suma%2);/* % 2U*/
            }
        }
	/*printf("[kraj mnozenja matrica]\n");*/
    return 0;
    }

twoByte kodiranaInformacija(elem ** redakMatrica, int stupaca)
    {
	int i = 0;
    twoByte rezultat;
    rezultat.a = 0;
    rezultat.b = 0;
	
	for(i = 0; i < stupaca/2; i++)
		{
		elem bit = getElementMatrice(redakMatrica, 1, STU, 0, i);
        rezultat.a = (rezultat.a << 1) | (bit & 0x1);
		}
	for(i = stupaca/2; i < stupaca; i++)
		{
		elem bit = getElementMatrice(redakMatrica, 1, STU, 0, i);
        rezultat.b = (rezultat.b << 1) | (bit & 0x1);
		}
	return rezultat;
    }

