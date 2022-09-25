/*---------------------------------------------------------------------------------------*/
/* Name: Muhammad Zaeem Shahzad, Student ID: ms12297 */
/* Date: November 27, 2020 */
/* Program: assignment4.cpp */
/* Description: Traffic Light Control System: This program simulates the control of traffic
lights at an intersection, displaying their characteristic details at set time intervals */
/*---------------------------------------------------------------------------------------*/

#include <iostream> //For input/output
#include <fstream> //For file-handling
#include <iomanip> //For output manipulation eg: in tabular format
#include<sstream> //For strings' content handling eg: getline function
#include <cmath> //For complex calculations
#include<ctime> //For use of time functions
#include "TrafficLight.h" //Contains the TrafficLight class
#include "Intersection.h" //Contains the Intersection class

using namespace std;

int main() {

	Intersection road; //Intersection instance
	int TLnum; //Number of traffic lights user wants to add
	int y = 1; //Counter for loops

	cout << "Welcome to the Traffic Light Control System Simulator!\n";
	cout << "You can run a simulation of traffic lights at an intersection in this program\n";
	cout << "Note that the program supports a maximum of 5 traffic lights at the intersection\n";

	while (y == 1) {
		cout << "\nEnter the number of traffic lights (not more than 5) you want to simulate at the intersection: \n";
		cout << "You may enter 0 to exit program\n";

		if (!(cin >> TLnum)) {
			//To clear the buffer memory
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Please enter a positive integer!\n";
			continue;
		}

		else {
			if (TLnum > 5) {
				cout << "You must enter an integer value less than 5!\nTry again\n";
				continue;
			}
			if (TLnum <= 0) {
				cout << "You chose to exit, please confirm\n";
				y = 0;
			}
			if (TLnum > 0 && TLnum <= 5) {
				for (int i = 0; i < TLnum; i++) {
					road.AddLight();
				}
				cout << "Enter the name of the file that contains the traffic information stored by the sensors: \n";

				//Clearing buffer memory for input stream
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				//Prompting input of filename
				getline(cin, filename);

				road.readTrafficData(); //Read data from input file
				road.calculate_greentime(); //Calculate greentimes for all traffic lights
				road.run(); //Run simulation
			}
		}

		//Exit display
		cout << "\nTo " << endl;
		cout << left << setw(35) << "Return to the start of program:" << setw(35) << "Exit the program:" << endl;
		cout << left << setw(35) << "Enter 1" << setw(35) << "Enter 0\n" << endl;

		//Validating counter for the return to start loop
		//To ensure that y can only be 1 or 0

		if (!(cin >> y)) { //To prompt for input of y AND validate an integer input

			//To clear the buffer memory
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "\nInvalid selection!\nYou will now be returned to the start of program\n" << endl;
			y = 1;
		}

		if (y != 1 && y != 0) { //To validate input of only 1 or 0
			cout << "\nInvalid selection!\nYou will now be returned to the start of program\n" << endl;
			y = 1;
		}

	}

	return 0;
}

