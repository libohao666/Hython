#include <hythonLexer.h>
#include <hythonParser.h>
#include <head.h>
#include <factory.h>

namespace haizei {

class ASTNode {
public:
    ASTNode(const char *file_name);
    ASTNode(ANTLR3_BASE_TREE);
    int size();
    std::string text();
    ASTNode operator[](int);
    bool hasToken();
    int type();
    void destroy();
    IMaster::IFactory *factory;
    ~ASTNode();

private:
    pANTLR3_BASE_TREE tree;
    pANTLR3_INPUT_STREAM input;
    phythonLexer lex;
    pANTLR3_COMMON_TOKEN_STREAM tokens;
    phythonParser parser;
    pANTLR3_COMMON_TOKEN tok;

    void init_tree(const char *file_name);
};

} // end of haizei