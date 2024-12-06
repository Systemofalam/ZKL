#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Forward declaration of helper functions
static ASTNode* parse_statement(Token** current);
static ASTNode* parse_expression(Token** current);
static ASTNode* parse_term(Token** current);
static ASTNode* parse_factor(Token** current);

// Helper to create an AST node
ASTNode* create_ast_node(ASTNodeType type, const char* value, ASTNode* left, ASTNode* right) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Error: Memory allocation failed for AST node.\n");
        exit(1);
    }
    node->type = type;
    node->value = value ? strdup(value) : NULL;
    node->left = left;
    node->right = right;
    return node;
}

// Frees an AST recursively
void free_ast(ASTNode* node) {
    if (!node) return;
    free_ast(node->left);
    free_ast(node->right);
    if (node->value) free(node->value);
    free(node);
}

// Main parser function
ASTNode* parse_tokens(Token* tokens) {
    Token* current = tokens; // Pointer to the current token
    ASTNode* root = create_ast_node(AST_PROGRAM, NULL, NULL, NULL); // Root program node
    ASTNode** program_body = &(root->left); // Link the body of the program

    // Parse each statement in sequence
    while (current->type != TOKEN_EOF) {
        ASTNode* statement = parse_statement(&current);
        if (!*program_body) {
            *program_body = statement; // First statement
        } else {
            // Append to the end of the program body (linked list)
            ASTNode* temp = *program_body;
            while (temp->right) temp = temp->right;
            temp->right = statement;
        }
    }

    return root;
}

// Parse a single statement
static ASTNode* parse_statement(Token** current) {
    Token* token = *current;

    if (token->type == TOKEN_IDENTIFIER) {
        // Assignment statement: identifier = expression
        Token* identifier = token;
        (*current)++; // Consume identifier
        if ((*current)->type != TOKEN_ASSIGN) {
            fprintf(stderr, "Error: Expected '=' after variable '%s'.\n", identifier->value);
            exit(1);
        }
        (*current)++; // Consume '='
        ASTNode* expression = parse_expression(current);
        return create_ast_node(AST_ASSIGNMENT, identifier->value, expression, NULL);
    } else if (token->type == TOKEN_KEYWORD_ASSERT) {
        // Assertion statement: assert(expression)
        (*current)++; // Consume 'assert'
        if ((*current)->type != TOKEN_LPAREN) {
            fprintf(stderr, "Error: Expected '(' after 'assert'.\n");
            exit(1);
        }
        (*current)++; // Consume '('
        ASTNode* expression = parse_expression(current);
        if ((*current)->type != TOKEN_RPAREN) {
            fprintf(stderr, "Error: Expected ')' after assertion expression.\n");
            exit(1);
        }
        (*current)++; // Consume ')'
        return create_ast_node(AST_ASSERTION, NULL, expression, NULL);
    }

    fprintf(stderr, "Error: Unexpected token '%s' at line %d, column %d.\n",
            token->value, token->line, token->column);
    exit(1);
}

// Parse an expression (e.g., addition or subtraction)
static ASTNode* parse_expression(Token** current) {
    // Parse the left-hand side term
    ASTNode* left = parse_term(current);

    // Look for operators and parse the right-hand side
    while ((*current)->type == TOKEN_OPERATOR &&
           (strcmp((*current)->value, "+") == 0 || strcmp((*current)->value, "-") == 0 ||
            strcmp((*current)->value, "==") == 0)) { // Include "=="
        Token* operator = *current;
        (*current)++; // Consume operator
        ASTNode* right = parse_term(current);
        left = create_ast_node(AST_BINARY_OP, operator->value, left, right);
    }

    return left;
}

// Parse a term (e.g., multiplication or division)
static ASTNode* parse_term(Token** current) {
    ASTNode* left = parse_factor(current);

    while ((*current)->type == TOKEN_OPERATOR && ((*current)->value[0] == '*' || (*current)->value[0] == '/')) {
        Token* operator = *current;
        (*current)++; // Consume operator
        ASTNode* right = parse_factor(current);
        left = create_ast_node(AST_BINARY_OP, operator->value, left, right);
    }

    return left;
}

// Parse a factor (e.g., literals, variables, or parenthesized expressions)
static ASTNode* parse_factor(Token** current) {
    Token* token = *current;

    if (token->type == TOKEN_NUMBER) {
        (*current)++; // Consume number
        return create_ast_node(AST_LITERAL, token->value, NULL, NULL);
    } else if (token->type == TOKEN_IDENTIFIER) {
        (*current)++; // Consume identifier
        return create_ast_node(AST_VARIABLE, token->value, NULL, NULL);
    } else if (token->type == TOKEN_LPAREN) {
        (*current)++; // Consume '('
        ASTNode* expression = parse_expression(current);
        if ((*current)->type != TOKEN_RPAREN) {
            fprintf(stderr, "Error: Expected ')' after expression.\n");
            exit(1);
        }
        (*current)++; // Consume ')'
        return expression;
    }

    fprintf(stderr, "Error: Unexpected token '%s' at line %d, column %d.\n",
            token->value, token->line, token->column);
    exit(1);
}

// Helper function to print indentation
static void print_indent(int indent) {
    for (int i = 0; i < indent; i++) {
        printf("  ");
    }
}

// Print the AST (recursive function)
void print_ast(const ASTNode* node, int indent) {
    if (!node) return;

    print_indent(indent);
    printf("Node Type: %d, Value: %s\n", node->type, node->value ? node->value : "NULL");

    // Print child nodes
    print_ast(node->left, indent + 1);
    print_ast(node->right, indent + 1);

    // Print next statement (if any)
    print_ast(node->next, indent);
}