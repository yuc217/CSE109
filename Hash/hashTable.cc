/*
CSE 109
Yuchen
yuc217
Program Description: Program #7
*/
#include "hashTable.h"

HashTable::HashTable(int n):size(n){
  indexAll=0;
  check(n > 2 && prime(n),
	"(HashTable()) Need positive prime number for table size");
  table = new Link*[n];
  check(table != NULL,"(HashTable(int)) Heap overflow");
  for(int j = 0; j < size; j++)
    table[j] = NULL;
}

HashTable::HashTable(const HashTable& t):size(t.size){
  table = new Link*[size];
  check(table != NULL, "(HashTable(HashTable)) Heap overflow");
  for(int j = 0; j < size; j++)
    table[j] = t.table[j];
}

HashTable::~HashTable(){
  for(int j = 0; j < size; j++)
    if(table[j] != NULL)
      delete table[j];
  delete [] table;
}

HashTable& HashTable::add(string str, int d = 0){
  int h;
  check(!inTable(str),"(add()) Duplicate key");
  h = Hash(str).hash() % size;
  table[h] = new Link(str, d, table[h]);
  check(table[h] != NULL, "(add()) Heap overflow");

  if(str == "$"){

  }

  //cout << hex << int(c) << endl;

  
  return *this;
}

bool HashTable::inTable(string k) const{
  int h;
  Link *temp;
  h = Hash(k).hash() % size;
  temp = table[h];
  while(temp != NULL && temp->key!=k)
    temp = temp->next;
  return temp != NULL;
}

int& HashTable::operator [](string str){
  int h;
  Link *temp;
  if(!inTable(str)) // t["Lehigh"] = 5;
    *this += str;
  h = Hash(str).hash() % size;
  temp = table[h];
  while(temp != NULL && temp->key!= str )
    temp = temp->next;
  return temp->data;
}

const int HashTable::operator [](string str) const{
  int h;
  Link *temp;  // double x = t["Lehigh"];
  check(inTable(str),"([]const) Missing key");
  h = Hash(str).hash() % size;
  temp = table[h];
  while(temp != NULL && temp->key!=str)
    temp = temp->next;
  return temp->data;
}

HashTable& HashTable::operator +=(string k){
  return add(k);
}

void HashTable::remove(string str){
  int h;
  Link *tempa, *tempb;
  check(inTable(str),"(remove()) Missing key");
  h = Hash(str).hash() % size;
  if(table[h]->key== str) {
    tempa = table[h];
    table[h] = table[h]->next;
  }
  else{
    tempb = table[h];
    while(tempb->next->key!= str)
      tempb = tempb->next;
    tempa = tempb->next;
    tempb->next = tempb->next->next;
  }
  delete tempa;
}

ostream& operator <<(ostream& out, const HashTable& h){
  Link *temp;
  for(int j = 0; j < h.size; j++){
    temp = h.table[j];
  /*  if(temp != NULL){
      out << "-----------[ " << j << "]------\n";
    }
   */ while(temp != NULL&&temp->key!="$"){
      out << *temp << endl;
      temp = temp->next;
    }
  }
  return out;
}

bool HashTable::prime(int k){
  int divisor;
  if(k < 0)
    k = -k;
  divisor = 2;
  while(divisor * divisor <= k && k % divisor != 0)
    divisor++;
  return k % divisor != 0;
}
  
void HashTable::check(bool b, string mess){
  if(!b){
    cerr << "ERROR[HashTable]: " << mess << endl;
    exit(1);
  }
}
void HashTable::labaddExtension(){

  for(int i=0;i<255;i++){
    if(allInfo[i].length()>0){
      allInfo[i]+="3aff";
    }
    else {allInfo[i]="aa";break;}
  }
}

void HashTable::argaddExtension(){
  for(int i=0;i<255;i++){
    if(allInfo[i].length()>0){
      allInfo[i]+="ff";
    }
    else {allInfo[i]="aa";break;}
  }
}

void HashTable::hasharray(const HashTable& h){
Link *temp;
string st;
string str;
int da;
  for(int j = 0; j < h.size; j++){
    temp = h.table[j];
   while(temp != NULL){
    da = temp->data;

  
   // cout << d << " "<< st<< endl;
    stringstream ss;
    ss<< hex << da; // int decimal value
    string hexvar (ss.str());
    if(hexvar.length()<2) st= "0"+hexvar;
    else st = hexvar;
    
    str = temp-> key;

    for(unsigned int i=0;i<str.length();i++){
      stringstream ss;
      ss << hex << int(str[i]);
      string newstr (ss.str());
      st+=newstr;
    }

    allInfo[indexAll++]=st;
      
      temp = temp->next;
    }
  }
}
void HashTable::ahasharray(const HashTable& h){
Link *temp;
string st;
string str;
int da;
  for(int j = 0; j < h.size; j++){
    temp = h.table[j];
   while(temp != NULL){
    da = temp->data;

  
   // cout << d << " "<< st<< endl;
    stringstream ss;
    ss<< hex << da; // int decimal value
    string hexvar (ss.str());
    if(hexvar.length()<2) st= "0"+hexvar;
    else st = hexvar;
    
    str = temp-> key;

    for(unsigned int i=0;i<str.length();i++){
      stringstream ss;
      ss << hex << int(str[i]);
      string newstr (ss.str());
      st+=newstr;
    }

    allInfo[da]=st;
      
      temp = temp->next;
    }
  }
}

/*
  for(int i=0;i<255;i++){
    if(allInfo[i].length()>0){
      cout << allInfo[i]<<endl;
    }
  }
  */

  





