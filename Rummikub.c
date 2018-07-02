//p =  --> Paulo Inay Cruz - N° USP 10388691
//p =  --> João Marcos Della Torre Divino - N° USP 10377708
//p =  --> Jonathan Ferreira de Mello - N° USP 10377754


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/* Declaração de tipos */

	struct carta_emjogo{
	
		char conteudo[2];
		int indice_seq;
		int indice_grupo;
		int indice_mao;
		int pos_seq;
	
	};
	
	typedef char opc;
	typedef int contador;
	typedef struct carta_emjogo carta_j;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


/* Declaração das funções */


/*Função Verificar_Tabuleiro: Verifica se o tabuleiro é válido após o movimento de um jogador.
  
  Entradas: *cartas: Vetor de structs, possui todas as cartas que já foram compradas e estão nas mãos dos jogadores ou no tabuleiro. 
  			n_grupos: Indica a quantidade de grupos.
  			n_seq: Indica o número de sequências.
  			n_cartas: Indica o número de cartas que foram compradas e estão nas mãos dos jogadores ou no tabuleiro.

  Saídas: 1 se o tabuleiro montado pelo jogador for válido, 0 se não o for.
*/

int Verificar_Tabuleiro(carta_j *cartas, int n_grupos, int n_seq, int n_cartas){
	
	//Verificar sequencias
	
	int max_pos = 0;
	char verif_naipe;
	int verif_valor;
	int naipe_set;
	contador c1;
	
	for(c1 = 1; c1 <= n_seq; c1++){
		
		contador c2;
		
		for (c2 = 0; c2 < n_cartas; c2++){
			if(cartas[c2].indice_seq == c1){
				max_pos++;
			}
		}
		
		if((max_pos > 0) && (max_pos < 3)){
			printf("Movimento invalido! Todas as sequencias devem ter 3 cartas ou mais!\n\n");
			return 0;
		}
		
		naipe_set = 0;
		
		for (c2 = 0; c2 < n_cartas; c2++){
			if(cartas[c2].indice_seq == c1){
				if(naipe_set == 0){
					if (cartas[c2].conteudo[1] != '*'){
						verif_naipe = cartas[c2].conteudo[1];
						naipe_set = 1;
					}
				} else {
					if(cartas[c2].conteudo[1] != verif_naipe){
						if(cartas[c2].conteudo[1] != '*'){
							printf("Movimento invalido! Todas as cartas de uma sequencia devem ter o mesmo naipe!\n\n");
							printf("%c%c\n", cartas[c2].conteudo[0], cartas[c2].conteudo[1]);
							return 0;
						}
					}
				}
			}
		}
		
		int flag = 0;

		for (c2 = 1; c2 <= max_pos; c2++){
			contador c3;
			for (c3 = 0; c3 < n_cartas; c3++){
				if(cartas[c3].indice_seq == c1){
					if(cartas[c3].pos_seq == c2){
						if(!flag){
							if(cartas[c3].conteudo[0] != '*'){
								if((cartas[c3].conteudo[0] <= '9') && (cartas[c3].conteudo[0] >= '1')){
									verif_valor = cartas[c3].conteudo[0];
									flag = 1;
								} else {
									verif_valor = cartas[c3].conteudo[0] - 7;
									flag = 1;
								}
							}
						} else {
							if((cartas[c3].conteudo[0] <= '9') && (cartas[c3].conteudo[0] >= '1')){
								if((cartas[c3].conteudo[0] - verif_valor) == 1){
									verif_valor = cartas[c3].conteudo[0];
								} else {
									printf("Movimento invalido! Todas as cartas de uma sequencia devem estar ordenadas!\n\n");
									return 0;
								}
							} else if (cartas[c3].conteudo[0] == '*'){
								verif_valor++;
							} else if (((cartas[c3].conteudo[0] - 7) - verif_valor) == 1){
								verif_valor = (cartas[c3].conteudo[0] - 7);
							} else {
								printf("Movimento invalido! Todas as cartas de uma sequencia devem estar ordenadas!\n\n");
								return 0;
							}
						}
					}
				}
			}
		}
	}
	
	//Verificar grupos
	
	naipe_set = 0;
	char verif_naipe2;
	char verif_naipe3;
	int naipe_set2 = 0;
	int naipe_set3 = 0;
	int valor_set = 0;
	
	for(c1 = 1; c1 <= n_grupos; c1++){
		
		int quant = 0;
		
		contador c2;
		
		for(c2 = 0; c2 < n_cartas; c2++){
			if(cartas[c2].indice_grupo == c1){
				quant++;
			}
		}
		
		if((quant != 0) && ((quant != 4) && (quant != 3))){
			printf("Movimento invalido! Todos os grupos devem ter 3 ou 4 cartas!\n\n");
			return 0;
		}
		
		for(c2 = 0; c2 < n_cartas; c2++){
			if(cartas[c2].indice_grupo == c1){
				if(!naipe_set){
					if (cartas[c2].conteudo[1] != '*'){
						verif_naipe = cartas[c2].conteudo[1];
						naipe_set = 1;
					}
				} else if(!naipe_set2){
					if((cartas[c2].conteudo[1] == verif_naipe) && (cartas[c2].conteudo[1] != '*')){
						printf("Movimento invalido! Todas as cartas de um grupo devem ter naipes diferentes!\n\n");
						return 0;
					}
					verif_naipe2 = cartas[c2].conteudo[1];
					naipe_set2 = 1;
				} else if(!naipe_set3){
					if(((cartas[c2].conteudo[1] == verif_naipe) || (cartas[c2].conteudo[1] == verif_naipe2)) && (cartas[c2].conteudo[1] != '*')){
						printf("Movimento invalido! Todas as cartas de um grupo devem ter naipes diferentes!\n\n");
						return 0;
					}
					verif_naipe3 = cartas[c2].conteudo[1];
					naipe_set3 = 1;
				} else if(((cartas[c2].conteudo[1] == verif_naipe) || (cartas[c2].conteudo[1] == verif_naipe2)) && (cartas[c2].conteudo[1] != '*')){
					printf("Movimento invalido! Todas as cartas de um grupo devem ter naipes diferentes!\n\n");
					return 0;
				} else if((cartas[c2].conteudo[1] == verif_naipe3) && (cartas[c2].conteudo[1] != '*')){
					printf("Movimento invalido! Todas as cartas de um grupo devem ter naipes diferentes!\n\n");
					return 0;
				}
			}
		}
		
		valor_set = 0;
		
		for(c2 = 0; c2 < n_cartas; c2++){
			if(cartas[c2].indice_grupo == c1){
				if(!valor_set){
					verif_valor = cartas[c2].conteudo[0];
					valor_set = 1;
				} else {
					if((cartas[c2].conteudo[0] != verif_valor) && (cartas[c2].conteudo[0] != '*')){
						printf("Movimento invalido! Todas as cartas de um grupo devem ter o mesmo valor!\n\n");
						return 0;
					}
				}
			}
		}
	}
	
	return 1;
	
}


