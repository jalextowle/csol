/* Function: Single-Line Scanner
 * ------------------------------------------
 * Scans files for single line comments and removes them non-destructively. 
 * 
 * src: The filepath to the source file to scan.  
 * target: The filepath to write the updated file.
 */
int comment_scanner(char* src, char* target);

int multi_comment_scanner(char* src, char* target);
