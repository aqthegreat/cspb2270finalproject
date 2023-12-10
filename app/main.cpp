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
    //Position_struct tempPos; // Temp position structure for working
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

    //Read in CSV file
    while(getline(filein, line)){

        row.clear();

        if (line.length() > 5) {
            stringstream str(line);

            // Now instead of above, we're taking each part of the line and putting into a structure
            while(getline(str,word, ',')) {
                row.push_back(word); // split the CSV row into parts for processing
            }

            tempBeacon = beacons.BuildBeacon(row); // create a temp Beacon

            beacons.AddBeacon(beacon_vector, tempBeacon);
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

    // Write the path the cat walked to a file
    beacons.GetPath(pepper_vector, PEPPER, FNAME_PEPPER_PATH, RX1, RX2);
    beacons.GetPath(jack_vector, JACK, FNAME_JACK_PATH, RX1, RX2);

    return 0; // Finish successfully
}