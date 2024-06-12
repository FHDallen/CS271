#include "SymbolTable.hpp"
#include <stdexcept> // Include the stdexcept header for runtime_error

SymbolTable::SymbolTable() {
    variableCounter = 16; // Assuming variables start at address 16
    labelCounter = 0;
    initializePredefinedSymbols();
}

// Initialize predefined symbols
void SymbolTable::initializePredefinedSymbols() {
    symbolTable["R0"] = 0;
    symbolTable["R1"] = 1;
    symbolTable["R2"] = 2;
    symbolTable["R3"] = 3;
    symbolTable["R4"] = 4;
    symbolTable["R5"] = 5;
    symbolTable["R6"] = 6;
    symbolTable["R7"] = 7;
    symbolTable["R8"] = 8;
    symbolTable["R9"] = 9;
    symbolTable["R10"] = 10;
    symbolTable["R11"] = 11;
    symbolTable["R12"] = 12;
    symbolTable["R13"] = 13;
    symbolTable["R14"] = 14;
    symbolTable["R15"] = 15;
    symbolTable["SCREEN"] = 16384;
    symbolTable["KBD"] = 24576;
}

// Add a symbol to the symbol table with its address
void SymbolTable::addSymbol(const std::string &symbolName, int symbolAddress) {
    symbolTable[symbolName] = symbolAddress;
}

// Add a label to the symbol table
void SymbolTable::addLabel(const std::string &label) {
    if (symbolTable.find(label) != symbolTable.end()) {
        throw std::runtime_error("Label redefined!");
    }
    symbolTable[label] = labelCounter++;
}

// Add a variable to the symbol table
void SymbolTable::addVariable(const std::string &variable) {
    if (symbolTable.find(variable) == symbolTable.end()) {
        symbolTable[variable] = variableCounter++;
    }
}

// Get the address associated with a symbol
int SymbolTable::getAddress(const std::string &symbolName) const {
    auto it = symbolTable.find(symbolName);
    if (it != symbolTable.end()) {
        return it->second;
    }
    return -1; // Symbol not found
}