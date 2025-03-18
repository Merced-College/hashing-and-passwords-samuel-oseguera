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
    ifstream passwordFile("/10-million-password-list-top-10000.txt"); // Replace with the actual password file

    if (!passwordFile) {
        cerr << "Error: Password file not found!" << endl;
        return 1;
    }

    string password;
    cout << "Reading passwords and hashing...\n";
    while (getline(passwordFile, password)) {
        int hashValue = HashString(password);
        passwordTable[hashValue].push_back(password); // Store in vector to handle collisions
    }
    passwordFile.close();

    cout << "Hashing complete. Enter a hashed password to find the original: ";
    
    int userHash;
    while (true) {
        cout << "\nEnter hashed value (or -1 to exit): ";
        cin >> userHash;

        if (userHash == -1) break;

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
