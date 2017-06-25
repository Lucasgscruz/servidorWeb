// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>

// int main(){
// 	/* Variaveis para estabelecer a comunicacao */
// 	int socket_con = 0, num_porta = 5008, temp = 0;
// 	socklen_t cliente_len;
// 	struct sockaddr_in endereco_servidor, endereco_cliente;
// 	int cliente;
// 	char mensagem[50];

// 	/* Abrindo o socket */
// 	socket_con = socket(AF_INET, SOCK_STREAM,0); 
// 	if(socket_con < 0){
// 		printf("Erro ao criar o socket.\n");
// 		exit(1);
// 	}

// 	/* Preenche com zero */
// 	bzero((char *)&endereco_servidor, sizeof(endereco_servidor));
// 	endereco_servidor.sin_family = AF_INET;
// 	endereco_servidor.sin_addr.s_addr = INADDR_ANY;
// 	endereco_servidor.sin_port = htons(num_porta);

// 	/* Associa uma porta ao socket */
// 	if (bind(socket_con, (struct sockaddr *) &endereco_servidor,sizeof(endereco_servidor)) < 0){
// 		printf("Erro ao Abrir a porta.\n");
// 		exit(1);
// 	}

// 	printf("Aguardando conexão dos 4 clientes...\n");	

// 	/* Tamanho maximo da fila de clientes. */
// 	listen(socket_con, 5);
	
// 	/* Estabelece a conexão com os clientes */
// 	cliente = accept(socket_con,(struct sockaddr *) &endereco_cliente, &cliente_len); // Atribuindo a porta

// 	if(cliente== -1){
// 	    printf("Erro ao conectar com o cliente.\n");
// 		exit(1);
// 	}
// 	printf("Conectado ao cliente: %d \n", cliente);

// 	read(cliente, mensagem, 50);
// 	printf("valor da mensagem:\n\n %s", mensagem);

// 	return 0;
// }

#include<netinet/in.h>    
#include<stdio.h>    
#include<stdlib.h>    
#include<sys/socket.h>    
#include<sys/stat.h>    
#include<sys/types.h>    
#include<unistd.h>    
#include<pthread.h> 

// int main() {    
//    int create_socket, new_socket;    
//    socklen_t addrlen;    
//    int bufsize = 1024;    
//    char *buffer = malloc(bufsize);    
//    struct sockaddr_in address;    
 
//    if ((create_socket = socket(AF_INET, SOCK_STREAM, 0)) > 0){    
//       printf("The socket was created\n");
//    }
	
//    address.sin_family = AF_INET;    
//    address.sin_addr.s_addr = INADDR_ANY;    
//    address.sin_port = htons(15002);    
	
//    if (bind(create_socket, (struct sockaddr *) &address, sizeof(address)) == 0){    
//       printf("Binding Socket\n");
//    }
	
	
//    while (1) {    
//       if (listen(create_socket, 10) < 0) {    
//          perror("server: listen");    
//          exit(1);    
//       }    
	
//       if ((new_socket = accept(create_socket, (struct sockaddr *) &address, &addrlen)) < 0) {    
//          perror("server: accept");    
//          exit(1);    
//       }    
	
//       if (new_socket > 0){    
//          printf("The Client is connected...\n");
//       }
		
//       recv(new_socket, buffer, bufsize, 0);    
//       printf("Mensagem recebida: \n%s\n", buffer);    
//       write(new_socket, "HTTP/1.1 200 OK\n", 16); 
//       write(new_socket, "Content-length: 46\n", 19); 
//       write(new_socket, "Content-Type: text/html\n\n", 25); 
//       write(new_socket, "<html><body><H1>Hello world</H1></body></html>",46);   
//       close(new_socket);    
//    }    
//    close(create_socket);    
//    return 0;    
// }

/* function to be executed by the new thread */
#define NUM_THREADS 4
int vet[10];

void *OLA(void *arg){
	int *valor = (void *) arg;
	int i = 0;
   	if(*valor == 0){
   		for(i = 0; i<10; i++)
   			vet[i] = 0;
   		printf(" %d brinquei!\n", 0);
   	}
   	else if(*valor == 1){
   		for(i = 0; i<10; i++)
   			vet[i] = 1;
   		printf(" %d brinquei!\n", 1);
   	}
   	else if(*valor == 2){
   		for(i = 0; i<10; i++)
   			vet[i] = 2;
   		printf(" %d brinquei!\n", 2);
   	}
   	else if(*valor == 3){
   		for(i = 0; i<10; i++)
   			vet[i] = 3;
   		printf(" %d brinquei!\n", 3);
   	}
	pthread_exit(NULL);
}

int main(){

   pthread_t ramo[5];
   int flag;
   int j=0, k = 0;

   printf("A criar uma nova thread\n\n");
    while(j < 4){
    	printf("Ja volteiiii! \n");
   		flag = pthread_create(&ramo[j], NULL, OLA, &j);
    	if (flag!=0) printf("Erro na criação duma nova thread\n");
    	else
    		printf("Thread %d criada \n",j );
    	if( j == 3){ 
    		j = 0;
    		flag = pthread_create(&ramo[j], NULL, OLA, &j);
    		k++; if(k == 3) break;
    	}
    	j++;
    }

    for (k = 0; k < 10; k++){
    	printf("%d  ",vet[k] );
    }
    printf("\n");
    printf("%lu\n",ramo[2] );

    

   return 0;   /* O programa não vai chegar aqui.         */ 

}