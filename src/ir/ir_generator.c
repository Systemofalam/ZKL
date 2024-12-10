#include "ir_generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Static counter for generating sequential temporary variable names
static int temp_var_counter = 0;

// Helper to create a new IR instruction
IRInstruction* create_ir_instruction(IROpType op, const char* dest, const char* src1, const char* src2) {
    IRInstruction* instr = (IRInstruction*)malloc(sizeof(IRInstruction));
    if (!instr) {
        fprintf(stderr, "Error: Memory allocation failed for IR instruction.\n");
        exit(1);
    }
    instr->op = op;
    instr->dest = dest ? strdup(dest) : NULL;
    instr->src1 = src1 ? strdup(src1) : NULL;
    instr->src2 = src2 ? strdup(src2) : NULL;
    instr->next = NULL;
    return instr;
}

// Recursive function to generate IR from an AST node
IRInstruction* generate_ir_from_ast(const ASTNode* node) {
    if (!node) return NULL;

    switch (node->type) {
        case AST_PROGRAM: {
            // Handle the root program node by iterating over child statements
            IRInstruction* head = NULL;
            IRInstruction* tail = NULL;

            for (ASTNode* stmt = node->left; stmt != NULL; stmt = stmt->next) {
                IRInstruction* stmt_ir = generate_ir_from_ast(stmt);
                if (!head) {
                    head = stmt_ir;
                } else {
                    tail->next = stmt_ir;
                }
                // Move to the end of the current IR list
                while (tail && tail->next) {
                    tail = tail->next;
                }
            }
            return head;
        }

        case AST_ASSIGNMENT: {
            // Generate IR for the right-hand side expression
            IRInstruction* rhs = generate_ir_from_ast(node->left);
            // Create an assignment IR instruction
            IRInstruction* assign = create_ir_instruction(IR_OP_ASSIGN, node->value, rhs->dest, NULL);
            assign->next = rhs;
            return assign;
        }

        case AST_BINARY_OP: {
            // Map binary operator strings to IR operation types
            IROpType op;
            if (strcmp(node->value, "+") == 0) op = IR_OP_ADD;
            else if (strcmp(node->value, "-") == 0) op = IR_OP_SUB;
            else if (strcmp(node->value, "*") == 0) op = IR_OP_MUL;
            else if (strcmp(node->value, "/") == 0) op = IR_OP_DIV;
            else if (strcmp(node->value, "==") == 0) op = IR_OP_EQ;
            else {
                fprintf(stderr, "Error: Unsupported binary operator '%s'.\n", node->value);
                exit(1);
            }

            // Generate IR for left and right operands
            IRInstruction* left = generate_ir_from_ast(node->left);
            IRInstruction* right = generate_ir_from_ast(node->right);

            // Create a temporary variable for the result
            char* temp = (char*)malloc(16);
            sprintf(temp, "t%d", temp_var_counter++);

            // Create the binary operation IR instruction
            IRInstruction* instr = create_ir_instruction(op, temp, left->dest, right->dest);
            instr->next = left;
            left->next = right;
            return instr;
        }

        case AST_ASSERTION: {
            // Generate IR for the assertion expression
            IRInstruction* expr = generate_ir_from_ast(node->left);
            // Create an assertion IR instruction
            IRInstruction* assert = create_ir_instruction(IR_OP_ASSERT, NULL, expr->dest, NULL);
            assert->next = expr;
            return assert;
        }

        case AST_LITERAL:
        case AST_VARIABLE: {
            // Create a temporary variable for the literal or variable value
            char* temp = (char*)malloc(16);
            sprintf(temp, "t%d", temp_var_counter++);
            return create_ir_instruction(IR_OP_ASSIGN, temp, node->value, NULL);
        }

        default:
            fprintf(stderr, "Error: Unsupported AST node type %d.\n", node->type);
            exit(1);
    }
    return NULL;
}

// Entry point for IR generation
IRInstruction* generate_ir(const ASTNode* ast) {
    temp_var_counter = 0; // Reset the temporary variable counter
    return generate_ir_from_ast(ast);
}

// Free IR instructions
void free_ir(IRInstruction* ir) {
    while (ir) {
        IRInstruction* next = ir->next;
        free(ir->dest);
        free(ir->src1);
        free(ir->src2);
        free(ir);
        ir = next;
    }
}

// Print IR instructions
void print_ir(const IRInstruction* ir) {
    while (ir) {
        printf("Op: %d, Dest: %s, Src1: %s, Src2: %s\n",
               ir->op, ir->dest ? ir->dest : "NULL",
               ir->src1 ? ir->src1 : "NULL",
               ir->src2 ? ir->src2 : "NULL");
        ir = ir->next;
    }
}
