// POP 2016 12 09 projekt 1 Cichocki Bartosz AIR 2 165355 Srodowisko: Dev-C++ 5.10 Kompilator: TDM-GCC 4.8.1 64-bit Release
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

////////////////////////////////////// STA£E //////////////////////////////////////

const short map_size_x = 4; // rozmiar mapy w poziomie
const short map_size_y = 2; // rozmiar mapy w pionie
const short seg_length = 10; 
const short seg_height = 5; 
const short points_amount = 5;
const short visible_radius = 2;

const short map_y = seg_height*map_size_y;
const short map_x = seg_length*map_size_x;

const char player_symbol = 'O';
const char point_symbol = 'x';

const char key_up = 'W';
const char key_down = 'S';
const char key_left = 'A';
const char key_right = 'D';
const char key_visible = 'V'; //znak prze³¹czaj¹cy tryb widocznoœci mapy

const char seg[][seg_height][seg_length+1] = { // definicja tablicy segmentów
{
{"####  ####"},
{"##    ####"},
{"    ##    "},
{"##      ##"},
{"####  ####"}
},

{
{"####    ##"},
{"  ####  ##"},
{"          "},
{"##      ##"},
{"####    ##"}
},

{
{"          "},
{"    ##    "},
{"    ####  "},
{"##  ######"},
{"##        "}
},

{
{"####      "},
{"##    ##  "},
{"    ##    "},
{"  ##    ##"},
{"##    ####"}
},

{
{"      ####"},
{"##      ##"},
{"    ##    "},
{"    ##    "},
{"        ##"}
},

{
{"####  ####"},
{"####  ####"},
{"          "},
{"####  ####"},
{"####  ####"}
}
};

///////////////////////////////////////////////////////////////////////////////////


struct coords_t
{
	short x;
	short y;
};

struct player_t
{
	short points;
	int moves;
	coords_t coords;
	bool map_visible;
	bool points_changed;  //czy nast¹pi³a zmiana liczby punktów
	
};

//////////////////////////////// PROTOTYPY FUNKCJI ////////////////////////////////

void win(player_t* player);
inline void draw_line(char znak);
void show_menu(player_t* player);
void game(char map[map_y][map_x], player_t* player);
void init(char map[map_y][map_x], player_t* player);

void gen_points(char map[map_y][map_x]);
void make_map(char map[map_y][map_x]);
void draw_arena(char map[map_y][map_x], player_t* player);
void get_keys(player_t* player, const char map[map_y][map_x]);
void check_point(char map[map_y][map_x], player_t* player, short y, short x);
void draw_map(char map[map_y][map_x], player_t* player, short y, short x);

///////////////////////////////////////////////////////////////////////////////////



int main(int argc, char const *argv[]) {
	
	char map[map_y][map_x];
	player_t* player = new player_t;
	
	init(map,player);
	
	game(map, player);
	
	delete player;
	return 0;
}


/*
Funkcja odpowiadaj¹ca za g³ówn¹ pêtlê gry
*/

void game(char map[map_y][map_x], player_t* player)
{
	while(player->points < points_amount)
	{
		system("cls");
		show_menu(player);
		draw_arena(map, player);
		if(player->points_changed) continue; //odœwie¿ ekran z menu po zdobyciu punktu
		get_keys(player, map);
	}
	
	win(player);
}

/*
Funkcja inicjalizuj¹ca mapê i gracza
*/

void init(char map[map_y][map_x], player_t* player)
{
	srand(time(0));

	player->points = 0;
	player->coords.x = 0;
	player->coords.y = 2;
	player->map_visible = false;
	player->moves = 0;
	player->points_changed = false;
	
	make_map(map);
	gen_points(map);
}

/*
Funkcja rysuj¹ca ekran z wynikami
*/

void win(player_t* player)
{
	system("cls");
	
	draw_line('*');
	cout << " *                                      *"<<endl;
	cout << " *               WYGRALES!              *"<<endl;
	cout << " *                                      *"<<endl;
	if(player->moves < 10) 
	cout << " *             ILOSC RUCHOW:"<<player->moves<<"           *"<<endl;
	else if(player->moves < 100)
	cout << " *             ILOSC RUCHOW:"<<player->moves<<"          *"<<endl;
	else 
	cout << " *            ILOSC RUCHOW:"<<player->moves<<"          *"<<endl;
	cout << " *                                      *"<<endl;
	draw_line('*');
	
	system("pause");
}

/*
Funkcja tworz¹ca mapê w tablicy 2D z segmentów 2D
*/

void make_map(char map[map_y][map_x])
{
  for(short z = 0; z < map_size_x*map_size_y ; z++)		//pêtla rysuj¹ca kolejne segmenty do tablicy
  {
  	short index = rand()%6;								// generowanie losowego segmentu (0..5)
						
	  for(short i = 0; i < seg_height; i++)				//
	  {
	  	for(short j = 0; j < seg_length;j++)			// dodawanie jednego segmentu do mapy
	  	{
	  		if(z < map_size_x)							// pierwsza linijka segmentów
	  			map[i][j + seg_length*z] = seg[index][i][j];	
			else 										// druga linijka segmentów
				map[i + seg_height-1][j + seg_length*z] = seg[index][i][j];		 	
		}
	  }
  }  
}

/*
Funkcja sprawdzaj¹ca, czy w danym miejscu znajduje siê punkt
*/

