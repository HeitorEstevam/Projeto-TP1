#ifndef DOMINIOS_HPP
#define DOMINIOS_HPP

#include <string>
#include <stdexcept>
#include <iostream>


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

#endif