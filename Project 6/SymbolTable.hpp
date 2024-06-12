#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include <string>
#include <map>

class SymbolTable {
public:
    SymbolTable();
    void addSymbol(const std::string &symbolName, int symbolAddress);
    void addLabel(const std::string &label);
    void addVariable(const std::string &variable);
    int getAddress(const std::string &symbolName) const;
    
private:
    std::map<std::string, int> symbolTable;
    int variableCounter;
    int labelCounter;
    void initializePredefinedSymbols();
};

#endif