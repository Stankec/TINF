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

void dodaj2retka(elem** src, elem** src2, elem** dest, int redak);
int getGreskaFromSindrom(elem** sindrom, elem** greska, elem** tablica1, elem** tablica2);
void generiraj2gresniSindrom(elem** matricaHt, elem** greskaX2);
void generiraj1gresniSindrom(elem** matricaHt, elem** greskaX1);
int pomnoziMatrice (elem** prva, elem** druga, int prvaR, int prvaC, int drugaR, int drugaC, elem** rezultat);
void transponirajMatricu(elem** glavnaMatrica, int Rg, int Sg, elem** transponiranaMatrica);
void setElementMatrice(elem** matrica, int redaka, int stupaca, int R, int S, elem element);
elem getElementMatrice(elem** matrica, int redaka, int stupaca, int R, int S);
void popuniDinamickuMatricu8_16(elem** matrica, elem podaci[RED][16]);
void izmjeniPodatakMatrice(int R, int S, elem** matrica, elem value);
void dodaj2RedakUMatricu(byte znak1, byte znak2, elem** matrica);
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
	elem* sindromMat = NULL;
	elem* greskaX2 = NULL;
	elem* greskaX1 = NULL;
	elem* kodGreske = NULL;
    byte ulazni;
    int ulazniInt;
    elem osnovniKod;
    long int velicinaDat = 0;
    FILE* ulaznaDatoteka;
    FILE* izlaznaDatoteka;
    twoByte* informacija;
    byte* izlaznaInformacija;
	int broj_zapisanih;
	twoByte primjer;
    /* ////////////////////////////////// */
    /* ////////////////////////////////// */
    /* ////////////////////////////////// */
	definirajMatricu(120, 16 + 8, &greskaX2);
    definirajMatricu(16, 16 + 8, &greskaX1);
    definirajMatricu(RED, STU, &matricaG);
    definirajMatricu(RED, STU, &matricaG_);
    definirajMatricu(RED, STU, &matricaH);
    definirajMatricu(STU, RED, &matricaGt);
	definirajMatricu(1, STU, &kodGreske);
    definirajMatricu(STU, RED, &matricaG_t);
    definirajMatricu(STU, RED, &matricaHt);
    definirajMatricu(1, RED, &ulazniRedak);
    definirajMatricu(1, STU, &kodiraniRedak);
	definirajMatricu(1, STU, &sindromMat);
    
    popuniDinamickuMatricu8_16(&matricaG, G);
    popuniDinamickuMatricu8_16(&matricaG_, G_);
    popuniDinamickuMatricu8_16(&matricaH, H);

    transponirajMatricu(&matricaG, RED, STU, &matricaGt);
    transponirajMatricu(&matricaG_, RED, STU, &matricaG_t);
    transponirajMatricu(&matricaH, RED, STU, &matricaHt);
	
	/*
	printf("H: \n");
    ispisMatrice(&matricaH, RED, STU);
    printf("H: transponirano: \n");
    ispisMatrice(&matricaHt, STU, RED);
    */
	
	printf("generiram matricu za ispravak 1 greske...\n");
	generiraj1gresniSindrom(&matricaHt, &greskaX1);
	printf("generiram matricu za ispravak 2 greske...\n");
	generiraj2gresniSindrom(&matricaHt, &greskaX2);
	printf("uspjesno popunjene tablice pogresaka");
	
	/*printf("jednostruke [sindrom, error]: \n");
    ispisMatrice(&greskaX1, 16, 24);
    printf("dvostruke [sindrom, error]: \n");
    ispisMatrice(&greskaX2, 120, 24);*/
	
	
    /*printf("G: \n");
    ispisMatrice(&matricaG, RED, STU);
    printf("G transponirano: \n");
    ispisMatrice(&matricaGt, STU, RED);*/
    

    
    /*printf("G_: \n");
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
    informacija = (twoByte*) malloc(velicinaDat);
    fseek(ulaznaDatoteka, 0L, SEEK_SET);
    
    if(informacija == NULL)
        {
        printf("nije moguce rezervirati toliko memorije za datoteku!\n");
        exit(-1);
        }

    printf("[%ld]B memorije uspjesno alocirano\n", velicinaDat);
	primjer.a = 0x7;
	primjer.b = 0x2;
    informacija[velicinaDat/2 - 1] = primjer;
    printf("uspjesno testiran range alocirane memorije\n");
    
    if(!fread(informacija, velicinaDat, 1, ulaznaDatoteka))
        {
        printf("neuspjelo citanje informacije iz datoteke!\n");
        exit(-1);
        }

    printf("ulazna datoteka ucitana u memoriju!\nzatvaram datoteku....\n");
    fclose(ulaznaDatoteka);
    printf("...uspjeh! Citam i dekodiram stream...\n");
    izlaznaInformacija = (byte *) malloc(velicinaDat / 2);
    
    if(izlaznaInformacija == NULL)
        {
        printf("nije moguce rezervirati memoriju za izlaznu datoteku!\n");
        exit(-1);
        }
    printf("rezervirano [%d]B za izlaznu datoteku\n", velicinaDat / 2);
    /* ////////////////////////////////// */
    /* ////////////////////////////////// */
    /* ////////////////////////////////// *//* ////////////////////////////////// Tu se odvija glavni dio programa*/
    
    printf("velicina: %d\n", velicinaDat / 2);
    for(i = 0; i < velicinaDat / 2; i++)
        {
		twoByte ulaz;
        ulaz = informacija[i];
		
		dodaj2RedakUMatricu(ulaz.a, ulaz.b, &kodiraniRedak);
		pomnoziMatrice (&kodiraniRedak, &matricaHt, 1, 16, 16, 8, &sindromMat);
		
		if(postojiGreska(&sindromMat))
			{
			twoByte greska;
			greska.a = (byte) 0x0;
			greska.b = (byte) 0x0;
			int code = getGreskaFromSindrom(&sindromMat, &kodGreske, &greskaX1, &greskaX2);
			printf("greska u prijenosu!! Greska je prisutna na bajtu [%d ili %d] , pokusaj ispravka\n", i * 2, i * 2 + 1);
			/*0 1 1 1 0 0 1 1*/
			if(code == 1)
				{
				printf("dogodila se jednostruka pogreska na bajtu\n");
				greska = kodiranaInformacija(&kodGreske, 16);
				}
			if(code == 2)
				{
				printf("dogodila se dvostruka pogreska na bajtu\n");
				greska = kodiranaInformacija(&kodGreske, 16);
				}
			if(code == 0)
				{
				printf("nije moguc oporavak od greske...(3 ili vise gresaka)\n");
				}
			printf("sindrom: \n");
			ispisMatrice(&sindromMat, 1, 8);
			printf("redak koji se cita:\n");
			ispisMatrice(&kodiraniRedak, 1, STU);
			printf("greske na mjestu:\n");
			ispisMatrice(&kodGreske, 1, STU);
			printf("procitani podatak:\n");
			printBinary(ulaz.a);
			printBinary(ulaz.b);
			printf("ispravljeni podatak:\n");
			ulaz.a = (byte) (ulaz.a ^ (greska.a));
			ulaz.b = (byte) (ulaz.b ^ (greska.b));
			printf("ispravljeni podatak:\n");
			printBinary(ulaz.a);
			printBinary(ulaz.b);
			}
        izlaznaInformacija[i] = ulaz.a;
        }
	printf("uspjesno dekodirano, zapisivanje u izlaznu binarnu datoteku\n");
	broj_zapisanih = fwrite(izlaznaInformacija, sizeof(byte), velicinaDat / 2, izlaznaDatoteka);
	
	if(broj_zapisanih != (velicinaDat / 2))
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
    free(matricaG_t);
	free(izlaznaInformacija);
    free(matricaHt);
    free(informacija);
    return 0;
    }

