#include <bits/stdc++.h>

using namespace std;

int main() {
    // Define file streams for input and output files
    ifstream inputFile("input.txt");        // Input file containing macro definitions
    ofstream mntFile("mnt.txt");            // Macro Name Table (MNT)
    ofstream mdtFile("mdt.txt");            // Macro Definition Table (MDT)
    ofstream kpdtFile("kpdt.txt");          // Keyword Parameter Default Table (KPDTAB)
    ofstream pntFile("pntab.txt");          // Parameter Name Table (PNTAB)
    ofstream irFile("intermediate.txt");    // Intermediate file for non-macro lines

    // Parameter Name Table (PNTAB) to store parameter names and their positions
    unordered_map<string, int> pntab;
    
    string line, macroName;    // Variables to store each line and current macro name
    int mdtp = 1, kpdtp = 0, paramNo = 1, pp = 0, kp = 0, flag = 0; // Initialize pointers and counters

    // Check if the input file opened successfully
    if (!inputFile.is_open()) {
        cerr << "Error opening input file!" << endl;
        return 1;
    }
 
    // Loop through each line in the input file
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string part;
        iss >> part;

        // Check for the start of a macro definition
        if (part == "MACRO") {
            flag = 1;  // Flag indicates a macro definition has started

            // Read the next line to get the macro name and parameters
            getline(inputFile, line);
            istringstream macroLine(line);
            macroLine >> macroName;   // First item in line is the macro name
            pp = kp = 0;              // Reset positional and keyword parameter counters

            vector<string> parts;
            string temp;

            // Extract all parameters in the macro definition line
            while (macroLine >> temp) {
                parts.push_back(temp);
            }

            // If there are no parameters, write basic macro info to MNT and continue
            if (parts.size() <= 1) {
                mntFile << macroName << "\t" << pp << "\t" << kp << "\t" << mdtp << "\t" 
                        << (kp == 0 ? kpdtp : (kpdtp + 1)) << "\n";
                continue;
            }

            // Process each parameter
            for (int i = 0; i < parts.size(); i++) {
                string param = parts[i];

                // Remove '&' and ',' from parameter names
                param.erase(remove(param.begin(), param.end(), '&'), param.end());
                param.erase(remove(param.begin(), param.end(), ','), param.end());

                // Check if parameter has a default value (keyword parameter)
                if (param.find('=') != string::npos) {
                    ++kp; // Increment keyword parameter counter

                    size_t pos = param.find('=');
                    string keyword = param.substr(0, pos);  // Extract keyword name
                    string defaultValue = (pos + 1 < param.size()) ? param.substr(pos + 1) : "-"; // Extract default value

                    pntab[keyword] = paramNo++;  // Add keyword to PNTAB
                    kpdtFile << keyword << "\t" << defaultValue << "\n";  // Write keyword and default to KPDTAB
                } else {  
                    // Positional parameter
                    pntab[param] = paramNo++;
                    pp++;  // Increment positional parameter counter
                }
            }

            // Write macro information to MNT
            mntFile << macroName << "\t" << pp << "\t" << kp << "\t" << mdtp << "\t" 
                    << (kp == 0 ? kpdtp : (kpdtp + 1)) << "\n";
            kpdtp += kp;  // Update KPDTAB pointer after processing keyword parameters
        } 
        else if (part == "MEND") {
            // Write "MEND" line to MDT to mark end of the macro definition
            mdtFile << line << "\n";

            // Reset counters and flags for the next macro definition
            flag = kp = pp = 0;
            mdtp++;
            paramNo = 1;

            // Write PNTAB entries for the current macro to the PNTAB file
            pntFile << macroName << ":\t";
            for (const auto &p : pntab) {
                pntFile << p.first << "\t";
            }
            pntFile << "\n";
            pntab.clear();  // Clear PNTAB for next macro
        } 
        else if (flag == 1) {
            // Inside a macro definition, processing each line in the macro
            istringstream commandLine(line);
            string commandPart;

            // Process each part of the command line
            while (commandLine >> commandPart) {
                if (commandPart.find('&') != string::npos) {
                    // If part is a parameter, remove '&' and ','
                    commandPart.erase(remove(commandPart.begin(), commandPart.end(), '&'), commandPart.end());
                    commandPart.erase(remove(commandPart.begin(), commandPart.end(), ','), commandPart.end());

                    // Replace parameter with its position from PNTAB
                    mdtFile << "(P," << pntab[commandPart] << ")\t";
                } else {
                    // Write non-parameter parts directly to MDT
                    mdtFile << commandPart << "\t";
                }
            }
            mdtFile << "\n"; // New line for each command
            mdtp++;          // Increment MDT pointer
        } 
        else {
            // For lines outside macro definitions, write them to the intermediate file
            irFile << line << "\n";
        }
    }

    // Close all file streams
    inputFile.close();
    mntFile.close();
    mdtFile.close();
    kpdtFile.close();
    pntFile.close();
    irFile.close();

    // Output completion message
    cout << "Macro Pass1 Processing done. :)" << endl;
    return 0;
}
