#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include "ast.h"

enum HierType {
    TRAIT,
    STRUCT,
};

struct HierNode {
    std::string name;
    HierType type;
    int start;
    int end;
    std::vector<HierNode*> parent;
    std::vector<HierNode*> children;

    HierNode(std::string name, std::string type, int start, int end) : name(name), type(type == "trait" ? TRAIT : STRUCT), start(start), end(end) {}

    void addChild(HierNode* child) {
        if (child == nullptr) {
            return;
        }
        if (find(children.begin(), children.end(), child) != children.end()) {
            return; // Child already exists
        }
        children.push_back(child);
    }

    void addParent(HierNode* parent) {
        if (parent == nullptr) {
            return;
        }
        if (find(parent->children.begin(), parent->children.end(), this) != parent->children.end()) {
            return; // Parent already exists
        }
        this->parent.push_back(parent);
        parent->addChild(this);
    }
};

struct Hierarchy {
    std::vector<HierNode*> nodes;

    Hierarchy() {}

    ~Hierarchy() {
        for (auto node : nodes) {
            delete node;
        }
    }

    HierNode* findNode(const std::string& name) {
        for (auto node : nodes) {
            if (node->name == name) {
                return node;
            }
        }
        return nullptr;
    }

    void addNode(const std::string& name, const std::string& type, int start, int end) {
        HierNode* node = new HierNode(name, type, start, end);
        nodes.push_back(node);
    }

    void print(std::string &code) {
        for (auto node : nodes) {
            std::cout << "Node: " << node->name << ", Type: " << (node->type == TRAIT ? "Trait" : "Struct") << ", Start: " << node->start << ", End: " << node->end << "\n";
            std::cout << code.substr(node->start, node->end - node->start) << "\n";
            std::cout << "  Parents: ";
            for (auto parent : node->parent) {
                std::cout << parent->name << " ";
            }
            std::cout << "\n  Children: ";
            for (auto child : node->children) {
                std::cout << child->name << " ";
            }
            std::cout << "\n";
        }
    }

    void walkAst(ASTNode* node, std::string &code) {
        if (node->type == "struct_item") {
            int start = node->start;
            int end = node->end;
            std::string name;
            for (auto child : node->children) {
                if (child->type == "type_identifier") {
                    HierNode* newNode = new HierNode(code.substr(child->start, child->end - child->start), "struct", start, end);
                    nodes.push_back(newNode);
                    break;
                }
            }
        } else if (node->type == "trait_item") {
            int start = node->start;
            int end = node->end;
            std::string name;
            for (auto child : node->children) {
                if (child->type == "type_identifier") {
                    HierNode* newNode = new HierNode(code.substr(child->start, child->end - child->start), "trait", start, end);
                    nodes.push_back(newNode);
                    break;
                }
            }
        } else {
            for (auto child : node->children) {
                walkAst(child, code);
            }
        }
    }

    void addClasses(AST* ast, std::string &code) {
        walkAst(ast->root, code);
        print(code);
    }
};

#endif // HIERARCHY_H