void check_point(char map[map_y][map_x], player_t* player, short y, short x)
{
	if (map[y][x] == point_symbol)
	{
	  	player->points++;
	  	map[y][x] = ' '; //kasowanie punktu z mapy
	  	player->points_changed = true;
	}else 
		player->points_changed = false;
}

/*
Funkcja rysuj¹ca mapê na ekranie
*/

void draw_map(char map[map_y][map_x], player_t* player, short y, short x)
{
	short distance_x = abs(x - player->coords.x); //odleg³oœæ danego punktu od gracza
	short distance_y = abs(y - player->coords.y);
	
	if( (y == player->coords.y) && (x == player->coords.x) ) //na pozycji gracza
	{
	  	cout << player_symbol;
	  	check_point(map, player, y, x);  // sprawdza, czy na pozycji jest punkt 
		    			
	}
	else if(  player->map_visible  ||  ( (distance_x <= visible_radius) && (distance_y <= visible_radius) )  ) // gdy w³¹czony tryb pe³nej mapy lub doleg³oœæ dooko³a 
			cout<<map[y][x]; 																				   // jest wystarczaj¹ca
	else cout<<' ';	
}

/*
Funkcja rysuj¹ca mapê z granicami
*/

void draw_arena(char map[map_y][map_x], player_t* player)
{
	draw_line('-');
  	 	
	for(short i = 0; i < 10; i++)
  	{
  		cout << '|';
	  	for(short j = 0; j < 40;j++)
	  	{
	  		draw_map(map,player,i,j);		
		}
		cout << '|';
		cout<<endl;
  	}
	  	
	draw_line('-');  	
}

/*
Funkcja-makro rysuj¹ca liniê z podanego znaku
*/

inline void draw_line(char znak)
{
	cout << ' ';
	for(short i = 0; i < map_x;i++) cout << znak;
	cout<<endl; 
}

/*
Funkcja rysuj¹ca menu i opis sterowania
*/

void show_menu(player_t* player)
{
	char visible ;
	
	if(player->map_visible) visible = 't';
	else visible = 'n';
	
	draw_line('#');
	cout << " #                                      #";
	cout << endl << " # Punkty: "<<player->points<<"/5"<<"      Sterowanie: "<<key_up<<"/"<<key_down<<"/"<<key_left<<"/"<<key_right<<" #";
	cout << endl << " #                                      #";
	cout << endl << " #       "<<key_visible<<" - wyswietlenie mapy  ("<<visible<<")     #";
	cout << endl << " #                                      #" << endl;
	draw_line('#');
	
	cout<<endl<<endl;
}

/*
Funkcja sprawdzaj¹ca, czy w podanym kierunku kolejny krok jest mo¿liwy (wolne miejsce)
*/

bool is_free(player_t* player,const char map[map_y][map_x], char direction)
{
	switch (direction)
	{
		case key_up: 	if(map[player->coords.y -1][player->coords.x] == '#') return false;
						else return true;
						break;
		case key_down: 	if(map[player->coords.y +1][player->coords.x] == '#') return false;
						else return true;
						break;
		case key_left: 	if(map[player->coords.y][player->coords.x-1] == '#') return false;
						else return true;
						break;
		case key_right: if(map[player->coords.y][player->coords.x+1] == '#') return false;
						else return true;
						break;		
	}
}

/*
Funkcja zajmuj¹ca siê obs³ug¹ klawiszy
*/

void get_keys(player_t* player,const char map[map_y][map_x])
{
	char key, key_upper;
	cout<<">";
	cin>>key;
	key_upper = toupper(key); // dla obs³ugi ma³ych i wielkich liter
	
	switch (key_upper)
	{
		case key_up: 	if (is_free(player,map,key_up)) 
						{
							player->coords.y -= 1;
							if(player->coords.y < 0 ) player->coords.y = 0;
							else player->moves++;
						}
						break;
		case key_down: if (is_free(player,map,key_down)) 
						{
							player->coords.y += 1;
							if(player->coords.y > map_y-1) player->coords.y = map_y-1;
							else player->moves++;
						}
						break;
		case key_left: if (is_free(player,map,key_left)) 
						{
							player->coords.x -= 1;
							if(player->coords.x < 0 ) player->coords.x = 0;
							else player->moves++;
						}	
						break;
		case key_right: if (is_free(player,map,key_right)) 
						{
							player->coords.x += 1;
							if(player->coords.x > map_x-1) player->coords.x = map_x-1;
							else player->moves++;
						}
						break;
		case key_visible: player->map_visible ^= 1; // przê³¹czanie trybu mapy
						break;	
		default: 		get_keys(player, map);
	}					
}

/*
Funkcja generuj¹ca losowe punkty i zapisuj¹ca je na mapie
*/

void gen_points(char map[map_y][map_x])
{
	coords_t *points = new coords_t[points_amount];
	short *x = new short;
	short *y = new short;

	for (short i = 0; i< points_amount; i++)
	{
		while(1) // szuka wolnego miejsca na mapie 
		{	
			(points + i)->x = rand() % ( map_x  );	// losowanie wspó³rzêdnych
			(points + i)->y = rand() % ( map_y  );
			*x = (points + i)->x; //dla skrócenia indeksów
			*y = (points + i)->y;
			
			if ( (map[*y][*x] != '#') && (map[*y][*x] != player_symbol) && (map[*y][*x] != point_symbol) )
			{
				map[*y][*x] = point_symbol;	// wolne miejsce, wyjœcie z pêtli, generowanie kolejnego punktu w forze
				break;
			} 	
		}
	}
		
	delete x,y;
	delete[] points;
}

