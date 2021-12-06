#include "recall.h"

extern int ReduceAdd(int a, int b, YYLTYPE* bloc)
{
    return a + b;
}

extern int ReduceSub(int a, int b, YYLTYPE* bloc)
{
    return a - b;
}

extern int ReduceMult(int a, int b, YYLTYPE* bloc)
{
    return a * b;
}

extern int ReduceDiv(int a, int b, YYLTYPE* bloc)
{
    if (b == 0) {
        PrintError("division by zero exception line %d:c%d to %d:c%d", bloc->first_line, bloc->first_column,
                   bloc->last_line, bloc->last_column);
        return INT_MAX;
    }
    return a / b;
}
