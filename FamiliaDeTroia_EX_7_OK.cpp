/*
Lucas Gabriel Neves Saber - 202020459
Otavio Augusto Trindade Fonseca - 202020551
Thiago Odilon de Almeida - 202021025
*/
#include <iostream>
#include <list>

using namespace std; 

list<int> *lista = new list<int>[50000];

void DFS(int x, int visitado[]){
	list<int>::iterator i;
	
	visitado[x] = 1; // marca o atual como visitado
	
	// busca por um vizinho não visitado
	for(i = lista[x].begin(); i != lista[x].end(); i++){
		if(visitado[*i] == -1){
			DFS(*i, visitado);
		}
	}
}

void grafo(int n, int m){
	int visitado[50000];
	int a, b;
	int qntd=0; // quantida de famílias
	
	// adiciona cada vértice um no outro
	for(int i=1; i <= m; i++){
		cin >> a >> b;
		lista[a].push_back(b);
		lista[b].push_back(a);
	}
	
	// marca todos como não visitado
	for (int i=1; i <= n; i++){
		visitado[i] = -1;
	}
	
	// vai percorrer os vértices um por um
	for (int i=1; i <= n; i++){
		if (visitado[i] == -1){
			DFS(i, visitado);
			qntd++;
		}
	}
	
	cout << qntd <<endl; // resultado de quantas famílias
}
int main(){
	int n, m;
	cin >> n >> m;
	
	grafo(n, m);
	
	return 0; 
}
