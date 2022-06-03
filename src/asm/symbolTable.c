
#include "system.h"
#include "memory.h"
#include "varStore.h"
#include "vMachine.h"
#include "errors.h"

extern VM* vm;

typedef struct _symtab_elem {
    const char* key;
    VarIdx idx;
    struct _symtab_elem* left;
    struct _symtab_elem* right;
} SymTabNode;

typedef struct _context {
    const char* name;
    struct _context* next;
} Context;

static SymTabNode* symtab = NULL;
static Context* context = NULL;

static char name_buffer[1024*64];
static void build_name(Context* cont, const char* name)
{
    if(cont != NULL) {
        strcat(name_buffer, cont->name);
        strcat(name_buffer, ".");
        build_name(cont->next, name);
    }
    else {
        strcat(name_buffer, name);
    }
}

static const char* create_name(const char* name)
{
    memset(name_buffer, 0, sizeof(name_buffer));
    name_buffer[0] = '.';
    build_name(context, name);

    return name_buffer;
}

// left is always the value that is being searched for
static int comp_names(const char* left, const char* right)
{
    int llen = strlen(left);
    int rlen = strlen(right);

    while(left[llen--] == right[rlen--]) {
        if(llen == 0)
            return 0;   // match
    }

    return left[llen] - right[rlen];
}

static void free_table(SymTabNode* node)
{
    if(node->left != NULL)
        free_table(node->left);
    if(node->right != NULL)
        free_table(node->right);

    _free((void*)node->key);
    _free(node);
}

static void dump_table(SymTabNode* node)
{
    if(node->left != NULL)
        dump_table(node->left);
    if(node->right != NULL)
        dump_table(node->right);

    printf("    %s <%d> ", node->key, node->idx);
    printVal(getVar(&vm->vstore, node->idx));
    printf("\n");
}

static void add_node(SymTabNode* tree, SymTabNode* node)
{
    int x = strcmp(tree->key, node->key);
    if(x > 0) {
        if(tree->right != NULL)
            add_node(tree->right, node);
        else {
            tree->right = node;
            return;
        }
    }
    else if(x < 0) {
        if(tree->left != NULL)
            add_node(tree->left, node);
        else {
            tree->left = node;
            return;
        }
    }
    else {
        syntaxError("symbol \"%s\" is already defined", node->key);
        _free((void*)node->key);
        _free(node);
        return;
    }
}

static SymTabNode* find_node(SymTabNode* node, const char* key)
{
    int x = strcmp(node->key, key);
    if(x > 0) {
        if(node->right != NULL)
            return find_node(node->right, key);
        else
            return NULL;
    }
    else if(x < 0) {
        if(node->left != NULL)
            return find_node(node->left, key);
        else
            return NULL;
    }
    else
        return node;
}

/*************************************************************
 * Interface
 */

void destroySymTab()
{
    free_table(symtab);

    Context *crnt, *next;
    for(crnt = context; crnt != NULL; crnt = next) {
        next = crnt->next;
        _free((void*)crnt->name);
        _free(crnt);
    }
}

// symbol definition
void addSym(const char* key, VarIdx idx)
{
    SymTabNode* node = _alloc_ds(SymTabNode);
    node->key = _alloc_str(create_name(key));
    node->idx = idx;

    if(symtab != NULL)
        add_node(symtab, node);
    else
        symtab = node;
}

// symbol reference
VarIdx symToIdx(const char* key)
{
    SymTabNode* node = find_node(symtab, key);

    if(node != NULL)
        return node->idx;
    else
        return 0;   // error Var
}

// symbol reference
Value symToVal(const char*key)
{
    SymTabNode* node = find_node(symtab, key);
    Value val;

    if(node != NULL)
        val = getVar(&vm->vstore, node->idx);
    else {
        memset(&val, 0, sizeof(Value));
        val.type = ERROR;
    }

    return val;
}

void dumpSymtab()
{
    printf("Dump Symbol Table\n");
    dump_table(symtab);
    printf("----------- end dump -----------\n");
}

void pushContext(const char* name)
{
    Context* cont;

    cont->name = _alloc_str(name);
    cont->next = context;
    context = cont;
}

void popContext()
{
    Context* cont = context;

    if(cont != NULL) {
        context = cont->next;
        _free((void*)cont->name);
        _free(cont);
    }
}
