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
};

// Container de hoteis
class ContainerHotel : public IServicoHotel {
private:
    std::vector<Hotel> dbHoteis;
public:
    void criarHotel(const Hotel& hotel) override;
    Hotel* buscarHotel(const std::string& codigo) override;
    std::vector<Hotel> listarHoteis() override;
};

// Container de quartos
class ContainerQuarto : public IServicoQuarto {
private:
    std::vector<Quarto> dbQuartos;
public:
    bool criarQuarto(const Quarto& quarto) override;
    std::vector<Quarto> listarQuartos() override;
};

// Container de hóspedes
class ContainerHospede : public IServicoHospede {
private:
    std::vector<Hospede> dbHospedes;
public:
    bool criarHospede(const Hospede& hospede) override;
    Hospede* buscarHospede(const std::string& email) override;
    std::vector<Hospede> listarHospedes() override;
};

// Container de reservas
class ContainerReserva : public IServicoReserva {
private:
    std::vector<Reserva> dbReservas;
public:
    bool criarReserva(const Reserva& reserva) override;
    std::vector<Reserva> listarReservas() override;
};

#endif