/**
*
*
* @author Ardelean Robert-Emanuel
* @group 30225
*
*
*/


#include <iostream>
#include <stack>

using namespace std;

const int NUM_MAX_NODURI = 20; // Ajusteaza numarul maxim de noduri dupa nevoie
int globalNumEdges[NUM_MAX_NODURI];
bool areCiclu;

enum StareNod {
    NEDESCOPERIT,
    DESCOPERIT,
    PROCESAT
};

void adaugaMuchie(int listaAdiacenta[NUM_MAX_NODURI][NUM_MAX_NODURI], int v, int w, int &numEdgesV) {
    listaAdiacenta[v][numEdgesV++] = w;
}

void initializareListaAdiacenta(int listaAdiacenta[NUM_MAX_NODURI][NUM_MAX_NODURI], int numNoduri) {
    // Initializeaza lista de adiacenta cu -1 pentru a marca absenta muchiilor
    for (int i = 0; i < numNoduri; ++i) {
        for (int j = 0; j < numNoduri; ++j) {
            listaAdiacenta[i][j] = -1;
        }
    }
}

void afiseazaListaAdiacenta(int listaAdiacenta[NUM_MAX_NODURI][NUM_MAX_NODURI], int numNoduri) {
    cout << "Lista de Adiacenta:\n";
    for (int i = 0; i < numNoduri; ++i) {
        cout << i << "->";
        for (int j = 0; j < NUM_MAX_NODURI; ++j) {
            if (listaAdiacenta[i][j] != -1) {
                cout << listaAdiacenta[i][j] << " ";
            }
        }
        cout << "\n";
    }
}

int DFS(const int listaAdiacenta[NUM_MAX_NODURI][NUM_MAX_NODURI], int nodCurent, StareNod stare[NUM_MAX_NODURI], int parinte[NUM_MAX_NODURI], int &timp, int finishingTimes[NUM_MAX_NODURI], const int &numMuchii, int noduriVizitate[NUM_MAX_NODURI], int &indexNoduriVizitate) {
    // Marcheaza nodul ca descoperit si actualizeaza timpul
    stare[nodCurent] = DESCOPERIT;
    timp++;

    // Proceseaza nodul curent (poti personaliza aceasta parte)
    noduriVizitate[indexNoduriVizitate++] = nodCurent;

    // Parcurge vecinii nodului curent
    for (int i = 0; i < numMuchii; ++i) {
        int vecin = listaAdiacenta[nodCurent][i];

        if (stare[vecin] == NEDESCOPERIT) {
            // Daca vecinul nu a fost descoperit, il exploreaza recursiv
            parinte[vecin] = nodCurent;
            indexNoduriVizitate = DFS(listaAdiacenta, vecin, stare, parinte, timp, finishingTimes, numMuchii, noduriVizitate, indexNoduriVizitate);
        } else if (stare[vecin] == DESCOPERIT && parinte[nodCurent] != vecin) {
            // S-a detectat un ciclu (vecinul este deja descoperit si nu este parintele nodului curent)
            areCiclu = true;
        } else {
            areCiclu = false;
        }
    }

    // Marcheaza nodul ca procesat si actualizeaza timpul de finalizare
    stare[nodCurent] = PROCESAT;
    finishingTimes[nodCurent] = timp++;

    return indexNoduriVizitate;
}

void afiseazaDFS(const int noduriVizitate[NUM_MAX_NODURI], int dimensiuneNoduriVizitate) {
    cout << "Parcurgere DFS: ";
    for (int i = 0; i < dimensiuneNoduriVizitate; ++i) {
        cout << noduriVizitate[i] << " ";
    }
    cout << endl;
}

void sortareTopologica(const int finishingTimes[NUM_MAX_NODURI], int numNoduri) {
    int ordineTopologica[NUM_MAX_NODURI];
    for (int i = 0; i < numNoduri; ++i) {
        ordineTopologica[i] = i;
    }

    // Sorteaza in functie de timpul de finalizare in ordine descrescatoare
    for (int i = 0; i < numNoduri; ++i) {
        for (int j = i + 1; j < numNoduri; ++j) {
            if (finishingTimes[ordineTopologica[i]] < finishingTimes[ordineTopologica[j]]) {
                swap(ordineTopologica[i], ordineTopologica[j]);
            }
        }
    }

    // Afiseaza ordinea topologica
    cout << "Ordine Topologica: ";
    for (int i = 0; i < numNoduri; ++i) {
        cout << ordineTopologica[i] << " ";
    }
    cout << endl;
}

