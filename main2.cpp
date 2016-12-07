#include<iostream>
#include<cstring>
#include<fstream>

using namespace std;

const unsigned int MAX_T=26; 
const int MAX_N=256;
const int MAX_K=3;
const int MAX_F=9; //

struct Szyfry
{
    char tablica_abc[MAX_T];
    char tablica_abc1_temp[MAX_T];
    char tablica_abc2_temp[MAX_T];
    char tablica_abc3_temp[MAX_T];
    char tablica_1[MAX_T];
    char tablica_2[MAX_T];
    char tablica_3[MAX_T]; 
};

struct Liczniki            // struktura sk³adaj¹ca siê z ze zmniennych, które zliczaj¹ obroty poszczególnych tablic
{
     int licznik_1;
     int licznik_2;
     int licznik_3;
};


 void wprowadz_napis(char *napis, int *dl_napisu);
 void klucz_na_licznik(char klucz_s, int &licznik_s, const Szyfry Szyfr);
 void wprowadz_klucz(char *klucz, Liczniki &Licznik,Szyfry Szyfr);
 void duze_litery(char *napis, const int dl_napisu);
 void polskie_zmien(char *napis, const int dl_napisu);
 void skroc_liczniki(Liczniki &Licznik);
 void ustaw_tablice(int licznik_s, char *tablica_s);
 void szyfruj_tablice(char *napis, const char *tablica_abc_temp, const char *tablica_s, int nr_n);
 void szyfruj_cale(char *napis, const int dl_napisu, Szyfry &Szyfr, Liczniki &Licznik);
 void pokaz_napis(const char* napis);
 
 
 void czysc_ekran()
{
     system("cls");
}

 void wprowadz_napis(char *napis, int &dl_napisu)
 {
     cout << "Wprowadz napis: ";
	cin >> napis;
     dl_napisu = strlen(napis);
	duze_litery(napis,dl_napisu);
	polskie_zmien(napis,dl_napisu);
	cout<<"Napis po zmianie malych liter i polskich znakow: "<<napis<<endl;
 }
 
void pokaz_liczniki(const Liczniki Licznik)
{
     cout<<"Licznik 1: "<<Licznik.licznik_1<<endl;
     cout<<"Licznik 2: "<<Licznik.licznik_2<<endl;
     cout<<"Licznik 3: "<<Licznik.licznik_3<<endl;
     cout<<endl;
}

void pokaz_tablice(const Szyfry Szyfr)
{    for(int i=0;i<MAX_T;i++)
     cout<<Szyfr.tablica_abc1_temp[i];
     cout<<endl;
     for(int i=0;i<MAX_T;i++)
     cout<<Szyfr.tablica_abc2_temp[i];
     cout<<endl;
     for(int i=0;i<MAX_T;i++)
     cout<<Szyfr.tablica_abc3_temp[i];
     cout<<endl;
}

 void klucz_na_licznik(char klucz_s, int &licznik_s, const Szyfry Szyfr)
 {
           for(int j=0;j<MAX_T;j++)
           {
                if(klucz_s==Szyfr.tablica_abc[j]) licznik_s=j;
           }           
 }
 
 void wprowadz_klucz(char *klucz, Liczniki &Licznik,Szyfry Szyfr)
 {
      cout<<"Wprowadz klucz szyfrowania: ";
	 cin>>klucz;
      duze_litery(klucz,MAX_K);
      
	 klucz_na_licznik(klucz[0],Licznik.licznik_1,Szyfr);
	 klucz_na_licznik(klucz[1],Licznik.licznik_2,Szyfr);
	 klucz_na_licznik(klucz[2],Licznik.licznik_3,Szyfr);
	
     // pokaz_liczniki(Licznik);	 
 }
 
 
void duze_litery(char *napis, const int dl_napisu)
{
     for(int i=0; i<dl_napisu; i++)
     {
        napis[i]=toupper(napis[i]);
     }
}



