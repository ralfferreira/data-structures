// Ralf Dewrich Ferreira

// Implemente uma lista encadeada de inteiros, utilizando alocação dinâmica de memória,
// com as seguintes operações:
//      1. Criação da lista vazia;
//      2. Verificar se a lista está vazia;
//      3. Obter o tamanho da lista;
//      4. Obter/modificar o valor do elemento de uma determinada
//      posição na lista;
//      5. Inserir um elemento em uma determinada posição;
//      6. Retirar um elemento de uma determinada posição.
//      7. Imprimir os elementos de toda a lista. 

// Arquivo de teste/input também contém as opções de menu

#include <iostream>
#include <stdexcept>

class Node {
public:
    int data;
    Node* next;
    
    Node(int value) : data(value), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
    int size;
    
    Node* getNodeAt(int position) const {
        if (position < 1 || position > size) {
            throw std::out_of_range("Posicao invalida");
        }
        
        Node* current = head;
        for (int i = 1; i < position; i++) {
            current = current->next;
        }
        return current;
    }

public:
    // Criação da lista vazia
    LinkedList() : head(nullptr), size(0) {}
    
    // Destrutor
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    
    // Verificar se está vazia
    bool isEmpty() const {
        return size == 0;
    }
    
    // Obter tamanho
    int getSize() const {
        return size;
    }
    
    // Obter valor de uma posição
    int getValue(int position) const {
        return getNodeAt(position)->data;
    }
    
    // Modificar valor de uma posição
    void setValue(int position, int value) {
        getNodeAt(position)->data = value;
    }
    
    // Inserir elemento
    void insert(int position, int value) {
        if (position < 1 || position > size + 1) {
            throw std::out_of_range("Posicao invalida para insercao");
        }
        
        Node* newNode = new Node(value);
        
        if (position == 1) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* prev = getNodeAt(position - 1);
            newNode->next = prev->next;
            prev->next = newNode;
        }
        
        size++;
    }
    
    // Remover elemento
    int remove(int position) {
        if (isEmpty()) {
            throw std::runtime_error("Lista vazia");
        }
        
        if (position < 1 || position > size) {
            throw std::out_of_range("Posicao invalida para remocao");
        }
        
        Node* nodeToRemove;
        int removedValue;
        
        if (position == 1) {
            nodeToRemove = head;
            head = head->next;
        } else {
            Node* prev = getNodeAt(position - 1);
            nodeToRemove = prev->next;
            prev->next = nodeToRemove->next;
        }
        
        removedValue = nodeToRemove->data;
        delete nodeToRemove;
        size--;
        
        return removedValue;
    }
    
    // Imprimir lista
    void print() const {
        std::cout << "Lista: [";
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data;
            if (current->next != nullptr) {
                std::cout << ", ";
            }
            current = current->next;
        }
        std::cout << "]" << std::endl;
    }
};

int main() {
    try {
        LinkedList lista;
        int opcao, posicao, valor;
        
        do {
            std::cout << "\nOperacoes disponiveis:\n";
            std::cout << "1. Inserir elemento\n";
            std::cout << "2. Remover elemento\n";
            std::cout << "3. Modificar elemento\n";
            std::cout << "4. Consultar elemento\n";
            std::cout << "5. Verificar se esta vazia\n";
            std::cout << "6. Obter tamanho\n";
            std::cout << "7. Imprimir lista\n";
            std::cout << "0. Sair\n";
            std::cout << "Digite sua opcao: ";
            std::cin >> opcao;
            
            switch(opcao) {
                case 1:
                    std::cout << "Digite a posicao e o valor: ";
                    std::cin >> posicao >> valor;
                    try {
                        lista.insert(posicao, valor);
                        std::cout << "Elemento inserido com sucesso!\n";
                    } catch (const std::exception& e) {
                        std::cout << "Erro ao inserir: " << e.what() << std::endl;
                    }
                    break;
                    
                case 2:
                    std::cout << "Digite a posicao para remover: ";
                    std::cin >> posicao;
                    try {
                        valor = lista.remove(posicao);
                        std::cout << "Elemento " << valor << " removido com sucesso!\n";
                    } catch (const std::exception& e) {
                        std::cout << "Erro ao remover: " << e.what() << std::endl;
                    }
                    break;
                    
                case 3:
                    std::cout << "Digite a posicao e o novo valor: ";
                    std::cin >> posicao >> valor;
                    try {
                        lista.setValue(posicao, valor);
                        std::cout << "Elemento modificado com sucesso!\n";
                    } catch (const std::exception& e) {
                        std::cout << "Erro ao modificar: " << e.what() << std::endl;
                    }
                    break;
                    
                case 4:
                    std::cout << "Digite a posicao para consultar: ";
                    std::cin >> posicao;
                    try {
                        valor = lista.getValue(posicao);
                        std::cout << "Valor na posicao " << posicao << ": " << valor << "\n";
                    } catch (const std::exception& e) {
                        std::cout << "Erro ao consultar: " << e.what() << std::endl;
                    }
                    break;
                    
                case 5:
                    std::cout << "Lista " << (lista.isEmpty() ? "esta" : "nao esta") << " vazia\n";
                    break;
                    
                case 6:
                    std::cout << "Tamanho atual: " << lista.getSize() << "\n";
                    break;
                    
                case 7:
                    lista.print();
                    break;
                    
                case 0:
                    std::cout << "Encerrando...\n";
                    break;
                    
                default:
                    std::cout << "Opcao invalida!\n";
            }
            
        } while (opcao != 0);
        
    } catch (const std::exception& e) {
        std::cout << "Erro: " << e.what() << std::endl;
    }
    
    return 0;
}