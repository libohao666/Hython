grammar ExprCppTree;
options {
    language = C;
    output = AST;
    ASTLabelType=pANTLR3_BASE_TREE;
}
@header {
    #include <assert.h>
}
expr: multExpr ((PLUS^ | MINUS^) multExpr)*
    ;
PLUS: '+';
MINUS: '-';
multExpr
    : atom ((TIMES^ | CHU^ | QUYU^) atom)*
    ;
TIMES: '*';
CHU: '/';
QUYU: '%';
atom: INT
    | ID
    | '('! expr ')'!
    ;
stmt:
    expr_stmt
    | block
    ;
expr_stmt: 
    expr NEWLINE -> expr  // tree rewrite syntax
    | ID ASSIGN expr NEWLINE -> ^(ASSIGN ID expr) // tree notation
    | NEWLINE 
    ;
code:
    '{'! stmt* '}'!
    ;
BLOCK: '{}';
block:
    code -> ^(BLOCK code);
ASSIGN: '=';
prog
    : (stmt {
            pANTLR3_STRING s = $stmt.tree->toStringTree($stmt.tree);
            assert(s->chars);
            printf("lbh-tree \%s\n", s->chars);
            }
        )+
    ;
ID: ('a'..'z'|'A'..'Z')+ ;
INT: '~'? '0'..'9'+ ;
NEWLINE: '\r'? '\n';
WS  :(' '|'/t'|'/r''/n'|'/n');
//WS : (' '|'\t')+ {$channel = HIDDEN;};
