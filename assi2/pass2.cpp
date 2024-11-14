#include <bits/stdc++.h>
using namespace std;

// Function to search and return address from the table based on the provided number (symbol or literal table)
string table(ifstream &fin, string n)
{
    string no, name, addr;
    
    // Loop to search for the matching number (symbol or literal) in the table
    while(fin >> no >> name >> addr)
    {
        // If a match is found, reset file pointer to the beginning and return the address
        if(no == n)
        {
            fin.seekg(0, ios::beg);
            return addr;
        }
    }
    // Reset file pointer if no match is found and return "NAN" (Not Available)
    fin.seekg(0, ios::beg);
    return "NAN";
}

int main()
{
    // File streams for intermediate code, symbol table, and literal table
    ifstream ic, st, lt;
    
    // Open the files
    ic.open("ic.txt"); 
    st.open("symtable.txt"); 
    lt.open("littable.txt");

    // File stream for the output machine code
    ofstream mc;
    mc.open("machine_code.txt");

    // Variables to store intermediate code parts
    string lc, ic1, ic2, ic3;

    // Print header for the output
    cout << "\n -- ASSEMBLER PASS-2 OUTPUT --" << endl;
    cout << "\n LC\t <INTERMEDIATE CODE>\t\t\tLC\t <MACHINE CODE>" << endl;

    // Read intermediate code line by line until end of file
    while(ic >> lc >> ic1 >> ic2 >> ic3) 
    {
        string MC; // Variable to store machine code for each line

        // Handle Assembly Directives (AD) and Declarative Statements (DL) without machine code
        if(ic1.substr(1, 2) == "AD" || (ic1.substr(1, 2) == "DL" && ic1.substr(4, 2) == "02"))
            MC = " -No Machine Code-";

        // Handle Declarative Statement (DL) for storage allocation (e.g., DC - Define Constant)
        else if(ic1.substr(1, 2) == "DL" && ic1.substr(4, 2) == "01")
        {
            // Generate machine code with the constant's value
            MC = "00\t0\t00" + ic2.substr(3, 1);
        }
        else 
        {
            // Handle Instruction Statement (IS) with a zero opcode
            if(ic1 == "(IS,00)")
                MC = ic1.substr(4, 2) + "\t0\t000";
            
            // Check if second operand is a symbol and get its address from symbol table
            else if(ic2.substr(1, 1) == "S") 
                MC = ic1.substr(4, 2) + "\t0\t" + table(st, ic2.substr(4, 1));
            else
            {
                // If third operand is a symbol, get address from symbol table
                if(ic3.substr(1, 1) == "S") 
                    MC = ic1.substr(4, 2) + "\t" + ic2.substr(1, 1) + "\t" + table(st, ic3.substr(4, 1));
                else 
                    // If third operand is a literal, get address from literal table
                    MC = ic1.substr(4, 2) + "\t" + ic2.substr(1, 1) + "\t" + table(lt, ic3.substr(4, 1));
            }
        }

        // Handle Assembly Directive (AD) for END
        // if(ic1 == "(AD,03)") 
        // {
        //     cout << " " << lc << "\t" << ic1 << "\t" << ic2 << " " << ic3 << "\t\t\t" << lc << "\t" << MC << endl;
        //     mc << lc << "\t" << MC << endl;
        //     continue;
        // }
        
        // Print both the intermediate code and the generated machine code
        cout << " " << lc << "\t" << ic1 << "\t" << ic2 << "\t " << ic3 << "\t\t\t" << lc << "\t" << MC << endl;
        mc << lc << "\t" << MC << endl;
    }

    return 0;
}