void TarjanDFS(const int listaAdiacenta[NUM_MAX_NODURI][NUM_MAX_NODURI], int nodCurent, int disc[NUM_MAX_NODURI], int low[NUM_MAX_NODURI], bool inStiva[NUM_MAX_NODURI], stack<int> &stiva) {
    static int timp = 0;
    disc[nodCurent] = low[nodCurent] = ++timp;
    stiva.push(nodCurent);
    inStiva[nodCurent] = true;

    for (int i = 0; i < NUM_MAX_NODURI; ++i) {
        int vecin = listaAdiacenta[nodCurent][i];

        if (vecin == -1) {
            break;
        }

        if (disc[vecin] == -1) {
            TarjanDFS(listaAdiacenta, vecin, disc, low, inStiva, stiva);
            low[nodCurent] = min(low[nodCurent], low[vecin]);
        } else if (inStiva[vecin]) {
            low[nodCurent] = min(low[nodCurent], disc[vecin]);
        }
    }

    if (disc[nodCurent] == low[nodCurent]) {
        cout << "Componenta Puternic Conexa: ";
        while (stiva.top() != nodCurent) {
            int nodExtras = stiva.top();
            cout << nodExtras << " ";
            inStiva[nodExtras] = false;
            stiva.pop();
        }
        cout << stiva.top() << endl;
        inStiva[stiva.top()] = false;
        stiva.pop();
    }
}

void afiseazaComponentePuternicConexe(const int listaAdiacenta[NUM_MAX_NODURI][NUM_MAX_NODURI], int numNoduri) {
    int disc[NUM_MAX_NODURI];
    int low[NUM_MAX_NODURI];
    bool inStiva[NUM_MAX_NODURI];
    stack<int> stiva;
    areCiclu = false;

    // Initializeaza vectorii pentru algoritmul lui Tarjan
    for (int i = 0; i < numNoduri; ++i) {
        disc[i] = low[i] = -1;
        inStiva[i] = false;
    }

    // Aplica algoritmul lui Tarjan pentru fiecare nod nevizitat
    for (int i = 0; i < numNoduri; ++i) {
        if (disc[i] == -1) {
            TarjanDFS(listaAdiacenta, i, disc, low, inStiva, stiva);
        }
    }
}

int main() {
    int listaAdiacenta[NUM_MAX_NODURI][NUM_MAX_NODURI];
    initializareListaAdiacenta(listaAdiacenta, NUM_MAX_NODURI);

    int numNoduri, numMuchii;
    cout << "Introduceti numarul de noduri (maximum " << NUM_MAX_NODURI << "): ";
    cin >> numNoduri;

    if (numNoduri > NUM_MAX_NODURI) {
        cout << "Eroare: Numarul de noduri depaseste limita maxima de " << NUM_MAX_NODURI << ".\n";
        return 1;
    }

    cout << "Introduceti numarul de muchii: ";
    cin >> numMuchii;

    // Adauga muchiile in lista de adiacenta
    for (int i = 0; i < numMuchii; ++i) {
        int v, w;
        cout << "Introduceti nodurile pentru muchia " << i + 1 << ": ";
        cin >> v >> w;
        adaugaMuchie(listaAdiacenta, v, w, globalNumEdges[v]);
    }

    // Afiseaza lista de adiacenta
    afiseazaListaAdiacenta(listaAdiacenta, numNoduri);

    // Initializare vectori si variabile pentru DFS
    StareNod stare[NUM_MAX_NODURI] = {NEDESCOPERIT};
    int parinte[NUM_MAX_NODURI] = {-1};
    int finishingTimes[NUM_MAX_NODURI];
    int timp = 0;

    int noduriVizitate[NUM_MAX_NODURI];
    int indexNoduriVizitate = 0;

    // Aplica DFS pentru fiecare nod nevizitat
    for (int i = 0; i < numNoduri; ++i) {
        if (stare[i] == NEDESCOPERIT) {
            indexNoduriVizitate = DFS(listaAdiacenta, i, stare, parinte, timp, finishingTimes, numMuchii, noduriVizitate, indexNoduriVizitate);
            afiseazaDFS(noduriVizitate, indexNoduriVizitate);

            // Reseteaza indexul nodurilor vizitate pentru urmatoarea parcurgere DFS
            indexNoduriVizitate = 0;
        }
    }

    // Verifica daca graful are cicluri sau afiseaza ordinea topologica
    if (areCiclu) {
        cout << "Graful are cicluri\n";
    } else {
        sortareTopologica(finishingTimes, numNoduri);
    }

    // Afla si afiseaza componentele puternic conexe folosind algoritmul lui Tarjan
    afiseazaComponentePuternicConexe(listaAdiacenta, numNoduri);

    return 0;
}
