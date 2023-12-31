#include "cattrackfever.h"
#include <vector>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>

Beacon::Beacon() {
    //Constructor if needed
};

Beacon::~Beacon() {
    //Deconstructor if needed
};

Beacon_struct Beacon::BuildBeacon(vector<string> row) {
    // Create new beacon record for each line from an input file

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

void Beacon::GetPath(vector<Beacon_struct> beacon_vector, string macName, string fnameout, string RX1, string RX2) {
    // Creates a path from all of the beacon reports to show how the cat walked
    Position_struct tempPos;

    // Open output file 1 for writing
    fstream fileout (fnameout, ios::out);

    if(!fileout.is_open()) {
        cout << "\nCould not open output file, so quitting.\n\n";
        return;
    }

    fileout << "MacName,Timestamp,Position,Distance" << endl;

    for (int i = 0; i < int(beacon_vector.size()); i++) {
        tempPos = this->GetCurrent(beacon_vector, i, RX1, RX2);
        cout << "Timestamp: " << tempPos.timestamp << ",Position: " << tempPos.relativePosition << ",Distance: " << tempPos.relativeDistance << endl;
        fileout << macName << "," << tempPos.timestamp << "," << tempPos.relativePosition << "," << tempPos.relativeDistance << endl;
    }
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

    // Swap values for sorting
    tempbeacon = beacon_vector.back();
    beacon_vector.insert(beacon_vector.begin() + m, tempbeacon);
    beacon_vector.pop_back();


}

Position_struct Beacon::GetCurrent(vector<Beacon_struct> cat_vector, int current_position, string RX1, string RX2) {
    // Outputs the current location of the cat, or last known location
    
    // Setup temp structure for working
    Position_struct tempPos;

    // Set initial values
    tempPos.distanceBack = 0;
    tempPos.distanceFront = 0;

    // Set the current timestamp
    tempPos.timestamp = cat_vector.at(current_position).timestamp; // Set the current timestamp so we know what time we're looking at

    // If this is first or last position
    if (current_position == 0 || current_position == int(cat_vector.size()-1)) {
        if (cat_vector.at(current_position).rxid == RX1) { // If the current position report is for the front receiver
            tempPos.distanceFront = -cat_vector.at(current_position).rssi; // Set rssi, but negate it to a positive number for "front"
        } else if (cat_vector.at(current_position).rxid == RX2) { // Otherwise it's probably the back receiver
            tempPos.distanceBack = cat_vector.at(current_position).rssi; // Set rssi
        }
        return tempPos; // Skip the rest of this function
    }

    // Check if the previous position is within the last 15 seconds
    if ((cat_vector.at(current_position).timestamp - cat_vector.at(current_position-1).timestamp) <= 15) {
        if (cat_vector.at(current_position).rxid == RX1) {
            tempPos.distanceFront = -cat_vector.at(current_position).rssi; // Set rssi, but negate it to a positive number for "front"
            tempPos.distanceBack = cat_vector.at(current_position-1).rssi; // Set rssi
        } else {
            tempPos.distanceFront = -cat_vector.at(current_position-1).rssi; // Set rssi, but negate it to a positive number for "front"
            tempPos.distanceBack = cat_vector.at(current_position).rssi; // Set rssi
        }
    } else { // Else if NOT within the last 15 seconds
        if (cat_vector.at(current_position).rxid == RX1) {
            tempPos.distanceFront = -cat_vector.at(current_position).rssi; // Set rssi, but negate it to a positive number for "front"
        } else {
            tempPos.distanceBack = cat_vector.at(current_position).rssi; // Set rssi
        }
    }

    // Find a position relative to the middle of the house
    tempPos.relativePosition = tempPos.distanceFront + tempPos.distanceBack;
    // Find a estimated distance from the position
    tempPos.relativeDistance = tempPos.distanceFront - tempPos.distanceBack;

    return tempPos;
}
