#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int attribute_ptr;
  char* token_name;
} Token;

typedef struct {
  int size;
  int cur;
  char* buffer;
} Arraylist;

typedef struct {
  regex_t* pragma;
  regex_t* solidity;
  regex_t* contract;
  regex_t* function;
} lexer;

void push(Arraylist *list, char value) {
  char *newBuffer;
  if (list->cur < list->size) {
    *(list->buffer + list->cur) = value;
    list->cur++;
  } else {
    newBuffer = malloc(list->size * 2 * sizeof(char));
    for (int i = 0; i < list->size; i++) {
      *(newBuffer + i) = *(list->buffer + i);
    }
    *(newBuffer + list->cur) = value;
    list->buffer = newBuffer;
    list->cur++;
    list->size *= 2;
  }
}

char* getNextWord(FILE *src) {
  char c;
  Arraylist *list = malloc(sizeof(Arraylist));
  list->cur = 0;
  list->size = 16;
  list->buffer = malloc(sizeof(char) * 16);
  while ((c = getc(src)) != EOF) {
    if (c == ' ') {
      break;
    } else {
      push(list, c); 
    }
  }
  push(list, '\0');
  return list->buffer;
}

int regex_match(char* s, regex_t* r) {
  int reti = regexec(r, s, 0, NULL, 0);
  return reti;
}

Token* getNextToken(FILE *src, lexer* lex) {
  Token* t = malloc(sizeof(Token)); 
  char *word = getNextWord(src);
  if (regex_match(word, lex->contract)) {
    t->token_name = word;
  } else if (regex_match(word, lex->function)) {
    t->token_name = word;
  } if (regex_match(word, lex->pragma)) {
    t->token_name = word;
  } else if (regex_match(word, lex->solidity)) {
    t->token_name = word;
  } 
  return t;
}

int main() {
  lexer* lex = malloc(sizeof(lexer));
  lex->contract = malloc(sizeof(regex_t));
  lex->function = malloc(sizeof(regex_t));
  lex->pragma = malloc(sizeof(regex_t));
  lex->solidity = malloc(sizeof(regex_t));
  regcomp(lex->contract, "^contract$", 0);
  regcomp(lex->function, "^function$", 0);
  regcomp(lex->pragma, "^pragma$", 0);
  regcomp(lex->solidity, "^solidity$", 0);
  FILE* src = fopen("/Users/alextowle/csol/src/lexical/master_target.sol", "r");
  if (src == NULL) {
    printf("File could not be opened");
    return 1;
  } 
  Token *t = getNextToken(src, lex);
  printf("%s\n", t->token_name);
  t = getNextToken(src, lex);
  printf("%s\n", t->token_name);
}