/*Função Mover_em_grupo: Adiciona uma carta a um grupo. É uma subfunção de Mover_Cartas().
  
  Entradas: *cartas: Vetor de structs, possui todas as cartas que já foram compradas e estão nas mãos dos jogadores ou no tabuleiro. 
  			indice_carta: Indica a posição ocupada pela carta no vetor de structs.
  			n_grupos: Indica a quantidade de grupos.
  			n_cartas: Indica o número de cartas que foram compradas e estão nas mãos dos jogadores ou no tabuleiro.
  
  Saídas: Nenhuma.
*/

void Mover_em_grupo(carta_j *cartas, int indice_carta, int n_grupos, int n_cartas){
	
	opc opc_mov;
	
	printf("Em qual grupo deseja colocar a carta?\n");
	opc_mov = getc(stdin);
	fflush(stdin);
	int ind_grupo;
	ind_grupo = (int) opc_mov - 48;
	
	while((ind_grupo > n_grupos) || (ind_grupo <= 0)){
		printf("Entrada invalida.\n");
		printf("Em qual grupo deseja colocar a carta?\n");
		opc_mov = getc(stdin);
		fflush(stdin);
		ind_grupo = (int) opc_mov - 48;
	}
	
	cartas[indice_carta].indice_grupo = ind_grupo;
	cartas[indice_carta].indice_seq = 0;
	cartas[indice_carta].pos_seq = 0;
	cartas[indice_carta].indice_mao = -1;
	printf("Carta adicionada com sucesso!\n\n");
}


/*Função Mover_em_seq: Adiciona uma carta a uma sequência. É uma subfunção de Mover_Cartas().
  
  Entradas: *cartas: Vetor de structs, possui todas as cartas que já foram compradas e estão nas mãos dos jogadores ou no tabuleiro. 
  			indice_carta: Indica a posição ocupada pela carta no vetor de structs.
  			n_seq: Indica a quantidade de sequências.
  			n_cartas: Indica o número de cartas que foram compradas e estão nas mãos dos jogadores ou no tabuleiro.
  
  Saídas: Nenhuma
*/

void Mover_em_seq(carta_j *cartas, int indice_carta, int n_seq, int n_cartas){
	
	opc opc_mov;
	
	printf("Em qual sequencia deseja colocar a carta?\n");
	opc_mov = getc(stdin);
	fflush(stdin);
	int ind_seq;
	ind_seq = (int) opc_mov - 48;
	
	while((ind_seq > n_seq) || (ind_seq <= 0)){
		printf("Entrada invalida.\n");
		printf("Em qual sequencia deseja colocar a carta?\n");
		opc_mov = getc(stdin);
		fflush(stdin);
		ind_seq = (int) opc_mov - 48;
	}
	
	int max_pos = 0;
	contador c1;
	
	for (c1 = 0; c1 < n_cartas; c1++){
		if(cartas[c1].indice_seq == ind_seq){
			max_pos++;
		}
	}
	
	if (!max_pos){
		cartas[indice_carta].indice_seq = ind_seq;
		cartas[indice_carta].pos_seq = 1;
		cartas[indice_carta].indice_mao = -1;
		cartas[indice_carta].indice_grupo = 0;
		printf("Carta adicionada com sucesso!\n\n");
	} else {
		printf("Em qual posicao deseja adicionar a carta?\n");
		opc_mov = getc(stdin);
		fflush(stdin);
		if((opc_mov > (max_pos + 49)) || (opc_mov < '1')){ // max_pos + 49 = max_pos + '1'
			printf("Posicao invalida! Leve em consideracao quantas cartas ja estao na sequencia.\n");
			printf("Em qual posicao deseja adicionar a carta?\n");
			opc_mov = getc(stdin);
			fflush(stdin);
		} else {
			for(c1 = 0; c1 < n_cartas; c1++){
				if(cartas[c1].indice_seq == ind_seq){
					if(cartas[c1].pos_seq >= (opc_mov - 48)){
						cartas[c1].pos_seq++;
					}
				}
			}
			cartas[indice_carta].indice_seq = ind_seq;
			cartas[indice_carta].pos_seq = (opc_mov - 48);
			cartas[indice_carta].indice_mao = -1;
			cartas[indice_carta].indice_grupo = 0;
			printf("Carta adicionada com sucesso!\n\n");
		}
	}
}

