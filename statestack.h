#pragma once
// Statestack.h contains the definition of a game state stack singleton.
// There can only ever be one state stack in the game, which is initialized here and accessible throughout
// the entire program.
// The state stack is basically a std::stack containing function pointers. The functions that the state stack points to should
// be in main.cpp, and are pushed on during initialization.
//
// Since the state stack is available everywhere in the program, any function may push or pop states to and from the stack:
// this allows the user to say, pause the game and then quit - pushing a Pause state on, and then popping all the states off until it is empty.

#include <stack>

// The STL stack can't take a function pointer as a data type, but
// I can make a struct which contains the function pointer.

struct State
{
    void (*StatePointer)();
};

class StateStack
{
public:
    static StateStack& Instance()
    {
        static StateStack singleton;
        return singleton;
    }

    // Actual stack of function pointers
    std::stack<State> states;


private:
    //Singletons have a private constructor to prevent more than one instance.
    StateStack() {};
    StateStack(const StateStack&);             // Prevent Copying;
    StateStack& operator=(const StateStack&); // Prevent Assignment
};

// Initializing Singleton
static StateStack* g_StateStack = &StateStack::Instance();

