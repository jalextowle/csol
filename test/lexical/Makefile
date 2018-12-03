run: 
	./bin /Users/alextowle/csol/test/lexical/mock/master_source.sol /Users/alextowle/csol/test/lexical/mock/master_target.sol /Users/alextowle/csol/test/lexical/mock/temp.txt
compile: 
	gcc -Wall ../../src/lexical/scanner/scanner.c ../../src/lexical/scanner/comments.c ../../src/lexical/scanner/whitespace.c -o bin
test: 
	gcc -Wall test.c ../../src/lexical/scanner/comments.c ../../src/lexical/scanner/whitespace.c -lcheck -lm -lpthread -o test_comments
	./test_comments
	rm test_comments
