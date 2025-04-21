#include "../lib/ast.h"
#include "../lib/astparse.h"

#include <string>
#include <fstream>

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <source_file>" << std::endl;
        return 1;
    }

    std::string source_file_path = argv[1];

    // Parse the AST from standard input
    AST* ast = parseAST();

    // Print the AST
    ast->print();

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
    // Print the source code
    std::cout << "Source Code:" << std::endl;
    std::cout << source_code << std::endl;

    return 0;
}


