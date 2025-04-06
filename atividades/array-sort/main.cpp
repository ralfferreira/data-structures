#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

void InsertionSortArray(int A[], int n) {
    int pivo = 0;
    for (int i = 1; i < n; i++) {
        pivo = A[i];
        int j = i - 1;
        while (j >= 0 && A[j] > pivo) {
            A[j + 1] = A[j];
            j = j - 1;
        }
        A[j + 1] = pivo;
    }
}

void InsertionSort(vector<int>& A) {
    int n = A.size();
    for (int i = 1; i < n; i++) {
        int pivo = A[i];
        int j = i - 1;
        while (j >= 0 && A[j] > pivo) {
            A[j + 1] = A[j];
            j = j - 1;
        }
        A[j + 1] = pivo;
    }
}

void SelectionSortArray(int A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int i_min = i;
        for (int j = i + 1; j < n; j++) {
            if (A[j] < A[i_min]) {
                i_min = j;
            }
        }
        if (A[i] != A[i_min]) {
            int temp = A[i];
            A[i] = A[i_min];
            A[i_min] = temp;
        }
    }
}

void SelectionSort(vector<int>& A) {
    int n = A.size();
    for (int i = 0; i < n - 1; i++) {
        int i_min = i;
        for (int j = i + 1; j < n; j++) {
            if (A[j] < A[i_min]) {
                i_min = j;
            }
        }
        if (A[i] != A[i_min]) {
            int temp = A[i];
            A[i] = A[i_min];
            A[i_min] = temp;
        }
    }
}

int main() {
    string filename;
    cout << "Nome do arquivo: ";
    cin >> filename;
    
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "ERR 404: " << filename << endl;
        return 1;
    }
    
    vector<int> numbers;
    int number;
    while (file >> number) {
        numbers.push_back(number);
    }
    file.close();
    
    if (numbers.empty()) {
        cerr << "ERR 400." << endl;
        return 1;
    }
    
    cout << "Arquivo lido com sucesso!" << endl;
    cout << "Quantidade de numeros: " << numbers.size() << endl;
    
    vector<int> numbersForInsertion = numbers;
    vector<int> numbersForSelection = numbers;
    
    auto startInsertion = chrono::high_resolution_clock::now();
    InsertionSort(numbersForInsertion);
    auto endInsertion = chrono::high_resolution_clock::now();
    
    auto durationInsertion = chrono::duration_cast<chrono::milliseconds>(endInsertion - startInsertion);
    double durationInsertion_s = chrono::duration<double>(endInsertion - startInsertion).count();
    
    cout << "InsertionSort Time: " << durationInsertion.count() << " ms, " 
         << durationInsertion_s << " s" << endl;
    
    auto startSelection = chrono::high_resolution_clock::now();
    SelectionSort(numbersForSelection);
    auto endSelection = chrono::high_resolution_clock::now();
    
    auto durationSelection = chrono::duration_cast<chrono::milliseconds>(endSelection - startSelection);
    double durationSelection_s = chrono::duration<double>(endSelection - startSelection).count();
    
    cout << "SelectionSort Time: " << durationSelection.count() << " ms, " 
         << durationSelection_s << " s" << endl;
    
    return 0;
}