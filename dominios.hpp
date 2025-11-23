#ifndef DOMINIOS_HPP
#define DOMINIOS_HPP

#include <string>
#include <vector>
#include <memory>
#include <iostream>

//Declaração de classe para evitar erro de compilação
class Hotel;
class Quarto;
class Reserva;
class Hospede;


// CLASSES DE DOMÍNIO (Tipos Básicos)

// Domínio: Nome
class Nome {
private:
    std::string valor;
    // Método auxiliar de validação (interno)
    void validar(std::string v);
public:
    void setValor(std::string v);
    std::string getValor() const { return valor; }
};

// Domínio: Email
class Email {
private:
    std::string valor;
    void validar(std::string v);
public:
    void setValor(std::string v);
    std::string getValor() const { return valor; }
};

// Domínio: Senha
class Senha {
private:
    std::string valor;
    void validar(std::string v);
public:
    void setValor(std::string v);
    std::string getValor() const { return valor; }
};

//Domínio Endereco
class Endereco {
private:
    std::string valor;
    void validar(std::string v); // Implementar regra: 5-30 chars, sem pontos consecutivos
public:
    void setValor(std::string v);
    std::string getValor() const { return valor; }
};

//Domínio telefone
class Telefone {
private:
    std::string valor;
    void validar(std::string v);
public:
    void setValor(std::string v);
    std::string getValor() const { return valor; }
};

//Domínio Código
class Codigo {
private:
    std::string valor;
    void validar(std::string v);
public:
    void setValor(std::string v);
    std::string getValor() const { return valor; }
};

//Domínio Email
class Email {
private:
    std::string valor;
    void validar(std::string v);
public:
    void setValor(std::string v);
    std::string getValor() const { return valor; }
};

//Domínio Senha
class Senha {
private:
    std::string valor;
    void validar(std::string v);
public:
    void setValor(std::string v);
    std::string getValor() const { return valor; }
};

//Domínio Ramal
class Ramal {
private:
    std::string valor; 
    void validar(std::string v);
public:
    void setValor(std::string v);
    std::string getValor() const { return valor; }
};

//Domínio Numero
class Numero {
private:
    std::string valor;
    void validar(std::string v);
public:
    void setValor(std::string v);
    std::string getValor() const { return valor; }
};

//Dominio Capacidade
class Capacidade {
private:
    int valor;
    void validar(int v);
public:
    void setValor(int v);
    int getValor() const { return valor; }
};

//Domínio Dinheiro
class Dinheiro {
private:
    int valor;
    void validar(int v);
public:
    void setValor(int v);
    int getValor() const { return valor; }
};

//Domínio Cartão
class Cartao {
private:
    std::string valor;
    void validar(std::string v);
public:
    void setValor(std::string v);
    std::string getValor() const { return valor; }
};

//Domínio Data
class Data {
private:
    std::string valor;
    void validar(std::string v);
public:
    void setValor(std::string v);
    std::string getValor() const { return valor; }
};


// CLASSES ENTIDADE (Objetos do Sistema)

// Classe Pessoa
class Pessoa {
protected:
    Nome nome;
    Email email;

public:
    // Construtores
    Pessoa() = default;
    Pessoa(const Nome& nome, const Email& email);

    // Destrutor virtual
    virtual ~Pessoa() = default;

    // Getters
    Nome getNome() const { return nome; }
    Email getEmail() const { return email; }

    // Setters
    void setNome(const Nome& nome) { this->nome = nome; }
    void setEmail(const Email& email) { this->email = email; }
};

// Classe Gerente (herda de Pessoa)
class Gerente : public Pessoa {
private:
    Senha senha;
    Ramal ramal;

public:
    // Construtores
    Gerente() = default;
    Gerente(const Nome& nome, const Email& email, const Senha& senha, const Ramal& ramal);

    // Getters
    Senha getSenha() const { return senha; }
    Ramal getRamal() const { return ramal; }

    // Setters
    void setSenha(const Senha& senha) { this->senha = senha; }
    void setRamal(const Ramal& ramal) { this->ramal = ramal; }
};

//Classe Hotel
class Hotel {
private:
    Nome nome;
    Endereco endereco;
    Telefone telefone;
    Codigo codigo;

    //Ponteiro para identificar o gerente do Hotel
    Gerente* gerente; 
public:
    // Construtores
    Hotel() = default;
    Hotel(const Nome& nome, const Endereco& endereco, const Telefone& telefone, const Codigo& codigo);

