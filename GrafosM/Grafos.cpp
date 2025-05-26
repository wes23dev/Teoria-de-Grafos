#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

class Grafo {
private:
    int n; // Numero de vertices
    int m; // Numero de arestas
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
            matrizAdj[u][v]++;
            matrizAdj[v][u]++; // Se for grafo direcionado, comente essa linha
        }

        arquivo.close();
    }

    void imprimirMatriz() {
        cout << "\nMatriz de Adjacencia:" << endl;
        for (const auto& linha : matrizAdj) {
            for (int val : linha) {
                cout << val << " ";
            }
            cout << endl;
        }
    }

    void imprimirArestas() {
        cout << "\nLista de Arestas:" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                for (int k = 0; k < matrizAdj[i][j]; k++) {
                    cout << i << " - " << j << endl;
                }
            }
        }
    }

    void calcularGraus() {
        cout << "\nGrau de cada vertice:" << endl;
        for (int i = 0; i < n; i++) {
            int grau = 0;
            for (int j = 0; j < n; j++) {
                grau += matrizAdj[i][j];
            }
            cout << "Vertice " << i << ": grau " << grau << endl;
        }
    }

    bool Simples() {
        for (int i = 0; i < n; i++) {
            if (matrizAdj[i][i] != 0) return false;
            for (int j = 0; j < n; j++) {
                if (i != j && matrizAdj[i][j] > 1) return false;
            }
        }
        return true;
    }

    bool Pseudografo() {
        for (int i = 0; i < n; i++) {
            if (matrizAdj[i][i] != 0) return true;
        }
        return false;
    }

    bool Multigrafo() {
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (matrizAdj[i][j] > 1) return true;
            }
        }
        return false;
    }

    bool Completo() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && matrizAdj[i][j] == 0)
                    return false;
            }
        }
        return true;
    }

    bool Conexo() {
        vector<bool> visitado(n, false);
        queue<int> fila;

        fila.push(0);
        visitado[0] = true;

        while (!fila.empty()) {
            int v = fila.front();
            fila.pop();

            for (int i = 0; i < n; i++) {
                if (matrizAdj[v][i] > 0 && !visitado[i]) {
                    visitado[i] = true;
                    fila.push(i);
                }
            }
        }

        for (bool v : visitado) {
            if (!v) return false;
        }
        return true;
    }

    void densoOuEsparso() {
        int maxArestas = n * (n - 1) / 2;
        if (m > maxArestas / 2) {
            cout << "\nO grafo eh DENSO." << endl;
        } else {
            cout << "\nO grafo eh ESPARSO." << endl;
        }
    }

    void propriedades() {
        cout << "\nTipo do Grafo:" << endl;
        if (Simples()) cout << "Grafo Simples" << endl;
        else if (Pseudografo()) cout << "Pseudografo" << endl;
        else if (Multigrafo()) cout << "Multigrafo" << endl;

        if (Completo()) cout << "eh um grafo completo" << endl;
        else cout << "Nao eh um grafo completo" << endl;

        if (Conexo()) cout << "eh um grafo conexo" << endl;
        else cout << "eh um grafo desconexo" << endl;

        densoOuEsparso();
    }
};

int main() {
    string nomeArquivo;
    cout << "Digite o nome do arquivo (ex.: entrada.txt): ";
    cin >> nomeArquivo;

    Grafo g(nomeArquivo);

    g.imprimirMatriz();
    g.imprimirArestas();
    g.calcularGraus();
    g.propriedades();

    return 0;
}
