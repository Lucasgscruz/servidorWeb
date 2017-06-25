necessario: iterativo.c concorrente.c servidor.c servidores.h
	gcc -Wall iterativo.c -o iterativo
	gcc -Wall concorrente.c -o concorrente
	gcc -Wall servidores.h servidor.c -o servidorweb
clear:
	rm -rf iterativo concorrente servidorweb
