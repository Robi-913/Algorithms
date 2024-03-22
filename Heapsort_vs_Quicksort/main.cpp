
/**
*
* @author Ardelean Robert-Emanuel
* @group 30225
*
*
*QuickSort:
*
*Complexitate în timp: O(n log n) este cea mai bună complexitate și cea mai proastă este O(n^2).
*Complexitatea spațiului: Datorită partiționării neechilibrate, complexitatea medie este O(log n).
*
*HeapSort:
*
*Complexitatea în timp: cea mai bună complexitate este O(n log n), în timp ce cea mai proastă este O(n^2).
*Spațiul este complex: Complexitatea medie este O(log n) ca urmare a partiționării neechilibrate.
*
*BubbleSort (iterative):
*
*În toate cazurile, complexitatea timpului este O(n^2).
*Spațiul este complex: Algoritmul sortează în loc, având o complexitate spațială de O(1).
*
*BubbleSort (recursiv):
*
*În toate cazurile, complexitatea timpului este O(n^2).
*Spațiul este complex: Adâncimea recursivității determină complexitatea spațială, care este mai puțin eficientă decât versiunea iterativă.
*
*
*În rezumat, QuickSort și HeapSort sunt eficiente din punct de vedere al complexității timpului,
*în timp ce BubbleSort este mai puțin eficient, în special pentru seturi de date mai mari.
*HeapSort are avantajul unei complexități spațiale constante, în timp ce complexitatea spațiului QuickSort
*depinde de datele de intrare. Rezultatele profilării oferă informații detaliate despre performanța acestor algoritmi în diverse scenarii.
*
*
*/

#include <iostream>
#include <algorithm>
#include "Profiler.h"

using namespace std;

#define max_size 10000
#define max_size_time 5000
#define time_value 100

Profiler prf("sortare");

int partition(int vector[], int size, int mic, int mare) {

    Operation atrb = prf.createOperation("atrb_quickSort", size);
    Operation comp = prf.createOperation("comp_quickSort", size);

    atrb.count();
    int pivot = vector[mare];
    int i = mic - 1;

    for (int j = mic; j <= mare - 1; j++) {
        comp.count();
        if (vector[j] <= pivot) {
            i++;
            atrb.count();
            std::swap(vector[i], vector[j]);

        }
    }
    atrb.count();
    std::swap(vector[i + 1], vector[mare]);

    prf.addSeries("quickSort", "atrb_quickSort", "comp_quickSort");

    return (i + 1);

}

void quickSort(int vector[], int size, int mic, int mare) {

    if (mic < mare) {

        int q = partition(vector, size, mic, mare);

        quickSort(vector, size, mic, q - 1);
        quickSort(vector, size, q + 1, mare);


    }

}

void quickSort_middlepivot(int vector[], int size, int mic, int mare) {

    Operation atrb = prf.createOperation("atrb_quickSort_mid", size);
    Operation comp = prf.createOperation("comp_quickSort_mid", size);

    if (mic < mare) {
        int i = mic;
        int j = mare;

        atrb.count();
        int pivot = vector[(mic + mare) / 2];

        // Partition
        while (i <= j) {
            comp.count();
            while (vector[i] < pivot) {
                comp.count();
                i++;
            }
            comp.count();
            while (vector[j] > pivot) {
                comp.count();
                j--;
            }
            if (i <= j) {
                atrb.count();
                std::swap(vector[i], vector[j]);
                i++;
                j--;
            }
        }

        prf.addSeries("quickSort_mid", "atrb_quickSort_mid", "comp_quickSort_mid");

        // Recursive calls
        if (mic < j) {
            quickSort_middlepivot(vector, size, mic, j);
        }
        if (i < mare) {
            quickSort_middlepivot(vector, size, i, mare);
        }
    }
}

void heapify(int vector[], int heapSize, int index, int nr) {

    Operation atr = prf.createOperation("atrb_heapSort", nr);
    Operation com = prf.createOperation("comp_heapSort", nr);

    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    com.count();
    if (left < heapSize && vector[left] > vector[largest]) {
        com.count();
        largest = left;

    }

    com.count();
    if (right < heapSize && vector[right] > vector[largest]) {
        com.count();
        largest = right;

    }

    if (largest != index) {

        atr.count();
        std::swap(vector[index], vector[largest]);

        heapify(vector, heapSize, largest, nr);

    }


}

