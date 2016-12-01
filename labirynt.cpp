
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const short map_size_x = 4; //                                                    rozmiar mapy w poziomie
const short map_size_y = 2;//                                                     rozmiar mapy w pionie
const short seg_length = 10;
const short seg_height = 5;

const char seg[][seg_height][seg_length+1] = {//                                                     definicja tablicy segmentow
{{"####  ####"},
{"##    ####"},
{"    ##    "},
{"##      ##"},
{"####  ####"}},


{{"####    ##"},
{"  ####  ##"},
{"          "},
{"##      ##"},
{"####    ##"}},


{{"          "},
{"    ##    "},
{"    ####  "},
{"##  ######"},
{"##        "}},


{{"####      "},
{"##    ##  "},
{"    ##    "},
{"  ##    ##"},
{"##    ####"}},


{{"      ####"},
{"##      ##"},
{"    ##    "},
{"    ##    "},
{"        ##"}},


{{"####  ####"},
{"####  ####"},
{"          "},
{"####  ####"},
{"####  ####"}}};

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
	
};

inline void print_line(char znak);
void show_menu(player_t* player);
void get_keys(player_t* player, const char map[10][40]);


void make_map(char map[10][40]);
void print_map(char map[10][40], player_t* player);

int main(int argc, char const *argv[]) {

	srand(time(0));
	char map[10][40];
	
	player_t* player = new player_t;
	player->points = 0;
	player->coords.x = 0;
	player->coords.y = 2;
	player->map_visible = false;
	player->moves = 0;
	
	make_map(map);
	
	while(player->points < 5)
	{
		system("cls");
		show_menu(player);
	print_map(map, player);
	get_keys(player, map);
	
	}
	
	
	//system("pause");
	delete player;
	return 0;
}

void make_map(char map[10][40])
{
//------------------------------------------------------
  // char **map = new char*[map_size_y*seg_height];
  // for (size_t i = 0; i < map_size_x*seg_lenght; i++) {
  //     *(map+i) = new char[seg_lenght];
  // }
//-----------------------------------------------------



  
 
  for(short z = 0; z < map_size_x*map_size_y ; z++)					//petla rysujaca kolejne segmenty do tablicy
  {
  	int index = rand()%6;
	 // int index = 5;						// generowanie losowego segmentu (0..5)
	  for(short i = 0; i < seg_height; i++)				//
	  {
	  	for(short j = 0; j < seg_length;j++)			// dodawanie jednego segmentu do mapy
	  	{
	  		if(z < map_size_x)							// pierwsza linijka segmentów
	  		{
	  			map[i][j + seg_length*z] = seg[index][i][j];
		 
			}
			else 										// druga linijka segmentów
			{
				map[i + seg_height-1][j + seg_length*z] = seg[index][i][j];
			}
		 	
		}
	  }
  }


 

  
}

void print_map(char map[10][40], player_t* player)
{
	 print_line('-');
  cout << endl;
	for(short i = 0; i < 10; i++)
  	{
  		cout << '|';
	  	for(short j = 0; j < 40;j++)
	  	{
	  		if( (i == player->coords.y && j == player->coords.x) && map[i][j] != '#' )
	  		{
	  			cout << "[";
	  			
			}else
			cout<<map[i][j];
			
		}
		cout << '|';
	cout<<endl;
  	}
	print_line('-');
  cout << endl;
}

inline void print_line(char znak)
{
	cout << ' ';
	for(short i = 0; i < map_size_x*seg_length;i++) cout << znak; 
}
//////////////////////////////////////////////////////
// 
//  Punkty: x/5  V - w³¹cz ca³¹ mapê
//  Sterowanie: 
//                                                    //
////////////////////////////////////////////////////////
void show_menu(player_t* player)
{
	char visible;
	if(player->map_visible) visible = 't';
	else visible = 'n';
	print_line('#');
	cout << endl << " #                                      #";
	cout << endl << " # Punkty: "<<player->points<<"/5"<<"      Sterowanie: W/S/A/D #";
	cout << endl << " #    X="<<player->coords.x<<" "<<"Y="<<player->coords.y<<"      Ruchy:"<<player->moves<<"               #";
	cout << endl << " #        V - wyswietlenie mapy ("<<visible<<")     #";
	cout << endl << " #                                      #" << endl;
	print_line('#');
	cout<<endl<<endl<<endl;
	
}
bool is_free(player_t* player,const char map[10][40], char direction)
{
	switch (direction)
	{
		case 'W': if(map[player->coords.y -1][player->coords.x] == '#') return false;
					else return true;
					break;
		case 'S': if(map[player->coords.y +1][player->coords.x] == '#') return false;
					else return true;
					break;
		case 'A': if(map[player->coords.y][player->coords.x-1] == '#') return false;
					else return true;
					break;
		case 'D': if(map[player->coords.y][player->coords.x+1] == '#') return false;
					else return true;
					break;
		
	}
}

void get_keys(player_t* player,const char map[10][40])
{
	char key, key_up;
	cout<<">";
	cin>>key;
	key_up = toupper(key);
	switch (key_up)
	{
		case 'W': if (is_free(player,map,'W')) 
					{
						player->coords.y -= 1;
						if(player->coords.y < 0 ) player->coords.y = 0;
						else player->moves++;
					}
				break;
		case 'S': if (is_free(player,map,'S')) 
					{
						player->coords.y += 1;
						if(player->coords.y > seg_height*map_size_y-1) player->coords.y = seg_height*map_size_y-1;
						else player->moves++;
					}
				break;
		case 'A': if (is_free(player,map,'A')) 
					{
						player->coords.x -= 1;
						if(player->coords.x < 0 ) player->coords.x = 0;
						else player->moves++;
					}	
				break;
		case 'D': if (is_free(player,map,'D')) 
					{
						player->coords.x += 1;
						if(player->coords.x > seg_length*map_size_x) player->coords.y = seg_length*map_size_x;
						else player->moves++;
					}
				break;
		case 'V': player->map_visible ^= 1;
				break;
		
		default: get_keys(player, map);
	}	
}
/*
TODO:
animacja ludzika
punkty
promieñ widzenia
suma ruchów
*/
