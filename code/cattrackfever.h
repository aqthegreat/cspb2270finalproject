#ifndef CATTRACKFEVER_H__
#define CATTRACKFEVER_H__

#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Beacon_struct {
    string macName;
    int timestamp;
    string rxid;
    int rssi;
};

struct Position_struct {
    int distanceFront;
    int distanceBack;
    int relativePosition;
    int relativeDistance;
    int timestamp;
};

class Beacon {
    public:
    Beacon();
    // Constructor

    ~Beacon();
    // Deconstructor

    Beacon_struct BuildBeacon(vector<string> row);
    // Creates the received beacon structure to be used when adding to the vector

    void AddBeacon(vector<Beacon_struct> &beacon_vector, Beacon_struct received_beacon);
    // AddBeacon adds the current beacon read in from the input file into the vector

    void GetPath(vector<Beacon_struct> beacon_vector, string macName, string fnameout, string RX1, string RX2);
    // Create an estimated path the cats walked


    private:
    void BeaconSort(vector<Beacon_struct> &beacon_vector);
    // Sort the vector of beacons by timestamp

    Position_struct GetCurrent(vector<Beacon_struct> beacon_vector, int current_position, string RX1, string RX2);
    // Get the current position of the cat, or at least the last known location
};


#endif  // CATTRACKFEVER_H__
