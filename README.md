## cspb2270finalproject

### CSPB 2270 – Fall 2023 – Final Project Proposal
### Title: Tracking cats using Bluetooth trackers, aka “Cat Track Fever”
### Aaron Quinto


**Problem:**

I have 2 cats I let outside on most days. I want to be able to know when they go too far from the house for too long. They both have Bluetooth trackers on their collars. The trackers transmit a beacon every 2 seconds. I have 2 Bluetooth sniffers in the house: 1 in front and 1 in back. It’s possible a signal will only be received by 1 receiver and not the other, or neither, so those possibilities need to be accounted. Also, the collection window is 15 seconds. That means every 15 seconds, a collection script will run on each receiver and saves only the most recent beacon. Therefore, 0 or 1 beacon can be received within a 15 second time frame per receiver and the program needs to account for this variability.

**Solution:**

The trackers allow me to determine which side of the house they’re on and estimating the distance from that point using the received signal strength measurements. The receivers collect multiple pieces of information about each beacon, including a unique identity number, a timestamp of when the beacon arrived in milliseconds, and the received signal strength at that timestamp. The receivers only save 1 instance per named transmitter per 15 second interval.

By coordinating the beacon’s timestamp and signal strength between both receivers, we can calculate an estimated direction and distance from the house. As examples, we can demonstrate the collected data and expected output:
1. Both receivers:
    1. Front = -60
    1. Back = -80
    1. Center point is +20 from the center of the house.
    1. The estimated range is 60 + 80 = 140 feet around that point.
    1. This tells us the cat is in front of the house, but could be across the street, or up to houses to each side.
1. One receiver:
    1. Front = 0 (no signal in the last 15 seconds)
    1. Back = -70
    1. Center point is -20 from the center of the house.
    1. The estimated range is 0 + 70 = 70 feet around that point.
   1. This tells us the cat is in back of the house and directly behind as the front did not receive a signal.

(Change from proposal which suggested using arrays of fixed lengths.)
Using a vector, we can load all of the signal reports in a CSV file to a dynamically-sized vector and search that vector as needed. Originally in the proposal, I was attempting to manage memory usage more, but that's not necessary. The servers and computers running this program have plenty of memory. The vector will be split into 2 separate new vectors, one per cat, to then create a position and path.


**Data structures:**

Beacon_structure:
- macName (MAC address as string) Per tracker ID is the MAC address of the tracker
- timestamp (integer in nanoseconds)
- rxid (string) Receiver ID
- rssi (integer in dBm) Received Signal Strength

Beacon_vector:
- A vector of Beacon_structures
- needs to be sorted by timestamp

pepper_vector: (new from proposal)
- A vector of Beacon_structures
- Contains only beacons from cat named "Pepper"
- Sorted by timestamp

jack_vector: (new from proposal)
- A vector of Beacon_structures
- Contains only beacons from cat named "Jack"
- Sorted by timestamp

Position_structure:
- Front distance (integer) distance from front receiver using signal strength as a reference (New from proposal)
- Back distance (integer) distance from back receiver using signal strength as a reference (New from proposal)
- Relative position (integer) Position relative to middle of house
- Relative distance (integer) Estimated distance relative to the position point
- Timestamp (integer) Time of received beacon in seconds, not milliseconds (New from proposal)


Public member functions:
- void BuildBeacon(vector-string row)
    - Creates a new beacon using each line from the CSV file
    - Called per line read from the CSV file
- void AddBeacon(vector-Beacon_structure &beacon_vector, Beacon_structure received_beacon)
    - Adds the most recent beacon to the array or list
    - Needs to insert in time order, which may not happen sequentially, so a search process needs to happen to insert it in the correct order. This calls BeaconSort to handle the sorting.
    
    ~~- Asks CheckLength() if the new beacon can be added.~~
    ~~- May need to call a “sort” function to make sure the beacon is added in order of the timestamp.~~
    
~~- void RemoveBeacon(Beacon_structure beacon_array, int maximum_length)
    - Removes the oldest beacons to keep the array from being infinitely long
    - Uses a maximum_length value to remove as many values as necessary.~~
    
- ~~Position_structure[]~~ void GetPath(vector-Beacon_structure beacon_vector, string macName, string fnameout, string RX1, string RX2)
    - Generates a path for the requested tracker
    - The output is printed to the terminal and a file using integers representing the position relative to the middle of the house, and the estimated distance from that point. Positive position numbers indicate the front and negative position numbers indicate the back. The distance is always positive and is used to generate circle or half-circle when a UI is implemented.
    - The macName searches for beacons by that name and only pulls out those reports.
    - The fnameout is the filename for the output file, which is defined in main.cpp and passed to the function.
    - The RX1 and RX2 strings are constants in the main.cpp file which define the names of the receivers.
    

**Private member functions:**

~~- bool CheckLength(Beacon_structure beacon_array)
    - Checks to make sure there room to add a new beacon report in the array~~
- void BeaconSort(vector-Beacon_structure &beacon_array)
    - This may or may not be required, so I’m adding it in the proposal in case it is.
    - This will sort the beacon_array by timestamp.
    - Hopefully this won’t be needed and I can sort the beacon as it’s added to the array, but there could be difficulties with that related to available space in the array.
- Position_structure GetCurrent(vector-Beacon_structure beacon_vector, int current_position, string RX1, string RX2)
    - Return the last position and estimated distance of the tracker ID by calculating most recent front and back reports together.
    - The function needs to verify the received beacons occurred within 15 seconds of each other, which is the collection window. If the previous beacon is not within 15 seconds, assume it was not received and only use the current value as the good piece of data.

**Testing procedure:**


~~I plan on gathering and saving data while the cats are outside and running it through the AddBeacon() function until I hit a certain number, then start running other functions like GetCurrent() to make sure it finds the “current” position at that time. As long as it works, I can then start removing and adding beacons and get a position each time. The ideal method of inputting the data is to have a CSV file with all the points that we can read in and run the AddBeacon() function for each point. The less elegant method is to generate a bunch of AddBeacon() calls in the Main() function to add them, but that would be really ugly and waste of CPU and compiler time. The problem in both cases is the output from the receivers is in JSON format. That format has to be converted to CSV to be useful.~~


Updated from proposal:
I did gather and save data while the cats were outside. It was in JSON format, so I had to convert that to a CSV file first by using a spreadsheet editor. The data is examined line by line and sent through AddBeacon() to add it to the vector of all beacons in the file. After being added to the vector, if the timestamp is less than the last beacon, the AddBeacon() function calls the BeaconSort() function to put it in the correct order.

After the entire CSV file has been read into the vector, the main.cpp program runs through the vector to separate the reports into 2 new vectors: one per cat/tracker ID name. The GetPath() function repeatedly calls the GetCurrent() function to create a list of position reports. Those are printed to the terminal, plus written to a file. Each cat/tracker gets a separate file. The output and file show an estimated path of where the cat went, relative to the center of the house.


~~At the end of the program, I plan on running GetPath() to see if it generates a path the cat(s) followed. This should generate an output of integer pairs using the Position_structure of all the points currently in the array.~~


**Alternatives:**

I chose to use a ~~simply array~~ vector for this project instead of something more complex such as a linked list because the structure is in order by time. We’re not likely to search for a particular point in time to find the position at a specific time. Therefore, instead of adding complexity and writing time to the program, we’ll use a simpler design that is ideal for creating a specific order of points. The points still need to be sorted by time, but they do not need to be quickly searched.
