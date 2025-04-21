#ifndef CODE_H
#define CODE_H

#include <string>
#include <map>

#include "hierarchy.h"
#include "ast.h"
#include "astparse.h"

class Code {
    std::string source_code;
    std::map<std::string, HierNode*> hierarchy_map;
    AST* ast;

public:

    void setSourceCode(const std::string& code) {
        source_code = code;
    }

    void setAST () {
        if (source_code.empty()) {
            std::cerr << "Error: Source code is empty." << std::endl;
            return;
        }
        ast = parseAST();
    }

    void setHierarchyMap() {
        if (ast == nullptr) {
            std::cerr << "Error: AST is not set." << std::endl;
            return;
        }
        // Populate the hierarchy_map based on the AST
        for (auto node : ast->nodes) {
            HierNode* hierNode = new HierNode();
            hierNode->name = node->type;
            hierNode->start = node->start;
            hierNode->end = node->end;
            hierarchy_map[node->type] = hierNode;
        }
    }
};

#endif // CODE_H