/* ////////////////////////////////// *//* ////////////////////////////////// */



void generiraj2gresniSindrom(elem** matricaHt, elem** greskaX2)
	{
	elem* redakGreska = NULL;
	elem* redakSindrom = NULL;
	int greska = 0;
	int brojilo = 0;
	int brj = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	int dodaoRedaka = 0;
	definirajMatricu(1, 16, &redakGreska);
	definirajMatricu(1, 8, &redakSindrom);

	for(i = 0; i < STU; i++)
		{
		for(j = i + 1; j < STU; j++)
			{
			if(i != j)
				{
				
				byte lijevi = (byte) 0;
				byte desni = (byte) 0;
				/*printf("i: %d, j:%d\n", i, j);/*/
				if(i < 8)
					{
					lijevi = (byte) (0x1 << (7 - i));
					}
				else
					{
					desni = (byte) (0x1 << (15 - i));
					}
				if(j < 8)
					{
					lijevi = lijevi | ((byte) (0x1 << (7 - j)));
					}
				else
					{
					desni = desni | ((byte) (0x1 << (15 - j)));
					}
				/*printf("dodajem rekte u matricu, jedan za drugim po stupcima");*/
				dodaj2RedakUMatricu(lijevi, desni, &redakGreska);
				/*printf("sad mnozim taj redak s H transponirano da dobijem sindrom\n");*/
				pomnoziMatrice (&redakGreska, matricaHt, 1, 16, 16, 8, &redakSindrom);

				for(k = 0; k < 24; k++)
					{
					
					if(k < 8)
						{
						elem moj2 = 0U;
						elem moj = getElementMatrice(&redakSindrom, 1, 8, 0, k);
						setElementMatrice(greskaX2, 120, 24, brj, k, moj);
						moj2 = getElementMatrice(greskaX2, 120, 24, brj, k);
						/*printf(" %u(%u)", moj, moj2);*/
						}
					else
						{
						elem moj2 = 0U;
						elem moj = getElementMatrice(&redakGreska, 1, 16, 0, k - 8);
						setElementMatrice(greskaX2, 120, 24, brj, k, moj);
						moj2 = getElementMatrice(greskaX2, 120, 24, brj, k);
						/*printf(" %u(%u)", moj, moj2);*/
						}
					}

				brj++;
				dodaoRedaka++;
				/*getchar();*/
				}
				
			}
		}

	}

