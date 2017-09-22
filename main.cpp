
#include <iostream>
#include <cstring>
#include <ctime>
#include <string.h>
# include <fstream>ac
using namespace std;




//desenare
void generareFisier(int bin[])
{
    fstream cod;
    cod.open( "produs.html", ios::out);

    cod << "<!DOCTYPE html>" << endl;
    cod << "<html>" << endl;
    cod << "<body>" << endl;
    cod << "<svg height=\"50\" width=\"200\">" << endl; // Doi pixeli pentru fiecare bara
    int pozx = 10; // De la acest x incep trasarea
    for(int i=0; i<95; i++)
    {
        if(bin[i] == 1) // Se traseaza o linie
            cod << "<line x1=\"" << pozx << "\" y1=\"20\" x2=\"" << pozx << "\" y2=\"50\" style=\"stroke:rgb(0,0,0); stroke-width:2\" />"
                << endl;
        pozx = pozx + 2; // Avans cu 2px, indiferent daca s-a trasat sau nu
    }
    cod << "</svg>" << endl;
    cod << "</body>" << endl;
    cod << "</html>" << endl;
    cod.close();
}


void L(int valoare, int bin[], int poz);
void G(int valoare, int bin[], int poz);
void R(int valoare, int bin[], int poz);


int bin[95];
int poz;
int valoare;
int i;


  int main()
    {
     char codDat[10],denumire[21];
     int lungime;
     int i=0;

      cout << "Introduceti denumirea produsului( max 20 caractere): ";
     // citeste  si spatiile dintre cuvinte
      cin.getline(denumire,21);

      cout << "Introduceti codul produsului( max 9 cifre fara spatii): ";
      cin >> codDat;


   //  Verificare. Numar toate caracterele bune folosind un contor.
   lungime = strlen(codDat);
     while(codDat[i] >= '0' && codDat[i] <= '9' )
        i++;
    if(i != lungime || lungime >9 )
           {
              cout << "Cod eronat: " << codDat << endl;
              cout << "Incearca din nou !! " << endl;
               return 0;
           }

 // generez sirul de caractere '7' necesar formãrii codului.

   char sirSapte[9] = "";  //  sirul initial este vid
   if(lungime < 9)
    {
         int j;
   for(j=0; j<9-lungime; j++)
     sirSapte[j] = '7';   //  Limitez sirSapte la dreapta adaugandu-i un caracter '\0'
     sirSapte[j] = '\0'; // daca am scris <9 cifre -intra automat cifra 7 in spatii libere pina la 9 cifre
     }

   /* trebuisc  unite sirurile  sir codDat si  sirSapte-
    dar codul final, de 13 cifre, are în faţă şirul "594",  codul României */

   // declar sirul 594  codul Romaniei
    char codRO[] = "594";

// repet funcţia de unire a două şiruri - strcat(),
   char ean13[13];  //  13 caractere, 12+1
   strcpy(ean13, codRO);
   strcat(ean13, sirSapte);
   strcat(ean13, codDat); //  Verific pana aici
   cout << "Primele 12 caractere sunt : " << ean13 << endl;

   // cele 12 caractere obţinute trebuie să devină valori numerice.
   // Convertim caracterele in valori numerice intregi (int)

   int  nean13[13]; // Pentru rezultate
   for(i=0; i<12; i++)
   nean13[i] = ean13[i] - '0';
  cout << "conversia celor 12 caractere in nr   : " << nean13[i] << endl;

  // Calculul cifrei de control
  int s1,s2,S;
  s1 = s2 = 0;
   for(i=0; i<12; i=i+2)
     {
          s1 =s1 + nean13[i];
       s2 =s2 + nean13[i+1];
   }
   S = s1 + 3*s2;
    nean13[12] = 10 - S%10;  //  Cifra de control
       cout<<"cifra de control este: "<< nean13[12]<<endl;

       cout<<"codul de bare este : "  <<ean13 <<nean13[i]<<endl;


 // construire sir b{95]

int b[95]; // se codifica inceputul:101
b[0]=b[2]=1;
b[1]=0;// se codifica prima parte a codului(6 caractere, nean13[1] la nean13[6])
L(nean13[1], b, 3);
G(nean13[2], b, 10);
G(nean13[3], b, 17);
L(nean13[4], b, 24);
L(nean13[5], b, 31);
G(nean13[6], b, 38);
// se codifica zona de separare din mijloc 01010;
b[45]=b[47]=b[49]=0;
b[46]=b[48]=1;
// se codifica a doua parte a codului de la nean13[7] la nean13[12];
// pentru toate se apeleaza functia R();
for(i=0; i<6; i++)
R(nean13[7+i], b, 50+i*7);
// se codifica partea finala a codului, 101;
b[92]=b[94]=1;
b[93]= 0;
cout << "Sirul de 95 de cifre binare este:  ";
for (i=0; i<95; i++)
cout << b[i];

 generareFisier(b);

        return 0;
}