void polskie_zmien(char *napis, const int dl_napisu) 
{  
 for(int i=0;i<dl_napisu;i++)    
 {
 	int kod=napis[i];
      switch(kod)
      {
      	case -91: napis[i]='A'; //ma³e polskie litery
      	          break;
          case -87: napis[i]='E';
      	          break;
      	case -122: napis[i]='C';
      	          break;
		case -28: napis[i]='N';
      	          break;
		case -120: napis[i]='L';
      	          break;
		case -66: napis[i]='Z';
      	          break;
		case -85: napis[i]='Z';
      	          break;
		case -94: napis[i]='O';
      	          break;
		case -104: napis[i]='S';
      	          break;	
		case -92: napis[i]='A';  // duze polskie litery
      	          break;
          case -88: napis[i]='E';
      	          break;
      	case -113: napis[i]='C';
      	          break;
		case -29: napis[i]='N';
      	          break;
		case -99: napis[i]='L';
      	          break;
		case -67: napis[i]='Z';
      	          break;
		case -115: napis[i]='Z';
      	          break;
		case -32: napis[i]='O';
      	          break;
		case -105: napis[i]='S';
      	          break;																		                 
	  }
 } 
}


void skroc_liczniki(Liczniki &Licznik)
{
     Licznik.licznik_1=Licznik.licznik_1%MAX_T;
     Licznik.licznik_2=Licznik.licznik_2%MAX_T;
     Licznik.licznik_3=Licznik.licznik_3%MAX_T;
}



void ustaw_tablice(int licznik_s, char *tablica_s, const char *tablica_wzor)
{
     for(int i=0;i<MAX_T;i++)
     tablica_s[i]=tablica_wzor[i];
     
     for(int i=0;i<licznik_s;i++)
     {
          char bufor=tablica_s[0];   
          for(int j=0;j<MAX_T;j++)
          {
          if(j<MAX_T-1)  tablica_s[j]=tablica_s[j+1]; 
             else if (j==MAX_T-1) tablica_s[j]=bufor; 
          }
     }
}



 void przesun_tablice(const int licznik_s, const int licznik_temp, char *tablica_s)
{
      for(int i=0;i<licznik_s-licznik_temp;i++)
     {
          char bufor=tablica_s[0];   
          for(int j=0;j<MAX_T;j++)
          {
          if(j<MAX_T-1)  tablica_s[j]=tablica_s[j+1]; 
             else if (j==MAX_T-1) tablica_s[j]=bufor; 
          }
     }
     
} 



void szyfruj_tablice(char *napis, const char *tablica_abc_temp, const char *tablica_s, int nr_n) // definicja funkcji szyfruj¹cej znaki w tablicach    
{    
   char bufor=napis[nr_n];   
   for(int nr_t=0; nr_t<MAX_T; nr_t++) //nr_t -> numer znaku tablicy szyfrowania
   {                                                /// zrobic funkcje, która przesuwa kopie tablicy_abc
   	if (napis[nr_n]==tablica_abc_temp[nr_t])       
	{
	     
	     bufor=tablica_s[nr_t]; 
	}
   }
   napis[nr_n]=bufor;
}



void szyfruj_cale(char *napis, const int dl_napisu, Szyfry &Szyfr, Liczniki &Licznik)
{
     Liczniki Licznik_temp;
     skroc_liczniki(Licznik);
     
     ustaw_tablice(Licznik.licznik_1,Szyfr.tablica_abc1_temp,Szyfr.tablica_abc); // Ustawianie pocz¹tkowego przesuniêcia tablic dla zadanego klucza szyfrowania
     ustaw_tablice(Licznik.licznik_2,Szyfr.tablica_abc2_temp,Szyfr.tablica_abc);
     ustaw_tablice(Licznik.licznik_3,Szyfr.tablica_abc3_temp,Szyfr.tablica_abc);
      
      for(int nr_n=0; nr_n<dl_napisu; nr_n++)  //nr_n -> numer znaku napisu
      {     
     // pokaz_tablice(Szyfr);//
      
      Licznik_temp=Licznik;
      
      Licznik.licznik_1++;
      if(Licznik.licznik_1==MAX_T) Licznik.licznik_2++;
      if(Licznik.licznik_2==MAX_T) Licznik.licznik_3++; 
      
     szyfruj_tablice(napis,Szyfr.tablica_abc1_temp,Szyfr.tablica_1,nr_n);
     szyfruj_tablice(napis,Szyfr.tablica_abc2_temp,Szyfr.tablica_2,nr_n);
     szyfruj_tablice(napis,Szyfr.tablica_abc3_temp,Szyfr.tablica_3,nr_n);
     
     przesun_tablice(Licznik.licznik_1,Licznik_temp.licznik_1,Szyfr.tablica_abc1_temp);
     przesun_tablice(Licznik.licznik_2,Licznik_temp.licznik_2,Szyfr.tablica_abc2_temp);
     przesun_tablice(Licznik.licznik_3,Licznik_temp.licznik_3,Szyfr.tablica_abc3_temp);
     
    // pokaz_napis(napis);//
    // pokaz_liczniki(Licznik_temp);//
     skroc_liczniki(Licznik);
      }  
}

