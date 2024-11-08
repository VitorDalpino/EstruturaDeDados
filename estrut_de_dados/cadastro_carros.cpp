#include <iostream>
#include <stdexcept> 
#include <string>
using namespace std;

const int MaxCapacidade = 100;

struct carro{
    string nome;
    string marca;
    string modelo;
};

class Pilha {
private:
    carro Cadastrados[MaxCapacidade]; // armazena os carros cadastrados
    int vagas; // controle de espaços disponiveis
    int QntdCarros; // controla a quantidade de carros castrados
public:
    Pilha() { // construtor
        vagas = -1; 
    }

    bool vazia() { // verificação -> vazia
        return vagas == -1; 
    }

    bool cheia() { // verificação -> cheia
        return vagas == MaxCapacidade - 1; 
    }
    // cadastro dos carros
    void Cadastro(const string& nome, const string& marca, const string& modelo){
        if (!cheia()) { 
            vagas++; 
        Cadastrados[vagas].marca = marca;
        Cadastrados[vagas].nome = nome;
        Cadastrados[vagas].modelo = modelo;
            cout << "Carro cadastrado com sucesso! " << endl;
        } else {
            throw overflow_error("Nao ha espaco para cadastrar mais carros!"); 
        }
    }
    // remoção dos carros
    carro Deletar() {
        if (!vazia()) { 
            carro dados = Cadastrados[vagas]; 
            vagas--; // 
            return dados; 
        } else {
            throw underflow_error("Nao ha carros cadastrados!");
        }
    }
    // listar os carros
    void Lista() {
        if(!vazia()){
        cout << "Lista de carros cadastrados: " << endl;
        for (int i = vagas; i >= 0; i--) {
        cout << "Marca: " << Cadastrados[i].marca << endl;
        cout << "Nome: " << Cadastrados[i].nome << endl;
        cout << "Modelo: " << Cadastrados[i].modelo << endl;
        }
    } else{
        cout <<"Nao ha carros cadastrados!"<<endl;
    }
}
};

int main() {
    Pilha p;
    string nome, marca, modelo; // receber o que o cliente quer cadastrar
    int escolha; // escolha do cliente no menu

    do { // menu
        cout << "\nMENU - Escolha uma opcao:" << endl;
        cout << "1. Cadastrar novo carro" << endl;
        cout << "2. Deletar carro cadastrado" << endl;
        cout << "3. Listar carros cadastrados" << endl;
        cout << "4. Sair" << endl;
        cout << "Opcao escolhida: ";
        cin >> escolha;

        switch (escolha) {
            case 1: // cadastro de carros
                cout << " Cadastro do carro:" << endl;
      cout << "Marca:";
      cin >> marca;
      cout << "Nome:";
      cin >> nome;
      cout << "Modelo:";
      cin >> modelo;
                try {
                    p.Cadastro(marca,nome,modelo);
                } catch (const exception& e) {
                    cout << "Erro: " << e.what() << endl;
                }
                break;
            case 2: // remoção do cadastro
                try {
                    carro dados = p.Deletar();
                cout << "Marca: " << dados.marca << endl;
                cout << "Nome:  " << dados.nome << endl;
                cout << "Modelo: " << dados.modelo << endl;
                cout << "Carro removido com sucesso! " << endl;
                } catch (const exception& e) {
                    cout << "Erro: " << e.what() << endl;
                }
                break;
            case 3: // listar os cadastros
                p.Lista();
                break;
            case 4: // sair do programa
                cout << "Saida efetuada com sucesso!" << endl;
                break;
            default: // escolha nao existe
                cout << "Opcao inválida!" << endl;
        }
    } while (escolha != 4);

    return 0;
}
