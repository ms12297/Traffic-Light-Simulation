# Traffic-Light-Simulation: A Civil Engineering Case Study


## Programming aspects learned and implemented:
* Object Oriented Programming


## Background
This project involves the design of a software to control a system of traffic lights at an intersection. An intersection consists of two streets that cross at right angles. For simplicity, each street has a single lane in each direction (no lanes designated for left turn). The software controls the 4 traffic lights (2 direction x 2 roads).

The system has the following components:
1. Traffic semaphores (signal lights): these are standard semaphores with three lights: red, yellow, and green.

2. Traffic sensors that are embedded in each lane near the intersection to record the traffic flow for all roads (4 sensors generating 4 traffic rate values when four traffic lights are used). The sensors save the traffic rate information into a file (average number of vehicles per hour passing through a particular road in one direction).

3. The signals operate in a conventional fashion. Traffic is allowed to move on one road, say R1, and then the next (R2), alternatively across the four roads of the intersection. Assuming that the four traffic lights are represented as L1, L2, L3, and L4, the system operates as follows:

a. Traffic light (L1) is green for a duration calculated based on the traffic flow rate in road R1, the other traffic lights (L2, L3, and L4) are red. 

b. L1 becomes yellow for X seconds (X being a constant value). The Department of Transportation's traffic manual recommends that yellow lights are between 3 and 6 seconds long. Other traffic lights (L2, L3, and L4) remain in red state.

c. Then, traffic light L2 becomes green for a duration calculated based on the traffic flow rate in road R2. Meanwhile, L1, L3, and L4 are red. 

d. Traffic light L2 becomes yellow for X seconds (X being a constant value). Other traffic lights (L1, L3, and L4) remain in red state.

e. Then, traffic light L3 becomes green for a duration calculated based on the traffic flow rate in road R3. Meanwhile, traffic lights L1, L2, and L4 are red. 

f. Traffic light L3 becomes yellow for X seconds (X being a constant value). Other traffic lights (L1, L2, and L4) remain in red state.

g. Then, traffic light L4 becomes green for a duration calculated based on the traffic flow rate in road R4. Meanwhile, traffic lights L1, L2, and L3 are red. 

h. Traffic light L4 becomes yellow for X seconds (X being a constant value). Other traffic lights (L1, L2, and L3) remain in red state.

i. The next cycle starts with traffic light L1 becoming green again, and so on.

4. The green timings for the traffic lights are updated regularly based on traffic flow. The program assumes that the traffic information is stored in a file (cycle time and traffic flow rates). Every specific duration (say 24 hours), the data is read from the file, the green timings are updated based on the latest traffic condition, and the control proceeds with the updated green timings. 

## Implementation

I developed two classes: TrafficLight to store information about individual traffic light and Intersection to store a collection of TrafficLight objects to manage traffic lights at an intersection. 

The class TrafficLight provides storage for a traffic light’s ID, state (an integer with value of 0 for off, 1 for red, 2 for yellow, and 3 for green), a variable to store the timing value for green state, and a static variable to store the total number of traffic light initiated from the TrafficLight class. Note the following:
1. The constructor function initializes the traffic light state to 1 (red) and the green timer to 0. 
2. The traffic light ID is auto-generated and can only be retrieved. 
3. The wait() function is an auxiliary function to pass a specific number of seconds and return only after the stipulated number of seconds.
4. The printLightInfo() function displays the traffic light information on the output screen. 

The Intersection class stores the cycle length, the number of traffic lights that are currently added to the intersection, an array of the TrafficLight objects (maximum number of traffic lights per intersection is defined through a constant variable or a symbolic constant), and the traffic flow rates. Cycle length is composed of the total signal time to serve all of the signal phases including the green time plus any change interval. Longer cycles will accommodate more vehicles per hour but that will also produce higher average delays. The green timing for each traffic light is proportional to the traffic flow rate reported for the same road, according to the following equation:

<div align="center">
  ### $d_i = {Q_i \over Q_T} × C$
</div> 

### $d_i = {Q_i \over Q_T} × C$

Where �" is the green time for the ith traffic light, �" represents the traffic flow (number of vehicles per 
hour) crossing the ith traffic light, �+ represents the total traffic flow passing through the intersection, and 
� represents the cycle length in seconds. Note that the cycle length and traffic flow information must be 
read from a file (where it is assumed that the sensory data is written into). 
Note the followings:
1. The constructor initializes the number of lights to zero. Other data members must be initialized to 
safe values whenever appropriate.
2. AddLight()adds a new traffic light object to the existing array of Light objects.
3. droplight()searches for a traffic light through its ID and removes it from the array if exists.
4. The run()executes the simulation by running the traffic lights in sequence. This function must 
also update the green timings as per the specified interval. 
5. The readTrafficData()reads the cycle time and the traffic flow rates from the file and store 
in appropriate data members. The file has the following structure: cycle time, traffic flow for road 
R1, traffic flow for road R2, traffic flow for R3, etc., all on separate lines.
6. The updateTiming()calculates the green timings for all the roads and saves the green timing 
values in the respective traffic light object. It is assumed that green timings are updated every 
specific interval (for example, every 24 hours). 
