#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>
#include "controladoras.hpp"

// FUNÇÕES AUXILIARES
static int converterStringParaInt(const std::string& s) {
    int resultado = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];
        if (!isdigit(c)) {
            throw std::invalid_argument("Deve conter apenas digitos.");
        }
        resultado = resultado * 10 + (c - '0');
    }
    return resultado;
}

int converterMoedaParaCentavos(const std::string& s) {
    int parteInteira = 0;
    int parteDecimal = 0;
    bool achouPonto = false;
    int casasDecimais = 0;

    for (char c : s) {
        if (c == '.' || c == ',') {
            if (achouPonto) throw std::invalid_argument("Formato invalido.");
            achouPonto = true;
            continue;
        }
        if (!isdigit(c)) throw std::invalid_argument("Apenas digitos e ponto.");

        if (!achouPonto) {
            parteInteira = parteInteira * 10 + (c - '0');
        } else {
            parteDecimal = parteDecimal * 10 + (c - '0');
            casasDecimais++;
        }
    }
    
    if (casasDecimais > 2) throw std::invalid_argument("Maximo 2 casas decimais.");
    if (casasDecimais == 1) parteDecimal *= 10; 

    return (parteInteira * 100) + parteDecimal;
}

int mesParaInt(const std::string& mes) {
    const char* meses[] = {"JAN", "FEV", "MAR", "ABR", "MAI", "JUN", 
                           "JUL", "AGO", "SET", "OUT", "NOV", "DEZ"};
    for(int i=0; i<12; i++) {
        if(mes == meses[i]) return i+1;
    }
    return 0; 
}

long calcularDiasAbsolutos(const std::string& dataStr) {
    int dia = (dataStr[0]-'0')*10 + (dataStr[1]-'0');
    std::string mesStr = dataStr.substr(3, 3);
    int mes = mesParaInt(mesStr);
    int ano = (dataStr[7]-'0')*1000 + (dataStr[8]-'0')*100 + 
              (dataStr[9]-'0')*10 + (dataStr[10]-'0');
    return (long)ano * 360 + mes * 30 + dia;
}

// Gerente
// Criar gerente
void CntrApresentacaoGerente::criarConta() {
    std::cout << "\nCriar Conta de Gerente\n";
    std::string entrada;

    Nome nome;
    Email email;
    Senha senha;
    Ramal ramal;

    // Nome
    while (true) {
        try {
            std::cout << "Nome: ";
            std::getline(std::cin >> std::ws, entrada);
            nome.setValor(entrada);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\nRegra: 5-20 chars, iniciais maiusculas.\n";
        }
    }

    // E-mail
    while (true) {
        try {
            std::cout << "Email: ";
            std::getline(std::cin, entrada);
            email.setValor(entrada);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\n";
        }
    }

    // Senha
    while (true) {
        try {
            std::cout << "Senha: ";
            std::getline(std::cin, entrada);
            senha.setValor(entrada);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\nRegra: 5 chars (Maiusc, Minusc, Digito, Especial).\n";
        }
    }

    // Ramal
    while (true) {
        try {
            std::cout << "Ramal (00-50): ";
            std::getline(std::cin, entrada);
            ramal.setValor(entrada);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\n";
        }
    }

    Gerente novoGerente(nome, email, senha, ramal);

    // MUDANÇA: Usando this->servicoGerente
    if (this->servicoGerente->criarGerente(novoGerente)) {
        std::cout << "\nConta criada com sucesso! Você já pode fazer login.\n";
    } else {
        std::cerr << "Erro: Este e-mail já esta cadastrado no sistema.\n";
    }
}

// Autenticação
Gerente* CntrApresentacaoGerente::autenticar() {
    std::string email, senha;
    std::cout << "\n--- LOGIN ---\n";
    std::cout << "Email: "; std::cin >> email;
    std::cout << "Senha: "; std::cin >> senha;
    
    // Chama o serviço
    Gerente* g = this->servicoGerente->autenticar(email, senha);
    if (g) {
        return g;
    } else {
        std::cout << "Falha: Email ou senha incorretos.\n";
        return nullptr;
    }
}

// Stubs (Vazios para compilar)
void CntrApresentacaoGerente::editarConta(Gerente* gerente) { std::cout << "[Em desenvolvimento...]\n"; }
void CntrApresentacaoGerente::excluirConta(Gerente* gerente) { std::cout << "[Em desenvolvimento...]\n"; }


