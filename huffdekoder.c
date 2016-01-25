#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

void dodaj(char* ispis, char znak){
    int i, duljina= strlen(ispis);
    for(i=duljina;i>=0;i--){
        ispis[i+1]=ispis[i];
    }
    ispis[0]=znak;
}

int main(int argc, char *argv[]) {
int size, i, j=0, k=0, l;
FILE *hufftablica, *ulazna, *izlazna;
char kod[256][256]={{'\0'}};
char dekodirano[256][9];
unsigned char* tekst, znak;
char ispis[1000]={'\0'};
char pomocno[256], *ispisi;
int brojac, max, pronasao;

hufftablica=fopen(argv[1], "rb");
ulazna=fopen(argv[2], "rb");
izlazna=fopen(argv[3], "wb");

fseek(hufftablica, 0, SEEK_END);
size = ftell(hufftablica);
tekst = (unsigned char*)malloc(size+1);
fseek(hufftablica, 0, SEEK_SET);
fread(tekst,sizeof(char)*size,1,hufftablica);

for(i=0;i<256;i++){
    j=0;
    while(tekst[k]!='\r'){
        kod[i][j]=tekst[k];
        k++;
        j++;
    }
    k++;
    k++;
}
for(i=0;i<256;i++){
        l=i;
    for(j=0;j<8;j++){
        if(l%2==0){
            dodaj(dekodirano[i], '0');
        }
        else{
            dodaj(dekodirano[i], '1');
        }
        l=l/2;
    }
}

fseek(ulazna, 0, SEEK_END);
size = ftell(ulazna);
fseek(ulazna, 0, SEEK_SET);

/*ispis[1000], dekodirano[256][9], brojac, pomocno, pronasao */
for(i=0;i<size;){
    if(ispis[0]=='\0'){
        i++;
        fread(&znak,sizeof(char),1,ulazna);
        strcpy(ispis, dekodirano[(int)znak]);
    }
    brojac=1;
    max=strlen(ispis);
    pronasao=0;
    while(1){
        if(brojac-max==-1){
            fread(&znak,sizeof(char),1,ulazna);
            i++;
            strcat(ispis, dekodirano[(int)znak]);
            max+=8;
        }
        strncpy(pomocno, ispis, brojac);
        pomocno[brojac]='\0';

        for(j=0;j<256;j++){
            if(strcmp(pomocno, kod[j])==0){
                pronasao=1;
                fwrite(&j, sizeof(char), 1, izlazna);
                strcpy(ispis, &ispis[brojac]);
                break;
            }
        }
        brojac++;
        if(pronasao==1) break;
    }
}

max=strlen(ispis);
ispisi=ispis;
if(ispis[0]!='\0'){
    brojac=1;
    for(i=0;i<max;i++){
        strncpy(pomocno, ispisi, brojac);
        pomocno[brojac]='\0';
        for(j=0;j<256;j++){
            if(strcmp(pomocno, kod[j])==0){
                fwrite(&j, sizeof(char), 1, izlazna);
                ispisi=&ispisi[brojac];
                brojac=0;
                break;
            }
        }
        brojac++;
    }
}
fclose(izlazna);
fclose(ulazna);
fclose(hufftablica);
return 0;
}

