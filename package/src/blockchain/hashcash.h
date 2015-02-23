#ifndef HASHCASH_H
#define HASHCASH_H

typedef void (*difficult_problem)(int);
//Solve hashcash takes an int for difficulty, solves a problem defined by function pointer
void solvehashcash(difficult_problem, int);
#endif
