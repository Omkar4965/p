#include<bits/stdc++.h>
using namespace std;

int main(){

    ifstream ip("input.txt");
    ofstream mnt("mnt.txt");
    ofstream mdt("mdt.txt");
    ofstream kpdt("kpdt.txt");
    ofstream ptab("pntab.txt");
    ofstream intermediate("intermediate.txt");

    string line;
    bool flag = 0;
    int kp = 0, pp = 0, paramno = 1;
    int mdtp = 1, kpdtp = 0;
    unordered_map<string, int>pntab;

    string part, mname;

    while(getline(ip, line)){
        istringstream iss(line);

        iss >> part;

        if(part == "MACRO"){
            flag = 1;
            // go to next line and add mname , kp, pp, kpdtp, mdtp
            getline(ip, line);
            istringstream iss(line);

            vector<string>parts;
            while(iss >> part){
                parts.push_back(part);
            }

            mname = parts[0];

            for(int i=1; i<parts.size(); i++){
                string token = parts[i];
                token.erase( remove(token.begin(), token.end(), '&') , token.end());
                token.erase( remove(token.begin(), token.end(), ',') , token.end());
                if(token.find("=") != string::npos){
                    kp++;
                    size_t eq = token.find('=');

                    string key = token.substr(0, eq);
                    string value = token.substr(eq+1);
                    
                    kpdt << key << "\t" << (value == "" ? "-" : value) <<"\n";
                    pntab[key] = paramno++;
                }else{
                    pp++;
                    pntab[token] = paramno++;
                }
            }

            mnt << mname << "\t" << pp << "\t" << kp << "\t" << mdtp << "\t" << ( kp == 0 ? kpdtp : (kpdtp + 1 ) ) << "\n";
            kpdtp += kp;

        }else if(part == "MEND"){
            mdt << line << "\n";
            mdtp++;
            kp = 0, pp = 0, paramno = 1;
            flag = 0;

            ptab << mname <<":\t";
            for(const auto &p : pntab){
                ptab << p.first<<"\t";
            }

            ptab << "\n";

            pntab.clear();
            mname = "";
        }else if(flag == 1){
            istringstream iss(line);
            string part;

            while(iss >> part){
                if(part.find('&') != string::npos){
                    part.erase(remove(part.begin(), part.end(), ','), part.end());
                    part = part.substr(1);
                    mdt << "(P, " << pntab[part] << ")" << "\t";
                }else{
                    mdt << part << "\t";
                }
            }

            mdtp++;
            mdt << "\n";
        }else{
            intermediate << line << "\n";
        }
    }

     ip.close();
     mnt.close();
     mdt.close();
     kpdt.close();
     ptab.close();
     intermediate.close();

    return 0;
}