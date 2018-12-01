#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 1000

typedef struct {
  int read_cur;
  int write_cur;
} current;

current* comment_scan_line(current* cur, char* read, char* write);

void comment_scanner(char* _src, char* _target) {
  FILE *src, *target;
  current* cur = malloc(sizeof(current)); 
  cur->read_cur = 0;
  cur->write_cur = 0;
  char* read_buffer = malloc(sizeof(char) * BUFFER_SIZE);
  char* write_buffer = malloc(sizeof(char) * BUFFER_SIZE);
  src = fopen(_src, "r");
  target = fopen(_target, "w");

  if (src == NULL) {
    printf("Error opening source file.");
  } else {
    while(fgets(read_buffer, BUFFER_SIZE, src)) {
      while (cur->read_cur < BUFFER_SIZE) {
        cur = comment_scan_line(cur, read_buffer, write_buffer); 
      }
      fprintf(target, "%s", write_buffer); 
      cur->read_cur = 0;
      cur->write_cur = 0;
    }
  }

  fclose(src);
  fclose(target);
  free(read_buffer);
  free(write_buffer);
}

/********** Helpers ***********/

char lookahead(int cur, char* read) {
  if (cur < BUFFER_SIZE - 1) {
    return *(read + cur + 1); 
  } else {
    return '\0';
  }
}

int advance_to_newline(int cur, char* read) {
  char c;
  while (cur < BUFFER_SIZE - 1) {
    c = *(read + cur);
    if (c == '\n') {
      break;
    } else {
      cur++;
    } 
  }
  return cur;
}

current* comment_scan_line(current* cur, char* read, char* write) {
  char c, peek;
  while (cur->read_cur < BUFFER_SIZE) {
    c = *(read + cur->read_cur);
    if (c == '\0' || c == EOF) {
      *(write + cur->write_cur) = c;
      cur->read_cur = BUFFER_SIZE;
      break;
    } else if (c == '\n') {
      *(write + cur->write_cur) = c;
    } else if (c == '/') {
      peek = lookahead(cur->read_cur, read);
      if (peek == '/') {
        cur->read_cur = advance_to_newline(cur->read_cur, read);
        return cur;  
      }
    } else {
      *(write + cur->write_cur) = c;
    }
    cur->write_cur++;
    cur->read_cur++;
  }
  return cur;
}
