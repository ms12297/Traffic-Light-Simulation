#pragma once
#include <iostream>
#include <cmath>
#include <fstream>
#include <ctime>

using namespace std;

class TrafficLight {
private:
	int ID;
	int state; //0 for off, 1 for red, 2 for yellow, and 3 for green
	double greentime;
	static int TLnum; //To record number of instances of this class

public:
	//Constructor
	TrafficLight() {
		ID = TLnum;
		state = 1; //Every instance starts as red
		greentime = 0;
		TLnum++;
	}

	//Getter functions
	int getID() {
		return (ID);
	}
	int getState() {
		return (state);
	}
	double getGreentime() {
		return (greentime);
	}
	//Setter functions
	void setState(int color) {
		state = color;
	}

	void setGreentime(double GreenTime) {
		greentime = GreenTime;
	}

	void PrintTLinfo() {
		cout << "ID = " << ID << endl;
		cout << "State = ";
		if (state == 1) cout << "Red" << endl;
		if (state == 2) cout << "Yellow" << endl;
		if (state == 3) cout << "Green" << endl;
		if (state == 0) cout << "Off" << endl;
		cout << "Green-time = " << greentime << endl;
		cout << endl;
	}
	static int get_numofTL() {
		return TLnum;
	}
	void wait(double seconds) {
		clock_t start = clock();
		double wait = seconds * CLOCKS_PER_SEC;
		while (clock() < (start + wait)); //Elapse the wait time
	}
};

int TrafficLight::TLnum = 0; //Initializing TLnum