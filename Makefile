compilar: servidor.c servidores.c servidores.h
	gcc -Wall servidor.c servidores.h -o saida -lpthread
limpar:
	rm -rf saida
