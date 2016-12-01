#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const short map_size_x = 4; //                                                    rozmiar mapy w poziomie
const short map_size_y = 2;//                                                     rozmiar mapy w pionie
const short seg_lenght = 10;
const short seg_height = 5;

const char seg[][seg_height][seg_lenght+1] = {//                                                     definicja tablicy segmentów
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
{"##     ###"}},


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
void make_map(void);

int main(int argc, char const *argv[]) {

srand(time(0));

make_map();
// for (size_t i = 0; i < 6; i++) {
//
//   for (size_t j = 0; j < 11; j++) {
//   std::cout << seg[0][i][j];
// }
// cout<<endl;
// }

  return 0;
}

void make_map(void)
{
char c;
  // char **map = new char*[map_size_y*seg_height];
  // for (size_t i = 0; i < map_size_x*seg_lenght; i++) {
  //     *(map+i) = new char[seg_lenght];
  // }
//-----------------------------------------------------
char index[3];

  for (size_t i = 0; i < 5; i++) {
    index[i] = i;
  }
  short temp = 0;
  for (size_t i = 0; i < 5; i++) {

    for (size_t j = 0; j < 41; j++) {

      if(j > 0 && j%11 == 0) temp++;
    std::cout << seg[index[temp]][i][j];
  }
  temp = 0;
  std::cout << std::endl;
}
  // for (size_t i = 0; i < 10; i++) {
  //   delete[] map[i];
  // }
  // delete[] map;

}
