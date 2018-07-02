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
			printf("\n\t\t\t\t\t     Movimento invalido... As sequencias devem ter no minimo 3 cartas!!!");
			getc(stdin);
			fflush(stdin);
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
							printf("\n\t\t\t\t\t     Movimento invalido... As cartas de uma sequencia devem ter o mesmo naipe!!!");
							getc(stdin);
							fflush(stdin);
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
									printf("\n\t\t\t\t\t     Movimento invalido... As cartas de uma sequencia devem estar ordenadas!!!");
									getc(stdin);
									fflush(stdin);
									return 0;
								}
							} else if (cartas[c3].conteudo[0] == '*'){
								verif_valor++;
							} else if (((cartas[c3].conteudo[0] - 7) - verif_valor) == 1){
								verif_valor = (cartas[c3].conteudo[0] - 7);
							} else {
								printf("\n\t\t\t\t\t     Movimento invalido... As cartas de uma sequencia devem estar ordenadas!!!");
								getc(stdin);
								fflush(stdin);
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
			printf("\n\t\t\t\t\t     Movimento invalido... Os grupos devem ter 3 ou 4 cartas!!!");
			getc(stdin);
			fflush(stdin);
			return 0;
		}
		
		naipe_set = 0;
		naipe_set2 = 0;
		naipe_set3 = 0;

		for(c2 = 0; c2 < n_cartas; c2++){
			if(cartas[c2].indice_grupo == c1){
				if(!naipe_set){
					if (cartas[c2].conteudo[1] != '*'){
						verif_naipe = cartas[c2].conteudo[1];
						naipe_set = 1;
					}
				} else if(!naipe_set2){
					if((cartas[c2].conteudo[1] == verif_naipe) && (cartas[c2].conteudo[1] != '*')){
						printf("\n\t\t\t\t\t     Movimento invalido... As cartas de um grupo devem ter naipes diferentes!!!");
						getc(stdin);
						fflush(stdin);
						return 0;
					}
					verif_naipe2 = cartas[c2].conteudo[1];
					naipe_set2 = 1;
				} else if(!naipe_set3){
					if(((cartas[c2].conteudo[1] == verif_naipe) || (cartas[c2].conteudo[1] == verif_naipe2)) && (cartas[c2].conteudo[1] != '*')){
						printf("\n\t\t\t\t\t     Movimento invalido... As cartas de um grupo devem ter naipes diferentes!!!");
						getc(stdin);
						fflush(stdin);
						return 0;
					}
					verif_naipe3 = cartas[c2].conteudo[1];
					naipe_set3 = 1;
				} else if(((cartas[c2].conteudo[1] == verif_naipe) || (cartas[c2].conteudo[1] == verif_naipe2)) && (cartas[c2].conteudo[1] != '*')){
					printf("\n\t\t\t\t\t     Movimento invalido... As cartas de um grupo devem ter naipes diferentes!!!");
					getc(stdin);
					fflush(stdin);
					return 0;
				} else if((cartas[c2].conteudo[1] == verif_naipe3) && (cartas[c2].conteudo[1] != '*')){
					printf("\n\t\t\t\t\t     Movimento invalido... As cartas de um grupo devem ter naipes diferentes!!!");
					getc(stdin);
					fflush(stdin);
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
						printf("\n\t\t\t\t\t     Movimento invalido... Todas as cartas de um grupo devem ter o mesmo valor!!!");
						getc(stdin);
						fflush(stdin);
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
	
	char a[3] = { '0', '\n', '\0'};
	printf("\n\t\t\t\t\t     Em qual grupo deseja colocar a carta?\n\n\t\t\t\t\t           --> ");
	fgets(a, 3, stdin);
	fflush(stdin);
	int ind_grupo;
	ind_grupo = atoi(a);
	
	while((ind_grupo > n_grupos) || (ind_grupo <= 0)){
		printf("\n\n\t\t\t\t\t     Comando invalido... Tente novamente --> ");
		fgets(a, 3, stdin);
		fflush(stdin);
		ind_grupo = atoi(a);
	}
	
	cartas[indice_carta].indice_grupo = ind_grupo;
	cartas[indice_carta].indice_seq = 0;
	cartas[indice_carta].pos_seq = 0;
	cartas[indice_carta].indice_mao = -1;
	printf("\n\t\t\t\t\t     Carta adicionada com sucesso!!!");
}


/*Função Mover_em_seq: Adiciona uma carta a uma sequência. É uma subfunção de Mover_Cartas().
  
  Entradas: *cartas: Vetor de structs, possui todas as cartas que já foram compradas e estão nas mãos dos jogadores ou no tabuleiro. 
  			indice_carta: Indica a posição ocupada pela carta no vetor de structs.
  			n_seq: Indica a quantidade de sequências.
  			n_cartas: Indica o número de cartas que foram compradas e estão nas mãos dos jogadores ou no tabuleiro.
  
  Saídas: Nenhuma
*/

void Mover_em_seq(carta_j *cartas, int indice_carta, int n_seq, int n_cartas){
	
	char a[3] = {'0', '\n', '\0'};

	printf("\n\t\t\t\t\t     Em qual sequencia deseja colocar a carta?\n\n\t\t\t\t\t           --> ");
	fgets(a, 3, stdin);
	fflush(stdin);
	int ind_seq;
	ind_seq = atoi(a);
	int ind_pos;
	
	while((ind_seq > n_seq) || (ind_seq <= 0)){
		printf("\n\n\t\t\t\t\t     Comando invalido... Tente novamente --> ");
		fgets(a, 3, stdin);
		fflush(stdin);
		ind_seq = atoi(a);
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
		printf("\n\t\t\t\t\t     Carta adicionada com sucesso!!!");
	} else {
		printf("\n\t\t\t\t\t     Em qual posicao deseja adicionar a carta?\n\n\t\t\t\t\t           --> ");
		fgets(a, 3, stdin);
		fflush(stdin);
		ind_pos = atoi(a);
		if((ind_pos > (max_pos + 1)) || (ind_pos < 1)){
			printf("\n\t\t\t\t\t     Posicao invalida... Leve em consideracao quantas cartas ja estao na sequencia.");
			printf("\n\n\t\t\t\t\t     Tente novamente --> ");
			fgets(a, 3, stdin);
			fflush(stdin);
			ind_pos = atoi(a);
		} else {
			for(c1 = 0; c1 < n_cartas; c1++){
				if(cartas[c1].indice_seq == ind_seq){
					if(cartas[c1].pos_seq >= ind_pos){
						cartas[c1].pos_seq++;
					}
				}
			}
			cartas[indice_carta].indice_seq = ind_seq;
			cartas[indice_carta].pos_seq = ind_pos;
			cartas[indice_carta].indice_mao = -1;
			cartas[indice_carta].indice_grupo = 0;
			printf("\n\t\t\t\t\t     Carta adicionada com sucesso!!!");
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
		printf("\n\t\t\t\t\t     Impossivel mover cartas... Nao ha grupos ou sequencias no tabuleiro!!!");
		valido = 0;
	}

	carta_j *cartas;
	cartas = (carta_j *) malloc(n_cartas * sizeof(carta_j));
	if(!cartas){
		printf("\n\t\t\t\t\t     Erro na alocacao dinamica de memoria!!!");
		getc(stdin);
		exit(1);
	}

	contador c;
	for(c = 0; c < n_cartas; c++){
		cartas[c] = cartas_orig[c];
	}

	while(valido){
		
		printf("\n\t\t\t\t\t     Selecionar carta\n\n\t\t\t\t\t     1 - Mao\n\t\t\t\t\t     2 - Sequencia\n\t\t\t\t\t     3 - Grupo\n\n\t\t\t\t\t           --> ");
		opc opc_mov;
		opc_mov = getc(stdin);
		fflush(stdin);
		int carta_existe = 0;
		int indice_carta;
		char carta_cmp[3];

		while((opc_mov > '3') && (opc_mov < '1')){
			printf("\n\n\t\t\t\t\t     Comando invalido... Tente novamente --> ");
			opc_mov = getc(stdin);
			fflush(stdin);
		}
		
		contador c1;

		switch(opc_mov){
			
			case '1':
				printf("\n\t\t\t\t\t     Insira a carta (numero e naipe) --> ");
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
					printf("\n\t\t\t\t\t     A carta nao foi encontrada!!!");
					break;
				}
				printf("\n\t\t\t\t\t     Posicionar carta\n\n\t\t\t\t\t     1 - Sequencia\n\t\t\t\t\t     2- Grupo\n\n\t\t\t\t\t           --> ");
				opc_mov = getc(stdin);
				fflush(stdin);
				while((opc_mov != '1') && (opc_mov != '2')){
					printf("\n\t\t\t\t\t     Comando invalido... Tente novamente --> ");
					opc_mov = getc(stdin);
					fflush(stdin);
				}
				if(opc_mov == '1'){
					if(!n_seq){
						printf("\n\t\t\t\t\t     Nao ha sequencias no tabuleiro!!!");
						break;
					}
					Mover_em_seq(cartas, indice_carta, n_seq, n_cartas);
					*carta_mao_usada = 1;
				} else {
					if(!n_grupos){
						printf("\n\t\t\t\t\t     Nao ha grupos no tabuleiro!!!");
						break;
					}
					Mover_em_grupo(cartas, indice_carta, n_grupos, n_cartas);
					*carta_mao_usada = 1;
				}
				break;
			
			case '2':;
				if(!n_seq){
					printf("\n\t\t\t\t\t     Nao ha sequencias no tabuleiro!!!");
					break;
				}
				char a[3] = {'0', '\n', '\0'};
				int add_seq;
				int pos_add_seq;
				printf("\n\t\t\t\t\t     Insira a sequencia na qual a carta se encontra --> ");
				fgets(a, 3 ,stdin);
				fflush(stdin);
				add_seq = atoi(a);
				while((add_seq > n_seq) || (add_seq <= 0)){
					printf("\n\n\t\t\t\t\t     Comando invalido... Tente novamente --> ");
					fgets(a, 3 ,stdin);
					fflush(stdin);
					add_seq = atoi(a);
				}
				printf("\n\t\t\t\t\t     Insira a posicao que a carta ocupa --> ");
				fgets(a, 3, stdin);
				fflush(stdin);
				pos_add_seq = atoi(a);
				int max_pos = 0;
				for (c1 = 0; c1 < n_cartas; c1++){
					if(cartas[c1].indice_seq == add_seq){
						max_pos++;
					}
				}
				while((pos_add_seq > max_pos) || (pos_add_seq <= 0)){
					printf("\n\n\t\t\t\t\t     Comando invalido... Tente novamente --> ");
					fgets(a, 3, stdin);
					fflush(stdin);
					pos_add_seq = atoi(a);
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
					printf("\n\t\t\t\t\t     A carta nao foi encontrada!!!");
					break;
				}
				printf("\n\t\t\t\t\t     Posicionar carta\n\n\t\t\t\t\t     1 - Sequencia\n\t\t\t\t\t     2- Grupo\n\n\t\t\t\t\t           --> ");
				opc_mov = getc(stdin);
				fflush(stdin);
				while((opc_mov != '1') && (opc_mov != '2')){
					printf("\n\n\t\t\t\t\t     Comando invalido... Tente novamente --> ");
					opc_mov = getc(stdin);
					fflush(stdin);
				}
				if(opc_mov == '1'){
					Mover_em_seq(cartas, indice_carta, n_seq, n_cartas);
				} else {
					if(!n_grupos){
						printf("\n\t\t\t\t\t     Nao ha grupos no tabuleiro!!!");
						break;
					}
					Mover_em_grupo(cartas, indice_carta, n_grupos, n_cartas);
				}
				break;
			
			case '3':;
				if(!n_grupos){
					printf("\n\t\t\t\t\t     Nao ha grupos no tabuleiro!!!");
					break;
				}
				char b[3] = {'0', '\n', '\0'};
				int add_grupo;
				printf("\n\t\t\t\t\t     Insira o grupo no qual a carta se encontra --> ");
				fgets(b, 3, stdin);
				fflush(stdin);
				add_grupo = atoi(b);
				while((add_grupo > n_grupos) || (add_grupo <= 0)){
					printf("\n\n\t\t\t\t\t     Comando invalido... Tente novamente --> ");
					fgets(b, 3, stdin);
					fflush(stdin);
					add_grupo = atoi(b);
				}
				printf("\n\t\t\t\t\t     Insira a carta (numero e naipe) --> ");
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
					printf("\n\t\t\t\t\t     A carta nao foi encontrada!!!");
					break;
				}
				printf("\n\t\t\t\t\t     Posicionar carta\n\n\t\t\t\t\t     1 - Sequencia\n\t\t\t\t\t     2- Grupo\n\n\t\t\t\t\t           --> ");
				opc_mov = getc(stdin);
				fflush(stdin);
				while((opc_mov != '1') && (opc_mov != '2')){
					printf("\n\n\t\t\t\t\t     Comando invalido... Tente novamente --> ");
					opc_mov = getc(stdin);
					fflush(stdin);
				}
				if(opc_mov == '1'){
					if(!n_seq){
						printf("\n\n\t\t\t\t\t     Nao ha sequencias no tabuleiro!!!");
						break;
					}
					Mover_em_seq(cartas, indice_carta, n_seq, n_cartas);
				} else {
					Mover_em_grupo(cartas, indice_carta, n_grupos, n_cartas);
				}
				break;
			
			default:;
		}
		
		printf("\n\t\t\t\t\t     Deseja mover mais cartas?\n\n\t\t\t\t\t     1 - Sim\n\t\t\t\t\t     2 - Nao\n\n\t\t\t\t\t           --> ");
		opc opc_continuar;
		opc_continuar = getc(stdin);
		fflush(stdin);
		
		while((opc_continuar != '1') && (opc_continuar != '2')){
			printf("\n\n\t\t\t\t\t     Comando invalido... Tente novamente --> ");
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
			printf("\n\t\t\t\t\t     Erro na alocacao dinamica de memoria!!!");
			getc(stdin);
			exit(1);
		}
	} else {
		cartas = (carta_j *) realloc(cartas, (n_cartas + 1) * (sizeof(carta_j)));
		if(!cartas){
			printf("\n\t\t\t\t\t     Erro na alocacao dinamica de memoria!!!");
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
	printf("\n\t\t\t\t\t     Insira o nome do arquivo (limite de 30 caracteres):\n");
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
		printf("\n\t\t\t\t\t     Erro na abertura do arquivo!!!");
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
		printf("\n\t\t\t\t\t     Nao ha cartas o suficiente no arquivo ou ele esta mal formatado.\n\t\t\t\t\t     Utilize outro arquivo ou um baralho aleatorio.\n\n");
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
	int invalido = 1;
	
	while (invalido){
		
		system("cls");
		
		
		printf("\n\t\t\t\t\t     Tabuleiro");
		printf("\n\t\t\t\t\t                   __________________________\n");
		
		for(c1 = 1; c1 <= *n_grupos; c1++){
			printf("\n\t\t\t\t\t         Grupo %d   ", c1);
			contador c2;
			for (c2 = 0; c2 < *n_cartas; c2++){
				if(cartas[c2].indice_grupo == c1){
					printf(" %c%c", cartas[c2].conteudo[0], cartas[c2].conteudo[1]);
				}
			}
		}
		
		printf("\n\t\t\t\t\t                   __________________________");
		
		printf("\n\t\t\t\t\t                   __________________________\n");
		
		for(c1 = 1; c1 <= *n_seq; c1++){
			printf("\n\t\t\t\t\t     Sequencia %d   ", c1);
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
		}
		
		printf("\n\t\t\t\t\t                   __________________________\n");
		
		for(c1 = 1; c1 <= n_jogadores; c1++){
			printf("\n\n\t\t\t     Cartas do jogador %d:", c1);
			contador c2;
			for (c2 = 0; c2 < *n_cartas; c2++){
				if(cartas[c2].indice_mao == c1 - 1){
					printf(" %c%c", cartas[c2].conteudo[0], cartas[c2].conteudo[1]);
				}
			}
			printf("\n");
		}

		printf("\n\n\t\t\t\t\t     >> Eh sua vez, Jogador %d <<", (n_rodadas % n_jogadores) + 1);

		printf("\n\n\n\t\t\t\t\t     Menu de opcoes\n\n\t\t\t\t\t     1 - Criar novo grupo\n\t\t\t\t\t     2 - Criar nova sequencia\n\t\t\t\t\t     3 - Manipular cartas\n\t\t\t\t\t     4 - Remover ultima sequencia ou grupo\n\t\t\t\t\t     5 - Comprar uma carta e passar a vez\n\t\t\t\t\t     6 - Terminar seu turno\n\n\t\t\t\t\t           --> ");
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
				printf("\n\n\t\t\t\t\t     Remover\n\n\t\t\t\t\t     1 - Sequencia\n\t\t\t\t\t     2 - Grupo\n\n\t\t\t\t\t           --> ");
				opc_jogo = getc(stdin);
				fflush(stdin);
				
				while((opc_jogo > '2') || (opc_jogo < '1')){
					printf("\n\n\t\t\t\t\t     Comando invalido... Tente novamente --> ");
					opc_jogo = getc(stdin);
					fflush(stdin);
				}
				
				if(opc_jogo == '1'){
					if(!(*n_seq)){
						printf("\n\n\t\t\t\t\t     Nao ha sequencias no tabuleiro.");
						getc(stdin);
						fflush(stdin);
						getc(stdin);
						fflush(stdin);
						break;
					}
					int flag1 = 0;
					for(c1 = 0; c1 < *n_cartas; c1++){
						if(cartas[c1].indice_seq == *n_seq){
							flag1 = 1;
						}
					}
					if(flag1){
						printf("\n\n\t\t\t\t\t     Ainda ha cartas nessa sequencia! Remova elas antes de deleta-la.");
						getc(stdin);
						fflush(stdin);
						break;
					} else {
						(*n_seq)--;
						printf("\n\n\t\t\t\t\t     Sequencia removida.");
						getc(stdin);
						fflush(stdin);
						break;
					}
				}
				
				if(opc_jogo == '2'){
					if(!(*n_grupos)){
						printf("\n\n\t\t\t\t\t     Nao ha grupos no tabuleiro.");
						getc(stdin);
						fflush(stdin);
						break;
					}
					int flag1 = 0;
					for(c1 = 0; c1 < *n_cartas; c1++){
						if(cartas[c1].indice_grupo == *n_grupos){
							flag1 = 1;
						}
					}
					if(flag1){
						printf("\n\n\t\t\t\t\t     Ainda ha cartas nesse grupo! Remova elas antes de deleta-lo.");
						getc(stdin);
						fflush(stdin);
						break;
					} else {
						(*n_grupos)--;
						printf("\n\n\t\t\t\t\t     Grupo removido.");
						getc(stdin);
						fflush(stdin);
						break;
					}
				}
				break;
			
			case '5':
				if(carta_mao_usada){
					printf("\n\n\t\t\t\t\t     Você já movimentou alguma carta!!! Não é possível comprar uma nova carta...");
					getc(stdin);
					fflush(stdin);
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
						printf("\n\n\t\t\t\t\t     Nao deixe grupos ou sequencias vazias antes de terminar seu turno.");
						getc(stdin);
						fflush(stdin);
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
						printf("\n\n\t\t\t\t\t     Nao deixe grupos ou sequencias vazias antes de terminar seu turno.");
						getc(stdin);
						fflush(stdin);
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
						printf("\n\n\t\t\t\t\t     Nao deixe grupos ou sequencias vazias antes de terminar seu turno.");
						getc(stdin);
						fflush(stdin);
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
						printf("\n\n\t\t\t\t\t     Nao deixe grupos ou sequencias vazias antes de terminar seu turno.");
						getc(stdin);
						fflush(stdin);
						break;
					}
				}
				
				if(!vazio){
					break;
				}
				
				if(!carta_mao_usada){
					printf("\n\n\t\t\t\t\t     Nao eh possivel terminar seu turno sem realizar algum movimento.\n\n\t\t\t\t\t     Coloque uma carta no tabuleiro ou compre uma.");
					getc(stdin);
					fflush(stdin);
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
	
	int start = 0; //Variável de controle do loop de repitição do jogo.
	
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

	int aux = 0; //Variável auxiliar para determinação de quem fez menos pontos, para o caso das peças de compra acabarem.
	int vit_sc[2] = {0, 9999}; //Vetor que guarda na primeira posição o jogador com menos pontos, e na segunda, a quantidade de pontos.
	
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
	
	fflush(stdin);
	
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
			printf("\n\n\t\t\t\t\t     Numero de jogadores\n\n\t\t\t\t\t    1 Jogador (Solitaire)\n\t\t\t\t\t         2 Jogadores\n\t\t\t\t\t         3 Jogadores\n\t\t\t\t\t         4 Jogadores\n\t\t\t\t\t         5 Jogadores\n\n\t\t\t\t\t           --> ");
			opc_jogadores = getc(stdin);
			fflush(stdin);
			n_jogadores = opc_jogadores - 48;
			if((n_jogadores > 5) || (n_jogadores < 1)){
				printf("\n\t\t\t\t\t     Comando invalido... Tente novamente --> ");
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
			printf("\n\n\t\t\t\t\t    Jogador %d venceu!!!", (n_rodadas % n_jogadores) + 1);
		}
		
		if(n_cartas == 106){
			contador c2;
			n_rodadas--;
			printf("\n\n\t\t\t\t\t    Acabaram as cartas... Fim de jogo! Ganha quem tiver menos pontos!!!");
			for(c1 = 0; c1 < n_jogadores; c1++){
				aux = 0;
				for(c2 = 0; c2 < 106; c2++){
					if(cartas[c2].indice_mao == c1){
						if(cartas[c2].conteudo[0] <= '9'){
							aux += ((int)cartas[c2].conteudo[0] - 48);
						} else if(cartas[c2].conteudo[0] == '*'){
							aux += 20;
						} else aux += ((int)cartas[c2].conteudo[0] - 55);
					}
				}
				if(aux < vit_sc[1]){
					vit_sc[0] = (c1 + 1);
					vit_sc[1] = aux;
				}
			}
			printf("\n\n\t\t\t\t\t    O vencedor foi %d!!!", vit_sc[0]);
		}
		
		
		free(cartas);
		free(baralho);		
			
		
		//Reiniciar o jogo
			
		printf("\n\n\t\t\t\t\t    Deseja jogar novamente?\n\n\t\t\t\t\t     Pressione 1 para Sim\n\t\t\t\t\t     Pressione 0 para Nao\n\n\t\t\t\t\t           --> ");
		scanf("%d", &start);
		fflush(stdin);
		
		while(start < 0 || start > 1){
			printf("\n\t\t\t\t\t     Comando invalido... Tente novamente --> ");
			scanf("%d", &start);
			fflush(stdin);
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
