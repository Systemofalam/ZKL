#include "optimizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Helper function to check if a string represents an integer
int is_integer(const char* str) {
    if (!str) return 0;
    while (*str) {
        if (!isdigit(*str++)) return 0;
    }
    return 1;
}

// Perform constant folding optimization
IRInstruction* constant_folding(IRInstruction* ir) {
    IRInstruction* current = ir;

    while (current) {
        // Check for constant binary operations
        if ((current->op == IR_OP_ADD || current->op == IR_OP_SUB ||
             current->op == IR_OP_MUL || current->op == IR_OP_DIV) &&
            is_integer(current->src1) && is_integer(current->src2)) {
            
            // Parse constants
            int val1 = atoi(current->src1);
            int val2 = atoi(current->src2);
            int result = 0;

            // Perform the operation
            switch (current->op) {
                case IR_OP_ADD: result = val1 + val2; break;
                case IR_OP_SUB: result = val1 - val2; break;
                case IR_OP_MUL: result = val1 * val2; break;
                case IR_OP_DIV: 
                    if (val2 == 0) {
                        fprintf(stderr, "Error: Division by zero.\n");
                        exit(1);
                    }
                    result = val1 / val2; 
                    break;
                default: break;
            }

            // Replace operation with constant result
            printf("Folding operation %d %s %d -> %d\n", val1, 
                   current->op == IR_OP_ADD ? "+" :
                   current->op == IR_OP_SUB ? "-" :
                   current->op == IR_OP_MUL ? "*" : "/", 
                   val2, result);

            char* folded_result = (char*)malloc(16);
            sprintf(folded_result, "%d", result);

            free(current->src1);
            free(current->src2);
            current->src1 = folded_result;
            current->src2 = NULL;
            current->op = IR_OP_ASSIGN;
        }

        // Propagate constants to subsequent instructions
        if (current->op == IR_OP_ASSIGN && is_integer(current->src1)) {
            IRInstruction* next = current->next;
            while (next) {
                if (next->src1 && strcmp(next->src1, current->dest) == 0) {
                    printf("Propagating constant %s to %s\n", current->src1, next->dest);
                    free(next->src1);
                    next->src1 = strdup(current->src1);
                }
                if (next->src2 && strcmp(next->src2, current->dest) == 0) {
                    printf("Propagating constant %s to %s\n", current->src1, next->dest);
                    free(next->src2);
                    next->src2 = strdup(current->src1);
                }
                next = next->next;
            }
        }

        current = current->next;
    }

    return ir;
}



// Main optimization function
IRInstruction* optimize_ir(IRInstruction* ir) {
    return constant_folding(ir);
}
