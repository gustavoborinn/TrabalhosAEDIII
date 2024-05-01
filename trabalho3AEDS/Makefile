# Makefile para compilar os códigos clonesses.c, desenhar_grafo.py e temp_grafo.py

all: closeness desenhar_grafo temp_grafo

closeness: closeness.c
	gcc closeness.c -o closeness -std=c99

desenhar_grafo:
	python desenhar_grafo.py

temp_grafo:
	python temp_grafo.py

clean:
	rm -f closeness

run_closeness: closeness
	./closeness

run_desenhar_grafo: desenhar_grafo
	python desenhar_grafo.py

run_temp_grafo: temp_grafo
	python temp_grafo.py