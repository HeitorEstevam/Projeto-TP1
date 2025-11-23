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

bool ContainerGerente::editarGerente(const Gerente& gerente) {
    for (size_t i = 0; i < dbGerentes.size(); ++i) {
        if (dbGerentes[i].getEmail().getValor() == gerente.getEmail().getValor()) {
            dbGerentes[i] = gerente; // Assume Gerente has appropriate assignment operator
            return true;
        }
    }
    return false; // Gerente não encontrado
}

bool ContainerGerente::excluirGerente(const std::string& email) {
    for (auto it = dbGerentes.begin(); it != dbGerentes.end(); ++it) {
        if (it->getEmail().getValor() == email) {
            dbGerentes.erase(it);
            return true;
        }
    }
    return false; // Gerente não encontrado
}

// Hotel
// Constructor with dependency injection
ContainerHotel::ContainerHotel(IServicoQuarto* sQuarto, IServicoReserva* sReserva) :
    servicoQuarto(sQuarto), servicoReserva(sReserva) {}

void ContainerHotel::criarHotel(const Hotel& hotel) {
    for (const auto& h : dbHoteis) {
        if (h.getCodigo().getValor() == hotel.getCodigo().getValor()) {
            return;
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

bool ContainerHotel::editarHotel(const Hotel& hotel) {
    for (size_t i = 0; i < dbHoteis.size(); ++i) {
        if (dbHoteis[i].getCodigo().getValor() == hotel.getCodigo().getValor()) {
            dbHoteis[i] = hotel;
            return true;
        }
    }
    return false;
}

bool ContainerHotel::excluirHotel(const std::string& codigo) {
    for (auto itHotel = dbHoteis.begin(); itHotel != dbHoteis.end(); ++itHotel) {
        if (itHotel->getCodigo().getValor() == codigo) {
            // Antes de excluir o Hotel, excluir todos os Quartos associados
            // e suas respectivas Reservas usando os serviços injetados.

            // Listar quartos para saber quais excluir
            std::vector<Quarto> todosQuartos = servicoQuarto->listarQuartos();
            for (const auto& quarto : todosQuartos) {
                if (quarto.getHotel()->getCodigo().getValor() == codigo) {
                    // Excluir quarto (que por sua vez excluirá suas reservas)
                    servicoQuarto->excluirQuarto(quarto.getHotel()->getCodigo().getValor(), quarto.getNumero().getValor());
                }
            }
            dbHoteis.erase(itHotel);
            return true;
        }
    }
    return false; // Hotel não encontrado
}

// Quarto
// Constructor with dependency injection
ContainerQuarto::ContainerQuarto(IServicoReserva* sReserva) :
    servicoReserva(sReserva) {}

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

bool ContainerQuarto::editarQuarto(const Quarto& quarto) {
    std::string codHotel = quarto.getHotel()->getCodigo().getValor();
    std::string numQuarto = quarto.getNumero().getValor();

    for (size_t i = 0; i < dbQuartos.size(); ++i) {
        if (dbQuartos[i].getHotel()->getCodigo().getValor() == codHotel &&
            dbQuartos[i].getNumero().getValor() == numQuarto) {
            dbQuartos[i] = quarto;
            return true;
        }
    }
    return false; // Quarto não encontrado
}

bool ContainerQuarto::excluirQuarto(const std::string& codigoHotel, const std::string& numeroQuarto) {
    for (auto itQuarto = dbQuartos.begin(); itQuarto != dbQuartos.end(); ++itQuarto) {
        if (itQuarto->getHotel()->getCodigo().getValor() == codigoHotel &&
            itQuarto->getNumero().getValor() == numeroQuarto) {
            
            // Antes de excluir o Quarto, excluir todas as Reservas associadas a ele
            std::vector<Reserva> todasReservas = servicoReserva->listarReservas();
            for (const auto& reserva : todasReservas) {
                if (reserva.getQuarto()->getHotel()->getCodigo().getValor() == codigoHotel &&
                    reserva.getQuarto()->getNumero().getValor() == numeroQuarto) {
                    servicoReserva->excluirReserva(reserva.getCodigo().getValor());
                }
            }
            dbQuartos.erase(itQuarto);
            return true;
        }
    }
    return false; // Quarto não encontrado
}


// Hóspede
// Constructor with dependency injection
ContainerHospede::ContainerHospede(IServicoReserva* sReserva) :
    servicoReserva(sReserva) {}

bool ContainerHospede::criarHospede(const Hospede& hospede) {
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

bool ContainerHospede::editarHospede(const Hospede& hospede) {
    for (size_t i = 0; i < dbHospedes.size(); ++i) {
        if (dbHospedes[i].getEmail().getValor() == hospede.getEmail().getValor()) {
            dbHospedes[i] = hospede;
            return true;
        }
    }
    return false;
}

bool ContainerHospede::excluirHospede(const std::string& email) {
    for (auto itHospede = dbHospedes.begin(); itHospede != dbHospedes.end(); ++itHospede) {
        if (itHospede->getEmail().getValor() == email) {
            // Antes de excluir o Hóspede, excluir todas as Reservas associadas a ele
            std::vector<Reserva> todasReservas = servicoReserva->listarReservas();
            for (const auto& reserva : todasReservas) {
                if (reserva.getHospede()->getEmail().getValor() == email) {
                    servicoReserva->excluirReserva(reserva.getCodigo().getValor());
                }
            }
            dbHospedes.erase(itHospede);
            return true;
        }
    }
    return false; // Hóspede não encontrado
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

bool ContainerReserva::editarReserva(const Reserva& reserva) {
    for (size_t i = 0; i < dbReservas.size(); ++i) {
        if (dbReservas[i].getCodigo().getValor() == reserva.getCodigo().getValor()) {
            dbReservas[i] = reserva;
            return true;
        }
    }
    return false; // Reserva não encontrada
}

bool ContainerReserva::excluirReserva(const std::string& codigo) {
    for (auto it = dbReservas.begin(); it != dbReservas.end(); ++it) {
        if (it->getCodigo().getValor() == codigo) {
            dbReservas.erase(it);
            return true;
        }
    }
    return false; // Reserva não encontrada
}