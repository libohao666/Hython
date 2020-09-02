#include <runtimeenv.h>
#include <handler.h>
#include <master.h>
#include <AST.h>

namespace haizei {

RunTimeEnv::RunTimeEnv(ASTNode *tree) : tree(tree) {}
void RunTimeEnv::run() {
    FactoryHandler::init_factory(tree);
    return ;
}

} // end of namespace haizei

