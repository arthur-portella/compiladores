#include <bits/stdc++.h>
using namespace std;

char proximo;
string simbolo;
int linha = 1;
ifstream arquivo;
string atomo;

map<string, int> palavras_reservadas = {
    {"program", 1}, {"label", 2}, {"var", 3}, {"procedure", 4}, {"function", 5}, {"begin", 6}, {"end", 7}, {"if", 8}, {"then", 9}, {"else", 10}, {"while", 11}, {"do", 12}, {"or", 13}, {"and", 14}, {"div", 15}, {"not", 16}, {"integer", 17}, {"read", 18}, {"write", 19}
};

map<string, int> simbolos_especiais = {
    {":=", 1}, {";", 2}, {",", 3}, {":", 4}, {"(", 5}, {")", 6}, {".", 7}, {"+", 8}, {"-", 9}, {"*", 10}, {"=", 11}, {"<", 12}, {">", 13}, {"<=", 14}, {">=", 15}, {"<>", 16}
};

int contador_id = 1;
map<string, int> tabela_simbolos = {};

int ENCONTRA_TABELA(string aux) {
    if (tabela_simbolos.count(aux)) 
        return tabela_simbolos[aux];

    tabela_simbolos[aux] = contador_id;
    return contador_id++;
}

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

void ERRO(string msg, string lexema = "") {
    cout << "\nErro na linha " << linha << ": " << msg;
    if (lexema != "")
        cout << " -> [ " << lexema << " ]";
    exit(1);
}

string CODIGO(string s) {
    string aux = s;
    transform(aux.begin(), aux.end(), aux.begin(), ::tolower);

    if (palavras_reservadas.count(aux)) {
        string str = to_string(palavras_reservadas[aux]);
        return "p_res[" + str + "]";
    }

    if (simbolos_especiais.count(aux)) {
        string str = to_string(simbolos_especiais[aux]);
        return "s_esp[" + str + "]";
    }
        
    if (isalpha(aux[0])) {
        int codigo_numerico = ENCONTRA_TABELA(aux);
        string str = to_string(codigo_numerico);
        return "id[" + str + "]";
    }

    if (isdigit(aux[0]))
        return "num[" + aux + "]";

    return "ERRO";
}

void ANALISADOR_LEXICO() {
    atomo = "";

    while (proximo != EOF && isspace(proximo)) {
        if (proximo == '\n') {
            cout << '\n';
            cout << linha << "\t";
        }
        else
            cout << proximo;
        PROXIMO();
    }

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

        if (simbolo != "ERRO")
            cout << "<" << s << ", " << simbolo << "> ";
        else
            ERRO("Simbolo especial nao reconhecido", s);
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
            atomo += proximo;
            PROXIMO();
        } while (isdigit(proximo));

        if (isalpha(proximo)) {
            while (isalnum(proximo)) {
                atomo += proximo;
                PROXIMO();
            }
            ERRO("Identificador ou numero nao reconhecido", atomo);
        }
            
        simbolo = CODIGO(atomo);
        cout << "<" << atomo << ", " << simbolo << "> ";
    }

    else {
        string caracter;
        caracter += proximo;
        ERRO("Caractere invalido", caracter);
    }    
}

int main() {
    arquivo.open("Trab1_Compiladores.txt");

    if (!arquivo.is_open()) {
        cout << "Arquivo Trab1_Compiladores.txt nao foi aberto!" << '\n';
    }

    cout << "1\t";

    PROXIMO();
    while(proximo != EOF) 
        ANALISADOR_LEXICO();

    arquivo.close();
}