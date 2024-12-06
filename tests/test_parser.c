#include <stdio.h>
#include "../src/frontend/lexer.h"
#include "../src/frontend/parser.h"

// Helper to print an AST
void print_ast(ASTNode* node, int indent) {
    if (!node) return;
    for (int i = 0; i < indent; i++) printf("  ");
    printf("Node Type: %d, Value: %s\n", node->type, node->value ? node->value : "NULL");
    print_ast(node->left, indent + 1);
    print_ast(node->right, indent + 1);
}

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