/*Função Mover_Cartas: É ativada sempre que o usuário deseja mover alguma carta, seja uma de sua mão ou uma que já esteja no tabuleiro.
					   Ela realiza o movimento caso ele seja válido.
  
  Entradas: *cartas: Vetor de structs, possui todas as cartas que já foram compradas e estão nas mãos dos jogadores ou no tabuleiro. 
  			n_cartas: Indica o número de cartas que foram compradas e estão nas mãos dos jogadores ou no tabuleiro.
  			indice_jogador: Indica qual jogador está realizando o movimento.
  			n_grupos: Indica a quantidade de grupos.
  			n_seq: Indica o número de sequências.
  			*carta_mao_usada: Ponteiro para inteiro. Aponta para uma flag que indica se o usuario colocou uma carta de sua mão no tabuleiro.
  
  Saídas: Nenhuma
*/

void Mover_Cartas(carta_j *cartas_orig, int n_cartas, int indice_jogador, int n_seq, int n_grupos, int *carta_mao_usada){

	int valido = 1;

	if((!n_seq) && (!n_grupos)){
		printf("Nao ha como mover cartas se nao ha grupos ou sequencias no tabuleiro!!\n\n");
		valido = 0;
	}

	carta_j *cartas;
	cartas = (carta_j *) malloc(n_cartas * sizeof(carta_j));
	if(!cartas){
		printf("Erro na alocacao dinamica de memoria!\n");
		getc(stdin);
		exit(1);
	}

	contador c;
	for(c = 0; c < n_cartas; c++){
		cartas[c] = cartas_orig[c];
	}

	while(valido){
		
		printf("A carta que deseja mover esta em:\n	1- Sua mao.\n	2- Uma sequencia.\n	3- Um grupo.\n");
		opc opc_mov;
		opc_mov = getc(stdin);
		fflush(stdin);
		int carta_existe = 0;
		int indice_carta;
		char carta_cmp[3];

		while((opc_mov > '3') && (opc_mov < '1')){
			printf("Opcao invalida!\n");
			printf("A carta que deseja mover esta em:\n	1- Sua mao.\n	2- Uma sequencia.\n	3- Um grupo.\n");
			opc_mov = getc(stdin);
			fflush(stdin);
		}
		
		contador c1;

		switch(opc_mov){
			
			case '1':
				printf("Digite o conteudo da carta (numero e naipe):\n");
				fgets(carta_cmp, 3, stdin);
				fflush(stdin);
				for(c1 = 0; c1 < n_cartas; c1++){
					if(cartas[c1].indice_mao == indice_jogador){
						if(cartas[c1].conteudo[0] == carta_cmp[0]){
							if (cartas[c1].conteudo[1] == carta_cmp[1]){
								carta_existe = 1;
								indice_carta = c1;
								break;
							}
						}
					}
				}
				if (!carta_existe){
					printf("A carta nao foi encontrada!\n");
					break;
				}
				printf("Aonde deseja colocar a carta?\n	1- Uma sequencia.\n	2- Um grupo.\n");
				opc_mov = getc(stdin);
				fflush(stdin);
				while((opc_mov != '1') && (opc_mov != '2')){
					printf("Opcao invalida!\n");
					printf("Aonde deseja colocar a carta?\n	1- Uma sequencia.\n	2- Um grupo.\n");
					opc_mov = getc(stdin);
					fflush(stdin);
				}
				if(opc_mov == '1'){
					if(!n_seq){
						printf("Nao ha sequencias no tabuleiro!!\n\n");
						break;
					}
					Mover_em_seq(cartas, indice_carta, n_seq, n_cartas);
					*carta_mao_usada = 1;
				} else {
					if(!n_grupos){
						printf("Nao ha grupos no tabuleiro!!\n\n");
						break;
					}
					Mover_em_grupo(cartas, indice_carta, n_grupos, n_cartas);
					*carta_mao_usada = 1;
				}
				break;
			
			case '2':;
				if(!n_seq){
					printf("Nao ha sequencias no tabuleiro!!\n\n");
					break;
				}
				int add_seq;
				int pos_add_seq;
				printf("Insira a sequencia aonde a carta esta no momento:\n");
				add_seq = getc(stdin) - 48;
				fflush(stdin);
				while((add_seq > n_seq) || (add_seq <= 0)){
					printf("Entrada invalida!\n");
					printf("Insira a sequencia aonde a carta esta no momento:\n");
					add_seq = getc(stdin) - 48;
					fflush(stdin);
				}
				printf("Insira a posicao na sequencia que a carta ocupa no momento:\n");
				pos_add_seq = getc(stdin) - 48;
				fflush(stdin);
				int max_pos = 0;
				for (c1 = 0; c1 < n_cartas; c1++){
					if(cartas[c1].indice_seq == add_seq){
						max_pos++;
					}
				}
				while((pos_add_seq > max_pos) || (pos_add_seq <= 0)){
					printf("Entrada invalida!\n");
					printf("Insira a posicao na sequencia que a carta ocupa no momento:\n");
					pos_add_seq = getc(stdin) - 48;
					fflush(stdin);
				}
				for(c1 = 0; c1 < n_cartas; c1++){
					if(cartas[c1].indice_seq == add_seq){
						if(cartas[c1].pos_seq == pos_add_seq){
							carta_existe = 1;
							indice_carta = c1;
							break;
						}
					}
				}
				if (!carta_existe){
					printf("A carta nao foi encontrada!\n");
					break;
				}
				printf("Aonde deseja colocar a carta?\n	1- Uma sequencia.\n	2- Um grupo.\n");
				opc_mov = getc(stdin);
				fflush(stdin);
				while((opc_mov != '1') && (opc_mov != '2')){
					printf("Opcao invalida!\n");
					printf("Aonde deseja colocar a carta?\n	1- Uma sequencia.\n	2- Um grupo.\n");
					opc_mov = getc(stdin);
					fflush(stdin);
				}
				if(opc_mov == '1'){
					Mover_em_seq(cartas, indice_carta, n_seq, n_cartas);
				} else {
					if(!n_grupos){
						printf("Nao ha grupos no tabuleiro!!\n\n");
						break;
					}
					Mover_em_grupo(cartas, indice_carta, n_grupos, n_cartas);
				}
				break;
			
			case '3':;
				if(!n_grupos){
					printf("Nao ha grupos no tabuleiro!!\n\n");
					break;
				}
				int add_grupo;
				printf("Insira o grupo aonde a carta esta no momento:\n");
				add_grupo = getc(stdin) - 48;
				fflush(stdin);
				while((add_grupo > n_grupos) || (add_grupo <= 0)){
					printf("Entrada invalida!\n");
					printf("Insira o grupo aonde a carta esta no momento:\n");
					add_grupo = getc(stdin) - 48;
					fflush(stdin);
				}
				printf("Digite o conteudo da carta (numero e naipe):\n");
				fgets(carta_cmp, 3, stdin);
				fflush(stdin);
				contador c1;
				for(c1 = 0; c1 < n_cartas; c1++){
					if(cartas[c1].indice_grupo == add_grupo){
						if(cartas[c1].conteudo[0] == carta_cmp[0]){
							if (cartas[c1].conteudo[1] == carta_cmp[1]){
								carta_existe = 1;
								indice_carta = c1;
								break;
							}
						}
					}
				}
				if (!carta_existe){
					printf("A carta nao foi encontrada!\n");
					break;
				}
				printf("Aonde deseja colocar a carta?\n	1- Uma sequencia.\n	2- Um grupo.\n");
				opc_mov = getc(stdin);
				fflush(stdin);
				while((opc_mov != '1') && (opc_mov != '2')){
					printf("Opcao invalida!\n");
					printf("Aonde deseja colocar a carta?\n	1- Uma sequencia.\n	2- Um grupo.\n");
					opc_mov = getc(stdin);
					fflush(stdin);
				}
				if(opc_mov == '1'){
					if(!n_seq){
						printf("Nao ha sequencias no tabuleiro!!\n\n");
						break;
					}
					Mover_em_seq(cartas, indice_carta, n_seq, n_cartas);
				} else {
					Mover_em_grupo(cartas, indice_carta, n_grupos, n_cartas);
				}
				break;
			
			default:;
		}
		
		printf("Deseja mover mais cartas? (lembre-se de mover as cartas de forma que o tabuleiro seja valido)\n	1- Sim.\n	2- Nao.\n");
		opc opc_continuar;
		opc_continuar = getc(stdin);
		fflush(stdin);
		
		while((opc_continuar != '1') && (opc_continuar != '2')){
			printf("Opcao invalida!\n");
			printf("Deseja mover mais cartas? (lembre-se de mover as cartas de forma que o tabuleiro seja valido)\n	1- Sim.\n	2- Nao.");
			opc_continuar = getc(stdin);
			fflush(stdin);
		}
		
		if(opc_continuar == '2'){
			break;
		}
	}

	if(Verificar_Tabuleiro(cartas, n_grupos, n_seq, n_cartas)){
		for(c = 0; c < n_cartas; c++){
			cartas_orig[c] = cartas[c];
		}
	} else {
		*carta_mao_usada = 0;
	}

	free(cartas);
}