    // Destrutor
    virtual ~Hotel() = default;

    // Setters
    void setNome(const Nome& nome) { this->nome = nome; }
    void setEndereco(const Endereco& endereco) { this->endereco = endereco; }
    void setTelefone(const Telefone& telefone) { this->telefone = telefone; }
    void setCodigo(const Codigo& codigo) { this->codigo = codigo; }
    void setGerente(Gerente* gerente) { this->gerente = gerente; }

    // Getters
    Nome getNome() const { return nome; }
    Endereco getEndereco() const { return endereco; }
    Telefone getTelefone() const { return telefone; }
    Codigo getCodigo() const { return codigo; }
    Gerente* getGerente() const { return gerente; }
};

// Classe Quarto
class Quarto {
private:
    Numero numero;
    Capacidade capacidade;
    Dinheiro diaria;
    Ramal ramal;

    // Associações
    Hotel* hotel;
    Reserva* reserva;

public:
    // Construtores
    Quarto() : hotel(nullptr), reserva(nullptr) {}
    
    Quarto(const Numero& numero, const Capacidade& capacidade, 
           const Dinheiro& diaria, const Ramal& ramal, Hotel* hotel);

    // Destrutor virtual
    virtual ~Quarto() = default;

    // Setters
    void setNumero(const Numero& numero) { this->numero = numero; }
    void setCapacidade(const Capacidade& capacidade) { this->capacidade = capacidade; }
    void setDiaria(const Dinheiro& diaria) { this->diaria = diaria; }
    void setRamal(const Ramal& ramal) { this->ramal = ramal; }

    // Gerenciamento de Associações
    void setHotel(Hotel* hotel) { this->hotel = hotel; }
    void associarReserva(Reserva* reserva) { this->reserva = reserva; }
    void removerReserva() { this->reserva = nullptr; }

    // Getters
    Numero getNumero() const { return numero; }
    Capacidade getCapacidade() const { return capacidade; }
    Dinheiro getDiaria() const { return diaria; }
    Ramal getRamal() const { return ramal; }
    Hotel* getHotel() const { return hotel; }
    Reserva* getReserva() const { return reserva; }
};

// Classe Hóspede
class Hospede : public Pessoa {
private:
    Endereco endereco;
    Cartao cartao;

    // Associação
    Reserva* reserva;

public:
    // Construtores
    Hospede() : reserva(nullptr) {}
    Hospede(const Nome& nome, const Email& email, const Endereco& endereco, const Cartao& cartao);

    // Destrutor
    virtual ~Hospede() = default;

    // Setters
    void setEndereco(const Endereco& endereco) { this->endereco = endereco; }
    void setCartao(const Cartao& cartao) { this->cartao = cartao; }

    // Gerenciamento
    void associarReserva(Reserva* reserva) { this->reserva = reserva; }
    void removerReserva() { this->reserva = nullptr; }

    // Getters
    Endereco getEndereco() const { return endereco; }
    Cartao getCartao() const { return cartao; }
    Reserva* getReserva() const { return reserva; }
};

//Classe Reserva
class Reserva {
private:
    Data dataChegada;
    Data dataPartida;
    Dinheiro valor;
    Codigo codigo;

    // Associações
    Hospede* hospede;
    Quarto* quarto;

public:
    // Construtores
    Reserva() : hospede(nullptr), quarto(nullptr) {}

    // Construtor principal
    Reserva(const Data& dataChegada, const Data& dataPartida, 
            const Dinheiro& valor, const Codigo& codigo);

    // Destrutor virtual
    virtual ~Reserva() = default;

    // Setters
    void setDataChegada(const Data& dataChegada) { this->dataChegada = dataChegada; }
    void setDataPartida(const Data& dataPartida) { this->dataPartida = dataPartida; }
    void setValor(const Dinheiro& valor) { this->valor = valor; }
    void setCodigo(const Codigo& codigo) { this->codigo = codigo; }

    // Gerenciamento de Associações
    void setHospede(Hospede* hospede) { this->hospede = hospede; }
    void setQuarto(Quarto* quarto) { this->quarto = quarto; }

    // Getters
    Data getDataChegada() const { return dataChegada; }
    Data getDataPartida() const { return dataPartida; }
    Dinheiro getValor() const { return valor; }
    Codigo getCodigo() const { return codigo; }
    Hospede* getHospede() const { return hospede; }
    Quarto* getQuarto() const { return quarto; }
};

#endif
