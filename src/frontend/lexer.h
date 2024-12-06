#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>

// Enum to represent different types of tokens
typedef enum {
    TOKEN_IDENTIFIER,   // Variable names or keywords
    TOKEN_NUMBER,       // Numeric constants
    TOKEN_OPERATOR,     // Operators (+, -, *, /)
    TOKEN_ASSIGN,       // Assignment operator (=)
    TOKEN_KEYWORD_ASSERT, // "assert" keyword
    TOKEN_LPAREN,       // Left parenthesis '('
    TOKEN_RPAREN,       // Right parenthesis ')'
    TOKEN_EOF           // End of file/input
} TokenType;

// Struct to represent a single token
typedef struct {
    TokenType type;     // Type of the token
    char* value;        // Token value as a string (e.g., "x", "42", "+")
    int line;           // Line number where the token was found
    int column;         // Column number where the token starts
} Token;

// Function prototypes

/**
 * Tokenizes the given input string.
 * 
 * @param input The input string to tokenize.
 * @return A dynamically allocated array of tokens, terminated by a TOKEN_EOF.
 */
Token* tokenize(const char* input);

/**
 * Frees a dynamically allocated array of tokens.
 * 
 * @param tokens The array of tokens to free.
 */
void free_tokens(Token* tokens);

#endif // LEXER_H
