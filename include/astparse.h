#ifndef ASTPARSE_H
#define ASTPARSE_H


#include <string>
#include <vector>
#include <iostream>
#include <stack>

#include "ast.h"

// Function to parse a node
ASTNode* parseNode(const std::string& line) {
    // Example parsing logic (to be replaced with actual parsing)
    std::string type = line.substr(0, line.find(' '));
    int start = std::stoi(line.substr(line.find(' ') + 1));
    int end = std::stoi(line.substr(line.rfind(' ') + 1));

    ASTNode* node = new ASTNode(type, start, end);
    return node;
}

AST* parseAST() {

    // Read lines from standard input until "END" is encountered
    std::vector<std::string> lines;
    while (true) {
        std::string line;
        std::getline(std::cin, line);
        std::string trimmedLine = line;
        line = trimmedLine.erase(trimmedLine.find_last_not_of(" \n\r\t") + 1);
        // std::cout << line << "---" << line.size() << std::endl;
        if (line == "END") {
            break;
        } else if (line.empty()) {
            break;
        }
        lines.push_back(line);
        // std::cout << line << std::endl;
    }

    // Create a new AST
    AST* ast = new AST();
    int currentLevel = 0;
    ASTNode* currentNode = nullptr;

    std::stack<ASTNode*> nodeStack;

    for (const auto& line : lines) {
        std::string x = "";
        int ind = 0;
        int level;
        std::string type = "";
        int start = 0;
        int end = 0;
        for (char c : line) {
            if (c == ' ') {
                switch (ind) {
                    case 0:
                        level = std::stoi(x);
                        break;
                    case 1:
                        type = x;
                        break;
                    case 2:
                        start = std::stoi(x);
                        break;
                }
                x = "";
                ind++;
            }
            else {
                x += c;
            }
        }
        end = std::stoi(x);
        if (level == 0) {
            // Create a new root node
            ASTNode* node = new ASTNode(type, start, end);
            ast->addNode(node);
            nodeStack.push(node);
        } else {
            // Find the parent node and add the child
            while (nodeStack.size() > level) {
                nodeStack.pop();
            }
            if (nodeStack.size() == level) {
                // Create a new node and add it to the parent
                ASTNode* parent = nodeStack.top();
                ASTNode* child = new ASTNode(type, start, end);
                parent->addChild(child);
                ast->addNode(child);
                nodeStack.push(child);
            }
        }
        currentLevel = level;
        currentNode = nodeStack.top();
    }

    return ast;
}

#endif // ASTPARSE_H