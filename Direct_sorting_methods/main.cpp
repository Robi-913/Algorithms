/**
*
* @author Ardelean Robert-Emanuel
* @group 30225
*
* Analiza și Compararea Metodelor Directe de Sortare
*
* Codul permite profilarea si compararea performantei acestor algoritmi in diferite scenarii.
* De asemenea, afiseazs un raport de profilare care indica numarul de atributii și comparari
* efectuate in fiecare scenariu de sortare.
* Acesta ofera date despre eficienta acestor algoritmi de sortare în diferite situatii.
*
*
*1.Bubble Sort:
*
*Complexitatea temporala:
*Cazul favorabil: O(n) (cand numerele sunt deja sortate).
*Cazul defavorabil: O(n^2) (cand numerele sunt sortate in ordine inversa).
*Cazul mediu: O(n^2).
*Complexitatea spațială: O(1) (sortare in loc).
*
*2.Selection Sort:
*
*Complexitatea temporala:
*Cazul favorabil: O(n^2).
*Cazul defavorabil: O(n^2).
*Cazul mediu: O(n^2).
*Complexitatea spațiala: O(1) (sortare in loc).
*
*Insertion Sort:
*
*3.Complexitatea temporala:
*Cazul favorabil: O(n) (cand numerele sunt deja sortate).
*Cazul defavorabil: O(n^2) (cand numerele sunt sortate in ordine inversa).
*Cazul mediu: O(n^2).
*Complexitatea spațială: O(1) (sortare in loc).
*
*
*/

#include <iostream>
#include "Profiler.h"

using namespace std;

#define Max_vector 50000

Profiler prf("complexitate_sortare");

void bubble_sort(int vector[], int nr) {
    Operation nr_atribuiri = prf.createOperation("Nr.atribuiri_bubble", nr);
    Operation nr_comparari = prf.createOperation("Nr.comparari_bubble", nr);

    int repetare;
    do {
        repetare = 0;

        for (int i = 0; i < nr - 1; i++) {
            nr_comparari.count();
            if (vector[i] > vector[i + 1]) {
                nr_atribuiri.count();
                std::swap(vector[i], vector[i + 1]);
                repetare++;
            }
        }
        nr--;

    } while (repetare != 0);

    prf.addSeries("Bubble_Sort", "Nr.atribuiri_bubble", "Nr.comparari_bubble");
}


void selection_sort(int vector[], int nr) {
    Operation nr_atribuiri = prf.createOperation("Nr.atribuiri_selection", nr);
    Operation nr_comparari = prf.createOperation("Nr.comparari_selection", nr);

    int pozitie;

    for (int i = 0; i < nr - 1; i++) {
        pozitie = i; // initializam cu pozitia intexului curent
        for (int j = i + 1; j < nr; j++) {
            nr_comparari.count();
            if (vector[pozitie] > vector[j]) {
                pozitie = j;
            }
        }
        if (pozitie != i) {
            nr_atribuiri.count();
            std::swap(vector[i], vector[pozitie]);
        }
    }

    prf.addSeries("Selection_Sort", "Nr.atribuiri_selection", "Nr.comparari_selection");
}


void insert_sort(int vector[], int nr) {
    Operation nr_atribuiri = prf.createOperation("Nr.atribuiri_insert", nr);
    Operation nr_comparari = prf.createOperation("Nr.comparari_insert", nr);

    for (int i = 1; i < nr; i++) {
        int curent = vector[i];
        int j = i - 1;

        nr_comparari.count();
        while (j >= 0 && vector[j] > curent) {
            nr_comparari.count();
            vector[j + 1] = vector[j];
            nr_atribuiri.count();
            j--;
        }

        vector[j + 1] = curent;
        nr_atribuiri.count();
    }

    prf.addSeries("Insert_Sort", "Nr.atribuiri_insert", "Nr.comparari_insert");
}


void raspuns(char caracter_sortare, int vector[], int n){

    if (caracter_sortare == 'B' || caracter_sortare == 'b') {

        bubble_sort(vector, n);

        std::cout << "Vectorul sortat folosind bubble sort: ";
        for (int i = 0; i < n; i++) {
            std::cout << vector[i] << " ";
        }
        std::cout << endl;

    } else if (caracter_sortare == 'S' || caracter_sortare == 's') {

        selection_sort(vector, n);

        std::cout << "Vectorul sortat folosind selection sort: ";
        for (int i = 0; i < n; i++) {
            std::cout << vector[i] << " ";
        }
        std::cout << endl;

    } else {

        insert_sort(vector, n);

        std::cout << "Vectorul sortat folosind insert sort: ";
        for (int i = 0; i < n; i++) {
            std::cout << vector[i] << " ";
        }
        std::cout << endl;

    }

}

