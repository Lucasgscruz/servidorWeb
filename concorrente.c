/*
   Desenvolvido por:
    - Carlos Magno Geraldo Barbosa
    - Lucas Geraldo Silva Cruz

   Licença: MIT
   Disciplina: Redes de Computadores
   Universidade Federal de São João del Rei - UFSJ

   Baseado nos códigos:
   http://www.binarytides.com/multiple-socket-connections-fdset-select-linux/

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

    int socket_principal = 0, num_porta = 5000, temp = 0,cliente=0,maior_descritor=0;
    int max_clientes=15,socket_cliente[100]={0},i=0;
    fd_set read_descritor;
    socklen_t cliente_len;
    struct sockaddr_in endereco_servidor, endereco_cliente;
    configura_porta(argc,argv,&num_porta);
    //
    /* Abrindo o socket */
    socket_principal = socket(AF_INET, SOCK_STREAM,0);
    if(socket_principal < 0) {
            printf("Erro ao criar o socket.\n");
    }
    /* Preenche com zero */
    bzero((char *)&endereco_servidor, sizeof(endereco_servidor));
    endereco_servidor.sin_family = AF_INET;
    endereco_servidor.sin_addr.s_addr = INADDR_ANY;
    endereco_servidor.sin_port = htons(num_porta);

    /* Associa uma porta ao socket */
    if (bind(socket_principal, (struct sockaddr *) &endereco_servidor,sizeof(endereco_servidor)) < 0) {
            printf("Erro ao Abrir a porta.\n");
    }else{
            printf("Aguardando conexão com os clientes Na porta [%d]...\n",num_porta);
    }

    /* Tamanho máximo da fila de clientes. */
    if(listen(socket_principal, 10)<0){
        printf("Erro na fila de clientes..");
        exit(EXIT_FAILURE);
    }
    /* Estabelece a conexão com os clientes */
    cliente_len = sizeof(endereco_cliente);

    while(1){

        //inicializa o descritor.
        FD_ZERO(&read_descritor);

        //Adiciona o socket principal no conjunto..
        FD_SET(socket_principal,&read_descritor);
        //FD_SET(socket_principal,&write_descritor);
        maior_descritor=socket_principal;

        for(i=0;i<max_clientes;i++){
            temp= socket_cliente[i];

            if(temp>0){

                //Adiciona o indice do descritor na lista de leituras
                FD_SET(temp,&read_descritor);
                //FD_SET(temp,&write_descritor);

            }
            if(temp>maior_descritor){
                maior_descritor=temp;
            }

        }

        temp=0;
        //seleciona o descritor que está em atividade.
        temp= select(maior_descritor+1,&read_descritor,NULL,NULL,NULL);
        if(temp<0){
            printf("ERRO no Select\n");
            exit(-1);
        }
        //Atividade no socket principal...

        if(FD_ISSET(socket_principal,&read_descritor)){
            cliente=accept(socket_principal,(struct sockaddr *) &endereco_cliente, &cliente_len);
            if(cliente<0) {
                    printf("Erro na conexão.\n");
                    exit(EXIT_FAILURE);
            }else{
                    printf("Cliente conectado ");
            }
            /*Envia mensagem para o cliente...*/
            send(cliente, "HTTP/1.1 200 OK\n", 16,0);
            send(cliente,"Server: C3PO-web7\n",19,0);
            send(cliente,"Connection: close\n",18,0);
            send(cliente,"Content-length: 89\n",19,0);
            send(cliente, "Content-Type: text/html\n\n", 25,0);
            send(cliente, "<!DOCTYPE html><html><head><title>Redes</title></head><body><h1>42...!!<h1></body></html>",89,0);
            //Adiciona o cliente na lista de clientes.
            for(i=0;i<max_clientes;i++){
                if(socket_cliente[i]==0){
                    socket_cliente[i]=cliente;
                    break;
                }
            }

        }

    }
    close(socket_principal);
    return 0;
}
