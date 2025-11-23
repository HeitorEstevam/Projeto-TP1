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
    //Destruidor virtual
    virtual ~IServicoHotel() {}
};

// Serviços quartos
class IServicoQuarto {
public:
    virtual bool criarQuarto(const Quarto& quarto) = 0;

    // Retorna a lista de todos os quartos
    virtual std::vector<Quarto> listarQuartos() = 0;
    //Destruidor virtual
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
    //Destruidor padrão
    virtual ~IServicoHospede() {}
};

// Serviços reserva
class IServicoReserva {
public:
    virtual bool criarReserva(const Reserva& reserva) = 0;

    // Lista todas as reservas
    virtual std::vector<Reserva> listarReservas() = 0;
    //Destruidor padrão
    virtual ~IServicoReserva() {}
};

#endif