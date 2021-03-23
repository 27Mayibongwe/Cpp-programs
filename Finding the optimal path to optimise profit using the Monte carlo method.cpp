#include <iostream>
#include <cstdlib>
#include <vector>
#include <time.h>
using namespace std;
struct path_type {
string sourch_location,
destination_location;
double distance;
//Constructors
path_type(void);
path_type(string sourch_location,string destination_location,double distance);
//Member functions
void print();
};
path_type::path_type(void) {
sourch_location="";
destination_location="";
distance=0.0;
}
path_type::path_type(string sourch_location,string destination_location,double distance) {
this->sourch_location=sourch_location;
this->destination_location=destination_location;
this->distance=distance;
}
void path_type::print() {
cout << " Travel " << distance << " km from " << sourch_location << " to "
<< destination_location << endl;
}
int main() {
//Set Random time seed
srand(time(NULL));
//Create list of paths from one location to another
vector<path_type> path_list;
path_list.push_back(path_type("Sun City","Tzaneen",480.0));
path_list.push_back(path_type("Tzaneen","Sun City",480.0));
path_list.push_back(path_type("Sun City","Johannesburg",202.0));
path_list.push_back(path_type("Johannesburg","Sun City",202.0));
path_list.push_back(path_type("Sun City","Kuruman",499.0));
path_list.push_back(path_type("Kuruman","Sun City",499.0));
path_list.push_back(path_type("Johannesburg","Tzaneen",411.0));
path_list.push_back(path_type("Tzaneen","Johannesburg",411.0));
path_list.push_back(path_type("Johannesburg","Nelspruit",341.0));
path_list.push_back(path_type("Nelspruit","Johannesburg",341.0));
path_list.push_back(path_type("Johannesburg","Durban",468.0));
path_list.push_back(path_type("Durban","Johannesburg",468.0));
path_list.push_back(path_type("Johannesburg","Bloemfontein",397.0));
path_list.push_back(path_type("Bloemfontein","Johannesburg",397.0));
path_list.push_back(path_type("Johannesburg","Kuruman",528.0));
path_list.push_back(path_type("Kuruman","Johannesburg",528.0));
path_list.push_back(path_type("Bloemfontein","Kuruman",401.0));
path_list.push_back(path_type("Kuruman","Bloemfontein",401.0));
path_list.push_back(path_type("Bloemfontein","Durban",635.0));
path_list.push_back(path_type("Durban","Bloemfontein",635.0));
path_list.push_back(path_type("Bloemfontein","East London",570.0));
path_list.push_back(path_type("East London","Bloemfontein",570.0));
path_list.push_back(path_type("Bloemfontein","Beaufort West",543.0));
path_list.push_back(path_type("Beaufort West","Bloemfontein",543.0));
path_list.push_back(path_type("Cape Town","Beaufort West",462.0));
path_list.push_back(path_type("Beaufort West","Cape Town",462.0));
path_list.push_back(path_type("Cape Town","Springbok",561.0));
path_list.push_back(path_type("Springbok","Cape Town",561.0));
path_list.push_back(path_type("Beaufort West","East London",580.0));
path_list.push_back(path_type("East London","Cape Town",580.0));
path_list.push_back(path_type("Beaufort West","Springbok",773.0));
path_list.push_back(path_type("Springbok","Beaufort West",773.0));
path_list.push_back(path_type("Springbok","Kuruman",637.0));
path_list.push_back(path_type("Kuruman","Springbok",637.0));
path_list.push_back(path_type("Durban","East London",659.0));
path_list.push_back(path_type("East London","Durban",659.0));
path_list.push_back(path_type("Durban","Nelspruit",679.0));
path_list.push_back(path_type("Nelspruit","Durban",679.0));
path_list.push_back(path_type("Nelspruit","Tzaneen",282.0));
path_list.push_back(path_type("Tzaneen","Nelspruit",282.0));
unsigned int max_iterations=1000;
vector<path_type> best_path;
double best_total_distance_travelled,
best_total_petrol_cost,
best_total_profit=0.0;
for(unsigned int iter=0;iter<max_iterations;iter++) {
//Generate random input - generate random path starting from Johannesburg that does not cross the same locations again
vector<path_type> curr_path_list;
while(1) {
//Set my current location, start at location "Johannesburg" or use previous path's end location
string current_location="Johannesburg";
if(curr_path_list.size()>0)
current_location=curr_path_list[curr_path_list.size()-1].destination_location;
//Compile vector list of all paths that travel from this location and have not yet been visited
vector<path_type> path_sublist;
for(unsigned int p_id=0;p_id<path_list.size();p_id++) {
//Possible travel path
if(current_location.compare(path_list[p_id].sourch_location)==0) {
//Check if path has been visited before, make sure it does return to any
//of your source or destination addresses
bool visited_flag=false;
for(unsigned int mp_id=0;mp_id<curr_path_list.size();mp_id++) {
if((curr_path_list[mp_id].sourch_location.compare(path_list[p_id].destination_location)==0) ||
(curr_path_list[mp_id].destination_location.compare(path_list[p_id].destination_location)==0))
visited_flag=true;
}
if(!visited_flag)
path_sublist.push_back(path_list[p_id]);
}
}
//Select single random path from possible next paths
if(path_sublist.size()>=1) {
unsigned int rand_index=rand()%path_sublist.size();
curr_path_list.push_back(path_sublist[rand_index]);
}
else //No where to go, no more path options left
break;
}
//Perform Experiment - calculate petrol costs and profit
double petrol_price_per_liter=14.23,
vehicle_range_per_liter=7.5; // 6.5 km per liter of petrol
//Calculate total range travelled for path
double total_distance_traveled=0.0;
for(unsigned int p_id=0;p_id<curr_path_list.size();p_id++)
total_distance_traveled+=curr_path_list[p_id].distance;
//Calculate Petrol cost for complete trip
double total_petrol_cost=total_distance_traveled/vehicle_range_per_liter*petrol_price_per_liter;
//Calculate Total Profit for entire trip - remember to deduct fuel costs and you will
//receive R5000 for each unique location that was visited
double total_profit=curr_path_list.size()*5000.0-total_petrol_cost;
//Save path and info of most profitable trip
if (total_profit>best_total_profit) {
best_path=curr_path_list;
best_total_distance_travelled=total_distance_traveled;
best_total_petrol_cost=total_petrol_cost;
best_total_profit=total_profit;
}
}
//Display bests solutions information
cout << "Information of the optimal path" << endl;
cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
cout << "Total Distance Travelled: " << best_total_distance_travelled << " km" << endl;
cout << "Total Petrol price: R " << best_total_petrol_cost << endl;
cout << "Total Profit: R" << best_total_profit << endl;
cout << "Travel plan: " << endl;
for(unsigned int p_id=0;p_id<best_path.size();p_id++)
best_path[p_id].print();
return 0;
}
