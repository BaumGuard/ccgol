output: src/ccgol.o
	gcc src/ccgol.o -o src/ccgol

ccgol.o: src/ccgol.c src/console_size.h src/import_field.h src/show_help.h
	gcc -c src/ccgol.c

clean:
	rm src/*.o src/ccgol
