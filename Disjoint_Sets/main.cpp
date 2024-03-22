/**
*
*
* @author Ardelean Robert-Emanuel
* @group 30225
*
*
*Complexitate Temporala:
*
*Sortarea Muchiilor (Selection Sort):
*
*Timp: O(n^2) în cel mai rău caz.
*Spatiu: O(1) deoarece se sortează vectorul de muchii în loc.
*Initializarea Seturilor și FIND_SET:
*
*Initializarea seturilor: O(n), unde n este numărul de muchii.
*
*FIND_SET în medie: Aproape O(1) datorită compresiei de drumuri (path compression).
*Spatiu: O(n) pentru stocarea seturilor.
*
*Iterarea Prin Muchii și Aplicarea UNION:
*
*În cel mai rău caz, toate muchiile sunt procesate,
*iar fiecare apel UNION efectuează O(1) operații.
*Timp total: O(E log V), unde E este numărul de muchii și V este numărul de noduri.
*
*Complexitate Spatiala:
*
*Structurile de Date:
*
*Spatiu pentru DisjointSet: O(n), unde n este numărul de muchii.
*Alte Variabile:
*
*Spatiu pentru vectorul de muchii: O(n).
*Spatiu pentru MST: O(n).
*
*Total:
*
*Spatiu total: O(n).
*
*Observații și Concluzii:
*
*Algoritmul lui Kruskal are o complexitate temporală eficientă în practică datorită utilizării compresiei de drumuri în operația FIND_SET.
*Sortarea muchiilor este cea mai costisitoare operație în termeni de timp,
*dar pot exista implementări mai eficiente cu algoritmi de sortare mai rapizi.
*Spatiul utilizat de acest algoritm este rezonabil și nu depinde de dimensiunea grafului,
*ci doar de numărul de muchii.
*În general, algoritmul lui Kruskal este o opțiune bună pentru găsirea Arborelui de Acoperire Minim în grafuri,
*și complexitatea sa poate fi îmbunătățită prin utilizarea unor algoritmi de sortare mai eficiente.
*
*
*
*/

#include <iostream>
#include <algorithm>
#include "Profiler.h"

using namespace std;

#define max_size 10000

Profiler prf("DisjointSet");

struct DisjointSet {
    DisjointSet* parinte;
    int data;
    int rang;
};

struct Muchie {
    int sursa;
    int destinatie;
    int greutate;
};

DisjointSet* MAKE_SET(int x, Operation operation) {
    Operation opr = operation;
    DisjointSet* set = new DisjointSet;
    opr.count(2);
    set->parinte = set; // Initial, setul este propriul său părinte (reprezentant)
    set->data = x;
    set->rang = 0;
    return set;
}

DisjointSet* FIND_SET(DisjointSet* x, Operation operation) {
    Operation opr = operation;

    opr.count();
    if (x->parinte != x) {
        opr.count();
        x->parinte = FIND_SET(x->parinte, opr); // Compresie de drumuri
    }
    return x->parinte;
}

void LINK(DisjointSet* x, DisjointSet* y, Operation operation) {
    Operation opr = operation;

    opr.count();
    if (x->rang > y->rang) {
        opr.count();
        y->parinte = x;
    } else {
        opr.count();
        x->parinte = y;
        opr.count();
        if (x->rang == y->rang) {
            opr.count();
            y->rang++;
        }
    }
}

void UNION(DisjointSet* x, DisjointSet* y, Operation operation) {
    Operation opr = operation;
    LINK(FIND_SET(x, opr), FIND_SET(y, opr), opr);
}

void displaySets(DisjointSet* sets[], int numSets, Operation operation) {
    Operation opr = operation;
    cout << "Seturi Disjuncte:" << endl;
    for (int i = 0; i < numSets; ++i) {
        DisjointSet* set = sets[i];
        DisjointSet* representative = FIND_SET(set, opr);
        cout << " Reprezentant: " << representative->data << " Set: " << i << endl;
    }
    cout << endl;
}

void prettyUnion(DisjointSet* sets[], int x, int y, int Seturi, Operation operation) {

    Operation opr = operation;

    DisjointSet* set1 = FIND_SET(sets[x], opr);
    DisjointSet* set2 = FIND_SET(sets[y], opr);

    if (set1 != set2) {
        cout << "Executarea operatiei UNION pentru seturile care contin elementele " << x << " si " << y << endl;
        cout << "Inainte de UNION:" << endl;
        displaySets(sets, Seturi, opr);

        UNION(set1, set2, opr);

        cout << "După UNION:" << endl;

        // Afișează elementele reprezentative după UNION
        cout << "Reprezentantul setului " << x << ": " << FIND_SET(sets[x], opr)->data << endl;
        cout << "Reprezentantul setului " << y << ": " << FIND_SET(sets[y], opr)->data << endl;

        displaySets(sets, Seturi, opr);
    } else {
        cout << "Elementele " << x << " si " << y << " sunt deja in acelasi set." << endl;
    }
}

void displayGraph(Muchie edges[], int numEdges) {
    cout << "Graf:" << endl;
    for (int i = 0; i < numEdges; ++i) {
        cout << "Muchie " << i + 1 << ": " << edges[i].sursa << " -- " << edges[i].destinatie << " : " << edges[i].greutate << endl;
    }
    cout << endl;
}

void displayMST(Muchie mst[], int numEdges) {
    cout << "Arborele de Acoperire Minim:" << endl;
    for (int i = 0; i < numEdges; ++i) {
        cout << "Muchie: " << mst[i].sursa << " -- " << mst[i].destinatie << " : " << mst[i].greutate << endl;
    }
    cout << endl;
}

