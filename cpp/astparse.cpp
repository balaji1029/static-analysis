#include "../include/code.h"

#include <string>
#include <fstream>

// void print_check(ASTNode* node, std::string* source_code, int level) {
//     std::string line = source_code->substr(node->start, node->end - node->start);
//     if (level == 0) {
//         goto direct;
//     }
//     for (int i = 0; i < level; ++i) {
//         std::cout << "\t";
//     }
//     std::cout << level << " " << node->type << " " << node->start << " " << node->end << std::endl;
//     for (int i = 0; i < level; ++i) {
//         std::cout << "\t";
//     }
//     std::cout << line << std::endl;

//     direct:

//     for (auto child : node->children) {
//         print_check(child, source_code, level + 1);
//     }
// }

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <source_file>" << std::endl;
        return 1;
    }

    std::string source_file_path = argv[1];

    // Parse the AST from standard input
    // AST* ast = parseAST();

    // Print the AST
    // ast->print();

    std::string source_code;
    std::fstream source_file(source_file_path, std::ios::in);

    if (source_file.is_open()) {
        std::string line;
        while (std::getline(source_file, line)) {
            source_code += line + "\n";
        }
        source_file.close();
    } else {
        std::cerr << "Error opening file: " << source_file_path << std::endl;
        return 1;
    }

    Code code;
    code.setSourceCode(source_code);
    code.setAST();
    code.setHierarchyMap();
    // Print the source code
    // std::cout << "Source Code:" << std::endl;
    // std::cout << source_code << std::endl;

    // print_check(ast->root, &source_code, 0);


    return 0;
}


