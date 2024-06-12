#include "Parser.hpp"
#include <sstream>

Parser::Parser(std::istream &sourceInput, SymbolTable &symbolRegistry) : sourceInput(sourceInput), symbolRegistry(symbolRegistry) {}

// Parse a line of assembly code into tokens
void Parser::parse(const std::string &currentLine) {
    std::istringstream lineStream(currentLine);
    std::string parsedToken;
    while (lineStream >> parsedToken) {
        tokenList.push_back(parsedToken);
    }
}

// Check if the instruction is a label
bool Parser::isLabel(const std::string &instruction) const {
    return instruction.front() == '(' && instruction.back() == ')';
}

// Check if the instruction is an A-instruction
bool Parser::isAInstruction(const std::string &instruction) const {
    return instruction.front() == '@';
}

// Check if the instruction is a C-instruction
bool Parser::isCInstruction(const std::string &instruction) const {
    return !isAInstruction(instruction) && !isLabel(instruction);
}

// Translate an A-instruction to its binary representation
std::string Parser::translateAInstruction(const std::string &instruction) const {
    int value = 0;
    if (isdigit(instruction[1])) {
        value = std::stoi(instruction.substr(1));
    } else {
        value = symbolRegistry.getAddress(instruction.substr(1));
    }
    return std::bitset<16>(value).to_string();
}

// Translate a C-instruction to its binary representation
std::string Parser::translateCInstruction(const std::string &instruction) const {
    std::string dest, comp, jump;
    // Parse the C-instruction
    size_t equalSign = instruction.find('=');
    size_t semicolon = instruction.find(';');
    if (equalSign != std::string::npos) {
        dest = instruction.substr(0, equalSign);
        comp = instruction.substr(equalSign + 1, semicolon - equalSign - 1);
    } else {
        comp = instruction.substr(0, semicolon);
    }
    if (semicolon != std::string::npos) {
        jump = instruction.substr(semicolon + 1);
    }
    return "111" + compTable(comp) + destTable(dest) + jumpTable(jump);
}

// Get the address associated with a label
int Parser::getAddress(const std::string &label) const {
    return symbolRegistry.getAddress(label);
}

// These tables would be defined elsewhere in the Parser class
std::string Parser::compTable(const std::string &comp) const {
    // Translate comp mnemonics to binary
    // Example implementation
    static const std::map<std::string, std::string> compMap = {
        {"0", "0101010"}, {"1", "0111111"}, {"-1", "0111010"},
        // Add all other comp mnemonics
    };
    return compMap.at(comp);
}

std::string Parser::destTable(const std::string &dest) const {
    // Translate dest mnemonics to binary
    // Example implementation
    static const std::map<std::string, std::string> destMap = {
        {"", "000"}, {"M", "001"}, {"D", "010"}, {"MD", "011"},
        // Add all other dest mnemonics
    };
    return destMap.at(dest);
}

std::string Parser::jumpTable(const std::string &jump) const {
    // Translate jump mnemonics to binary
    // Example implementation
    static const std::map<std::string, std::string> jumpMap = {
        {"", "000"}, {"JGT", "001"}, {"JEQ", "010"}, {"JGE", "011"},
        // Add all other jump mnemonics
    };
    return jumpMap.at(jump);
}
