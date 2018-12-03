run: 
	./bin /Users/alextowle/csol/src/lexical/scanner/mock/master_source.sol /Users/alextowle/csol/src/lexical/scanner/mock/master_target.sol /Users/alextowle/csol/src/lexical/scanner/temp.txt
compile: 
	gcc -Wall scanner.c comments.c whitespace.c -o bin
test: 
	gcc -Wall test.c comments.c whitespace.c -lcheck -lm -lpthread -o test_comments
	./test_comments
	rm test_comments