// Hotel
//Criar hotel
void CntrApresentacaoHotel::criarHotel(Gerente* gerenteLogado) {
    std::string entrada;
    Nome nome;
    Endereco endereco;
    Telefone telefone;
    Codigo codigo;

    std::cout << "\nCriar Hotel\n";

    // NOME
    while (true) {
        try {
            std::cout << "Nome do hotel: ";
            std::getline(std::cin >> std::ws, entrada);
            nome.setValor(entrada); 
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\nTente novamente.\n";
        }
    }

    // ENDEREÇO
    while (true) {
        try {
            std::cout << "Endereço: ";
            std::getline(std::cin, entrada);
            endereco.setValor(entrada);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\nTente novamente.\n";
        }
    }

    // TELEFONE
    while (true) {
        try {
            std::cout << "Telefone (+DDDDNXXXXXXXX): ";
            std::getline(std::cin, entrada);
            telefone.setValor(entrada);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\nTente novamente.\n";
        }
    }

    // CÓDIGO
    while (true) {
        try {
            std::cout << "Código (10 caracteres alfanuméricos): ";
            std::getline(std::cin, entrada);
            codigo.setValor(entrada);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\nTente novamente.\n";
        }
    }

    Hotel novoHotel(nome, endereco, telefone, codigo);
    novoHotel.setGerente(gerenteLogado);

    // MUDANÇA: Usando this->servicoHotel
    this->servicoHotel->criarHotel(novoHotel); 
    
    std::cout << "\nHotel '" << novoHotel.getNome().getValor() << "' criado com sucesso!\n";
}

//Listar hoteis
void CntrApresentacaoHotel::listarHoteis() {
    std::cout << "\n--- LISTA DE HOTEIS ---\n";
    std::vector<Hotel> lista = this->servicoHotel->listarHoteis();

    if (lista.empty()) {
        std::cout << "Nenhum hotel cadastrado.\n";
    } else {
        for (const auto& h : lista) {
            std::cout << "Cod: " << h.getCodigo().getValor() 
                      << " | Nome: " << h.getNome().getValor() << "\n";
        }
    }
}

// Stubs
void CntrApresentacaoHotel::editar(Gerente* gerenteLogado) { std::cout << "[Em desenvolvimento...]\n"; }
void CntrApresentacaoHotel::excluir(Gerente* gerenteLogado) { std::cout << "[Em desenvolvimento...]\n"; }


// Quartos
//Criar quarto
void CntrApresentacaoQuarto::criarQuarto() {
    std::cout << "\nCriar Quarto\n";
    std::string entrada;
    
    // Associar ao hotel
    Hotel* hotelPai = nullptr;
    while (true) {
        std::cout << "Informe o código do Hotel deste quarto: ";
        std::getline(std::cin >> std::ws, entrada);
        
        // MUDANÇA: this->servicoHotel
        hotelPai = this->servicoHotel->buscarHotel(entrada);
        if (hotelPai) break;
        
        std::cerr << "Erro: Hotel nao encontrado.\n";

        std::cout << "\nHoteis Disponíveis\n";
        std::vector<Hotel> lista = this->servicoHotel->listarHoteis();
        
        if (lista.empty()) {
            std::cout << "Nenhum hotel cadastrado. Impossível criar quarto.\n";
            return;
        }

        for (size_t i = 0; i < lista.size(); ++i) {
            std::cout << " - Codigo: " << lista[i].getCodigo().getValor() 
                      << " | Nome: " << lista[i].getNome().getValor() << "\n";
        }
        std::cout << "\nTente novamente abaixo:\n";
    }

    Numero numero;
    Capacidade capacidade;
    Dinheiro diaria;
    Ramal ramal;
    
    // Numero
    while (true) {
        try {
            std::cout << "Numero do quarto (001-999): ";
            std::getline(std::cin, entrada);
            numero.setValor(entrada);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\n";
        }
    }

    // Capacidade
    while (true) {
        try {
            std::cout << "Capacidade (1-4): ";
            std::getline(std::cin, entrada);
            int valorCap = converterStringParaInt(entrada);
            capacidade.setValor(valorCap);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\n";
        }
    }

    // Diária
    while (true) {
        try {
            std::cout << "Diaria (Ex.: 152.99): ";
            std::getline(std::cin, entrada);
            int centavos = converterMoedaParaCentavos(entrada);
            diaria.setValor(centavos);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\n";
        }
    }

    // Ramal
    while (true) {
        try {
            std::cout << "Ramal (00-50): ";
            std::getline(std::cin, entrada);
            ramal.setValor(entrada);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\n";
        }
    }

    Quarto novoQuarto(numero, capacidade, diaria, ramal, hotelPai);
    
    // MUDANÇA: this->servicoQuarto
    if (this->servicoQuarto->criarQuarto(novoQuarto)) {
        std::cout << "\nQuarto criado com sucesso!\n";
    } else {
        std::cerr << "Erro: Quarto ja existe neste hotel.\n";
    }
}

