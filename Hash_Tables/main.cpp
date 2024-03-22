/**
*
*
* @author Ardelean Robert-Emanuel
* @group 30225
*
*
*Complexitatea Spațială:
*
*O(1) – spațiu constant, deoarece dimensiunea
*tabelului de dispersie (hashTable_size) este fixă.
*
*Complexitatea Temporală:
*
*Inserare, Căutare și Ștergere:
*
*Cazul Cel Mai Rău: O(n), unde n este
*dimensiunea tabelului de dispersie.
*Cazul Mediu: O(1) cu o funcție de dispersie
*bună și un factor de umplere scăzut.
*
*Inițializare (initializeHashTable):
*
*O(n), unde n este dimensiunea
*tabelului de dispersie.
*
*Umplerea Tabelului de Dispersie (fillHashTable):
*
*O(nr_elemente), unde nr_elemente reprezintă
*numărul de elemente de inserat.

*Funcția Demo (demo):
*
*Depinde de numărul de elemente inserate, denumit m.
*Complexitatea temporală este O(m).
*Buclele de Testare ale Factorului de Umplere:
*
*O((1/factor_umplere_test) * 7500 * n), unde n
*este dimensiunea tabelului de dispersie.
*
*
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include "Profiler.h"

using namespace std;

#define hashTable_size 10007

int vector_id[3000];

struct Entry {
    int id;
    char name[30];
};

const int increment1 = 7;
const int increment2 = 3;

Entry hashTable[hashTable_size];

int hashing(int key, int size) {
    return (key + increment1 * size + size * increment2 * increment2) % hashTable_size;
}

void insertEntry(Entry entry, int size) {
    int index = hashing(entry.id, size);
    int originalIndex = index;

    do {
        if (hashTable[index].id == -1) {
            hashTable[index] = entry;
            return;
        }
        index = (index + 1) % hashTable_size;
    } while (index != originalIndex);
}

int searchEntry(int key, int size, int &operations) {
    int index = hashing(key, size);
    int originalIndex = index;

    do {
        operations++;

        if (hashTable[index].id == key) {
            return index;
        }
        index = (index + 1) % hashTable_size;
    } while (hashTable[index].id != -1 && index != originalIndex);

    return -1;  // Entry not found
}

void deleteEntry(int key, int size) {
    int index = hashing(key, size);

    while (hashTable[index].id != -1) {
        if (hashTable[index].id == key) {
            hashTable[index].id = -1;
            return;
        }

        index = (index + 1) % hashTable_size;
    }
}

void initializeHashTable() {
    for (int i = 0; i < hashTable_size; i++) {
        hashTable[i].id = -1;
    }
}

int factor_umplere(double fillFactor) {
    return static_cast<int>(hashTable_size * fillFactor);
}

int randkey() {
    int randkey;
    FillRandomArray(&randkey, 1, 10, 30, false, 0);
    return randkey;
}

int randkeyoutofrange() {
    int randkeyoutofrange;
    FillRandomArray(&randkeyoutofrange, 1, 30, 60, false, 0);
    return randkeyoutofrange;
}

void fillarrayofids() {
    generate_n(vector_id, 1500, randkey);
    generate_n(vector_id + 1500, 1500, randkeyoutofrange);
    random_shuffle(begin(vector_id), end(vector_id));
}

void emptyarray() {
    fill(vector_id, vector_id + 3000, 0);
}

void fillHashTable(int nr_elemente) {
    for (int i = 0; i < nr_elemente; ++i) {
        int key = randkey();
        insertEntry({key, "RandomName"}, nr_elemente);
    }

    random_shuffle(begin(hashTable), end(hashTable));
}

void printHashTable() {
    cout << "Hash Table:\n";
    for (int i = 0; i < hashTable_size; ++i) {
        if (hashTable[i].id != -1) {
            cout << " Index " << i << ": Key=" << hashTable[i].id << ", Name=" << hashTable[i].name << "\n";
        }
    }
    cout << "\n";
}

void demo() {
    initializeHashTable();

    // Add entries
    int nr_elemente;
    int nr_el_dorite;
    cout << "Introduceti nr de elemente: ";
    cin >> nr_elemente;
    cout << "Introduceti cate elemente dorim in tabela: ";
    cin >> nr_el_dorite;


    for (int i = 0; i < nr_el_dorite; ++i) {
        Entry demo;

        cout << "Introduceti cheia " << i + 1 << ": ";
        cin >> demo.id;

        cout << "Introduceti numele " << i + 1 << ": ";
        cin >> demo.name;

        insertEntry(demo, nr_elemente);
    }

    // Print hash table
    printHashTable();

    // Search and delete examples
    int keyToSearch;
    cout << "Introduceti cheia dorita pentru a fi cautata: ";
    cin >> keyToSearch;

    int operation;

    int searchResult = searchEntry(keyToSearch, nr_elemente, operation);
    if (searchResult != -1) {
        cout << "Cheia a fost gasita la indexul: " << searchResult << endl;
    } else {
        cout << "Nu s-a gasit cheia." << endl;
    }

    int keyToDelete;
    cout << "Introduceti cheia care vreti sa fie stearsa: ";
    cin >> keyToDelete;

    deleteEntry(keyToDelete, nr_elemente);

    // Print hash table after deletion
    printHashTable();
}

int main() {
    int verificare;

    std::cout << "1 pentru tabel" << std::endl;
    std::cout << "2 pentru demo" << std::endl;
    std::cout << "Raspuns:";
    std::cin >> verificare;

    double efort_mediu_gasite = 0;
    double efort_mediu_maxgasite = 0;
    double efort_mediu_negasite = 0;
    double efort_mediu_maxnegasite = 0;

    double factor_umplere_test = 0.8;

    if (verificare == 1) {

        do {
            int nr_elemente = factor_umplere(factor_umplere_test);

            for (int k = 0; k < 5; k++) {
                fillarrayofids();
                initializeHashTable();
                fillHashTable(nr_elemente);

                int operationsGasite = 0;

                for (int i = 0; i < 3000; i++) {

                    operationsGasite = 0;

                    int key = vector_id[i];
                    int rezultat = searchEntry(key, nr_elemente, operationsGasite);
                    if (rezultat != -1) {
                        efort_mediu_gasite += operationsGasite;
                        if (efort_mediu_maxgasite < operationsGasite) {
                            efort_mediu_maxgasite = operationsGasite;
                        }
                    } else {
                        efort_mediu_negasite += operationsGasite;
                        if (efort_mediu_maxnegasite < operationsGasite) {
                            efort_mediu_maxnegasite = operationsGasite;
                        }
                    }
                }

                emptyarray();
            }

            efort_mediu_gasite /= 7500;
            efort_mediu_negasite /= 7500;

            cout << "Factorul de umplere: " << setprecision(3) << factor_umplere_test
                 << " " << "Maxime: " << "gasit:"<< setprecision(3)<< efort_mediu_maxgasite
                 << " " << "negasit:" << setprecision(3) << efort_mediu_maxnegasite << endl;
            cout << "Factorul de umplere: " << setprecision(3) << factor_umplere_test
                 << " " << "Mediu: " << "gasit:"<< setprecision(3) << efort_mediu_gasite
                 << " " << "negasit:" << setprecision(3) << efort_mediu_negasite << endl;

            factor_umplere_test += 0.05;


        } while (factor_umplere_test < 1);

        factor_umplere_test = 0.99;

        int nr_elemente = factor_umplere(factor_umplere_test);

        for (int k = 0; k < 5; k++) {
            fillarrayofids();
            initializeHashTable();
            fillHashTable(nr_elemente);

            int operationsGasite = 0;

            for (int i = 0; i < 3000; i++) {

                operationsGasite = 0;

                int key = vector_id[i];
                int rezultat = searchEntry(key, nr_elemente, operationsGasite);
                if (rezultat != -1) {
                    efort_mediu_gasite += operationsGasite;
                    if (efort_mediu_maxgasite < operationsGasite) {
                        efort_mediu_maxgasite = operationsGasite;
                    }
                } else {
                    efort_mediu_negasite += operationsGasite;
                    if (efort_mediu_maxnegasite < operationsGasite) {
                        efort_mediu_maxnegasite = operationsGasite;
                    }
                }
            }

            emptyarray();
        }

        efort_mediu_gasite /= 7500;
        efort_mediu_negasite /= 7500;

        cout << "Factorul de umplere: " << factor_umplere_test << " " << "Maxime: "
        << "gasit:"<< efort_mediu_maxgasite << " " << "negasit:" << efort_mediu_maxnegasite << endl;
        cout << "Factorul de umplere: " << factor_umplere_test << " " << "Mediu: "
        << "gasit:" << efort_mediu_gasite<< " " << "negasit:" << efort_mediu_negasite << endl;





    } else {

        demo();

    }

    return 0;
}
