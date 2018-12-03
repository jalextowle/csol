compile: 
	gcc -Wall comments.c -o comments
test: 
	gcc -Wall test.c comments.c whitespace.c -lcheck -lm -lpthread -o test_comments
	./test_comments
	rm test_comments
