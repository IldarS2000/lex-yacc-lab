#ifndef RECALL_H
#define RECALL_H

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h>
#include <limits.h>
#include "y.tab.h"

extern int debug;

extern int yylex(void);
extern int yyparse(void);
extern void yyerror(char*);

extern void DumpRow(void);
extern int GetNextChar(char* b, int maxBuffer);
extern void NewToken(char*);
extern void PrintError(char* s, ...);

extern int ReduceAdd(int, int, YYLTYPE*);
extern int ReduceSub(int, int, YYLTYPE*);
extern int ReduceMult(int, int, YYLTYPE*);
extern int ReduceDiv(int, int, YYLTYPE*);

typedef struct Variable {
    char* name;
    int value;
} Variable;

extern Variable* VarGet(char*, YYLTYPE*);
extern void VarSetValue(Variable*, int);
extern int VarGetValue(char*, YYLTYPE*);
extern void DumpAllVariables(int errorCount);

#endif
