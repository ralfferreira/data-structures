#include <iostream>

class Queue {
private:
    static const int MAX_SIZE = 100;  // tam max
    int array[MAX_SIZE];              // array que guarda os elementos
    int front;                        // indicie do primeiro
    int rear;                         // indicie do ultimo
    int count;                        // num de elementos

public:
    // construtor
    Queue() {
        front = 0;
        rear = -1;
        count = 0;
    }

    // fila vazia
    bool isEmpty() {
        return count == 0;
    }

    // fila cheia
    bool isFull() {
        return count == MAX_SIZE;
    }

    // add elemento no fim
    bool enqueue(int value) {
        if (isFull()) {
            std::cout << "Erro: Fila cheia!" << std::endl;
            return false;
        }
        
        // incremento circular
        rear = (rear + 1) % MAX_SIZE;
        array[rear] = value;
        count++;
        return true;
    }

    // deletando elemento da frente
    bool dequeue() {
        if (isEmpty()) {
            std::cout << "Erro: Fila vazia!" << std::endl;
            return false;
        }
        
        // incremento circular
        front = (front + 1) % MAX_SIZE;
        count--;
        return true;
    }

    // get elemento da frente sem deletar
    int getFront() {
        if (isEmpty()) {
            std::cout << "Erro: Fila vazia!" << std::endl;
            return -1;
        }
        return array[front];
    }

    // mostrar todos 
    void showAll() {
        if (isEmpty()) {
            std::cout << "Fila vazia!" << std::endl;
            return;
        }

        std::cout << "Elementos da fila: ";
        int current = front;
        for (int i = 0; i < count; i++) {
            std::cout << array[current] << " ";
            current = (current + 1) % MAX_SIZE;
        }
        std::cout << std::endl;
    }

    // tamanho da fila
    int size() {
        return count;
    }
};

int main() {
    Queue fila;
    int opcao, valor;
    
    do {
        std::cout << "\nOperacoes disponiveis:\n";
        std::cout << "1. Inserir elemento no fim da fila\n";
        std::cout << "2. Remover elemento do inicio da fila\n";
        std::cout << "3. Consultar elemento do inicio\n";
        std::cout << "4. Verificar se esta vazia\n";
        std::cout << "5. Verificar se esta cheia\n";
        std::cout << "6. Mostrar tamanho atual\n";
        std::cout << "7. Mostrar status completo\n";
        std::cout << "8. Mostrar todos os elementos\n";
        std::cout << "0. Sair\n";
        std::cout << "Digite sua opcao: ";
        std::cin >> opcao;
        
        switch(opcao) {
            case 1:
                std::cout << "Digite o valor a ser inserido: ";
                std::cin >> valor;
                if (fila.enqueue(valor)) {
                    std::cout << "Valor " << valor << " inserido com sucesso!\n";
                }
                break;
                
            case 2:
                if (fila.dequeue()) {
                    std::cout << "Elemento removido com sucesso!\n";
                }
                break;
                
            case 3:
                if (!fila.isEmpty()) {
                    std::cout << "Elemento do inicio: " << fila.getFront() << std::endl;
                }
                break;
                
            case 4:
                std::cout << "Fila " << (fila.isEmpty() ? "esta" : "nao esta") << " vazia\n";
                break;
                
            case 5:
                std::cout << "Fila " << (fila.isFull() ? "esta" : "nao esta") << " cheia\n";
                break;
                
            case 6:
                std::cout << "Tamanho atual: " << fila.size() << "\n";
                break;
                
            case 7:
                std::cout << "\nStatus da fila:\n";
                std::cout << "- Vazia: " << (fila.isEmpty() ? "Sim" : "Nao") << std::endl;
                std::cout << "- Cheia: " << (fila.isFull() ? "Sim" : "Nao") << std::endl;
                std::cout << "- Tamanho: " << fila.size() << std::endl;
                if (!fila.isEmpty()) {
                    std::cout << "- Elemento da frente: " << fila.getFront() << std::endl;
                }
                break;

            case 8:
                fila.showAll();
                break;
                
            case 0:
                std::cout << "Encerrando...\n";
                break;
                
            default:
                std::cout << "Opcao invalida!\n";
        }
        
    } while (opcao != 0);
    
    return 0;
}