#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "redblack.h"
#define ESPACO 5  
#define MAX_LINHAS 100
#define MAX_COLUNAS 255

struct nodo *cria_nodo(struct nodo *pai, int chave) {
	struct nodo *n = malloc(sizeof(struct nodo));
	n->chave = chave;
	n->esq = NULL;
	n->dir = NULL;
	//Se o nó que foi passado é NULL = Não tem pai:
	if (pai == NULL)
		n->pai = NULL;
	//Se não for NULL = Juntar pai e filho:
	else {
		n->pai = pai;
		if (pai->chave > n->chave)
			pai->esq = n;
		else if (pai->chave < n->chave)
			pai->dir = n;
	}
	return n;
}

struct nodo *inserir(struct nodo *pai, struct nodo *no, int chave) {
	if (no == NULL)
		return cria_nodo(pai, chave);
	if (no->chave > chave)
		return inserir(no, no->esq, chave);
	// AINDA NÃO DEFINI QUAL LADO VAI SE FOR IGUAL!!!
	if (no->chave < chave)
		return inserir(no, no->dir, chave);
	return NULL;
}

void print_tree(struct nodo *no) {
	if (no == NULL)
		return;
	print_tree(no->esq);
	printf("%.d ", no->chave);
	print_tree(no->dir);
}

int altura(struct nodo *raiz) {
	if (raiz == NULL) return 0;
	int h_esq = altura(raiz->esq);
	int h_dir = altura(raiz->dir);
	return (h_esq > h_dir ? h_esq : h_dir) + 1;
}


void preenche_matriz(char tela[MAX_LINHAS][MAX_COLUNAS], struct nodo *raiz, int linha, int col, int espaco) {
	if (raiz == NULL) return;

	char buffer[10];
	sprintf(buffer, "%d", raiz->chave);
	int len = strlen(buffer);

	for (int i = 0; i < len; i++)
		tela[linha][col + i] = buffer[i];

	if (raiz->esq != NULL) {
		tela[linha + 1][col - 1] = '/';
		preenche_matriz(tela, raiz->esq, linha + 2, col - espaco, espaco / 2);
	}
	if (raiz->dir != NULL) {
		tela[linha + 1][col + len] = '\\';
		preenche_matriz(tela, raiz->dir, linha + 2, col + espaco, espaco / 2);
	}
}


void print_arvore_vertical(struct nodo *raiz) {
	char tela[MAX_LINHAS][MAX_COLUNAS];
	for (int i = 0; i < MAX_LINHAS; i++)
		for (int j = 0; j < MAX_COLUNAS; j++)
			tela[i][j] = ' ';

	int h = altura(raiz);
	int largura = 64;  
	preenche_matriz(tela, raiz, 0, largura / 2, largura / 4);

	for (int i = 0; i < h * 2; i++) {
		tela[i][MAX_COLUNAS - 1] = '\0';
		printf("%s\n", tela[i]);
	}
}

int main() {
	int booleano_raiz = 1;
	struct nodo *raiz;
	while (1) {
		char escolha;
		int chave;
		scanf(" %c %d", &escolha, &chave);
		if (escolha != 'i')
			break;
		if (booleano_raiz) {
			raiz = cria_nodo(NULL, chave);
			booleano_raiz = 0;
		}
		else {
			inserir(NULL, raiz, chave);
		}
	}
	print_tree(raiz);
	printf("\nVisual (pra baixo):\n");
	print_arvore_vertical(raiz);
	printf("\n");
}
