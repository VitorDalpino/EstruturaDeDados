#include <stdio.h>
#include <stdlib.h>


/*

Hashing
Toda tabela de símbolos armazena objetos de algum tipo. Nesta página, esse tipo será chamado Item. Cada Item tem uma chave, usualmente um número inteiro positivo. As chaves não são necessariamente todas diferentes: dois Items diferentes podem ter chaves iguais.
O universo de chaves é o conjunto de todas as possíveis chaves. Em geral, uma aplicação usa apenas uma pequena parte do universo de chaves. Assim, o tamanho da tabela de símbolos é em geral bem menor que o tamanho do universo de chaves.
Denotaremos o tamanho de nossa tabela por  M.  A tabela terá a forma  tab[0 .. M-1].  É preciso inventar agora uma maneira de mapear o universo de chaves no conjunto de índices da tabela.  Esse é o papel da função de espalhamento (= hash function). Ao receber uma chave v, a função de espalhamento devolve:
=> um número inteiro h no intervalo 0..M-1.

O número h é o código de espalhamento (= hash code) da chave v.
O número de Items que queremos armazenar na tabela é, em geral, maior que M. Assim, a função de espalhamento pode levar várias chaves para o mesmo código. Quando duas chaves diferentes são levadas no mesmo código, dizemos que há uma colisão.
Exemplo:  Digamos que o universo de chaves é o conjunto dos números inteiros entre 100001 e 9999999 (veja o exemplo no capítulo de tabelas de símbolos).  Suponha que M = 100. Podemos adotar os dois últimos dígitos da chave como código de espalhamento. Nesse caso, o código de v é o resto da divisão de v por 100:
chave     código
123456       56
     7531       31
677756       56

*/



#define TABLE_SIZE 10

typedef struct Node {
    int key; 
    int value; 
    struct Node *next;
} Node;

typedef struct HashTable {
    Node **table;
} HashTable;

// Função de hash
unsigned int hash(int key) {
    return key % TABLE_SIZE;
}

// Cria uma nova hash table
HashTable* createHashTable() {
    HashTable *ht = malloc(sizeof(HashTable));
    ht->table = malloc(sizeof(Node*) * TABLE_SIZE);
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
    return ht;
}

// Insere um par chave-valor na hash table
void insert(HashTable *ht, int key, int value) {
    unsigned int index = hash(key);
    Node *newNode = malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = ht->table[index];
    ht->table[index] = newNode;
}

// Busca um valor pela chave
int search(HashTable *ht, int key) {
    unsigned int index = hash(key);
    Node *current = ht->table[index];
    while (current) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return -1; // Retorna -1 se a chave não for encontrada
}

// Exibe todos os pares chave-valor na hash table
void display(HashTable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *current = ht->table[i];
        if (current) {
            printf("Índice %d: ", i);
            while (current) {
                printf("(%d, %d) -> ", current->key, current->value);
                current = current->next;
            }
            printf("NULL\n");
        }
    }
}

// Libera a memória da hash table
void freeHashTable(HashTable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *current = ht->table[i];
        while (current) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(ht->table);
    free(ht);
}

// Exemplo de uso
int main() {
    HashTable *ht = createHashTable();

    // Insere alguns pares chave-valor
    insert(ht, 1, 100);
    insert(ht, 2, 200);
    insert(ht, 12, 300); 
    insert(ht, 3, 400);

    // Busca e exibe valores
    printf("Valor associado à chave 1: %d\n", search(ht, 1));
    printf("Valor associado à chave 2: %d\n", search(ht, 2));
    printf("Valor associado à chave 12: %d\n", search(ht, 12));
    printf("Valor associado à chave 3: %d\n", search(ht, 3));
    printf("Valor associado à chave 4: %d\n", search(ht, 4)); 

    // Exibe todos os pares na hash table
    display(ht);

    freeHashTable(ht);
    return 0;
}