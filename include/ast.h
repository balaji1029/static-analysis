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
        // std::cout << level << " " << type << " " << start << " " << end << std::endl;
        // std::cout << type << std::endl;
        // std::string in;
        // if (type == ";") {
        //     in = "semicolon";
        // } else if (type == "{") {
        //     in = "open";
        // } else if (type == "}") {
        //     in = "close";
        // } else if (type == "(") {
        //     in = "open";
        // } else if (type == ")") {
        //     in = "close";
        // } else if (type == "[") {
        //     in = "open";
        // } else if (type == "]") {
        //     in = "close";
        // } else if (type == ",") {
        //     in = "comma";
        // } else if (type == ":") {
        //     in = "colon";
        // } else if (type == "&") {
        //     in = "ref";
        // } else if (type == "-") {
        //     in = "minus";
        // } else if (type == "!") {
        //     in = "excl";
        // } else {
        //     in = type;
        // } 
        // for (auto child : children) {
        //     std::string out;
        //     if (child->type == ";") {
        //         out = "semicolon";
        //     } else if (child->type == "{") {
        //         out = "open";
        //     } else if (child->type == "}") {
        //         out = "close";
        //     } else if (child->type == "(") {
        //         out = "open";
        //     } else if (child->type == ")") {
        //         out = "close";
        //     } else if (child->type == "[") {
        //         out = "open";
        //     } else if (child->type == "]") {
        //         out = "close";
        //     } else if (child->type == ",") {
        //         out = "comma";
        //     } else if (child->type == ":") {
        //         out = "colon";
        //     } else if (child->type == "&") {
        //         out = "ref";
        //     } else if (child->type == "-") {
        //         out = "minus";
        //     } else if (child->type == "!") {
        //         out = "excl";
        //     }else {
        //         out = child->type;
        //     }
        //     std::cout << "  " << in << " -> " << out << ";" << std::endl;
        //     child->print(level + 1);
        // }
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
        // std::cout << "digraph G {" << std::endl;
        if (root) {
            // std::cout << "AST:" << std::endl;
            root->print(0);
        }
        // std::cout << "}" << std::endl;
        // std::cout << "END" << std::endl;
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