void L(int valoare, int bin[], int poz)
{
  switch(valoare)
    {  case 0: //  0001101
           bin[poz]=bin[poz+1]=bin[poz+2]=bin[poz+5]=0;
           bin[poz+3]=bin[poz+4]=bin[poz+6]=1;
           break;
       case 1: //  0011001
           bin[poz]=bin[poz+1]=bin[poz+4]=bin[poz+5]=0;
           bin[poz+2]=bin[poz+3]=bin[poz+6]=1;
           break;
       case 2: //  0010011
           bin[poz]=bin[poz+1]=bin[poz+3]=bin[poz+4]=0;
           bin[poz+2]=bin[poz+5]=bin[poz+6]=1;
           break;
       case 3: //  0111101
           bin[poz]=bin[poz+5]=0;
           bin[poz+1]=bin[poz+2]=bin[poz+3]=bin[poz+4]=bin[poz+6]=1;
           break;
       case 4: //  0100011
           bin[poz]=bin[poz+2]=bin[poz+3]=bin[poz+4]=0;
           bin[poz+1]=bin[poz+5]=bin[poz+6]=1;
           break;
       case 5: //  0110001
           bin[poz]=bin[poz+3]=bin[poz+4]=bin[poz+5]=0;
           bin[poz+1]=bin[poz+2]=bin[poz+6]=1;
           break;
       case 6: //  0101111
           bin[poz]=bin[poz+2]=0;
           bin[poz+1]=bin[poz+3]=bin[poz+4]=bin[poz+5]=bin[poz+6]=1;
           break;
       case 7: //  0111011
           bin[poz]=bin[poz+4]=0;
           bin[poz+1]=bin[poz+2]=bin[poz+3]=bin[poz+5]=bin[poz+6]=1;
           break;
       case 8: //  0110111
           bin[poz]=bin[poz+3]=0;
           bin[poz+1]=bin[poz+2]=bin[poz+4]=bin[poz+5]=bin[poz+6]=1;
           break;
       case 9: //  0001011
           bin[poz]=bin[poz+1]=bin[poz+2]=bin[poz+4]=0;
           bin[poz+3]=bin[poz+5]=bin[poz+6]=1;
           break;
    }
}

void G(int valoare, int bin[], int poz)
{
    switch(valoare)
    {  case 0: //  0100111
           bin[poz]=bin[poz+2]=bin[poz+3]=0;
           bin[poz+1]=bin[poz+4]=bin[poz+5]=bin[poz+6]=1;
           break;
       case 1: //  0110011
           bin[poz]=bin[poz+3]=bin[poz+4]=0;
           bin[poz+1]=bin[poz+2]=bin[poz+5]=bin[poz+6]=1;
           break;
       case 2: //  0011011
           bin[poz]=bin[poz+1]=bin[poz+4]=0;
           bin[poz+2]=bin[poz+3]=bin[poz+5]=bin[poz+6]=1;
           break;
       case 3: //  0100001
           bin[poz]=bin[poz+2]=bin[poz+3]=bin[poz+4]=bin[poz+5]=0;
           bin[poz+1]=bin[poz+6]=1;
           break;
       case 4: //  0011101
           bin[poz]=bin[poz+1]=bin[poz+5]=0;
           bin[poz+2]=bin[poz+3]=bin[poz+4]=bin[poz+6]=1;
           break;
       case 5: //  0111001
           bin[poz]=bin[poz+4]=bin[poz+5]=0;
           bin[poz+1]=bin[poz+2]=bin[poz+3]=bin[poz+6]=1;
           break;
       case 6: //  0000101
           bin[poz]=bin[poz+1]=bin[poz+2]=bin[poz+3]=bin[poz+5]=0;
           bin[poz+4]=bin[poz+6]=1;
           break;
       case 7: //  0010001
           bin[poz]=bin[poz+1]=bin[poz+3]=bin[poz+4]=bin[poz+5]=0;
           bin[poz+2]=bin[poz+6]=1;
           break;
       case 8: //  0001001
           bin[poz]=bin[poz+1]=bin[poz+2]=bin[poz+4]=bin[poz+5]=0;
           bin[poz+3]=bin[poz+6]=1;
           break;
       case 9: //  0010111
           bin[poz]=bin[poz+1]=bin[poz+3]=0;
           bin[poz+2]=bin[poz+4]=bin[poz+5]=bin[poz+6]=1;
           break;
    }
}

void R(int valoare, int bin[], int poz)
{
    switch(valoare)
    { case 0: //  1110010
           bin[poz+3]=bin[poz+4]=bin[poz+6]=0;
           bin[poz]=bin[poz+1]=bin[poz+2]=bin[poz+5]=1;
           break;
       case 1: //  1100110
           bin[poz+2]=bin[poz+3]=bin[poz+6]=0;
           bin[poz]=bin[poz+1]=bin[poz+4]=bin[poz+5]=1;
           break;
       case 2: //  1101100
           bin[poz+2]=bin[poz+5]=bin[poz+6]=0;
           bin[poz]=bin[poz+1]=bin[poz+3]=bin[poz+4]=1;
           break;
       case 3: //  1000010
           bin[poz+1]=bin[poz+2]=bin[poz+3]=bin[poz+4]=bin[poz+6]=0;
           bin[poz]=bin[poz+5]=1;
           break;
       case 4: //  1011100
           bin[poz+1]=bin[poz+5]=bin[poz+6]=0;
           bin[poz]=bin[poz+2]=bin[poz+3]=bin[poz+4]=1;
           break;
       case 5: //  1001110
           bin[poz+1]=bin[poz+2]=bin[poz+6]=0;
           bin[poz]=bin[poz+3]=bin[poz+4]=bin[poz+5]=1;
           break;
       case 6: //  1010000
           bin[poz+1]=bin[poz+3]=bin[poz+4]=bin[poz+5]=bin[poz+6]=0;
           bin[poz]=bin[poz+2]=1;
           break;
       case 7: //  1000100
           bin[poz+1]=bin[poz+2]=bin[poz+3]=bin[poz+5]=bin[poz+6]=0;
           bin[poz]=bin[poz+4]=1;
           break;
       case 8: //  1001000
           bin[poz+1]=bin[poz+2]=bin[poz+4]=bin[poz+5]=bin[poz+6]=0;
           bin[poz]=bin[poz+3]=1;
           break;
       case 9: //  1110100
           bin[poz+3]=bin[poz+5]=bin[poz+6]=0;
           bin[poz]=bin[poz+1]=bin[poz+2]=bin[poz+4]=1;
           break;
    }
}

















