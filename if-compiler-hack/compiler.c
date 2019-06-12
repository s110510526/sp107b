#include <assert.h>
#include "compiler.h"

int E();
void STMT();
void IF();
void BLOCK();

int tempIdx = 0, labelIdx = 0;

#define nextTemp() (tempIdx++)
#define nextLabel() (labelIdx++)
#define emit printf

int isNext(char *set) {
  char eset[SMAX], etoken[SMAX];
  sprintf(eset, " %s ", set);
  sprintf(etoken, " %s ", tokens[tokenIdx]);
  return (tokenIdx < tokenTop && strstr(eset, etoken) != NULL);
}

int isEnd() {
  return tokenIdx >= tokenTop;
}

char *next() {
  // printf("token[%d]=%s\n", tokenIdx, tokens[tokenIdx]);
  return tokens[tokenIdx++];
}

char *skip(char *set) {
  if (isNext(set)) {
    return next();
  } else {
    printf("skip(%s) got %s fail!\n", set, next());
    assert(0);
  }
}

// F = (E) | Number | Id
int F() {
  int f;
  if (isNext("(")) { // '(' E ')'
    next(); // (
    f = E();
    next(); // )
  } else { // Number | Id
    f = nextTemp();
    char *item = next();
    //emit("..t%d = %s..\n", f, item);
    emit("@%s\n", item);
    emit("D = A\n");
    emit("@t%d\n", f);
    emit("M = D\n");
  }
  return f;
}

// E = F (op E)*
int E() {
  int i1 = F();
  while (isNext("+ - * / & | ! < > =")) {
    char *op = next();
    int i2 = E();
    int i = nextTemp();
    //emit("..t%d = t%d %s t%d..\n", i, i1, op, i2);
    emit("@t%d\n",i2);
    emit("D = M\n");
    emit("@t%d\n",i);
    emit("M = D\n");
    emit("@t%d\n",i1);
    emit("D = M\n");
    emit("@t%d\n", i);
    emit("M = D %s M\n", op);
    /*
    @i2
    D = M
    @i
    M = D
    @i1
    D = M
    @i
    M = D op M
     */
    i1 = i;
  }
  return i1;
}

// ASSIGN = id '=' E;
void ASSIGN() {
  char *id = next();
  skip("=");
  int e = E();
  skip(";");
  //emit("..%s = t%d..\n", id, e);
  emit("@t%d\n", e);
  emit("D = M\n");
  emit("@%s\n", id);
  emit("M = D\n");
  /*
  @t0
  D = M
  @a
  M = D
   */
}

//if (E) STMT

void IF() {
  int notIf = nextLabel();
  skip("if");
  skip("(");
  int e = E();
  //emit("..if not T%d goto L%d..\n", e, notIf);
  emit("@t%d\n", e);
  emit("D = M\n");
  emit("@L%d\n", notIf);
  emit("D; JEQ\n");
  /*
  D=M
  @notIf
  D; JEQ
   */
  skip(")");
  STMT();
  emit("(L%d)\n", notIf);
}

// while (E) STMT
void WHILE() {
  int whileBegin = nextLabel();
  int whileEnd = nextLabel();
  emit("(L%d)\n", whileBegin);
  skip("while");
  skip("(");
  int e = E();
  //emit("..if not T%d goto L%d..\n", e, whileEnd);
  emit("@t%d\n", e);
  emit("D = M\n");
  emit("@L%d\n", whileEnd);
  emit("D; JEQ\n");
  skip(")");
  STMT();
  //emit("goto L%d\n", whileBegin);
  emit("@L%d\n", whileBegin);
  emit("0; JMP\n");
  emit("(L%d)\n", whileEnd);
}

void STMT() {
  if (isNext("while"))
    return WHILE();
   else if (isNext("if"))
     IF();
  else if (isNext("{"))
    BLOCK();
  else
    ASSIGN();
}

void STMTS() {
  while (!isEnd() && !isNext("}")) {
    STMT();
  }
}

// { STMT* }
void BLOCK() {
  skip("{");
  STMTS();
  skip("}");
}

void PROG() {
  STMTS();
}

void parse() {
  printf("============ parse =============\n");
  tokenIdx = 0;
  PROG();
}