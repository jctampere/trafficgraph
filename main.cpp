/* 
 * File:   main.cpp
 * Author: jc79478
 *
 * Created on 1. heinäkuuta 2014, 15:56
 */


#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;
/* Define stopvertext class
 *
 */
class Stopvertex {
      private: 
         int stop_id;
         string stop_name;
         double stop_lat, stop_lon;
      public: 
      Stopvertex(int id, string name, double lat, double lon){
             stop_id = id;
             stop_name = name;
             stop_lat = lat;
             stop_lon = lon;
              }
          int getStopID(){
             return stop_id;
              }
          string getStopName(){
             return stop_name;
              }
          double getStoplat(){
             return stop_lat;
              }
          double getStoplon(){
              return stop_lon;
              }
};
/* Define edge class
 *
 */
//class 
/*Read Stops.txt file and put the stops information into vector
 * 
 */
vector <Stopvertex> getStops();

/*get edges from GTFS files (ongoing)
 * 
 */
//vector <Edge> getEdges();

int main(int argc, char** argv) {
    vector <Stopvertex> stops;
    stops = getStops();

    //print stops 
    vector<Stopvertex>::iterator i;
    cout << "stops are: "<< endl;
    for (vector<Stopvertex>::iterator i = stops.begin(); i!=stops.end(); ++i){
       
        cout << (*i).getStopID() << ","<<(*i).getStopName()<<","<<(*i).getStoplat()<<","<<(*i).getStoplon()<< endl;
    }
    return 0;
}

/*Read Stops.txt file and put the stops information into vector
 * 
 */
vector <Stopvertex> getStops(){
    vector <Stopvertex> stopsfromfile;
    ifstream file;
    file.open("stops1.txt");
    
    int id;
    //string code;
    string name;
    double lat;
    double lon;
    
    string line;

    if (!file){
     cerr << "Failed to open file" << endl;
     exit(1); 
     }
    while ( getline(file,line))
    {
        stringstream lineStream(line);
        string value;
        getline(lineStream, value, ','); 
        id =atof(value.c_str());              
        std::getline(lineStream, value, ','); 
        //code = value;  
        std::getline(lineStream, value, ','); 
        name = value;
        std::getline(lineStream, value, ','); 
        lat = atof(value.c_str());
        std::getline(lineStream, value); 
        lon = atof(value.c_str());  
        cout.precision(15);
        // cout << id << ","<<name<<","<<lat<<","<<lon<< endl;
        stopsfromfile.push_back(Stopvertex(id,name,lat,lon));
     } 
    file.close();

   
    return stopsfromfile;
}