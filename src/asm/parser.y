/*
 * This is the complete grammar for the NOP programming language.
 */

%debug
%defines
%locations

%{

#include "system.h"
#include <stdarg.h>
#include "vMachine.h"

#include "values.h"
#include "symbolTable.h"
#include "opcodes.h"
#include "registers.h"
#include "scanner.h"

// defined by flex
extern int yylex(void);
extern int yyparse(void);
extern FILE *yyin;
void yyerror(const char* s)
{
    fprintf(stderr, "%s\n", s);
}

// defined in main.c
//extern Symbol* sym_table;
extern int error_count;
void syntaxError(const char*, ...);
extern VM* vm;

%}

%define parse.error verbose
%locations

%union {
    Value literal;
    int opcode;
    int type;
    int reg;
    char* symbol;
    char* str;
};

%token <symbol> TOK_SYMBOL
%token <literal> TOK_UNUM
%token <literal> TOK_INUM
%token <literal> TOK_FNUM
%token <literal> TOK_STR
%token <literal> TOK_TRUE TOK_FALSE
%type <literal> expression expression_factor expr_parameter

%token <type> TOK_UINT8 TOK_UINT16 TOK_UINT32 TOK_UINT64
%token <type> TOK_INT8 TOK_INT16 TOK_INT32 TOK_INT64 TOK_FLOAT TOK_DOUBLE
%token <type> TOK_ADDR TOK_LIST TOK_DICT TOK_STRING TOK_BOOL

%token <opcode> TOK_ABORT TOK_EXIT TOK_NOP TOK_CALL TOK_RCALL TOK_TRAP
%token <opcode> TOK_RETURN TOK_JMP TOK_RJMP TOK_BR TOK_RBR
%token <opcode> TOK_PUSH TOK_POP TOK_LOAD TOK_DIV TOK_MOD
%token <opcode> TOK_STORE TOK_NOT TOK_EQ TOK_NEQ TOK_LEQ
%token <opcode> TOK_GEQ TOK_LESS TOK_GTR TOK_NEG TOK_ADD TOK_SUB TOK_MUL

%token <reg> TOK_R0 TOK_R1 TOK_R2 TOK_R3 TOK_R4 TOK_R5 TOK_R6 TOK_R7
%token <reg> TOK_R8 TOK_R9 TOK_R10 TOK_R11 TOK_R12 TOK_R13 TOK_R14 TOK_R15
%type <reg> register

%token TOK_NAMESPACE TOK_CONST

%right '='
%left '+' '-'
%left '*' '/' '%'
%left NEGATE

%%
program
    :  {
        // Emit stuff at the beginning of the file.
    } module
    ;

module
    : module_item_list {
        // Emit stuff at the end of the file.
    }
    ;

module_item_list
    : module_item
    | module_item_list module_item
    ;

module_item
    : namespace_definition
    | instruction_block
    | data_definition
    ;

namespace_definition
    : TOK_NAMESPACE TOK_SYMBOL '{' {
        pushContext($2);
    } module_item_list '}' {
        popContext();
    }

instruction_block
    : TOK_SYMBOL {
        /* define an address var */
        Value val;
        val.type = ADDRESS;
        val.data.addr = getInstrLen(&vm->istore);
        addVar(&vm->vstore, val);
    } instruction_list
    ;

instruction_list
    : instruction
    | instruction_list instruction
    ;

instruction
    : TOK_EXIT { WRITE_VM_OBJ(uint8_t, OP_EXIT); }
    | TOK_RETURN { WRITE_VM_OBJ(uint8_t, OP_RETURN); }
    | TOK_NOP { WRITE_VM_OBJ(uint8_t, OP_NOP); }
    | class1_instr
    | class2_instr
    | class3_instr
    | class4_instr
    | class5_instr
    | class6_instr
    | class7_instr
    | class8_instr
    ;

register
    : TOK_R0
    | TOK_R1
    | TOK_R2
    | TOK_R3
    | TOK_R4
    | TOK_R5
    | TOK_R6
    | TOK_R7
    | TOK_R8
    | TOK_R9
    | TOK_R10
    | TOK_R11
    | TOK_R12
    | TOK_R13
    | TOK_R14
    | TOK_R15
    ;

    /* binary arithmetic into register */
