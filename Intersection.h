#pragma once

#include <iostream>
#include <cmath>
#include <fstream>
#include <ctime>
#include <iomanip>
#include "TrafficLight.h"

using namespace std;

string filename; //For input of file name of data file
//Defining constants as global variables
const int x = 1; //Counter for run()
const double yellowtime = 3;  //3 seconds
const double updatetime = (1.5 * 60.0); //Number of seconds in 1.5 minutes, short interval for test purposes
const int TLmax = 5; //Maximum traffic lights in intersection

class Intersection {
private:
	TrafficLight TL[TLmax]; //Array of TrafficLight instances
	double C; //Cycle length
	double Q_t; //Total traffic flow
	double Q_i[TLmax]; //Traffic flow for traffic light at index TLmax
	double green_time[TLmax]; //Array of greentimes to be stored in TrafficLight instances
	int TLnum; //To trakc total number of TrafficLight instances employed in Intersection instance

public:
	//Constructor function
	Intersection() { 
		TLnum = 0;
		C = 0;
		Q_t = 0;
		for (int i = 0; i < TLmax; i++) {
			//Set traffic flows and greentimes to 0
			Q_i[i] = 0;
			green_time[i] = 0;
		}
	}

	void AddLight() {
		if (TLnum < TLmax) {
			TrafficLight a;
			TL[TLnum] = a;
			TLnum++;
		}
		else
			cout << "\nLimit reached! Cannot add more traffic lights" << endl;
	}
	void droplight(int TL_ID) {
		bool isTL = false;

		for (int i = 0; i < TLnum; i++)
		{
			if (TL_ID == TL[i].getID())
			{
				for (int j = i; j < TLnum; j++)
				{
					TL[j] = TL[j + 1];
				}
				TLnum--;
				cout << "Removed traffic light " << TL_ID << endl;
				isTL = true;
			}
		}

		if (!isTL)
			cout << "Can't find the traffic light to drop!" << endl;
	}

	int get_numofTL() {
		return TLnum;
	}


	void readTrafficData() {

		Q_t = 0; //Initiallziing total traffic flow for every time this function is called
		ifstream infile; //Input filestream

		//Validate input of filename
		while (int z = 1) {
			infile.open(filename, ios::in);

			if (infile.fail()) { //Check if file opened successfully
				cerr << "Error opening file!\nPlease enter the correct file name: \n";
				getline(cin, filename);
			}
			else break;
		}

		//Storing data into variables
		string skip;
		getline(infile, skip, '='); //Skip to data
		infile >> C;
		//Subtracting yellowtime from C to get greentimes only, useful in calculations later
		C -= TLnum * yellowtime;

		for (int i = 0; i < TLnum; i++) { //Store respective traffic flows
			if (infile.eof()) break;
			getline(infile, skip, '=');
			infile >> Q_i[i];
			Q_t += Q_i[i]; //Calculating total traffic flow as the sum of all traffic flows
		}

		infile.close(); //Close input file
	}

	void calculate_greentime() { 
		for (int i = 0; i < TLnum; i++) {
			//Calculating greentime
			double greentime = ((Q_i[i] / Q_t) * C);
			green_time[i] = greentime;
			//Setting value of greentime
			TL[i].setGreentime(green_time[i]);
			cout << "\nGreen Time for Traffic Light " << (i + 1) << " is = " << TL[i].getGreentime() << " seconds" << endl;
		}
	}

	void run() {
		double SimulationT = 0;
		int cycle = 1;
		cout << "\nCommencing Simulation\n" << endl;

		while (x == 1) { //Loop does not end
			double start = 0;
			double end = 0;
			double time_Cycle = 0;
			start = clock(); //Start time
			cout << "Cycle " << cycle << endl << endl;
			cycle++;

			for (int i = 0; i < TLnum; i++) {

				TL[i].setState(3); //Set state to green
				cout << "Traffic Light " << (i + 1) << ":\nGreen\n";
				TL[i].wait(TL[i].getGreentime()); //To elapse greetime
				TL[i].setState(2); //State becomes yellow
				cout << "Yellow\n";
				TL[i].wait(yellowtime); //To elapse yellowtime
				TL[i].setState(1); //State becomes red
				cout << "Red\n" << endl;

			}
			end = clock(); //End time of cycle
			time_Cycle = end - start; //Time for cycle
			SimulationT += time_Cycle; //Time in simulation

			cout << "Time elapsed since start of simulation: " << (SimulationT / CLOCKS_PER_SEC) << " seconds\n" << endl;

			if (SimulationT >= (updatetime * CLOCKS_PER_SEC)) { //Check if total time elapsed is greater than or equal to updatetime
				updateTiming(); //Update green times from new sensor info in data file
				cout << "\nThe time for the updated simulation will now be reset\n" << endl;
				SimulationT = 0;
				cycle = 1;
			}
			//Now cycles restart
		}
	}

	void updateTiming() {
		cout << "\nGreen times for all traffic lights will now be updated\n";
		readTrafficData(); //Reads new data stored by sensors
		calculate_greentime(); //To update greentimes
	}
};
