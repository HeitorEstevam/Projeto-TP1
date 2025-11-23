#ifndef INTERFACES_HPP
#define INTERFACES_HPP

#include "entidades.hpp"
#include <vector>
#include <string>

// INTERFACE DE SERVIÇO DE GERENTES
// Responsável por autenticação e cadastro de novos gerentes
class IServicoGerente {
public:
    // Tenta criar um gerente. Retorna false se o email já estiver em uso.
    virtual bool criarGerente(const Gerente& gerente) = 0;

    // Tenta autenticar. Retorna ponteiro para o gerente se sucesso, ou nullptr se falha.
    virtual Gerente* autenticar(const std::string& email, const std::string& senha) = 0;

    // Destrutor virtual obrigatório em interfaces
    virtual ~IServicoGerente() {}
};

// INTERFACE DE SERVIÇO DE HOTÉIS
// Responsável por gerenciar a lista de hotéis
class IServicoHotel {
public:
    // Cria um novo hotel
    virtual void criarHotel(const Hotel& hotel) = 0;

    // Busca um hotel pelo código único. Retorna nullptr se não achar.
    virtual Hotel* buscarHotel(const std::string& codigo) = 0;

    // Retorna a lista completa (usado para exibir ajuda ao usuário)
    virtual std::vector<Hotel> listarHoteis() = 0;

    virtual ~IServicoHotel() {}
};

// INTERFACE DE SERVIÇO DE QUARTOS
// Responsável por gerenciar a lista de quartos
class IServicoQuarto {
public:
    // Cria um quarto. Retorna false se já existir um quarto com mesmo número no mesmo hotel.
    virtual bool criarQuarto(const Quarto& quarto) = 0;

    // Retorna a lista de todos os quartos (a filtragem por hotel é feita na apresentação ou aqui)
    virtual std::vector<Quarto> listarQuartos() = 0;

    virtual ~IServicoQuarto() {}
};

// INTERFACE DE SERVIÇO DE HÓSPEDES
// Responsável por gerenciar cadastro de hóspedes
class IServicoHospede {
public:
    // Cria um hóspede. Retorna false se o email já estiver cadastrado.
    virtual bool criarHospede(const Hospede& hospede) = 0;

    // Busca hóspede por email (chave única). Retorna nullptr se não achar.
    virtual Hospede* buscarHospede(const std::string& email) = 0;

    // Lista todos os hóspedes (útil para ajudar o gerente a achar o email correto)
    virtual std::vector<Hospede> listarHospedes() = 0;

    virtual ~IServicoHospede() {}
};

// INTERFACE DE SERVIÇO DE RESERVAS
// Responsável por armazenar reservas e verificar disponibilidade
class IServicoReserva {
public:
    // Cria uma reserva. Retorna false se houver conflito de código ou lógica.
    virtual bool criarReserva(const Reserva& reserva) = 0;

    // Lista todas as reservas (usado para verificar conflitos de data na apresentação)
    virtual std::vector<Reserva> listarReservas() = 0;

    virtual ~IServicoReserva() {}
};

#endif