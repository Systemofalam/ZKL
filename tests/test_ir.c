#include <stdio.h>
#include "../src/frontend/parser.h"
#include "../src/ir/ir_generator.h"
#include "../src/ir/optimizer.h"

int main() {
    // Input code (parsed into AST)
    const char* code = "x = 3 + 6\nassert(x == 8)";
    Token* tokens = tokenize(code);
    ASTNode* ast = parse_tokens(tokens);

    // Generate IR
    IRInstruction* ir = generate_ir(ast);
    printf("Generated IR:\n");
    print_ir(ir);

    // Optimize IR
    IRInstruction* optimized_ir = optimize_ir(ir);
    printf("\nOptimized IR:\n");
    print_ir(optimized_ir);

    // Free resources
    free_ir(ir);
    free_tokens(tokens);
    free_ast(ast);
    return 0;
}
