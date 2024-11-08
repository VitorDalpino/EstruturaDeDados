#include <stdio.h>
#include <stdlib.h>

#define MAX_KEYS 4  // Máximo de 4 chaves por nó (ordem 5)
#define MIN_KEYS 2  // Mínimo de 2 chaves por nó (exceto raiz)

// Definição de um nó da árvore B
typedef struct BTreeNode {
    int keys[MAX_KEYS + 1];          // Chaves armazenadas no nó
    struct BTreeNode* children[MAX_KEYS + 2]; // Ponteiros para filhos
    int numKeys;                     // Número de chaves no nó
    int isLeaf;                      // Indica se o nó é folha
} BTreeNode;

// Função para criar um novo nó da árvore B
BTreeNode* createNode(int isLeaf) {
    BTreeNode* newNode = (BTreeNode*)malloc(sizeof(BTreeNode));
    newNode->isLeaf = isLeaf;
    newNode->numKeys = 0;

    for (int i = 0; i < MAX_KEYS + 2; i++) {
        newNode->children[i] = NULL;
    }

    return newNode;
}

// Função para buscar uma chave na árvore B
BTreeNode* search(BTreeNode* root, int key) {
    if (!root) return NULL;

    int i = 0;
    while (i < root->numKeys && key > root->keys[i]) {
        i++;
    }

    if (i < root->numKeys && key == root->keys[i]) {
        return root;  // A chave foi encontrada
    }

    if (root->isLeaf) {
        return NULL;  // Não é folha, portanto, a chave não foi encontrada
    }

    return search(root->children[i], key);  // Recursivamente buscar nos filhos
}

// Função para dividir um nó quando ele ultrapassa o número máximo de chaves
void splitChild(BTreeNode* parent, int childIndex) {
    BTreeNode* fullChild = parent->children[childIndex];
    BTreeNode* newChild = createNode(fullChild->isLeaf);
    parent->children[childIndex + 1] = newChild;

    // Mover a chave do meio para o nó pai
    parent->keys[childIndex] = fullChild->keys[2];
    parent->numKeys++;

    // Transferir a segunda metade das chaves do nó cheio para o novo nó
    newChild->keys[0] = fullChild->keys[3];
    newChild->numKeys++;

    // Se o nó não for folha, mover os ponteiros de filhos também
    if (!fullChild->isLeaf) {
        newChild->children[0] = fullChild->children[2];
        newChild->children[1] = fullChild->children[3];
        newChild->children[2] = fullChild->children[4];
    }

    fullChild->numKeys = 2;  // Agora o nó cheio tem apenas 2 chaves
}

