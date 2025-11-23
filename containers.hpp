#ifndef CONTAINERS_HPP
#define CONTAINERS_HPP

#include "interfaces.hpp"
#include <vector>

// Container de gerentes
class ContainerGerente : public IServicoGerente {
private:
    std::vector<Gerente> dbGerentes; // Banco de dados em memória
public:
    bool criarGerente(const Gerente& gerente) override;
    Gerente* autenticar(const std::string& email, const std::string& senha) override;
    bool editarGerente(const Gerente& gerente) override; // Added
    bool excluirGerente(const std::string& email) override; // Added
};

// Container de hoteis
class ContainerHotel : public IServicoHotel {
private:
    std::vector<Hotel> dbHoteis;
    IServicoQuarto* servicoQuarto;    // Injected dependency
    IServicoReserva* servicoReserva;  // Injected dependency
public:
    // Constructor to inject dependencies
    ContainerHotel(IServicoQuarto* sQuarto, IServicoReserva* sReserva);

    void criarHotel(const Hotel& hotel) override;
    Hotel* buscarHotel(const std::string& codigo) override;
    std::vector<Hotel> listarHoteis() override;
    bool editarHotel(const Hotel& hotel) override;
    bool excluirHotel(const std::string& codigo) override;
};

// Container de quartos
class ContainerQuarto : public IServicoQuarto {
private:
    std::vector<Quarto> dbQuartos;
    IServicoReserva* servicoReserva;  // Injected dependency
public:
    // Constructor to inject dependencies
    ContainerQuarto(IServicoReserva* sReserva);

    bool criarQuarto(const Quarto& quarto) override;
    std::vector<Quarto> listarQuartos() override;
    bool editarQuarto(const Quarto& quarto) override;
    bool excluirQuarto(const std::string& codigoHotel, const std::string& numeroQuarto) override;
};

// Container de hóspedes
class ContainerHospede : public IServicoHospede {
private:
    std::vector<Hospede> dbHospedes;
    IServicoReserva* servicoReserva; // Injected dependency
public:
    // Constructor to inject dependencies
    ContainerHospede(IServicoReserva* sReserva);

    bool criarHospede(const Hospede& hospede) override;
    Hospede* buscarHospede(const std::string& email) override;
    std::vector<Hospede> listarHospedes() override;
    bool editarHospede(const Hospede& hospede) override;
    bool excluirHospede(const std::string& email) override;
};

// Container de reservas
class ContainerReserva : public IServicoReserva {
private:
    std::vector<Reserva> dbReservas;
public:
    bool criarReserva(const Reserva& reserva) override;
    std::vector<Reserva> listarReservas() override;
    bool editarReserva(const Reserva& reserva) override; // Added
    bool excluirReserva(const std::string& codigo) override; // Added
};

#endif