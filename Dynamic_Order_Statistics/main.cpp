/**
*
*
* @author Ardelean Robert-Emanuel
* @group 30225
*
*
*Complexitatea temporala a functiei buildBTree_divide_et_impera este O(n),
*unde n este numarul de noduri din arborele binar.
*Acest lucru se datoreaza faptului ca fiecare nod este vizitat o singura data,
*iar timpul petrecut pe fiecare nod este constant.
*
*Functia OS_SELECT are o complexitate temporala de O(log n),
*unde n este numarul de noduri din arborele de cautare binar.
*Acest lucru se datoreaza impartirii spatiului de cautare la fiecare pas.
*
*Functia OS_DELETE are o complexitate temporala de O(log n) in cazul mediu,
*dar in cel mai rau caz poate fi O(n) atunci cand arborele devine dezechilibrat.
*Aceasta se datoreaza apelurilor recursive si cautarii succesorului in cazul in care nodul de sters are doi copii.
*
*Complexitatea temporala totala a functiei buildBTree,
*atunci cand este apelata in functia main in interiorul buclei,
*este O(n^2 log n), deoarece construieste un arbore binar de dimensiune n in fiecare iteratie a buclei,
*iar fiecare arbore are o inaltime medie de log n.
*
*Complexitatea spatiala este O(n) pentru structurile de arbori binari create in timpul executiei.
*Acest lucru se datoreaza faptului ca fiecare nod in arbore necesita spatiu constant,
*iar in total exista n noduri.
*
*
*/


#include <iostream>
#include "Profiler.h"

Profiler prf("statistici_dinamice");

using namespace std;

#define size_teste 10000

// Structura pentru a reprezenta un nod intr-un arbore binar
struct BinaryTreeNode {
    int data;
    BinaryTreeNode *left;
    BinaryTreeNode *right;
    int size;  // camp pentru a stoca numarul de noduri din subarbore
};

// Functia pentru construirea unui arbore binar folosind metoda divide et impera
BinaryTreeNode *buildBTree_divide_et_impera(int inceput, int final) {


    if (inceput > final) {
        return nullptr;
    }

    // Gasesc medianul pentru a-l folosi ca date pentru nodul curent
    int mediana = (inceput + final) / 2;

    // Construiesc nodul curent
    BinaryTreeNode *node = new BinaryTreeNode;
    node->data = mediana;
    node->size = final - inceput + 1;  // numarul de noduri din subarbore

    // Construiesc recursiv subarborii stang si drept
    node->left = buildBTree_divide_et_impera(inceput, mediana - 1);
    node->right = buildBTree_divide_et_impera(mediana + 1, final);

    return node;
}

// Functia pentru construirea unui arbore binar de dimensiune 'n'
BinaryTreeNode *buildBTree(int n) {
    return buildBTree_divide_et_impera(1, n);
}

// Functia pentru selectarea nodului cu cel de-al i-lea cel mai mic cheie in arborele binar de cautare
BinaryTreeNode *OS_SELECT(BinaryTreeNode *root, int i, Operation atribuiri, Operation comparatii) {

    Operation atr = atribuiri;
    Operation com = comparatii;

    if (root == nullptr) {
        return nullptr;
    }

    // Calculez dimensiunea subarborelui stang
    atr.count();
    int dummySize_left = (root->left) ? root->left->size : 0;

    com.count();
    if (i == dummySize_left + 1) {
        // Daca i este egal cu dimensiunea subarborelui stang plus unu, nodul curent este raspunsul
        return root;
    } else {
        com.count();
        if (i <= dummySize_left) {
            // Daca i este mai mic sau egal cu dimensiunea subarborelui stang, fac recursie pe subarborele stang
            return OS_SELECT(root->left, i, atr, com);
        } else {
            // Daca i este mai mare decat dimensiunea subarborelui stang, fac recursie pe subarborele drept cu un index ajustat
            return OS_SELECT(root->right, i - dummySize_left - 1, atr, com);
        }
    }
}

// Functia pentru stergerea unui nod cu cheia 'i' din arborele binar de cautare
BinaryTreeNode *OS_DELETE(BinaryTreeNode *root, int i, Operation atribuiri, Operation comparari) {

    Operation atr = atribuiri;
    Operation com = comparari;

    if (root == nullptr) {
        return nullptr;
    }

    com.count();
    if (i < root->data) {
        // Daca cheia de sters este mai mica decat cheia radacinii, atunci aceasta se afla in subarborele stang
        atr.count();
        root->left = OS_DELETE(root->left, i, atr, com);
    } else {
        com.count();
        if (i > root->data) {
            // Daca cheia de sters este mai mare decat cheia radacinii, atunci aceasta se afla in subarborele drept
            atr.count();
            root->right = OS_DELETE(root->right, i, atr, com);
        } else {
            // Nodul de sters a fost gasit

            // Cazul 1: Nodul nu are copii sau are doar un copil
            com.count();
            if (root->left == nullptr) {
                atr.count();
                BinaryTreeNode *dummy = root->right;
                delete root;
                return dummy;
            } else {
                com.count();
                if (root->right == nullptr) {
                    atr.count();
                    BinaryTreeNode *dummy = root->left;
                    delete root;
                    return dummy;
                }
            }
            // Cazul 3: Nodul are doi copii
            atr.count();
            BinaryTreeNode *succesor_dummy = root->right;
            com.count();
            while (succesor_dummy->left != nullptr) {
                succesor_dummy = succesor_dummy->left;
            }

            // Inlocuiesc cheia nodului curent cu cheia succesorului
            atr.count();
            root->data = succesor_dummy->data;
            // Sterg succesorul (care acum este duplicat)
            atr.count();
            root->right = OS_DELETE(root->right, succesor_dummy->data, atr, com);
        }
    }

    // Actualizez dimensiunea dupa stergere
    com.count();
    atr.count();
    root->size = 1 + ((root->left) ? root->left->size : 0) + ((root->right) ? root->right->size : 0);

    return root;
}

