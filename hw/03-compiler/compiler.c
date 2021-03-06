#include <assert.h>
#include "compiler.h"

int E();
void STMT();
void IF();
void BLOCK();
void WHILE();

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
    emit("t%d = %s\n", f, item);
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
    emit("t%d = t%d %s t%d\n", i, i1, op, i2);
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
  emit("%s = t%d\n", id, e);
}

// WHILE = while (E) STMT
void WHILE() {
  int whileBegin = nextLabel();
  int whileEnd = nextLabel();
  emit("(L%d)\n", whileBegin);
  skip("while");
  skip("(");
  int e = E();
  emit("if not T%d goto L%d\n", e, whileEnd);
  skip(")");
  STMT();
  emit("goto L%d\n", whileBegin);
  emit("(L%d)\n", whileEnd);
}

// IF = if (E) STMT (else STMT)? 這個else是可選的
void IF() {
  //ifBegin讀起開始 ifEnd讀起結束
  int ifBegin = nextLabel();//需要產生標記
  int ifEnd = nextLabel();
  //emit("(L%d)\n", ifBegin);
  skip("if");//取一個if字
  skip("(");//取一個(
  int e = E();
  //如果運算的結果符合E()就不用跳 不符合就要跳(if not T%d...)
  emit("if not T%d goto L%d\n", e, ifBegin);//需要產生中間碼
  skip(")");//再取一個)
  STMT();//取一個STMT
  
  //如果後面是一個else 就繼續比對else
  //if結束但else還沒開始的地方 這裡要跳到結尾 否則會連else一起做(if和else的結果不可能同時出現)if的區塊完成就跳到最後
  emit("goto L%d\n", ifEnd);
  emit("(L%d)\n", ifBegin);
  if(isNext("else")){
    skip("else");//取else字
    STMT();
   
    
  }
   emit("(L%d)\n", ifEnd);
}

// STMT = IF | WHILE | BLOCK | ASSIGN
void STMT() {
  if (isNext("while"))
     WHILE();
  else if (isNext("if"))
     IF();
  else if (isNext("{"))
    BLOCK();
  else
    ASSIGN();
}

// STMTS = STMT*
void STMTS() {
  while (!isEnd() && !isNext("}")) {
    STMT();
  }
}

// BLOCK = { STMTS }
void BLOCK() {
  skip("{");
  STMTS();
  skip("}");
}

// PROG = STMTS
void PROG() {
  STMTS();
}

void parse() {
  printf("============ parse =============\n");
  tokenIdx = 0;
  PROG();
}