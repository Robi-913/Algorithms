/**
*
* @author Ardelean Robert-Emanuel
* @group 30225
*
*
* 1. Construcția Heap Bottom-Up (build_BottomUp_Heap):
*
* Complexitatea în timp: O(n), unde 'n' reprezintă dimensiunea heap-ului. Acest lucru se datorează faptului că
* parcurge elementele o singură dată și apelează funcția *bottom_upHeapify pentru fiecare element.
* Complexitatea în spațiu: O(1), deoarece utilizează o cantitate constantă de spațiu suplimentar pentru variabile.
*
* 2. Construcția Heap Top-Down (build_TopDown_Heap):
*
* Complexitatea în timp: O(n log n), unde 'n' reprezintă dimensiunea heap-ului.
* Acest lucru se datorează faptului că, în cel mai rău caz, operația de top-down heapify durează *O(log n) timp, iar aceasta este apelată pentru fiecare element.
* Complexitatea în spațiu: O(log n) din cauza apelurilor recursive pe stiva de apel.
*
* 3. Heapify Bottom-Up (bottom_upHeapify):
*
* Complexitatea în timp: O(log n), unde 'n' reprezintă dimensiunea heap-ului. Aceasta reprezintă înălțimea heap-ului.
* Complexitatea în spațiu: O(1).
*
* 4. Heapify Top-Down (top_downHeapify):
*
* Complexitatea în timp: O(log n), unde 'n' reprezintă dimensiunea heap-ului. Aceasta reprezintă înălțimea heap-ului.
* Complexitatea în spațiu: O(log n) datorită apelurilor recursive pe stiva de apel.
*
* 5. Sortare Heap (heapSortBottomUp și heapSortTopDown):
*
* Complexitatea în timp: O(n log n), unde 'n' reprezintă dimensiunea heap-ului. Aceasta este complexitatea în cel mai rău caz pentru sortarea heap-ului.
* Complexitatea în spațiu: O(1), deoarece sortează elementele în loc.
*
* 6. Complexitatea spațiului pentru printHeap:
*
* Complexitatea în timp: O(n), unde 'n' reprezintă dimensiunea heap-ului, deoarece parcurge și tipărește fiecare element.
* Complexitatea în spațiu: O(1), deoarece nu utilizează spațiu suplimentar.
*
* 7. Complexitatea totală a spațiului (main și alte funcții):
*
* Complexitatea în spațiu: O(n) pentru majoritatea funcțiilor datorită stocării vectorului de intrare și a unor variabile locale.
*
*/


#include <iostream>
#include "Profiler.h"

using namespace std;

#define max_value 10000

Profiler prf("complexitate_heap");

void bottom_upHeapify(int vector[], int sizeHeap, int index) {


    Operation nr_atribuiri = prf.createOperation("Nr.atribuiri_bottom_up_heap", sizeHeap);
    Operation nr_comparari = prf.createOperation("Nr.comparari_bottom_up_heap", sizeHeap);

    int largest = index; // Initialize largest as root
    int left = 2 * index + 1; // left = 2*i + 1
    int right = 2 * index + 2; // right = 2*i + 2

    nr_comparari.count();
    // If left child is larger than root, left becomes largest
    if (left < sizeHeap && vector[left] > vector[largest]) {
        nr_comparari.count();
        largest = left;
    }

    nr_comparari.count();
    // If right child is larger than largest becomes right
    if (right < sizeHeap && vector[right] > vector[largest]) {
        nr_comparari.count();
        largest = right;
    }


    // If largest is not root, will swap the values
    if (largest != index) {
        nr_atribuiri.count();
        std::swap(vector[index], vector[largest]);

        bottom_upHeapify(vector, sizeHeap, largest);
    }

    prf.addSeries("Bottom_up", "Nr.atribuiri_bottom_up_heap", "Nr.comparari_bottom_up_heap");


}


void build_BottomUp_Heap(int vector[], int heapSize) {
    for (int i = (heapSize / 2) - 1; i >= 0; i--) {
        bottom_upHeapify(vector, heapSize, i);
    }
}


void top_downHeapify(int vector[], int sizeHeap, int index) {

    Operation nr_atribuiri = prf.createOperation("Nr.atribuiri_top_down_heap", sizeHeap);
    Operation nr_comparari = prf.createOperation("Nr.comparari_top_down_heap", sizeHeap);

    int parent = (index - 1) / 2;

    nr_comparari.count();
    if (parent >= 0 && vector[index] > vector[parent]) {
        nr_comparari.count();
        nr_atribuiri.count();
        std::swap(vector[index], vector[parent]);

        top_downHeapify(vector, sizeHeap, parent);
    }

    prf.addSeries("Top_down", "Nr.atribuiri_top_down_heap", "Nr.comparari_top_down_heap");

}


void build_TopDown_Heap(int vector[], int sizeHeap) {

    for (int i = 0; i < sizeHeap; i++) {
        top_downHeapify(vector, sizeHeap, i);
    }
}

