#ifndef CATTRACKFEVER_H__
#define CATTRACKFEVER_H__

#include <string>
#include <vector>

using namespace std;

struct Beacon_struct {
    string macName;
    int timestamp;
    string rxid;
    int rssi;
};

struct Position_struct {
    int positionFront;
    int positionBack;
    int distanceFront;
    int distanceBack;
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
    
    void RemoveBeacon(vector<Beacon_struct> &beacon_vector, int maximum_length);
    // RemoveBeacon removes a beacon from the vector and uses the maximum_length integer as the vector's maximum length
    // to decide if a beacon needs to be removed or not.

    Position_struct GetCurrent(vector<Beacon_struct> beacon_vector);
    // Get the current position of the cat, or at least the last known location

    //Position_struct[] GetPath(Beacon_struct beacon_vector);
    // Create an estimated path the cats walked

    private:
    bool CheckMaxLength(Beacon_struct beacon_vector, int maximum_length);
    // Check if the vector has reached a maximum set length

    void BeaconSort(vector<Beacon_struct> &beacon_vector);
    // Sort the vector of beacons by timestamp

};


#endif  // CATTRACKFEVER_H__