void selectionSort(Muchie arr[], int n) {

    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j].greutate < arr[minIdx].greutate) {
                minIdx = j;
            }
        }
        std::swap(arr[i], arr[minIdx]);
    }
}

void Kruskal(Muchie edges[], int numEdges, Muchie mst[], int& mstIndex, Operation operation) {

    Operation opr = operation;
    // Sortează muchiile pe baza greutății folosind sortarea prin selecție
    selectionSort(edges, numEdges);

    // Creează seturi disjuncte pentru fiecare vârf
    DisjointSet** sets = new DisjointSet*[numEdges];
    for (int i = 0; i < numEdges; ++i) {
        opr.count();
        sets[i] = MAKE_SET(i, opr);
    }

    // Iterează prin muchiile sortate și le adaugă în arborele de acoperire minim
    for (int i = 0; i < numEdges && mstIndex < numEdges - 1; ++i) {
        opr.count(2);
        DisjointSet* set1 = FIND_SET(sets[edges[i].sursa], opr);
        DisjointSet* set2 = FIND_SET(sets[edges[i].destinatie], opr);

        opr.count();
        if (set1 != set2) {
            opr.count();
            mst[mstIndex++] = edges[i];
            UNION(set1, set2, opr);
        }
    }

    // Eliberează memoria
    for (int i = 0; i < numEdges; ++i) {
        delete sets[i];
    }
    delete[] sets;
}

void generateRandomGraph(Muchie muchii[], int n, int greutateMaxima) {

    // Generează un graf aleator conectat cu greutăți aleatoare

    for (int i = 0; i < n; i++) {
        for(int j=i*4; j<=(i+1)*4; j++){

            muchii[i].sursa = i;
            muchii[i].destinatie = (i + 1) % n;  // Conectare la nodul următor
            FillRandomArray(&muchii[i].greutate, 1, 1, greutateMaxima);

        }

    }


}

void demo(){

    Operation opr = prf.createOperation("", 0);

    cout << "Numarul de seturi:";
    int Seturi;
    cin >> Seturi;

    DisjointSet** ds = new DisjointSet*[Seturi];

    // Creează și afișează seturi
    cout << "Creare si Afisare a " << Seturi << " Seturi:" << endl;
    for (int i = 0; i < Seturi; ++i) {
        int element;
        cout << "Introduceti un element pentru setul " << i << ": ";
        cin >> element;

        // Inițializare fiecare element ca un set separat
        ds[i] = MAKE_SET(element, opr);
    }

    // Afișează seturi înainte de aplicarea UNION
    cout << "Afisare seturi inainte de aplicarea UNION:" << endl;
    displaySets(ds, Seturi, opr);

    cout << "Numarul de Union:";
    int SetUnion;
    cin >> SetUnion;

    // Aplică UNION
    cout << "Aplicare UNION pentru " << SetUnion << " seturi:" << endl;
    for (int i = 0; i < SetUnion; ++i) {
        // Inside demo() or any other function
        int x, y;
        cout << "Introduceti elementul x pentru UNION: ";
        cin >> x;
        cout << "Introduceti elementul y pentru UNION: ";
        cin >> y;

        prettyUnion(ds, x, y, Seturi, opr);
    }

    cout << "FIND_SET:" << endl;
    int findSetElement;
    cout << "Introduceti un element pentru operatia FIND_SET: ";
    cin >> findSetElement;

    // Găsește reprezentantul folosind FIND_SET
    DisjointSet* findSetResult = FIND_SET(ds[findSetElement], opr);
    cout << "Reprezentantul setului care contine elementul " << findSetElement << " este: " << findSetResult->data << endl;

    // Afișează conținutul seturilor după aplicarea FIND_SET
    cout << "Continutul Seturilor dupa aplicarea FIND_SET:" << endl;
    displaySets(ds, Seturi, opr);

    // Eliberare memorie pentru array de seturi
    for (int i = 0; i < Seturi; ++i) {
        delete ds[i];
    }
    delete[] ds;

    cout << "Introduceti numarul de muchii in graf:";
    int n; // Numărul de vârfuri în graf
    cin >> n;

    Muchie muchii[n];

    for (int i = 0; i < n; i++) {
        cout << "Introduceti sursa muchiei " << i << ":";
        cin >> muchii[i].sursa;
        cout << "Introduceti destinatarul muchiei " << i << ":";
        cin >> muchii[i].destinatie;
        cout << "Introduceti ponderea muchiei " << i << ":";
        cin >> muchii[i].greutate;
    }

    // Afișează graful original
    displayGraph(muchii, n);

    // Vector pentru stocarea muchiilor Arborelui de Acoperire Minim (MST)
    Muchie mst[n];
    int dimensiuneMST = 0;

    // Aplică algoritmul lui Kruskal
    Kruskal(muchii, n, mst, dimensiuneMST, opr);

    // Afișează muchiile Arborelui de Acoperire Minim
    displayMST(mst, dimensiuneMST);

}

int main() {

    Muchie muchie[max_size*4];
    Muchie mst[max_size*4];
    int verificare;
    cout << "1 pentru grafice" << endl;
    cout << "2 pentru tastatura" << endl;
    cout << "Raspuns:";
    cin >> verificare;

    if (verificare == 1) {

        int dimensiuneMST;

        for(int i=100; i<=max_size; i+=100){

            Operation opr = prf.createOperation("Kruskal",i);

            dimensiuneMST = 0;

            generateRandomGraph(muchie,i,500);
            Kruskal(muchie,i,mst,dimensiuneMST,opr);

        }

        prf.createGroup("Kruskal_opr","Kruskal");

        prf.showReport();


    } else {
        demo();
    }

    return 0;

}