void siftDown(int vector[], int start, int end) {
    int root = start;
    int maxChild;

    while ((maxChild = 2 * root + 1) <= end) {
        if (maxChild + 1 <= end && vector[maxChild] < vector[maxChild + 1]) {
            maxChild++;
        }

        if (vector[root] >= vector[maxChild]) {
            break;
        }

        std::swap(vector[root], vector[maxChild]);
        root = maxChild;
    }
}

void heapSortBottomUp(int vector[], int size) {
    build_BottomUp_Heap(vector, size);

    for (int i = size - 1; i > 0; i--) {
        std::swap(vector[0], vector[i]);
        bottom_upHeapify(vector, i, 0);
    }
}

void heapSortTopDown(int vector[], int sizeHeap) {
    // Build a max heap
    build_TopDown_Heap(vector, sizeHeap);

    for (int i = sizeHeap - 1; i > 0; i--) {
        swap(vector[0], vector[i]);
        siftDown(vector, 0, i - 1);
    }
}

void printHeap(int vector[], int sizeheap) {

    for (int i = 0; i < sizeheap; i++) {
        std::cout << vector[i] << " ";
    }

}


void raspuns(int verificare_heap, int vector[], int sizeHeap) {

    if (verificare_heap == 1) {

        build_BottomUp_Heap(vector, sizeHeap);
        std::cout << "bottom-up heap:";
        printHeap(vector, sizeHeap);


    } else if (verificare_heap == 2) {

        build_TopDown_Heap(vector, sizeHeap);
        std::cout << "top-down heap:";
        printHeap(vector, sizeHeap);

    }  else if (verificare_heap == 3) {

        heapSortBottomUp(vector, sizeHeap);
        std::cout << "heap sort bottom up:";
        printHeap(vector, sizeHeap);


    }else{

        heapSortTopDown(vector, sizeHeap);
        std::cout << "heap sort top down:";
        printHeap(vector, sizeHeap);

    }
}

int main() {

    int vector[max_value];
    int copie_vector[max_value];
    int verificare;

    std::cout << "1 pentru grafice" << endl;
    std::cout << "2 pentru tastura" << endl;
    std::cout << "Raspuns:";
    std::cin >> verificare;

    if (verificare == 1) {

        //caz defavorabil
        for (int i = 100; i <= max_value; i += 100) {

            FillRandomArray(vector, i, 100, max_value, false, 1);
            CopyArray(copie_vector, vector, i);
            build_BottomUp_Heap(copie_vector, i);

        }

        for (int i = 100; i < max_value; i += 100) {

            FillRandomArray(vector, i, 100, max_value, false, 1);
            CopyArray(copie_vector, vector, i);
            build_TopDown_Heap(copie_vector, i);

        }

        prf.createGroup("Caz_Defavorabil_atribuiri", "Nr.atribuiri_bottom_up_heap", "Nr.atribuiri_top_down_heap");
        prf.createGroup("Caz_Defavorabil_comparatii", "Nr.comparari_bottom_up_heap", "Nr.comparari_top_down_heap");
        prf.createGroup("Caz_Defavorabil_total", "Top_down", "Bottom_up");

        prf.reset("complexitate_heap");


        //caz mediu
        for (int j = 0; j < 5; j++) {

            for (int i = 100; i <= max_value; i += 100) {

                FillRandomArray(vector, i, 100, max_value, false, 0);
                CopyArray(copie_vector, vector, i);
                build_BottomUp_Heap(copie_vector, i);

            }

            for (int i = 100; i < max_value; i += 100) {

                FillRandomArray(vector, i, 100, max_value, false, 0);
                CopyArray(copie_vector, vector, i);
                build_TopDown_Heap(copie_vector, i);

            }

        }

        prf.divideValues("Nr.atribuiri_bottom_up_heap", 5);
        prf.divideValues("Nr.comparari_bottom_up_heap", 5);
        prf.divideValues("Bottom_up", 5);
        prf.divideValues("Nr.atribuiri_top_down_heap", 5);
        prf.divideValues("Nr.comparari_top_down_heap", 5);
        prf.divideValues("Top_down", 5);

        prf.createGroup("Caz_Mediiu_atribuiri", "Nr.atribuiri_bottom_up_heap", "Nr.atribuiri_top_down_heap");
        prf.createGroup("Caz_Mediu_comparatii", "Nr.comparari_bottom_up_heap", "Nr.comparari_top_down_heap");
        prf.createGroup("Caz_Mediu_total", "Top_down", "Bottom_up");


        prf.showReport();


    } else {

        int sizeHeap;

        std::cout << "Marimea heap:";
        std::cin >> sizeHeap;

        std::cout << "Intosuceti elementele:" << endl;
        for (int i = 0; i < sizeHeap; i++) {

            std::cin >> vector[i];

        }

        int verificare_heap;
        std::cout << "1 pentru bottom up" << endl;
        std::cout << "2 pentru top down" << endl;
        std::cout << "3 pentru heap sort bottom up" << endl;
        std::cout << "4 pentru heap sort top down" << endl;
        std::cout << "Raspuns:";
        std::cin >> verificare_heap;

        raspuns(verificare_heap, vector, sizeHeap);


    }


    return 0;
}