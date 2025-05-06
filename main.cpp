//Samuel Oseguera
//May 6, 2025
//CPSC-25-10103

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

// Hash function from ZyBooks
int HashString(const string& value) {
   int hashCode = 0;
   for (int character : value) {
      hashCode += character;
   }
   return (int)(hashCode & 0x7fffffff); // Ensure positive value
}

int main() {
    unordered_map<int, vector<string>> passwordTable; // Handles collisions using a vector
    ifstream passwordFile("rockyou.txt"); 

    if (!passwordFile) {
        cerr << "Error: Password file not found!" << endl;
        return 1;
    }

    string password;
    int count = 0; // Used to print first 10 passwords
    int collisionCount = 0; // Tracks collision numbers

    cout << "Reading passwords and hashing...\n";
    while (getline(passwordFile, password)) {
        int hashValue = HashString(password);

        // Count collision if hash already exists
        if (passwordTable.find(hashValue) != passwordTable.end()) {
            collisionCount++;
        }

        passwordTable[hashValue].push_back(password); // Store in vector to handle collisions

        // Prints the first 10 passwords
        if (count < 10) {
            cout << "Password: " << password << " | Hash: " << hashValue << endl;
        }

        count++;
    }
    passwordFile.close();

    cout << "\nHashing complete. Total collisions: " << collisionCount << endl;

    cout << "Enter a hashed password to find the original: ";
    
    int userHash;
    while (true) {
        cout << "\nEnter hashed value (or -1 to exit): ";
        cin >> userHash;

        if (userHash == -1) break;

        // Look up hash and print all matching passwords
        if (passwordTable.find(userHash) != passwordTable.end()) {
            cout << "Possible original passwords:\n";
            for (const string& pass : passwordTable[userHash]) {
                cout << " - " << pass << endl;
            }
        } else {
            cout << "Password not found in database." << endl;
        }
    }

    cout << "Goodbye!" << endl;
    return 0;
}