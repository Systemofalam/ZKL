#include "validator.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Simple symbol table for tracking variable declarations
typedef struct SymbolTable {
    char** symbols; // Array of variable names
    int count;      // Number of variables
    int capacity;   // Capacity of the array
} SymbolTable;

// Initializes a symbol table
SymbolTable* create_symbol_table() {
    SymbolTable* table = (SymbolTable*)malloc(sizeof(SymbolTable));
    table->count = 0;
    table->capacity = 16;
    table->symbols = (char**)malloc(sizeof(char*) * table->capacity);
    return table;
}

// Frees a symbol table
void free_symbol_table(SymbolTable* table) {
    for (int i = 0; i < table->count; i++) {
        free(table->symbols[i]);
    }
    free(table->symbols);
    free(table);
}

// Adds a variable to the symbol table
void add_symbol(SymbolTable* table, const char* name) {
    if (table->count >= table->capacity) {
        table->capacity *= 2;
        table->symbols = (char**)realloc(table->symbols, sizeof(char*) * table->capacity);
    }
    table->symbols[table->count++] = strdup(name);
}

// Checks if a variable exists in the symbol table
bool has_symbol(const SymbolTable* table, const char* name) {
    for (int i = 0; i < table->count; i++) {
        if (strcmp(table->symbols[i], name) == 0) {
            return true;
        }
    }
    return false;
}

// Recursive AST validation function
void validate_ast(const ASTNode* node, SymbolTable* table) {
    if (!node) return;

    switch (node->type) {
        case AST_ASSIGNMENT:
            if (!node->value) {
                fprintf(stderr, "Error: Assignment must have a variable name.\n");
                exit(1);
            }
            validate_ast(node->left, table); // Validate the right-hand side expression
            add_symbol(table, node->value); // Add the variable to the symbol table
            break;

        case AST_ASSERTION:
            validate_ast(node->left, table); // Validate the assertion expression
            break;

        case AST_BINARY_OP:
            validate_ast(node->left, table); // Validate left operand
            validate_ast(node->right, table); // Validate right operand
            break;

        case AST_LITERAL:
            // Literals are always valid
            break;

        case AST_VARIABLE:
            if (!has_symbol(table, node->value)) {
                fprintf(stderr, "Error: Undefined variable '%s'.\n", node->value);
                exit(1);
            }
            break;

        default:
            fprintf(stderr, "Error: Unsupported AST node type %d.\n", node->type);
            exit(1);
    }
}

// Entry point for validating a program
void validate_program(const ASTNode* root) {
    if (!root || root->type != AST_PROGRAM) {
        fprintf(stderr, "Error: Root node must be of type AST_PROGRAM.\n");
        exit(1);
    }

    SymbolTable* table = create_symbol_table();
    validate_ast(root->left, table); // Validate the program body
    free_symbol_table(table);
}
