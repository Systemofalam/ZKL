#ifndef IR_GENERATOR_H
#define IR_GENERATOR_H

#include "../frontend/parser.h"

// Enum for IR operation types
typedef enum {
    IR_OP_ASSIGN,  // Assignment operation
    IR_OP_ADD,     // Addition
    IR_OP_SUB,     // Subtraction
    IR_OP_MUL,     // Multiplication
    IR_OP_DIV,     // Division
    IR_OP_EQ,      // Equality check
    IR_OP_ASSERT   // Assertion
} IROpType;

// Structure for a single IR instruction
typedef struct IRInstruction {
    IROpType op;              // Operation type
    char* dest;               // Destination variable
    char* src1;               // Source operand 1
    char* src2;               // Source operand 2 (if applicable)
    struct IRInstruction* next; // Pointer to the next instruction
} IRInstruction;

// Function prototypes

/**
 * Generates the IR from the given AST.
 * 
 * @param ast The root of the Abstract Syntax Tree.
 * @return The head of the linked list of IR instructions.
 */
IRInstruction* generate_ir(const ASTNode* ast);

/**
 * Frees the memory allocated for the IR instructions.
 * 
 * @param ir The head of the IR instruction list.
 */
void free_ir(IRInstruction* ir);

/**
 * Prints the IR instructions for debugging.
 * 
 * @param ir The head of the IR instruction list.
 */
void print_ir(const IRInstruction* ir);

#endif // IR_GENERATOR_H
