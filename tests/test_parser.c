#include <stdio.h>
#include "../src/frontend/lexer.h"
#include "../src/frontend/parser.h"



int main() {
    const char* code = "x = 3 + 5\nassert(x == 8)";
    Token* tokens = tokenize(code);

    ASTNode* ast = parse_tokens(tokens);
    printf("Abstract Syntax Tree:\n");
    print_ast(ast, 0);

    free_ast(ast);
    free_tokens(tokens);
    return 0;
}
