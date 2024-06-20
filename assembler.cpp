#include <bits/stdc++.h>
using namespace std;

vector<string> lines;
unordered_map<string, short> symbol_table;
unordered_map<string, string> comp_table, dest_table, jump_table;
void init_tables() {
    symbol_table = {{"SCREEN", 16384},
                    {"KBD", 24576},
                    {"SP", 0},
                    {"LCL", 1},
                    {"ARG", 2},
                    {"THIS", 3},
                    {"THAT", 4}};
    for (short i = 0; i < 16; ++i) symbol_table["R" + to_string(i)] = i;

    comp_table = {{"0", "0101010"},
                  {"1", "0111111"},
                  {"-1", "0111010"},
                  {"D", "0001100"},
                  {"A", "0110000"},
                  {"M", "1110000"},
                  {"!D", "0001101"},
                  {"!A", "0110001"},
                  {"!M", "1110001"},
                  {"-D", "0001111"},
                  {"-A", "0110011"},
                  {"-M", "1110011"},
                  {"D+1", "0011111"},
                  {"A+1", "0110111"},
                  {"M+1", "1110111"},
                  {"D-1", "0001110"},
                  {"A-1", "0110010"},
                  {"M-1", "1110010"},
                  {"D+A", "0000010"},
                  {"D+M", "1000010"},
                  {"D-A", "0010011"},
                  {"D-M", "1010011"},
                  {"A-D", "0000111"},
                  {"M-D", "1000111"},
                  {"D&A", "0000000"},
                  {"D&M", "1000000"},
                  {"D|A", "0010101"},
                  {"D|M", "1010101"},};

    dest_table = {{"", "000"},
                  {"M", "001"},
                  {"D", "010"},
                  {"MD", "011"},
                  {"A", "100"},
                  {"AM", "101"},
                  {"AD", "110"},
                  {"AMD", "111"}};

    jump_table = {{"", "000"},
                  {"JGT", "001"},
                  {"JEQ", "010"},
                  {"JGE", "011"},
                  {"JLT", "100"},
                  {"JNE", "101"},
                  {"JLE", "110"},
                  {"JMP", "111"}};
}
int main(int argc, char *argv[]) {
    // preprocessing file name and folder
    string filepath = argv[1];
    int filename_start = filepath.rfind("/") + 1, filename_end = filepath.rfind(".");
    string filename = filepath.substr(filename_start, filename_end - filename_start),
           filefolder = filepath.substr(0, filename_start - 1);
    
    // opening input and output files
    ifstream input(argv[1]);
    ofstream output(filefolder + "/" + filename + ".hack");

    // initialize lookup tables
    init_tables();

    // preprocess the input file
    string s;
    while (getline(input, s)) {
        // removing whitespace and adjusting iterator
        s.erase(remove(s.begin(), s.end(), ' '), s.end());
        // ignoring comments
        if (s.find("//") != -1ULL) s = s.substr(0, s.find("//"));
        // skipping comments and empty lines
        if (s == "") continue;

        // if label, add it to symbol table and assign next instruction as its value
        if (s[0] == '(') symbol_table[s.substr(1, s.find(')') - 1)] = lines.size();
        // else add instruction to list
        else lines.push_back(s);
    }

    // keep track of variable symbols
    short idx = 15;
    // parse the instructions and write it into the output file
    for (auto line : lines) {
        // handling a-instructions
        if (line[0] == '@') {
            string temp = line.substr(1);
            bool isNum = true;
            short value = -1;
            for (char &c : temp) if (!isdigit(c)) isNum = false;

            // if value is decimal constant, convert to short
            if (isNum) value = stoi(line.substr(1));
            // else retrieve value of symbol from lookup table
            else {
                if (symbol_table.find(temp) == symbol_table.end()) symbol_table[temp] = ++idx;
                value = symbol_table[temp];
            }

            // convert value to binary and write it to the output file
            output << bitset<16>(value).to_string() << "\n";
        }
        
        // handling c-instructions
        else {
            int ide = line.find('='), idj = line.find(';'), lenj = 3;
            if (idj == -1) lenj = 0;
            
            // retrieves binary comp, dest, and jump values from their lookup tables
            string comp = comp_table[line.substr(ide + 1, idj - ide - 1)],
                   dest = dest_table[line.substr(0, max(ide, 0))],
                   jump = jump_table[line.substr(idj + 1, lenj)];

            // write the instruction in binary to output file
            output << "111" + comp + dest + jump << "\n";
        }
    }

    output.close();
    return 0;
}