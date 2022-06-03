
%{
//#undef //_DEBUGGING
//#undef //_TRACE
//#define //_TRACE(...)

#include "system.h"
//#include "vm_support.h"
#include "values.h"
#include "parser.h"
#include "scanner.h"
#include "opcodes.h"
#include "registers.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"

void yyerror(const char* s);

int bidx = 0;
char buffer[1024*64];

static void __append_char(char ch)
{
// TODO: bounds checking
    buffer[bidx] = ch;
    bidx++;
}

static void __append_str(const char* str)
{
// TODO: bounds checking
    strcpy(&buffer[bidx], str);
    bidx += strlen(str);
}

%}

/* state definitions */
%x SQUOTES
%x DQUOTES
%option noinput nounput
%option yylineno
%option noyywrap
%%

    /* overhead */
\n              { yylineno++; }
[ \t\r]         {}

    /* keywords */
"UINT8"         { yylval.type = UINT8; return TOK_UINT8; }
"UINT16"        { yylval.type = UINT16; return TOK_UINT16; }
"UINT32"        { yylval.type = UINT32; return TOK_UINT32; }
"UINT64"        { yylval.type = UINT64; return TOK_UINT64; }
"INT8"          { yylval.type = INT8; return TOK_INT8; }
"INT16"         { yylval.type = INT16; return TOK_INT16; }
"INT32"         { yylval.type = INT32; return TOK_INT32; }
"INT64"         { yylval.type = INT64; return TOK_INT64; }
"FLOAT"         { yylval.type = FLOAT; return TOK_FLOAT; }
"DOUBLE"        { yylval.type = DOUBLE; return TOK_DOUBLE; }
"ADDRESS"       { yylval.type = ADDRESS; return TOK_ADDR; }
"LIST"          { yylval.type = LIST; return TOK_LIST; }
"DICT"          { yylval.type = DICT; return TOK_DICT; }
"STRING"        { yylval.type = STRING; return TOK_STRING; }
"BOOL"          { yylval.type = BOOL; return TOK_BOOL; }

"TRUE"          { yylval.literal.type = BOOL; yylval.literal.data.boolean = true; return TOK_TRUE; }
"FALSE"         { yylval.literal.type = BOOL; yylval.literal.data.boolean = false; return TOK_FALSE; }

"ABORT"         { yylval.opcode = OP_ABORT; return TOK_ABORT; }
"EXIT"          { yylval.opcode = OP_EXIT; return TOK_EXIT; }
"NOP"           { yylval.opcode = OP_NOP; return TOK_NOP; }
"CALL"          { yylval.opcode = OP_CALL; return TOK_CALL; }
"RCALL"         { yylval.opcode = OP_RCALL; return TOK_RCALL; }
"TRAP"          { yylval.opcode = OP_TRAP; return TOK_TRAP; }
"RETURN"        { yylval.opcode = OP_RETURN; return TOK_RETURN; }
"JMP"           { yylval.opcode = OP_JMP; return TOK_JMP; }
"RJMP"          { yylval.opcode = OP_RJMP; return TOK_RJMP; }
"BR"            { yylval.opcode = OP_BR; return TOK_BR; }
"RBR"           { yylval.opcode = OP_RBR; return TOK_RBR; }
"PUSH"          { yylval.opcode = OP_PUSH; return TOK_PUSH; }
"POP"           { yylval.opcode = OP_POP; return TOK_POP; }
    /* "PEEK"          { yylval.opcode = OP_PEEK; return TOK_PEEK; } */
"LOAD"          { yylval.opcode = OP_LOAD; return TOK_LOAD; }
"STORE"         { yylval.opcode = OP_STORE; return TOK_STORE; }
"NOT"           { yylval.opcode = OP_NOT; return TOK_NOT; }
"EQ"            { yylval.opcode = OP_EQ; return TOK_EQ; }
"NEQ"           { yylval.opcode = OP_NEQ; return TOK_NEQ; }
"LEQ"           { yylval.opcode = OP_LEQ; return TOK_LEQ; }
"GEQ"           { yylval.opcode = OP_GEQ; return TOK_GEQ; }
"LESS"          { yylval.opcode = OP_LESS; return TOK_LESS; }
"GTR"           { yylval.opcode = OP_GTR; return TOK_GTR; }
"NEG"           { yylval.opcode = OP_NEG; return TOK_NEG; }
"ADD"           { yylval.opcode = OP_ADD; return TOK_ADD; }
"SUB"           { yylval.opcode = OP_SUB; return TOK_SUB; }
"MUL"           { yylval.opcode = OP_MUL; return TOK_MUL; }
"DIV"           { yylval.opcode = OP_DIV; return TOK_DIV; }
"MOD"           { yylval.opcode = OP_MOD; return TOK_MOD; }

