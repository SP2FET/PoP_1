#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <cstring>

using namespace std;

void draw_table(int** teach_tab, int teachers_count);
void fill_table(int** teach_tab, int teachers_count);
void check(int** teach_tab, int** class_tab, int teachers_count, int class_count,int *teacher, int index );
void verify(int** teach_tab,int** class_tab, int teachers_count, int class_count);

int main()
{
	int teachers_count;
	int class_count;
	int max_tries = 1; // iloœæ powtórzeñ
	
	
	
	cout << "Podaj liczbe nauczycieli: ";
	cin >> teachers_count;
	cout << endl;
	cout << "Podaj liczbe sal: ";
	cin >> class_count;
	cout << endl;
	cout << "Podaj ilosc prob: ";
	cin >> max_tries;
	cout << endl;
	

	
	// tworzenie beznadziejnych tablic 
	int **teach_tab = new int*[teachers_count];
	for(int i = 0; i < teachers_count; i++)
		{
			teach_tab[i] = new int[teachers_count];	
		}
		
	int **class_tab = new int*[class_count];
	for(int i = 0; i < class_count; i++)
		{
			class_tab[i] = new int[teachers_count];	
		}
	
	// zerowanie tablic
	for(int i = 0; i < teachers_count; i++)
	{
		for(int j = 0; j < teachers_count; j++)
		{
			teach_tab[i][j] = 0;
		}
	}
		
	for(int i = 0; i < class_count; i++)
	{
		for(int j = 0; j < teachers_count; j++)
		{
			class_tab[i][j] = 0;
		}
	}
			
	fill_table(teach_tab,teachers_count);
	cout<<endl;		
	draw_table(teach_tab,teachers_count);
	cout<<endl;
	
	//tablica z kolejnymi nauczycielami, pod indeksem jest numer nauczyciela, gdy jest równy 0 - nauczyciel przypisany do sali
	
	
	
	int *teacher = new int[teachers_count];
	for(int i = 0; i < teachers_count; i++) teacher[i] = i+1;
	
	
	for(int i = 0; i < max_tries; i++)
	{
		check(teach_tab, class_tab, teachers_count, class_count, teacher, 0);
		verify(teach_tab,class_tab,teachers_count,class_count);
		
	
	}
	
		
	for(int i = 0; i < class_count; i++)
	{
		cout << "Klasa "<<i+1<<":"<<"  ";
		for(int j = 0;class_tab[i][j] != 0; j++)
		{
			if (class_tab[i][j] != 9999)
			cout <<" n"<<class_tab[i][j];
		}
		if (class_tab[i][0] == 0) cout<<" PUSTA :)";
		cout<<endl;
	}

				
	system("pause");
	// usuniêcie tablic
	for(int i = 0; i < teachers_count; i++)
		delete [] teach_tab[i];
	delete [] teach_tab;
	delete [] teacher;
}
// n-1 razy, n naczycieli, po funkcji tablica nauczycieli o wers w dó³ <- tak w teorii mia³o byæ

	/*
	Algorytm:
	do 1 sali 1 nauczyciel
	je¿eli 2 nauczyciel mo¿e pracowaæ z 1, to do 1 sali. Jak nie, do kolejnej.
		
		    n1 n2 n3 n4 n5 n6
	n1  	o  -  x  -  -  -
	n2 		-  o  -  -  x  -
	n3  	x  -  o  -  -  x
	n4  	-  -  -  o  -  -
	n5  	-  x  -  -  o  -
	n6  	-  -  x  -  -  o
		
	*/