// Functie pentru afisarea dimensiunii fiecarui nod in arborele binar de cautare
void printSize(BinaryTreeNode *root) {
    if (root == nullptr) {
        return;
    }

    // Parcurgere in ordine pentru afisarea dimensiunilor
    printSize(root->left);
    cout << "Dimensiunea nodului cu data " << root->data << ": " << root->size << endl;
    printSize(root->right);
}

// Functie pentru afisarea arborelui binar de cautare cu indentare corespunzatoare
void printTree(BinaryTreeNode *root, int adancime = 0) {
    const int spatii = 4;

    if (root == nullptr) {
        return;
    }

    // Afisez subarborele drept
    printTree(root->right, adancime + 1);

    // Afisez nodul curent cu indentarea corespunzatoare
    for (int i = 0; i < adancime * spatii; ++i) {
        cout << " ";
    }

    cout << "|-- " << root->data << endl;

    // Afisez subarborele stang
    printTree(root->left, adancime + 1);
}

void demo() {

    int size_n;
    cout << "Introduceti valoarea lui n: ";
    cin >> size_n;

    Operation atr = prf.createOperation("", size_n);
    Operation com = prf.createOperation("", size_n);

    // Construiesc arborele binar de cautare
    BinaryTreeNode *root = buildBTree(size_n);

    // Afisez arborele cu linii
    cout << "Arborele Binar de Cautare:" << endl;
    printTree(root);
    cout << "" << endl;

    // Afisez dimensiunea fiecarui nod inainte de stergere
    cout << "Dimensiunea nodurilor inainte de stergere:" << endl;
    printSize(root);

    for (int i = 0; i < 3; i++) {

        // Selectez cheia a i-a cea mai mica din arbore
        int index_cautare;
        cout << "Introduceti valoarea lui i: ";
        cin >> index_cautare;

        BinaryTreeNode *selectedNode = OS_SELECT(root, index_cautare, atr, com);

        if (selectedNode != nullptr) {
            cout << "Elementul cu cheia a " << index_cautare << "-a cea mai mica este: " << selectedNode->data << endl;
        } else {
            cout << "Valoare i invalida." << endl;
        }

        // Sterg un nod din arbore
        int index_stergere;
        cout << "Introduceti indexul nodului de sters: ";
        cin >> index_stergere;

        //Cautam al i-lea cel mai mic element care il trimitrm pentru sters
        BinaryTreeNode *stergereNode = OS_SELECT(root, index_stergere, atr, com);

        // Actualizez arborele dupa stergere
        root = OS_DELETE(root, stergereNode->data, atr, com);

        // Afisez arborele actualizat
        cout << "Arborele actualizat dupa stergere:" << endl;
        printTree(root);

        // Afisez dimensiunea fiecarui nod dupa stergere
        cout << "Dimensiunea nodurilor dupa stergere:" << endl;
        printSize(root);

    }

}

// Functia principala
int main() {

    int verificare;
    cout << "1 pentru grafice" << endl;
    cout << "2 pentru tastura" << endl;
    cout << "Raspuns:";
    cin >> verificare;

    if (verificare == 1) {

        for (int k = 0; k < 5; k++) {
            for (int j = 100; j <= 10000; j += 100) {

                Operation atr = prf.createOperation("NR_atr", j);
                Operation com = prf.createOperation("NR_com", j);
                BinaryTreeNode *root = buildBTree(j);
                int size_j = j;

                for (int i = 0; i <= size_j; i++) {

                    int index_cautare_sgtergere;
                    FillRandomArray(&index_cautare_sgtergere, 1, 10, size_j, false, 0);
                    BinaryTreeNode *selectare_root = OS_SELECT(root, index_cautare_sgtergere, atr, com);
                    root = OS_DELETE(root, selectare_root->data, atr, com);
                    size_j--;

                }


            }
        }
        prf.addSeries("Nr_total", "NR_atr", "NR_com");

        prf.divideValues("Nr_total", 5);
        prf.divideValues("NR_atr", 5);
        prf.divideValues("NR_com", 5);

        prf.showReport();

    } else {

        //Demo pentru functiile create
        demo();

    }

    return 0;
}
