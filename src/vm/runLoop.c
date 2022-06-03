
#include "common.h"
#include "runLoop.h"
#include "opcodes.h"
//#include "vMachine.h"
#include "values.h"
#include "varStore.h"
#include "instrStore.h"
#include "valStack.h"
#include "memory.h"
#include "doArith.h"
#include "doComp.h"
#include "doJmps.h"
#include "errors.h"
#include "traps.h"

int runLoop(VM* vm)
{
    bool finished = false;
    uint8_t op;
    int retv = 0;

    while(!finished) {
        if(getErrors() > 0) {
            finished = true;
            retv = -getErrors();
            continue;
        }
        READ_VM_OBJ(uint8_t, op);

        switch(op) {

            // exit the VM with a error.
            case OP_ABORT: {
                    // Immediate is a VarIdx
                    fprintf(stderr, "runtime error: abort instruction: ");
                    VarIdx idx;
                    READ_VM_OBJ(VarIdx, idx);
                    printVal(getVar(&vm->vstore, idx));
                    fprintf(stderr, "\n");
                    finished = true;
                    retv = -1;
                }
                break;

            case OP_ABORTI: {
                    // immediate is a Value
                    fprintf(stderr, "runtime error: abort instruction: ");
                    Value val;
                    READ_VM_OBJ(Value, val);
                    printVal(val);
                    fprintf(stderr, "\n");
                    finished = true;
                    retv = -1;
                }
                break;

            case OP_ABORTR: {
                    // immediate is a register
                    fprintf(stderr, "runtime error: abort instruction: ");
                    uint8_t reg;
                    READ_VM_OBJ(uint8_t, reg);
                    finished = true;
                    printVal(vm->registers[reg]);
                    fprintf(stderr, "\n");
                    retv = -1;
                }
                break;


            case OP_EXIT:
                // exit with no error
                printf("exiting\n");
                finished = true;
                retv = 0;
                break;

            case OP_NOP:
                // do nothing
                break;

            case OP_CALL: {
                    // operand is a Value index
                    VarIdx idx;
                    READ_VM_OBJ(VarIdx, idx);
                    doCall(vm, getVar(&vm->vstore, idx));
                }
                break;

            case OP_CALLI:{
                    // operand is an immediate Value
                    Value val;
                    READ_VM_OBJ(Value, val);
                    doCall(vm, val);
                }
                break;

            case OP_CALLR:{
                    // operand is a single register
                    uint8_t reg;
                    READ_VM_OBJ(uint8_t, reg);
                    doCall(vm, vm->registers[reg]);
                }
                break;

            case OP_RCALL:{
                    // operand is a Value index
                    VarIdx idx;
                    READ_VM_OBJ(VarIdx, idx);
                    doRCall(vm, getVar(&vm->vstore, idx));
                }
                break;

            case OP_RCALLI:{
                    // operand is a immediate value
                    Value val;
                    READ_VM_OBJ(Value, val);
                    doRCall(vm, val);
                }
                break;

            case OP_RCALLR:{
                    // operand is a single register
                    RegNumType reg;
                    READ_VM_OBJ(RegNumType, reg);
                    doRCall(vm, vm->registers[reg]);
                }
                break;

            case OP_TRAP: {
                    // operand is a uint16_t
                    TrapNumType tno;
                    READ_VM_OBJ(TrapNumType, tno);
                    doTrap(vm, tno);
                }
                break;

            case OP_RETURN: {
                    // no operands
                    doReturn(vm);
                }
                break;

            case OP_JMP:{
                    // operand is a Value index
                    VarIdx idx;
                    READ_VM_OBJ(VarIdx, idx);
                    doJmp(vm, getVar(&vm->vstore, idx));
                }
                break;

            case OP_JMPI:{
                    // operand is an immediate Value
                    Value val;
                    READ_VM_OBJ(Value, val);
                    doJmp(vm, val);
                }
                break;

            case OP_JMPR:{
                    // operand is a single register
                    RegNumType reg;
                    READ_VM_OBJ(RegNumType, reg);
                    doJmp(vm, vm->registers[reg]);
                }
                break;

            case OP_RJMP:{
                    // operand is a Value index
                    VarIdx idx;
                    READ_VM_OBJ(VarIdx, idx);
                    doRJmp(vm, getVar(&vm->vstore, idx));
                }
                break;

            case OP_RJMPI:{
                    // operand is an immediate Value
                    Value val;
                    READ_VM_OBJ(Value, val);
                    doRJmp(vm, val);
                }
                break;

            case OP_RJMPR:{
                    // operand is a single register
                    RegNumType reg;
                    READ_VM_OBJ(RegNumType, reg);
                    doRJmp(vm, vm->registers[reg]);
                }
                break;

            case OP_BR:{
                    // operand is a Value Index
                    VarIdx idx;
                    READ_VM_OBJ(VarIdx, idx);
                    doBr(vm, getVar(&vm->vstore, idx));
                }
                break;

            case OP_BRI: {
                    // operand is an immediate Value
                    Value val;
                    READ_VM_OBJ(Value, val);
                    doBr(vm, val);
                }
                break;

            case OP_BRR: {
                    // operand is a single register
                    RegNumType reg;
                    READ_VM_OBJ(RegNumType, reg);
                    doBr(vm, vm->registers[reg]);
                }
                break;

            case OP_RBR: {
                    // operand is a Value index
                    VarIdx idx;
                    READ_VM_OBJ(VarIdx, idx);
                    doRBr(vm, getVar(&vm->vstore, idx));
                }
                break;

            case OP_RBRI: {
                    // operand is an immediate Value
                    Value val;
                    READ_VM_OBJ(Value, val);
                    doRBr(vm, val);
                }
                break;

            case OP_RBRR: {
                    // operand is a single register
                    RegNumType reg;
                    READ_VM_OBJ(RegNumType, reg);
                    doRBr(vm, vm->registers[reg]);
                }
                break;

            case OP_PUSH: {
                    // operand is a Value index
                    VarIdx idx;
                    READ_VM_OBJ(VarIdx, idx);
                    pushValStack(&vm->vstack, getVar(&vm->vstore, idx));
                }
                break;

            case OP_PUSHI: {
                    // operand is an immediate Value
                    Value val;
                    READ_VM_OBJ(Value, val);
                    pushValStack(&vm->vstack, val);
                }
                break;

            case OP_PUSHR: {
                    // operand is a single register
                    RegNumType reg;
                    READ_VM_OBJ(RegNumType, reg);
                    pushValStack(&vm->vstack, vm->registers[reg]);
                }
                break;

            case OP_POP: {
                    // operand is a single register
                    uint8_t reg;
                    READ_VM_OBJ(uint8_t, reg);
                    vm->registers[reg] = popValStack(&vm->vstack);
                }
                break;

            case OP_PEEK: {
                    // operand is a single register
// TODO: operand is an immediate Value
                    RegNumType reg;
                    READ_VM_OBJ(RegNumType, reg);
                    vm->registers[reg] = peekValStack(&vm->vstack, 0);
                }
                break;

            case OP_LOAD: {
                    // operand is a single register
                    // operand is a Value index
                    RegNumType reg;
                    READ_VM_OBJ(RegNumType, reg);
                    VarIdx idx;
                    READ_VM_OBJ(VarIdx, idx);
                    vm->registers[reg] = getVar(&vm->vstore, idx);
                }
                break;

            case OP_LOADI: {
                    // operand is a single register
                    // operand is an immediate Value
                    RegNumType reg;
                    READ_VM_OBJ(RegNumType, reg);
                    Value val;
                    READ_VM_OBJ(Value, val);
                    vm->registers[reg] = val;
                }
                break;

            case OP_LOADR: {
                    // operand is 2 registers
                    RegNumType regs;
                    READ_VM_OBJ(RegNumType, regs);
                    vm->registers[(regs >> 4) & 0xF] = vm->registers[regs & 0xF];
                }
                break;

            case OP_STORE: {
                    // operand is a Value index
                    // operand is a single register
                    VarIdx idx;
                    READ_VM_OBJ(VarIdx, idx);
                    RegNumType reg;
                    READ_VM_OBJ(RegNumType, reg);
                    assignVar(&vm->vstore, idx, vm->registers[reg]);
                }
                break;

            case OP_NOT: {
                    // operand is single register (result in zero flag)
                    RegNumType reg;
                    READ_VM_OBJ(RegNumType, reg);
                    doNot(vm, reg);
                }
                break;

            case OP_EQ: {
                    // operand is 2 registers (result in zero flag)
                    RegNumType regs;
                    READ_VM_OBJ(RegNumType, regs);
                    doEq(vm, regs);
                }
                break;

            case OP_NEQ: {
                    // operand is 2 registers (result in zero flag)
                    RegNumType regs;
                    READ_VM_OBJ(RegNumType, regs);
                    doNEq(vm, regs);
                }
                break;

            case OP_LEQ: {
                    // operand is 2 registers (result in zero flag)
                    RegNumType regs;
                    READ_VM_OBJ(RegNumType, regs);
                    doLeq(vm, regs);
                }
                break;

            case OP_GEQ: {
                    // operand is 2 registers (result in zero flag)
                    RegNumType regs;
                    READ_VM_OBJ(RegNumType, regs);
                    doGeq(vm, regs);
                }
                break;

            case OP_LESS: {
                    // operand is 2 registers (result in zero flag)
                    RegNumType regs;
                    READ_VM_OBJ(RegNumType, regs);
                    doLess(vm, regs);
                }
                break;

            case OP_GTR: {
                    // operand is 2 registers (result in zero flag)
                    RegNumType regs;
                    READ_VM_OBJ(RegNumType, regs);
                    doGtr(vm, regs);
                }
                break;

            case OP_NEG: {
                    // operand is 2 registers
                    RegNumType regs;
                    READ_VM_OBJ(RegNumType, regs);
                    doNeg(vm, regs);
                }
                break;

            case OP_ADD: {
                    // operand is 3 registers
                    uint16_t regs;
                    READ_VM_OBJ(uint16_t, regs);
                    doAdd(vm, regs);
                }
                break;

            case OP_SUB: {
                    // operand is 3 registers
                    uint16_t regs;
                    READ_VM_OBJ(uint16_t, regs);
                    doSub(vm, regs);
                }
                break;

            case OP_MUL: {
                    // operand is 3 registers
                    uint16_t regs;
                    READ_VM_OBJ(uint16_t, regs);
                    doMul(vm, regs);
                }
                break;

            case OP_DIV: {
                    // operand is 3 registers
                    uint16_t regs;
                    READ_VM_OBJ(uint16_t, regs);
                    doDiv(vm, regs);
                }
                break;

            case OP_MOD: {
                    // operand is 3 registers
                    uint16_t regs;
                    READ_VM_OBJ(uint16_t, regs);
                    doMod(vm, regs);
                }
                break;

            default:
                fprintf(stderr, "runtime error: Unknown instruction: 0x%02X\n", op);
                finished = true;
                retv = -2;
                break;
        }
    }

    return retv;
}
