#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

// Variaveis para estabelecer a comunicacao
    int num_porta = 5000;
struct sockaddr_in endereco_servidor, endereco_cliente;
int socket_con = 0, flag = 0, cliente = 0;
int socket_principal = 0, temp = 0, maior_descritor = 0;
int max_clientes = 15, socket_cliente[100] = {0}, i = 0;
socklen_t cliente_len;
fd_set read_descritor;
char mensagem[1024];
pid_t pid;


// Funçoes
void configura_porta(int, char const **, int *);
int menu(int, char const **);
void error(const char *);
void *funcao(void *);
void concorrente(int);
void iterativo(int);
void resposta(int);
void forked(int);
void fila(int);
void help();

