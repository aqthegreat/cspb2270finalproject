#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "../code/cattrackfever.cpp"

using namespace std;

int main(){

    string fname_in = "../cattrackfever.csv";
    string fname_out = "../cattrackfever-out.csv";

    //string macName, rxid; // String variables for data
    string line, word; // String variables for reading input
    //int timestamp, rssi; // integer variables for data
    vector<string> row;
    vector<vector<string>> content;
    Beacon_struct tempBeacon;
    vector<Beacon_struct> beacon_vector;
    Beacon beacons;

    fstream filein (fname_in, ios::in);

    if(!filein.is_open()) {
        cout << "\nCould not open input file, so quitting.\n\n";
        return 1;
    }

    fstream fileout (fname_out, ios::out);

    if(!fileout.is_open()) {
        cout << "\nCould not open output file, so quitting.\n\n";
        return 1;
    }

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

    /*
    //Print and create output file of read in values
    for(int i=0;i<content.size();i++)
    {
        for(int j=0;j<content[i].size();j++)
        {
            cout<<content[i][j];
            fileout << content[i][j];
            if (j != content[i].size()-1) {
                cout << ",";
                fileout << ",";
            }
        }
        cout<<endl;
        fileout<<endl;
    }
    */

    return 0;
}