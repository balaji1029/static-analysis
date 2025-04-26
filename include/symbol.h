#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>
#include <vector>
#include <algorithm>

struct Symbol {
    std::string name;
    std::string type;
    std::pair<int, int> scope;
    SymbolTable* table;

    Symbol(std::string name, std::string type, std::pair<int, int> scope, SymbolTable* table)
        : name(name), type(type), scope(scope), table(table) {}
};

struct Function : public Symbol {
    std::vector<std::string> parameters;
    std::string returnType;

    Function(std::string name, std::string type, std::pair<int, int> scope, SymbolTable* table)
        : Symbol(name, type, scope, table) {}

    void addParameter(std::string param) {
        parameters.push_back(param);
    }

    void setReturnType(std::string retType) {
        returnType = retType;
    }
};

struct Class : public Symbol {
    std::vector<std::string> members;
    std::vector<std::string> methods;

    Class(std::string name, std::string type, std::pair<int, int> scope, SymbolTable* table)
        : Symbol(name, type, scope, table) {}

    void addMember(std::string member) {
        members.push_back(member);
    }

    void addMethod(std::string method) {
        methods.push_back(method);
    }
};

struct SymbolTable {
    std::vector<Symbol> symbols;
    std::vector<SymbolTable*> children;
    SymbolTable* parent;
    std::pair<int, int> scope;

    SymbolTable(SymbolTable* parent = nullptr, int start = 0, int end = 0)
        : parent(parent), scope(start, end) {}

    Symbol* findSymbol(std::string name) {
        for (auto& symbol : symbols) {
            if (symbol.name == name) {
                return &symbol;
            }
        }
        SymbolTable* table = this->parent;
        while (table != nullptr) {
            for (auto& symbol : table->symbols) {
                if (symbol.name == name) {
                    return &symbol;
                }
            }
            table = table->parent;
        }
        return nullptr;
    }

    void addSymbol(std::string name, std::string type, std::pair<int, int> scope) {
        Symbol symbol(name, type, scope, this);
        symbols.push_back(symbol);
    }

    void addChild(SymbolTable* child) {
        if (child == nullptr) {
            return;
        }
        if (find(children.begin(), children.end(), child) != children.end()) {
            return; // Child already exists
        }
        children.push_back(child);
        child->parent = this;
    }
};

struct SymbolTree {
    SymbolTable* root;
    std::vector<SymbolTable*> tables;

    SymbolTree() {
        root = new SymbolTable();
        root->scope = {0, 0};
        root->parent = nullptr;
    }

    ~SymbolTree() {
        for (auto table : tables) {
            delete table;
        }
        delete root;
    }
};

#endif // SYMBOL_H