
#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <queue>
#include <cstdlib>
#include <stdio.h>  
#include <cstdio>
using namespace std;
class Vehicle { public:
Vehicle() { }
void move();
void virtual noise();
};
void Vehicle::move() { cout << "driving vehicle" << endl; } void Vehicle::noise(){ cout << "making noise" << endl; } ;
class Car: public Vehicle { void move();
void noise();
};
void Car::move() { cout << "driving car" << endl; } void Car::noise() { cout << "honk horn" << endl; }
int main(int argc, char **argv) { 
	Vehicle *v = new Vehicle(); v->move();
v->noise();

}