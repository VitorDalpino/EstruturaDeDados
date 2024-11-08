#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <list>
#include <fstream>

using namespace std;

// Classe Item para representar itens no jogo
class Item {
public:
    string nome;
    string tipo; // Ex: arma, armadura, po��o

    Item(string nome, string tipo) : nome(nome), tipo(tipo) {}
};

// Classe Personagem para representar personagens no jogo
class Personagem {
public:
    string nome;
    string classe;
    int vida;
    int ataque;
    int defesa;
    vector<string> habilidades;
    vector<Item> inventario;

    // Construtor do personagem com valores padr�o
    Personagem(string nome = "default", string classe = "default", int vida = 0, int ataque = 0, int defesa = 0)
        : nome(nome), classe(classe), vida(vida), ataque(ataque), defesa(defesa) {}

    // M�todo para adicionar habilidades ao personagem
    void adicionarHabilidade(string habilidade) {
        habilidades.push_back(habilidade);
    }

    // M�todo para adicionar itens ao invent�rio do personagem
    void adicionarItem(Item item) {
        inventario.push_back(item);
    }

    // M�todo para remover itens do invent�rio do personagem
    void removerItem(string nomeItem) {
        for (auto it = inventario.begin(); it != inventario.end(); ++it) {
            if (it->nome == nomeItem) {
                inventario.erase(it);
                break;
            }
        }
    }

    // M�todo para mostrar o invent�rio do personagem
    void mostrarInventario() {
        cout << "Invent�rio de " << nome << ":\n";
        for (const auto& item : inventario) {
            cout << item.nome << " (" << item.tipo << ")\n";
        }
    }

    // M�todo para equipar itens, aumentando atributos
    void equiparItem(string nomeItem) {
        for (const auto& item : inventario) {
            if (item.nome == nomeItem) {
                if (item.tipo == "arma") {
                    ataque += 10; // Exemplo: Aumenta o ataque ao equipar uma arma
                } else if (item.tipo == "armadura") {
                    defesa += 10; // Exemplo: Aumenta a defesa ao equipar uma armadura
                }
                cout << nomeItem << " equipado com sucesso!" << endl;
                return;
            }
        }
        cout << "Item n�o encontrado no invent�rio!" << endl;
    }

    // M�todo para utilizar itens, aplicando efeitos
    void utilizarItem(string nomeItem) {
        for (const auto& item : inventario) {
            if (item.nome == nomeItem) {
                if (item.tipo == "po��o") {
                    vida += 20; // Exemplo: Recupera vida ao usar uma po��o
                }
                removerItem(nomeItem);
                cout << nomeItem << " utilizado com sucesso!" << endl;
                return;
            }
        }
        cout << "Item n�o encontrado no invent�rio!" << endl;
    }
};

// Classe Pilha para salvar estados anteriores dos personagens
class Pilha {
    stack<Personagem> historico;
public:
    // Salva o estado do personagem na pilha
    void salvarEstado(const Personagem& p) {
        historico.push(p);
    }

    // Desfaz a �ltima a��o, retornando o estado anterior do personagem
    Personagem desfazer() {
        if (!historico.empty()) {
            Personagem p = historico.top();
            historico.pop();
            return p;
        }
        return Personagem();
    }
};

// Classe Fila para gerenciar a ordem de turnos dos personagens
class Fila {
    queue<Personagem> ordemDeTurnos;
public:
    // Adiciona um personagem � fila de turnos
    void adicionarPersonagem(const Personagem& p) {
        ordemDeTurnos.push(p);
    }

    // Retorna o pr�ximo personagem na fila de turnos
    Personagem proximoTurno() {
        if (!ordemDeTurnos.empty()) {
            Personagem p = ordemDeTurnos.front();
            ordemDeTurnos.pop();
            return p;
        }
        return Personagem();
    }
};

// Classe NoArvore para representar n�s em uma �rvore de habilidades
class NoArvore {
public:
    string habilidade;
    vector<NoArvore*> filhos;

    NoArvore(string habilidade) : habilidade(habilidade) {}

    // Adiciona um filho ao n�
    void adicionarFilho(NoArvore* filho) {
        filhos.push_back(filho);
    }
};

// Classe ArvoreHabilidades para representar a �rvore de habilidades
class ArvoreHabilidades {
    NoArvore* raiz;
public:
    ArvoreHabilidades(string habilidadeBase) {
        raiz = new NoArvore(habilidadeBase);
    }

