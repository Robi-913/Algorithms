/**
*
*
* @author Ardelean Robert-Emanuel
* @group 30225
*
*
*Complexitatea Timpului:
*
*Inserarea elementelor în liste (distributeElements): O(N),
*unde N reprezintă numărul total de elemente.
*Unirea a două liste sortate (mergeTwoSortedLists): O(N).
*Unirea a K liste sortate (mergeKSortedLists și mergeKSortedListsHeap): O(KN * log(K)),
*unde K este numărul de liste, iar N este numărul total de elemente.
*Complexitatea Spațiului:

*Complexitatea spațiului depinde în principal de memoria alocată pentru liste înlănțuite,
*unirea bazată pe heap (stivă),
*și variabilele temporare. În cel mai rău caz, complexitatea spațiului este O(N),
*unde N reprezintă numărul total de elemente.
*În rezumat, complexitatea timpului este O(KN * log(K)),
*iar complexitatea spațiului este O(N) în cel mai rău caz.
*
*
*/
#include <iostream>
#include <cstdlib>
#include "Profiler.h"

using namespace std;

#define max_lists 500

Profiler prf("K way sort");

struct noduri {
    int key;
    struct noduri *next;
};

typedef struct {
    int arrayIndex;
    int data;
    noduri *nod;
} HeapNod;

noduri *createNode(int el) {
    noduri *newNod = new noduri;
    newNod->key = el;
    newNod->next = NULL;
    return newNod;
}

void insertNodeSorted(noduri *&vector, int value) {
    noduri *newNod = createNode(value);
    noduri *lista_anterioara = NULL;
    noduri *lista_curenta = vector;

    while (lista_curenta != NULL && lista_curenta->key < value) {
        lista_anterioara = lista_curenta;
        lista_curenta = lista_curenta->next;
    }

    if (lista_anterioara == NULL) {
        newNod->next = vector;
        vector = newNod;
    } else {
        newNod->next = lista_curenta;
        lista_anterioara->next = newNod;
    }
}

void printList(noduri *lista) {
    noduri *lista_curenta = lista;
    while (lista_curenta != NULL) {
        cout << lista_curenta->key << " ";
        lista_curenta = lista_curenta->next;
    }
    cout << endl;
}

noduri *mergeTwoSortedLists(noduri *prima_lista, noduri *ultima_lista) {



    noduri temporal;
    noduri *mergelist = &temporal;


    while (prima_lista && ultima_lista) {



        if (prima_lista->key < ultima_lista->key) {

            mergelist->next = prima_lista;
            prima_lista = prima_lista->next;
        } else {

            mergelist->next = ultima_lista;
            ultima_lista = ultima_lista->next;
        }

        mergelist = mergelist->next;
    }


    if (prima_lista) {

        mergelist->next = prima_lista;
    } else {

        mergelist->next = ultima_lista;
    }


    return temporal.next;
}

noduri *mergeKSortedLists(noduri *lista[], int k) {

    if (k == 0) {

        return NULL;

    }

    while (k > 1) {
        int p = 0;
        int r = k - 1;
        while (p < r) {
            lista[p] = mergeTwoSortedLists(lista[p], lista[r]);
            p++;
            r--;
        }
        k = r + 1;
    }

    return lista[0];
}

void heapify(HeapNod *vector, int heapSize, int index, int i,Operation opration) {

    Operation opr = opration;

    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    opr.count();
    if (left < heapSize && vector[left].data < vector[smallest].data) {

        opr.count();
        smallest = left;

    }

    opr.count();
    if (right < heapSize && vector[right].data < vector[smallest].data) {

        opr.count();
        smallest = right;

    }

    if (smallest != index) {

        opr.count();
        swap(vector[index], vector[smallest]);
        heapify(vector, heapSize, smallest, i,opr);

    }

}

void buildMinHeap(HeapNod *vector, int heapSize, int i,Operation opration) {
    for (int j = (heapSize / 2) - 1; j >= 0; j--) {
        heapify(vector, heapSize, j, i,opration);
    }
}

