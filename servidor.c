/******************************************************************
   Desenvolvido por:
    - Carlos Magno Geraldo Barbosa
    - Lucas Geraldo Silva Cruz

   Licença: MIT
   Disciplina: Redes de Computadores
   Universidade Federal de São João del Rei - UFSJ
 ******************************************************************/

#include "servidores.h"

void help(){
    printf("    ServidorWeb HELP -- Atenção!\n\
    Favor digitar os parâmetros no seguinte formato:\n\
        ./servidorweb porta modo\n\
    Modos Disponiveis:\n\
        1 - Iterativo\n\
        2 - Multi Processos \n\
        3 - Fila \n\
        4 - Select\n\
    Exemplo de comando válido:\n\
        ./servidorweb 5002 1\n");
}

int menu(int argc,char const *argv[]){
/* Menu de opçoes de modelos de servidor Web */

    if(argc<2){
        help();
        exit(-1);
    }
	int modelo = 0;
    modelo=atoi(argv[2]);
    if(modelo<0 || modelo>4){
        printf("Opção Inválida\n");
        exit(-1);
    }

	return modelo;
}

void error(const char *msg){
/* Exibe a mensagem de erro e encerra a execuçao do programa */

	printf("%s\n", msg);
	exit(1);
}

void configura_porta(int argc,char const *argv[],int *num_porta){
    //Recebe o novo número da porta do servidor e atualiza.
    if(argc >= 2 && (atoi(argv[1])>1024)) {
        *num_porta=atoi(argv[1]);
        printf("Número da Porta definido: %d\n",*num_porta);

    }else{
        printf("Utilizando a porta padrão definida: %d\n",*num_porta);
        printf("Digite uma porta maior de 1023 para usar uma porta personalizada\n");
    }
}


void resposta(int cliente){
	/*Escreve a resposta para o cliente*/

	int flag;

    flag=write(cliente,"HTTP/1.1 200 OK\n\
    Server: C3PO-web7\n\
    Connection: close\n\
    Content-length: 89\n\
    Content-Type: text/html\n\n\
    <!DOCTYPE html><html><head><title>Redes</title></head><body><h1>42...!!<h1></body></html>",185);
	//Erro ao enviar resposta para o cliente
	if(flag < 0)
		error("ERRO ao escrever resposta para o cliente!");
}

void iterativo(int num_porta){
	// Abrindo o socket
	socket_con = socket(AF_INET, SOCK_STREAM,0);
	if(socket_con < 0)
        error("ERRO ao abrir o socket.\n");

    // Preenche com zero
    bzero((char *)&endereco_servidor, sizeof(endereco_servidor));
    endereco_servidor.sin_family = AF_INET;
    endereco_servidor.sin_addr.s_addr = INADDR_ANY;
    endereco_servidor.sin_port = htons(num_porta);

    // Associa uma porta ao socket
    if(bind(socket_con, (struct sockaddr *) &endereco_servidor,sizeof(endereco_servidor)) < 0)
        error("ERRO ao Abrir a porta.");
    printf("Aguardando conexão dos clientes...\n");

    // Tamanho maximo da fila de clientes
    listen(socket_con, 10);
    cliente_len = sizeof(endereco_cliente);

    while(1){
    	// Estabelece conexao com o cliente
    	cliente = accept(socket_con,(struct sockaddr *) &endereco_cliente, &cliente_len);

        if(cliente < 0)
            printf("ERRO na conexão com o cliente.");
        printf("\n\tCliente conectado!\n");

        bzero(mensagem,1024);

        // Le requisicao enviada pelo cliente
        flag = read(cliente, mensagem, 1024);
        if (flag < 0)
            error("ERRO ao ler o socket.\n");
        printf("Mensagem Recebida:\n %s\n",mensagem);

        // Escreve a resposta para o cliente
 		resposta(cliente);
        close(cliente);
    }
    close(socket_con);
}

void forked(int num_porta){
	// Abrindo o socket
	socket_con = socket(AF_INET, SOCK_STREAM,0);
	if(socket_con < 0)
        error("ERRO ao abrir o socket.\n");

    // Preenche com zero
    bzero((char *)&endereco_servidor, sizeof(endereco_servidor));
    endereco_servidor.sin_family = AF_INET;
    endereco_servidor.sin_addr.s_addr = INADDR_ANY;
    endereco_servidor.sin_port = htons(num_porta);

    // Associa uma porta ao socket
    if(bind(socket_con, (struct sockaddr *) &endereco_servidor,sizeof(endereco_servidor)) < 0)
        error("ERRO ao Abrir a porta.");
    printf("Aguardando conexão dos clientes...\n");

    // Tamanho maximo da fila de clientes
    listen(socket_con, 10);
    cliente_len = sizeof(endereco_cliente);

    while(1){
    	// Estabelece conexao com o cliente
    	cliente = accept(socket_con,(struct sockaddr *) &endereco_cliente, &cliente_len);

        if(cliente < 0)
            printf("ERRO na conexão com o cliente.");
        printf("\n\tCliente conectado!\n");

        // Cria novo processo para tratar requisiçoes do cliente recem conectado
        if ((pid = fork()) < 0)
			error("ERRO ao gerar novo processo!");

		// Apenas o processo filho executa este trecho
		if (pid == 0){
			// Zerando mensagem a ser lida
			bzero(mensagem, 1024);
			// Le requisicao enviada pelo cliente
			flag = read(cliente, mensagem, 1024);

			// Erro na leitura da mensagem vinda do cliente
			if (flag < 0)
				error("Erro ao ler o socket.\n");

			printf("Mensagem Recebida:\n %s\n", mensagem);
			resposta(cliente);
			exit(0);
		}
        close(cliente);
    }
    close(socket_con);
}

int main(int argc, char const *argv[]){
	int modelo = menu(argc,argv);
    int num_porta=5000;

	configura_porta(argc,argv,&num_porta);

	if(modelo == 1)
		iterativo(num_porta);

	else if(modelo == 2)
		forked(num_porta);

	return 0;
}
