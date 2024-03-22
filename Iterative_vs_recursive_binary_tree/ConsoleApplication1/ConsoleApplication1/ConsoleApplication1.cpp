#include <iostream>
#include "Profiler.h"

using namespace std;

Profiler prf("Itr vs Rec");

const int MAX_SIZE = 10000;

struct BinaryTreeNode {
    int data;
    BinaryTreeNode* left;
    BinaryTreeNode* right;
};

BinaryTreeNode* buildBTree_divide_et_impera(int inceput, int final) {
    if (inceput > final) {
        return nullptr;
    }

    int mediana = (inceput + final) / 2;
    BinaryTreeNode* node = new BinaryTreeNode;
    node->data = mediana;
    node->left = buildBTree_divide_et_impera(inceput, mediana - 1);
    node->right = buildBTree_divide_et_impera(mediana + 1, final);
    return node;
}

BinaryTreeNode* buildBTree(int n) {
    return buildBTree_divide_et_impera(1, n);
}

void recursive_preorder(BinaryTreeNode* root) {
    if (root == nullptr) {
        return;
    }

    cout << root->data << " ";
    recursive_preorder(root->left);
    recursive_preorder(root->right);
}

void push(BinaryTreeNode* stack[], int& cap, BinaryTreeNode* valoare) {
    if (cap < MAX_SIZE - 1) {
        stack[++cap] = valoare;
    }
    else {
        cout << "Stack overflow" << endl;
    }
}

BinaryTreeNode* pop(BinaryTreeNode* stack[], int& cap) {
    if (cap >= 0) {
        return stack[cap--];
    }
    else {
        cout << "Stack underflow" << endl;
        return nullptr;
    }
}

bool isEmpty(int cap) {
    return cap == -1;
}

void iterative_preorder(BinaryTreeNode* root) {
    if (root == nullptr) {
        return;
    }

    BinaryTreeNode* stack[MAX_SIZE];
    int top = -1;

    push(stack, top, root);

    while (!isEmpty(top)) {
        BinaryTreeNode* currentNode = pop(stack, top);

        cout << currentNode->data << " ";

        if (currentNode->right != nullptr) {
            push(stack, top, currentNode->right);
        }

        if (currentNode->left != nullptr) {
            push(stack, top, currentNode->left);
        }
    }
}

int partition(int vector[], int mic, int mare, Operation atr, Operation com) {

    Operation atrb = atr;
    Operation comp = com;

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


    return (i + 1);

}


void quickSort(int vector[], int size, int mic, int mare, Operation atr, Operation com) {
    if (mic <= mare) {

        int q = partition(vector, mic, mare, atr, com);

        quickSort(vector, size, mic, q - 1, atr, com);
        quickSort(vector, size, q + 1, mare, atr, com);

    }
}




int partition_hybread(int vector[], int mic, int mare, Operation atr, Operation com) {


    Operation atrb = atr;
    Operation comp = com;

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


    return (i + 1);

}


void insert_sort(int vector[], int nr, Operation atr, Operation com) {

    Operation nr_atribuiri = atr;
    Operation nr_comparari = com;


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


}

const int PRAG_INSERTION_SORT = 8; // Setati pragul pentru Insertion Sort

void hybridQuickSort_help(int vector[], int size, int mic, int mare, Operation atr, Operation com) {

    Operation nr_atribuiri = atr;
    Operation nr_comparari = com;

    if (mare - mic + 1 <= PRAG_INSERTION_SORT) {

        // Utilizam Insertion Sort pentru dimensiuni mici
        insert_sort(vector + mic, mare - mic + 1, nr_atribuiri, nr_comparari);

    }
    else {
        // Continuam cu QuickSort pentru dimensiuni mari

        if (mic < mare) {
            int q = partition_hybread(vector, mic, mare, nr_atribuiri, nr_comparari);

            hybridQuickSort_help(vector, size, mic, q - 1, nr_atribuiri, nr_comparari);
            hybridQuickSort_help(vector, size, q + 1, mare, nr_atribuiri, nr_comparari);

        }
    }


}


// Func?ia de apel pentru a porni hibridizarea
void hybridQuickSort(int vector[], int size, Operation atr, Operation com) {
    hybridQuickSort_help(vector, size, 0, size - 1, atr, com);
}


