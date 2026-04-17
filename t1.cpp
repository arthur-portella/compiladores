#include <bits/stdc++.h>
using namespace std;

char proximo;
int simbolo;
int linha = 1;
ifstream arquivo;
string atomo;

const int codigo_identificador = 45;
const int codigo_numero = 40;

map<string, int> palavras_reservadas = {
    {"program", 1}, {"label", 2}, {"var", 3}, {"procedure", 4}, {"function", 5}, {"begin", 6}, {"end", 7}, {"if", 8}, {"then", 9}, {"else", 10}, {"while", 11}, {"do", 12}, {"or", 13}, {"and", 14}, {"div", 15}, {"not", 16}, {"integer", 17}, {"read", 18}, {"write", 19}
};

map<string, int> simbolos_especiais = {
    {":=", 20}, {";", 21}, {",", 22}, {":", 23}, {"(", 24}, {")", 25}, {".", 26}, {"+", 27}, {"-", 28}, {"*", 29}, {"=", 30}, {"<", 31}, {">", 32}, {"<=", 33}, {">=", 34}, {"<>", 35}
};

void PROXIMO() {
    if (arquivo.get(proximo)) {
        if (proximo == '\n') {
            linha++;
        }
    } else {
        proximo = EOF;
        return;
    }
}

void ERRO(string msg) {
    cout << "Erro na linha " << linha << ": " << msg << '\n';
    exit(1);
}

int CODIGO(string s) {
    string aux = s;
    transform(aux.begin(), aux.end(), aux.begin(), ::tolower);

    if (palavras_reservadas.count(aux)) 
        return palavras_reservadas[aux];
    
    if (simbolos_especiais.count(aux)) 
        return simbolos_especiais[aux];
        
    if (isalpha(aux[0]))
        return codigo_identificador;

    if (isdigit(aux[0]))
        return codigo_numero;

    return -1;
}

void ANALISADOR_LEXICO() {
    atomo = "";

    while (proximo != EOF && isspace(proximo)) 
        PROXIMO();

    if (proximo == EOF)
        return;

    string simbolos_especiais_iniciais = ":;,().+-*=<>";
    if (simbolos_especiais_iniciais.find(proximo) != string::npos) {
        string s;
        s = proximo;
        PROXIMO();

        if (((s == ":" || s == "<" || s == ">") && proximo == '=') || (s == "<" && proximo == '>')) {
            s += proximo;
            PROXIMO();
        }
        
        simbolo = CODIGO(s);

        if (simbolo != -1)
            cout << "<" << s << ", " << simbolo << "> ";
        else
            ERRO("Simbolo especial nao reconhecido: " + s);
    } 
    
    else if (isalpha(proximo)) {
        do {
            atomo += proximo;
            PROXIMO();
        } while (isalnum(proximo));

        simbolo = CODIGO(atomo);
        cout << "<" << atomo << ", " << simbolo << "> ";
    }

    else if (isdigit(proximo)) {
        do {
            atomo +=proximo;
            PROXIMO();
        } while (isdigit(proximo));

        if (isalpha(proximo))
            ERRO("Identificador ou numero nao reconhecidos");

        simbolo = codigo_numero;
        cout << "<" << atomo << ", " << simbolo << "> ";
    }

    else {
        ERRO("Caractere invalido.");
    }    
}

int main() {
    arquivo.open("Trab1_Compiladores.txt");

    if (!arquivo.is_open()) {
        cout << "Arquivo Trab1_Compiladores.txt nao foi aberto!" << '\n';
    }

    PROXIMO();
    while(proximo != EOF) 
        ANALISADOR_LEXICO();

    arquivo.close();
}