void generiraj1gresniSindrom(elem** matricaHt, elem** greskaX1)
	{
	int greska = 0;
	int brojilo = 0;
	int i = 0;
	int j = 0;
	int brj = 0;
	int dodaoRedaka;
	int k = 0;
	elem* redakGreska = NULL;
	elem* redakSindrom = NULL;
	definirajMatricu(1, 16, &redakGreska);
	definirajMatricu(1, 8, &redakSindrom);
	for(i = 0; i < STU; i++)
		{
		byte lijevi = (byte) 0;
		byte desni = (byte) 0;
		
		if(i < 8)
			{
			lijevi = (byte) (0x1 << (7 - i));
			}
		else
			{
			desni = (byte) (0x1 << (15 - i));
			}
		
		dodaj2RedakUMatricu(lijevi, desni, &redakGreska);
		pomnoziMatrice (&redakGreska, matricaHt, 1, 16, 16, 8, &redakSindrom);
		/*ispisMatrice(&redakSindrom, 1, 8);/*/
		/*ispisMatrice(&redakGreska, 1, 16);/*/
		/*dodaj2retka(&redakSindrom, &redakGreska, greskaX1, brojilo++);*/
		
		/*printf("postavljam:");/*/
		for(k = 0; k < 24; k++)
			{		
			if(k < 8)
				{
				elem moj2 = 0U;
				elem moj = getElementMatrice(&redakSindrom, 1, 8, 0, k);
				setElementMatrice(greskaX1, 16, 24, brj, k, moj);
				moj2 = getElementMatrice(greskaX1, 16, 24, brj, k);
				/*printf("%u(%u) ", moj, moj2);/*/
				}
			else
				{
				elem moj2 = 0U;
				elem moj = getElementMatrice(&redakGreska, 1, 16, 0, k - 8);
				setElementMatrice(greskaX1, 16, 24, brj, k, moj);
				moj2 = getElementMatrice(greskaX1, 16, 24, brj, k);
				/*printf(" %u(%u)", moj, moj2);/*/
				}
			}
		/*printf("\ndodao ovo:\n");
		for(k = 0; k < 24; k++)
			{
			elem temp4 = getElementMatrice(greskaX1, 16, 24, brj, k);
			printf("%u ", temp4);
			}
		printf("\n");/*/
		brj++;
		dodaoRedaka++;
		}
		
	}

	
	