/*Função Comprar_Carta:
  
  Entradas: *baralho: Vetor de char, possui todas as cartas do baralho.
  			indice_jogador: Indica qual jogador está realizando a compra da carta.
  			*cartas: Vetor de structs, possui todas as cartas que já foram compradas e estão nas mãos dos jogadores ou no tabuleiro.
			n_cartas: Indica o número de cartas que foram compradas e estão nas mãos dos jogadores ou no tabuleiro.
  
  Saídas: Retorna um ponteiro para struct, devido a realocação.
*/

carta_j* Comprar_Carta(char *baralho, int indice_jogador, carta_j *cartas, int n_cartas){
	
	if(n_cartas == 0){
		cartas = (carta_j *) malloc(sizeof(carta_j));
		if(!cartas){
			printf("Erro na alocacao dinamica de memoria!\n");
			getc(stdin);
			exit(1);
		}
	} else {
		cartas = (carta_j *) realloc(cartas, (n_cartas + 1) * (sizeof(carta_j)));
		if(!cartas){
			printf("Erro na alocacao dinamica de memoria!\n");
			getc(stdin);
			exit(1);
		}
	}
	
	cartas[n_cartas].conteudo[0] = baralho[2*n_cartas];
	cartas[n_cartas].conteudo[1] = baralho[(2*n_cartas)+1];
	cartas[n_cartas].indice_seq = 0;
	cartas[n_cartas].indice_grupo = 0;
	cartas[n_cartas].pos_seq = 0;
	cartas[n_cartas].indice_mao = indice_jogador;
	
	return cartas;
}


