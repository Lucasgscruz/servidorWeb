/*
   Desenvolvido por:
    - Carlos Magno Geraldo Barbosa
    - Lucas Geraldo Silva Cruz

   Licença: MIT
   Disciplina: Redes de Computadores
   Universidade Federal de São João del Rei - UFSJ
 */
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
void configura_porta(int argc,char const *argv[],int *num_porta){
    //Recebe o novo número da porta do servidor e atualiza.
    if(argc >= 2 && (atoi(argv[1])>1023)) {
        *num_porta=atoi(argv[1]);
        printf("Número da Porta definido: %d\n",*num_porta);

    }else{
        printf("Utilizando a porta padrão definida: %d \n",*num_porta);
    }
}


int main(int argc, char const *argv[]){
    /* Variaveis para estabelecer a comunicacao */

    int socket_con = 0, num_porta = 5000, temp = 0,cliente=0;
    char mensagem[1024];
    socklen_t cliente_len;
    struct sockaddr_in endereco_servidor, endereco_cliente;
    configura_porta(argc,argv,&num_porta);
    //
    /* Abrindo o socket */
    socket_con = socket(AF_INET, SOCK_STREAM,0);
    if(socket_con < 0) {
            printf("Erro ao criar o socket.\n");
    }
    /* Preenche com zero */
    bzero((char *)&endereco_servidor, sizeof(endereco_servidor));
    endereco_servidor.sin_family = AF_INET;
    endereco_servidor.sin_addr.s_addr = INADDR_ANY;
    endereco_servidor.sin_port = htons(num_porta);

    /* Associa uma porta ao socket */
    if (bind(socket_con, (struct sockaddr *) &endereco_servidor,sizeof(endereco_servidor)) < 0) {
            printf("Erro ao Abrir a porta.\n");
    }else{
            printf("Aguardando conexão com os clientes...\n");
    }

    /* Tamanho maximo da fila de clientes. */
    listen(socket_con, 10);
    /* Estabelece a conexão com os clientes */
    cliente_len = sizeof(endereco_cliente);
    while(1) {
            cliente=accept(socket_con,(struct sockaddr *) &endereco_cliente, &cliente_len);
            if(cliente<0) {
                    printf("Erro na conexão.\n");
            }else{
                    printf("Cliente conectado %d\n",cliente);
            }
            bzero(mensagem,1024);
            temp = read(cliente,mensagem,1024);
            if (temp < 0) {
                perror("Erro ao ler o socket.\n");
            }
            /*Resposta vinda do servidor"*/
            printf("Mensagem Recebida:\n %s\n",mensagem);
            /*Escreve a resposta para o cliente*/
            temp=write(cliente,"HTTP/1.1 200 OK\n",16);
            write(cliente,"Server: C3PO-web7\n",18);
            write(cliente,"Connection: close\n",18);
            write(cliente,"Content-length: 89\n", 19);
            write(cliente,"Content-Type: text/html\n\n", 25);
            write(cliente,"<!DOCTYPE html><html><head><title>Redes</title></head><body><h1>42...!!<h1></body></html>",89);
            if(temp<0) {
                printf("erro ao escrever no socket\n");
            }
            //Encerra a conexão com o cliente.
            close(cliente);

    }
    close(socket_con);

    return 0;
}