void verify(int** teach_tab,int** class_tab, int teachers_count, int class_count)
{
		for(int i = 0; i < teachers_count; i++)
		{
			for(int j = 0; j < teachers_count; j++) //szuka w tablicy nauczycieli czy jest konflikt
			{
				if (teach_tab[i][j] == 1) // konflikt dla n_i i n_j
				{
					for(int ii = 0; ii < class_count; ii++) //szuka w ka¿dej klasie...
					{
						for(int jj = 0; j < teachers_count; j++) //... czy któryœ z nauczycieli...
						{
							// tu mo¿na daæ t¹ losowoœæ
							if( class_tab[ii][jj] == i || class_tab[ii][jj] == j ) //... nie jest w konflikcie. Je¿eli s¹
							{
								 class_tab[ii+1][jj+1] = class_tab[ii][jj]+1; // przenieœ klasê wy¿ej
								 class_tab[ii][jj+1] = 9999; // a tego konfliktowego nazwij 9999
								
							} 
						}
					
					}
				}
				
			}
		}
}
void check(int** teach_tab, int** class_tab, int teachers_count, int class_count,int *teacher, int index )
{
	
	
	int class_index = 0; //numer klasy
	int next = 0; // indeks kolejnego nauczyciela w klasie 
	int added = 0; // liczba przypisanych nauczycieli
	
	for(int j = 0; j < teachers_count; j++) // przeleæ przez wszystkich nauczycieli
		{ 										// dla jednego nauczyciela
			for(int i = 0; i < teachers_count; i++) // sprawdzenie wszystkich innych nauczycieli ( wiersze z tabeli)
			{
				if(teach_tab[j+index][i] != 1 && teacher[i] != 0) // je¿eli dany nauczyciel ( o indeksie i) mo¿e wyst¹piæ z nauczycielem z fora powy¿ej i nie jest jeszcze przypisany
				{
					
					class_tab[class_index][next] = teacher[i]; //przypisz go do klasy na pozycjê next
					teacher[i] = 0; //wykorzystany
					added++; // zwiêksz licznik
					next++; //przesuñ siê dla kolejnego nauczyciela
				}
				
		
			}
			//
			//
			class_index++;
			if (added == teachers_count)
			{
				cout << "gotowe :)"<<endl;
				break;
			}
			if (class_index > class_count) 
			{
				cout<<"za malo klas";
				system("pause");
				exit(1);
			}
			next = 0;
		
		}
		
	
}

/*

void check(int** teach_tab, int** class_tab, int teachers_count, int class_count, int index )
{
	int *teacher = new int[teachers_count];
	for(int i = 0; i < teachers_count; i++) teacher[i] = i+1;
	
	int class_index = 0; //numer klasy
	int next = 0; // indeks kolejnego nauczyciela w klasie 
	int added = 0; // liczba przypisanych nauczycieli
	
	for(int j = 0; j < teachers_count; j++) // przeleæ przez wszystkich nauczycieli
		{ 										// dla jednego nauczyciela
			for(int i = 0; i < teachers_count; i++) // sprawdzenie wszystkich innych nauczycieli ( wiersze z tabeli)
			{
				if(teach_tab[j+index][i] != 1 && teacher[i] != 0) // je¿eli dany nauczyciel ( o indeksie i) mo¿e wyst¹piæ z nauczycielem z fora powy¿ej i nie jest jeszcze przypisany
				{
				class_tab[class_index][next] = teacher[i]; //przypisz go do klasy na pozycjê next
				teacher[i] = 0; //wykorzystany
				added++; // zwiêksz licznik
				next++; //przesuñ siê dla kolejnego nauczyciela
				}
		
			}
		
			class_index++;
			if (added == teachers_count)
			{
				cout << "gotowe :)"<<endl;
				break;
			}
			if (class_index > class_count) 
			{
				cout<<"za malo klas";
				system("pause");
				exit(1);
			}
			next = 0;
		}
	delete [] teacher;
}

*/

void fill_table(int** teach_tab, int teachers_count)
{
	char teacher_1[3];
	char teacher_2[3];
	
		cout << "Podaj pary osob, ktore nie moga razem pracowac:"<<endl
		 << "(podaj pare w formacie: n1 n2, zatwierdz enter, 0 0 oznacza koniec wprowadzania)"<<endl;
	
	while(true)
	{
		cout << ">";
		cin >> teacher_1 >> teacher_2;
		if (teacher_1[0] == '0') break;
		
		
		cout << "n" <<teacher_1[1]<<" "<<"n"<<teacher_2[1]<<endl;
		teach_tab[teacher_1[1] -49][teacher_2[1] -49] = 1;
		teach_tab[teacher_2[1]-49][teacher_1[1]-49] = 1;
		
	}
}

// no to rysujemy...
void draw_table(int** teach_tab, int teachers_count)
{
	cout <<"   ";
	for(int i = 0; i < teachers_count; i++)
	{
		cout << setw(2) <<'n'<<i+1;
	}
	cout << endl;
		for(int i = 0; i < teachers_count; i++)
		{
			cout <<'n'<<i+1;
			for(int j = 0; j < teachers_count; j++)
			{
				if (teach_tab[i][j] == 1)
					cout << setw(3)<< 'x';
				else
					cout << setw(3)<< '-';
			}
			cout << endl;
		}
	
}
