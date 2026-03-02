#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits> // Required for user input validation

using namespace std;

// Class implementation with public and private sections to track grocery items
class GroceryTracker {
private:
    // Map to store the item name as the key and frequency as the value
    map<string, int> itemFrequencies;

public:
    // Reads the input file and populates the item frequency map
    void processInputFile(string fileName) {
        ifstream inFS;
        string itemName;

        inFS.open(fileName);

        // Error handling if the file cannot be opened
        if (!inFS.is_open()) {
            cout << "Error: Could not open " << fileName << endl;
            return;
        }

        // Read file word by word and increment the frequency map
        while (inFS >> itemName) {
            itemFrequencies[itemName]++;
        }

        inFS.close();
    }

    // Creates the backup data file without user intervention
    void createBackupFile(string backupFileName) {
        ofstream outFS;
        outFS.open(backupFileName);

        // Error handling if the backup file cannot be created
        if (!outFS.is_open()) {
            cout << "Error: Could not create backup file " << backupFileName << endl;
            return;
        }

        // Iterate through the map and write each item and frequency to the file
        for (auto const& pair : itemFrequencies) {
            outFS << pair.first << " " << pair.second << endl;
        }

        outFS.close();
    }

    // Menu Option 1: Returns the frequency of a specific item
    int getItemFrequency(string item) {
        // Use map::count to avoid inserting the item with a 0 value if it doesn't exist
        if (itemFrequencies.count(item) > 0) {
            return itemFrequencies[item];
        }
        return 0; // Return 0 if the item was not found
    }

    // Menu Option 2: Prints all items and their numerical frequencies
    void printAllFrequencies() {
        cout << "\n--- Overall Item Frequencies ---" << endl;
        for (auto const& pair : itemFrequencies) {
            cout << pair.first << " " << pair.second << endl;
        }
        cout << "--------------------------------" << endl;
    }

    // Menu Option 3: Prints all items and a histogram representation of their frequencies
    void printHistogram() {
        cout << "\n--- Item Frequency Histogram ---" << endl;
        for (auto const& pair : itemFrequencies) {
            cout << pair.first << " ";
            // Print an asterisk for each count of the item
            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
        cout << "--------------------------------" << endl;
    }
};

// Function to display the user menu
void displayMenu() {
    cout << "\n========== CORNER GROCER MENU ==========" << endl;
    cout << "1. Look up specific item frequency" << endl;
    cout << "2. Print all item frequencies" << endl;
    cout << "3. Print histogram of item frequencies" << endl;
    cout << "4. Exit program" << endl;
    cout << "========================================" << endl;
    cout << "Enter your choice (1-4): ";
}

int main() {
    GroceryTracker tracker;

    // Read the input file provided in the scenario
    tracker.processInputFile("CS210_Project_Three_Input_File.txt");

    // Create the backup file at the beginning of the program automatically
    tracker.createBackupFile("frequency.dat");

    int userChoice = 0;
    string searchItem;

    // Menu loop with user input validation
    while (userChoice != 4) {
        displayMenu();

        // Check if the input is a valid integer to prevent infinite loops from bad input
        if (!(cin >> userChoice)) {
            cout << "Invalid input. Please enter a number between 1 and 4." << endl;
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard bad input
            continue;
        }

        switch (userChoice) {
        case 1:
            cout << "\nEnter the name of the item you wish to look for: ";
            cin >> searchItem;
            // Capitalize the first letter just in case the user types in lowercase, 
            // since the input file format uses capitalized first letters.
            if (!searchItem.empty()) {
                searchItem[0] = toupper(searchItem[0]);
            }
            cout << "\nFrequency of " << searchItem << ": "
                << tracker.getItemFrequency(searchItem) << endl;
            break;
        case 2:
            tracker.printAllFrequencies();
            break;
        case 3:
            tracker.printHistogram();
            break;
        case 4:
            cout << "\nExiting program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
            break;
        }
    }

    return 0;
}