#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "ir_generator.h"

/**
 * Optimizes the given IR instructions.
 * 
 * @param ir The head of the IR instruction list.
 * @return The head of the optimized IR instruction list.
 */
IRInstruction* optimize_ir(IRInstruction* ir);

#endif // OPTIMIZER_H
