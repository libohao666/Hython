#include <factory.h>
#include <master.h>
#include <AST.h>

namespace haizei {

IMaster *PrintFactory::create(haizei::ASTNode tree) {
    return new PrintMaster(tree);
}

IMaster *ExprFactory::create(haizei::ASTNode tree) {
    return new ExprMaster(tree);
}

IMaster *BlockFactory::create(haizei::ASTNode tree) {
    return new BlockMaster(tree);
}

IMaster *CondFactory::create(haizei::ASTNode tree) {
    return new CondMaster(tree);
}

IMaster *CtrlFactory::create(haizei::ASTNode tree) {
    return new PrintMaster(tree);
}

}
