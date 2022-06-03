
#include "common.h"
#include "vMachine.h"
#include "opcodes.h"
#include "traps.h"
#include "registers.h"
#include "values.h"
#include "errors.h"

void showListing(VM* vm)
{
    uint8_t op;
    FILE* outf = stdout;
    bool finished = false;

    while(!finished) {

        READ_VM_OBJ(uint8_t, op);
        fprintf(outf, "%04d: %s\t", getInstrIndex(&vm->istore), opToStr(op));

        switch(op) {

            // exit the VM with a error.
            case OP_ABORT: {
                    // Immediate is a VarIdx
                    VarIdx idx;
                    READ_VM_OBJ(VarIdx, idx);
                    printVal(getVar(&vm->vstore, idx));
                }
                break;

            case OP_ABORTI: {
                    // immediate is a Value
                    Value val;
                    READ_VM_OBJ(Value, val);
                    printVal(val);
                }
                break;

            case OP_ABORTR: {
                    // immediate is a register
                    uint8_t reg;
                    READ_VM_OBJ(uint8_t, reg);
                    printVal(vm->registers[reg]);
                }
                break;


            case OP_EXIT:
            case OP_NOP:
            case OP_RETURN:
                // no parameters
                break;

            case OP_CALL: {
                    // operand is a Value index
                    VarIdx idx;
                    READ_VM_OBJ(VarIdx, idx);
                    fprintf(outf, "<%d>\t", idx);
                    printVal(getVar(&vm->vstore, idx));
                }
                break;

            case OP_CALLI:{
                    // operand is an immediate Value
                    Value val;
                    READ_VM_OBJ(Value, val);
                    printVal(val);
                }
                break;

            case OP_CALLR:{
                    // operand is a single register
                    uint8_t reg;
                    READ_VM_OBJ(uint8_t, reg);
                    fprintf(outf, "<%s>\t", regToStr(reg));
                    printVal(vm->registers[reg]);
                }
                break;

            case OP_RCALL:{
                    // operand is a Value index
                    VarIdx idx;
                    READ_VM_OBJ(VarIdx, idx);
                    fprintf(outf, "<%d>\t", idx);
                    printVal(getVar(&vm->vstore, idx));
                }
                break;

            case OP_RCALLI:{
                    // operand is a immediate value
                    Value val;
                    READ_VM_OBJ(Value, val);
                    printVal(val);
                }
                break;

            case OP_RCALLR:{
                    // operand is a single register
                    RegNumType reg;
                    READ_VM_OBJ(RegNumType, reg);
                    fprintf(outf, "<%s>\t", regToStr(reg));
                    printVal(vm->registers[reg]);
                }
                break;

            case OP_TRAP: {
                    // operand is a uint16_t
                    TrapNumType tno;
                    READ_VM_OBJ(TrapNumType, tno);
                    fprintf(outf, "<%d>\t", tno);
                }
                break;

            case OP_JMP:{
                    // operand is a Value index
                    VarIdx idx;
                    READ_VM_OBJ(VarIdx, idx);
                    fprintf(outf, "<%d>\t", idx);
                    printVal(getVar(&vm->vstore, idx));
                }
                break;

            case OP_JMPI:{
                    // operand is an immediate Value
                    Value val;
                    READ_VM_OBJ(Value, val);
                    printVal(val);
                }
                break;

            case OP_JMPR:{
                    // operand is a single register
                    RegNumType reg;
                    READ_VM_OBJ(RegNumType, reg);
                    fprintf(outf, "<%s>\t", regToStr(reg));
                    printVal(vm->registers[reg]);
                }
                break;

            case OP_RJMP:{
                    // operand is a Value index
                    VarIdx idx;
                    READ_VM_OBJ(VarIdx, idx);
                    fprintf(outf, "<%d>\t", idx);
                    printVal(getVar(&vm->vstore, idx));
                }
                break;

            case OP_RJMPI:{
                    // operand is an immediate Value
                    Value val;
                    READ_VM_OBJ(Value, val);
                    printVal(val);
                }
                break;

            case OP_RJMPR:{
                    // operand is a single register
                    RegNumType reg;
                    READ_VM_OBJ(RegNumType, reg);
                    fprintf(outf, "<%s>\t", regToStr(reg));
                    printVal(vm->registers[reg]);
                }
                break;

            case OP_BR:{
                    // operand is a Value Index
                    VarIdx idx;
                    READ_VM_OBJ(VarIdx, idx);
                    fprintf(outf, "<%d>\t", idx);
                    printVal(getVar(&vm->vstore, idx));
                }
                break;

            case OP_BRI: {
                    // operand is an immediate Value
                    Value val;
                    READ_VM_OBJ(Value, val);
                    printVal(val);
                }
                break;

            case OP_BRR: {
                    // operand is a single register
                    RegNumType reg;
                    READ_VM_OBJ(RegNumType, reg);
                    fprintf(outf, "<%s>\t", regToStr(reg));
                    printVal(vm->registers[reg]);
                }
                break;

            case OP_RBR: {
                    // operand is a Value index
                    VarIdx idx;
                    READ_VM_OBJ(VarIdx, idx);
                    fprintf(outf, "<%d>\t", idx);
                    printVal(getVar(&vm->vstore, idx));
                }
                break;

            case OP_RBRI: {
                    // operand is an immediate Value
                    Value val;
                    READ_VM_OBJ(Value, val);
                    printVal(val);
                }
                break;

            case OP_RBRR: {
                    // operand is a single register
                    RegNumType reg;
                    READ_VM_OBJ(RegNumType, reg);
                    fprintf(outf, "<%s>\t", regToStr(reg));
                    printVal(vm->registers[reg]);
                }
                break;

            case OP_PUSH: {
                    // operand is a Value index
                    VarIdx idx;
                    READ_VM_OBJ(VarIdx, idx);
                    fprintf(outf, "<%d>\t", idx);
                    printVal(getVar(&vm->vstore, idx));
                }
                break;

            case OP_PUSHI: {
                    // operand is an immediate Value
                    Value val;
                    READ_VM_OBJ(Value, val);
                    printVal(val);
                }
                break;

            case OP_PUSHR: {
                    // operand is a single register
                    RegNumType reg;
                    READ_VM_OBJ(RegNumType, reg);
                    fprintf(outf, "<%s>\t", regToStr(reg));
                    printVal(vm->registers[reg]);
                }
                break;

            case OP_POP: {
                    // operand is a single register
                    uint8_t reg;
                    READ_VM_OBJ(uint8_t, reg);
                    fprintf(outf, "<%s>\t", regToStr(reg));
                }
                break;

            case OP_PEEK: {
                    // operand is a single register
// TODO: operand is an immediate Value
                    RegNumType reg;
                    READ_VM_OBJ(RegNumType, reg);
                    fprintf(outf, "<%s>\t", regToStr(reg));
                    printVal(vm->registers[reg]);
                }
                break;

            case OP_LOAD: {
                    // operand is a single register
                    // operand is a Value index
                    RegNumType reg;
                    READ_VM_OBJ(RegNumType, reg);
                    fprintf(outf, "<%s> ", regToStr(reg));
                    printVal(vm->registers[reg]);
                    VarIdx idx;
                    READ_VM_OBJ(VarIdx, idx);
                    fprintf(outf, ", <%d>\t", idx);
                    printVal(getVar(&vm->vstore, idx));
                }
                break;

            case OP_LOADI: {
                    // operand is a single register
                    // operand is an immediate Value
                    RegNumType reg;
                    READ_VM_OBJ(RegNumType, reg);
                    fprintf(outf, "<%s> ", regToStr(reg));
                    printVal(vm->registers[reg]);
                    Value val;
                    READ_VM_OBJ(Value, val);
                    printVal(val);
                }
                break;

            case OP_LOADR: {
                    // operand is 2 registers
                    RegNumType regs;
                    READ_VM_OBJ(RegNumType, regs);
                    fprintf(outf, "<%s> ", regToStr((regs >> 4) & 0xF));
                    printVal(vm->registers[regs]);
                    fprintf(outf, ", <%s>", regToStr(regs & 0xF));
                    printVal(vm->registers[regs]);
                    fprintf(outf, "\t");
                }
                break;

            case OP_STORE: {
                    // operand is a Value index
                    // operand is a single register
                    VarIdx idx;
                    READ_VM_OBJ(VarIdx, idx);
                    fprintf(outf, "<%d>\t", idx);
                    printVal(getVar(&vm->vstore, idx));
                    RegNumType reg;
                    READ_VM_OBJ(RegNumType, reg);
                    fprintf(outf, "<%s>\t", regToStr(reg));
                    printVal(vm->registers[reg]);
                }
                break;

            case OP_NOT: {
                    // operand is single register (result in zero flag)
                    RegNumType reg;
                    READ_VM_OBJ(RegNumType, reg);
                    fprintf(outf, "<%s>\t", regToStr(reg));
                    printVal(vm->registers[reg]);
                }
                break;

            case OP_EQ: {
                    // operand is 2 registers (result in zero flag)
                    RegNumType regs;
                    READ_VM_OBJ(RegNumType, regs);
                    fprintf(outf, "<%s> ", regToStr((regs >> 4) & 0xF));
                    printVal(vm->registers[regs]);
                    fprintf(outf, ", <%s>", regToStr(regs & 0xF));
                    printVal(vm->registers[regs]);
                    fprintf(outf, "\t");
                }
                break;

            case OP_NEQ: {
                    // operand is 2 registers (result in zero flag)
                    RegNumType regs;
                    READ_VM_OBJ(RegNumType, regs);
                    fprintf(outf, "<%s> ", regToStr((regs >> 4) & 0xF));
                    printVal(vm->registers[regs]);
                    fprintf(outf, ", <%s>", regToStr(regs & 0xF));
                    printVal(vm->registers[regs]);
                    fprintf(outf, "\t");
                }
                break;

            case OP_LEQ: {
                    // operand is 2 registers (result in zero flag)
                    RegNumType regs;
                    READ_VM_OBJ(RegNumType, regs);
                    fprintf(outf, "<%s> ", regToStr((regs >> 4) & 0xF));
                    printVal(vm->registers[regs]);
                    fprintf(outf, ", <%s>", regToStr(regs & 0xF));
                    printVal(vm->registers[regs]);
                    fprintf(outf, "\t");
                }
                break;

            case OP_GEQ: {
                    // operand is 2 registers (result in zero flag)
                    RegNumType regs;
                    READ_VM_OBJ(RegNumType, regs);
                    fprintf(outf, "<%s> ", regToStr((regs >> 4) & 0xF));
                    printVal(vm->registers[regs]);
                    fprintf(outf, ", <%s>", regToStr(regs & 0xF));
                    printVal(vm->registers[regs]);
                    fprintf(outf, "\t");
                }
                break;

            case OP_LESS: {
                    // operand is 2 registers (result in zero flag)
                    RegNumType regs;
                    READ_VM_OBJ(RegNumType, regs);
                    fprintf(outf, "<%s> ", regToStr((regs >> 4) & 0xF));
                    printVal(vm->registers[regs]);
                    fprintf(outf, ", <%s>", regToStr(regs & 0xF));
                    printVal(vm->registers[regs]);
                    fprintf(outf, "\t");
                }
                break;

            case OP_GTR: {
                    // operand is 2 registers (result in zero flag)
                    RegNumType regs;
                    READ_VM_OBJ(RegNumType, regs);
                    fprintf(outf, "<%s> ", regToStr((regs >> 4) & 0xF));
                    printVal(vm->registers[regs]);
                    fprintf(outf, ", <%s>", regToStr(regs & 0xF));
                    printVal(vm->registers[regs]);
                    fprintf(outf, "\t");
                }
                break;

            case OP_NEG: {
                    // operand is 2 registers
                    RegNumType regs;
                    READ_VM_OBJ(RegNumType, regs);
                    fprintf(outf, "<%s> ", regToStr((regs >> 4) & 0xF));
                    printVal(vm->registers[regs]);
                    fprintf(outf, ", <%s>", regToStr(regs & 0xF));
                    printVal(vm->registers[regs]);
                    fprintf(outf, "\t");
                }
                break;

            case OP_ADD: {
                    // operand is 3 registers
                    uint16_t regs;
                    READ_VM_OBJ(uint16_t, regs);
                    fprintf(outf, "<%s> ", regToStr((regs >> 8) & 0xF));
                    printVal(vm->registers[regs]);
                    fprintf(outf, ", <%s>", regToStr((regs >> 4) & 0xF));
                    printVal(vm->registers[regs]);
                    fprintf(outf, ", <%s>", regToStr(regs & 0xF));
                    printVal(vm->registers[regs]);
                    fprintf(outf, "\t");
                }
                break;

            case OP_SUB: {
                    // operand is 3 registers
                    uint16_t regs;
                    READ_VM_OBJ(uint16_t, regs);
                    fprintf(outf, "<%s> ", regToStr((regs >> 8) & 0xF));
                    printVal(vm->registers[regs]);
                    fprintf(outf, ", <%s>", regToStr((regs >> 4) & 0xF));
                    printVal(vm->registers[regs]);
                    fprintf(outf, ", <%s>", regToStr(regs & 0xF));
                    printVal(vm->registers[regs]);
                    fprintf(outf, "\t");
                }
                break;

            case OP_MUL: {
                    // operand is 3 registers
                    uint16_t regs;
                    READ_VM_OBJ(uint16_t, regs);
                    fprintf(outf, "<%s> ", regToStr((regs >> 8) & 0xF));
                    printVal(vm->registers[regs]);
                    fprintf(outf, ", <%s>", regToStr((regs >> 4) & 0xF));
                    printVal(vm->registers[regs]);
                    fprintf(outf, ", <%s>", regToStr(regs & 0xF));
                    printVal(vm->registers[regs]);
                    fprintf(outf, "\t");
                }
                break;

            case OP_DIV: {
                    // operand is 3 registers
                    uint16_t regs;
                    READ_VM_OBJ(uint16_t, regs);
                    fprintf(outf, "<%s> ", regToStr((regs >> 8) & 0xF));
                    printVal(vm->registers[regs]);
                    fprintf(outf, ", <%s>", regToStr((regs >> 4) & 0xF));
                    printVal(vm->registers[regs]);
                    fprintf(outf, ", <%s>", regToStr(regs & 0xF));
                    printVal(vm->registers[regs]);
                    fprintf(outf, "\t");
                }
                break;

            case OP_MOD: {
                    // operand is 3 registers
                    uint16_t regs;
                    READ_VM_OBJ(uint16_t, regs);
                    fprintf(outf, "<%s> ", regToStr((regs >> 8) & 0xF));
                    printVal(vm->registers[regs]);
                    fprintf(outf, ", <%s>", regToStr((regs >> 4) & 0xF));
                    printVal(vm->registers[regs]);
                    fprintf(outf, ", <%s>", regToStr(regs & 0xF));
                    printVal(vm->registers[regs]);
                    fprintf(outf, "\t");
                }
                break;

            default:
                fatalError("unknown instruction: 0x%02X\n", op);
                return;
        }
        fprintf(outf, "\n");
        finished = isInstrEnded(&vm->istore);
    }
}