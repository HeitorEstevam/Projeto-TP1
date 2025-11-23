#include "containers.hpp"
#include <fstream>   // For file operations
#include <sstream>   // For string stream operations
#include <limits>    // For numeric_limits in ignore
#include <iostream>

// Gerente
ContainerGerente::ContainerGerente(std::string nomeArquivo) : nomeArquivo(nomeArquivo) {
    carregar(); // Load data from file when constructed
}

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

bool ContainerGerente::carregar() {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        return false; // File might not exist yet, or cannot be opened
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        std::stringstream ss(linha);
        std::string emailStr, senhaStr, nomeStr, ramalStr;

        std::getline(ss, emailStr, '|');
        std::getline(ss, senhaStr, '|');
        std::getline(ss, nomeStr, '|');
        std::getline(ss, ramalStr, '|');

        try {
            Email email;
            email.setValor(emailStr);
            Senha senha;
            senha.setValor(senhaStr);
            Nome nome;
            nome.setValor(nomeStr);
            Ramal ramal;
            ramal.setValor(ramalStr);

            dbGerentes.push_back(Gerente(nome, email, senha, ramal));
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro ao carregar Gerente: " << e.what() << " - Linha ignorada: " << linha << std::endl;
        }
    }
    arquivo.close();
    return true;
}

bool ContainerGerente::salvar() {
    std::ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        return false; // Cannot be opened for writing
    }

    for (const auto& gerente : dbGerentes) {
        arquivo << gerente.getEmail().getValor() << "|"
                << gerente.getSenha().getValor() << "|"
                << gerente.getNome().getValor() << "|"
                << gerente.getRamal().getValor() << std::endl;
    }
    arquivo.close();
    return true;
}


// Hotel
// Constructor with dependency injection
ContainerHotel::ContainerHotel(std::string nomeArquivo, IServicoQuarto* sQuarto, IServicoReserva* sReserva) :
    nomeArquivo(nomeArquivo), servicoQuarto(sQuarto), servicoReserva(sReserva) {
    carregar(); // Load data from file when constructed
}

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

bool ContainerHotel::carregar() {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        return false;
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        std::stringstream ss(linha);
        std::string codigoStr, nomeStr, enderecoStr, telefoneStr, gerenteEmailStr;

        std::getline(ss, codigoStr, '|');
        std::getline(ss, nomeStr, '|');
        std::getline(ss, enderecoStr, '|');
        std::getline(ss, telefoneStr, '|');
        std::getline(ss, gerenteEmailStr, '|');

        try {
            Codigo codigo;
            codigo.setValor(codigoStr);
            Nome nome;
            nome.setValor(nomeStr);
            Endereco endereco;
            endereco.setValor(enderecoStr);
            Telefone telefone;
            telefone.setValor(telefoneStr);
            
            // Reconstruir o Hotel. O gerente é um ponteiro e será injetado na entidade Hotel
            // no momento do uso ou carregado de forma separada se necessário.
            // Por simplicidade aqui, vamos apenas criar o Hotel sem associar o gerente no carregamento.
            // A associação real do gerente ao hotel seria feita em outro lugar (ex: ao logar o gerente)
            // ou exigiria um serviço de gerente para buscar o gerente pelo email.
            Hotel hotel(nome, endereco, telefone, codigo);
            // hotel.setGerente(servicoGerente->buscarGerente(gerenteEmailStr)); // This would require IServicoGerente as a dependency
            dbHoteis.push_back(hotel);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro ao carregar Hotel: " << e.what() << " - Linha ignorada: " << linha << std::endl;
        }
    }
    arquivo.close();
    return true;
}

bool ContainerHotel::salvar() {
    std::ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        return false;
    }

    for (const auto& hotel : dbHoteis) {
        arquivo << hotel.getCodigo().getValor() << "|"
                << hotel.getNome().getValor() << "|"
                << hotel.getEndereco().getValor() << "|"
                << hotel.getTelefone().getValor() << "|"
                << (hotel.getGerente() ? hotel.getGerente()->getEmail().getValor() : "N/A") << std::endl;
    }
    arquivo.close();
    return true;
}


// Quarto
// Constructor with dependency injection
ContainerQuarto::ContainerQuarto(std::string nomeArquivo, IServicoReserva* sReserva) :
    nomeArquivo(nomeArquivo), servicoReserva(sReserva) {
    carregar(); // Load data from file when constructed
}

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

bool ContainerQuarto::carregar() {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        return false;
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        std::stringstream ss(linha);
        std::string numeroStr, capacidadeStr, diariaStr, ramalStr, codigoHotelStr;

        std::getline(ss, numeroStr, '|');
        std::getline(ss, capacidadeStr, '|');
        std::getline(ss, diariaStr, '|');
        std::getline(ss, ramalStr, '|');
        std::getline(ss, codigoHotelStr, '|');

        try {
            Numero numero;
            numero.setValor(numeroStr);
            Capacidade capacidade;
            capacidade.setValor(std::stoi(capacidadeStr));
            Dinheiro diaria;
            diaria.setValor(std::stoi(diariaStr));
            Ramal ramal;
            ramal.setValor(ramalStr);

            // Reconstruir o Quarto. O Hotel é um ponteiro. Para carregar corretamente
            // precisaríamos de um IServicoHotel injetado aqui para buscar o hotel pelo código.
            // Por simplicidade, assumimos que o hotel existe.
            // Quarto quarto(numero, capacidade, diaria, ramal, servicoHotel->buscarHotel(codigoHotelStr));
            // Como o ContainerQuarto não tem IServicoHotel injetado, vamos criar com nullptr e a associação real
            // será feita "fora" ou em um passo posterior, ou exigiria refatorar a injeção de dependência.
            dbQuartos.push_back(Quarto(numero, capacidade, diaria, ramal, nullptr)); // Temporarily nullptr
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro ao carregar Quarto: " << e.what() << " - Linha ignorada: " << linha << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Erro de número ao carregar Quarto: " << e.what() << " - Linha ignorada: " << linha << std::endl;
        }
    }
    arquivo.close();
    return true;
}

