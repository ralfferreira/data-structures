// Ralf Dewrich Ferreira

// Implemente uma lista sequencial de inteiros, utilizando o tipo vetor, de inteiros com as seguintes operações:
//      1. Criação da lista vazia;
//      2. Verificar se a lista está vazia;
//      3. Verificar se a lista está cheia;
//      4. Obter o tamanho da lista;
//      5. Obter/modificar o valor do elemento de uma determinada
//      posição na lista;
//      6. Inserir um elemento em uma determinada posição;
//      7. Retirar um elemento de uma determinada posição.

// Arquivo de teste/input também contém as opções de menu

#include <iostream>
#include <stdexcept>
#include <string>

class Array {
private:
    int* data;          // ponteiro para o array dinâmico
    int capacity;       // tamanho max do array
    int size;          // quantidade atual de elementos

public:
    // construtor
    Array(int maxSize) {
        if (maxSize <= 0) {
            throw std::invalid_argument("Tamanho max deve ser positivo");
        }
        capacity = maxSize;
        data = new int[capacity];
        size = 0;
    }
    
    // destrutor
    ~Array() {
        delete[] data;
    }
    
    // vê se está vazia
    bool isEmpty() const {
        return size == 0;
    }
    
    // vê se está cheia
    bool isFull() const {
        return size == capacity;
    }
    
    // get tamanho atual
    int getSize() const {
        return size;
    }
    
    // get valor de uma posicao
    int getValue(int position) const {
        if (position < 1 || position > size) {
            throw std::out_of_range("Posicao invalida para consulta");
        }
        return data[position - 1];
    }
    
    // set (modificar) valor de uma posicao
    void setValue(int position, int value) {
        if (position < 1 || position > size) {
            throw std::out_of_range("Posicao invalida para modificacao");
        }
        data[position - 1] = value;
    }
    
    // add/inserir elemento
    void insert(int position, int value) {
        if (isFull()) {
            throw std::runtime_error("Lista cheia");
        }
        
        // vê se a posicao é válida para inserção
        if (position < 1 || position > size + 1) {
            throw std::out_of_range("Posicao invalida para insercao");
        }
        
        // desloca elementos para a direita
        for (int i = size; i >= position; i--) {
            data[i] = data[i-1];
        }
        
        // insere o novo elemento
        data[position-1] = value;
        size++;
    }
    
    // delete elemento
    int remove(int position) {
        if (isEmpty()) {
            throw std::runtime_error("Lista vazia");
        }
        
        if (position < 1 || position > size) {
            throw std::out_of_range("Posicao invalida para remocao");
        }
        
        int removedValue = data[position-1];
        
        // desloca elementos para a esquerda
        for (int i = position-1; i < size-1; i++) {
            data[i] = data[i+1];
        }
        
        size--;
        return removedValue;
    }
    
    // imprimir lista
    void print() const {
        std::cout << "Lista: [";
        for (int i = 0; i < size; i++) {
            std::cout << data[i];
            if (i < size - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
};

int main() {
    try {
        int maxSize;
        bool validInput = false;
        
        do {
            std::cout << "Digite o tamanho maximo da lista (deve ser maior que 0): ";
            
            // verifica se a entrada é um número
            if (!(std::cin >> maxSize)) {
                std::cin.clear(); // clear no estado de erro
                std::cin.ignore(10000, '\n'); // descarta entrada inválida
                std::cout << "Erro: Digite um numero valido!\n";
                continue;
            }
            
            // vê se o número é válido
            if (maxSize <= 0) {
                std::cout << "Erro: O tamanho deve ser maior que 0!\n";
                continue;
            }
            
            validInput = true;
            
        } while (!validInput);
        
        Array lista(maxSize);
        int opcao, posicao, valor;
        
        do {
            std::cout << "\nOperacoes disponiveis:\n";
            std::cout << "1. Inserir elemento\n";
            std::cout << "2. Remover elemento\n";
            std::cout << "3. Modificar elemento\n";
            std::cout << "4. Consultar elemento\n";
            std::cout << "5. Verificar se esta vazia\n";
            std::cout << "6. Verificar se esta cheia\n";
            std::cout << "7. Obter tamanho\n";
            std::cout << "8. Imprimir lista\n";
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
                    std::cout << "Lista " << (lista.isFull() ? "esta" : "nao esta") << " cheia\n";
                    break;
                    
                case 7:
                    std::cout << "Tamanho atual: " << lista.getSize() << "\n";
                    break;
                    
                case 8:
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