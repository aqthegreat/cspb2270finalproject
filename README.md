## cspb2270finalproject

### CSPB 2270 – Fall 2023 – Final Project Proposal
### Title: Tracking cats using Bluetooth trackers, aka “Cat Track Fever”
### Aaron Quinto


**Problem:**

I have 2 cats I let outside on most days. I want to be able to know when they go too far from the house for too long. They both have Bluetooth trackers on their collars. The trackers transmit a beacon every 2 seconds. I have 2 Bluetooth sniffers in the house: 1 in front and 1 in back. It’s possible a signal will only be received by 1 receiver and not the other, or neither, so those possibilities need to be accounted. Also, the collection window is 15 seconds. That means every 15 seconds, a collection script will run on each receiver and saves only the most recent beacon. Therefore, 0 or 1 beacon can be received within a 15 second time frame per receiver and the program needs to account for this variability.

**Solution:**

The trackers allow me to determine which side of the house they’re on and estimating the distance from the house using the received signal strength. The receivers collect multiples pieces of information about each beacon, including a unique identity number, a timestamp of when the beacon arrived, and the received signal strength at that timestamp.

By coordinating the beacon’s timestamp and signal strength between both receivers, we can calculate an estimated direction and distance from the house.

Using an array of some type, we can also keep a history of the location tracking and create an estimated path the cat walked during the tracking period.

**Data structures:**

Beacon_structure:
- macName (MAC address as string) Per tracker ID is the MAC address of the tracker
- timestamp (integer in nanoseconds)
- rxid (string) Receiver ID
- rssi (integer in dBm) Received Signal Strength

Beacon_array:
- An array of Beacon_structures
- needs to be sorted by timestamp

Position_structure:
- position (integer) Position relative to middle of house
- distance (integer) Estimated distance relative to the position point

Public member functions:
- void AddBeacon(Beacon_structure beacon_array, Beacon_structure received_beacon)
    - Adds the most recent beacon to the array or list
    - Needs to insert in time order, which may not happen sequentially, so a search process needs to happen to insert it in the correct order.
    - Asks CheckLength() if the new beacon can be added.
    - May need to call a “sort” function to make sure the beacon is added in order of the timestamp.
- void RemoveBeacon(Beacon_structure beacon_array, int maximum_length)
    - Removes the oldest beacons to keep the array from being infinitely long
    - Uses a maximum_length value to remove as many values as necessary.
- Position_structure[] GetPath(Beacon_structure beacon_array)
    - Generates a path for the requested tracker
    - The output is an array using integers representing the position relative to the middle of the house, and the estimated distance from that point. Positive position numbers indicate the front and negative position numbers indicate the back. The distance is always positive and is used to generate circle or half-circle when a UI is implemented.
- Position_structure GetCurrent(Beacon_structure beacon_array)
    - Return the last position and estimated distance of the tracker ID by calculating most recent front and back reports together.
    - The function needs to verify the received beacons occurred within 15 seconds of each other, which is the collection window.

**Private member functions:**
- bool CheckLength(Beacon_structure beacon_array)
    - Checks to make sure there room to add a new beacon report in the array
- void AddBeaconSort(Beacon_structure &beacon_array)
    - This may or may not be required, so I’m adding it in the proposal in case it is.
    - This will sort the beacon_array by timestamp.
    - Hopefully this won’t be needed and I can add the beacon as it’s added to the array, but there could be difficulties with that related to available space in the array.

**Testing procedure:**

I plan on gathering and saving data while the cats are outside and running it through the AddBeacon() function until I hit a certain number, then start running other functions like GetCurrent() to make sure it finds the “current” position at that time. As long as it works, I can then start removing and adding beacons and get a position each time. The ideal method of inputting the data is to have a CSV file with all the points that we can read in and run the AddBeacon() function for each point. The less elegant method is to generate a bunch of AddBeacon() calls in the Main() function to add them, but that would be really ugly and waste of CPU and compiler time. The problem in both cases is the output from the receivers is in JSON format. That format has to be converted to CSV to be useful.

At the end of the program, I plan on running GetPath() to see if it generates a path the cat(s) followed. This should generate an output of integer pairs using the Position_structure of all the points currently in the array.


**Alternatives:**

I chose to use a simply array for this project instead of something more complex such as a linked list because the structure is in order by time. We’re not likely to search for a particular point in time to find the position at that time. Therefore, instead of adding complexity and writing time to the program, we’ll use a simpler design that is ideal for creating a specific order of points.
