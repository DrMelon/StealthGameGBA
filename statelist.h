#pragma once

#include "statestack.h" // Game State Stack - basically for handling game states.

// List of Game State Functions are included here so that the individual states themselves may access the master list of states:
// this lets Menu push Game onto the stack for example.

void Menu();
void Game();
void Pause();
