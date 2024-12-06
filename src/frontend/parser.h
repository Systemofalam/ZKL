#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

// Enum for different AST node types
typedef enum {
    AST_PROGRAM,      // Root node for the program
    AST_ASSIGNMENT,   // Assignment statement (e.g., x = 3 + 5)
    AST_ASSERTION,    // Assertion (e.g., assert(x == 8))
    AST_BINARY_OP,    // Binary operations (+, -, *, /)
    AST_LITERAL,      // Numeric or identifier literal
    AST_VARIABLE      // Variable reference
} ASTNodeType;

// Struct for an AST node
typedef struct ASTNode {
    ASTNodeType type;       // Type of the node
    char* value;            // Literal value or variable name
    struct ASTNode* left;   // Left child (e.g., LHS of an expression)
    struct ASTNode* right;  // Right child (e.g., RHS of an expression)
    struct ASTNode* next;   // Next statement in the sequence
} ASTNode;

// Function prototypes

/**
 * Parses an array of tokens and constructs an Abstract Syntax Tree.
 * 
 * @param tokens Array of tokens from the lexer.
 * @return Pointer to the root of the constructed AST.
 */
ASTNode* parse_tokens(Token* tokens);

/**
 * Frees an Abstract Syntax Tree.
 * 
 * @param node The root node of the AST to free.
 */
void free_ast(ASTNode* node);


/**
 * Prints the ast.
 * 
 * @param node The root node of the AST to print 
 * @param indent The number of indentations.
 */
void print_ast(const ASTNode* node, int indent);

#endif // PARSER_H
