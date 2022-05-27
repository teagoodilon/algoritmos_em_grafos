/*
Lucas Gabriel Neves Saber - 202020459
Otavio Augusto Trindade Fonseca - 202020551
Thiago Odilon de Almeida - 202021025
*/
#include<iostream>
#include <list>
using namespace std;

class Grafo{
	int V; 
	list<int> *adj;
public:
	Grafo(int V);
	void addAresta(int v, int w);
	bool alcancavel(int s, int d);
};

Grafo::Grafo(int V){
	this->V = V;
	adj = new list<int>[V];
}

void Grafo::addAresta(int v, int w){
	adj[v].push_back(w); //ADICONA w EM v.
}

bool Grafo :: alcancavel(int s, int d)//VERIFICA SE EXISTE UM CAMINHO ENTRE s E d
{
	// CASO BASE
	if (s == d){
	    return true;
    }
	//MARCA TODOS VERTICES COMO NAO VISITADO
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++){
		visited[i] = false;
    }
	//CRIA UMA QUEUE PARA BFS
	list<int> queue;

	//MARCA O VERTICE ATUAL COMO VISITADO E ADICIONA NA FILA
	visited[s] = true;
	queue.push_back(s);

	//TODOS VERTICES ADJACENTES
	list<int>::iterator i;

	while (!queue.empty()){
		s = queue.front();
		queue.pop_front();

		
		for (i = adj[s].begin(); i != adj[s].end(); ++i)
		{
			//SE O VERTICE NA adj FOR O DE DESTINO RETORNA true
			if (*i == d){
				return true;
            }
			//SE NAO FOR CONTINUA A BUSCA
			if (!visited[*i]){
				visited[*i] = true;
				queue.push_back(*i);
			}
		}
	}

	//SE NAO CHEGAR RETORNA FALSO
	return false;
}

int main(){
    int numCasos;
    cin >> numCasos;
    int p[numCasos] ;
  
    ///FAZ DE 2 GRAFOS POR VEZ
    for(int i = 0; i < numCasos; i++){
        int t1,t2;                      //TAMANHO DOS GRAFOS
        cin >> t1;

        Grafo g1(t1);                   //GRAFO 1
        int  tamG1 = 0;                 //ARMAZENA O MAIOR VERTICE, QUE TAMBEM E A QUANTIDADE DE VERTICES
        for(int j = 0; j < t1; j++){
            int x,y;
            cin >> x >> y;
            if(x > y ){                 //ACHA O MAIOR VERTICE INSERIDO
                if(x > tamG1)
                    tamG1 = x;
            }else{
                if(y > tamG1)
                    tamG1 = y;
            }
            g1.addAresta(x,y);
        } 

        cin >> t2;
        Grafo g2(t2);                   //GRAFO 2
        int tamG2 =0; 
        for(int k = 0; k < t2; k++){
            int x,y;
            cin >> x >> y;
            if(x > y ){                             //ACHA O MAIOR VERTICE INSERIDO
                if(x > tamG2)
                    tamG2 = x;
                } else {
                if(y > tamG2)
                    tamG2 = y;
                }
            g2.addAresta(x,y);
        }

        int imprime1, imprime2;                 //VARIAVEL Q ARMAZENA SE CHEGA 0 OU 1
                                                //VERIFICA SE O SEGUNDO CHEGA NOS PONTOS DO PRIMEIRO
        for(int i = 0; i < tamG1; i++){
            for(int j = 0; j < tamG1; j++){
                if((g1.alcancavel(i,j) == true and g2.alcancavel(i,j) == true) or
                (g1.alcancavel(i,j) == false and g2.alcancavel(i,j) == false)){
                    imprime1 = 1;
                } else {
                    imprime1 = 0;
                    i = tamG1;
                    j = i;
                }
            }
        }

                                                //VERIFICA SE O PRIMEIRO CHEGA NOS MESMO QUE O SEGUNDO
        for(int i = 0; i < tamG2; i++){         //VERIFICA SE O SEGUNDO CHEGA NOS PONTOS DO PRIMEIRO
            for(int j = 0; j < tamG2; j++){
                if((g1.alcancavel(i,j) == true and g2.alcancavel(i,j) == true) or
                (g1.alcancavel(i,j) == false and g2.alcancavel(i,j) == false)){
                    imprime2 = 1;
                } else {
                    imprime2 = 0;
                    i = tamG1;
                    j = i;
                }
            }
        }

        if(imprime1 == imprime2){
            p[i] = imprime1;
        } else {
            p[i] = 0;
        }
    }

    for (int i = 0; i < numCasos; i++){
        cout<< p[i]<< endl;
    }
    return 0; 
}