int partition_hybread_timer(int vector[], int mic, int mare) {

    int pivot = vector[mare];
    int i = mic - 1;

    for (int j = mic; j <= mare - 1; j++) {
        if (vector[j] <= pivot) {
            i++;
            std::swap(vector[i], vector[j]);

        }
    }
    std::swap(vector[i + 1], vector[mare]);


    return (i + 1);

}

void quickSort_timer(int vector[], int size, int mic, int mare) {
    if (mic <= mare) {

        int q = partition_hybread_timer(vector, mic, mare);

        quickSort_timer(vector, size, mic, q - 1);
        quickSort_timer(vector, size, q + 1, mare);

    }
}


void insert_sort_timer(int vector[], int nr) {

    for (int i = 1; i < nr; i++) {
        int curent = vector[i];
        int j = i - 1;

        while (j >= 0 && vector[j] > curent) {
            vector[j + 1] = vector[j];
            j--;
        }

        vector[j + 1] = curent;
    }


}


void hybridQuickSort_timer(int vector[], int size, int mic, int mare) {


    if (mare - mic + 1 <= PRAG_INSERTION_SORT) {

        // Utilizam Insertion Sort pentru dimensiuni mici
        insert_sort_timer(vector + mic, mare - mic + 1);

    }
    else {
        // Continuam cu QuickSort pentru dimensiuni mari

        if (mic < mare) {
            int q = partition_hybread_timer(vector, mic, mare);

            hybridQuickSort_timer(vector, size, mic, q - 1);
            hybridQuickSort_timer(vector, size, q + 1, mare);

        }
    }


}









int main() {
    BinaryTreeNode* root = buildBTree(200);

    int vector[MAX_SIZE];
    int copie_vector[MAX_SIZE];


    //    for(int k=0; k<500; k++){
    //
    //        for(int i=100; i<=10000; i+=100){
    //
    //            Operation atrb = prf.createOperation("atrb_quickSort", i);
    //            Operation comp = prf.createOperation("comp_quickSort", i);
    //            Operation nr_atribuiri = prf.createOperation("atrb_hyquickSort", i);
    //            Operation nr_comparari = prf.createOperation("comp_hyquickSort", i);
    //
    //            FillRandomArray(vector,i,10,50000,false,0);
    //            CopyArray(copie_vector,vector,i);
    //            hybridQuickSort(copie_vector,i,nr_atribuiri,nr_comparari);
    //            CopyArray(copie_vector,vector,i);
    //            quickSort(copie_vector,i,0,i-1,atrb,comp);
    //
    //        }
    //
    //    }
    //
    //    prf.addSeries("quickSort", "atrb_quickSort", "comp_quickSort");
    //    prf.addSeries("hybridquickSort", "atrb_hyquickSort", "comp_hyquickSort");
    //
    //    prf.divideValues("atrb_hyquickSort",500);
    //    prf.divideValues("atrb_quickSort",500);
    //    prf.divideValues("comp_hyquickSort",500);
    //    prf.divideValues("comp_quickSort",500);
    //    prf.divideValues("hybridquickSort",500);
    //    prf.divideValues("quickSort",500);
    //
    //    prf.createGroup("Atribuiri","atrb_hyquickSort","atrb_quickSort");
    //    prf.createGroup("Comparari","comp_hyquickSort","comp_quickSort");
    //    prf.createGroup("Total","hybridquickSort","quickSort");




    for (int i = 100; i <= 10000; i += 100) {

        FillRandomArray(vector, i, 10, 50000, false, 0);

        prf.startTimer("Timer_quickSort", i);
        for (int test = 0; test < 1000; ++test) {

            CopyArray(copie_vector, vector, i);
            quickSort_timer(copie_vector, i, 0, i - 1);

        }
        prf.stopTimer("Timer_quickSort", i);

        prf.startTimer("Timer_hybridquickSort", i);
        for (int test = 0; test < 1000; ++test) {

            CopyArray(copie_vector, vector, i);
            hybridQuickSort_timer(copie_vector, i, 0, i - 1);

        }
        prf.stopTimer("Timer_hybridquickSort", i);

    }


    prf.divideValues("Timer_quickSort", 1000);
    prf.divideValues("Timer_hybridquickSort", 1000);


    prf.createGroup("Time", "Timer_quickSort", "Timer_hybridquickSort");



    prf.showReport();




    return 0;
}
