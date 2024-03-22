/**
*
*
* @author Ardelean Robert-Emanuel
* @group 30225
*
*
*creareParentArray
*
*Intrare: Radacina arborelui MultiWay (TreeNode *root), un array pentru a stoca relatiile parinte-copil (int *parentArray).
*Operatie: Parcurge arborele MultiWay in adancime, salvand indicii parintilor in array.
*Scop: Creaza un array care reprezinta relatiile parinte-copil intr-un arbore MultiWay.
*
*buildMultiWayTree
*
*Intrare: Array ce reprezinta relatiile parinte-copil (int *parentArray), dimensiunea array-ului (int size_array).
*Operatie: Construieste un arbore MultiWay folosind un array de MultiWayTreeNode.
*Scop: Construieste un arbore MultiWay din relatiile parinte-copil.
*
*convertToBinaryTree
*
*Intrare: Radacina unui arbore MultiWay (MultiWayTreeNode *multiWayRoot).
*Operatie: Converteste un arbore MultiWay intr-un arbore Bin.
*Scop: Transforma un arbore MultiWay intr-un arbore Bin.
*
*printMultiWayTree
*
*Intrare: Radacina unui arbore MultiWay (MultiWayTreeNode *root), parametru optional pentru adancime (int adancime).
*Operatie: Afiseaza arborele MultiWay intr-un format indentat vizual.
*Scop: Reprezentare vizuala a unui arbore MultiWay.
*
*printBinaryTree
*
*Intrare: Radacina unui arbore Bin (const BinaryTreeNode *root).
*Operatie: Afiseaza arborele Bin cu linii care conecteaza nodurile.
*Scop: Reprezentare vizuala a unui arbore Bin.
*
*Complexitate:
*
*creareParentArray: O(n), unde n este numarul total de noduri in arborele MultiWay.
*buildMultiWayTree: O(n), unde n este dimensiunea array-ului parentArray.
*convertToBinaryTree: O(n), unde n este numarul total de noduri in arborele MultiWay.
*printMultiWayTree si printBinaryTree: O(n), unde n este numarul total de noduri in arborii respectivi. Operatia de afisare pentru fiecare nod are o complexitate constanta.
*
*/

#include <iostream>
#include <queue>

using namespace std;

// Structura pentru un nod de arbore cu mai multi copii
struct TreeNode {
    int data;
    TreeNode **Childrens; // Vector de pointeri catre copii
    int nrChildren;       // Numarul de copii
};

const int nr_copii = 10; // Numarul maxim de copii pentru MultiWayTreeNode

// Structura pentru un nod de arbore cu mai multi copii
struct MultiWayTreeNode {
    int data;
    MultiWayTreeNode *Childrens[nr_copii]; // Vector de pointeri catre copii
    int nrChildren;                         // Numarul de copii
};

// Structura pentru un nod de arbore binar
struct BinaryTreeNode {
    int data;
    BinaryTreeNode *left;
    BinaryTreeNode *right;
};

// Functie pentru a crea un nod de arbore cu mai multi copii
TreeNode *creare_nod(int data, int nr_copii_nod) {
    TreeNode *nod = new TreeNode;
    nod->data = data;
    nod->nrChildren = nr_copii_nod;
    nod->Childrens = new TreeNode *[nr_copii_nod];
    return nod;
}

// Functie pentru a construi recursiv un arbore
TreeNode *buildTree(int data) {
    int nrChildrens;
    cout << "Introduceti numarul de copii pentru nodul " << data << ": ";
    cin >> nrChildrens;

    TreeNode *nod = creare_nod(data, nrChildrens);

    for (int i = 0; i < nrChildrens; i++) {
        cout << "Introduceti valoarea copilului " << i + 1 << " al nodului " << data << ":\n";
        int childData;
        cin >> childData;
        nod->Childrens[i] = buildTree(childData);
    }

    return nod;
}

// Functie pentru a gasi valoarea maxima intr-un arbore
int find_max_val(TreeNode *root) {
    if (root == nullptr) {
        return 0;
    }

    int val_max = root->data;

    for (int i = 0; i < root->nrChildren; i++) {
        int copil_max = find_max_val(root->Childrens[i]);
        if (copil_max > val_max) {
            val_max = copil_max;
        }
    }

    return val_max;
}

// Functie pentru a crea un array care reprezinta relatii parinte-copil
void creareParentArray(TreeNode *root, int *parentArray, int parinte = -1) {
    if (root == nullptr) {
        return;
    }

    // Se seteaza parintele nodului curent in parentArray
    parentArray[root->data - 1] = parinte;

    // Se apeleaza recursiv functia pentru fiecare copil
    for (int i = 0; i < root->nrChildren; i++) {
        creareParentArray(root->Childrens[i], parentArray, root->data);
    }
}

