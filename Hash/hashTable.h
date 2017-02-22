/*
CSE 109
Yuchen
yuc217
Program Description: Program #7
*/
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "hash.h"
#include "link.h"
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

class HashTable{
public:
  HashTable(int n=97);
  HashTable(const HashTable &t);
  ~HashTable();

  string allInfo[255];
  int indexAll;

  HashTable& add(string str, int d);

  bool inTable(string)const;

  int& operator [](string);

  const int operator [](string) const;

  HashTable& operator += (string);

  void remove(string);

  void hasharray(const HashTable& h);
  void ahasharray(const HashTable& h);
  void labaddExtension();
  void argaddExtension();
  friend ostream& operator<<(ostream &out,const HashTable& h);
  
private:
  int size;   //the size of the array table
  Link **table;  //dynamically allocated array of pointers, each
		 //pointer pointing to a linked list of Links or NULL

  // return true if and only iff k is a positive prime
  bool prime(int k);

  // if b is true do nothing, else display on cerr the error message and exit
  static void check(bool b, string mess);
};

#endif
