#include<iostream>
#include<fstream>
#include<vector>

std::vector< std::vector<int> > readDIMACSFormat(std::ifstream * inputFile) {
    int c = 0; // Character reading
    int rawLiteral = -1;
    std::vector< std::vector<int> > clauseSet;
    while ( (c = inputFile->peek()) != EOF ) {
        switch(c) {
            case 'c' :
                inputFile->get();
                // Skip
                while((c = inputFile->get()) != '\n');
                break;
            case 'p' :
                inputFile->get();
                // Skip
                while((c = inputFile->get()) != '\n');
                break;
            default :
                std::vector<int> clause;
                *inputFile >> rawLiteral;
                while (rawLiteral) {
                    clause.push_back(rawLiteral);
                    *inputFile >> rawLiteral;
                }
                clauseSet.push_back(clause);
                // Jump to newline
                c = inputFile->get();
                while((c != '\n') && (c != EOF)) {
                    c = inputFile->get();
                }
                break;
        }
    }
    return clauseSet;
}
