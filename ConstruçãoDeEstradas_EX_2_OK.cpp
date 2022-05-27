/*
Lucas Gabriel Neves Saber - 202020459
Otavio Augusto Trindade Fonseca - 202020551
Thiago Odilon de Almeida - 202021025
*/

#include <iostream>
#include <vector>
#include <queue>
#include <math.h>

using namespace std;

int main(){
  int vertices;
  cin >> vertices;

  vector < pair <int,int> > vetor, vetor_reserva;
  vector <vector <pair <int,int> > > arestas(vertices);

  for(int i = 0; i < vertices; i++){
    int x1,y1;               
    cin >> x1 >> y1;                    
    vetor.push_back({x1,y1});          //coloca pares no vetor
  }

  int estradas_fixas, cid1, cid2;
  cin >> estradas_fixas;                      //estradas fixas
  for (int i = 0; i < estradas_fixas; i++){              
    cin >> cid1 >> cid2;
    arestas[cid1-1].push_back ({cid2-1, 0});        //insere as estradas (arestas) fixas na lista de adjacencia
    arestas[cid2-1].push_back ({cid1-1, 0});        //ajustamos o custo para 0, pois assim que o algoritmo de prim passar, ele vai escolher esse caminho
  }
  for (int i = 0; i < vertices; i++){                             //calculamos todos os custos e ligações possiveis
    for (int j = 0; j < vertices; j++){
      double distancia = sqrt(((vetor[j].first - vetor[i].first)
      * (vetor[j].first - vetor[i].first))
      + ((vetor[j].second - vetor[i].second)
      * (vetor[j].second - vetor[i].second)));
        arestas[i].push_back({ j, round(distancia)});            //armazenamos os valores na lista
    }
  }

  priority_queue< pair<int, int> > prim;  //lista de prioridade
  vector<bool> mark(vertices, false);     //um marcador para indicar se o vertice foi visitado

  mark[0] = true;                         //partimos do vertice 1
  for(pair<int,int> ed: arestas[0]){      //percorre todas as arestas saindo do 0
    prim.push({-ed.second, ed.first});    //como a fila de prioridade é máxima, colocamos o custo negativo com isso o maior negativo vai ser o menor positvo
  }
  int custo = 0;
  while(prim.size()){
    pair<int,int> menor_aresta = prim.top();    //aresta de menor tamanho
    prim.pop();                                 //apaga a fila de prioridade
    
    if(mark[menor_aresta.second]==true) continue; //se o vertice foi visitado, ele continua
    custo += -menor_aresta.first;                 //soma o custo das menores arestas

    mark[menor_aresta.second] = true;                         //marca o vertice que a aresta vai como positivo
    for(pair<int,int> ed: arestas[menor_aresta.second]){      //pega todas as arestas que sai de menor_aresta.second
      prim.push({-ed.second, ed.first});                      
    }
  }
  cout << custo << endl;
}