class1_instr
    : TOK_ADD register ',' register ',' register {
        WRITE_VM_OBJ(uint8_t, OP_ADD);
        WRITE_VM_OBJ(uint16_t, (($2 & 0x0F) << 8)|(($4 & 0xF) << 4)|($6 & 0xF));
    }
    | TOK_SUB register ',' register ',' register {
        WRITE_VM_OBJ(uint8_t, OP_SUB);
        WRITE_VM_OBJ(uint16_t, (($2 & 0x0F) << 8)|(($4 & 0xF) << 4)|($6 & 0xF));
    }
    | TOK_MUL register ',' register ',' register {
        WRITE_VM_OBJ(uint8_t, OP_MUL);
        WRITE_VM_OBJ(uint16_t, (($2 & 0x0F) << 8)|(($4 & 0xF) << 4)|($6 & 0xF));
    }
    | TOK_DIV register ',' register ',' register {
        WRITE_VM_OBJ(uint8_t, OP_DIV);
        WRITE_VM_OBJ(uint16_t, (($2 & 0x0F) << 8)|(($4 & 0xF) << 4)|($6 & 0xF));
    }
    | TOK_MOD register ',' register ',' register {
        WRITE_VM_OBJ(uint8_t, OP_MOD);
        WRITE_VM_OBJ(uint16_t, (($2 & 0x0F) << 8)|(($4 & 0xF) << 4)|($6 & 0xF));
    }
    ;

    /* binary compare into zero flag */
class2_instr
    : TOK_NEG register ',' register {
        WRITE_VM_OBJ(uint8_t, OP_NEG);
        WRITE_VM_OBJ(uint8_t, (($2 & 0xF) << 4)|($4 & 0xF));
    }
    | TOK_EQ register ',' register {
        WRITE_VM_OBJ(uint8_t, OP_EQ);
        WRITE_VM_OBJ(uint8_t, (($2 & 0xF) << 4)|($4 & 0xF));
    }
    | TOK_NEQ register ',' register {
        WRITE_VM_OBJ(uint8_t, OP_NEQ);
        WRITE_VM_OBJ(uint8_t, (($2 & 0xF) << 4)|($4 & 0xF));
    }
    | TOK_LEQ register ',' register {
        WRITE_VM_OBJ(uint8_t, OP_LEQ);
        WRITE_VM_OBJ(uint8_t, (($2 & 0xF) << 4)|($4 & 0xF));
    }
    | TOK_GEQ register ',' register {
        WRITE_VM_OBJ(uint8_t, OP_GEQ);
        WRITE_VM_OBJ(uint8_t, (($2 & 0xF) << 4)|($4 & 0xF));
    }
    | TOK_LESS register ',' register {
        WRITE_VM_OBJ(uint8_t, OP_LESS);
        WRITE_VM_OBJ(uint8_t, (($2 & 0xF) << 4)|($4 & 0xF));
    }
    | TOK_GTR register ',' register {
        WRITE_VM_OBJ(uint8_t, OP_GTR);
        WRITE_VM_OBJ(uint8_t, (($2 & 0xF) << 4)|($4 & 0xF));
    }
    ;

    /* one register parm */
class3_instr
    : TOK_NOT register {
        WRITE_VM_OBJ(uint8_t, OP_NOT);
        WRITE_VM_OBJ(uint8_t, ($2 & 0xF));
    }
    | TOK_POP register {
        WRITE_VM_OBJ(uint8_t, OP_POP);
        WRITE_VM_OBJ(uint8_t, ($2 & 0xF));
    }
    ;


    /* Register parameter that must contain an address or an offset */
