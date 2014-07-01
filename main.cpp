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
class stopvertex {
      private: 
         string stop_id;
         string stop_name;
         double stop_lat, stop_lon;
      public: 
      stopvertex(string id, string name, double lat, double lon){
             stop_id = id;
             stop_name = name;
             stop_lat = lat;
             stop_lon = lon;
              }
          string getStopID(){
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

/*Read Stops.txt file and put the stops information into vector
 * 
 */
int main(int argc, char** argv) {
    std::vector <stopvertex> stops;
    std::ifstream file;
    file.open("stops1.txt");
    
    string id;
    //string code;
    string name;
    double lat;
    double lon;
    
    std::string line;

    if (!file){
     cerr << "Failed to open file" << endl;
     exit(1); 
     }
    while ( getline(file,line))
    {
        std::stringstream lineStream(line);
        std::string value;
        std::getline(lineStream, value, ','); 
        id = value;              
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
        stops.push_back(stopvertex(id,name,lat,lon));
     } 
    file.close();

    //print stops 
    std::vector<stopvertex>::iterator i;
    cout << "stops are: "<< endl;
    for (std::vector<stopvertex>::iterator i = stops.begin(); i!=stops.end(); ++i){
       
        cout << (*i).getStopID() << ","<<(*i).getStopName()<<","<<(*i).getStoplat()<<","<<(*i).getStoplon()<< endl;
    }
    return 0;
}