/*Função Baralho_Aleatorio: Ativada quando o usuário decide utilizar um baralho aleatório ao invés de um arquivo.
  
  Entradas: *baralho: Vetor de char, possui todas as cartas do baralho.
  			*carta: Vetor de char, possui uma única carta.
  
  Saídas: Nenhuma.
*/

void Baralho_Aleatorio(char *baralho, char *carta){
	
	contador c1;
	contador c2;
	
	srand((unsigned) time(NULL)); // Seed para o rand() baseada em tempo.
	
	for(c1 = 0; c1 < 106; c1++){
		
		int repetido = 1;
		
		while(repetido){
			int randn;
			randn = rand() % 52;
			if(randn == 0){
				carta[0] = carta[1] = '*';
			} else{
				randn = rand() % 4;
				switch(randn){
				case 0:
					carta[1] = '!';
					break;
				case 1:
					carta[1] = '@';
					break;
				case 2:
					carta[1] = '#';
					break;
				case 3:
					carta[1] = '&';
				}

				// Ao ler a próxima parte, lembre-se que as cartas vão de 1 a 9 e A a D.
				// Os valores de rand de 0 a 8 viram 1 a 9, e os de 9 a 12 viram A a D.
				// Não se esqueça que a adição é devido a posição dos caracteres na tabela ASCII.
				// Não foi utilizado else pra ficar mais fácil de ler.
				
				randn = rand() % 13;
				if (randn <= 8){
					carta[0] = (char)(randn + 49);
				}
				if (randn >= 9){
					carta[0] = (char)(randn + 56);
				}
			}
			
			repetido = 0;
			int repetido1 = 0;

			for (c2 = 0; c2 < 106; c2++){
				if (baralho[2*c2] == carta[0]){
					if (baralho[(2*c2)+1] == carta[1]){
						if (!repetido1){
							repetido1 = 1;
						} else repetido = 1;
					}
				}
			}

		}
		
		baralho[2*c1] = carta[0];
		baralho[(2*c1)+1] = carta[1];

	}
}


/*Função Ler_Baralho: Ativada quando o usuário deseja utilizar o baralho encontrado em um arquivo.
  
  Entradas: *f_read: Ponteiro para arquivo.
  			*baralho: Vetor de char, possui todas as cartas do baralho. 
  
  Saídas: Retorna 1 se o baralho lido for válido, e 0 se ele não o for.
*/

int Ler_Baralho(FILE *f_read, char *baralho){
	
	contador c1;
	printf("Insira o nome do arquivo (limite de 30 caracteres):\n");
	char nome_arquivo[31];
	fgets(nome_arquivo,30,stdin);
	fflush(stdin);
	for(c1=0; c1 < 31; c1++){
		if(nome_arquivo[c1] == '\n'){
			nome_arquivo[c1] = '\0';
		}
	}

	f_read = fopen(nome_arquivo,"r");
	if (!f_read){
		printf("Erro na abertura do arquivo!\n");
		getc(stdin);
		exit(1);
	}

	char leitura;

	c1 = 0;

	do {
		leitura = (char) fgetc(f_read); //As partes a seguir são para garantir que nenhum caractere
		fflush(stdin);					//diferente dos usados no baralho entrará na string.
		if ((leitura >= '0') && (leitura <= '9')){
			baralho[c1] = leitura;
			c1++;
		} else if ((leitura >= 'A') && (leitura <= 'D')){
			baralho[c1] = leitura;
			c1++;
		} else {
			switch(leitura){
			case '!':
				baralho[c1] = leitura;
				c1++;
				break;
			case '@':
				baralho[c1] = leitura;
				c1++;
				break;
			case '#':
				baralho[c1] = leitura;
				c1++;
				break;
			case '&':
				baralho[c1] = leitura;
				c1++;
				break;
			case '*':
				baralho[c1] = leitura;
				c1++;
				break;
			default:;
			}
		}
	} while ((leitura != EOF) && (c1 != 212));

	if(c1 < 212){
		printf("Nao ha cartas o suficiente no arquivo ou ele esta mal formatado.\nEscolha utilizar outro arquivo ou um baralho aleatorio.\n\n");
		fclose(f_read);
		return 1; // A função retorna um valor para a flag invalido, então 1 significa que o loop continuará.
	}

	fclose(f_read);
	return 0;
}