// Functie pentru a construi un arbore MultiWay dintr-un array de parinti
MultiWayTreeNode *buildMultiWayTree(int *parentArray, int size_array) {
    if (size_array <= 0 || parentArray == nullptr) {
        return nullptr;
    }

    // Se creeaza un array de MultiWayTreeNode
    MultiWayTreeNode *noduri = new MultiWayTreeNode[size_array];

    // Se initializeaza nodurile cu datele lor si zero copii
    for (int i = 0; i < size_array; ++i) {
        noduri[i].data = i + 1;
        noduri[i].nrChildren = 0;
    }

    MultiWayTreeNode *root_temp = nullptr;

    // Se itereaza prin parentArray pentru a construi arborele
    for (int i = 0; i < size_array; ++i) {
        if (parentArray[i] == -1) {
            root_temp = &noduri[i];
        } else {
            // Se conecteaza nodul curent ca fiind copil al parintelui sau
            MultiWayTreeNode *parent = &noduri[parentArray[i] - 1];
            parent->Childrens[parent->nrChildren++] = &noduri[i];
        }
    }

    return root_temp;
}

// Functie pentru a converti un arbore MultiWay intr-un arbore Binar
BinaryTreeNode *convertToBinaryTree(MultiWayTreeNode *multiWayRoot) {
    if (multiWayRoot == nullptr) {
        return nullptr;
    }

    // Se creeaza un nod de arbore Binar cu datele din radacina arborelui MultiWay
    BinaryTreeNode *binaryRoot = new BinaryTreeNode;
    binaryRoot->data = multiWayRoot->data;
    binaryRoot->left = nullptr;
    binaryRoot->right = nullptr;

    // Daca exista copii in arborele MultiWay, acestia sunt convertiti in noduri de arbore Binar
    if (multiWayRoot->nrChildren > 0) {
        binaryRoot->left = convertToBinaryTree(multiWayRoot->Childrens[0]);

        BinaryTreeNode *temp = binaryRoot->left;

        // Se conecteaza ceilalti copii ca fiind copii drept in arborele Binar
        for (int i = 1; i < multiWayRoot->nrChildren; ++i) {
            temp->right = convertToBinaryTree(multiWayRoot->Childrens[i]);
            temp = temp->right;
        }
    }

    return binaryRoot;
}

// Functie pentru a afisa un arbore MultiWay
void printMultiWayTree(MultiWayTreeNode *root, int adancime = 0) {
    if (root == nullptr) {
        return;
    }

    // Se afiseaza datele nodului curent
    for (int i = 0; i < adancime; ++i) {
        cout << "    ";
    }
    cout << "|-- " << root->data << endl;

    // Se apeleaza recursiv functia pentru fiecare copil
    for (int i = 0; i < root->nrChildren; ++i) {
        printMultiWayTree(root->Childrens[i], adancime + 1);
    }
}

// Functie pentru a afisa un arbore Binar
void printBT(const string &linii, const BinaryTreeNode *root, bool isLeft) {
    if (root != nullptr) {
        // Se afiseaza datele nodului curent
        cout << linii;
        cout << (isLeft ? "|--" : "L--");
        cout << root->data << endl;

        // Se apeleaza recursiv functia pentru copiii din stanga si dreapta
        printBT(linii + (isLeft ? "|   " : "    "), root->right, true);
        printBT(linii + (isLeft ? "|   " : "    "), root->left, false);
    }
}

// Functie pentru a afisa un arbore Binar
void printBinaryTree(const BinaryTreeNode *root) {
    printBT("", root, false);
}

// Functia principala
int main() {
    cout << "Introduceti radacina:\n";
    int root;
    cin >> root;

    // Se construieste arborele
    TreeNode *rootdata = buildTree(root);

    // Se gaseste valoarea maxima in arbore
    int val_max = find_max_val(rootdata);

    // Se creeaza un array care reprezinta relatii parinte-copil
    int *parentArray = new int[val_max];
    for (int i = 0; i < val_max; i++) {
        parentArray[i] = 0;
    }

    // Se completeaza array-ul cu relatii parinte-copil
    creareParentArray(rootdata, parentArray);

    // Se afiseaza array-ul de relatii parinte-copil
    cout << "Array de reprezentare a relatiilor parinte-copil:\n";
    cout << "pi = { ";
    for (int i = 0; i < val_max; i++) {
        if (parentArray[i] != 0) {
            cout << parentArray[i] << " ";
        }
    }
    cout << "}\n";

    // Se construieste arborele MultiWay
    MultiWayTreeNode *multiWayRoot = buildMultiWayTree(parentArray, val_max);

    // Se afiseaza arborele MultiWay
    cout << "Arbore MultiWay:\n";
    printMultiWayTree(multiWayRoot);

    // Se converteste arborele MultiWay in arbore Binar
    BinaryTreeNode *binaryRoot = convertToBinaryTree(multiWayRoot);

    // Se afiseaza arborele Binar
    cout << "Arbore Binar:\n";
    printBinaryTree(binaryRoot);

    // Se elibereaza memoria
    delete[] parentArray;
    delete rootdata;

    return 0;
}
