#include "containers.hpp"

// Gerente
bool ContainerGerente::criarGerente(const Gerente& gerente) {
    // Verifica duplicidade de email
    for (const auto& g : dbGerentes) {
        if (g.getEmail().getValor() == gerente.getEmail().getValor()) {
            return false; // Email já existe
        }
    }
    dbGerentes.push_back(gerente);
    return true;
}

Gerente* ContainerGerente::autenticar(const std::string& email, const std::string& senha) {
    for (size_t i = 0; i < dbGerentes.size(); ++i) {
        if (dbGerentes[i].getEmail().getValor() == email &&
            dbGerentes[i].getSenha().getValor() == senha) {
            return &dbGerentes[i]; // Sucesso
        }
    }
    return nullptr; // Falha
}

// Hotel
void ContainerHotel::criarHotel(const Hotel& hotel) {
    // Como o PDF não especifica validação estrita de código único para criar hotel
    // (apenas diz que código é PK), vamos assumir que a apresentação cuida ou simplesmente inserimos.
    // Mas uma boa prática é verificar:
    for (const auto& h : dbHoteis) {
        if (h.getCodigo().getValor() == hotel.getCodigo().getValor()) {
            return; // Evita duplicar código (opcional, mas recomendado)
        }
    }
    dbHoteis.push_back(hotel);
}

Hotel* ContainerHotel::buscarHotel(const std::string& codigo) {
    for (size_t i = 0; i < dbHoteis.size(); ++i) {
        if (dbHoteis[i].getCodigo().getValor() == codigo) {
            return &dbHoteis[i];
        }
    }
    return nullptr;
}

std::vector<Hotel> ContainerHotel::listarHoteis() {
    return dbHoteis;
}

// Quarto
bool ContainerQuarto::criarQuarto(const Quarto& quarto) {
    // Regra: Não pode haver dois quartos com mesmo número NO MESMO HOTEL.
    std::string codHotelNovo = quarto.getHotel()->getCodigo().getValor();
    std::string numQuartoNovo = quarto.getNumero().getValor();

    for (const auto& q : dbQuartos) {
        if (q.getHotel()->getCodigo().getValor() == codHotelNovo &&
            q.getNumero().getValor() == numQuartoNovo) {
            return false; // Já existe este quarto neste hotel
        }
    }
    dbQuartos.push_back(quarto);
    return true;
}

std::vector<Quarto> ContainerQuarto::listarQuartos() {
    return dbQuartos;
}

// Hóspede
bool ContainerHospede::criarHospede(const Hospede& hospede) {
    // Validação de unicidade por Email
    for (const auto& h : dbHospedes) {
        if (h.getEmail().getValor() == hospede.getEmail().getValor()) {
            return false;
        }
    }
    dbHospedes.push_back(hospede);
    return true;
}

Hospede* ContainerHospede::buscarHospede(const std::string& email) {
    for (size_t i = 0; i < dbHospedes.size(); ++i) {
        if (dbHospedes[i].getEmail().getValor() == email) {
            return &dbHospedes[i];
        }
    }
    return nullptr;
}

std::vector<Hospede> ContainerHospede::listarHospedes() {
    return dbHospedes;
}

// Reserva
bool ContainerReserva::criarReserva(const Reserva& reserva) {
    // Validação de unicidade pelo Código da Reserva
    for (const auto& r : dbReservas) {
        if (r.getCodigo().getValor() == reserva.getCodigo().getValor()) {
            return false;
        }
    }
    dbReservas.push_back(reserva);
    return true;
}

std::vector<Reserva> ContainerReserva::listarReservas() {
    return dbReservas;
}