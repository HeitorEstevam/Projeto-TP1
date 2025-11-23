#ifndef INTERFACES_HPP
#define INTERFACES_HPP

#include "entidades.hpp"
#include <vector>
#include <string>

// Serviços gerentes
class IServicoGerente {
public:
    virtual bool criarGerente(const Gerente& gerente) = 0;
    virtual Gerente* autenticar(const std::string& email, const std::string& senha) = 0;

    // Edita os dados de um gerente. Retorna true se sucesso, false se o gerente não for encontrado ou se o novo email já estiver em uso.
    virtual bool editarGerente(const Gerente& gerente) = 0;

    // Exclui um gerente pelo email. Retorna true se sucesso, false se o gerente não for encontrado.
    virtual bool excluirGerente(const std::string& email) = 0;

    virtual bool carregar() = 0; // Added for persistence
    virtual bool salvar() = 0;   // Added for persistence

    // Destrutor virtual
    virtual ~IServicoGerente() {}
};

// Serviços hoteis
class IServicoHotel {
public:
    virtual void criarHotel(const Hotel& hotel) = 0;
    virtual Hotel* buscarHotel(const std::string& codigo) = 0;

    // Retorna a lista completa
    virtual std::vector<Hotel> listarHoteis() = 0;

    // Edita os dados de um hotel. Retorna true se sucesso, false se o hotel não for encontrado ou se o novo código já estiver em uso.
    virtual bool editarHotel(const Hotel& hotel) = 0;

    // Exclui um hotel pelo código. Retorna true se sucesso, false se o hotel não for encontrado.
    virtual bool excluirHotel(const std::string& codigo) = 0;

    virtual bool carregar() = 0; // Added for persistence
    virtual bool salvar() = 0;   // Added for persistence

    //Destrutor virtual
    virtual ~IServicoHotel() {}
};

// Serviços quartos
class IServicoQuarto {
public:
    virtual bool criarQuarto(const Quarto& quarto) = 0;

    // Retorna a lista de todos os quartos
    virtual std::vector<Quarto> listarQuartos() = 0;

    // Edita os dados de um quarto. Retorna true se sucesso, false se o quarto não for encontrado ou se o novo número já estiver em uso no mesmo hotel.
    virtual bool editarQuarto(const Quarto& quarto) = 0;

    // Exclui um quarto pelo código do hotel e número do quarto. Retorna true se sucesso, false se o quarto não for encontrado.
    virtual bool excluirQuarto(const std::string& codigoHotel, const std::string& numeroQuarto) = 0;

    virtual bool carregar() = 0; // Added for persistence
    virtual bool salvar() = 0;   // Added for persistence

    //Destrutor virtual
    virtual ~IServicoQuarto() {}
};

// Serviços hóspedes
class IServicoHospede {
public:
    virtual bool criarHospede(const Hospede& hospede) = 0;

    // Busca hóspede por email (chave única).
    virtual Hospede* buscarHospede(const std::string& email) = 0;

    // Lista todos os hóspedes
    virtual std::vector<Hospede> listarHospedes() = 0;

    // Edita os dados de um hóspede. Retorna true se sucesso, false se o hóspede não for encontrado ou se o novo email já estiver em uso.
    virtual bool editarHospede(const Hospede& hospede) = 0;

    // Exclui um hóspede pelo email. Retorna true se sucesso, false se o hóspede não for encontrado.
    virtual bool excluirHospede(const std::string& email) = 0;

    virtual bool carregar() = 0; // Added for persistence
    virtual bool salvar() = 0;   // Added for persistence

    //Destruidor virtual
    virtual ~IServicoHospede() {}
};

// Serviços reserva
class IServicoReserva {
public:
    virtual bool criarReserva(const Reserva& reserva) = 0;

    // Lista todas as reservas
    virtual std::vector<Reserva> listarReservas() = 0;

    // Edita os dados de uma reserva. Retorna true se sucesso, false se a reserva não for encontrada.
    virtual bool editarReserva(const Reserva& reserva) = 0;

    // Exclui uma reserva pelo código. Retorna true se sucesso, false se a reserva não for encontrada.
    virtual bool excluirReserva(const std::string& codigo) = 0;

    virtual bool carregar() = 0; // Added for persistence
    virtual bool salvar() = 0;   // Added for persistence

    //Destruidor virtual
    virtual ~IServicoReserva() {}
};

#endif