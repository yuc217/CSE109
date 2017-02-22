/*
CSE 109
Yuchen
yuc217
Program Description: Program #7
*/
#include "hash.h"

Hash::Hash(string str) {
  int tmp = 0;
  string p = str;
  for(unsigned int i =0;i<p.length();i++) {
    tmp += p[i];
  }
  key = abs(tmp);
}

int Hash::hash() const{
  return key;
}
