# Hython语言设计与开发

## 项目描述

​	c++综合项目，设计开发一门语言。

​	参考 https://code.aliyun.com/huguangchaoren/hython_198.git

## 1.Antlr 的基础使用

```cpp
1. 增加除法表达式的支持（增加文本【源代码】中的关键字）
2. 增加取余表达式的支持（增加文本【源代码】中的关键字）
3. 修改解释器，对于每一行内容，都输出其表达式的值（修改解释器的功能）
4. 增加变量定义的语法结构
5. 增加作用域的功能
```

antlr配置 [配置](file://0.About/antlr配置.md)

## 2.简单的流程控制

```cpp
1.整理工程目录，include/lib/bin/src/...
2.整理 main.cpp 内容，分成头文件和原文件，main.cpp 尽量简单
3.print 子句
4.增加条件表达式(==,<=, >=, && , ||)
5.if 结构的增加
6.for 结构的增加
7.while 结构的增加
8.do...while 结构的增加
```



![1](1.png)

### 使用Antlr的C接口

Antlr 4，它是一个非常强大的词法、语法分析器辅助生成工具，比之前用Flex + Bison强太多倍。遗憾的是，当前的v4只支持Java，暂不支持C、C++，于是降级了一把，尝试了一下在3.4版上使用Antlr C。

```bash
wget http://www.antlr3.org/download/C/libantlr3c-3.4.tar.gz
tar -xzvf ./libantlr3c-3.4.tar.gz
./configure --enable-64bit
make
sudo make install
wget http://www.antlr3.org/download/antlr-3.4-complete.jar
```

ExprCppTree.g 

```java
grammar ExprCppTree;
options {
    language = C;
    output = AST;
    ASTLabelType=pANTLR3_BASE_TREE;
}
@header {
    #include <assert.h>
}
// The suffix '^' means make it a root.
// The suffix '!' means ignore it.
expr: multExpr ((PLUS^ | MINUS^) multExpr)*
    ;
PLUS: '+';
MINUS: '-';
multExpr
    : atom (TIMES^ atom)*
    ;
TIMES: '*';
atom: INT
    | ID
    | '('! expr ')'!
    ;
stmt: expr NEWLINE -> expr  // tree rewrite syntax
    | ID ASSIGN expr NEWLINE -> ^(ASSIGN ID expr) // tree notation
    | NEWLINE ->   // ignore
    ;
ASSIGN: '=';
prog
    : (stmt {pANTLR3_STRING s = $stmt.tree->toStringTree($stmt.tree);
             assert(s->chars);
             printf(" tree \%s\n", s->chars);
            }
        )+
    ;
ID: ('a'..'z'|'A'..'Z')+ ;
INT: '~'? '0'..'9'+ ;
NEWLINE: '\r'? '\n' ;
WS : (' '|'\t')+ {$channel = HIDDEN;};
```

```bash
lbh@lbh-PC:~/Desktop/ALL/1.haizei/19.hython/Hython/1.antlr_test/test1$ java -jar ../download/antlr-3.4-complete.jar ./ExprCppTree.g 
```

main.cpp

```cpp
#include "ExprCppTreeLexer.h"
#include "ExprCppTreeParser.h"
#include <cassert>
#include <map>
#include <string>
#include <iostream>
using std::map;
using std::string;
using std::cout;
class ExprTreeEvaluator {
    map<string,int> memory;
public:
    int run(pANTLR3_BASE_TREE);
};
pANTLR3_BASE_TREE getChild(pANTLR3_BASE_TREE, unsigned);
const char* getText(pANTLR3_BASE_TREE tree);
int main(int argc, char* argv[])
{
  pANTLR3_INPUT_STREAM input;
  pExprCppTreeLexer lex;
  pANTLR3_COMMON_TOKEN_STREAM tokens;
  pExprCppTreeParser parser;
  assert(argc > 1);
  input = antlr3FileStreamNew((pANTLR3_UINT8)argv[1],ANTLR3_ENC_8BIT);
  lex = ExprCppTreeLexerNew(input);
  tokens = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT,
                                            TOKENSOURCE(lex));
  parser = ExprCppTreeParserNew(tokens);
  ExprCppTreeParser_prog_return r = parser->prog(parser);
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
            return memory[var];
        }
        case PLUS:
            return run(getChild(tree,0)) + run(getChild(tree,1));
        case MINUS:
            return run(getChild(tree,0)) - run(getChild(tree,1));
        case TIMES:
            return run(getChild(tree,0)) * run(getChild(tree,1));
        case ASSIGN: {
            string var(getText(getChild(tree,0)));
            int val = run(getChild(tree,1));
            memory[var] = val;
            return val;
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
```



```bash
lbh@lbh-PC:~/Desktop/ALL/1.haizei/19.hython/Hython/1.antlr_test/test1$ g++ -g -Wall *.cpp *.c ../download/libantlr3c-3.4/.libs/libantlr3c.a -o test -I. -I ../download/libantlr3c-3.4/include/
```

data

```
1+2*(3+4)
```



```bash
lbh@lbh-PC:~/Desktop/ALL/1.haizei/19.hython/Hython/1.antlr_test/test1$ ./test data 
 tree (+ 1 (* 2 (+ 3 4)))
Evaluator result: 15

```