void szyfruj_cale_plik(fstream &plik_we,fstream &plik_wy,char *napis, int dl_napisu, Szyfry &Szyfr, Liczniki &Licznik)
{
     while(plik_we>>napis)
     { 
       dl_napisu=strlen(napis); 
	   cout<<napis<<endl; 
       cout<<dl_napisu<<" "<<endl; 
       //pokaz_liczniki(Licznik);
       //pokaz_tablice(Szyfr);
       
       szyfruj_cale(napis,dl_napisu,Szyfr,Licznik);    
       cout<<napis<<endl;
       plik_wy<<napis<<" ";      
     }
     
}
 void deszyfruj_cale(char *napis, const int dl_napisu, Szyfry &Szyfr, Liczniki &Licznik)
{
     Liczniki Licznik_temp;
     skroc_liczniki(Licznik);
     
     ustaw_tablice(Licznik.licznik_1,Szyfr.tablica_abc1_temp,Szyfr.tablica_abc); // Ustawianie pocz¹tkowego przesuniêcia tablic dla zadanego klucza szyfrowania
     ustaw_tablice(Licznik.licznik_2,Szyfr.tablica_abc2_temp,Szyfr.tablica_abc);
     ustaw_tablice(Licznik.licznik_3,Szyfr.tablica_abc3_temp,Szyfr.tablica_abc);
      
      for(int nr_n=0; nr_n<dl_napisu; nr_n++)  //nr_n -> numer znaku napisu
      {    
       Licznik_temp=Licznik;
     
      Licznik.licznik_1++;
      if(Licznik.licznik_1==MAX_T) Licznik.licznik_2++;
      if(Licznik.licznik_2==MAX_T) Licznik.licznik_3++; 
      
      //pokaz_tablice(Szyfr);
      
      szyfruj_tablice(napis,Szyfr.tablica_3, Szyfr.tablica_abc3_temp,nr_n);
      szyfruj_tablice(napis,Szyfr.tablica_2, Szyfr.tablica_abc2_temp,nr_n);
      szyfruj_tablice(napis,Szyfr.tablica_1, Szyfr.tablica_abc1_temp,nr_n);
      
      przesun_tablice(Licznik.licznik_1,Licznik_temp.licznik_1,Szyfr.tablica_abc1_temp);
      przesun_tablice(Licznik.licznik_3,Licznik_temp.licznik_3,Szyfr.tablica_abc3_temp);
      przesun_tablice(Licznik.licznik_2,Licznik_temp.licznik_2,Szyfr.tablica_abc2_temp);
      
     //pokaz_napis(napis);
     //pokaz_liczniki(Licznik_temp);
     skroc_liczniki(Licznik);
      }  
}
  
  
 void rysuj_linie()
 {
      cout<<"-------------------------------------------------------------------------------"<<endl;
  } 

void pokaz_napis(const char* napis)
{
 cout<<"Napis po szyfrowaniu: "<<napis<<endl;     
 //cout<<"Dlugosc napisu: "<<strlen(napis)<<endl;  
}

void pokaz_naglowek_szyfrowania()
{
 rysuj_linie();
 cout<<"                                SZYFROWANIE WYRAZU                         "<<endl;
 rysuj_linie();   
  
}

void pokaz_naglowek_szyfrowania_pliku()
{
 rysuj_linie();
 cout<<"                               SZYFROWANIE PLIKU                         "<<endl;
 rysuj_linie();   
  
}

