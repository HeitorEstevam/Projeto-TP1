#include "entidades.hpp"

// Pessoa
Pessoa::Pessoa(const Nome& nome, const Email& email) {
    this->nome = nome;
    this->email = email;
}

// Gerente
Gerente::Gerente(const Nome& nome, const Email& email, const Senha& senha, const Ramal& ramal) 
    : Pessoa(nome, email) {
    this->senha = senha;
    this->ramal = ramal;
}

// Hotel
Hotel::Hotel(const Nome& nome, const Endereco& endereco, const Telefone& telefone, const Codigo& codigo) {
    this->nome = nome;
    this->endereco = endereco;
    this->telefone = telefone;
    this->codigo = codigo;
    this->gerente = nullptr; // Inicializa ponteiro como nulo por segurança
}

// Quarto
Quarto::Quarto(const Numero& numero, const Capacidade& capacidade, 
               const Dinheiro& diaria, const Ramal& ramal, Hotel* hotel) {
    this->numero = numero;
    this->capacidade = capacidade;
    this->diaria = diaria;
    this->ramal = ramal;
    this->hotel = hotel;
    this->reserva = nullptr; // Inicializa sem reserva
}

// Hóspede
Hospede::Hospede(const Nome& nome, const Email& email, const Endereco& endereco, const Cartao& cartao) 
    : Pessoa(nome, email) {
    this->endereco = endereco;
    this->cartao = cartao;
    this->reserva = nullptr; // Inicializa sem reserva
}

// Reserva
Reserva::Reserva(const Data& dataChegada, const Data& dataPartida, 
                 const Dinheiro& valor, const Codigo& codigo) {
    this->dataChegada = dataChegada;
    this->dataPartida = dataPartida;
    this->valor = valor;
    this->codigo = codigo;
    this->hospede = nullptr; // Inicializa ponteiros
    this->quarto = nullptr;
}