int main() {
    int vector[Max_vector];
    int copie_vector[Max_vector];
    char verificare;

    std::cout << "Ce fel de rulare este?" << endl;
    std::cin >> verificare;

    if (verificare == 'g' || verificare == 'G') {

        // caz favorabil bubble_sort

        for (int i = 100; i <= 10000; i += 100) {
            FillRandomArray(vector, i, 100, Max_vector, false, 1);
            CopyArray( copie_vector,vector, i);
            bubble_sort(copie_vector, i);

        }


        // caz favorabil insert_sort

        for (int i = 100; i <= 10000; i += 100) {
            FillRandomArray(vector, i, 100, Max_vector, false, 1);
            CopyArray( copie_vector,vector, i);
            insert_sort(copie_vector, i);

        }


        // caz favorabil selection_sort

        for (int i = 100; i <= 10000; i += 100) {
            FillRandomArray(vector, i, 100, Max_vector, false, 1);
            CopyArray( copie_vector,vector, i);
            selection_sort(copie_vector, i);

        }


        prf.createGroup("Caz_Favorabil_atribuiri", "Nr.atribuiri_bubble","Nr.atribuiri_insert","Nr.atribuiri_selection");
        prf.createGroup("Caz_Favorabil_comparatii", "Nr.comparari_bubble", "Nr.comparari_insert", "Nr.comparari_selection");
        prf.createGroup("Caz_Favorabil_total", "Bubble_Sort", "Insert_Sort", "Selection_Sort");

        prf.reset("complexitate_sortare");

        // caz defavorabil bubble_sort

        for (int i = 100; i <= 10000; i += 100) {
            FillRandomArray(vector, i, 100, Max_vector, false, 2);
            CopyArray( copie_vector,vector, i);
            bubble_sort(copie_vector, i);

        }


        // caz defavorabil insert_sort

        for (int i = 100; i <= 10000; i += 100) {
            FillRandomArray(vector, i, 100, Max_vector, false, 2);
            CopyArray( copie_vector,vector, i);
            insert_sort(copie_vector, i);

        }


        // caz defavorabil selection_sort

        for (int i = 100; i <= 10000; i += 100) {
            FillRandomArray(vector, i, 100, Max_vector, false, 2);
            CopyArray( copie_vector,vector, i);
            selection_sort(copie_vector, i);

        }


        prf.createGroup("Caz_Defavorabil_atribuiri", "Nr.atribuiri_bubble","Nr.atribuiri_insert","Nr.atribuiri_selection");
        prf.createGroup("Caz_Defavorabil_comparatii", "Nr.comparari_bubble", "Nr.comparari_insert", "Nr.comparari_selection");
        prf.createGroup("Caz_Defavorabil_total", "Bubble_Sort", "Insert_Sort", "Selection_Sort");

        prf.reset("complexitate_sortare");


        //caz mediu bubble_sort

        for (int j = 0; j < 5; j++) {

            for (int i = 100; i <= 10000; i += 100) {
                FillRandomArray(vector, i, 100, Max_vector, false, 0);
                CopyArray( copie_vector,vector, i);
                bubble_sort(copie_vector, i);

            }

        }
        prf.divideValues("Nr.atribuiri_bubble", 5);
        prf.divideValues("Nr.comparari_bubble", 5);
        prf.divideValues("Bubble_Sort", 5);


        //caz mediu insert_sort

        for (int j = 0; j < 5; j++) {

            for (int i = 100; i <= 10000; i += 100) {
                FillRandomArray(vector, i, 100, Max_vector, false, 0);
                CopyArray( copie_vector,vector, i);
                insert_sort(copie_vector, i);

            }

        }
        prf.divideValues("Nr.atribuiri_insert", 5);
        prf.divideValues("Nr.comparari_insert", 5);
        prf.divideValues("Insert_Sort", 5);


        //caz mediu selection_sort

        for (int j = 0; j < 5; j++) {

            for (int i = 100; i <= 10000; i += 100) {
                FillRandomArray(vector, i, 100, Max_vector, false, 0);
                CopyArray( copie_vector,vector, i);
                selection_sort(copie_vector, i);

            }

        }
        prf.divideValues("Nr.atribuiri_selection", 5);
        prf.divideValues("Nr.comparari_selection", 5);
        prf.divideValues("Selection_Sort", 5);

        prf.createGroup("Caz_Mediu_atribuiri", "Nr.atribuiri_bubble","Nr.atribuiri_insert","Nr.atribuiri_selection");
        prf.createGroup("Caz_Mediu_comparatii", "Nr.comparari_bubble", "Nr.comparari_insert", "Nr.comparari_selection");
        prf.createGroup("Caz_Mediu_total", "Bubble_Sort", "Insert_Sort", "Selection_Sort");


        prf.showReport();

    } else {

        int n;
        std::cout << "n=";
        std::cin >> n;

        std::cout << "Intoduceti numerele:" << endl;
        for (int i = 0; i < n; i++) {
            cin >> vector[i];
        }

        char caracter_sortare;
        std::cout << "Ce sortare doriti?" << endl;
        std::cin >> caracter_sortare;

        raspuns(caracter_sortare,vector,n);

    }

    return 0;
}