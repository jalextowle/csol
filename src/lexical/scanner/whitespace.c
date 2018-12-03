#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 1000

typedef struct {
  int read_ptr;
  int write_ptr; 
  int flag;
  int error_code;
} current; 

void whitespace_scan(current* cur, char* read, char* write) {
  char c;
  while (cur->read_ptr < BUFFER_SIZE) {
    c = *(read + cur->read_ptr); 
    if (c == '\0' || c == EOF) {
      *(write + cur->write_ptr) = c;
      cur->write_ptr++;
      break;
    } else if (isspace((int) c)) {
      if (!cur->flag) {
        *(write + cur->write_ptr) = '\x20';
        cur->write_ptr++;
        cur->flag = 1;
      }
    } else {
      if (cur->flag) {
        cur->flag = 0;
      }
      *(write + cur->write_ptr) = c;
      cur->write_ptr++;
    }
    cur->read_ptr++;
  }
}

int whitespace_scanner(char* _src, char* _target) {
  current *cur;
  char *read, *write;
  FILE *src, *target;
  cur = malloc(sizeof(current));
  cur->read_ptr = 0;
  cur->write_ptr = 0;
  cur->flag = 0;
  src = fopen(_src, "r");
  target = fopen(_target, "w");
  read = malloc(sizeof(char) * BUFFER_SIZE);
  write = malloc(sizeof(char) * BUFFER_SIZE);
 
  if (src == NULL) {
    printf("Error opening source file");
  } else {
    while (fgets(read, sizeof(char) * BUFFER_SIZE, src)) {
      whitespace_scan(cur, read, write);      
      fprintf(target, "%s", write);
      cur->read_ptr = 0;
      cur->write_ptr = 0;
    }
  }

  fclose(src);
  fclose(target);
  free(cur);
  free(read);
  free(write);
  return 0;
}
