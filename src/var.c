#include "recall.h"

#define MAX_NAME_LEN 32
#define MAXVARS 11

static int nVars       = 0;
static int N           = 0;
static Variable** vars = NULL;

static Variable* findVar(char* varname)
{
    int i, j;
    if (varname == NULL) {
        return NULL;
    }
    if (N == 1) {
        for (j = 0; j < nVars; j++) {
            if (strcmp(vars[0][j].name, varname) == 0)
                return (*(vars) + j);
        }
    } else if (N == 0)
        return NULL;

    else {
        for (i = 0; i < N; i++)
            for (j = 0; j < MAXVARS; j++) {
                if (i * MAXVARS + j >= nVars + (N - 1) * MAXVARS)
                    return NULL;

                if (strcmp(vars[i][j].name, varname) == 0)
                    return (*(vars + i) + j);
            }
    }
    return NULL;
}

static Variable* addVar(char* varname)
{
    if (varname == NULL) {
        return NULL;
    }
    if ((nVars == MAXVARS) || (N == 0)) {
        nVars   = 0;
        vars    = (Variable**)realloc(vars, (N + 1) * sizeof(Variable*));
        vars[N] = (Variable*)malloc(MAXVARS * sizeof(Variable));
        N += 1;
    }

    vars[N - 1][nVars].value = 0;
    int len                  = strlen(varname) + 1;
    if (len > MAX_NAME_LEN)
        vars[N - 1][nVars].name = malloc(strlen(varname) + 1);
    else
        vars[N - 1][nVars].name = malloc(MAX_NAME_LEN);

    if (vars[N - 1][nVars].name == NULL) {
        PrintError("internal error creating variable '%s'", varname);
        return NULL;
    }

    strcpy(vars[N - 1][nVars].name, varname);
    nVars += 1;
    return (*(vars + (N - 1)) + (nVars - 1));
}

extern Variable* VarGet(char* varname, YYLTYPE* bloc)
{
    Variable* var = findVar(varname);
    if (var == NULL) {
        var = addVar(varname);
    }
    return var;
}

extern void VarSetValue(Variable* var, int value)
{
    if (var == NULL) {
        return;
    }
    var->value = value;
    return;
}

extern int VarGetValue(char* varname, YYLTYPE* bloc)
{
    Variable* var = NULL;

    var = findVar(varname);
    if (var == NULL) {
        PrintError("reference to unknown variable '%s'", varname);
        var = addVar(varname);
        return 0;
    }
    return var->value;
}


extern void DumpAllVariables(int errorcount)
{
    int i, j;
    char formatsymbols[MAX_NAME_LEN - 3];
    for (int i = 0; i < MAX_NAME_LEN - 3; i++) {
        formatsymbols[i] = '-';
    }
    printf("\tName%.*s Value----------\n", MAX_NAME_LEN - 3, formatsymbols);
    for (i = 0; i < N - 1; i++) {
        for (j = 0; j < MAXVARS; j++) {
            printf("%d\t: %-*.*s: %u\n", i * MAXVARS + j + 1, MAX_NAME_LEN, MAX_NAME_LEN, vars[i][j].name,
                   vars[i][j].value);
        }
    }
    for (i = N - 1; i < N; i++) {
        for (j = 0; j < nVars; j++) {
            printf("%d\t: %-*.*s: %u\n", i * MAXVARS + j + 1, MAX_NAME_LEN, MAX_NAME_LEN, vars[i][j].name,
                   vars[i][j].value);
        }
    }
    printf("==== count of variables - %d ====\n", (N - 1) * MAXVARS + j);
    printf("==== count of errors - %d ====\n", errorcount);
    return;
}
