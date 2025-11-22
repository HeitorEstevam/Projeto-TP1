#ifndef DOMINIOS_HPP
#define DOMINIOS_HPP

#include <string>
#include <vector>
#include <memory>
#include <iostream>

//Declaração de classe para evitar erro de compilação
class Quarto;
class Reserva;
class Hospede;

// Classe Pessoa
class Pessoa {
protected:
    std::string nome;
    std::string email;

public:
    //Métodos contrutores
    Pessoa() = default;
    Pessoa(const std::string& nome, const std::string& email);

    // Getters
    std::string getNome() const { return nome; };
    std::string getEmail() const { return email; };

    // Setters com validação
    void setNome(const std::string& nome) { this->nome = nome; };
    void setEmail(const std::string& email) { this->email = email; };

    // Validações
    bool validarNome(const std::string& nome) const;
    bool validarEmail(const std::string& email) const;
};


// Classe Gerente (herda de Pessoa)
class Gerente : public Pessoa {
private:
    std::string senha;
    int ramal;

    //Declaração de vetor para guardar hoteis
    std::vector<Hotel> hoteis;
    std::vector<Hospede> hospedes;

public:
    //Métodos contrutores
    Gerente() = default;
    Gerente(const std::string& nome, const std::string& email, const std::string& senha, int ramal);

    // Getters e setters
    std::string getSenha() const { return senha; };
    int getRamal() const { return ramal; };
    void setSenha(const std::string& senha) { this->senha = senha; };
    void setRamal(int ramal) { this->ramal = ramal; };

    // Validação
    bool validarSenha(const std::string& senha) const;
    bool validarRamal(int ramal) const;

    // Ações do gerente
    void criarHotel();
    void editarHotel();
    void excluirHotel();
    void listarHoteis();

    void criarQuarto();
    void editarQuarto();
    void excluirQuarto();
    void listarQuartos();

    void criarHospede();
    void editarHospede();
    void excluirHospede();
    void listarHospedes();

    void criarReserva();
    void editarReserva();
    void excluirReserva();
    void listarReservas();

    void lerConta();
    void editarConta();
    void excluirConta();

    //Ações complementares
    Hotel* buscarHotelPorCodigo(const std::string& codigo);
    Quarto* buscarQuartoPorCodigo(const std::string& codigo) const;
    Reserva* buscarReservaPorCodigo(const std::string& codigo) const;
    std::vector<Hospede>& getHospedes();
};


// Classe Hotel
class Hotel {
private:
    std::string nome;
    std::string endereco;
    std::string telefone;
    std::string codigo;

    //Associação obrigatória
    Gerente* gerente;

    //Composição (um hotel tem quartos)
    std::vector<Quarto> quartos;

public:
    //Métodos contrutores
    Hotel() = default;
    Hotel(const std::string& nome, const std::string& endereco, const std::string& telefone, const std::string& codigo, Gerente* gerente);

    // Getters e setters
    std::string getNome() const { return nome; };
    std::string getEndereco() const { return endereco; };
    std::string getTelefone() const { return telefone; };
    std::string getCodigo() const { return codigo; };
    Gerente& getgerente() const { return *gerente; };

    void setNome(const std::string& nome);
    void setEndereco(const std::string& endereco);
    void setTelefone(const std::string& telefone);
    void setCodigo(const std::string& codigo);

    // Validações
    bool validarNome(const std::string& nome) const;
    bool validarEndereco(const std::string& endereco) const;
    bool validarTelefone(const std::string& telefone) const;
    bool validarCodigo(const std::string& codigo) const;

    // Método usado pelo gerente para associar um quarto ao hotel
    void adicionarQuarto(const Quarto& quarto) {
        quartos.push_back(quarto);
    }

    //Métodos complementares
    std::vector<Quarto>& getQuartos();
    void listarQuartos() const;
};


// Classe Quarto
class Quarto {
private:
    std::string numero;
    int capacidade;
    int diaria;
    std::string ramal;

