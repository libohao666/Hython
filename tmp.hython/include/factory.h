#include <master.h>

namespace haizei {

class ASTNode;

class PrintFactory : public IMaster::IFactory {
    virtual IMaster *create(ASTNode*);
};

class ExprFactory : public IMaster::IFactory {
    virtual IMaster *create(ASTNode*);
};

class BlockFactory : public IMaster::IFactory {
    virtual IMaster *create(ASTNode*);
};

class CondFactory : public IMaster::IFactory {
    virtual IMaster *create(ASTNode*);
};
class CtrlFactory : public IMaster::IFactory {
    virtual IMaster *create(ASTNode*);
};

}