int getGreskaFromSindrom(elem** sindrom, elem** greska, elem** tablica1, elem** tablica2)
	{
	int i = 0;
	int j = 0;
	int k = 0;
	int pronasao = 0;
	int p[RED] = {0, 0, 0, 0, 0, 0, 0, 0};
	
	for(i = 0; i < STU; i++)
		{
		for(j = 0; j < RED; j++)
			{
			elem tren = getElementMatrice(tablica1, 16, 24, i, j);
			elem tren2 = getElementMatrice(sindrom, 1, 8, 0, j);
			/*printf("%d %d. provjeravam: %u {tablica gresaka}, %u {sindrom}\n", i, j, tren, tren2);*/
			if(tren != tren2)
				{
				for(k = 0; k < 8; k++) p[k] = 0;
				break;
				}
			else
				{
				p[j] = 1;
				}
			}
		if((p[0] == 1) && (p[1] == 1) && (p[2] == 1) && (p[3] == 1) && (p[4] == 1) && (p[5] == 1) && (p[6] == 1) && (p[7] == 1))
			{
			for(j = 0; j < STU; j++)
				setElementMatrice(greska, 1, 16, 0, j, getElementMatrice(tablica1, 16, 24, i, j+8));
			return 1;
			}
		}
	
	for(k = 0; k < 8; k++) p[k] = 0;
	
	for(i = 0; i < 120; i++)
		{
		for(j = 0; j < RED; j++)
			{
			elem tren = getElementMatrice(tablica2, 120, 24, i, j);
			elem tren2 = getElementMatrice(sindrom, 1, 8, 0, j);
			if(tren != tren2)
				{
				for(k = 0; k < 8; k++) p[k] = 0;
				break;
				}
			else
				{
				p[j] = 1;
				}
			}
		if((p[0] == 1) && (p[1] == 1) && (p[2] == 1) && (p[3] == 1) && (p[4] == 1) && (p[5] == 1) && (p[6] == 1) && (p[7] == 1))
			{
			for(j = 0; j < STU; j++)
				setElementMatrice(greska, 1, 16, 0, j, getElementMatrice(tablica2, 120, 24, i, j+8));
			return 2;
			}
		}
	return 0;
	}

	
void dodaj2retka(elem** src, elem** src2, elem** dest, int redak)
	{
	int i = 0;
	printf("postavljam %d. red na: ", redak);
	for(i = 0; i < (16 + 8); i++)
		{
		if(i < 8)
			{
			setElementMatrice(dest, 120, STU, redak, i, getElementMatrice(src, 1, 8, 0, i));
			printf("%d ", getElementMatrice(src, 1, 8, 0, i));
			}
		else
			{
			setElementMatrice(dest, 120, STU, redak, i, getElementMatrice(src2, 1, 16, 0, i - 8));
			printf("%d ", getElementMatrice(src2, 1, 16, 0, i - 8));
			}
		}
	printf("\n");
	}

int postojiGreska(elem** sindrom)
	{
	int i = 0;
	for(i = 0; i < RED; i++)
		{
		elem s = 0;
		s = getElementMatrice(sindrom, 1, RED, 0, i);
		if(s != ((elem) 0))
			{
			return 1;
			}
		}
	return 0;
	}

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

void dodaj2RedakUMatricu(byte znak1, byte znak2, elem** matrica)
    {
    int i = 0;
	int j = 0;
    for(i = 0; i < RED; i++)
        {
        elem bit = (elem)((znak1 >> (RED - 1 - i)) & 0x1);
        izmjeniPodatakMatrice(0, i, matrica, bit);
        }
	for(j = RED; j < STU; j++)
		{
		i = j - RED;
        elem bit = (elem)((znak2 >> (RED - 1 - i)) & 0x1);
        izmjeniPodatakMatrice(0, RED + i, matrica, bit);
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
        byte bin = (podatak >> (RED - 1 - i)) & 0x1;
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

