#include <bits/stdc++.h>
using namespace std;

class MNTEntry {
public:
    string name;
    int pp, kp, mdtp, kpdtp;

    
    MNTEntry() : name(""), pp(0), kp(0), mdtp(0), kpdtp(0) {}

    MNTEntry(string name, int pp, int kp, int mdtp, int kpdtp)
        : name(name), pp(pp), kp(kp), mdtp(mdtp), kpdtp(kpdtp) {}

    string getName() const { return name; }
    int getPp() const { return pp; }
    int getKp() const { return kp; }
    int getMdtp() const { return mdtp; }
    int getKpdtp() const { return kpdtp; }
};


int main() {
    ifstream irb("intermediate.txt");
    ifstream mdtb("mdt.txt");
    ifstream kpdtb("kpdt.txt");
    ifstream mntb("mnt.txt");
    ofstream fr("pass2.txt");

    unordered_map<string, MNTEntry> mnt;
    unordered_map<int, string> aptab;
    unordered_map<string, int> aptabInverse;

    vector<string> mdt;
    vector<string> kpdt;

    string line;

    while (getline(mdtb, line)) {
        mdt.push_back(line);
    }

    while (getline(kpdtb, line)) {
        kpdt.push_back(line);
    }

    while (getline(mntb, line)) {
        istringstream iss(line);
        string name;
        int pp, kp, mdtp, kpdtp;
        iss >> name >> pp >> kp >> mdtp >> kpdtp;
        mnt[name] = MNTEntry(name, pp, kp, mdtp, kpdtp);
    }

    while (getline(irb, line)) {
        cout<<line<<endl;
        istringstream iss(line);
        vector<string> parts;
        string part;
        while (iss >> part) {
            parts.push_back(part);
        }

        if (mnt.find(parts[0]) != mnt.end()) {
            int pp = mnt[parts[0]].getPp();
            int kp = mnt[parts[0]].getKp();
            int kpdtp = mnt[parts[0]].getKpdtp();
            int mdtp = mnt[parts[0]].getMdtp();
            int paramNo = 1;

            for (int i = 0; i < pp; i++) {
                parts[paramNo].erase(remove(parts[paramNo].begin(), parts[paramNo].end(), ','), parts[paramNo].end());
                aptab[paramNo] = parts[paramNo];
                aptabInverse[parts[paramNo]] = paramNo;
                paramNo++;
            }


            int j = kpdtp - 1;
            for (int i = 0; i < kp; i++) {
                istringstream kpdtLine(kpdt[j++]);
                string key, value;
                kpdtLine >> key >> value;
                aptab[paramNo] = value;
                aptabInverse[key] = paramNo;
                paramNo++;
            }

            for (int i = pp + 1; i < parts.size(); i++) {
                parts[i].erase(remove(parts[i].begin(), parts[i].end(), ','), parts[i].end());
                string name = parts[i].substr(0, parts[i].find('=')).substr(1);
                string value = parts[i].substr(parts[i].find('=') + 1);
                aptab[aptabInverse[name]] = value;
            }

            int i = mdtp - 1;
            while (mdt[i] != "MEND") {
                istringstream mdtLine(mdt[i++]);
                string token;
                fr << "+";
            while (mdtLine >> token) {
                // Check if the token contains "(P,"
                if (token.find("(P,") != string::npos) {
                    // Remove all non-digit characters from the token to isolate the parameter index
                    string indexString = "";
                    for (char ch : token) {
                        if (isdigit(ch)) {  // Check if character is a digit
                            indexString += ch;  // Append digit characters to indexString
                        }
                    }

                    // Convert the numeric string to an integer index
                    int index = stoi(indexString);

                    // Substitute the parameter value from aptab based on the index
                    fr << aptab[index] << "\t";
                } else {
                    // Write non-parameter tokens directly to the file
                    fr << token << "\t";
                }
            }

                fr << "\n";
            }

            aptab.clear();
            aptabInverse.clear();
        } else {
            fr << line << "\n"; 
        }

         cout << "Macro Pass2 Processing done. :)" << endl;
    }


    cout << "exit" << endl;
    fr.close();
    mntb.close();
    mdtb.close();
    kpdtb.close();
    irb.close();
  

    return 0;
}
