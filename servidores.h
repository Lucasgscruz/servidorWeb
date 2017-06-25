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
struct sockaddr_in endereco_servidor, endereco_cliente;
int socket_con = 0, num_porta, flag = 0, cliente;
socklen_t cliente_len;
char mensagem[1024];
pid_t pid;

<<<<<<< HEAD
// Funcoes
void configura_porta(int ,char const *argv[], int *num_porta);
int menu(int, char const *argv[]);
=======
int menu(int argc,char const *argv[]);
void resposta(int);
>>>>>>> 8ce474054b4b8923a26b837afad90fce93c987f6
void iterativo(int);
void resposta(int);
void forked(int);
<<<<<<< HEAD
void help();




=======
void concorrente(int num_porta);
>>>>>>> 8ce474054b4b8923a26b837afad90fce93c987f6