// Listar quartos
void CntrApresentacaoQuarto::listarQuartos() {
    std::vector<Quarto> lista = this->servicoQuarto->listarQuartos();
    std::cout << "\n--- LISTA DE QUARTOS ---\n";
    for(const auto& q : lista) {
        std::cout << "Hotel: " << q.getHotel()->getNome().getValor() 
                  << " | Quarto: " << q.getNumero().getValor() << "\n";
    }
}

// Stubs
void CntrApresentacaoQuarto::editarQuarto() { std::cout << "[Em desenvolvimento...]\n"; }
void CntrApresentacaoQuarto::excluirQuarto() { std::cout << "[Em desenvolvimento...]\n"; }


// Hóspedes
//Criar hóspede
void CntrApresentacaoHospede::criarHospede() {
    std::string entrada;
    std::cout << "\nCriar Hospede" << std::endl;

    Nome nome;
    Email email;
    Endereco endereco;
    Cartao cartao;

    // Nome
    while (true) {
        try {
            std::cout << "Nome do hospede: ";
            std::getline(std::cin >> std::ws, entrada);
            nome.setValor(entrada);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\nRegra: 5 a 20 caracteres, apenas letras/espacos, iniciais maiúsculas.\n";
        }
    }

    // Email
    while (true) {
        try {
            std::cout << "Email: ";
            std::getline(std::cin, entrada);
            email.setValor(entrada);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\n";
        }
    }

    // Endereço
    while (true) {
        try {
            std::cout << "Endereço: ";
            std::getline(std::cin, entrada);
            endereco.setValor(entrada);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\nRegra: 5-30 chars.\n";
        }
    }

    // Cartão
    while (true) {
        try {
            std::cout << "Cartão de Crédito (16 dígitos): ";
            std::getline(std::cin, entrada);
            cartao.setValor(entrada);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\nRegra: Luhn e 16 digitos.\n";
        }
    }

    Hospede novoHospede(nome, email, endereco, cartao);
    
    // MUDANÇA: this->servicoHospede
    if (this->servicoHospede->criarHospede(novoHospede)) {
        std::cout << "\nHospede '" << novoHospede.getNome().getValor() << "' cadastrado com sucesso!\n";
    } else {
        std::cerr << "Erro: Hóspede já cadastrado (email duplicado).\n";
    }
}

// Listar Hóspedes
void CntrApresentacaoHospede::listarHospedes() {
    std::vector<Hospede> lista = this->servicoHospede->listarHospedes();
    std::cout << "\n--- LISTA DE HÓSPEDES ---\n";
    for(const auto& h : lista) {
        std::cout << "Email: " << h.getEmail().getValor() 
                  << " | Nome: " << h.getNome().getValor() << "\n";
    }
}

// Stubs
void CntrApresentacaoHospede::editarHospedde() { std::cout << "[Em desenvolvimento...]\n"; }
void CntrApresentacaoHospede::excluirHospede() { std::cout << "[Em desenvolvimento...]\n"; }


// Reserva
// Criar reserva

