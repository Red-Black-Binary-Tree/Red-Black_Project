#ifndef __REDBLACK__
#define __REDBLACK__

struct nodo {
	int chave;
	struct nodo *esq;
	struct nodo *dir;
	struct nodo *pai;
	//(0 == preto e 1 == vermelho)
	int cor;
	int nivel;
};




#endif
