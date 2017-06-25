/* A simple server in the internet domain using TCP
   The port number is passed as an argument
   This version runs forever, forking off a separate
   process for each connection
   Fonte do exemplo
   http://www.linuxhowtos.org/C_C++/socket.htm
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


void error(const char *msg){
	/* Exibe a mensagem de erro e encerra a execuçao do programa */

	printf("%s\n", msg);
	exit(1);
}

void resposta(int cliente){
	/*Escreve a resposta para o cliente*/	

	int flag;
	flag = write(cliente,"HTTP/1.1 200 OK\n\
	Server: Iterativo\n\
	Connection: close\n\
	Content-length: 60\n\
	Content-Type: text/html\n\n\
	<!DOCTYPE html><html><body><h1>Alo Muuundo!!<h1></body></html>",159);

	//Erro ao enviar resposta para o cliente
	if(flag < 0) {
		error("Erro ao escrever resposta para o cliente!");
	}
}

int main(int argc, char *argv[]){
	// Variaveis do servidor
	int sockfd, cliente, portno, temp = 0;
	pid_t pid;
	struct sockaddr_in serv_addr, cli_addr;
	socklen_t clilen;
	char mensagem[1024];

	// Se nao for passada nenhuma porta como parametro
	if (argc < 2) 
		 error("ERRO, porta nao fornecida!\n"); 

	 // Abrindo socket
	 sockfd = socket(AF_INET, SOCK_STREAM, 0);
	 
	 //Se ocorrer erro ao abrir o socket
	 if (sockfd < 0)
		error("ERROR opening socket");

	 bzero((char *) &serv_addr, sizeof(serv_addr));
	 portno = atoi(argv[1]);
	 serv_addr.sin_family = AF_INET;
	 serv_addr.sin_addr.s_addr = INADDR_ANY;
	 serv_addr.sin_port = htons(portno);

	// Atribuir a uma porta
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR on binding");
	printf("Aguardando conexão com os clientes...\n");
	 
	 listen(sockfd,5);
	 clilen = sizeof(cli_addr);

	// Inicio do loop do Servidor
	while(1) {
		cliente = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		if (cliente < 0)
			error("Erro ao se conectar com o cliente!");
	 	
	 	printf("\n\tCliente conectado!\n");
		 
		if ((pid = fork()) < 0)
			error("ERRO ao gerar novo processo!");

		// Apenas o processo filho executa este trecho
		if (pid == 0){
			// Zerando mensagem a ser lida
			bzero(mensagem, 1024);
			temp = read(cliente, mensagem, 1024);

			// Erro na leitura da mensagem vinda do cliente
			if (temp < 0)
				error("Erro ao ler o socket.\n");

			printf("Mensagem Recebida:\n %s\n", mensagem);	
			resposta(cliente);						 
			exit(0);
		}		

		close(cliente);      
	}

	// Fechando sockets
	close(cliente);
	close(sockfd);
	return 0; 
}