void buildHeapsort(int vector[], int heapSize) {


    for (int i = heapSize / 2 - 1; i >= 0; i--) {

        heapify(vector, heapSize, i, heapSize);

    }

}

void heapSort(int vector[], int heapSize) {

    Operation atr = prf.createOperation("atrb_heapSort", heapSize);
    Operation com = prf.createOperation("comp_heapSort", heapSize);
    buildHeapsort(vector, heapSize);

    for (int i = heapSize - 1; i > 0; i--) {
        atr.count();
        std::swap(vector[0], vector[i]);
        heapify(vector, i, 0, heapSize);
    }
    prf.addSeries("heapSort_final", "atrb_heapSort", "comp_heapSort");

}


void bubbleSort_itr(int vector[], int nr) {
    Operation atr = prf.createOperation("atrb_bubble_itr", nr);
    Operation com = prf.createOperation("comp_bubble_itr", nr);

    int repetare;
    do {
        repetare = 0;

        for (int i = 0; i < nr - 1; i++) {
            com.count();
            if (vector[i] > vector[i + 1]) {
                atr.count();
                std::swap(vector[i], vector[i + 1]);
                repetare++;
            }
        }
        nr--;

    } while (repetare != 0);

    prf.addSeries("bubble_itr", "atrb_bubble_itr", "comp_bubble_itr");
}

void bubbleSort_rec(int vector[], int nr, int nraux) {
    Operation atr = prf.createOperation("atrb_bubble_rec", nraux);
    Operation com = prf.createOperation("comp_bubble_rec", nraux);

    if (nr == 1)
        return;

    int rec = 0;

    for (int i = 0; i < nr - 1; i++) {

        com.count();
        if (vector[i] > vector[i + 1]) {
            atr.count();
            swap(vector[i], vector[i + 1]);
            rec++;
        }

    }

    if (rec == 0)
        return;

    prf.addSeries("bubble_rec", "atrb_bubble_rec", "comp_bubble_rec");

    bubbleSort_rec(vector, nr - 1, nraux);

}

void printare(int vector[], int marime) {

    for (int i = 0; i < marime; i++) {
        std::cout << vector[i] << " ";
    }

}

void raspuns(int verificare_sort, int vector[], int size, int mic, int mare) {

    if (verificare_sort == 1) {

        quickSort(vector, size, mic, mare);
        std::cout << "quickSort:";
        printare(vector, size);


    } else if (verificare_sort == 2) {

        heapSort(vector, size);
        std::cout << "heapSort:";
        printare(vector, size);

    } else if (verificare_sort == 3) {

        bubbleSort_itr(vector, size);
        std::cout << "bubbleSort iterativ::";
        printare(vector, size);

    } else {

        bubbleSort_rec(vector, size, size);
        std::cout << "bubbleSort recursiv::";
        printare(vector, size);

    }
}


