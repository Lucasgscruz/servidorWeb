necessario: iterativo.c concorrente.c
	gcc -Wall iterativo.c -o iterativo
	gcc -Wall concorrente.c -o concorrente
clear:
	rm -rf *.exe
