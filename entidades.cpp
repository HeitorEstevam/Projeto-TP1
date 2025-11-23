#include "entidades.hpp"

// Pessoa
Pessoa::Pessoa(const Nome& nome, const Email& email) {
    this->nome = nome;
    this->email = email;
}

Pessoa::Pessoa(const std::string& nomeStr, const std::string& emailStr) {
    Nome n;
    n.setValor(nomeStr);
    Email e;
    e.setValor(emailStr);
    this->nome = n;
    this->email = e;
}

// Gerente
Gerente::Gerente(const Nome& nome, const Email& email, const Senha& senha, const Ramal& ramal) 
    : Pessoa(nome, email) {
    this->senha = senha;
    this->ramal = ramal;
}

Gerente::Gerente(const std::string& nomeStr, const std::string& emailStr, const std::string& senhaStr, const std::string& ramalStr)
    : Pessoa(nomeStr, emailStr) { // Call Pessoa's string-based constructor
    Senha s;
    s.setValor(senhaStr);
    Ramal r;
    r.setValor(ramalStr);
    this->senha = s;
    this->ramal = r;
}

// Hotel
Hotel::Hotel(const Nome& nome, const Endereco& endereco, const Telefone& telefone, const Codigo& codigo) {
    this->nome = nome;
    this->endereco = endereco;
    this->telefone = telefone;
    this->codigo = codigo;
    this->gerente = nullptr; // Inicializa ponteiro como nulo por segurança
}

Hotel::Hotel(const std::string& nomeStr, const std::string& enderecoStr, const std::string& telefoneStr, const std::string& codigoStr) {
    Nome n;
    n.setValor(nomeStr);
    Endereco e;
    e.setValor(enderecoStr);
    Telefone t;
    t.setValor(telefoneStr);
    Codigo c;
    c.setValor(codigoStr);
    this->nome = n;
    this->endereco = e;
    this->telefone = t;
    this->codigo = c;
    this->gerente = nullptr; // Initialize pointer as null
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

Quarto::Quarto(const std::string& numeroStr, const std::string& capacidadeStr, const std::string& diariaStr, const std::string& ramalStr) {
    Numero num;
    num.setValor(numeroStr);
    Capacidade cap;
    cap.setValor(std::stoi(capacidadeStr)); // Assuming stoi works, careful with errors
    Dinheiro d;
    d.setValor(std::stoi(diariaStr)); // Assuming stoi works
    Ramal r;
    r.setValor(ramalStr);
    this->numero = num;
    this->capacidade = cap;
    this->diaria = d;
    this->ramal = r;
    this->hotel = nullptr;   // Initialize pointer as null
    this->reserva = nullptr; // Initialize pointer as null
}

// Hóspede
Hospede::Hospede(const Nome& nome, const Email& email, const Endereco& endereco, const Cartao& cartao) 
    : Pessoa(nome, email) {
    this->endereco = endereco;
    this->cartao = cartao;
    this->reserva = nullptr; // Inicializa sem reserva
}

Hospede::Hospede(const std::string& nomeStr, const std::string& emailStr, const std::string& enderecoStr, const std::string& cartaoStr)
    : Pessoa(nomeStr, emailStr) { // Call Pessoa's string-based constructor
    Endereco e;
    e.setValor(enderecoStr);
    Cartao c;
    c.setValor(cartaoStr);
    this->endereco = e;
    this->cartao = c;
    this->reserva = nullptr; // Initialize pointer as null
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

Reserva::Reserva(const std::string& dataChegadaStr, const std::string& dataPartidaStr, const std::string& valorStr, const std::string& codigoStr) {
    Data dc;
    dc.setValor(dataChegadaStr);
    Data dp;
    dp.setValor(dataPartidaStr);
    Dinheiro v;
    v.setValor(std::stoi(valorStr)); // Assuming stoi works
    Codigo c;
    c.setValor(codigoStr);
    this->dataChegada = dc;
    this->dataPartida = dp;
    this->valor = v;
    this->codigo = c;
    this->hospede = nullptr; // Initialize pointer as null
    this->quarto = nullptr;  // Initialize pointer as null
}