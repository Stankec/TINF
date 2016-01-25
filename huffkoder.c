#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
char buffer;

struct cvor {
	int otac;
	int frekvencija;
	int checked;
	int vecisin;
	int manjisin;
};
typedef struct cvor p;

void dodaj(char* ispis, char znak){
    int i, duljina= strlen(ispis);
    for(i=duljina;i>=0;i--){
        ispis[i+1]=ispis[i];
    }
    ispis[0]=znak;
}

int main(int argc, char *argv[]) {
int duljina=256, j, t, daj;
char znak, buffer=0, mjesto=0;
char ispis[256]={'\0'};
char kod[256][256]={{'\0'}};
p *polje;
int vrijednosti[8]={128, 64, 32, 16, 8, 4, 2 ,1};
int index1, index2;
int najmanji1, najmanji2;
char pomocna[3]={'\r','\n', '\0'};
int i, tata, size, pom;
FILE *ulTok, *izlaz;
FILE *out = fopen(argv[2], "wb");
unsigned char * tekst =NULL;

ulTok = fopen (argv[1], "rb");
izlaz = fopen (argv[3], "wb");

if(ulTok==NULL){
    printf("nije ucitana datoteka 1");
    return 1;
}
if(out==NULL){
    printf("nije ucitana datoteka 2");
    return 1;
}
if(izlaz==NULL){
    printf("nije ucitana datoteka 3");
    return 1;
}
fseek(ulTok, 0, SEEK_END);
size = ftell(ulTok);
tekst = (unsigned char*)malloc(size+1);
polje = (p*)malloc(sizeof(p)*265*3+1);
for(i=0;i<265*2;i++){
    polje[i].frekvencija=0;
    polje[i].checked=0;
    polje[i].otac=-1;
    polje[i].manjisin=-1;
    polje[i].vecisin=-1;
}

for(i=256;i<265*2;i++){
    polje[i].checked=99;
}
fseek(ulTok, 0, SEEK_SET);
fread(tekst,sizeof(char)*size,1,ulTok);
for(i=0;i<size;i++){
    polje[tekst[i]].frekvencija++;
}

while(1){
    najmanji1=999999999;
    najmanji2=999999999;
    index1=-1;
    index2=-1;
    for(i=0;i<260*2;i++){
        if(polje[i].checked!=0) continue;
        if(polje[i].frekvencija<najmanji1){
            index1=i;
            najmanji1=polje[i].frekvencija;
            continue;
        }
    }
    polje[index1].checked=1;

    for(i=0;i<260*2;i++){
        if(polje[i].checked!=0) continue;
        if(polje[i].frekvencija<najmanji2){
            index2=i;
            najmanji2=polje[i].frekvencija;
            continue;
        }
    }


    polje[index2].checked=1;
    if((index1==-1)||(index2==-1)){
        break;
    }
    polje[index1].otac=duljina;
    polje[index2].otac=duljina;
    polje[duljina].checked=0;
    polje[duljina].frekvencija=najmanji1+najmanji2;
    polje[duljina].manjisin=index1;
    polje[duljina].vecisin=index2;
    duljina++;
}


i=0;
while(i<256){
    ispis[0]='\0';
    pom=i;
    while(1){
        tata=polje[pom].otac;
        if(tata==-1){
            break;
        }
        if(polje[tata].vecisin==pom){
            dodaj(ispis, '1');
        }
        else if (polje[tata].manjisin==pom){
            dodaj(ispis, '0');
        }
        pom=tata;
    }
    strcpy(kod[i], ispis);
    /*printf("%d\t %d \t%s\n", polje[i].frekvencija, i, ispis);*/
    strcat(ispis, pomocna);
    fwrite(ispis, sizeof(char)*strlen(ispis), 1, out);
    i++;
}
/* char znak, daj, buffer=0, mjesto=0; */
for(i=0;i<size;i++){
    znak=tekst[i];
    t=strlen(kod[znak]);
    for(j=0;j<t;j++){
        daj=1;
        if((kod[znak][j])=='0') daj=0;
        buffer+=vrijednosti[mjesto]*daj;
        mjesto++;
        if(mjesto==8){
            mjesto=0;
            fwrite(&buffer, sizeof(char), 1, izlaz);
            buffer=0;
        }
    }
}
if(mjesto!=0){
    fwrite(&buffer, sizeof(char), 1, izlaz);
}

free(tekst);
free(polje);

fclose(ulTok);
fclose(izlaz);
fclose(out);
return 0;
}
