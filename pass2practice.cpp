#include <bits/stdc++.h>
using namespace std;
class MNTEntry{
    public:
    int pp, kp, mdtp, kpdtp;

    MNTEntry(){}
    MNTEntry(int pp,int kp, int mdtp, int kpdtp){
        this->pp = pp;
        this->kp = kp;
        this->mdtp = mdtp;
        this->kpdtp = kpdtp;
    }
};
int main(){

    ifstream itr("intermediate.txt");
    ifstream mdtab("mdt.txt");
    ifstream mntab("mnt.txt");
    ifstream kpdtab("kpdt.txt");
    ofstream output("pass2.txt");

    string line;
    unordered_map<string, MNTEntry>mnt;
    unordered_map<int, string>aptab;
    unordered_map<string, int>aptabInverse;
    vector<string>mdt, kpdt;

    while(getline(mntab, line)){
        istringstream iss(line);
        string name;
        int pp, kp, mdtp, kpdtp;

        iss >> name >> pp >> kp >> mdtp >> kpdtp;

        

        mnt[name] = MNTEntry(pp, kp, mdtp, kpdtp);

    }
    
    while(getline(mdtab, line)){
        mdt.push_back(line);
    }

    while(getline(kpdtab, line)){
        kpdt.push_back(line);
    }


    while(getline(itr, line)){
        istringstream iss(line);
        string part;
        iss >> part;

        if(mnt.find(part) != mnt.end()){
            string name = part;
            int pp, kp, mdtp, kpdtp;
            int paramno = 1;
            
            pp = mnt[name].pp;
            kp = mnt[name].kp;
            mdtp = mnt[name].mdtp;
            kpdtp = mnt[name].kpdtp;

            cout<<pp<<" "<<kp<<" "<<mdtp<<" "<<kpdtp<<"\n";

            for(int i = 0; i < pp; i++){
                iss >> part;
                part.erase( remove(part.begin(), part.end(), ','), part.end());
                aptab[paramno++] = part;
            }

            int j = kpdtp - 1;
             for(int i = 0; i < kp; i++){
                
           
                 istringstream iss(kpdt[j++]);

                string key, value;
                iss >> key >> value;
            cout<<key<<" "<<value<<"\n";

                aptab[paramno] = value;
                aptabInverse[key] = paramno;
                paramno++;
            }

            //overide
            while(iss >> part){
                part.erase( remove(part.begin(), part.end(), '&'), part.end());
                part.erase( remove(part.begin(), part.end(), ','), part.end());

                size_t eq = part.find("=");
                string key = part.substr(0, eq);
                string value = part.substr(eq + 1);

                if(value != ""){
                    aptab[aptabInverse[key]] = value;
                }

            }

            //macroexpansionremaining

            int i = mdtp - 1;
            while(mdt[i] != "MEND"){
                istringstream iss(mdt[i]);
                string part ;
                while( iss >> part ){
                    if(part.find("(P,") != string::npos){
                        part.erase( remove(part.begin(), part.end(), '('), part.end());
                        part.erase( remove(part.begin(), part.end(), 'P'), part.end());
                        part.erase( remove(part.begin(), part.end(), ','), part.end());
                        part.erase( remove(part.begin(), part.end(), ')'), part.end());

                        int num = stoi(part);
                        
                        output << aptab[num] << "\t";

                    }else{
                        output << part << "\t";
                    }
                }
                cout << line<<"\n";
                output << "\n";
                i++;
            }
               


            while(getline(mdtab, line)){
                istringstream iss(line);
            }


        }else{
            cout << line<<"\n";
            output<<line<< "\n";
        }
    }

    itr.close();
     mdtab.close();
     mntab.close();
     kpdtab.close();
     output.close();


    return 0;
}