#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "../code/cattrackfever.cpp"

using namespace std;

int main(){

    // Declare some contants
    const string PEPPER = "E1:3B:27:F4:89:31";
    const string JACK = "F2:6D:89:DF:9B:04";
    const string RX1 = "mt-knot-front";
    const string RX2 = "mt-knot-back";
    const string FNAME_IN = "../cattrackfever.csv";
    const string FNAME_PEPPER_PATH = "../cattrackfever-pepper-path.csv";
    const string FNAME_JACK_PATH = "../cattrackfever-jack-path.csv";

    // Declare some more variables
    string line, word; // String variables for reading input
    vector<string> row; // Temp vector for reading in file
    vector<vector<string>> content; // Temp vector for decoding each row
    Beacon_struct tempBeacon; // Temp beacon structure for working
    Position_struct tempPos; // Temp position structure for working
    vector<Beacon_struct> beacon_vector; // Total vector for all beacon reports
    vector<Beacon_struct> pepper_vector; // Vector for Pepper's beacons
    vector<Beacon_struct> jack_vector; // Vector for Jack's beacons
    Beacon beacons; // Define the class to use

    // Open input CSV file
    fstream filein (FNAME_IN, ios::in);

    if(!filein.is_open()) {
        cout << "\nCould not open input file, so quitting.\n\n";
        return 1;
    }

    // Open output file 1 for writing
    fstream fileout1 (FNAME_PEPPER_PATH, ios::out);

    if(!fileout1.is_open()) {
        cout << "\nCould not open output file, so quitting.\n\n";
        return 1;
    }

    // Open output file 2 for writing
    fstream fileout2 (FNAME_JACK_PATH, ios::out);

    if(!fileout2.is_open()) {
        cout << "\nCould not open output file, so quitting.\n\n";
        return 1;
    }


    //Read in CSV file
    while(getline(filein, line)){

        row.clear();

        if (line.length() > 5) {
            stringstream str(line);
    
            // Following is the take each line from CSV file and push into a single vector
            //while(getline(str, word, ',')) {
            //    row.push_back(word);
            //}
            //content.push_back(row);


            // Now instead of above, we're taking each part of the line and putting into a structure
            while(getline(str,word, ',')) {
                row.push_back(word); // split the CSV row into parts for processing
            }

            tempBeacon = beacons.BuildBeacon(row); // create a temp Beacon

            beacons.AddBeacon(beacon_vector, tempBeacon);
            //cout << beacon_vector.back().timestamp << "," << beacon_vector.back().macName << "," << beacon_vector.back().rxid << "," << beacon_vector.back().rssi << "," << beacon_vector.size() << endl;
            //cout << "size: " << beacon_vector.size() << endl;
        }
    }

    // Split the total vector into separate vectors per transmitter ID using constants
    for (int i = 0; i < int(beacon_vector.size()); i++) {
        if (beacon_vector.at(i).macName == PEPPER) {
            pepper_vector.push_back(beacon_vector.at(i));
        } else if (beacon_vector.at(i).macName == JACK) {
            jack_vector.push_back(beacon_vector.at(i));
        }
    }

    // Scan each vector for the current position
    for (int i = 0; i < int(pepper_vector.size()); i++) {
        tempPos = beacons.GetCurrent(pepper_vector, i, RX1, RX2);
        cout << "Pepper,Timestamp: " << tempPos.timestamp << ",Position: " << tempPos.relativePosition << ",Distance: " << tempPos.relativeDistance << endl;
        fileout1 << "Pepper,Timestamp: " << tempPos.timestamp << ",Position: " << tempPos.relativePosition << ",Distance: " << tempPos.relativeDistance << endl;
    }

    for (int i = 0; i < int(jack_vector.size()); i++) {
        tempPos = beacons.GetCurrent(jack_vector, i, RX1, RX2);
        cout << "Jack,Timestamp: " << tempPos.timestamp << ",Position: " << tempPos.relativePosition << ",Distance: " << tempPos.relativeDistance << endl;
        fileout2 << "Jack,Timestamp: " << tempPos.timestamp << ",Position: " << tempPos.relativePosition << ",Distance: " << tempPos.relativeDistance << endl;
    }

    return 0; // Finish successfully
}