#include <stdio.h>
#include "comments.h"
#include "whitespace.h"

int main(int argc, char** argv) {
  if (argc != 4) {
    printf("Error: Scanner expects three char* as arguments.");
  } else {
    comment_scanner(*(argv + 1), *(argv + 2));
    multi_comment_scanner(*(argv + 2), *(argv + 3));
    whitespace_scanner(*(argv + 3), *(argv + 2));
  }
}
