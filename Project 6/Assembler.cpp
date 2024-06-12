#include "Parser.hpp"
#include "SymbolTable.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

int main(int argumentCount, char *arguments[]) {
    // Check if the correct number of arguments is provided
    if (argumentCount != 2) {
        std::cerr << "Usage: MyAssembler sourcefile" << std::endl;
        return 1;
    }
    
    // Open the input file
    std::ifstream inputFile(arguments[1]);
    if (!inputFile) {
        std::cerr << "Error opening file: " << arguments[1] << std::endl;
        return 1;
    }

    SymbolTable symbolRegistry; // Create the SymbolTable object
    Parser sourceParser(inputFile, symbolRegistry); // Pass the symbolRegistry to the Parser constructor
    std::vector<std::string> instructionList;
    std::string currentLine;

    // Read each line from the input file and parse it
    while (std::getline(inputFile, currentLine)) {
        sourceParser.parse(currentLine);
        instructionList.push_back(currentLine);
    }

    // First pass: Add labels to the symbol table
    for (const auto &instruction : instructionList) {
        if (sourceParser.isLabel(instruction)) {
            std::string label = instruction.substr(1, instruction.length() - 2); // Remove parentheses
            symbolRegistry.addLabel(label);
        }
    }

    // Second pass: Translate instructions and output them
    for (const auto &instruction : instructionList) {
        if (sourceParser.isAInstruction(instruction)) {
            std::cout << sourceParser.translateAInstruction(instruction) << std::endl;
        } else if (sourceParser.isCInstruction(instruction)) {
            std::cout << sourceParser.translateCInstruction(instruction) << std::endl;
        }
    }

    return 0;
}
