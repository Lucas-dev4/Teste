#define _CRT_SECURE_NO_WARNINGS
#define BUFFER_SIZE 8300
#define BUFFER_SIZE_Y 16
#include <stdio.h>
#include <math.h>
#include <ctype.h>

int _atribuir_valor_a_tabela(int linhas, int variacao, int prop);
void _exibir_tabela(int linhas, int variacao, int proposicoes);
void _realizar_operacao(int linhas, char colunaA, char colunaB, char operar, int vetor[], int pre_vetor[], int vb[], int vc[]);
void _imprimir_resultante(int l, int da, int db, int v[], int vb[], int vc[]);
int _encontrar_valor(int coluna, int vetora[], int vetorb[], int vetorc[], int pre_vetor[], int indice, int pos);
int pegar_valor(int coluna, int i, int v[], int vb[], int vc[]);
int tabela[BUFFER_SIZE][BUFFER_SIZE_Y],vetor_memoria[BUFFER_SIZE],pre_vetor_memoria[BUFFER_SIZE],negative_prop_buffer[BUFFER_SIZE], vetor_memoria_b[BUFFER_SIZE], vetor_memoria_c[BUFFER_SIZE];
int not_flag[3];
int negative_print_buffer[BUFFER_SIZE],memory_lines = 0;
int main() {
	
	printf("==================================\n|         TABELA VERDADE         |\n");
	printf("| Feito por: Gabriel Maia Duarte |\n==================================\n");
	int num_p, num_l, _var, to_do;
	char op,ca,cb;
	printf("Digite o numero de proposicoes entre 1 e 13\n");
	printf("Digite 0 para encerrar...\n");
	scanf("%d", &num_p);
	if (num_p == 0) {
		return 0;
	}
	if (num_p > 13) {
		printf("Voce nao sabe ler? O MAXIMO E 13, ANIMAL.");
		return 0;
	}
	num_l = pow(2, num_p);
	_var = num_l / 2;
	_atribuir_valor_a_tabela(num_l, _var, num_p);
	printf("O que desejas fazer?\n");
	printf("0. Encerrar\n");
	printf("1. Exibir tabela\n");
	printf("2. Comparar Valores\n");
	printf("3. Limpar Terminal\n");
	printf("4. Esvaziar Memoria\n");
	printf("5. Exibir Memoria\n");
	while (scanf("%d", &to_do) != EOF) {

		switch (to_do) {
		case 0:
			exit(0);
			break;

		case 1:
			_exibir_tabela(num_l, _var, num_p);
			printf("\n");
			break;

		case 2:
			printf("Por favor insira a operacao\n");
			printf("operacoes: e(and),o(or),x(xor),c(->),b(<->) \n");
			printf("Use a seguinte formatacao: p e q, p o q, etc\n");
			printf("Para negar a proposicao, use maiusculo.\n");
			printf("Para ultilizar o resultado da ultima comparação, use o digito m. ex: m e q \n");
			printf("ATENCAO: 'm' sempre sera equivalente ao ultimo resultado, 'n' ao antepenultimo e 'o' ao anterior a n!\n");
			while (scanf(" %c %c %c",&ca, &op, &cb) != EOF) {
				_realizar_operacao(num_l, ca,cb,op,vetor_memoria,pre_vetor_memoria,vetor_memoria_b,vetor_memoria_c);
				break;
			}
			break;

		case 3:
			system("cls");
			printf("==================================\n|         TABELA VERDADE         |\n");
			printf("| Feito por: Gabriel Maia Duarte |\n==================================\n");
			break;

		case 4:
			for (int i = 0; i < BUFFER_SIZE;i++) {
				vetor_memoria[i] = 0;
				pre_vetor_memoria[i] = 0;
				vetor_memoria_b[i] = 0;
				vetor_memoria_c[i] = 0;
			}
			break;
		case 5:
			if (memory_lines != 0){
				printf("\033[4mm | n | o\033[0m\n");
				for (int i = 0; i < memory_lines;i++) {

					printf("%d | %d | %d\n", vetor_memoria[i], vetor_memoria_b[i], vetor_memoria_c[i]);
				}
				break;
			}
			printf("ERRO - NAO HA NADA NA MEMORIA! \n");
			break;
		default:
			printf("ERRO - COMANDO INVALIDO! \n");
			break;
		}
		
		printf("O que desejas fazer?\n");
		printf("0. Encerrar\n");
		printf("1. Exibir tabela\n");
		printf("2. Comparar Valores\n");
		printf("3. Limpar Terminal\n");
		printf("4. Esvaziar Memoria\n");
		printf("5. Exibir Memoria\n");
	}
	return 0;
}		

