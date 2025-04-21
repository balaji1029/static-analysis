#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <string>
#include <vector>

enum HierType {
    TRAIT,
    STRUCT,
};

struct HierNode {
    std::string name;
    HierType type;
    int start;
    int end;
    std::vector<HierNode*> parents;
    std::vector<HierNode*> children;

    
}

#endif // HIERARCHY_H