noduri *mergeTwoSortedListsHeap(noduri *lista1, noduri *lista2, int i, Operation opration) {

    Operation opr = opration;


    int sizeHeap = 2;

    HeapNod *minHeap = new HeapNod[2];
    minHeap[0].arrayIndex = 0;
    minHeap[0].data = lista1->key;
    minHeap[0].nod = lista1;

    minHeap[1].arrayIndex = 1;
    minHeap[1].data = lista2->key;
    minHeap[1].nod = lista2;


    buildMinHeap(minHeap, sizeHeap, i,opr);

    noduri temporal;
    noduri *lista_curenta = &temporal;

    opr.count();
    while (minHeap[0].nod != NULL) {

        opr.count();
        HeapNod element_minim = minHeap[0];
        lista_curenta->next = element_minim.nod;
        lista_curenta = lista_curenta->next;
        opr.count();
        minHeap[0].nod = element_minim.nod->next;

        opr.count();
        if (minHeap[0].nod != NULL) {

            opr.count();
            minHeap[0].data = minHeap[0].nod->key;

        } else {

            opr.count();
            minHeap[0].data = INT_MAX;
        }

        heapify(minHeap, sizeHeap, 0, i,opr);
    }

    delete[] minHeap;

    return temporal.next;
}

noduri *mergeKSortedListsHeap(noduri *lista[], int k, int n, Operation opration ) {


    Operation opr=opration;

    if (k == 0) {
        return NULL;
    }

    int copie;

    if(n == 10001){

        copie=k;

    }else{

        copie=n;
    }


    while (k > 1) {
        int p = 0;
        int r = k - 1;
        while (p < r) {
            lista[p] = mergeTwoSortedListsHeap(lista[p], lista[r], copie,opr);
            p++;
            r--;
        }
        k = r + 1;
    }

    return lista[0];
}

void distributeElements(noduri *lists[], int k, int n) {
    int randvector[n];

    FillRandomArray(randvector, n, 10, 1000, false, 0);

    for (int i = 0; i < k; i++) {
        insertNodeSorted(lists[i], randvector[i]);
        n--;
    }

    while (n > 0) {

        int index_lista = rand() % k;
        insertNodeSorted(lists[index_lista], randvector[n - 1]);
        n--;
    }
}

void reconstruireLists(noduri *newLists[], int nr_liste) {

    for (int i = 0; i < nr_liste; i++) {
        newLists[i] = NULL;
    }

}

void deleteList(noduri *&list) {
    noduri *lista_curenta = list;
    while (lista_curenta != NULL) {
        noduri *next = lista_curenta->next;
        delete lista_curenta;
        lista_curenta = next;
    }
    list = NULL;
}

void raspuns(int verificare_sort, noduri *lists[], int nr_liste, int nr_elemente) {
    if (verificare_sort == 1) {
        distributeElements(lists, nr_liste, nr_elemente);

        for (int i = 0; i < nr_liste; i++) {

            cout << "List " << i + 1 << ": ";
            printList(lists[i]);
        }
        noduri *cazul1 = mergeTwoSortedLists(lists[0], lists[1]);
        cout << "Merged List: ";
        printList(cazul1);
        reconstruireLists(lists, nr_liste);
        deleteList(cazul1);

    } else if (verificare_sort == 2) {

        distributeElements(lists, nr_liste, nr_elemente);

        for (int i = 0; i < nr_liste; i++) {
            cout << "List " << i + 1 << ": ";
            printList(lists[i]);
        }
        Operation opr = prf.createOperation("k_way_demo", nr_elemente);
        noduri *cazul2 = mergeTwoSortedListsHeap(lists[0], lists[1], nr_elemente,opr);
        cout << "Merged List: ";
        printList(cazul2);
        reconstruireLists(lists, nr_liste);
        deleteList(cazul2);

    } else if (verificare_sort == 3) {

        distributeElements(lists, nr_liste, nr_elemente);

        for (int i = 0; i < nr_liste; i++) {
            cout << "List " << i + 1 << ": ";
            printList(lists[i]);
        }
        noduri *cazul3 = mergeKSortedLists(lists, nr_liste);
        cout << "Merged List: ";
        printList(cazul3);
        reconstruireLists(lists, nr_liste);
        deleteList(cazul3);

    } else {

        distributeElements(lists, nr_liste, nr_elemente);

        for (int i = 0; i < nr_liste; i++) {
            cout << "List " << i + 1 << ": ";
            printList(lists[i]);
        }
        Operation opr = prf.createOperation("k_way_demo", nr_elemente);
        noduri *cazul4 = mergeKSortedListsHeap(lists, nr_liste, nr_elemente,opr);
        cout << "Merged List: ";
        printList(cazul4);
        reconstruireLists(lists, nr_liste);
        deleteList(cazul4);

    }
}