void CntrApresentacaoReserva::criarReserva() {
    std::cout << "\nCriar Reserva\n";
    std::string entrada;

    // Seleção do hotel
    Hotel* hotelSelecionado = nullptr;
    while (true) {
        std::cout << "Informe o código do Hotel: ";
        std::getline(std::cin >> std::ws, entrada);
        
        // MUDANÇA: this->servicoHotel
        hotelSelecionado = this->servicoHotel->buscarHotel(entrada);
        if (hotelSelecionado) break;

        std::cerr << "Hotel não encontrado. Hotéis disponíveis:\n";
        std::vector<Hotel> listaH = this->servicoHotel->listarHoteis();
        if (listaH.empty()) { std::cout << "Nenhum hotel cadastrado.\n"; return; }
        
        for(size_t i = 0; i < listaH.size(); ++i) 
            std::cout << " - " << listaH[i].getCodigo().getValor() << "\n";
    }

    // Seleção do hóspede
    Hospede* hospedeSelecionado = nullptr;
    while (true) {
        std::cout << "Informe o e-mail do Hóspede: ";
        std::getline(std::cin, entrada);

        // MUDANÇA: this->servicoHospede
        hospedeSelecionado = this->servicoHospede->buscarHospede(entrada);
        if (hospedeSelecionado) break;

        std::cerr << "Hospede nao encontrado.\n";
    }

    // Datas
    Data dataChegada;
    Data dataPartida;
    long diasDif = 0;
    long absChegada = 0;
    long absPartida = 0;

    while (true) {
        try {
            std::cout << "Data Chegada (DD-MMM-AAAA): ";
            std::getline(std::cin, entrada);
            dataChegada.setValor(entrada);
            absChegada = calcularDiasAbsolutos(dataChegada.getValor());

            std::cout << "Data Partida (DD-MMM-AAAA): ";
            std::getline(std::cin, entrada);
            dataPartida.setValor(entrada);
            absPartida = calcularDiasAbsolutos(dataPartida.getValor());

            if (absPartida <= absChegada) {
                std::cerr << "Erro: Data de partida deve ser posterior a chegada.\n";
                continue;
            }

            diasDif = absPartida - absChegada;
            break;

        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro de formato: " << e.what() << "\n";
        }
    }

    // Seleção de quarto
    Quarto* quartoSelecionado = nullptr;
    
    while (true) {
        std::cout << "Informe o número do Quarto: ";
        std::getline(std::cin, entrada);

        // MUDANÇA: this->servicoQuarto
        std::vector<Quarto> todosQuartos = this->servicoQuarto->listarQuartos();
        bool quartoExisteNoHotel = false;

        for (size_t i = 0; i < todosQuartos.size(); ++i) {
            if (todosQuartos[i].getHotel()->getCodigo().getValor() == hotelSelecionado->getCodigo().getValor() &&
                todosQuartos[i].getNumero().getValor() == entrada) {
                
                quartoExisteNoHotel = true;

                // Verificação de conflitos de datas
                bool conflitoDetectado = false;
                // MUDANÇA: this->servicoReserva
                std::vector<Reserva> todasReservas = this->servicoReserva->listarReservas();

                for (size_t j = 0; j < todasReservas.size(); ++j) {
                    Reserva r = todasReservas[j];
                    if (r.getQuarto()->getHotel()->getCodigo().getValor() == hotelSelecionado->getCodigo().getValor() &&
                        r.getQuarto()->getNumero().getValor() == entrada) {
                        
                        long rInicio = calcularDiasAbsolutos(r.getDataChegada().getValor());
                        long rFim = calcularDiasAbsolutos(r.getDataPartida().getValor());

                        if (absChegada < rFim && absPartida > rInicio) {
                            conflitoDetectado = true;
                            break; 
                        }
                    }
                }

                if (conflitoDetectado) {
                    std::cerr << "ERRO: Quarto indisponível neste período.\n";
                } else {
                    quartoSelecionado = new Quarto(todosQuartos[i]);
                }
                break;
            }
        }

        if (quartoSelecionado) break;
        if (!quartoExisteNoHotel) {
            std::cerr << "Quarto não encontrado neste hotel. Tente novamente.\n";
        }
    }

    // Cálculo do valor
    int diariaCentavos = quartoSelecionado->getDiaria().getValor();
    long totalCentavosLong = diariaCentavos * diasDif; 
    
    if (totalCentavosLong > 100000000) { 
        std::cerr << "Erro: Valor total excede o limite permitido pelo sistema.\n";
        return;
    }

    Dinheiro valorTotal;
    try {
        valorTotal.setValor((int)totalCentavosLong);
    } catch (std::exception& e) {
        std::cerr << "Erro interno valor: " << e.what() << "\n";
        return;
    }

    Codigo codigo;
    while(true) {
        try {
            std::cout << "Código da Reserva (10 alphanum): ";
            std::getline(std::cin, entrada);
            codigo.setValor(entrada);
            break;
        } catch (std::exception& e) {
            std::cerr << "Erro: " << e.what() << "\n";
        }
    }

    Reserva novaReserva(dataChegada, dataPartida, valorTotal, codigo);
    novaReserva.setHospede(hospedeSelecionado);
    novaReserva.setQuarto(quartoSelecionado);

    // MUDANÇA: this->servicoReserva
    if (this->servicoReserva->criarReserva(novaReserva)) {
        std::cout << "\nReserva criada com sucesso!\n";
    } else {
        std::cerr << "Erro: Código de reserva duplicado.\n";
    }
}

// Listar Reservas
void CntrApresentacaoReserva::listarReservas() {
    std::vector<Reserva> lista = this->servicoReserva->listarReservas();
    std::cout << "\nLISTA DE RESERVAS\n";
    for(const auto& r : lista) {
        std::cout << "Cod: " << r.getCodigo().getValor() 
                  << " | Hospede: " << r.getHospede()->getNome().getValor() 
                  << " | Quarto: " << r.getQuarto()->getNumero().getValor() << "\n";
    }
}

// Stubs
void CntrApresentacaoReserva::editarReserva() { std::cout << "[Em desenvolvimento...]\n"; }
void CntrApresentacaoReserva::excluirReserva() { std::cout << "[Em desenvolvimento...]\n"; }