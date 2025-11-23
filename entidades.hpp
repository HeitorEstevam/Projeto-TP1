#ifndef ENTIDADES_HPP 
#define ENTIDADES_HPP

#include "dominios.hpp"
#include <vector>
#include <iostream>

// Declarações para evitar erro de compilação
class Reserva;
class Hospede;
class Quarto;
class Hotel;

// PESSOA
class Pessoa {
protected:
    Nome nome;
    Email email;

public:
    Pessoa() = default;
    Pessoa(const Nome& nome, const Email& email);
    Pessoa(const std::string& nomeStr, const std::string& emailStr); // Added for deserialization
    virtual ~Pessoa() = default;

    Nome getNome() const { return nome; }
    Email getEmail() const { return email; }

    void setNome(const Nome& nome) { this->nome = nome; }
    void setEmail(const Email& email) { this->email = email; }
};

// GERENTE
class Gerente : public Pessoa {
private:
    Senha senha;
    Ramal ramal;

public:
    Gerente() = default;
    Gerente(const Nome& nome, const Email& email, const Senha& senha, const Ramal& ramal);
    // Added for deserialization
    Gerente(const std::string& nomeStr, const std::string& emailStr, const std::string& senhaStr, const std::string& ramalStr);

    Senha getSenha() const { return senha; }
    Ramal getRamal() const { return ramal; }

    void setSenha(const Senha& senha) { this->senha = senha; }
    void setRamal(const Ramal& ramal) { this->ramal = ramal; }
};

// HOTEL
class Hotel {
private:
    Nome nome;
    Endereco endereco;
    Telefone telefone;
    Codigo codigo;
    Gerente* gerente; 

public:
    Hotel() = default;
    Hotel(const Nome& nome, const Endereco& endereco, const Telefone& telefone, const Codigo& codigo);
    // Added for deserialization (gerente will be set separately if needed)
    Hotel(const std::string& nomeStr, const std::string& enderecoStr, const std::string& telefoneStr, const std::string& codigoStr);
    virtual ~Hotel() = default;

    void setNome(const Nome& nome) { this->nome = nome; }
    void setEndereco(const Endereco& endereco) { this->endereco = endereco; }
    void setTelefone(const Telefone& telefone) { this->telefone = telefone; }
    void setCodigo(const Codigo& codigo) { this->codigo = codigo; }
    void setGerente(Gerente* gerente) { this->gerente = gerente; }

    Nome getNome() const { return nome; }
    Endereco getEndereco() const { return endereco; }
    Telefone getTelefone() const { return telefone; }
    Codigo getCodigo() const { return codigo; }
    Gerente* getGerente() const { return gerente; }
};

// QUARTO
class Quarto {
private:
    Numero numero;
    Capacidade capacidade;
    Dinheiro diaria;
    Ramal ramal;

    Hotel* hotel;
    Reserva* reserva;

public:
    Quarto() : hotel(nullptr), reserva(nullptr) {}
    Quarto(const Numero& numero, const Capacidade& capacidade, 
           const Dinheiro& diaria, const Ramal& ramal, Hotel* hotel);
    // Added for deserialization (hotel and reserva will be set separately if needed)
    Quarto(const std::string& numeroStr, const std::string& capacidadeStr, 
           const std::string& diariaStr, const std::string& ramalStr);
    virtual ~Quarto() = default;

    void setNumero(const Numero& numero) { this->numero = numero; }
    void setCapacidade(const Capacidade& capacidade) { this->capacidade = capacidade; }
    void setDiaria(const Dinheiro& diaria) { this->diaria = diaria; }
    void setRamal(const Ramal& ramal) { this->ramal = ramal; }

    void setHotel(Hotel* hotel) { this->hotel = hotel; }
    void associarReserva(Reserva* reserva) { this->reserva = reserva; }
    void removerReserva() { this->reserva = nullptr; }

    Numero getNumero() const { return numero; }
    Capacidade getCapacidade() const { return capacidade; }
    Dinheiro getDiaria() const { return diaria; }
    Ramal getRamal() const { return ramal; }
    Hotel* getHotel() const { return hotel; }
    Reserva* getReserva() const { return reserva; }
};

// HÓSPEDE
class Hospede : public Pessoa {
private:
    Endereco endereco;
    Cartao cartao;
    Reserva* reserva;

public:
    Hospede() : reserva(nullptr) {}
    Hospede(const Nome& nome, const Email& email, const Endereco& endereco, const Cartao& cartao);
    // Added for deserialization (reserva will be set separately if needed)
    Hospede(const std::string& nomeStr, const std::string& emailStr, const std::string& enderecoStr, const std::string& cartaoStr);
    virtual ~Hospede() = default;

    void setEndereco(const Endereco& endereco) { this->endereco = endereco; }
    void setCartao(const Cartao& cartao) { this->cartao = cartao; }

    void associarReserva(Reserva* reserva) { this->reserva = reserva; }
    void removerReserva() { this->reserva = nullptr; }

    Endereco getEndereco() const { return endereco; }
    Cartao getCartao() const { return cartao; }
    Reserva* getReserva() const { return reserva; }
};

// RESERVA
class Reserva {
private:
    Data dataChegada;
    Data dataPartida;
    Dinheiro valor;
    Codigo codigo;

    Hospede* hospede;
    Quarto* quarto;

public:
    Reserva() : hospede(nullptr), quarto(nullptr) {}
    Reserva(const Data& dataChegada, const Data& dataPartida, 
            const Dinheiro& valor, const Codigo& codigo);
    // Added for deserialization (hospede and quarto will be set separately if needed)
    Reserva(const std::string& dataChegadaStr, const std::string& dataPartidaStr, 
            const std::string& valorStr, const std::string& codigoStr);
    virtual ~Reserva() = default;

    void setDataChegada(const Data& dataChegada) { this->dataChegada = dataChegada; }
    void setDataPartida(const Data& dataPartida) { this->dataPartida = dataPartida; }
    void setValor(const Dinheiro& valor) { this->valor = valor; }
    void setCodigo(const Codigo& codigo) { this->codigo = codigo; }

    void setHospede(Hospede* hospede) { this->hospede = hospede; }
    void setQuarto(Quarto* quarto) { this->quarto = quarto; }

    Data getDataChegada() const { return dataChegada; }
    Data getDataPartida() const { return dataPartida; }
    Dinheiro getValor() const { return valor; }
    Codigo getCodigo() const { return codigo; }
    Hospede* getHospede() const { return hospede; }
    Quarto* getQuarto() const { return quarto; }
};

#endif