/*Função Rodada: Controla as rodadas do jogo. É a função megazord, só que não.
  
  Entradas: n_jogadores: Indica o total de jogadores.
  			n_rodadas: Indica quantas rodadas já se passaram.
  			*carta_mao_usada: Ponteiro para inteiro. Aponta para uma flag que indica se o usuario colocou uma carta de sua mão no tabuleiro.
  			*cartas: Vetor de structs, possui todas as cartas que já foram compradas e estão nas mãos dos jogadores ou no tabuleiro.
  			*n_grupos: Ponteiro para inteiro. Aponta para um inteiro que indica o número de grupos.
  			*n_seq: Ponteiro para inteiro. Aponta para um inteiro que indica o número de sequências.
  			*n_cartas: Ponteiro para inteiro. Aponta para um inteiro que indica o número de cartas nas mãos dos jogadores ou no tabuleiro.
  			*baralho: Vetor de char, possui todas as cartas do baralho.
  			*v: Ponteiro para inteiro. Aponta para uma flag que indica se a vitória foi atingida ou não.
  
  Saídas:
*/

carta_j *Rodada(int n_jogadores, int n_rodadas, int *carta_mao_usada, carta_j *cartas, int *n_grupos, int *n_seq, int *n_cartas, char *baralho, int *v){
	
	int vazio = 0;
	contador c1;
	opc opc_jogo;
	carta_mao_usada = 0;
	int *usada;
	usada = (int *) &carta_mao_usada;
	printf("E sua vez Jogador %d! ", (n_rodadas % n_jogadores) + 1);
	int invalido = 1;
	
	while (invalido){
		
		printf("\n");
		
		for(c1 = 1; c1 <= n_jogadores; c1++){
			printf("Cartas do jogador %d:", c1);
			contador c2;
			for (c2 = 0; c2 < *n_cartas; c2++){
				if(cartas[c2].indice_mao == c1 - 1){
					printf(" %c%c", cartas[c2].conteudo[0], cartas[c2].conteudo[1]);
				}
			}
			printf("\n");
		}
		
		printf("\nTabuleiro:\n");
		
		for(c1 = 1; c1 <= *n_grupos; c1++){
			printf("	Grupo %d:", c1);
			contador c2;
			for (c2 = 0; c2 < *n_cartas; c2++){
				if(cartas[c2].indice_grupo == c1){
					printf(" %c%c", cartas[c2].conteudo[0], cartas[c2].conteudo[1]);
				}
			}
			printf("\n");
		}
		
		for(c1 = 1; c1 <= *n_seq; c1++){
			printf("	Sequencia %d:", c1);
			contador c2;
			int total = 0;
			for (c2 = 0; c2 < *n_cartas; c2++){
				if(cartas[c2].indice_seq == c1){
					total++;
				}
			}
			for (c2 = 1; c2 <= total; c2++){
				contador c3;
				for (c3 = 0; c3 < *n_cartas; c3++){
					if(cartas[c3].indice_seq == c1){
						if(cartas[c3].pos_seq == c2){
							printf(" %c%c", cartas[c3].conteudo[0], cartas[c3].conteudo[1]);
						}
					}
				}
			}
			printf("\n");
		}
		
		printf("\n");

		printf("Escolha uma das opcoes a seguir:\n	1- Adicionar grupo.\n	2- Adicionar sequencia.\n	3- Mover ou adicionar cartas no tabuleiro.\n	4- Remover ultima sequencia ou grupo (obs: ele(a) deve estar vazio(a)).\n	5- Comprar uma carta e passar a vez.\n	6- Terminar seu turno (obs: uma carta de sua mao deve ser colocada no tabuleiro)\n");
		opc_jogo = getc(stdin);
		fflush(stdin);
		
		switch(opc_jogo){
			
			case '1':
				(*n_grupos)++;
				printf("\n");
				break;
			
			case '2':
				(*n_seq)++;
				printf("\n");
				break;
			
			case '3':
				Mover_Cartas(cartas, *n_cartas, n_rodadas % n_jogadores, *n_seq, *n_grupos, usada);
				break;
			
			case '4':
				printf("Remover:\n	1- Sequencia.\n	2- Grupo.\n");
				opc_jogo = getc(stdin);
				fflush(stdin);
				
				while((opc_jogo > '2') || (opc_jogo < '1')){
					printf("Valor invalido!\n\n");
					printf("Remover:\n	1- Sequencia.\n	2- Grupo.\n");
					opc_jogo = getc(stdin);
					fflush(stdin);
				}
				
				if(opc_jogo == '1'){
					if(!(*n_seq)){
						printf("Nao ha sequencias no tabuleiro.\n\n");
						break;
					}
					int flag1 = 0;
					for(c1 = 0; c1 < *n_cartas; c1++){
						if(cartas[c1].indice_seq == *n_seq){
							flag1 = 1;
						}
					}
					if(flag1){
						printf("Ainda ha cartas nessa sequencia! Remova elas antes de deleta-la.\n\n");
						break;
					} else {
						(*n_seq)--;
						printf("Sequencia removida.\n\n");
						break;
					}
				}
				
				if(opc_jogo == '2'){
					if(!(*n_grupos)){
						printf("Nao ha grupos no tabuleiro.\n\n");
						break;
					}
					int flag1 = 0;
					for(c1 = 0; c1 < *n_cartas; c1++){
						if(cartas[c1].indice_grupo == *n_grupos){
							flag1 = 1;
						}
					}
					if(flag1){
						printf("Ainda ha cartas nesse grupo! Remova elas antes de deleta-lo.\n\n");
						break;
					} else {
						(*n_grupos)--;
						printf("Grupo removido.\n\n");
						break;
					}
				}
				break;
			
			case '5':
				if(carta_mao_usada){
					printf("Voce utilizou uma carta de sua mao, termine o turno normalmente em vez de comprar uma carta.\n\n");
					break;
				}
				
				vazio = 1;
				
				for(c1 = 1; c1 <= *n_seq; c1++){
					vazio = 0;
					contador c2;
					for (c2 = 0; c2 < *n_cartas; c2++){
						if(cartas[c2].indice_seq == c1){
							vazio = 1;
						}
					}
					if(!vazio){
						printf("Nao deixe grupos ou sequencias vazias antes de terminar seu turno.\n\n");
						break;
					}
				}
				
				if(!vazio){
					break;
				}
				
				for (c1 = 1; c1 <= *n_grupos; c1++){
					vazio = 0;
					contador c2;
					for (c2 = 0; c2 < *n_cartas; c2++){
						if(cartas[c2].indice_grupo == c1){
							vazio = 1;
						}
					}
					if(!vazio){
						printf("Nao deixe grupos ou sequencias vazias antes de terminar seu turno.\n\n");
						break;
					}
				}
				
				if(!vazio){
					break;
				}
				
				cartas = Comprar_Carta(baralho, n_rodadas % n_jogadores, cartas, *n_cartas);
				(*n_cartas)++;
				invalido = 0;
				break;
			
			case '6':
				vazio = 1;
				
				for(c1 = 1; c1 <= *n_seq; c1++){
					vazio = 0;
					contador c2;
					for (c2 = 0; c2 < *n_cartas; c2++){
						if(cartas[c2].indice_seq == c1){
							vazio = 1;
						}
					}
					if(!vazio){
						printf("Nao deixe grupos ou sequencias vazias antes de terminar seu turno.\n\n");
						break;
					}
				}
				
				if(!vazio){
					break;
				}
				
				for (c1 = 1; c1 <= *n_grupos; c1++){
					vazio = 0;
					contador c2;
					for (c2 = 0; c2 < *n_cartas; c2++){
						if(cartas[c2].indice_grupo == c1){
							vazio = 1;
						}
					}
					if(!vazio){
						printf("Nao deixe grupos ou sequencias vazias antes de terminar seu turno.\n\n");
						break;
					}
				}
				
				if(!vazio){
					break;
				}
				
				if(!carta_mao_usada){
					printf("Nao e possivel terminar seu turno sem colocar pelo menos uma carta de sua mao no tabuleiro.\nColoque uma carta no tabuleiro ou compre uma carta.\n\n");
					break;
				}
				
				invalido = 0;
				
				*v = 1;
				for(c1 = 0; c1 < *n_cartas; c1++){
					if(cartas[c1].indice_mao == n_rodadas % n_jogadores){
						*v = 0;
						break;	
					}
				}
				
				break;
		}
	}

	return cartas;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


int main(){
	
/* Declaração das variáveis do main e alocações */
	
	int start = 0;
	
	FILE *f_read = NULL;

	char *baralho = (char *) calloc(106 * 2, sizeof(char));
	char carta[2];
	
	carta_j *cartas = NULL;

	int n_jogadores = 0; //Número de jogadores.
	int n_cartas = 0; //Número de cartas que não estão no baralho.
	int n_rodadas = 0; //Número de rodadas que já se passaram.
	int n_grupos = 0; //Número de grupos.
	int n_seq = 0; //Número de sequências.

	contador c1; //Contador geral para for.

	opc opc_baralho; //Variáveis de controle para as opções que o usuário selecionar.
	opc opc_jogadores;
	opc opc_jogo;

	int invalido = 1; //Flag de controle para whiles.
	int vitoria = 0; //Indica se a vitória já foi atingida.
	int carta_mao_usada = 0; //Indica se o jogador já colocou uma carta de sua mão no tabuleiro durante a rodada.
	int vazio; //Flag que indica se o grupo ou sequência que está sendo avaliado está vazio.

	int aux = 0;
	int vit_sc[2] = {0, 9999};
	
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	
	printf("\n\t RRRRRRRRR                                                    OOO   KKK                  BBB");
	printf("\n\t  RRR   RRR                                                   OOO KKKKK                BBBBB");
	printf("\n\t  RRR    RRR   U     U      M                 M                    KKK         U     U  BBB");
	printf("\n\t  RRR   RRR   UU    UU     MM MMM   MMM      MM MMM   MMM     III  KKKKKKK    UU    UU  BBBBBBBB");
	printf("\n\t  RRRRRRRR  UUUU  UUUU   MMMMMMMMMMMMMMMM  MMMMMMMMMMMMMMMM  IIII  KKK  KKK UUUU  UUUU  BBB   BBB");
	printf("\n\t  RRR  RRR   UUU   UUU    MMM   MMM   MMM   MMM   MMM   MMM   III  KKKKKKK   UUU   UUU  BBB    BB");
	printf("\n\t  RRR   RRR  UUUU UUUU    MMM   MMM   MMM   MMM   MMM   MMM   III  KKK  KKK  UUUU UUUU  BBB   BBB");
	printf("\n\t RRRRR   RRR UUUUUU UUU  MMMMM MMMMM MMMMMMMMMMM MMMMM MMMMMIIIII KKKKK  KKK UUUUUU UUU BBBBBBBB");
	printf("\n\t          RRR        RR");
	printf("\n\t           RRRR    RRR");
	printf("\n\t            RRRRRRRRR");
	
	
	printf("\n\n\n\t\t\t\t\t     Pressione 1 para Jogar\n\n\t\t\t\t\t     Pressione 0 para Sair\n\n\t\t\t\t\t           --> ");
	
	scanf("%d", &start);
	
	while(start < 0 || start > 1){
		printf("\n\t\t\t\t\t     Comando invalido... Tente novamente\n\n\t\t\t\t\t           --> ");
		scanf("%d", &start);
	}
	
	while(start){
		
		system("cls");
		
		//Modo de jogo
		
		while(invalido){
			printf("\n\t\t\t\t\t        Modo de jogo\n\n\t\t\t\t\t       1 - Aleatorio\n\t\t\t\t\t       2 - Controlado\n\n\t\t\t\t\t           --> ");
			opc_baralho = getc(stdin);
			fflush(stdin);
			switch(opc_baralho){
				case '1':
					Baralho_Aleatorio(baralho, carta);
					invalido = 0;
					break;
				case '2':
					invalido = Ler_Baralho(f_read, baralho);
					break;
				default:
					printf("\n\t\t\t\t\t     Comando invalido... Tente novamente\n\n\t\t\t\t\t           --> ");
			}
		}
		
		//Número de jogadores
		
		invalido = 1;
		while(invalido){
			printf("\n\t\t\t\t\t     Numero de jogodores\n\n\t\t\t\t\t    1 Jogador (Solitaire)\n\t\t\t\t\t         2 Jogadores\n\t\t\t\t\t         3 Jogadores\n\t\t\t\t\t         4 Jogadores\n\t\t\t\t\t         5 Jogadores\n\n\t\t\t\t\t           --> ");
			opc_jogadores = getc(stdin);
			fflush(stdin);
			n_jogadores = opc_jogadores - 48;
			if((n_jogadores > 5) || (n_jogadores < 1)){
				printf("\n\t\t\t\t\t     Comando invalido... Tente novamente\n\n\t\t\t\t\t           --> ");
			} else invalido = 0;
		}
		
		
		//Jogo
		
		for(c1 = 0; c1 < (n_jogadores * 14); c1++, n_cartas++){
			cartas = Comprar_Carta(baralho, c1 % n_jogadores, cartas, n_cartas);
		}

		n_rodadas = 0;
	
		while((!vitoria) && (n_cartas != 106)){
			cartas = Rodada(n_jogadores, n_rodadas, &carta_mao_usada, cartas, &n_grupos, &n_seq, &n_cartas, baralho, &vitoria);
	
			n_rodadas++;
		}
	
		getc(stdin);
		
		if(vitoria){
			n_rodadas--;
			printf("Jogador %d venceu!!!", (n_rodadas % n_jogadores) + 1);
		}
		
		if(n_cartas == 106){
			contador c2;
			n_rodadas--;
			printf("Acabaram as cartas... Fim de jogo! Ganha quem tiver menos pontos!!!");
			for(c1 = 0; c1 < n_jogadores; c1++){
				aux = 0;
				for(c2 = 0; c2 < 106; c2++){
					if(cartas[c2].indice_mao == c1){
						if(cartas[c2].conteudo[0] <= '9'){
							aux += ((int)cartas[c2].conteudo[0] - 48);
						}else aux += ((int)cartas[c2].conteudo[0] - 55);
					}
				}
				if(aux < vit_sc[1]){
					vit_sc[0] = (c1 + 1);
					vit_sc[1] = aux;
				}
			}
			printf("O vencedor foi %d!!!", vit_sc[0]);
		}
		
		
		free(cartas);
		free(baralho);		
			
		
		//Reiniciar o jogo
			
		printf("\n\t\t\t\t\t    Deseja jogar novamente?\n\n\t\t\t\t\t     Pressione 1 para Sim\n\t\t\t\t\t     Pressione 0 para Nao\n\n\t\t\t\t\t           --> ");
		scanf("%d", &start);
		
		while(start < 0 || start > 1){
			printf("\n\t\t\t\t\t     Comando invalido... Tente novamente\n\n\t\t\t\t\t           --> ");
			scanf("%d", &start);
		}
		
		if(start == 1){

			f_read = NULL;
		
			baralho = (char *) calloc(106 * 2, sizeof(char));
						
			cartas = NULL;
		
			n_jogadores = 0;
			n_cartas = 0;
			n_rodadas = 0;
			n_grupos = 0;
			n_seq = 0;
		
			invalido = 1;
			vitoria = 0;
			carta_mao_usada = 0;
				
			aux = 0;
			vit_sc[0] = 0;
			vit_sc[1] = 9999;
			
		}
			
	}
	
	return(0);
}
