#ifndef DOMINIOS_HPP
#define DOMINIOS_HPP

#include <string>
#include <stdexcept>
#include <iostream>
#include <iomanip> // Added


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
    friend std::ostream& operator<<(std::ostream& os, const Nome& nome) {
        return os << nome.valor;
    }
};

// Domínio: Email
class Email {
private:
    std::string valor;
    void validar(std::string v);
public:
    void setValor(std::string v);
    std::string getValor() const { return valor; }
    friend std::ostream& operator<<(std::ostream& os, const Email& email) {
        return os << email.valor;
    }
};

// Domínio: Senha
class Senha {
private:
    std::string valor;
    void validar(std::string v);
public:
    void setValor(std::string v);
    std::string getValor() const { return valor; }
    friend std::ostream& operator<<(std::ostream& os, const Senha& senha) {
        return os << senha.valor;
    }
};

//Domínio Endereco
class Endereco {
private:
    std::string valor;
    void validar(std::string v); // Implementar regra: 5-30 chars, sem pontos consecutivos
public:
    void setValor(std::string v);
    std::string getValor() const { return valor; }
    friend std::ostream& operator<<(std::ostream& os, const Endereco& endereco) {
        return os << endereco.valor;
    }
};

//Domínio telefone
class Telefone {
private:
    std::string valor;
    void validar(std::string v);
public:
    void setValor(std::string v);
    std::string getValor() const { return valor; }
    friend std::ostream& operator<<(std::ostream& os, const Telefone& telefone) {
        return os << telefone.valor;
    }
};

//Domínio Código
class Codigo {
private:
    std::string valor;
    void validar(std::string v);
public:
    void setValor(std::string v);
    std::string getValor() const { return valor; }
    friend std::ostream& operator<<(std::ostream& os, const Codigo& codigo) {
        return os << codigo.valor;
    }
};

//Domínio Ramal
class Ramal {
private:
    std::string valor; 
    void validar(std::string v);
public:
    void setValor(std::string v);
    std::string getValor() const { return valor; }
    friend std::ostream& operator<<(std::ostream& os, const Ramal& ramal) {
        return os << ramal.valor;
    }
};

//Domínio Numero
class Numero {
private:
    std::string valor;
    void validar(std::string v);
public:
    void setValor(std::string v);
    std::string getValor() const { return valor; }
    friend std::ostream& operator<<(std::ostream& os, const Numero& numero) {
        return os << numero.valor;
    }
};

//Dominio Capacidade
class Capacidade {
private:
    int valor;
    void validar(int v);
public:
    void setValor(int v);
    int getValor() const { return valor; }
    friend std::ostream& operator<<(std::ostream& os, const Capacidade& capacidade) {
        return os << capacidade.valor;
    }
};

//Domínio Dinheiro
class Dinheiro {
private:
    int valor;
    void validar(int v);
public:
    void setValor(int v);
    int getValor() const { return valor; }
    friend std::ostream& operator<<(std::ostream& os, const Dinheiro& dinheiro) {
        // Formata para R$ X.YY (assuming valor is in cents)
        std::ios_base::fmtflags ff = os.flags(); // Save original flags
        os << std::fixed << std::setprecision(2) << (static_cast<double>(dinheiro.valor) / 100.0);
        os.flags(ff); // Restore original flags
        return os;
    }
};

//Domínio Cartão
class Cartao {
private:
    std::string valor;
    void validar(std::string v);
public:
    void setValor(std::string v);
    std::string getValor() const { return valor; }
    friend std::ostream& operator<<(std::ostream& os, const Cartao& cartao) {
        return os << cartao.valor;
    }
};

//Domínio Data
class Data {
private:
    std::string valor;
    void validar(std::string v);
public:
    void setValor(std::string v);
    std::string getValor() const { return valor; }
    friend std::ostream& operator<<(std::ostream& os, const Data& data) {
        return os << data.valor;
    }
};

#endif