#include <iostream>
#include <iomanip>
#include <clocale>


using namespace std;

int main(int argc, char const *argv[]) {
//setlocale(LC_ALL, "pl_PL"); 
char znaki[50];
cout<<"Wpisz znaki:";
cin >> znaki;
char i = 0;
for(int j = 0; znaki[j] != 0; j++)
{
	while(znaki[j] != i) i++;
cout<<"znak:"<<i<<" kod:"<<(int)i<<endl;
}


  return 0;
}
