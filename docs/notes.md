# Random Notes

How to handle function parameters? The assembler does not know about functions but the compiler above it does. Function parameters can be constants or they can be variables. Constants are embedded in the instruction stream, but variables are in a store and accessed by index. When a CALL is done, the function parameters are supposed to already be on the stack. When the completes, the parameters are popped from the stack. So the function arity and the base pointer in the stack have to be stored. Care has to be taken when modifying function parameters. So the value stack needs to handle random access instead of simple push and pop.

~~When a call is made, the CALL instruction has 2 parameters. The first is a uint8 which gives the call arity. The second is the address of the destination. An address in this context means an index of the fist instruction into the instruction stream. When the CALL is executed, the return address, the arity and the current location into to the call stack is stored.~~

Before a call is made, the parameters are stored in the stack along with the function arity. When the call instruction is executed, the parameters are popped from the stack into an array in the call stack data structure. The last thing that is pushed is the arity and the first thing popped is that. If there are no parameters, then the arity is zero.

Need a way to explicitly access parameters. Also local variables... However, there is really no such thing as a local in this assembly. So, all variables are global. A mechanism is needed to allocate variables in the call stack data structure so that they do not need to be global. THis is partially resolved by using a stack, but that makes it hard to peek and see. Tracking the indexes of locals is not easy. Tracking the index of an array may be easier to think about if not actually do. The normal varStore can be used for that. Possibly, this can be resolved using registers and a stack.

Instead of a call stack, call it a context stack. When name spaces are implemented, then will the idea of a "local" be more important? Or, is a namespace simply a way to separate names?

Should the assembler insert the code to automagically call the program entry point? This allows the first instruction to create an entry in the call stack. Instead of executing an explicit exit instruction, a return with an empty call stack can return from the VM. The name of the entry point should be specified on the command line and have some reasonable default value. Main parameters, etc.

Need to think about how exceptions are to be handled in the VM. This can be partially done with an exception stack. When an exception block is introduced with a try{}, then a data structure is pushed on the stack. When an exception is raised then the stack is popped until a handler is located or the stack is empty. If there is no exception handler encountered, then the program is aborted. This could be a higher level functionality, but I think it needs direct support in the VM.

# TRAPS
~~A TRAP is a pre-defined non-local goto. In the context of this VM a trap is the interface to external code outside of the VM, such as the C stream library. The trap is set up the same as a CALL with the return value on the TOS when it returns. Need to design the mechanism by which this operates. Maybe another type of variable or a user defined type.~~

~~Could make traps a generic function entry point and all traps are defined at compile time. There would be a generic function that receives the trap number and retrieves the parameters from the stack, etc. That would make error handling a bit easier and there would be no need to keep an array of pointers. It would be handled in a separate module that would be built when the VM is built. The source code can be auto generated and placed in the user's code with the C preprocessor.~~

Traps are simply function calls that provide access to external functions. Parameters are stored in registers or on the stack and the function knows how to interface the external call to the parameters.

# NameSpace Context

A namespace is simply a way to ease the problem of duplicate names. When a namespace is entered, a naming context is created and all of the names that are defined in the namespace use the namespace name to access that name outside of the namespace. However, inside the namespace the namespace is not required.

```
namespace name1 {
    test_name
}

namespace name2 {
    test_name
    name1.test_name // different name
}
```

Contexts are integrated into the symbol table. A context has a symbol table the stores the local symbols. When a reference to a symbol that has dots (.) then it is divided into sections and the context is searched for the first segment. If it is found, then the next segment is searched in that context until the final segment is located.

Contexts are stored in a stack and are used to generate the names only. The names are stored as complete paths to the current context and begin with a dot. When a name that was defined outside the current context is referenced, the string of the name is first reversed and then it is checked according to the length of searched key. for example:
```
Searching for the name ".e.f". The name that is specified could be simply "f", but the context specified is "e". the rest of the name is unknown.

The name to be found is ".d.e.f". So when the name is tested, it is truncated to ".e.f" and the full name is returned if it's found.
```
So, the symbol table is separate from the context.

# TODO

-- Switch to a register based scheme. Registers hold values and there are load and store instructions that load and store the varStore. The addresses that the instructions use are the indexes of the registers. Keep the stack based expression manipulation. Load instructions load from the varStore and store instructions store to it. In fact, why keep the stack based expressions? Just use the registers. The stack now become a call stack only. Function parameters are loaded into registers and accessed from there. The register allocation issues can be answered by just having a lot of registers. The call stack will use variables to store the things like the return address. Can still have an expression stack, but use it as a temporary memory area instead of an expression stack. For example, can be used for return values and function parameters. (fewer registers needed)


# Done
-- Need to add variables to instruction streams.