//Uma cacetada de função e códigos feios, mas funcionam :)
int _atribuir_valor_a_tabela(int linhas, int variacao, int prop) {
	int controle_var = 0, retornar_var = 0, nova_variacao = variacao, iteracoes = 0;
	for (int l = 0; l < prop;l++) {

		controle_var = 0;
		retornar_var = 0;
		if (iteracoes > 0) {
			if (nova_variacao / 2 != 0) {
				nova_variacao /= 2;

			}


		}
		iteracoes++;
		for (int c = 0; c < linhas; c++) {

			if (controle_var < nova_variacao) {
				tabela[c][l] = 1;
				controle_var++;
			}
			else {
				tabela[c][l] = 0;

				retornar_var++;
				if (retornar_var >= nova_variacao) {
					controle_var = 0;
					retornar_var = 0;
					continue;
				}
			}


		}
	}
	return 1;
}
void _exibir_tabela(int linhas, int variacao, int proposicoes) {
	char props[40] = { 'p','q','r','s','t','u','v','w','x','y','z','2','3','4' };
	char retprop[40] = { 0 };
	for (int i = 0; i < proposicoes; i++) {
		printf(" %c |", props[i]);
		retprop[i] = props[i];
	}
	printf("\n");
	if (_atribuir_valor_a_tabela(linhas, variacao, proposicoes)) {
		for (int c = 0; c < linhas; c++) {
			printf("\n");
			for (int l = 0; l < proposicoes;l++) {
				printf(" %d |", tabela[c][l]);
			}
		}
	}
	printf("\na tabela verdade %s possui : %d proposicoes e %d linhas\n",retprop,proposicoes,linhas);
	return;
}
int _converter_char(char dig,int pos) {
	if (isupper(dig)) {
		not_flag[pos] = 1;
		dig = tolower(dig);
	}
	switch (dig) {
		
	case 'p':
			return 0;
		case 'q':
			return 1;
		case 'r':
			return 2;
		case 's':
			return 3;
		case 't':
			return 4;
		case 'u':
			return 5;
		case 'v':
			return 6;
		case 'w':
			return 7;
		case 'x':
			return 8;
		case 'y':
			return 9;
		case 'z':
			return 10;
		case '2':
			return 11;
		case '3':
			return 12;
		case 'm':
			return 13;
		case 'n':
			return 14;
		case 'o':
			return 15;
		default:
			printf("ERRO - TENTOU COMPARAR UMA PROPOSICAO INEXISTENTE. CANCELANDO COMPARACAO \n");
			return -1;
	}
}
void _realizar_operacao(int linhas, char colunaA, char colunaB, char operar, int vetor[], int pre_vetor[],int vb[],int vc[]) {
	int digit_id_a = _converter_char(colunaA, 0);
	int digit_id_b = _converter_char(colunaB, 1);
	memory_lines = linhas;
	if (digit_id_a == -1 || digit_id_b == -1) {
		return;
	}
	for (int i = 0; i < linhas; i++) {
		vc[i] = vb[i]; // o = n, 0 default,0
		vb[i] = vetor[i]; // n = m, 0 default, ur
		

	}
		//se o digito a for negação, então novo_buffer_negativo AAAAAAAAAA calma 
		switch (operar) {
		case 'e':
			for (int i = 0; i < linhas;i++) {

				pre_vetor[i] = vetor[i];
				
				if (_encontrar_valor(digit_id_a,vetor,vb, vc,pre_vetor,i,0) && _encontrar_valor(digit_id_b, vetor, vb, vc, pre_vetor, i,1)) {
					vetor[i] = 1;

				}
				else {
					vetor[i] = 0;
				}
			}
			break;
		case 'o':
			for (int i = 0; i < linhas;i++) {
				pre_vetor[i] = vetor[i];
				
				if (_encontrar_valor(digit_id_a, vetor, vb, vc, pre_vetor, i,0) || _encontrar_valor(digit_id_b, vetor, vb, vc, pre_vetor, i,1)) {
					vetor[i] = 1;
				}
				else {
					vetor[i] = 0;
				}
			}
			break;
		case 'x':
			for (int i = 0; i < linhas;i++) {
				pre_vetor[i] = vetor[i];
				
				if ((_encontrar_valor(digit_id_a, vetor, vb, vc, pre_vetor, i,0) && _encontrar_valor(digit_id_b, vetor, vb, vc, pre_vetor, i,1) == 0) || (_encontrar_valor(digit_id_a, vetor, vb, vc, pre_vetor, i,0) ==0 && _encontrar_valor(digit_id_b, vetor, vb, vc, pre_vetor, i,1))) {
					vetor[i] = 1;
				}
				else {
					vetor[i] = 0;
				}
			}
			break;
		case 'c':
			for (int i = 0; i < linhas;i++) {
				pre_vetor[i] = vetor[i];
				
				if (_encontrar_valor(digit_id_a, vetor, vb, vc, pre_vetor, i,0) == 0 && _encontrar_valor(digit_id_b, vetor, vb, vc, pre_vetor, i,1)) {
					vetor[i] = 0;
				}
				else {
					vetor[i] = 1;
				}
			}
			break;
		case 'b':
			for (int i = 0; i < linhas;i++) {
				pre_vetor[i] = vetor[i];
				
				if ((_encontrar_valor(digit_id_a, vetor, vb, vc, pre_vetor, i,0) && _encontrar_valor(digit_id_b, vetor, vb, vc, pre_vetor, i,1)) || (_encontrar_valor(digit_id_a, vetor, vb, vc, pre_vetor, i,0) == 0 && _encontrar_valor(digit_id_b, vetor, vb, vc, pre_vetor, i,1)) == 0) {
					vetor[i] = 1;
				}
				else {
					vetor[i] = 0;
				}
			}
			break;
		default:
			printf("ERRO - OPERACAO INVALIDA! \n");
			return;
		}


	printf("\033[4m| %c | %c | RESULTADO |\033[0m\n", colunaA, colunaB);
	_imprimir_resultante(linhas, digit_id_a, digit_id_b, vetor,vb,vc);
	
	not_flag[0] = 0;
	not_flag[1] = 0;
	
}
void _imprimir_resultante(int l, int da,int db,int v[],int vb[], int vc[]) {
	for (int i = 0; i < l; i++) {

		int valA = pegar_valor(da, i, v, vb, vc);
		int valB = pegar_valor(db, i, v, vb, vc);
		int valC = v[i];

		if (not_flag[0]) valA = !valA;
		if (not_flag[1]) valB = !valB;

		printf("| %d | %d | %d |\n", valA, valB, valC);
	}
}
int pegar_valor(int coluna, int i, int v[], int vb[], int vc[]) {
	if (coluna == 13) return v[i];
	if (coluna == 14) return vb[i];
	if (coluna == 15) return vc[i];
	return tabela[i][coluna];
}
int _encontrar_valor(int coluna,int vetora[],int vetorb[], int vetorc[], int pre_vetor[], int indice, int pos) {
	
	int valA = tabela[indice][coluna];
	int valC = vetora[indice];
	int valE = vetorb[indice];
	int valF = vetorc[indice];
	int valD = pre_vetor[indice];
	if (coluna == 13) {
		if (not_flag[pos]) { return !valC; }
		return valC;
	}
	if (coluna == 14) {
		if (not_flag[pos]) { return !valE; }
		return valE;
	}
	if (coluna == 15) {
		if (not_flag[pos]) { return !valF; }
		return valF;
	}
	if (not_flag[pos]) { return !valA; }
	return valA;
}
