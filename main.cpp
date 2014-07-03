/* 
 * File:   main.cpp
 * Author: jc
 *
 * Created on 1. heinäkuuta 2014, 15:56
 */


#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;
/* Define stopvertext class
 *
 */
class Stop {
      private: 
         int stop_id;
         string stop_name;
         double stop_lat, stop_lon;
      public: 
      Stop(int id, string name, double lat, double lon){
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

class Edge{
    private: 
        Stop startVertex, endVertex;
        vector lines;
        
    public: 
        Edge (Stop start, Stop end, vector ls){
             startVertex = start;
             endVertex = end;
             lines = ls;
           }
        Stop getStartstop(){
              return startVertex;
           }
        Stop getEndstop(){
              return endVertex;
           }
        vector getLines(){
           return lines;
           }
};
 */
/* Define route class
 *

class Route {
      private: 
          int route_id;
          vector<int> trip_ids;
      public: 
          Route(int id, vector<int> t_ids){
              route_id = id;
              trip_ids = t_ids;
          }
          int getRouteID (){
              return route_id;       
             }
          vector<int> getTripIDs (){
              return trip_ids;
               }
          int tripInRoute (int t_id){
              
             for (vector<int>::iterator i = trip_ids.begin(); i!=trip_ids.end(); ++i){
                if( *i == t_id)
                    return route_id;
              }  
               }
          void addTriptoRoute(int t_id){
              trip_ids.push_back(t_id);  
           }
} */
/*Read Stops.txt file and put the stops information into vector
 * 
 */
vector <Stop> getStops();

/*Read trips.txt file and put the route_id, trip_id information into vector
 * 
 */
unordered_map<int, vector<string> > getRoutes();

/* Get stop info from a stop id
 *
 */
//Stop getStop(int s_id); 

/*get edges from GTFS files (ongoing)
 * 
 */
//vector <Edge> getEdges();

int main(int argc, char** argv) {
    vector <Stop> stops;
    unordered_map <int, vector<string> > routes;
    stops = getStops();
    routes = getRoutes();
    //print stops 
    vector<Stop>::iterator i;
    cout << "stops are: "<< endl;
    for (vector<Stop>::iterator i = stops.begin(); i!=stops.end(); ++i){
       
        cout << (*i).getStopID() << ","<<(*i).getStopName()<<","<<(*i).getStoplat()<<","<<(*i).getStoplon()<< endl;
    }

   //print routes 
   for (auto& x: routes){
       cout<<"route: " <<x.first<<" has the following trips";
       for (int i =0; i<x.second.size(); ++i){
         cout <<x.second[i]<<", "; 
         }  
       cout <<endl;
       }
    return 0;
}

/*Read Stops.txt file and put the stops information into vector
 * 
 */
vector <Stop> getStops(){
    vector <Stop> stopsfromfile;
    ifstream file;
    file.open("testdata/stops1.txt");
    
    int id;
    //string code;
    string name;
    double lat;
    double lon;
    
    string line;

    if (!file){
     cerr << "Failed to open stops file" << endl;
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
        stopsfromfile.push_back(Stop(id,name,lat,lon));
     } 
    file.close();

   
    return stopsfromfile;
}

/*Read trips.txt file and put the route_id, trip_id information into unordered_map struct
 * 
 */
unordered_map<int, vector<string> > getRoutes(){
    unordered_map<int, vector<string> >  routesfromfile;
    vector <string> tripids;
    ifstream file;
    file.open("testdata/trips1.txt");
    
    int r_id;
    string t_id;
    
    string line;

    if (!file){
     cerr << "Failed to open trips file" << endl;
     exit(1); 
     }
    while ( getline(file,line))
    {
        stringstream lineStream(line);
        string value;
        //read route_id field
        getline(lineStream, value, ','); 
        r_id =atof(value.c_str());              
        //read service_id field
        getline(lineStream, value, ','); 
        //read trip_id field
        getline(lineStream, value, ','); 
        t_id = value;
        cout<<t_id;
        //ignore shape_id value
        //std::getline(lineStream, value); 
        unordered_map<int,vector<string> >::iterator got = routesfromfile.find(r_id);
        if (got == routesfromfile.end()){
           //if route_id is new, add to routes 
           routesfromfile.insert(make_pair(r_id, vector<string>()));
           routesfromfile.at(r_id).push_back(t_id);
         }else {
           //if route_id exist, add trip_id to the route trip vector
           routesfromfile.at(r_id).push_back(t_id);
         }
        
      
     } 
    file.close();
    return routesfromfile;
 }