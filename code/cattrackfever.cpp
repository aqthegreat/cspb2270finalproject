#include "cattrackfever.h"
#include <vector>
#include <stdlib.h>
#include <string>
#include <iostream> //added for troubleshooting

Beacon::Beacon() {
    //Constructor if needed
};

Beacon::~Beacon() {
    //Deconstructor if needed
};


Beacon_struct Beacon::BuildBeacon(vector<string> row) {

    Beacon_struct new_beacon;
    string temptime;

    new_beacon.macName = row.at(0);
    temptime = row.at(1).substr(0,row.at(1).length()-3);
    new_beacon.timestamp = stoi(temptime);
    new_beacon.rxid = row.at(2);
    new_beacon.rssi = stoi(row.at(3));

    return new_beacon;
}

void Beacon::AddBeacon(vector<Beacon_struct> &beacon_vector, Beacon_struct received_beacon) {
    // Adds a beacon to the vector
    // Should use BeaconSort to sort by timestamp

    beacon_vector.push_back(received_beacon);

}

void Beacon::RemoveBeacon(vector<Beacon_struct> &beacon_vector, int maximum_length) {
    // Removes a beacon if the vector gets too large

}

Position_struct Beacon::GetCurrent(Beacon_struct beacon_vector) {
    Position_struct tempPos;
    // Outputs the current location of the cat, or last known location

    return tempPos;
}

/* Stretch Goal of creating a path
Position_struct[] Beacon::GetPath(Beacon_struct beacon_vector) {
    // Creates a path from all of the beacon reports to show how the cat walked

}
*/

bool Beacon::CheckMaxLength(Beacon_struct beacon_vector, int maximum_length) {
    // Checks if the vector has reached a maximum length

    return false;
}

void BeaconSort(Beacon_struct &beacon_vector){
    // Sorts the beacon vector
    
}