class4_instr
    : TOK_ABORT register {
        WRITE_VM_OBJ(uint8_t, OP_ABORTR);
        WRITE_VM_OBJ(uint8_t, ($2 & 0xF));
    }
    | TOK_CALL register {
        WRITE_VM_OBJ(uint8_t, OP_CALLR);
        WRITE_VM_OBJ(uint8_t, ($2 & 0xF));
    }
    | TOK_RCALL register {
        WRITE_VM_OBJ(uint8_t, OP_RCALLR);
        WRITE_VM_OBJ(uint8_t, ($2 & 0xF));
    }
    | TOK_JMP register {
        WRITE_VM_OBJ(uint8_t, OP_JMPR);
        WRITE_VM_OBJ(uint8_t, ($2 & 0xF));
    }
    | TOK_RJMP register {
        WRITE_VM_OBJ(uint8_t, OP_RJMPR);
        WRITE_VM_OBJ(uint8_t, ($2 & 0xF));
    }
    | TOK_BR register {
        WRITE_VM_OBJ(uint8_t, OP_BRR);
        WRITE_VM_OBJ(uint8_t, ($2 & 0xF));
    }
    | TOK_RBR register {
        WRITE_VM_OBJ(uint8_t, OP_RBRR);
        WRITE_VM_OBJ(uint8_t, ($2 & 0xF));
    }
    | TOK_PUSH register {
        WRITE_VM_OBJ(uint8_t, OP_PUSHR);
        WRITE_VM_OBJ(uint8_t, ($2 & 0xF));
    }
    ;

    /* references an operand from the varStore */
class5_instr
    : TOK_ABORT TOK_SYMBOL {}
    | TOK_CALL TOK_SYMBOL {}
    | TOK_RCALL TOK_SYMBOL {}
    | TOK_JMP TOK_SYMBOL {}
    | TOK_RJMP TOK_SYMBOL {}
    | TOK_BR TOK_SYMBOL {}
    | TOK_RBR TOK_SYMBOL {}
    | TOK_PUSH TOK_SYMBOL {}
    ;

    /* If there is no type coersion, then just take the largest one. */
expr_parameter
    : expression {}
    | '(' type_name ')' expression {}
    ;

    /* literal value parameter that must have an address or an address offset */
class6_instr
    : TOK_ABORT expr_parameter {}
    | TOK_CALL expr_parameter {}
    | TOK_RCALL expr_parameter {}
    | TOK_JMP expr_parameter {}
    | TOK_RJMP expr_parameter {}
    | TOK_BR expr_parameter {}
    | TOK_RBR expr_parameter {}
    | TOK_PUSH expr_parameter {}
    ;

    /* Numeric literal as parameter */
class7_instr
    : TOK_TRAP TOK_UNUM {}
    | TOK_TRAP TOK_INUM {}
    ;

    /* moving data in and out of registers */
class8_instr
    : TOK_LOAD register ',' register {}
    | TOK_LOAD register ',' TOK_SYMBOL {}
    | TOK_LOAD register ',' expr_parameter {}
    | TOK_STORE TOK_SYMBOL ',' register {
        WRITE_VM_OBJ(uint8_t, OP_STORE);
// symbol reference
        WRITE_VM_OBJ(uint8_t, ($4 & 0xF));
    }
    ;

type_name
    : TOK_INT8 {}
    | TOK_INT16 {}
    | TOK_INT32 {}
    | TOK_INT64 {}
    | TOK_UINT8 {}
    | TOK_UINT16 {}
    | TOK_UINT32 {}
    | TOK_UINT64 {}
    | TOK_FLOAT {}
    | TOK_DOUBLE {}
    | TOK_BOOL {}
    | TOK_STRING {}
    | TOK_LIST {}
    | TOK_DICT {}
    | TOK_ADDR {}
    ;

type_specifier
    : TOK_CONST type_name {}
    | type_name {}
    ;

data_declaration
    : type_specifier TOK_SYMBOL {}
    ;

data_definition
    : data_declaration '=' expression {}
    | data_declaration '=' bool_value {}
    ;

bool_value
    : TOK_TRUE {}
    | TOK_FALSE {}
    ;

expression_factor
    : TOK_UNUM {}
    | TOK_INUM {}
    | TOK_FNUM {}
    | TOK_STR {}
    ;

expression
    : expression_factor
    | expression '+' expression { }
    | expression '-' expression { }
    | expression '*' expression { }
    | expression '/' expression { }
    | expression '%' expression { }
    | '-' expression %prec NEGATE { }
    | '(' expression ')' { }
    ;

%%
