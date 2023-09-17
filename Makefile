output: ccgol.o
	gcc ccgol.o -o ccgol

ccgol.o: ccgol.c console_size.h import_field.h show_help.h
	gcc -c ccgol.c

clean:
	rm *.o ccgol
