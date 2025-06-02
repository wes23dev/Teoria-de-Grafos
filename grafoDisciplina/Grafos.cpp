#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

class Grafo {
private:
    int n; // número de vértices (disciplinas)
    int m; // número de arestas (pré-requisitos)
    vector<vector<int>> matrizAdj;

public:

    Grafo(const string& nomeArquivo) {
        ifstream arquivo(nomeArquivo);
        if (!arquivo.is_open()) {
            cout << "Erro ao abrir o arquivo. Verifique o nome ou o local." << endl;
            return;
        }


        arquivo >> n >> m;
        matrizAdj.resize(n, vector<int>(n, 0));
        
        for (int i = 0; i < m; i++) {
            int u, v;
            arquivo >> u >> v;
            matrizAdj[u][v] = 1; // u é pré-requisito de v
        }
        
        arquivo.close();
    }

    void imprimirMatriz() {
        cout << "Matriz de Adjacência:" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << matrizAdj[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    
    Grafo g("C:\\Users\\15102938681\\Desktop\\grafoDisciplina\\output\\cod.txt");
    g.imprimirMatriz();

    
    return 0;
}
