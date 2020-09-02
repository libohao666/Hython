#include <AST.h>

namespace haizei {

class IHandle {
public:
    IHandle(IHandle *next);
    virtual bool Test(const ASTNode &) const = 0;
    IHandle *next();

private:
    IHandle *__next;
};

class ExprHandle : public IHandle {
public:
    ExprHandle(IHandle *);
    bool Test(const ASTNode &) const ;
};

class ControlNoBlockHandle : public IHandle {
public:
    ControlNoBlockHandle(IHandle *);
    bool Test(const ASTNode &) const ;
};

class ControlBlockHandle : public IHandle {
public:
    ControlBlockHandle(IHandle *);
    bool Test(const ASTNode &) const ;
};

class PrintHandle : public IHandle {
public:
    PrintHandle(IHandle *);
    bool Test(const ASTNode &) const ;
};

} // end of namespace haizei