// Função para inserir uma chave em um nó não cheio
void insertNonFull(BTreeNode* node, int key) {
    int i = node->numKeys - 1;

    if (node->isLeaf) {
        // Encontre a posição correta para inserir a chave
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->numKeys++;
    } else {
        // Encontre o filho para onde a chave deve ser inserida
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;

        if (node->children[i]->numKeys == MAX_KEYS) {
            splitChild(node, i);

            // Depois de dividir, verifique em qual filho a chave deve ser inserida
            if (key > node->keys[i]) {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

// Função para inserir uma chave na árvore B
void insert(BTreeNode** root, int key) {
    BTreeNode* r = *root;

    if (r->numKeys == MAX_KEYS) {
        // Se a raiz está cheia, divide-a
        BTreeNode* newRoot = createNode(0);  // Nova raiz
        newRoot->children[0] = r;
        *root = newRoot;
        splitChild(newRoot, 0);
        insertNonFull(newRoot, key);
    } else {
        insertNonFull(r, key);
    }
}

// Função para excluir uma chave de um nó folha
void deleteFromLeaf(BTreeNode* node, int index) {
    // Desloca as chaves subsequentes para a esquerda para preencher o espaço vazio
    for (int i = index + 1; i < node->numKeys; i++) {
        node->keys[i - 1] = node->keys[i];
    }
    node->numKeys--;
}

// Função para excluir uma chave de um nó não folha
void deleteFromNonLeaf(BTreeNode* node, int index) {
    int key = node->keys[index];

    // Verificar se o filho à esquerda tem pelo menos MIN_KEYS
    if (node->children[index]->numKeys >= MIN_KEYS) {
        // Obter o predecessor (máximo na subárvore à esquerda)
        BTreeNode* pred = node->children[index];
        while (!pred->isLeaf) {
            pred = pred->children[pred->numKeys];
        }

        int predKey = pred->keys[pred->numKeys - 1];
        node->keys[index] = predKey;
        deleteFromLeaf(pred, pred->numKeys - 1);
    } else if (node->children[index + 1]->numKeys >= MIN_KEYS) {
        // Obter o sucessor (mínimo na subárvore à direita)
        BTreeNode* succ = node->children[index + 1];
        while (!succ->isLeaf) {
            succ = succ->children[0];
        }

        int succKey = succ->keys[0];
        node->keys[index] = succKey;
        deleteFromLeaf(succ, 0);
    } else {
        // Fundir os filhos
        merge(node, index);
        deleteFromNonLeaf(node->children[index], MIN_KEYS - 1);
    }
}

// Função para fundir dois filhos
void merge(BTreeNode* parent, int index) {
    BTreeNode* left = parent->children[index];
    BTreeNode* right = parent->children[index + 1];

    // Mover a chave do meio do nó pai para o filho esquerdo
    left->keys[2] = parent->keys[index];
    left->numKeys++;

    // Copiar todas as chaves e filhos do nó direito para o nó esquerdo
    for (int i = 0; i < right->numKeys; i++) {
        left->keys[i + 3] = right->keys[i];
    }
    for (int i = 0; i <= right->numKeys; i++) {
        left->children[i + 3] = right->children[i];
    }

    // Desloca as chaves do nó pai para a esquerda
    for (int i = index + 1; i < parent->numKeys; i++) {
        parent->keys[i - 1] = parent->keys[i];
    }
    parent->numKeys--;

    // Libera o nó direito
    free(right);
}

// Função para excluir uma chave na árvore B
void delete(BTreeNode* root, int key) {
    if (!root) {
        printf("Árvore vazia\n");
        return;
    }

    int i = 0;
    while (i < root->numKeys && key > root->keys[i]) {
        i++;
    }

    if (i < root->numKeys && key == root->keys[i]) {
        if (root->isLeaf) {
            deleteFromLeaf(root, i);
        } else {
            deleteFromNonLeaf(root, i);
        }
    } else if (root->isLeaf) {
        printf("Chave %d não encontrada!\n", key);
        return;
    } else {
        delete(root->children[i], key);
    }
}

// Função para exibir a árvore B
void printTree(BTreeNode* root, int level) {
    printf("Impressão\n");
    if (root != NULL) {
        printf("Nivel %d: ", level);
        for (int i = 0; i < root->numKeys; i++) {
            printf("%d ", root->keys[i]);
        }
        printf("\n");

        if (!root->isLeaf) {
            for (int i = 0; i <= root->numKeys; i++) {
                printTree(root->children[i], level + 1);
            }
        }
    }
    printf("=============\n");
}

int main() {
    BTreeNode* root = createNode(1);  // Cria a raiz, sendo uma folha

    // Inserindo elementos
    insert(&root, 1);
    insert(&root, 2);
    insert(&root, 3);
    printTree(root, 0);
    insert(&root, 4);
    printTree(root, 0);
    insert(&root, 5);
    printTree(root, 0);
    insert(&root, 6);
    insert(&root, 7);
    insert(&root, 8);
    insert(&root, 9);
    insert(&root, 10);
    printf("Árvore B após inserções:\n");
    printTree(root, 0);

    // Excluindo elementos
    delete(root, 10);
    delete(root, 30);
    delete(root, 12);

    printf("\nÁrvore B após exclusões:\n");
    printTree(root, 0);

    return 0;
}