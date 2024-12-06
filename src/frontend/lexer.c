#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Maximum number of tokens to allocate initially
#define MAX_TOKENS 1024

// Helper function to create a token
Token* create_token(TokenType type, const char* value, int line, int column) {
    Token* token = (Token*)malloc(sizeof(Token));
    if (!token) {
        fprintf(stderr, "Error: Memory allocation failed for token.\n");
        exit(1);
    }

    token->type = type;
    token->value = strdup(value); // Duplicate the string value
    token->line = line;
    token->column = column;
    return token;
}

// Helper function to add a token to the token list
void add_token(Token* tokens, int* token_count, TokenType type, const char* value, int line, int column) {
    if (*token_count >= MAX_TOKENS) {
        fprintf(stderr, "Error: Maximum token limit reached.\n");
        exit(1);
    }
    tokens[*token_count] = *create_token(type, value, line, column);
    (*token_count)++;
}

// The main lexer function
Token* tokenize(const char* input) {
    Token* tokens = malloc(sizeof(Token) * MAX_TOKENS); // Allocate memory for tokens
    if (!tokens) {
        fprintf(stderr, "Error: Memory allocation failed for tokens array.\n");
        exit(1);
    }

    int token_count = 0; // Number of tokens generated
    int line = 1, column = 1; // Track line and column for error reporting

    for (const char* p = input; *p != '\0'; ++p) {
        // Skip whitespace
        if (isspace(*p)) {
            if (*p == '\n') {
                line++;
                column = 1;
            } else {
                column++;
            }
            continue;
        }

        // Handle identifiers or keywords
        if (isalpha(*p)) {
            const char* start = p;
            while (isalnum(*p)) p++;
            char* value = strndup(start, p - start); // Extract the identifier/keyword
            TokenType type = (strcmp(value, "assert") == 0) ? TOKEN_KEYWORD_ASSERT : TOKEN_IDENTIFIER;
            add_token(tokens, &token_count, type, value, line, column);
            column += p - start;
            p--; // Adjust pointer to compensate for the for loop increment
            free(value);
            continue;
        }

        // Handle numbers
        if (isdigit(*p)) {
            const char* start = p;
            while (isdigit(*p)) p++;
            char* value = strndup(start, p - start); // Extract the numeric value
            add_token(tokens, &token_count, TOKEN_NUMBER, value, line, column);
            column += p - start;
            p--; // Adjust pointer
            free(value);
            continue;
        }

        // Handle operators
        if (*p == '+' || *p == '-' || *p == '*' || *p == '/') {
            char op[2] = {*p, '\0'}; // Convert char to string
            add_token(tokens, &token_count, TOKEN_OPERATOR, op, line, column++);
            continue;
        }

        // Handle assignment operator
        if (*p == '=') {
            if (*(p + 1) == '=') { // Check for ==
                add_token(tokens, &token_count, TOKEN_OPERATOR, "==", line, column);
                p++; // Skip the second '='
                column += 2;
            } else { // Single '='
                add_token(tokens, &token_count, TOKEN_ASSIGN, "=", line, column++);
            }
            continue;
        }

        // Handle parentheses
        if (*p == '(') {
            add_token(tokens, &token_count, TOKEN_LPAREN, "(", line, column++);
            continue;
        }
        if (*p == ')') {
            add_token(tokens, &token_count, TOKEN_RPAREN, ")", line, column++);
            continue;
        }

        // Handle unexpected characters
        fprintf(stderr, "Error: Unexpected character '%c' at line %d, column %d.\n", *p, line, column);
        exit(1);
    }

    // Add the EOF token to mark the end of input
    add_token(tokens, &token_count, TOKEN_EOF, "EOF", line, column);

    return tokens; // Return the array of tokens
}

// Free the memory allocated for tokens
void free_tokens(Token* tokens) {
    for (int i = 0; tokens[i].type != TOKEN_EOF; i++) {
        free(tokens[i].value); // Free the dynamically allocated value
    }
    free(tokens); // Free the token array itself
}
