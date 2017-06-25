/******************************************************************
   Desenvolvido por:
    - Carlos Magno Geraldo Barbosa
    - Lucas Geraldo Silva Cruz

   Licença: MIT
   Disciplina: Redes de Computadores
   Universidade Federal de São João del Rei - UFSJ
 ******************************************************************/

#include "servidores.c"

int main(int argc, char const *argv[]){
	int modelo = menu(argc, argv);
    
	configura_porta(argc, argv, &num_porta);

    switch (modelo) {
        case 1:
            iterativo(num_porta); // Modelo iterativo
            break;
        case 2:
            forked(num_porta);    // Modelo multiprocessos
            break;
        case 3:
            fila(num_porta);      // Modelo com fila detarefas
            break;
        case 4:
            concorrente(num_porta); // Modelo concorrente
            break;
        default:
            printf("Opção inválida.\n");
            exit(-1);
    }
	return 0;
}
