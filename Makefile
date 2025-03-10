build: 	
	gcc -std=c9x -g -O0 -Wall -Wextra tema2.c -o suffix_tree

run:
	./suffix_tree
	
clean:
	rm -f suffix_tree

