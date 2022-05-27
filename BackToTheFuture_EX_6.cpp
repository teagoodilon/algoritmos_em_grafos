/*
	Lucas Neves Gabriel Saber
	Otavio Augusto Trindade Fonseca
	Thiago Odilon de Almeida
*/

#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define maxNumCidades 101
#define criarPar make_pair

typedef long long ll;
const ll dezAquinze  = 1e15;
typedef pair <ll,ll> par;
typedef vector <ll> vetor;
vector<par> grafo[maxNumCidades];

ll capacidade[maxNumCidades][maxNumCidades], dist[maxNumCidades], anterior[maxNumCidades];

bool Dijkstra(ll cidades, ll &restam, ll assentos){
	for(ll i = 1; i <= cidades; i++){
		dist[i] = dezAquinze;
		anterior[i] = -1;
	}
	dist[1] = 0;
	priority_queue<par, vector<par>, greater<par> > filaDePrioridade;
	filaDePrioridade.push(criarPar(0,1));
	while(!filaDePrioridade.empty()){
		par selecionado = filaDePrioridade.top();
		filaDePrioridade.pop();
		ll percorrido = selecionado.first;
		ll v = selecionado.second;
		if(v == cidades){
				break;
		}
		for(long unsigned int i = 0; i < grafo[v].size(); i++){
			ll u = grafo[v][i].first;
			ll peso = grafo[v][i].second;
			if(capacidade[u][v] < assentos){
					peso *= -1;
			}
			if(percorrido + peso < dist[u] && capacidade[v][u] > 0){
				anterior[u] = v;
				dist[u] =  percorrido + peso;
				filaDePrioridade.push(criarPar(dist[u],u));
			}
		}
	}
	if(dist[cidades] == dezAquinze){
		return false;
	}
	vetor caminho;
	caminho.push_back(cidades);
	ll atual = cidades;
	while(atual != 1){
		caminho.push_back(anterior[atual]);
		atual = anterior[atual];
	}
	reverse(caminho.begin(),caminho.end());
	ll temp = restam;
	for(long unsigned int i = 0; i + 1 < caminho.size(); i++){
		temp = min(temp, capacidade[caminho[i]][caminho[i+1]]);
	}
	restam -= temp;
	for(long unsigned int i = 0; i + 1<caminho.size(); i++){
		capacidade[caminho[i]][caminho[i+1]] -= temp;
		capacidade[caminho[i+1]][caminho[i]] += temp;
	}
	return true;
}

void Edmond(ll cidades, ll &restam, ll &custo, ll assentos){
	while(Dijkstra(cidades, restam, assentos)){
	if(restam <= 0){
			break;
		}
	}
	for(int i = 1; i <= cidades; i++){
		for(long unsigned int j = 0; j < grafo[i].size(); j++){
			ll v = grafo[i][j].first;
			if(capacidade[i][v] < assentos){
				custo += (assentos - capacidade[i][v])*grafo[i][j].second;
			}
		}
	}
}

int main(){
	int instancia = 1;
  ll cidades, rotas, restam, custo, assentos;
	while(scanf("%lld %lld", &cidades,&rotas) != EOF){
  	custo = 0;
		for(int i = 1; i <= cidades; i++){
			grafo[i].clear();
			for(int j = 1; j <= cidades; j++){
				capacidade[i][j] = 0;
			}
		}
		while(rotas--){
			ll u,v,peso;
			cin >> u >> v >> peso;
			grafo[u].push_back(criarPar(v,peso));
			grafo[v].push_back(criarPar(u,peso));
			capacidade[u][v] = 1;
			capacidade[v][u] = 1;
		}
		cin >> restam >> assentos;
		for(int i = 1; i <= cidades; i++){
			for(int j = 1; j <= cidades; j++){
				capacidade[i][j] *= assentos;
			}
		}
		Edmond(cidades, restam, custo, assentos);
		cout << "Instancia " << instancia++ << endl;
		if(restam == 0){
			cout << custo << endl;
		} else {
			cout << "impossivel" << endl;
		}
		cout << endl;
	}
	return 0;
}