    //Associações dos quartos (obrigatória e opcional)
    Hotel* hotel;
    Reserva* reserva;

public:
    //Métodos contrutores
    Quarto() : hotel(nullptr), reserva(nullptr) {}
    Quarto(const std::string& numero, int capacidade, int diaria, const std::string& ramal, Hotel* hotel)
    : numero(numero),
      capacidade(capacidade),
      diaria(diaria),
      ramal(ramal),
      hotel(hotel),
      reserva(nullptr) {}


    // Getters e setters
    std::string getNumero() const { return numero; };
    int getCapacidade() const { return capacidade; };
    int getDiaria() const { return diaria; };
    std::string getRamal() const { return ramal; };
    Hotel* getHotel() const { return hotel; }
    Reserva* getReserva() const { return reserva; }

    void setNumero(const std::string& numero) { this->numero = numero;}
    void setCapacidade(int capacidade) { this->capacidade = capacidade; };
    void setDiaria(int diaria) { this->diaria = diaria; };
    void setRamal(const std::string& ramal) { this->ramal = ramal;}

    // Validações
    bool validarNumero(const std::string& numero) const;
    bool validarCapacidade(int capacidade) const;
    bool validarDiaria(int diaria) const;
    bool validarRamal(const std::string& ramal) const;

    //Associações com reserva
    void associarReserva(Reserva* reserva) { this->reserva = reserva; }
    void removerReserva(Reserva* reserva) { this->reserva = nullptr; }
};

// Classe Hospede
class Hospede : public Pessoa {
private:
    std::string endereco;
    std::string cartao;

    //Associação opcional
    Reserva* reserva;

public:
    //Métodos contrutores
    Hospede() : reserva(nullptr) {}
    Hospede(const std::string& nome, const std::string& email, const std::string& endereco, const std::string& cartao)
        : Pessoa(nome, email), endereco(endereco), cartao(cartao), reserva(nullptr) {}

    //Getters e setters
    std::string getEndereco() const { return endereco; };
    std::string getCartao() const { return cartao; };
    Reserva* getReserva() const { return reserva; }

    void setEndereco(const std::string& endereco) { this->endereco = endereco; };
    void setCartao(const std::string& cartao) { this->cartao = cartao; };

    //Validações
    bool validarEndereco(const std::string& endereco) const;
    bool validarCartao(const std::string& cartao) const;

    //Associação com reserva
    void associarReserva(Reserva* reserva) { this->reserva = reserva; }
    void removerReserva(Reserva* reserva) { this->reserva = nullptr; }
};


// Classe Reserva
class Reserva {
private:
    std::string dataChegada;
    std::string dataPartida;
    int valor;
    std::string codigo;

    //Associações obrigatórias
    Hospede* hospede;
    Quarto* quarto;

public:
    //Métodos contrutores
    Reserva() = default;
    Reserva(const std::string& dataChegada, const std::string& dataPartida, int valor, const std::string& codigo);

    //Getters e setters
    std::string getDataChegada() const { return dataChegada; };
    std::string getDataPartida() const { return dataPartida; };
    int getValor() const { return valor; };
    std::string getCodigo() const { return codigo; };
    Hospede* getHospede() const { return hospede; }
    Quarto* getQuarto() const { return quarto; }

    void setDataChegada(const std::string& data) { this->dataChegada = data; };
    void setDataPartida(const std::string& data) { this->dataPartida = data; };
    void setValor(int valor) { this->valor = valor; };
    void setCodigo(const std::string& codigo) { this->codigo = codigo; };

    //Validações
    bool validarData(const std::string& data) const;
    bool validarValor(int valor) const;
    bool validarCodigo(const std::string& codigo) const;

    //Associações
    void setHospede(Hospede* hospede) { this->hospede = hospede; }
    void setQuarto(Quarto* quarto) { this->quarto = quarto; }
};

#endif