int main() {

    int vector[max_size];
    int copie_vector[max_size];
    int verificare;

    std::cout << "1 pentru grafice" << std::endl;
    std::cout << "2 pentru tastura" << std::endl;
    std::cout << "Raspuns:";
    std::cin >> verificare;

    if (verificare == 1) {

        //cazul mediu
        for (int k = 0; k < 5; k++) {

            for (int i = 100; i <= max_size; i += 100) {

                FillRandomArray(vector, i, 100, max_size, false, 0);
                CopyArray(copie_vector, vector, i);
                quickSort(copie_vector, i, 0, i - 1);
                CopyArray(copie_vector, vector, i);
                heapSort(copie_vector, i);

            }

        }

        prf.divideValues("atrb_quickSort", 5);
        prf.divideValues("comp_quickSort", 5);
        prf.divideValues("quickSort", 5);
        prf.divideValues("atrb_heapSort", 5);
        prf.divideValues("comp_heapSort", 5);
        prf.divideValues("heapSort_final", 5);

        prf.createGroup("atrb_mediu_quickSort", "atrb_quickSort");
        prf.createGroup("comp_mediu_quickSort", "comp_quickSort");
        prf.createGroup("Caz_mediu_quickSort", "quickSort");

        prf.createGroup("atrb_mediu", "atrb_quickSort", "atrb_heapSort");
        prf.createGroup("comp_mediu", "comp_quickSort", "comp_heapSort");
        prf.createGroup("Caz_mediu", "quickSort", "heapSort_final");

        prf.reset("sortare");

        //caz favorabil
        //quisksort ordonat crescator cu pivot pe mijloc

        for (int i = 100; i <= max_size; i += 100) {

            FillRandomArray(vector, i, 100, max_size, false, 1);
            CopyArray(copie_vector, vector, i);
            quickSort_middlepivot(copie_vector, i, 0, i - 1);
            CopyArray(copie_vector, vector, i);
            heapSort(copie_vector, i);

        }

        prf.createGroup("atrb_fav_quickSort", "atrb_quickSort_mid");
        prf.createGroup("comp_fav_quickSort", "comp_quickSort_mid");
        prf.createGroup("Caz_fav_quickSort", "quickSort_mid");

//        prf.createGroup("atrb_fav", "atrb_quickSort_mid", "atrb_heapSort");
//        prf.createGroup("comp_fav", "comp_quickSort_mid", "comp_heapSort");
//        prf.createGroup("Caz_fav", "quickSort_mid", "heapSort_final");

        prf.reset("sortare");

        //caz defavorabil
        // quick sort crescator cu pivot pe dreapta
        for (int i = 100; i <= max_size; i += 100) {

            FillRandomArray(vector, i, 100, max_size, false, 1);
            CopyArray(copie_vector, vector, i);
            quickSort(copie_vector, i, 0, i - 1);
            FillRandomArray(vector, i, 100, max_size, false, 2);
            CopyArray(copie_vector, vector, i);
            heapSort(copie_vector, i);

        }

        prf.createGroup("atrb_defav_quickSort", "atrb_quickSort");
        prf.createGroup("comp_defav_quickSort", "comp_quickSort");
        prf.createGroup("Caz_defav_quickSort", "quickSort");

//        prf.createGroup("atrb_defav", "atrb_quickSort", "atrb_heapSort");
//        prf.createGroup("comp_defav", "comp_quickSort", "comp_heapSort");
//        prf.createGroup("Caz_defav", "quickSort", "heapSort_final");

        prf.reset("sortare");


        for (int k = 0; k < 5; k++) {

            for (int i = 100; i <= max_size; i += 100) {

                FillRandomArray(vector, i, 100, max_size, false, 0);
                CopyArray(copie_vector, vector, i);
                bubbleSort_itr(copie_vector, i);
                CopyArray(copie_vector, vector, i);
                bubbleSort_rec(vector, i, i);

            }

        }

        prf.divideValues("atrb_bubble_itr", 5);
        prf.divideValues("comp_bubble_itr", 5);
        prf.divideValues("bubble_itr", 5);
        prf.divideValues("atrb_bubble_rec", 5);
        prf.divideValues("comp_bubble_rec", 5);
        prf.divideValues("bubble_rec", 5);

        prf.createGroup("atrb_bubble", "atrb_bubble_itr", "atrb_bubble_rec");
        prf.createGroup("comp_bubble", "comp_bubble_itr", "comp_bubble_rec");
        prf.createGroup("total_bubble", "bubble_itr", "bubble_rec");



        for (int i = 100; i <= max_size_time; i += 100) {

            FillRandomArray(vector, i, 10, max_size, false, 0);

            prf.startTimer("time_itr", i);
            for (int test = 0; test < time_value; ++test) {

                CopyArray(copie_vector, vector, i);
                bubbleSort_itr(copie_vector, i);

            }
            prf.stopTimer("time_itr", i);

            prf.startTimer("time_rec", i);
            for (int test = 0; test < time_value; ++test) {

                CopyArray(copie_vector, vector, i);
                bubbleSort_rec(copie_vector, i, i);

            }
            prf.stopTimer("time_rec", i);

        }


        prf.divideValues("time_itr", time_value);
        prf.divideValues("time_rec", time_value);


        prf.createGroup("Time", "time_itr", "time_rec");


        prf.showReport();

    } else {

        int marime;

        std::cout << "Marime=";
        std::cin >> marime;

        std::cout << "Intosuceti elementele:" << endl;
        for (int i = 0; i < marime; i++) {

            std::cin >> vector[i];

        }


        int verificare_sort;

        std::cout << "1 pentru quickSort" << endl;
        std::cout << "2 pentru heap sort bottom up" << endl;
        std::cout << "3 pentru bubbleSort iterativ" << endl;
        std::cout << "4 pentru bubbleSort recursiv" << endl;
        std::cout << "Raspuns:";
        std::cin >> verificare_sort;

        raspuns(verificare_sort, vector, marime, 0, marime - 1);


    }


    return 0;
}
