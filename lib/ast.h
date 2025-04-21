#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <iostream>

struct ASTNode {
    std::string type;
    int start;
    int end;
    std::vector<ASTNode*> children;
    ASTNode* parent;

    ASTNode(const std::string& type, int start, int end)
        : type(type), start(start), end(end) 
    {}

    void addChild(ASTNode* child) {
        children.push_back(child);
    }

    void print(int level) {
        std::cout << level << " " << type << " " << start << " " << end << std::endl;
        // std::cout << type << std::endl;

        for (auto child : children) {
            child->print(level + 1);
        }
    }

    ~ASTNode() {
        for (auto child : children) {
            delete child;
        }
    }

};

struct AST {
    ASTNode* root;
    std::vector<ASTNode*> nodes;

    AST() : root(nullptr) {}

    void addNode(ASTNode* node) {
        nodes.push_back(node);
        if (!root) {
            root = node;
        }
    }

    void print() {
        // std::cout << "AST Nodes:" << std::endl;
        if (root) {
            // std::cout << "AST:" << std::endl;
            root->print(0);
        }
        std::cout << "END" << std::endl;
    }

    void clear() {
        delete root;
        root = nullptr;
    }

    ~AST() {
        clear();
    }
};

#endif // AST_H