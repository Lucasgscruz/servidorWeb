# Modelos de Servidores Web
Projeto apresentado ao curso de Ciência da Computação, da
Universidade Federal de São João del Rei, como requisito parcial
para obtenção da nota final da disciplina de Redes de Computadores.

Este projeto disponibiliza quatro modelos de implementação de um servidor web,
sendo eles:
- 1: Servidor web iterativo;
- 2: Servidor utilizando fork;
- 3: Servidor utilizando threads e fila de tarefas;
- 4: Servidor concorrente utilizando select;

## Execução
Para compilar os servidor, basta acessar a pasta raiz do projeto através de um
terminal linux e digitar o seguinte comando:

        make

Para executar o servidor digite o comando:

        ./servidorweb <numero da porta> <modelo de servidor desejado>

Exemplo de comando válido:

        ./servidorweb 5000 1


### Desenvolvido por:
![](https://github.com/Exterminus.png?size=100)
Carlos Magno ([github](https://github.com/Exterminus))

![](https://github.com/Lucasgscruz.png?size=100)
Lucas Cruz ([github](https://github.com/lucasgscruz))
