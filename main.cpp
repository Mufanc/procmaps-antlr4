#include <iostream>
#include <fstream>

#include "antlr4-runtime.h"
#include "ProcMapsLexer.h"
#include "ProcMapsParser.h"

using namespace std::literals;
using namespace antlr4;

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " <pid>" << std::endl;
        return 1;
    }

    std::ifstream stream;
    stream.open("/proc/"s + argv[1] + "/maps");

    if (!stream.is_open()) {
        std::cerr << "error opening file!" << std::endl;
        return 1;
    }

    ANTLRInputStream input(stream);

    ProcMapsLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    ProcMapsParser parser(&tokens);

    while (tokens.LA(1) != Token::EOF) {
        ProcMapsParser::EntryContext *ctx = parser.entry();

        std::cout << "> Parsed: " << ctx->toStringTree(&parser) << std::endl;
        std::cout << "> Range:\t" << ctx->range()->getText() << std::endl;
        std::cout << "> Permissions:\t" << ctx->perms()->getText() << std::endl;
        std::cout << "> Offset:\t" << ctx->offset()->getText() << std::endl;
        std::cout << "> Device:\t" << ctx->dev()->getText() << std::endl;
        std::cout << "> Inode:\t" << ctx->inode()->getText() << std::endl;

        auto *pathname = ctx->pathname();
        if (pathname) {
            std::cout << "> Pathname:\t" << pathname->getText() << std::endl;
        }

        std::cout << std::endl;
    }

    stream.close();

    return 0;
}