void pokaz_naglowek_deszyfrowania()
{
 rysuj_linie();
 cout<<"                                DESZYFROWANIE WYRAZU                         "<<endl;
 rysuj_linie();     
  
}



void pokaz_menu_glowne(short &wybor)
{
     rysuj_linie();
     cout<<"                                     MENU                                   "<<endl;
     rysuj_linie();
     cout<<"1.Zaszyfruj pojedynczy wyraz"<<endl;
     cout<<"2.Odszyfruj pojedynczy wyraz"<<endl;
     cout<<"3.Wczytaj i zaszyfruj napis z pliku"<<endl;
     cout<<"4.Wczytaj i odszyfruj napis z pliku"<<endl;
     cout<<"0.Opusc program"<<endl;
     rysuj_linie();
     cout<<">";
     cin>>wybor;
    /* while(!(cin>>wybor))
     {
        cout<<"Niepoprawny format danych wejsciowych"<<endl;
        cout<<"Wybierz opcje ponownie"<<endl; 
     } */
}

void menu_szyfruj_wyraz(char *napis,int &dl_napisu, char *klucz, Szyfry Szyfr, Liczniki Licznik)
{
     short wybor;
     bool powrot;
     
     while(!powrot)
     {
       
       pokaz_naglowek_szyfrowania();
       cout<<"1.Zaszyfruj nowy wyraz"<<endl;
       cout<<"9.Wroc do menu glownego"<<endl;
       cout<<"0.Wyjdz z programu"<<endl;
       rysuj_linie();
       cout<<">";
       cin>>wybor;
       czysc_ekran();
       switch (wybor)
      {
          case 0:  exit(1);
                   break;
          case 1:  pokaz_naglowek_szyfrowania();
                   wprowadz_napis(napis,dl_napisu);
                   wprowadz_klucz(klucz, Licznik, Szyfr);
                   szyfruj_cale(napis,dl_napisu,Szyfr,Licznik);
                   pokaz_napis(napis); 
                   system ("pause");
                   czysc_ekran();
                   break;
          case 9:  powrot=true;
                   break;
         } 
    }
}

void wprowadz_plik_zrodlowy(fstream &plik_we)
{
     char nazwa_pliku[MAX_F];
     cout<<"Wprowadz nazwe pliku zrodlowego, ktory chesz zaszyfrowac:";
     cin>>nazwa_pliku;
     plik_we.open(nazwa_pliku,ios::in);
     
     while(!plik_we)
     {
          cout<<"Nie udalo sie otworzyc pliku zrodlowgo"<<endl;
          cout<<"Wprowadz nazwe pliku ponownie:";
          cin>>nazwa_pliku;
          plik_we.open(nazwa_pliku, ios::in);
     }
     
}

void wprowadz_plik_docelowy(fstream &plik_wy)
{
     char nazwa_pliku[MAX_F];
     cout<<"Wprowadz nazwe pliku docelowego, w ktorym zapiszesz zaszyfrowany tekst: ";
     cin>>nazwa_pliku;
     plik_wy.open(nazwa_pliku,ios::out);
     
     while(!plik_wy)
     {
          cout<<"Nie udalo sie otworzyc pliku docelowego"<<endl;
          cout<<"Wprowadz nazwe pliku ponownie:";
          cin>>nazwa_pliku;
          plik_wy.open(nazwa_pliku, ios::out);
     }
     
}

void menu_szyfruj_plik(char *napis,int &dl_napisu, char *klucz, Szyfry Szyfr, Liczniki Licznik)
{
     short wybor;
     bool powrot;
     fstream plik_we;
     fstream plik_wy;
     
     while(!powrot)
     {
       
       pokaz_naglowek_szyfrowania_pliku();
       cout<<"1.Zaszyfruj nowy plik"<<endl;
       cout<<"9.Wroc do menu glownego"<<endl;
       cout<<"0.Wyjdz z programu"<<endl;
       rysuj_linie();
       cout<<">";
       cin>>wybor;
       czysc_ekran();
       switch (wybor)
      {
          case 0:  exit(1);
                   break;
          case 1:  pokaz_naglowek_szyfrowania_pliku();
                   wprowadz_plik_zrodlowy(plik_we);
                   wprowadz_plik_docelowy(plik_wy);
                   wprowadz_klucz(klucz, Licznik, Szyfr);
                   szyfruj_cale_plik(plik_we,plik_wy,napis,dl_napisu,Szyfr,Licznik);
                   plik_we.close();
                   plik_wy.close();
                  // pokaz_napis(napis); 
                   system ("pause");
                   czysc_ekran();
                   break;
          case 9:  powrot=true;
                   break;
         } 
    }
}