bool ContainerQuarto::salvar() {
    std::ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        return false;
    }

    for (const auto& quarto : dbQuartos) {
        arquivo << quarto.getNumero().getValor() << "|"
                << std::to_string(quarto.getCapacidade().getValor()) << "|"
                << std::to_string(quarto.getDiaria().getValor()) << "|"
                << quarto.getRamal().getValor() << "|"
                << (quarto.getHotel() ? quarto.getHotel()->getCodigo().getValor() : "N/A") << std::endl;
    }
    arquivo.close();
    return true;
}


// Hóspede
// Constructor with dependency injection
ContainerHospede::ContainerHospede(std::string nomeArquivo, IServicoReserva* sReserva) :
    nomeArquivo(nomeArquivo), servicoReserva(sReserva) {
    carregar(); // Load data from file when constructed
}

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

bool ContainerHospede::carregar() {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        return false;
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        std::stringstream ss(linha);
        std::string emailStr, nomeStr, enderecoStr, cartaoStr;

        std::getline(ss, emailStr, '|');
        std::getline(ss, nomeStr, '|');
        std::getline(ss, enderecoStr, '|');
        std::getline(ss, cartaoStr, '|');

        try {
            Email email;
            email.setValor(emailStr);
            Nome nome;
            nome.setValor(nomeStr);
            Endereco endereco;
            endereco.setValor(enderecoStr);
            Cartao cartao;
            cartao.setValor(cartaoStr);

            dbHospedes.push_back(Hospede(nome, email, endereco, cartao));
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro ao carregar Hóspede: " << e.what() << " - Linha ignorada: " << linha << std::endl;
        }
    }
    arquivo.close();
    return true;
}

bool ContainerHospede::salvar() {
    std::ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        return false;
    }

    for (const auto& hospede : dbHospedes) {
        arquivo << hospede.getEmail().getValor() << "|"
                << hospede.getNome().getValor() << "|"
                << hospede.getEndereco().getValor() << "|"
                << hospede.getCartao().getValor() << std::endl;
    }
    arquivo.close();
    return true;
}


// Reserva
ContainerReserva::ContainerReserva(std::string nomeArquivo) : nomeArquivo(nomeArquivo) {
    carregar(); // Load data from file when constructed
}

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

bool ContainerReserva::carregar() {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        return false;
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        std::stringstream ss(linha);
        std::string codigoStr, dataChegadaStr, dataPartidaStr, valorStr, emailHospedeStr, numeroQuartoStr, codigoHotelStr;

        std::getline(ss, codigoStr, '|');
        std::getline(ss, dataChegadaStr, '|');
        std::getline(ss, dataPartidaStr, '|');
        std::getline(ss, valorStr, '|');
        std::getline(ss, emailHospedeStr, '|');
        std::getline(ss, numeroQuartoStr, '|');
        std::getline(ss, codigoHotelStr, '|');

        try {
            Codigo codigo;
            codigo.setValor(codigoStr);
            Data dataChegada;
            dataChegada.setValor(dataChegadaStr);
            Data dataPartida;
            dataPartida.setValor(dataPartidaStr);
            Dinheiro valor;
            valor.setValor(std::stoi(valorStr));

            // Reconstruir Reserva. Hospede e Quarto são ponteiros.
            // Isso exigiria que os serviços de Hospede e Quarto estivessem injetados aqui
            // para buscar as entidades por seus identificadores.
            // Por simplicidade, criamos a Reserva com ponteiros nulos e a associação real
            // seria feita em um passo posterior ou exigiria refatorar a injeção de dependência.
            Reserva reserva(dataChegada, dataPartida, valor, codigo);
            // reserva.setHospede(servicoHospede->buscarHospede(emailHospedeStr));
            // reserva.setQuarto(servicoQuarto->buscarQuarto(codigoHotelStr, numeroQuartoStr));
            dbReservas.push_back(reserva);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro ao carregar Reserva: " << e.what() << " - Linha ignorada: " << linha << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Erro de número ao carregar Reserva: " << e.what() << " - Linha ignorada: " << linha << std::endl;
        }
    }
    arquivo.close();
    return true;
}

bool ContainerReserva::salvar() {
    std::ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        return false;
    }

    for (const auto& reserva : dbReservas) {
        arquivo << reserva.getCodigo().getValor() << "|"
                << reserva.getDataChegada().getValor() << "|"
                << reserva.getDataPartida().getValor() << "|"
                << std::to_string(reserva.getValor().getValor()) << "|"
                << (reserva.getHospede() ? reserva.getHospede()->getEmail().getValor() : "N/A") << "|"
                << (reserva.getQuarto() ? reserva.getQuarto()->getNumero().getValor() : "N/A") << "|"
                << (reserva.getQuarto() && reserva.getQuarto()->getHotel() ? reserva.getQuarto()->getHotel()->getCodigo().getValor() : "N/A") << std::endl;
    }
    arquivo.close();
    return true;
}
