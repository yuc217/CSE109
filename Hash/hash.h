/*
CSE 109
Yuchen
yuc217
Program Description: Program #7
*/
#ifndef HASH_H
#define HASH_H
#include <stdlib.h>
#include <iostream>
#include <cstdio>

#include <fstream>
#include <cstring>
#include <string>

using namespace std;

class Hash{
public:
  Hash(string str);
  int key;
  int hash() const;  //return the hash value
};
#endif
