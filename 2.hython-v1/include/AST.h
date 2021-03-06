/*
* @Author: lbh
* @Date: 2020-09-02 09:13:49 
* @Last Modified by: lbh
* @Last Modified time: 2020-09-02 09:13:49 
*/
#include <hythonLexer.h>
#include <hythonParser.h>
#include <string>

namespace haizei {

class ASTNode {
public:
    ASTNode(const char *file_name);
    ASTNode(pANTLR3_BASE_TREE);
    int size();
    std::string text();
    ASTNode operator[](int);
    bool hasToken();
    int type();
    void destroy();
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