void menu_deszyfruj_wyraz(char *napis,int &dl_napisu, char *klucz, Szyfry Szyfr, Liczniki Licznik)
{
     short wybor;
     bool powrot;
     
     while(!powrot)
     {
       pokaz_naglowek_deszyfrowania();
       cout<<"1.Deszyfruj nowy wyraz"<<endl;
       cout<<"9.Wroc do menu glownego"<<endl;
       cout<<"0.Wyjdz z programu"<<endl;
       rysuj_linie();
       cout<<">";
       cin>>wybor;
       czysc_ekran();
       switch (wybor)
      {
          case 0:  exit(1);
                   break;   
          case 1:  pokaz_naglowek_deszyfrowania();
                   wprowadz_napis(napis,dl_napisu);
                   wprowadz_klucz(klucz, Licznik, Szyfr);
                   deszyfruj_cale(napis,dl_napisu,Szyfr,Licznik);
                   pokaz_napis(napis); 
                   system ("pause");
                   czysc_ekran();
                   break;
          case 9:  powrot=true;
                   break;
         } 
    }
}



void wybor_menu_glowne(Szyfry Szyfr, Liczniki Licznik)
{
     char napis[MAX_N];
     char klucz[MAX_K];  
     int dl_napisu=0; 
     short wybor;  
     while(1)
     {
      pokaz_menu_glowne(wybor);
      czysc_ekran();
      switch (wybor)
      {
          case 0:  exit(1);
                   break;
          case 1:  menu_szyfruj_wyraz(napis,dl_napisu,klucz,Szyfr,Licznik);
                   break;
          case 2:  menu_deszyfruj_wyraz(napis,dl_napisu,klucz,Szyfr,Licznik);
                   break;
          case 3:  menu_szyfruj_plik(napis,dl_napisu,klucz,Szyfr,Licznik);
                   break;
          case 4: // menu_deszyfruj_plik(napis,dl_napisu,klucz,Szyfr,Licznik);
                   break;
         }   
     }
}

int main()
{
     // DO ZROBIENIA:
     // odpowiednie tabluacje
     // komentarze
     // (wczytywanie z pliku)
     
     // bledy aktualne:

	Szyfry Szyfr; //definuje obiekt przechowujacy wartoœci dolnych wierszy wszystkich trzech tablic szyfrowania oraz wartosæ górnego (wspólnego) wiersza 
     strcpy(Szyfr.tablica_abc,"ABCDEFGHIJKLMNOPQRSTUVWXYZ"); 
     strcpy(Szyfr.tablica_abc1_temp,"ABCDEFGHIJKLMNOPQRSTUVWXYZ"); 
     strcpy(Szyfr.tablica_abc2_temp,"ABCDEFGHIJKLMNOPQRSTUVWXYZ"); 
     strcpy(Szyfr.tablica_abc3_temp,"ABCDEFGHIJKLMNOPQRSTUVWXYZ");    
	strcpy(Szyfr.tablica_1, "EKMFLGDQVZNTOWYHXUSPAIBRCJ");   
	strcpy(Szyfr.tablica_2, "AJDKSIRUXBLHWTMCQGZNPYFVOE");
	strcpy(Szyfr.tablica_3, "BDFHJLCPRTXVZNYEIWGAKMUSQO"); 
	
	Liczniki Licznik;
	Licznik.licznik_1=0;
	Licznik.licznik_2=0;
	Licznik.licznik_3=0;   
           
     wybor_menu_glowne(Szyfr,Licznik);
    
//	pokaz_napis(napis);
	
	return 0;
}
