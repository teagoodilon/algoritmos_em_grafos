#include <iostream> 
#include <list> 
#include <vector>
using namespace std;  
  
class grafo{ 
  int V;                  // Vertices 
  list<int> *adj;         // Ponteiro da lista de adjacência
  vector<int> finais;     // Armazena todos finais possiveis
  void descobrirCaminhos(int v1, int v2, bool visitado[], int caminho[], int indice, int& contador); // Função recursiva para descobrir todos caminhos
    public: 
    grafo(int V);   
    bool caminhoExistente;
    void addGrafo(int v, int w); 
    void imprimirCaminhos(int v1, int v2, int& contador);
    void acharFinais(int n);
    int QntCaminhos();
}; 
  
grafo::grafo(int V){                        // Construtor
  this->V = V; 
  adj = new list<int>[V]; 
}
  
void grafo::addGrafo(int v, int w){ 
    adj[v].push_back(w);                    // Adiciona "w" para a lista de "v"
} 
                                               
void grafo::descobrirCaminhos(int v1, int v2, bool visitado[], int caminho[], int indice, int& contador){  
  visitado[v1] = true;                         // Função recursiva para descobrir todos caminhos de v1 até v2
  caminho[indice]=v1;                          // Marca o grafo como visitado e coloca em caminho[]
  indice++;
  if(v1==v2){                                  // Se o vertice é o mesmo de v2, marca o caminho como true
    caminhoExistente = true;
    contador++;                                //contador para quantidade de caminhos existentes
  }
  else {                                       // Se não chama a função recursiva para todos vertices adjacentes
    list<int>::iterator i; 
    for (i = adj[v1].begin(); i != adj[v1].end(); ++i){ 
      if (!visitado[*i]){ 
        descobrirCaminhos(*i, v2, visitado, caminho, indice, contador); 
      }
    }
  }
  indice--;                                     // Remove o vértice de caminho[] 
  visitado[v1]=false;                           // Marca ele como não vistado
} 
  
void grafo::imprimirCaminhos(int v1, int v2, int& contador){ 
  
    bool *visitado = new bool[V]; 
    for (int i = 0; i < V; i++){
      visitado[i] = false;
    }
                                                          
    int *caminho = new int[V];
                                               
    int indice = 0;                                            // Inicializa o caminho[] como vazio 
    caminhoExistente = false;
    descobrirCaminhos(v1,v2,visitado,caminho,indice,contador); // Chama a função recursiva para descobrir os caminhos
} 

void grafo::acharFinais(int n){
  for(int i = 0; i <n; i++){
    if(adj[i].size()==0){
      finais.push_back(i);
    }
  }
}

int grafo:: QntCaminhos(){
  int qnt = 0;
  for(unsigned i=0; i <finais.size();i ++){
    imprimirCaminhos(0,finais[i], qnt);
  }
  return qnt;
}
   
int main(){
  int n;                                     // Quatidade de vertices
  cin >> n;
  grafo pares(n);                            // Cria grafos de pares "n"
  int v1,v2;                                 // Vertices das ligacoes
  cin >> v1 >> v2;
	while(v1 != -1 and v2 != -1){
    if(v1 != -1 and v2 != -1){
      pares.addGrafo(v1-1,v2-1);
    }
    cin >> v1 >> v2;
  }
  pares.acharFinais(n);                      // Acha os finais
  int qntCaminhos = pares.QntCaminhos();     // Acha a quantidade de caminhos
  cout << qntCaminhos << endl;
  return 0; 
} 
