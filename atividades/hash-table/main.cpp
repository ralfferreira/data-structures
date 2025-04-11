#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <functional>

class Objeto {
private:
    int chave;
    std::string nome;

public:
    Objeto(int chave, std::string nome) : chave(chave), nome(nome) {}

    int getChave() const {
        return chave;
    }

    std::string getNome() const {
        return nome;
    }
};

class HashTable {
private:
    // num total de objetos que a tabela pode armazenar
    int n;
    
    // primeiro nível: vetor de 10 ponteiros para o segundo nível
    std::vector<std::vector<std::list<Objeto>>*> primeirNivel;
    
    // hash function para o primeiro nível (mapeia para 0-9)
    int hashPrimeiroNivel(int chave) const {
        return chave % 10;
    }
    
    // hash function para o segundo nível (diferente da primeira)
    int hashSegundoNivel(int chave, int tamanhoSegundoNivel) const {
        // hash function diferente para o segundo nível
        // podemos usar deslocamento de bits ou divisão por outro número
        return (chave / 10) % tamanhoSegundoNivel;
    }

public:
    HashTable(int capacidadeTotal) {
        n = capacidadeTotal;
        
        // inicia o primeiro nível com 10 posições
        primeirNivel.resize(10, nullptr);
        
        // size de cada table do segundo nível
        int tamanhoSegundoNivel = n / 10;
        
        // garante que cada tabela do segundo nível tenha pelo menos 1 posição
        if (tamanhoSegundoNivel < 1) {
            tamanhoSegundoNivel = 1;
        }        
    }
    
    ~HashTable() {
        for (auto tabela : primeirNivel) {
            delete tabela;
        }
    }
    
    void inserir(int chave, std::string nome) {
        int indicePrimeiroNivel = hashPrimeiroNivel(chave);
        
        // ve se a tabela do segundo nível já foi criada
        if (primeirNivel[indicePrimeiroNivel] == nullptr) {
            // cria
            int tamanhoSegundoNivel = n / 10;
            if (tamanhoSegundoNivel < 1) tamanhoSegundoNivel = 1;
            
            primeirNivel[indicePrimeiroNivel] = new std::vector<std::list<Objeto>>(tamanhoSegundoNivel);
        }
        
        // referência para a tabela do segundo nível
        std::vector<std::list<Objeto>>& segundoNivel = *primeirNivel[indicePrimeiroNivel];
        
        // calculo do índice no segundo nível
        int indiceSegundoNivel = hashSegundoNivel(chave, segundoNivel.size());
        
        // insere o objeto na lista
        segundoNivel[indiceSegundoNivel].push_back(Objeto(chave, nome));
        
        std::cout << "Objeto '" << nome << "' com chave " << chave << " inserido em [" 
                  << indicePrimeiroNivel << "][" << indiceSegundoNivel << "]" << std::endl;
    }
    
    Objeto* buscar(int chave) {
        // calculo do índice no primeiro nível
        int indicePrimeiroNivel = hashPrimeiroNivel(chave);
        
        // ve se a tabela do segundo nível existe
        if (primeirNivel[indicePrimeiroNivel] == nullptr) {
            return nullptr;
        }
        
        // pega a eferência para a tabela do segundo nível
        std::vector<std::list<Objeto>>& segundoNivel = *primeirNivel[indicePrimeiroNivel];
        
        // calcula o ndice no segundo nível
        int indiceSegundoNivel = hashSegundoNivel(chave, segundoNivel.size());
        
        // busca na lista
        for (auto& objeto : segundoNivel[indiceSegundoNivel]) {
            if (objeto.getChave() == chave) {
                return const_cast<Objeto*>(&objeto);
            }
        }
        
        return nullptr;
    }
    
    void imprimir() const {
        std::cout << "\n----- Estrutura da Tabela Hash -----\n";
        for (size_t i = 0; i < primeirNivel.size(); i++) {
            std::cout << "Primeiro Nivel [" << i << "]: ";
            
            if (primeirNivel[i] == nullptr) {
                std::cout << "Vazio\n";
                continue;
            }
            
            std::cout << "\n";
            for (size_t j = 0; j < primeirNivel[i]->size(); j++) {
                std::cout << "  Segundo Nivel [" << j << "]: ";
                
                if ((*primeirNivel[i])[j].empty()) {
                    std::cout << "Vazio\n";
                } else {
                    std::cout << "[ ";
                    for (const auto& obj : (*primeirNivel[i])[j]) {
                        std::cout << "(" << obj.getChave() << ":" << obj.getNome() << ") ";
                    }
                    std::cout << "]\n";
                }
            }
        }
        
        std::cout << "---------------------------------\n";
    }
};

int main() {
    HashTable tabela(100);
    
    tabela.inserir(0, "Joao");
    tabela.inserir(1, "Marco");
    tabela.inserir(10, "Marina");
    tabela.inserir(21, "Julia");
    tabela.inserir(20, "Antônio");
    tabela.inserir(30, "Jose");
    tabela.inserir(42, "Carlos");
    tabela.inserir(81, "Pedro");
    tabela.inserir(90, "Ana");
    
    tabela.imprimir();
    
    int chaveBusca = 21;
    Objeto* resultado = tabela.buscar(chaveBusca);
    
    if (resultado != nullptr) {
        std::cout << "\nObjeto encontrado com chave " << chaveBusca << ": " 
                  << resultado->getNome() << std::endl;
    } else {
        std::cout << "\nObjeto com chave " << chaveBusca << " nao encontrado." << std::endl;
    }
    
    chaveBusca = 50;
    resultado = tabela.buscar(chaveBusca);
    
    if (resultado != nullptr) {
        std::cout << "Objeto encontrado com chave " << chaveBusca << ": " 
                  << resultado->getNome() << std::endl;
    } else {
        std::cout << "Objeto com chave " << chaveBusca << " nao encontrado." << std::endl;
    }
    
    return 0;
}