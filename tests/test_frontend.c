#include <stdio.h>
#include "../src/frontend/lexer.h"
#include "../src/frontend/parser.h"
#include "../src/frontend/validator.h"

int main() {
    const char* code = "x = 3 + 5\nassert(x == 8)";
    printf("Input Code:\n%s\n\n", code);

    // Lexical Analysis
    Token* tokens = tokenize(code);
    printf("Tokens:\n");
    for (int i = 0; tokens[i].type != TOKEN_EOF; i++) {
        printf("Type: %d, Value: '%s', Line: %d, Column: %d\n",
               tokens[i].type, tokens[i].value, tokens[i].line, tokens[i].column);
    }

    // Parsing
    ASTNode* ast = parse_tokens(tokens);
    printf("\nAbstract Syntax Tree:\n");
    print_ast(ast, 0);

    // Validation
    printf("\nValidating AST...\n");
    validate_program(ast);
    printf("Validation successful!\n");

    // Free resources
    free_ast(ast);
    free_tokens(tokens);

    return 0;
    
}
