#include <bits/stdc++.h>
using namespace std;

char proximo;
int simbolo;
int linha_atual = 1;
ifstream arquivo;
string atomo;

const int codigo_identificador = 45;
const int codigo_numero = 40;

map<string, int> palavras_reservadas = {
    {"program", 1}, {"label", 2}, {"var", 3}, {"procedure", 4}, {"function", 5}, {"begin", 6}, {"end", 7}, {"if", 8}, {"then", 9}, {"else", 10}, {"while", 11}, {"do", 12}, {"or", 13}, {"and", 14}, {"div", 15}, {"not", 16}, {"integer", 17}
};

map<string, int> simbolos_especiais = {
    {":=", 20}, {";", 21}, {",", 22}, {":", 23}, {"(", 24}, {")", 25}, {".", 26}, {"+", 27}, {"-", 28}, {"*", 29}, {"=", 30}, {"<=", 31}
};

void PROXIMO() {
    if (arquivo.get(proximo)) {
        if (proximo == '\n') {
            linha_atual++;
            proximo = ' ';
        }
    } else {
        proximo = EOF;
    }
}

void ERRO(string msg) {
    cout << "Erro na linha " << linha_atual << ": " << msg << '\n';
}

int CODIGO(string s, bool eh_palavra) {
    string aux = s;
    transform(aux.begin(), aux.end(), aux.begin(), ::tolower);

    if (eh_palavra) {
        if (palavras_reservadas.count(aux)) 
            return palavras_reservadas[aux];
        return codigo_identificador;
    } else {
        if (simbolos_especiais.count(aux)) 
            return simbolos_especiais[aux];
        return -1;
    }
}