int main() {
    int verificare;

    std::cout << "1 pentru grafice" << std::endl;
    std::cout << "2 pentru tastura" << std::endl;
    std::cout << "Raspuns:";
    std::cin >> verificare;
    noduri *lists[max_lists] = {NULL};

    if (verificare == 1) {

        for(int j=0; j<5;j++){


            for (int i = 100; i <= 10000; i += 100) {

                Operation opr1 = prf.createOperation("k_way_5", i);
                distributeElements(lists, 5, i);
                noduri *cazul1 = mergeKSortedListsHeap(lists, 5, i,opr1);
                reconstruireLists(lists, 5);
                deleteList(cazul1);


            }

            for (int i = 100; i <= 10000; i += 100) {

                Operation opr2 = prf.createOperation("k_way_10", i);
                distributeElements(lists, 10, i);
                noduri *cazul2 = mergeKSortedListsHeap(lists, 10, i,opr2);
                reconstruireLists(lists, 10);
                deleteList(cazul2);


            }

            for (int i = 100; i <= 10000; i += 100) {

                Operation opr3 = prf.createOperation("k_way_100", i);
                distributeElements(lists, 100, i);
                noduri *cazul3 = mergeKSortedListsHeap(lists, 100, i,opr3);
                reconstruireLists(lists, 100);
                deleteList(cazul3);


            }

        }

        prf.divideValues("k_way_5",5);
        prf.divideValues("k_way_10",5);
        prf.divideValues("k_way_100",5);
        prf.createGroup("k_stabil","k_way_5","k_way_10","k_way_100" );

        prf.reset("K way sort");

        int n = 10001;


        for(int j=0; j<5; j++){

            for (int i = 10; i <= 500; i += 10) {

                distributeElements(lists, i, n);
                Operation opr = prf.createOperation("k_way", i);
                noduri *cazul4 = mergeKSortedListsHeap(lists, i, n,opr);
                reconstruireLists(lists, i);
                deleteList(cazul4);

            }

        }

        prf.divideValues("k_way",5);
        prf.createGroup("n_stabil", "k_way");


        prf.showReport();

    } else {
        int nr_liste;
        int nr_elemente;

        std::cout << "k liste=";
        std::cin >> nr_liste;

        std::cout << "n elemente=";
        std::cin >> nr_elemente;

        if (nr_liste > nr_elemente) {
            std::cout << "K nu poate fi mai mare decat N; Reintoduceti valorile;" << endl;
            std::cout << "k liste=";
            std::cin >> nr_liste;

            std::cout << "n elemente=";
            std::cin >> nr_elemente;
        }

        int verificare_merge;

        std::cout << "1 pentru merge two lists" << endl;
        std::cout << "2 pentru merge two lists cu heap" << endl;
        std::cout << "3 pentru merge k lists" << endl;
        std::cout << "4 pentru merge k lists cu heap" << endl;
        std::cout << "Raspuns:";
        std::cin >> verificare_merge;

        raspuns(verificare_merge, lists, nr_liste, nr_elemente);
    }

    return 0;
}