    // Adiciona uma nova habilidade � �rvore
    void adicionarHabilidade(string habilidadePai, string novaHabilidade) {
        adicionarHabilidadeRecursivo(raiz, habilidadePai, novaHabilidade);
    }

private:
    // Fun��o recursiva para adicionar habilidades � �rvore
    void adicionarHabilidadeRecursivo(NoArvore* no, string habilidadePai, string novaHabilidade) {
        if (no->habilidade == habilidadePai) {
            no->adicionarFilho(new NoArvore(novaHabilidade));
        } else {
            for (auto filho : no->filhos) {
                adicionarHabilidadeRecursivo(filho, habilidadePai, novaHabilidade);
            }
        }
    }
};

// Classe TabelaHash para gerenciar personagens usando uma tabela de hash
class TabelaHash {
    unordered_map<string, Personagem> tabela;
public:
    // Adiciona um personagem � tabela de hash
    void adicionarPersonagem(string nome, const Personagem& p) {
        tabela[nome] = p;
    }

    // Busca um personagem na tabela de hash
    Personagem buscarPersonagem(string nome) {
        if (tabela.find(nome) != tabela.end()) {
            return tabela[nome];
        }
        return Personagem();
    }

    // Atualiza um personagem na tabela de hash
    void atualizarPersonagem(const Personagem& p) {
        tabela[p.nome] = p;
    }

    // M�todo para listar todos os personagens
    void listarPersonagens() {
        for (const auto& par : tabela) {
            const Personagem& personagem = par.second;
            cout << "Nome: " << personagem.nome
                 << ", Vida: " << personagem.vida
                 << ", Ataque: " << personagem.ataque
                 << ", Defesa: " << personagem.defesa << endl;
        }
    }

    // Adicionar um m�todo para obter a tabela de personagens
    const unordered_map<string, Personagem>& obterTabela() const {
        return tabela;
    }
};

// Fun��o para criar um novo personagem
void criarPersonagem(TabelaHash& tabela, vector<Personagem>& personagens, Pilha& historico) {
    string nome, classe;
    int vida, ataque, defesa;

    cout << "Nome do personagem: ";
    cin >> nome;
    cout << "Classe do personagem: ";
    cin >> classe;
    cout << "Vida: ";
    cin >> vida;
    cout << "Ataque: ";
    cin >> ataque;
    cout << "Defesa: ";
    cin >> defesa;

    Personagem p(nome, classe, vida, ataque, defesa);
    tabela.adicionarPersonagem(nome, p);
    personagens.push_back(p);
    historico.salvarEstado(p);

    cout << "Personagem criado com sucesso!" << endl;
}

// Fun��o para gerenciar o invent�rio de um personagem
void gerenciarInventario(Personagem& personagem, TabelaHash& tabela) {
    int opcao;
    do {
        cout << "1. Adicionar item" << endl;
        cout << "2. Remover item" << endl;
        cout << "3. Equipar item" << endl;
        cout << "4. Utilizar item" << endl;
        cout << "5. Mostrar invent�rio" << endl;
        cout << "6. Voltar" << endl;
        cin >> opcao;

        switch (opcao) {
            case 1: {
                string nomeItem, tipoItem;
                cout << "Nome do item: ";
                cin >> nomeItem;
                cout << "Tipo do item (arma, armadura, po��o): ";
                cin >> tipoItem;
                Item item(nomeItem, tipoItem);
                personagem.adicionarItem(item);
                cout << "Item adicionado com sucesso!" << endl;
                break;
            }
            case 2: {
                string nomeItem;
                cout << "Nome do item a ser removido: ";
                cin >> nomeItem;
                personagem.removerItem(nomeItem);
                cout << "Item removido com sucesso!" << endl;
                break;
            }
            case 3: {
                string nomeItem;
                cout << "Nome do item a ser equipado: ";
                cin >> nomeItem;
                personagem.equiparItem(nomeItem);
                break;
            }
            case 4: {
                string nomeItem;
                cout << "Nome do item a ser utilizado: ";
                cin >> nomeItem;
                personagem.utilizarItem(nomeItem);
                break;
            }
            case 5:
                personagem.mostrarInventario();
                break;
            case 6:
                cout << "Voltando..." << endl;
                break;
            default:
                cout << "Op��o inv�lida!" << endl;
        }
        
        // Atualiza o personagem na tabela ap�s qualquer modifica��o
        tabela.atualizarPersonagem(personagem);
    } while (opcao != 6);
}

