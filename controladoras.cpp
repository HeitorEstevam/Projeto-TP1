#include <iostream>
#include <string>
#include <stdexcept>
#include "dominios.hpp"

void criarHotel(Gerente* gerenteLogado) {
    std::string entrada;
    
    Nome nome;
    Endereco endereco;
    Telefone telefone;
    Codigo codigo;

    std::cout << "\nCriar Hotel\n";

    //NOME
    while (true) {
        try {
            std::cout << "Nome do hotel: ";
            std::getline(std::cin >> std::ws, entrada);
            nome.setValor(entrada); 
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\n";
            std::cerr << "Tente novamente.\n";
        }
    }

    //ENDEREÇO
    while (true) {
        try {
            std::cout << "Endereço: ";
            std::getline(std::cin, entrada);
            
            endereco.setValor(entrada);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\n";
            std::cerr << "Tente novamente.\n";
        }
    }

    //TELEFONE
    while (true) {
        try {
            std::cout << "Telefone (+DDDDNXXXXXXXX): ";
            std::getline(std::cin, entrada);
            
            telefone.setValor(entrada);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\n";
            std::cerr << "Tente novamente.\n";
        }
    }

    //CÓDIGO
    while (true) {
        try {
            std::cout << "Código (10 caracteres alfanuméricos): ";
            std::getline(std::cin, entrada);
            
            codigo.setValor(entrada);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\n";
            std::cerr << "Tente novamente.\n";
        }
    }

    //CRIAÇÃO FINAL
    Hotel novoHotel(nome, endereco, telefone, codigo);
    
    //ASSOCIAÇÃO AO GERENTE
    novoHotel.setGerente(gerenteLogado);

    servicoHotel.criar(novoHotel); 
    
    std::cout << "\nHotel '" << novoHotel.getNome().getValor()
              << "' criado com sucesso!\n";
}