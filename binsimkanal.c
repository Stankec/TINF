#include <stdio.h>
#include <stdlib.h>
#define RED 8
#define STU 16

typedef unsigned int elem;
typedef char byte;

typedef struct
    {
    char a;
    char b;
    }
twoByte;

void printBinary(elem podatak)
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


int uniform_distribution(int rangeLow, int rangeHigh)
	{
    double myRand = rand()/(1.0 + RAND_MAX); 
    int range = rangeHigh - rangeLow + 1;
    int myRand_scaled = (myRand * range) + rangeLow;
    return myRand_scaled;
	}

int jeNije(double err)
	{
	return uniform_distribution(1000, 2000) < (1000 + err * 1000);
	}	
	
int main(int argc, char *argv[])
    {
    double errRate;
	time_t vrijeme;
	FILE* ulaznaDatoteka;
	FILE* izlaznaDatoteka;
	int velicinaDat;
	byte* informacija;
	byte* izlaznaInformacija;
	int i;
	int brojilo = 0;
	int j;
	int broj_zapisanih;
	double postotak;
	
	srand((unsigned) time(&vrijeme));
	
    if(argc != 4)
        {
        printf("krivi broj argumenata!\nargumenti moraju biti u obliku:\n\nprogram.exe ulazna izlazna err_rate");
        exit(-1);
        }

    ulaznaDatoteka = fopen(argv[1], "rb");
    izlaznaDatoteka = fopen(argv[3], "wb");
	errRate = atof(argv[2]);
	
	printf("bit error rate: %f\n", errRate);
    
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
    printf("...uspjeh! Citam stream i vrsim smetnju nad njime...\n");
    izlaznaInformacija = (byte *) malloc(sizeof(byte));
    
    if(izlaznaInformacija == NULL)
        {
        printf("nije moguce rezervirati memoriju za izlaznu datoteku!\n");
        exit(-1);
        }
    printf("rezervirano [%d]B za izlaznu datoteku\n", velicinaDat);
    /* ////////////////////////////////// */
    /* ////////////////////////////////// */
    /* ////////////////////////////////// *//* ////////////////////////////////// Tu se odvija glavni dio programa*/
	printf("BER: %f\n", errRate);
/*	for(i = 0; i < 100; i++) 
		{
		printf("%d", jeNije(errRate));
		}
	getchar();*/
    printf("\n#######################################################################################\n");
	

    for(i = 0; i < velicinaDat; i++)
        {
		int did = 0;
		byte izlaz = informacija[i];
		if(jeNije(errRate))
			{
			for(j = 0; j < 8; j++)
				{
				
				if(jeNije(errRate) * jeNije(errRate))
					{
					printf("radim gresku na [%d] bajtu\n", i);
					izlaz = (izlaz ^ (0x1 << j));
					printf("  originalni bajt:\n  ");
					printBinary(informacija[i]);
					printf("  pokvareni bajt:\n  ");
					printBinary(izlaz);
					did = 1;
					}
				}
		}
		if(did == 1) brojilo++;
		informacija[i] = izlaz;
        }
	printf("#######################################################################################\n");

	postotak = ((double) brojilo)/((double) velicinaDat);
	postotak *= 100;
	printf("ucinjena greska na %d/%d (%6.3f od 100) bitova\n", brojilo, velicinaDat, postotak);
	printf("uspjesno posumljeno, zapisivanje u izlaznu binarnu datoteku\n");
	broj_zapisanih = fwrite(informacija, sizeof(byte), velicinaDat, izlaznaDatoteka);
	
	if(broj_zapisanih != velicinaDat)
		{
		printf("zapisano samo [%d] elemenata u izlaznu datoteku :( (greska!)\n", broj_zapisanih);
		exit(-1);
		}
	printf("uspjesno zapisano [%d] zapisa u datoteku!", broj_zapisanih);

    printf("\n-----\n[kraj!]\n");
	fclose(izlaznaDatoteka);
    free(informacija);
	free(izlaznaInformacija);
    return 0;
    }