// Fun��o para desfazer a �ltima a��o
void desfazerAcao(TabelaHash& tabela, Pilha& historico) {
    Personagem p = historico.desfazer();
    if (p.nome != "default") {
        tabela.atualizarPersonagem(p);
        cout << "�ltima a��o desfeita com sucesso!" << endl;
    } else {
        cout << "N�o h� a��es para desfazer!" << endl;
    }
}

// Fun��o para salvar o estado do jogo em um arquivo
void salvarEstadoJogo(const TabelaHash& tabela) {
    ofstream arquivo("estado_jogo.txt");
    if (arquivo.is_open()) {
        const auto& personagens = tabela.obterTabela();
        for (const auto& par : personagens) {
            const Personagem& p = par.second;
            arquivo << p.nome << " " << p.classe << " " << p.vida << " " << p.ataque << " " << p.defesa << endl;
            for (const auto& item : p.inventario) {
                arquivo << item.nome << " " << item.tipo << endl;
            }
            arquivo << "END" << endl;
        }
        arquivo.close();
        cout << "Estado do jogo salvo com sucesso!" << endl;
    } else {
        cout << "Erro ao salvar o estado do jogo!" << endl;
    }
}
// Fun��o para explorar e contar a hist�ria
void explorar() {
    cout << "Explorando...\n";
    cout << "Voc� se encontra em uma floresta sombria, onde os galhos das �rvores se entrela�am formando uma teia impenetr�vel.\n";
    cout << "Caminhando lentamente, voc� ouve o som de passos se aproximando.\n";
    cout << "De repente, uma figura encapuzada aparece na sua frente e sussurra: 'Voc� n�o deveria estar aqui...'\n";
    cout << "O que voc� faz?\n";
    cout << "1. Perguntar quem ele �\n";
    cout << "2. Atacar\n";
    cout << "3. Fugir\n";

    int escolha;
    cin >> escolha;

    switch (escolha) {
        case 1:
            cout << "A figura encapuzada ri sombriamente e diz: 'Eu sou o guardi�o desta floresta. Prove seu valor, ou pere�a.'\n";
            break;
        case 2:
            cout << "Voc� se prepara para atacar, mas a figura desaparece em uma nuvem de fuma�a, deixando apenas um eco risonho.\n";
            break;
        case 3:
            cout << "Voc� tenta fugir, mas seus p�s parecem presos ao ch�o. A figura sussurra: 'N�o h� escapat�ria.'\n";
            break;
        default:
            cout << "Op��o inv�lida. A figura encapuzada desaparece na escurid�o, e voc� continua sua jornada solit�ria.\n";
    }
}

int main() {
    TabelaHash tabelaPersonagens;
    vector<Personagem> personagens;
    Pilha historico;
    Fila ordemDeTurnos;
    ArvoreHabilidades habilidades("Base");

    int opcao;
    do {
        cout << "1. Criar personagem" << endl;
        cout << "2. Listar personagens" << endl;
        cout << "3. Explorar" << endl;
        cout << "4. Gerenciar invent�rio de personagem" << endl;
        cout << "5. Desfazer �ltima a��o" << endl;
        cout << "6. Salvar estado do jogo" << endl;
        cout << "7. Sair" << endl;
        cin >> opcao;

        switch (opcao) {
            case 1:
                criarPersonagem(tabelaPersonagens, personagens, historico);
                break;
            case 2:
                tabelaPersonagens.listarPersonagens();
                break;
            case 3:
                explorar();
                break;
            case 4: {
                string nome;
                cout << "Nome do personagem: ";
                cin >> nome;
                Personagem p = tabelaPersonagens.buscarPersonagem(nome);
                if (p.nome != "default") {
                    gerenciarInventario(p, tabelaPersonagens);
                } else {
                    cout << "Personagem n�o encontrado!" << endl;
                }
                break;
            }
            case 5:
                desfazerAcao(tabelaPersonagens, historico);
                break;
            case 6:
                salvarEstadoJogo(tabelaPersonagens);
                break;
            case 7:
                cout << "Saindo..." << endl;
                break;
            default:
                cout << "Op��o inv�lida!" << endl;
        }
    } while (opcao != 7);

    return 0;
}

