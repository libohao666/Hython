/*
* @Author: lbh
* @Date: 2020-08-27 13:39:39 
 * @Last Modified by: mikey.zhaopeng
 * @Last Modified time: 2020-08-27 14:05:14
*/
#include <head.h>
#include <ExprTreeEvaluator.h>
 
int main(int argc, char* argv[]) {
    assert(argc > 1);
    haizei::ASTNode tree(argv[1]);

    ExprTreeEvaluator eval;
    int rr = eval.run(tree);
    std::cout << "Evaluator result: " << rr << '\n';

    tree.destroy();
    return 0;
}



