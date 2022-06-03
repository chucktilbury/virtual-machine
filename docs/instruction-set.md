# Instruction Set
This document outlines the actual instruction set that the VM understands. Note that the assembler does not understand all of these because it selects instructions based upon the syntax it encounters while reading the input file.

This document describes the opcodes, the syntax used to invoke them, and the encodings that are to be emitted by the assembler in response to syntax.

## General
These things apply to all instructions except where otherwise noted.
### Format of instructions
All instructions have the format of an instruction name and operands. The operands have specific (and generic) formats.
* Examples:
  * CALL somename
    Make the call using the ADDR value stored in the value "somename".
  * Call (int16)-10
    Make the call encoding the CALLR instruction with a negative offset of 10. The operand is signed, so the jump is relative. If can be positive or negative.
  * CALL 0x1234
    Make the call with unsigned immediate value, which represents an absolute address.
  * ADD R1, R2, R3
    This adds the contents of the registers as R1=R2+R3.
  * LOAD R7, somename
    Take the value stored in the variable "somename" and store it in register R7.
### Format of operands
Operands have a regular format. This refers to the syntax that the assembler recognizes in order to encode the proper instruction. Some instructions are capable of taking a variety of types as operands and others are more restricted. These are noted in the instruction descriptions.
#### Format of register operands
There is a finite number of registers. (16 at the time of this writing) The registers are numbered 0-15 and accessed by name. For example, the name R1 refers to the register numbered as "1".
#### Format of variable operands
Variables are accessed by name in the assembler. Variables that represent an address, such as a label in code, do not need to be defined before they are referenced, but they must be assigned a value before the assembly ends. Other variables must be defined before they are referenced. If a variable is defined but never assigned a value before it is used, then that generates a runtime error.
#### Format of immediate operands
Immediate operands can be any native non-object type.
## Type promotion

## Instructions

### Housekeeping Instructions
These instructions are used to control the virtual machine, rather than to process data.

#### OP_ERROR
This instruction takes to operands. It is used to cause the Virtual machine to exit with an error when the programer determine that the program can no longer continue, but there is no error from the VM's point of view.

* Example:
  * ERROR

#### OP_EXIT
This instruction takes no operands. It is used to terminate the running program normally and return to the operating system.

* Example:
  * EXIT

#### OP_NOP
This instruction is used to take up space in the instruction stream without actually doing anything.

* Example:
  * NOP

### Flow Control
These instructions directly change the instruction pointer in various ways.
#### OP_CALLI
CALLI takes a single immediate Value which must be of type ADDR. When a CALL is executed, it causes a new entry to be placed upon the call stack that contains a copy of the stack index, the return instruction index, and the arity of the call. The arity is the number of function parameters that are expected by the function. Before the CALL is seen, any function parameters mush be pushed upon the Value stack, followed by the function's arity.
#### OP_CALLR
CALLR takes a single immediate Value that must be a signed offset to the current instruction pointer. This is intended to be used in situations where the CALL destination is calculated by the user's program.
#### OP_CALL
CALL is exactly like CALLI and CALLR except that it takes an immediate Value that references a Variable.
#### OP_RETURN
RETURN
#### OP_JMP
#### OP_JMPIF

### Moving Data Instructions
These instructions are used to move data around the various parts of the virtual machine.
#### OP_LOAD
#### OP_LOADI
#### OP_STORE
#### OP_STOREI
#### OP_PUSH
#### OP_PUSHI
#### OP_POP
#### OP_PEEK

### Comparison Instructions
These instructions are used to implement flow logic in a program. They operate on registers. The unary ```NOT``` instruction takes 2 operands, a source and a destination register. The binary instructions take 3 operands. A left, right, and destination. The destination is a new Value that has a boolean type.
#### OP_NOT
#### OP_EQ
#### OP_NEQ
#### OP_LEQ
#### OP_GEQ
#### OP_LESS
#### OP_GTR

### Arithmetic Instructions
These instructions are used to implement arithmetic operations. All of these instructions only operate on registers. The unary ```NEG``` instruction takes 2 operands a source and a destination. Binary operations take 3 operands, a left, right and destination register operand. The destination is a new Value that contains the result of the operation.
#### OP_NEG
#### OP_ADD
#### OP_SUB
#### OP_MUL
#### OP_DIV
#### OP_MOD
