#ifndef CONTAINERS_HPP
#define CONTAINERS_HPP

#include "interfaces.hpp"
#include <vector>

// Container de gerentes
class ContainerGerente : public IServicoGerente {
private:
    std::vector<Gerente> dbGerentes; // Banco de dados em memória
    std::string nomeArquivo;         // Filename for persistence
public:
    ContainerGerente(std::string nomeArquivo); // Constructor to accept filename
    bool criarGerente(const Gerente& gerente) override;
    Gerente* autenticar(const std::string& email, const std::string& senha) override;
    bool editarGerente(const Gerente& gerente) override;
    bool excluirGerente(const std::string& email) override;
    bool carregar() override; // Added
    bool salvar() override;   // Added
};

// Container de hoteis
class ContainerHotel : public IServicoHotel {
private:
    std::vector<Hotel> dbHoteis;
    IServicoQuarto* servicoQuarto;    // Injected dependency
    IServicoReserva* servicoReserva;  // Injected dependency
    std::string nomeArquivo;         // Filename for persistence
public:
    // Constructor to inject dependencies and filename
    ContainerHotel(std::string nomeArquivo, IServicoQuarto* sQuarto, IServicoReserva* sReserva);

    void criarHotel(const Hotel& hotel) override;
    Hotel* buscarHotel(const std::string& codigo) override;
    std::vector<Hotel> listarHoteis() override;
    bool editarHotel(const Hotel& hotel) override;
    bool excluirHotel(const std::string& codigo) override;
    bool carregar() override; // Added
    bool salvar() override;   // Added
};

// Container de quartos
class ContainerQuarto : public IServicoQuarto {
private:
    std::vector<Quarto> dbQuartos;
    IServicoReserva* servicoReserva;  // Injected dependency
    std::string nomeArquivo;         // Filename for persistence
public:
    // Constructor to inject dependencies and filename
    ContainerQuarto(std::string nomeArquivo, IServicoReserva* sReserva);

    bool criarQuarto(const Quarto& quarto) override;
    std::vector<Quarto> listarQuartos() override;
    bool editarQuarto(const Quarto& quarto) override;
    bool excluirQuarto(const std::string& codigoHotel, const std::string& numeroQuarto) override;
    bool carregar() override; // Added
    bool salvar() override;   // Added
};

// Container de hóspedes
class ContainerHospede : public IServicoHospede {
private:
    std::vector<Hospede> dbHospedes;
    IServicoReserva* servicoReserva; // Injected dependency
    std::string nomeArquivo;         // Filename for persistence
public:
    // Constructor to inject dependencies and filename
    ContainerHospede(std::string nomeArquivo, IServicoReserva* sReserva);

    bool criarHospede(const Hospede& hospede) override;
    Hospede* buscarHospede(const std::string& email) override;
    std::vector<Hospede> listarHospedes() override;
    bool editarHospede(const Hospede& hospede) override;
    bool excluirHospede(const std::string& email) override;
    bool carregar() override; // Added
    bool salvar() override;   // Added
};

// Container de reservas
class ContainerReserva : public IServicoReserva {
private:
    std::vector<Reserva> dbReservas;
    std::string nomeArquivo;         // Filename for persistence
public:
    ContainerReserva(std::string nomeArquivo); // Constructor to accept filename
    bool criarReserva(const Reserva& reserva) override;
    bool editarReserva(const Reserva& reserva) override;
    bool excluirReserva(const std::string& codigo) override;
    std::vector<Reserva> listarReservas() override;
    bool carregar() override; // Added
    bool salvar() override;   // Added
};

#endif