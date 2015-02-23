#ifndef HASHCASH_H
#define HASHCASH_H

typedef char* (*difficult_problem)(int);
//Solve hashcash takes an int for difficulty, solves a problem defined by function pointer
char* solvehashcash(difficult_problem, int);
char* diff_problem_sample(int difficulty);

#endif
