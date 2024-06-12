#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <bitset>
#include "SymbolTable.hpp" // Include SymbolTable header

class Parser {
public:
    // Constructor
    Parser(std::istream &sourceInput, SymbolTable &symbolRegistry);
    
    // Parse a line of assembly code
    void parse(const std::string &currentLine);
    
    // Check instruction types
    bool isLabel(const std::string &instruction) const;
    bool isAInstruction(const std::string &instruction) const;
    bool isCInstruction(const std::string &instruction) const;
    
    // Translate instructions
    std::string translateAInstruction(const std::string &instruction) const;
    std::string translateCInstruction(const std::string &instruction) const;
    
    // Get address of a label
    int getAddress(const std::string &label) const;

private:
    std::istream &sourceInput;
    std::vector<std::string> tokenList;
    SymbolTable &symbolRegistry; // Add reference to SymbolTable

    // Helper functions to translate parts of C-instruction
    std::string compTable(const std::string &comp) const;
    std::string destTable(const std::string &dest) const;
    std::string jumpTable(const std::string &jump) const;
};

#endif