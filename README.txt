Trabalho 4  - Rummikub

Paulo Inay Cruz (p = 0)  - N� USP 10388691
Jonathan Ferreira de Mello (p = 1)  - N� USP 10377754 (Aluno da disciplina SSC0601)
Jo�o Marcos Della Torre Divino (p = 2)  - N� USP 10377708

     Neste trabalho, foi implementado, utilizando linguagem C, um programa que
permite jogar Rummikub.
     O programa fornece uma interface interativa e bem detalhada, com um menu inicial,
op��o de sele��o do modo de jogo (Aleat�rio ou Controlado) e da quantidade de
jogadores, um menu secund�rio com as a��es do jogo, vis�o do tabuleiro e das cartas
de cada jogador, indica��o de vit�ria e possibilidade de jogar novamente.
     O c�digo � praticamente todo estruturado em cima de fun��es, as quais controlam
todo o andamento do jogo. Os menus t�m como entrada, em sua maioria, caracteres.
O baralho (com 106 cartas) � composto por n�meros hexadecimais (de 1 a D), que
indicam o valor da carta, e por caracteres especiais ('!', '@', '#' e '$'), que indicam
os naipes, al�m de dois coringas ('**' e '**').
     Limita��es s�o encontradas no que diz respeito � entradas diferentes das exigidas
nos poucos menus que funcionam com inteiros. Ainda, aleatoriamente, � impresso
'C:' para algum jogador quando o anterior compra uma carta.
