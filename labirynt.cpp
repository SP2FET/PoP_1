#include <iostream>

using namespace std;

const char seg1[][11] = {
{"####  ####"},
{"##    ####"},
{"    ##    "},
{"##      ##"},
{"####  ####"}};

const char seg2[][11] = {
{"####    ##"},
{"  ####  ##"},
{"          "},
{"##      ##"},
{"####    ##"}};

const char seg3[][11] = {
{"          "},
{"    ##    "},
{"    ####  "},
{"##  ######"},
{"##        "}};

const char seg4[][11] = {
{"####      "},
{"##    ##  "},
{"    ##    "},
{"  ##    ##"},
{"##    ###"}};

const char seg5[][11] = {
{"      ####"},
{"##      ##"},
{"    ##    "},
{"    ##    "},
{"        ##"}};

const char seg6[][11] = {
{"####  ####"},
{"####  ####"},
{"          "},
{"####  ####"},
{"####  ####"}};

int main(int argc, char const *argv[]) {

for (size_t i = 0; i < 5; i++) {
  for (size_t j = 0; j < 10; j++) {
  std::cout << seg1[i][j];
}
cout<<endl;
}

  return 0;
}