"R0"            { yylval.reg = REG_0; return TOK_R0; }
"R1"            { yylval.reg = REG_1; return TOK_R1; }
"R2"            { yylval.reg = REG_2; return TOK_R2; }
"R3"            { yylval.reg = REG_3; return TOK_R3; }
"R4"            { yylval.reg = REG_4; return TOK_R4; }
"R5"            { yylval.reg = REG_5; return TOK_R5; }
"R6"            { yylval.reg = REG_6; return TOK_R6; }
"R7"            { yylval.reg = REG_7; return TOK_R7; }
"R8"            { yylval.reg = REG_8; return TOK_R8; }
"R9"            { yylval.reg = REG_9; return TOK_R9; }
"R10"           { yylval.reg = REG_10; return TOK_R10; }
"R11"           { yylval.reg = REG_11; return TOK_R11; }
"R12"           { yylval.reg = REG_12; return TOK_R12; }
"R13"           { yylval.reg = REG_13; return TOK_R13; }
"R14"           { yylval.reg = REG_14; return TOK_R14; }
"R15"           { yylval.reg = REG_15; return TOK_R15; }

"CONST"         { return TOK_CONST; }
"NAMESPACE"     { return TOK_NAMESPACE; }

        /* arithmetic operators */
"+"             { return '+'; }
"-"             { return '-'; }
"="             { return '='; }
"/"             { return '/'; }
"*"             { return '*'; }
"%"             { return '%'; }
"("             { return '('; }
")"             { return ')'; }
"#"             { return '#'; }
"{"             { return '{'; }
"}"             { return '}'; }
","             { return ','; }

    /* constructed tokens */

    /* A simple symbol */
[a-zA-Z_][a-zA-Z_0-9]* {
        yylval.symbol = (char*)strdup(yytext);
        //printf("SYMBOL: %s\n", yytext);
        return TOK_SYMBOL;
    }

[0-9]+ {
        yylval.literal.data.snum64 = strtol(yytext, NULL, 10);
        yylval.literal.type = INT64;
        return TOK_INUM;
    }

    /* recognize a float */
([0-9]*\.)?[0-9]+([Ee][-+]?[0-9]+)? {
        yylval.literal.data.dnum = strtod(yytext, NULL);
        yylval.literal.type = DOUBLE;
        //printf("number: %0.3f\n", yylval.fnum);
        return TOK_FNUM;
    }

0[Xx][0-9a-fA-F]+ {
        yylval.literal.data.unum64 = strtol(yytext, NULL, 16);
        yylval.literal.type = UINT64;
        return TOK_UNUM;
    }

    /* double quoted strings have escapes managed */
\"  {
        bidx = 0;
        memset(buffer, 0, sizeof(buffer));
        BEGIN(DQUOTES);
    }

<DQUOTES>\" {
        //yylval.literal.str = STRDUP(buffer);
        yylval.str = (char*)strdup(buffer);
        BEGIN(INITIAL);
        return TOK_STRING;
    }

    /* the short rule matches before the long one does */
<DQUOTES>\\n    { __append_char('\n'); }
<DQUOTES>\\r    { __append_char('\r'); }
<DQUOTES>\\e    { __append_char('\x1b'); }
<DQUOTES>\\t    { __append_char('\t'); }
<DQUOTES>\\b    { __append_char('\b'); }
<DQUOTES>\\f    { __append_char('\f'); }
<DQUOTES>\\v    { __append_char('\v'); }
<DQUOTES>\\\\   { __append_char('\\'); }
<DQUOTES>\\\"   { __append_char('\"'); }
<DQUOTES>\\\'   { __append_char('\''); }
<DQUOTES>\\\?   { __append_char('\?'); }
<DQUOTES>\\.    { __append_char(yytext[1]); }
<DQUOTES>\\[0-7]{1,3} { __append_char((char)strtol(yytext+1, 0, 8));  }
<DQUOTES>\\[xX][0-9a-fA-F]{1,3} { __append_char((char)strtol(yytext+2, 0, 16));  }
<DQUOTES>[^\\\"\n]*  { __append_str(yytext); }
<DQUOTES>\n     { yylineno++; } /* track line numbers, but strip new line */


    /* single quoted strings are absolute literals */
\'  {
        bidx = 0;
        memset(buffer, 0, sizeof(buffer));
        BEGIN(SQUOTES);
    }

<SQUOTES>\' {
        //yylval.literal.str = STRDUP(buffer);
        yylval.str = (char*)strdup(buffer);
        BEGIN(INITIAL);
        return TOK_STRING;
    }

<SQUOTES>[^\\'\n]*  { __append_str(yytext); }
<SQUOTES>\\.    { __append_str(yytext); }
<SQUOTES>\n     { __append_str(yytext); yylineno++; } /* don't strip new lines */

.               { printf("Warning: unrecognized character: %c (0x%02X)", yytext[0], yytext[0]);}


%%

int open_file(const char *fname) {

    yyin = fopen(fname, "r");
    return 0;
}

