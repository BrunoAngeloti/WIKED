compile: main.c Link.c Contribuicao.c Editores.c Paginas.c ListaContribuicao.c ListaEditores.c ListaLink.c ListaPaginas.c
	gcc -ggdb -Wno-unused-const-variable -o wiked.out *.c

clean:
	rm -f *.0 a.out wiked.out log.txt

run:
	valgrind --leak-check=full -s ./wiked.out entrada.txt