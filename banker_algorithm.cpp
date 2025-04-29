

//zyaire Bush
//Banker project
//4/28/25


#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

const int Processes = 5;
const int Resources = 3;

// Function to check if system is in safe state
bool isSafe(vector<vector<int>>& allocation, vector<vector<int>>& max,


                 vector<vector<int>>& need, vector<int>& available, 

                 vector<int>& safeSeq) {

    // Create copy of available resources
    vector<int> work = available;
    
    // Keep track of finished processes
    vector<bool> finish(Processes, false);
    
    // Count of processes that have finished
    int count = 0;
    
    // find rocess that can be allocated resources
    while (Processes > count) {
        
        bool found = false;
        
        for (int i = 0; i < Processes; i++) {
            
            if (!finish[i]) {
                bool Allocatable = true;

                for (int j = 0; j < Resources; j++) {
                    if (need[i][j] > work[j]) {

                    Allocatable = false;

                    break;
                    }
                }
                
                // If all resources can be allocated
                if (Allocatable) {
                    for (int j = 0; j < Resources; j++) {

                          work[j] += allocation[i][j];
                    }
                    
                    // safe
                    safeSeq[count] = i;
                    
                    // finish
                    finish[i] = true;
                    
                    
                    count++;
                    
                    
                    found = true;
                }
            }
        }
        
        // If none can be allocated resources
        if (!found) {

            return false;

        }
    }
    
    // If all can be allocated resources
    return true;
}

int main() {
    ifstream inputFile("banker_input.txt");
    
    if (!inputFile.is_open()) {

        cerr << "Error cant open files" << endl;
        
        return 1;
    }
    
    // Create the data structures
    vector<vector<int>> allocation(Processes, vector<int>(Resources));
    vector<vector<int>> max(Processes, vector<int>(Resources));
    vector<int> available(Resources);
    
    // Read available resources
    for (int i = 0; i < Resources; i++) {
        inputFile >> available[i];
    }
    
    // Read allocation 
    for (int i = 0; i < Processes; i++) {
        for (int j = 0; j < Resources; j++) {
            inputFile >> allocation[i][j];
        }
    }
    
    // Read max 
    for (int i = 0; i < Processes; i++) {
        for (int j = 0; j < Resources; j++) {
            inputFile >> max[i][j];
        }
    }
    
   
    inputFile.close();
    
    // Calculate
    vector<vector<int>> need(Processes, vector<int>(Resources));
    for (int i = 0; i < Processes; i++) {
        for (int j = 0; j < Resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    
    // Print to verify
    cout << "Allocation" << endl;
    for (int i = 0; i < Processes; i++) {
        cout << "P" << i << ": ";
        for (int j = 0; j < Resources; j++) {
            cout << allocation[i][j] << " ";
        }
        cout << endl;
    }
    
    cout << "Max" << endl;
    for (int i = 0; i < Processes; i++) {
        cout << "P" << i << ": ";
        for (int j = 0; j < Resources; j++) {
            cout << max[i][j] << " ";
        }
        cout << endl;
    }
    
    cout << "Need" << endl;
    for (int i = 0; i < Processes; i++) {
        cout << "P" << i << ": ";
        for (int j = 0; j < Resources; j++) {
            cout << need[i][j] << " ";
        }
        cout << endl;
    }
    
    cout << "Available:" << endl;
    for (int i = 0; i < Resources; i++) {
        cout << available[i] << " ";
    }
    cout << endl;
    
    // Check if safe state
    vector<int> safeSeq(Processes);
    
    if (isSafe(allocation, max, need, available, safeSeq)) {
        cout << "\nSys is in a safe state.Safe sequence is: ";
        for (int i = 0; i < Processes; i++) {
            cout << "P" << safeSeq[i];
            if (i != Processes - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    } else {
        cout << "\nSys is not in a safe state." << endl;
    }
    
    return 0;
}