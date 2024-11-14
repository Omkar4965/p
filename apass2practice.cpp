#include<bits/stdc++.h>
using namespace std;
int main(){

    ifstream ic("ic.txt");
    ifstream lt("littable.txt");
    ifstream st("symtable.txt");

    ofstream mcfile("machine_code.txt");

    unordered_map<int,string>symtab, littab;
    string line, lc, ic1, ic2, ic3, mc = "";
    int i = 1;
    while(getline(st, line)){
        symtab[i++] = line;
    }

    i = 1;
    while(getline(lt, line)){
        littab[i++] = line;
    }

    while(ic >> lc >> ic1 >> ic2 >> ic3){

        if(ic1.substr(1,2) == "AD" || ic1.substr(1,2) == "DL" && ic1.substr(4,2) == "02"){
            cout<<ic1<<" ";
            mc = "--- Machine code ---------";
        }else if(ic1.substr(1,2) == "DL"){
            mc = "00\t0\t00" + ic2.substr(3,1) ;
        }else{
            if(ic1 == "(IS,00)"){
                mc= "00\t0\t000";
            }else if(ic2.substr(1,1) == "S"){
                string addr ;
                istringstream symt(symtab[stoi(ic2.substr(3,2))]);
                while(symt >> addr);
                mc = ic1.substr(4,2) + "\t" + ic2.substr(1,1) + "\t" +  addr;
            }else{
                string addr ;
                if(ic3.substr(1,1) == "S"){
                    istringstream symt(symtab[stoi(ic3.substr(3,2))]);
                    while(symt >> addr);
                    mc = ic1.substr(4,2) + "\t" + ic2.substr(1,1) + "\t" +  addr;
                }else{
                    istringstream symt(littab[stoi(ic3.substr(3,2))]);
                    while(symt >> addr);
                    mc = ic1.substr(4,2) + "\t" + ic2.substr(1,1) + "\t" +  addr;
                }
            }
        }
        mcfile << lc << "\t" << mc <<"\n";
    }

    ic.close();
    lt.close();
    st.close();

    mcfile.close();

    return 0;
}