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

    Beacon_struct new_beacon; // Create new beacon record
    string temptime; // Create temporary variable for converting string to int

    new_beacon.macName = row.at(0); // set transmitter ID
    temptime = row.at(1).substr(0,row.at(1).length()-3); // Set temp string to timestamp without milliseconds
    new_beacon.timestamp = stoi(temptime); // set timestamp in int form
    new_beacon.rxid = row.at(2); // set receiver ID
    new_beacon.rssi = stoi(row.at(3)); // set recevied strength in int form

    return new_beacon; // return the newly created beacon report
}

void Beacon::AddBeacon(vector<Beacon_struct> &beacon_vector, Beacon_struct received_beacon) {
    // Adds a beacon to the vector
    // Should use BeaconSort to sort by timestamp

    int n = beacon_vector.size(); // temp variable for math operations

    if (n == 0) { // If vector is empty
        beacon_vector.push_back(received_beacon); // Just add the beacon with no more checks
    } else if (received_beacon.timestamp >= beacon_vector.at(n-1).timestamp) { // otherwise, check if the new timestamp is greater than or equal to the last timestamp in the vector
        beacon_vector.push_back(received_beacon); // Add the beacon to the end
        } else { // if the timestamp is earlier than the last beacon in the vector
            beacon_vector.push_back(received_beacon); // go ahead and add the new one...
            BeaconSort(beacon_vector); // but then run a sort
        }

}

void Beacon::RemoveBeacon(vector<Beacon_struct> &beacon_vector, int maximum_length) {
    // Removes a beacon if the vector gets too large

}

Position_struct Beacon::GetCurrent(vector<Beacon_struct> beacon_vector) {
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

void Beacon::BeaconSort(vector<Beacon_struct> &beacon_vector){
    // Sorts the beacon vector

    Beacon_struct tempbeacon; // create a temp beacon variable for swapping
    int n = beacon_vector.size() - 1; // set the last value of the vector
    int m = n; // start with the size of vector-1

    while (beacon_vector.back().timestamp >= beacon_vector.at(m).timestamp) { // find the first timestamp from the end that is smaller
        m = m - 1; // move backwards 1 value
    }
    
    if (m < 0) { // check for first sort
        m = 0; // set to first value
    }

//cout << "sort: " << beacon_vector.back().timestamp << "," << beacon_vector.back().macName << "," << beacon_vector.back().rxid << "," << beacon_vector.back().rssi << "," << m << "," << n << endl;

    tempbeacon = beacon_vector.back();
    beacon_vector.insert(beacon_vector.begin() + m, tempbeacon);
    beacon_vector.pop_back();


}

