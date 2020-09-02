#include <AST.h>
#include <memory>

namespace haizei {

class IMaster {
public:
    virtual int run(ASTNode &, std::shared_ptr<Parameter> &) = 0;
};

class ExprMaster : public IMaster {
public:
    virtual int run(ASTNode &, std::shared_ptr<Parameter> &);
};
class ControlBlockMaster : public IMaster {
public:
    virtual int run(ASTNode &, std::shared_ptr<Parameter> &);
};
class ControlNoBlockMaster : public IMaster {
public:
    virtual int run(ASTNode &, std::shared_ptr<Parameter> &);
};
class PrintMaster : public IMaster {
public:
    virtual int run(ASTNode &, std::shared_ptr<Parameter> &);
};

} // end of namespace haizei