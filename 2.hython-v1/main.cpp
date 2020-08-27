/*
* @Author: lbh
* @Date: 2020-08-27 13:39:39 
 * @Last Modified by: mikey.zhaopeng
 * @Last Modified time: 2020-08-27 14:05:14
*/
#include <head.h>
#include <hythonLexer.h>
#include <hythonParser.h>
using std::map;
using std::string;
using std::cout;
using std::endl;
 
class ExprTreeEvaluator {
    map<string,int> memory;
    int block_cnt = 0;
public:
    ExprTreeEvaluator() : next(NULL){}
    ExprTreeEvaluator(ExprTreeEvaluator *next) : next(next) {}
    int run(pANTLR3_BASE_TREE);
    void set_param(string name, int val);
    void def_param(string name, int val);
    int get_param(string name);
    ExprTreeEvaluator *next;
};

pANTLR3_BASE_TREE getChild(pANTLR3_BASE_TREE, unsigned);
const char* getText(pANTLR3_BASE_TREE tree);
 
int main(int argc, char* argv[])
{
  pANTLR3_INPUT_STREAM input;
  phythonLexer lex;
  pANTLR3_COMMON_TOKEN_STREAM tokens;
  phythonParser parser;
 
  assert(argc > 1);
  input = antlr3FileStreamNew((pANTLR3_UINT8)argv[1],ANTLR3_ENC_8BIT);
  lex = hythonLexerNew(input);
  tokens = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT,
                                            TOKENSOURCE(lex));
  parser = hythonParserNew(tokens);
 
  hythonParser_prog_return r = parser->prog(parser);
 
  pANTLR3_BASE_TREE tree = r.tree;
 
  ExprTreeEvaluator eval;
  int rr = eval.run(tree);
  cout << "Evaluator result: " << rr << '\n';
 
  parser->free(parser);
  tokens->free(tokens);
  lex->free(lex);
  input->close(input);
 
  return 0;
}

void ExprTreeEvaluator::def_param(string name, int val) {
    if (memory.find(name) != memory.end()) {
        throw std::runtime_error("!!![Error] param redefined : " + name);
    }
    memory[name] = val;
    return ;
}

void ExprTreeEvaluator::set_param(string name, int val) {
    if (memory.find(name) != memory.end()) {
        memory[name] = val;
        return ;
    }
    if (this->next) {
        this->next->set_param(name, val);
        return ;
    }
}

int ExprTreeEvaluator::get_param(string name) {
    if (this->memory.find(name) == this->memory.end() && !this->next) {
        throw std::runtime_error("!!![Error] param unknown : " + name);
    } 
    if (this->memory.find(name) != this->memory.end()) {
        return this->memory[name];
    }
    if (this->next) return this->next->get_param(name);
    return 0;
}

int ExprTreeEvaluator::run(pANTLR3_BASE_TREE tree)
{
    pANTLR3_COMMON_TOKEN tok = tree->getToken(tree);
    if(tok) {
        switch(tok->type) {
        case INT: {
            const char* s = getText(tree);
            if(s[0] == '~') {
                return -atoi(s+1);
            }
            else {
                return atoi(s);
            }
        }
        case ID: {
            string var(getText(tree));
            return this->get_param(var);
        }
        case PLUS:
            return run(getChild(tree,0)) + run(getChild(tree,1));
        case MINUS:
            return run(getChild(tree,0)) - run(getChild(tree,1));
        case TIMES:
            return run(getChild(tree,0)) * run(getChild(tree,1));
        case DIV:
            return run(getChild(tree,0)) / run(getChild(tree,1));
        case MOD:
            return run(getChild(tree,0)) % run(getChild(tree,1));
        case ASSIGN: {
            string var(getText(getChild(tree,0)));
            int val = run(getChild(tree,1));
            this->set_param(var, val);
            return 1;
        }
        case DEF: {
            int k = tree->getChildCount(tree);
            int init_val = 0;
            for(int i = 0; i < k; i++) {
                pANTLR3_BASE_TREE child = getChild(tree, i);
                string var(getText(child));
                if (child->getChildCount(child) == 1) {
                    init_val = run(getChild(child, 0));
                }
                cout << "var : " << var << " = " << init_val << endl;
                this->def_param(var, init_val);
            }
            return init_val;
        }
        case BLOCK: {
            ExprTreeEvaluator tmp(this);
            int k = tree->getChildCount(tree);
            int r = 0;
            for(int i = 0; i < k; i++) {
                r = tmp.run(getChild(tree, i));
                //cout << "Block value : " << r << endl;
            }
            return r;
        }
        case PRINT: {
            int k = tree->getChildCount(tree);
            int r = 0;
            for(int i = 0; i < k; i++) {
                r = run(getChild(tree, i));
                cout << r;
            }
            cout << endl;
            return 1;
        }
        case WHILE: {
            cout << "In while" << endl;
            return 0;
        }
        case OR: {
            cout << "In OR" << endl;
            return 0;
        }
        case AND: {
            cout << "In AND" << endl;
            return 0;
        }
        case GE: {
            cout << "In GE" << endl;
            return 0;
        }
        case GT: {
            cout << "In GT" << endl;
            return 0;
        }
        case LE: {
            cout << "In LE" << endl;
            return 0;
        }
        case LITTLE: {
            cout << "In LITTLE" << endl;
            return 0;
        }
        case EQ: {
            cout << "In EQ" << endl;
            return 0;
        }
        case NE: {
            cout << "In NE" << endl;
            return 0;
        }
        case IF: {
            cout << "In IF" << endl;
            return 0;
        }
        default:
            cout << "Unhandled token: #" << tok->type << '\n';
            return -1;
        }
    }
    else {
        int k = tree->getChildCount(tree);
        int r = 0;
        for(int i = 0; i < k; i++) {
            r = run(getChild(tree, i));
            cout << "lbh result----" << r << endl;
        }
        return r;
    }
}

pANTLR3_BASE_TREE getChild(pANTLR3_BASE_TREE tree, unsigned i)
{
    assert(i < tree->getChildCount(tree));
    return (pANTLR3_BASE_TREE) tree->getChild(tree, i);
}

const char* getText(pANTLR3_BASE_TREE tree)
{
    return (const char*) tree->getText(tree)->chars;
}
