#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "parser.h" // For ASTNode and related structures

/**
 * Validates the Abstract Syntax Tree (AST).
 * 
 * @param root Pointer to the root of the AST.
 */
void validate_program(const ASTNode* root);

#endif // VALIDATOR_H
