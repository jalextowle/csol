HEX_LITERAL              hex\((?:\"[0-9a-fA-F]{2}*\"|\\[0-9a-fA-F]{2}*\\)\)
HEX_NUM                  0x[0-9a-fA-F]+
STRING_LITERAL           \"(?:[^\"\r\n\\]|\\\\.)*\" 
ID                       [a-zA-Z_$][0-9a-zA-Z_$]*
%%
{HEXLITERAL}             printf("A hexadecimal literal: %s\n", yytext); 
{HEXNUM}                 printf("A hexadecimal number: %s\n", yytext); 
{STRING_LITERAL}         printf("A string literal: %s\n", yytext);
{ID}                     printf("An identifier: %s\n", yytext);
%%
int main(int argc, char **argv) {
  if (argc > 1) 
    yyin = fopen(argv[1], "r");
  else 
    yyin = stdin;
  yylex();
}
