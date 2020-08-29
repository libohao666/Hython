/*
* @Author: lbh
* @Date: 2020-08-27 13:39:39 
 * @Last Modified by: mikey.zhaopeng
 * @Last Modified time: 2020-08-27 14:05:14
*/
#include <head.h>
#include <hythonLexer.h>
#include <hythonParser.h>
#include <ExprTree.h>
using std::cout;
using std::endl;
 
int main(int argc, char* argv[]) {
    haizei::ASTNode tree(argc, argv[1]);
    ExprTreeEvaluator eval;
    int rr = eval.run(tree);
    cout << "Evaluator result: " << rr << '\n';
    tree.destroy();
    return 0;
}
