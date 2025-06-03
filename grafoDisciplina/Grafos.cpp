#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <set>
using namespace std;

unordered_map<string, vector<string>> grafo;

void buscarPreRequisitos(const string& materia, set<string>& visitado) {
    for (const string& pre : grafo[materia]) {
        if (visitado.find(pre) == visitado.end()) {
            visitado.insert(pre);
            buscarPreRequisitos(pre, visitado);
        }
    }
}


void mostrarPreRequisitos(const string& materia) {
    set<string> visitado;
    buscarPreRequisitos(materia, visitado);

    if (visitado.empty()) {
        cout << "A disciplina " << materia << " não possui pré-requisitos.\n";
    } else {
        cout << "Para cursar " << materia << ", voce deve fazer antes:\n";
        for (const auto& pre : visitado) {
            cout << "- " << pre << '\n';
        }
    }
}

void carregarGrafoDeArquivo(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo " << nomeArquivo << endl;
        exit(1);
    }

    string linha;
    while (getline(arquivo, linha)) {
        if (linha.empty()) continue;

        stringstream ss(linha);
        string materia;
        getline(ss, materia, ';'); // lê a disciplina

        vector<string> preRequisitos;
        string pre;
        bool temPreRequisito = false;

        while (getline(ss, pre, ';')) {
            if (pre != "n") { // "n" significa sem pré-requisito
                preRequisitos.push_back(pre);
                temPreRequisito = true;
            }
        }

        if (temPreRequisito) {
            grafo[materia] = preRequisitos;
        } else {
            grafo[materia] = {}; // sem pré-requisitos
        }
    }
    arquivo.close();
}

int main() {
    string nomeArquivo = "C:\\Users\\15102938681\\Desktop\\grafoDisciplina\\build\\Debug\\cod.txt";

    carregarGrafoDeArquivo(nomeArquivo);

    string materia;
    cout << "Digite o codigo da materia (ex.: DCC455): "; 
    cin >> materia;

    mostrarPreRequisitos(materia);

    return 0;
}
