#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 1000

// Error codes: 
// 0 - No error
// 1 - Missing multi-line comment close 
// FIXME - Update with the correct error codes
typedef struct {
  int read_cur;
  int write_cur; 
  int flag;
  int error_code;
} current;

void throw_error(int error_code) {
  /* FIXME */
  printf("Exited with error code: %d\n", error_code);
}

void comment_scan_line(current* cur, char* read, char* write);
void multi_comment_scan(current* cur, char* read, char* write);

int comment_scanner(char* _src, char* _target) {
  FILE *src, *target;
  current* cur = malloc(sizeof(current)); 
  cur->read_cur = 0;
  cur->write_cur = 0;
  cur->flag = 0;
  char* read_buffer = malloc(sizeof(char) * BUFFER_SIZE);
  char* write_buffer = malloc(sizeof(char) * BUFFER_SIZE);
  src = fopen(_src, "r");
  target = fopen(_target, "w");

  if (src == NULL) {
    printf("Error opening source file.");
    return 1;
  } else {
    while(fgets(read_buffer, sizeof(char) * BUFFER_SIZE, src)) {
      comment_scan_line(cur, read_buffer, write_buffer); 
      fprintf(target, "%s", write_buffer); 
      cur->read_cur = 0;
      cur->write_cur = 0;
    }
  }

  fclose(src);
  fclose(target);
  free(read_buffer);
  free(write_buffer);
  free(cur);
  return 0;
}

int multi_comment_scanner(char* _src, char* _target) {
  int error = 0;
  FILE *src, *target;
  current* cur = malloc(sizeof(current)); 
  cur->read_cur = 0;
  cur->write_cur = 0;
  cur->flag = 0;
  cur->error_code = 0;
  char* read_buffer = malloc(sizeof(char) * BUFFER_SIZE);
  char* write_buffer = malloc(sizeof(char) * BUFFER_SIZE);
  src = fopen(_src, "r");
  target = fopen(_target, "w");

  if (src == NULL) {
    printf("Error opening source file.");
  } else {
    while(fgets(read_buffer, sizeof(char) * BUFFER_SIZE, src)) {
      multi_comment_scan(cur, read_buffer, write_buffer);
      if (cur->error_code) {
        error = cur->error_code;
        throw_error(cur->error_code);
        break;
      } else {
        fprintf(target, "%s", write_buffer); 
        cur->read_cur = 0;
        cur->write_cur = 0;
      }
    }
  }
  if (cur->flag) {
    throw_error(1);
    error = 1;
  }

  fclose(src);
  fclose(target);
  free(read_buffer);
  free(write_buffer);
  free(cur);
  return error;
}

/********** Helpers ***********/

char lookahead(int cur, char* read) {
  if (cur < BUFFER_SIZE - 1) {
    return *(read + cur + 1); 
  } else {
    return '\0';
  }
}

void comment_scan_line(current* cur, char* read, char* write) {
  char c, peek;
  while (cur->read_cur < BUFFER_SIZE) {
    c = *(read + cur->read_cur);
    if (c == '\0' || c == EOF) {
      *(write + cur->write_cur) = c;
      cur->write_cur++;
      cur->read_cur = BUFFER_SIZE;
      break;
    } else if (c == '\n') {
      if (cur->flag) {
        cur->flag = 0;
      }
      *(write + cur->write_cur) = c;
      cur->write_cur++;
    } else if (c == '/') {
      peek = lookahead(cur->read_cur, read);
      if (peek == '/') {
        cur->flag = 1;
        cur->read_cur++;
      } else {
        if (!(cur->flag)) {
          *(write + cur->write_cur) = c;
          cur->write_cur++;
        } 
      }
    } else {
      if (!(cur->flag)) {
        *(write + cur->write_cur) = c;
        cur->write_cur++;
      }
    }
    cur->read_cur++;
  }
}

void multi_comment_scan(current* cur, char* read, char* write) {
  // When flag is 0, a multi-line comment has not been identified
  char c, peek;
  while (cur->read_cur < BUFFER_SIZE) {
    c = *(read + cur->read_cur);
    if (c == '\0' || c == EOF) {
      *(write + cur->write_cur) = c;
      cur->write_cur++;
      cur->read_cur = BUFFER_SIZE;
    } else if (c == '/') {
      peek = lookahead(cur->read_cur, read); 
      if (peek == '*') {
        if (cur->flag) {
          cur->error_code = 2;
          break;
        } else {
          cur->flag = 1;
          cur->read_cur += 2;
        }
      } else {
        *(write + cur->write_cur) = c;
        cur->write_cur++;
      }
    } else if (c == '*') {
      peek = lookahead(cur->read_cur, read); 
      if (peek == '/') {
        // If a multi-line comment has been opened, close it
        if (cur->flag) {
          cur->flag = 0;
          cur->read_cur += 2;
        } else {
          cur->error_code = 3;
          break;
        }
      } else {
        *(write + cur->write_cur) = c;
        cur->write_cur++;
      }
    } else {
      if (!(cur->flag)) {
        *(write + cur->write_cur) = c;
        cur->write_cur++;
      }
      cur->read_cur++;
    }
  }
}
