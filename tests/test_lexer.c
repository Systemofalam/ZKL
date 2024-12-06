#include <stdio.h>
#include "../src/frontend/lexer.h"

int main() {
    const char* code = "x = 3 + 5\nassert(x == 8)";
    Token* tokens = tokenize(code);

    printf("Tokens:\n");
    for (int i = 0; tokens[i].type != TOKEN_EOF; i++) {
        printf("Type: %d, Value: '%s', Line: %d, Column: %d\n",
               tokens[i].type, tokens[i].value, tokens[i].line, tokens[i].column);
    }

    free_tokens(tokens); // Free the tokens after use
    return 0;
}
