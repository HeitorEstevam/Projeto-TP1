#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>
#include <vector> 
#include <algorithm>
#include "controladoras.hpp"

// FUNCOES AUXILIARES
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

    // MUDANCA: Usando this->servicoGerente
    if (this->servicoGerente->criarGerente(novoGerente)) {
        std::cout << "\nConta criada com sucesso! Voce ja pode fazer login.\n";
    } else {
        std::cerr << "Erro: Este e-mail ja esta cadastrado no sistema.\n";
    }
}

// Autenticacao
Gerente* CntrApresentacaoGerente::autenticar() {
    std::string email, senha;
    std::cout << "\nLOGIN\n";
    std::cout << "Email: "; std::cin >> email;
    std::cout << "Senha: "; std::cin >> senha;
    
    // Chama o servico
    Gerente* g = this->servicoGerente->autenticar(email, senha);
    if (g) {
        return g;
    } else {
        std::cout << "Falha: Email ou senha incorretos.\n";
        return nullptr;
    }
}

// Stubs (Vazios para compilar)
void CntrApresentacaoGerente::editarConta(Gerente* gerenteLogado) {
    std::cout << "\n--- EDITAR CONTA DE GERENTE ---\n";
    std::string entrada;
    
    Nome novoNome;
    Email novoEmail;
    Senha novaSenha;
    Ramal novoRamal;

    // Novo Nome
    while (true) {
        try {
            std::cout << "Novo Nome (atual: " << gerenteLogado->getNome().getValor() << "): ";
            std::getline(std::cin >> std::ws, entrada);
            if (entrada.empty()) { // Permite manter o valor atual
                novoNome = gerenteLogado->getNome();
                break;
            }
            novoNome.setValor(entrada);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\nRegra: 5-20 chars, iniciais maiusculas.\n";
        }
    }

    // Novo E-mail (chave primaria, nao editavel diretamente)
    // Requisito: Nao e possivel editar dado que identifica registro (chave primaria)
    std::cout << "Email (nao editavel): " << gerenteLogado->getEmail().getValor() << "\n";
    novoEmail = gerenteLogado->getEmail();


    // Nova Senha
    while (true) {
        try {
            std::cout << "Nova Senha (atual: " << gerenteLogado->getSenha().getValor() << "): ";
            std::getline(std::cin, entrada);
            if (entrada.empty()) { // Permite manter o valor atual
                novaSenha = gerenteLogado->getSenha();
                break;
            }
            novaSenha.setValor(entrada);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\nRegra: 5 chars (Maiusc, Minusc, Digito, Especial).\n";
        }
    }

    // Novo Ramal
    while (true) {
        try {
            std::cout << "Novo Ramal (atual: " << gerenteLogado->getRamal().getValor() << "): ";
            std::getline(std::cin, entrada);
            if (entrada.empty()) { // Permite manter o valor atual
                novoRamal = gerenteLogado->getRamal();
                break;
            }
            novoRamal.setValor(entrada);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\n";
        }
    }

    Gerente gerenteAtualizado(novoNome, novoEmail, novaSenha, novoRamal);

    if (this->servicoGerente->editarGerente(gerenteAtualizado)) {
        // Atualiza o objeto logado para refletir as mudancas
        gerenteLogado->setNome(novoNome);
        gerenteLogado->setSenha(novaSenha);
        gerenteLogado->setRamal(novoRamal);
        std::cout << "\nConta atualizada com sucesso!\n";
    } else {
        std::cerr << "Erro ao atualizar conta.\n";
    }
}

void CntrApresentacaoGerente::excluirConta(Gerente*& gerenteLogado) { // Corrected signature
    std::cout << "\n--- EXCLUIR CONTA DE GERENTE ---\n";
    std::string confirmacao;
    std::cout << "Tem certeza que deseja excluir sua conta (" << gerenteLogado->getEmail().getValor() << ")? (s/n): ";
    std::cin >> confirmacao;

    if (confirmacao == "s" || confirmacao == "S") {
        if (this->servicoGerente->excluirGerente(gerenteLogado->getEmail().getValor())) {
            std::cout << "\nConta excluida com sucesso!\n";
            gerenteLogado = nullptr; // Forca logout apos exclusao
        } else {
            std::cerr << "Erro ao excluir conta.\n";
        }
    } else {
        std::cout << "Exclusao cancelada.\n";
    }
}


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

    // ENDERECO
    while (true) {
        try {
            std::cout << "Endereco: ";
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

    // CODIGO
    while (true) {
        try {
            std::cout << "Codigo (10 caracteres alfanumericos): ";
            std::getline(std::cin, entrada);
            codigo.setValor(entrada);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\nTente novamente.\n";
        }
    }

    Hotel novoHotel(nome, endereco, telefone, codigo);
    novoHotel.setGerente(gerenteLogado);

    // MUDANCA: Usando this->servicoHotel
    this->servicoHotel->criarHotel(novoHotel); 
    
    std::cout << "\nHotel '" << novoHotel.getNome().getValor() << "' criado com sucesso!\n";
}

//Listar hoteis
void CntrApresentacaoHotel::listarHoteis(Gerente* gerenteLogado) { // MODIFIED
    std::cout << "\nLISTA DE HOTEIS\n";
    std::vector<Hotel> listaCompleta = this->servicoHotel->listarHoteis();
    std::vector<Hotel> listaFiltrada;

    for (const auto& h : listaCompleta) {
        if (h.getGerente() != nullptr && h.getGerente()->getEmail().getValor() == gerenteLogado->getEmail().getValor()) {
            listaFiltrada.push_back(h);
        }
    }

    if (listaFiltrada.empty()) {
        std::cout << "Nenhum hotel cadastrado por voce.\n";
    } else {
        for (const auto& h : listaFiltrada) {
            std::cout << "Cod: " << h.getCodigo().getValor() 
                      << " | Nome: " << h.getNome().getValor() << "\n";
        }
    }
}

// Stubs
void CntrApresentacaoHotel::editar(Gerente* gerenteLogado) {
    std::cout << "\n--- EDITAR HOTEL ---\n";
    std::string codigoHotel;
    std::string entrada;

    std::vector<Hotel> listaHoteisDoGerente = this->servicoHotel->listarHoteis(); // Get all to filter
    // Filter to only show manager's hotels for editing
    listaHoteisDoGerente.erase(std::remove_if(listaHoteisDoGerente.begin(), listaHoteisDoGerente.end(), 
                                              [gerenteLogado](const Hotel& h){
                                                  return h.getGerente() == nullptr || h.getGerente()->getEmail().getValor() != gerenteLogado->getEmail().getValor();
                                              }), 
                               listaHoteisDoGerente.end());

    if (listaHoteisDoGerente.empty()) {
        std::cout << "Nenhum hotel cadastrado por voce para editar.\n";
        return;
    }

    // Mostrar apenas os hoteis do gerente logado
    std::cout << "\nSeus Hoteis Disponiveis para Edicao:\n";
    for (const auto& h : listaHoteisDoGerente) {
        std::cout << "Cod: " << h.getCodigo().getValor() 
                  << " | Nome: " << h.getNome().getValor() << "\n";
    }

    std::cout << "\nInforme o Codigo do Hotel a ser editado (ou 0 para cancelar): ";
    std::getline(std::cin >> std::ws, codigoHotel);

    if (codigoHotel == "0") {
        std::cout << "Edicao cancelada.\n";
        return;
    }

    Hotel* hotelExistente = this->servicoHotel->buscarHotel(codigoHotel);
    if (!hotelExistente || hotelExistente->getGerente() == nullptr || hotelExistente->getGerente()->getEmail().getValor() != gerenteLogado->getEmail().getValor()) { // Ownership check
        std::cerr << "Erro: Hotel com codigo " << codigoHotel << " nao encontrado ou nao pertence a voce.\n";
        return;
    }

    Nome novoNome = hotelExistente->getNome();
    Endereco novoEndereco = hotelExistente->getEndereco();
    Telefone novoTelefone = hotelExistente->getTelefone();
    Codigo codigoOriginal = hotelExistente->getCodigo(); // Codigo nao e editavel

    // Edita Nome
    while (true) {
        try {
            std::cout << "Novo Nome (atual: " << hotelExistente->getNome().getValor() << ", Enter para manter): ";
            std::getline(std::cin, entrada);
            if (entrada.empty()) break;
            novoNome.setValor(entrada);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\n";
        }
    }

    // Edita Endereco
    while (true) {
        try {
            std::cout << "Novo Endereco (atual: " << hotelExistente->getEndereco().getValor() << ", Enter para manter): ";
            std::getline(std::cin, entrada);
            if (entrada.empty()) break;
            novoEndereco.setValor(entrada);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\n";
        }
    }

    // Edita Telefone
    while (true) {
        try {
            std::cout << "Novo Telefone (atual: " << hotelExistente->getTelefone().getValor() << ", Enter para manter): ";
            std::getline(std::cin, entrada);
            if (entrada.empty()) break;
            novoTelefone.setValor(entrada);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\n";
        }
    }

    Hotel hotelAtualizado(novoNome, novoEndereco, novoTelefone, codigoOriginal);
    hotelAtualizado.setGerente(gerenteLogado); // Mantem o mesmo gerente

    if (this->servicoHotel->editarHotel(hotelAtualizado)) {
        std::cout << "\nHotel atualizado com sucesso!\n";
    } else {
        std::cerr << "Erro ao atualizar hotel.\n";
    }
}

void CntrApresentacaoHotel::excluir(Gerente* gerenteLogado) {
    std::cout << "\n--- EXCLUIR HOTEL ---\n";
    std::string codigoHotel;
    std::string confirmacao;

    std::vector<Hotel> listaHoteisDoGerente = this->servicoHotel->listarHoteis(); // Get all to filter
    // Filter to only show manager's hotels for deleting
    listaHoteisDoGerente.erase(std::remove_if(listaHoteisDoGerente.begin(), listaHoteisDoGerente.end(), 
                                              [gerenteLogado](const Hotel& h){
                                                  return h.getGerente() == nullptr || h.getGerente()->getEmail().getValor() != gerenteLogado->getEmail().getValor();
                                              }), 
                               listaHoteisDoGerente.end());

    if (listaHoteisDoGerente.empty()) {
        std::cout << "Nenhum hotel cadastrado por voce para excluir.\n";
        return;
    }

    // Mostrar apenas os hoteis do gerente logado
    std::cout << "\nSeus Hoteis Disponiveis para Exclusao:\n";
    for (const auto& h : listaHoteisDoGerente) {
        std::cout << "Cod: " << h.getCodigo().getValor() 
                  << " | Nome: " << h.getNome().getValor() << "\n";
    }

    std::cout << "\nInforme o Codigo do Hotel a ser excluido (ou 0 para cancelar): ";
    std::getline(std::cin >> std::ws, codigoHotel);

    if (codigoHotel == "0") {
        std::cout << "Exclusao cancelada.\n";
        return;
    }

    Hotel* hotelExistente = this->servicoHotel->buscarHotel(codigoHotel);
    if (!hotelExistente || hotelExistente->getGerente() == nullptr || hotelExistente->getGerente()->getEmail().getValor() != gerenteLogado->getEmail().getValor()) { // Ownership check
        std::cerr << "Erro: Hotel com codigo " << codigoHotel << " nao encontrado ou nao pertence a voce.\n";
        return;
    }
    
    std::cout << "Tem certeza que deseja excluir o hotel '" << hotelExistente->getNome().getValor() << "' (" << codigoHotel << ")? (s/n): ";
    std::cin >> confirmacao;

    if (confirmacao == "s" || confirmacao == "S") {
        if (this->servicoHotel->excluirHotel(codigoHotel)) {
            std::cout << "\nHotel excluido com sucesso!\n";
        } else {
            std::cerr << "Erro ao excluir hotel.\n";
        }
    } else {
        std::cout << "Exclusao cancelada.\n";
    }
}


// Quartos
//Criar quarto
void CntrApresentacaoQuarto::criarQuarto(Gerente* gerenteLogado) { // MODIFIED
    std::cout << "\nCriar Quarto\n";
    std::string entrada;
    
    // Associar ao hotel
    Hotel* hotelPai = nullptr;
    while (true) {
        std::cout << "Informe o codigo do Hotel deste quarto: ";
        std::getline(std::cin >> std::ws, entrada);
        
        hotelPai = this->servicoHotel->buscarHotel(entrada);
        if (hotelPai) {
            // Check ownership
            if (hotelPai->getGerente() == nullptr || hotelPai->getGerente()->getEmail().getValor() != gerenteLogado->getEmail().getValor()) {
                std::cerr << "Erro: Hotel com codigo " << entrada << " nao pertence a voce. Impossivel criar quarto nele.\n";
                // Show available hotels if owned by manager.
                std::vector<Hotel> listaH = this->servicoHotel->listarHoteis();
                std::vector<Hotel> listaFiltradaH;
                for (const auto& h : listaH) {
                    if (h.getGerente() != nullptr && h.getGerente()->getEmail().getValor() == gerenteLogado->getEmail().getValor()) {
                        listaFiltradaH.push_back(h);
                    }
                }
                if (listaFiltradaH.empty()) {
                    std::cout << "Nenhum hotel cadastrado por voce. Impossivel criar quarto.\n";
                    return;
                }
                std::cout << "\nSeus Hoteis Disponiveis:\n";
                for (size_t i = 0; i < listaFiltradaH.size(); ++i) {
                    std::cout << " - Codigo: " << listaFiltradaH[i].getCodigo().getValor() 
                              << " | Nome: " << listaFiltradaH[i].getNome().getValor() << "\n";
                }
                std::cout << "\nTente novamente abaixo:\n";
                continue; // Ask for hotel code again
            }
            break; // Hotel found and owned by manager
        }
        
        std::cerr << "Erro: Hotel nao encontrado.\n";

        std::cout << "\nHoteis Disponiveis\n";
        std::vector<Hotel> lista = this->servicoHotel->listarHoteis();
        
        if (lista.empty()) {
            std::cout << "Nenhum hotel cadastrado. Impossivel criar quarto.\n";
            return;
        }
        
        std::cout << "\nSeus Hoteis Disponiveis:\n";
        for (size_t i = 0; i < lista.size(); ++i) {
            // Filter list to show only hotels owned by the manager
            if (lista[i].getGerente() != nullptr && lista[i].getGerente()->getEmail().getValor() == gerenteLogado->getEmail().getValor()) {
                std::cout << " - Codigo: " << lista[i].getCodigo().getValor() 
                          << " | Nome: " << lista[i].getNome().getValor() << "\n";
            }
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

    // Diaria
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
    
    if (this->servicoQuarto->criarQuarto(novoQuarto)) {
        std::cout << "\nQuarto criado com sucesso!\n";
    } else {
        std::cerr << "Erro: Quarto ja existe neste hotel.\n";
    }
}

// Listar quartos
void CntrApresentacaoQuarto::listarQuartos(Gerente* gerenteLogado) { // MODIFIED
    std::vector<Quarto> listaCompleta = this->servicoQuarto->listarQuartos();
    std::vector<Quarto> listaFiltrada;

    for(const auto& q : listaCompleta) {
        if (q.getHotel() != nullptr && q.getHotel()->getGerente() != nullptr && q.getHotel()->getGerente()->getEmail().getValor() == gerenteLogado->getEmail().getValor()) {
            listaFiltrada.push_back(q);
        }
    }

    std::cout << "\nLISTA DE SEUS QUARTOS\n";
    if (listaFiltrada.empty()) {
        std::cout << "Nenhum quarto cadastrado por voce.\n";
    } else {
        for(const auto& q : listaFiltrada) {
            std::cout << "Hotel: " << q.getHotel()->getNome().getValor() 
                      << " | Quarto: " << q.getNumero().getValor() << "\n";
        }
    }
}

// Stubs
void CntrApresentacaoQuarto::editarQuarto(Gerente* gerenteLogado) { // MODIFIED
    std::cout << "\n--- EDITAR QUARTO ---\n";
    std::string codigoHotel, numeroQuartoStr;
    std::string entrada;

    std::vector<Quarto> listaQuartosDoGerente = this->servicoQuarto->listarQuartos();
    // Filter to only show manager's quartos for editing
    listaQuartosDoGerente.erase(std::remove_if(listaQuartosDoGerente.begin(), listaQuartosDoGerente.end(), 
                                                [gerenteLogado](const Quarto& q){
                                                    return q.getHotel() == nullptr || q.getHotel()->getGerente() == nullptr || q.getHotel()->getGerente()->getEmail().getValor() != gerenteLogado->getEmail().getValor();
                                                }), 
                                 listaQuartosDoGerente.end());

    if (listaQuartosDoGerente.empty()) {
        std::cout << "Nenhum quarto cadastrado por voce para editar.\n";
        return;
    }

    // Mostrar apenas os quartos do gerente logado
    std::cout << "\nSeus Quartos Disponiveis para Edicao:\n";
    for(const auto& q : listaQuartosDoGerente) {
        std::cout << "Hotel: " << q.getHotel()->getNome().getValor() 
                  << " | Quarto: " << q.getNumero().getValor() << "\n";
    }


    std::cout << "\nInforme o Codigo do Hotel ao qual o quarto pertence (ou 0 para cancelar): ";
    std::getline(std::cin >> std::ws, codigoHotel);

    if (codigoHotel == "0") {
        std::cout << "Edicao cancelada.\n";
        return;
    }

    std::cout << "Informe o Numero do Quarto a ser editado (ou 0 para cancelar): ";
    std::getline(std::cin, numeroQuartoStr);

    if (numeroQuartoStr == "0") {
        std::cout << "Edicao cancelada.\n";
        return;
    }

    std::vector<Quarto> todosQuartos = this->servicoQuarto->listarQuartos();
    Quarto* quartoExistente = nullptr;

    for (auto& q : todosQuartos) {
        if (q.getHotel()->getCodigo().getValor() == codigoHotel &&
            q.getNumero().getValor() == numeroQuartoStr) {
            quartoExistente = &q;
            break;
        }
    }

    if (!quartoExistente || quartoExistente->getHotel() == nullptr || quartoExistente->getHotel()->getGerente() == nullptr || quartoExistente->getHotel()->getGerente()->getEmail().getValor() != gerenteLogado->getEmail().getValor()) { // Ownership check
        std::cerr << "Erro: Quarto com numero " << numeroQuartoStr << " no hotel " << codigoHotel << " nao encontrado ou nao pertence a voce.\n";
        return;
    }

    // Copia os dados existentes para o objeto de edicao
    Numero novoNumero = quartoExistente->getNumero(); // Numero e chave, nao editavel
    Capacidade novaCapacidade = quartoExistente->getCapacidade();
    Dinheiro novaDiaria = quartoExistente->getDiaria();
    Ramal novoRamal = quartoExistente->getRamal();

    // Edita Capacidade
    while (true) {
        try {
            std::cout << "Nova Capacidade (atual: " << novaCapacidade.getValor() << ", Enter para manter): ";
            std::getline(std::cin, entrada);
            if (entrada.empty()) break;
            novaCapacidade.setValor(converterStringParaInt(entrada));
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\n";
        }
    }

    // Edita Diaria
    while (true) {
        try {
            std::cout << "Nova Diaria (atual: " << (static_cast<double>(novaDiaria.getValor()) / 100.0) << ", Ex.: 152.99, Enter para manter): ";
            std::getline(std::cin, entrada);
            if (entrada.empty()) break;
            novaDiaria.setValor(converterMoedaParaCentavos(entrada));
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\n";
        }
    }

    // Edita Ramal
    while (true) {
        try {
            std::cout << "Novo Ramal (atual: " << novoRamal.getValor() << ", Enter para manter): ";
            std::getline(std::cin, entrada);
            if (entrada.empty()) break;
            novoRamal.setValor(entrada);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\n";
        }
    }
    
    // Cria um novo objeto Quarto com os dados atualizados (mantendo a referencia ao hotel original)
    Quarto quartoAtualizado(novoNumero, novaCapacidade, novaDiaria, novoRamal, quartoExistente->getHotel());

    if (this->servicoQuarto->editarQuarto(quartoAtualizado)) {
        std::cout << "\nQuarto atualizado com sucesso!\n";
    } else {
        std::cerr << "Erro ao atualizar quarto.\n";
    }
}

void CntrApresentacaoQuarto::excluirQuarto(Gerente* gerenteLogado) { // MODIFIED
    std::string confirmacao;
    std::cout << "\n--- EXCLUIR QUARTO ---\n";
    std::string codigoHotel, numeroQuartoStr;
    std::string entrada;

    std::vector<Quarto> listaQuartosDoGerente = this->servicoQuarto->listarQuartos();
    // Filter to only show manager's quartos for deleting
    listaQuartosDoGerente.erase(std::remove_if(listaQuartosDoGerente.begin(), listaQuartosDoGerente.end(), 
                                                [gerenteLogado](const Quarto& q){
                                                    return q.getHotel() == nullptr || q.getHotel()->getGerente() == nullptr || q.getHotel()->getGerente()->getEmail().getValor() != gerenteLogado->getEmail().getValor();
                                                }), 
                                 listaQuartosDoGerente.end());

    if (listaQuartosDoGerente.empty()) {
        std::cout << "Nenhum quarto cadastrado por voce para excluir.\n";
        return;
    }

    // Mostrar apenas os quartos do gerente logado
    std::cout << "\nSeus Quartos Disponiveis para Exclusao:\n";
    for(const auto& q : listaQuartosDoGerente) {
        std::cout << "Hotel: " << q.getHotel()->getNome().getValor() 
                  << " | Quarto: " << q.getNumero().getValor() << "\n";
    }

    std::cout << "\nInforme o Codigo do Hotel ao qual o quarto pertence (ou 0 para cancelar): ";
    std::getline(std::cin >> std::ws, codigoHotel);

    if (codigoHotel == "0") {
        std::cout << "Exclusao cancelada.\n";
        return;
    }

    std::cout << "Informe o Numero do Quarto a ser excluido (ou 0 para cancelar): ";
    std::getline(std::cin, numeroQuartoStr);

    if (numeroQuartoStr == "0") {
        std::cout << "Exclusao cancelada.\n";
        return;
    }

    std::vector<Quarto> todosQuartos = this->servicoQuarto->listarQuartos();
    Quarto* quartoExistente = nullptr;

    for (auto& q : todosQuartos) {
        if (q.getHotel()->getCodigo().getValor() == codigoHotel &&
            q.getNumero().getValor() == numeroQuartoStr) {
            quartoExistente = &q;
            break;
        }
    }

    if (!quartoExistente || quartoExistente->getHotel() == nullptr || quartoExistente->getHotel()->getGerente() == nullptr || quartoExistente->getHotel()->getGerente()->getEmail().getValor() != gerenteLogado->getEmail().getValor()) { // Ownership check
        std::cerr << "Erro: Quarto com numero " << numeroQuartoStr << " no hotel " << codigoHotel << " nao encontrado ou nao pertence a voce.\n";
        return;
    }

    std::cout << "Tem certeza que deseja excluir o quarto " << numeroQuartoStr << " do hotel " << codigoHotel << "? (s/n): ";
    std::cin >> confirmacao;

    if (confirmacao == "s" || confirmacao == "S") {
        if (this->servicoQuarto->excluirQuarto(codigoHotel, numeroQuartoStr)) {
            std::cout << "\nQuarto excluido com sucesso!\n";
        } else {
            std::cerr << "Erro ao excluir quarto.\n";
        }
    } else {
        std::cout << "Exclusao cancelada.\n";
    }
}


// Hospedes
//Criar hospede
void CntrApresentacaoHospede::criarHospede() {
    std::cout << "\nCriar Hospede" << std::endl;
    std::string entrada;

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
            std::cerr << "Erro: " << e.what() << "\nRegra: 5 a 20 caracteres, apenas letras/espacos, iniciais maiusculas.\n";
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

    // Endereco
    while (true) {
        try {
            std::cout << "Endereco: ";
            std::getline(std::cin, entrada);
            endereco.setValor(entrada);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\nRegra: 5-30 chars.\n";
        }
    }

    // Cartao
    while (true) {
        try {
            std::cout << "Cartao de Credito (16 digitos): ";
            std::getline(std::cin, entrada);
            cartao.setValor(entrada);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\nRegra: Luhn e 16 digitos.\n";
        }
    }

    Hospede novoHospede(nome, email, endereco, cartao);
    
    // MUDANCA: this->servicoHospede
    if (this->servicoHospede->criarHospede(novoHospede)) {
        std::cout << "\nHospede '" << novoHospede.getNome().getValor() << "' cadastrado com sucesso!\n";
    } else {
        std::cerr << "Erro: Hospede ja cadastrado (email duplicado).\n";
    }
}

// Listar Hospedes
void CntrApresentacaoHospede::listarHospedes() {
    std::vector<Hospede> lista = this->servicoHospede->listarHospedes();
    std::cout << "\nLISTA DE HOSPEDES\n";
    if (lista.empty()) {
        std::cout << "Nenhum hospede cadastrado.\n";
    } else {
        for(const auto& h : lista) {
            std::cout << "Email: " << h.getEmail().getValor() 
                    << " | Nome: " << h.getNome().getValor() << "\n";
        }
    }
}

// Stubs
void CntrApresentacaoHospede::editarHospedde() {
    std::cout << "\n--- EDITAR HOSPEDE ---\n";
    std::string emailHospede;
    std::string entrada;

    std::vector<Hospede> listaHospedes = this->servicoHospede->listarHospedes();
    if (listaHospedes.empty()) {
        std::cout << "Nenhum hospede cadastrado para editar.\n";
        return;
    }

    listarHospedes(); // Mostra os hospedes disponiveis

    std::cout << "\nInforme o Email do Hospede a ser editado (ou 0 para cancelar): ";
    std::getline(std::cin >> std::ws, emailHospede);

    if (emailHospede == "0") {
        std::cout << "Edicao cancelada.\n";
        return;
    }

    Hospede* hospedeExistente = this->servicoHospede->buscarHospede(emailHospede);
    if (!hospedeExistente) {
        std::cerr << "Erro: Hospede com email " << emailHospede << " nao encontrado.\n";
        return;
    }

    Nome novoNome = hospedeExistente->getNome();
    Email novoEmail = hospedeExistente->getEmail(); // Email e chave primaria, nao editavel
    Endereco novoEndereco = hospedeExistente->getEndereco();
    Cartao novoCartao = hospedeExistente->getCartao();

    // Edita Nome
    while (true) {
        try {
            std::cout << "Novo Nome (atual: " << hospedeExistente->getNome().getValor() << ", Enter para manter): ";
            std::getline(std::cin, entrada);
            if (entrada.empty()) break;
            novoNome.setValor(entrada);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\n";
        }
    }

    // Edita Endereco
    while (true) {
        try {
            std::cout << "Novo Endereco (atual: " << hospedeExistente->getEndereco().getValor() << ", Enter para manter): ";
            std::getline(std::cin, entrada);
            if (entrada.empty()) break;
            novoEndereco.setValor(entrada);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\n";
        }
    }

    // Edita Cartao
    while (true) {
        try {
            std::cout << "Novo Cartao (atual: " << hospedeExistente->getCartao().getValor() << ", Enter para manter): ";
            std::getline(std::cin, entrada);
            if (entrada.empty()) break;
            novoCartao.setValor(entrada);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\n";
        }
    }

    Hospede hospedeAtualizado(novoNome, novoEmail, novoEndereco, novoCartao);

    if (this->servicoHospede->editarHospede(hospedeAtualizado)) {
        std::cout << "\nHospede atualizado com sucesso!\n";
    } else {
        std::cerr << "Erro ao atualizar hospede.\n";
    }
}

void CntrApresentacaoHospede::excluirHospede() {
    std::cout << "\n--- EXCLUIR HOSPEDE ---\n";
    std::string emailHospede;
    std::string confirmacao;

    std::vector<Hospede> listaHospedes = this->servicoHospede->listarHospedes();
    if (listaHospedes.empty()) {
        std::cout << "Nenhum hospede cadastrado para excluir.\n";
        return;
    }

    listarHospedes(); // Mostra os hospedes disponiveis

    std::cout << "\nInforme o Email do Hospede a ser excluido (ou 0 para cancelar): ";
    std::getline(std::cin >> std::ws, emailHospede);

    if (emailHospede == "0") {
        std::cout << "Exclusao cancelada.\n";
        return;
    }

    Hospede* hospedeExistente = this->servicoHospede->buscarHospede(emailHospede);
    if (!hospedeExistente) {
        std::cerr << "Erro: Hospede com email " << emailHospede << " nao encontrado.\n";
        return;
    }
    
    std::cout << "Tem certeza que deseja excluir o hospede '" << hospedeExistente->getNome().getValor() << "' (" << emailHospede << ")? (s/n): ";
    std::cin >> confirmacao;

    if (confirmacao == "s" || confirmacao == "S") {
        if (this->servicoHospede->excluirHospede(emailHospede)) {
            std::cout << "\nHospede excluido com sucesso!\n";
        } else {
            std::cerr << "Erro ao excluir hospede.\n";
        }
    } else {
        std::cout << "Exclusao cancelada.\n";
    }
}


// Reserva
// Criar reserva

void CntrApresentacaoReserva::criarReserva(Gerente* gerenteLogado) { // MODIFIED
    std::cout << "\nCriar Reserva\n";
    std::string entrada;

    // Selecao do hotel
    Hotel* hotelSelecionado = nullptr;
    std::vector<Hotel> listaH = this->servicoHotel->listarHoteis();
    // Filter hotels to only show manager's hotels
    listaH.erase(std::remove_if(listaH.begin(), listaH.end(), 
                                [gerenteLogado](const Hotel& h){
                                    return h.getGerente() == nullptr || h.getGerente()->getEmail().getValor() != gerenteLogado->getEmail().getValor();
                                }), 
                 listaH.end());
    if (listaH.empty()) { std::cout << "Nenhum hotel cadastrado por voce. Impossivel criar reserva.\n"; return; }

    while (true) {
        std::cout << "Informe o codigo do Hotel (somente os seus hoteis): ";
        std::getline(std::cin >> std::ws, entrada);
        
        hotelSelecionado = this->servicoHotel->buscarHotel(entrada);
        if (hotelSelecionado) {
            // Check ownership
            if (hotelSelecionado->getGerente() == nullptr || hotelSelecionado->getGerente()->getEmail().getValor() != gerenteLogado->getEmail().getValor()) {
                std::cerr << "Erro: Hotel com codigo " << entrada << " nao pertence a voce.\n";
                std::cout << "\nSeus Hoteis Disponiveis:\n";
                for(size_t i = 0; i < listaH.size(); ++i) 
                    std::cout << " - " << listaH[i].getCodigo().getValor() << "\n";
                std::cout << "\nTente novamente abaixo:\n";
                continue;
            }
            break;
        }

        std::cerr << "Erro: Hotel nao encontrado.\n";
        std::cout << "\nSeus Hoteis Disponiveis:\n";
        for(size_t i = 0; i < listaH.size(); ++i) 
            std::cout << " - " << listaH[i].getCodigo().getValor() << "\n";
        std::cout << "\nTente novamente abaixo:\n";
    }

    // Selecao do hospede (Hospedes sao globais, nao gerenciados por gerente individual)
    Hospede* hospedeSelecionado = nullptr;
    std::vector<Hospede> listaHospedes = this->servicoHospede->listarHospedes();
    if (listaHospedes.empty()) { std::cout << "Nenhum hospede cadastrado. Impossivel criar reserva.\n"; return; }

    while (true) {
        std::cout << "Informe o e-mail do Hospede: ";
        std::getline(std::cin, entrada);

        hospedeSelecionado = this->servicoHospede->buscarHospede(entrada);
        if (hospedeSelecionado) break;

        std::cerr << "Erro: Hospede nao encontrado.\n";
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

    // Selecao de quarto
    Quarto* quartoSelecionado = nullptr;
    std::vector<Quarto> todosQuartos = this->servicoQuarto->listarQuartos();
    // Filter quartos to only show quartos of hotels owned by the manager
    todosQuartos.erase(std::remove_if(todosQuartos.begin(), todosQuartos.end(), 
                                      [gerenteLogado](const Quarto& q){
                                          return q.getHotel() == nullptr || q.getHotel()->getGerente() == nullptr || q.getHotel()->getGerente()->getEmail().getValor() != gerenteLogado->getEmail().getValor();
                                      }), 
                       todosQuartos.end());

    if (todosQuartos.empty()) { std::cout << "Nenhum quarto cadastrado por voce. Impossivel criar reserva.\n"; return; }
    
    while (true) {
        std::cout << "Informe o numero do Quarto (dos seus hoteis): ";
        std::getline(std::cin, entrada);

        bool quartoExisteNoHotel = false;

        for (size_t i = 0; i < todosQuartos.size(); ++i) { // Iterar sobre a lista ja filtrada
            if (todosQuartos[i].getHotel()->getCodigo().getValor() == hotelSelecionado->getCodigo().getValor() &&
                todosQuartos[i].getNumero().getValor() == entrada) {
                
                quartoExisteNoHotel = true;

                // Verificacao de conflitos de datas
                bool conflitoDetectado = false;
                std::vector<Reserva> todasReservas = this->servicoReserva->listarReservas();
                // Filter reservations to only show reservations of hotels owned by the manager
                todasReservas.erase(std::remove_if(todasReservas.begin(), todasReservas.end(), 
                                                    [gerenteLogado](const Reserva& r){
                                                        return r.getQuarto() == nullptr || r.getQuarto()->getHotel() == nullptr || r.getQuarto()->getHotel()->getGerente() == nullptr || r.getQuarto()->getHotel()->getGerente()->getEmail().getValor() != gerenteLogado->getEmail().getValor();
                                                    }), 
                                     todasReservas.end());


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
                    std::cerr << "ERRO: Quarto indisponivel neste periodo.\n";
                } else {
                    quartoSelecionado = new Quarto(todosQuartos[i]);
                }
                break;
            }
        }

        if (quartoSelecionado) break;
        if (!quartoExisteNoHotel) {
            std::cerr << "Quarto nao encontrado neste hotel. Tente novamente.\n";
            std::cout << "\nSeus Quartos Disponiveis neste hotel (" << hotelSelecionado->getNome().getValor() << "):\n";
            for(const auto& q : todosQuartos) { // Iterate through already filtered list
                 if (q.getHotel()->getCodigo().getValor() == hotelSelecionado->getCodigo().getValor()) {
                    std::cout << " - Quarto: " << q.getNumero().getValor() << " | Capacidade: " << q.getCapacidade().getValor() << "\n";
                 }
            }
            std::cout << "\nTente novamente abaixo:\n";
        }
    }

    // Calculo do valor
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
            std::cout << "Codigo da Reserva (10 alphanum): ";
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

    if (this->servicoReserva->criarReserva(novaReserva)) {
        std::cout << "\nReserva criada com sucesso!\n";
    } else {
        std::cerr << "Erro: Codigo de reserva duplicado.\n";
    }
}

// Listar Reservas
void CntrApresentacaoReserva::listarReservas(Gerente* gerenteLogado) { // MODIFIED
    std::vector<Reserva> listaCompleta = this->servicoReserva->listarReservas();
    std::vector<Reserva> listaFiltrada;

    for(const auto& r : listaCompleta) {
        if (r.getQuarto() != nullptr && r.getQuarto()->getHotel() != nullptr && r.getQuarto()->getHotel()->getGerente() != nullptr && r.getQuarto()->getHotel()->getGerente()->getEmail().getValor() == gerenteLogado->getEmail().getValor()) {
            listaFiltrada.push_back(r);
        }
    }

    std::cout << "\nLISTA DE SUAS RESERVAS\n";
    if (listaFiltrada.empty()) {
        std::cout << "Nenhuma reserva cadastrada por voce.\n";
    } else {
        for(const auto& r : listaFiltrada) {
            std::cout << "Cod: " << r.getCodigo().getValor() 
                      << " | Hospede: " << r.getHospede()->getNome().getValor() 
                      << " | Hotel: " << r.getQuarto()->getHotel()->getNome().getValor()
                      << " | Quarto: " << r.getQuarto()->getNumero().getValor() << "\n";
        }
    }
}

// Stubs
void CntrApresentacaoReserva::editarReserva(Gerente* gerenteLogado) { // MODIFIED
    std::cout << "\n--- EDITAR RESERVA ---\n";
    std::string codigoReserva;
    std::string entrada;

    std::vector<Reserva> listaReservasDoGerente = this->servicoReserva->listarReservas();
    listaReservasDoGerente.erase(std::remove_if(listaReservasDoGerente.begin(), listaReservasDoGerente.end(), 
                                                  [gerenteLogado](const Reserva& r){
                                                      return r.getQuarto() == nullptr || r.getQuarto()->getHotel() == nullptr || r.getQuarto()->getHotel()->getGerente() == nullptr || r.getQuarto()->getHotel()->getGerente()->getEmail().getValor() != gerenteLogado->getEmail().getValor();
                                                  }), 
                                   listaReservasDoGerente.end());

    if (listaReservasDoGerente.empty()) {
        std::cout << "Nenhuma reserva cadastrada por voce para editar.\n";
        return;
    }

    // Mostrar apenas as reservas do gerente logado
    std::cout << "\nSuas Reservas Disponiveis para Edicao:\n";
    for(const auto& r : listaReservasDoGerente) {
        std::cout << "Cod: " << r.getCodigo().getValor() 
                  << " | Hospede: " << r.getHospede()->getNome().getValor() 
                  << " | Hotel: " << r.getQuarto()->getHotel()->getNome().getValor()
                  << " | Quarto: " << r.getQuarto()->getNumero().getValor() << "\n";
    }

    std::cout << "\nInforme o Codigo da Reserva a ser editada (ou 0 para cancelar): ";
    std::getline(std::cin >> std::ws, codigoReserva);

    if (codigoReserva == "0") {
        std::cout << "Edicao cancelada.\n";
        return;
    }

    std::vector<Reserva> todasReservas = this->servicoReserva->listarReservas();
    Reserva* reservaExistente = nullptr;

    for (auto& r : todasReservas) {
        if (r.getCodigo().getValor() == codigoReserva) {
            reservaExistente = &r;
            break;
        }
    }

    if (!reservaExistente || reservaExistente->getQuarto() == nullptr || reservaExistente->getQuarto()->getHotel() == nullptr || reservaExistente->getQuarto()->getHotel()->getGerente() == nullptr || reservaExistente->getQuarto()->getHotel()->getGerente()->getEmail().getValor() != gerenteLogado->getEmail().getValor()) { // Ownership check
        std::cerr << "Erro: Reserva com codigo " << codigoReserva << " nao encontrada ou nao pertence a um dos seus hoteis.\n";
        return;
    }

    // Copia os dados existentes para o objeto de edicao
    Data novaDataChegada = reservaExistente->getDataChegada();
    Data novaDataPartida = reservaExistente->getDataPartida();
    Dinheiro novoValor = reservaExistente->getValor(); // Recalculado, nao editavel diretamente
    Codigo codigoOriginal = reservaExistente->getCodigo(); // Codigo e chave, nao editavel

    // Edita Data Chegada
    while (true) {
        try {
            std::cout << "Nova Data de Chegada (atual: " << reservaExistente->getDataChegada().getValor() << ", DD-MMM-AAAA, Enter para manter): ";
            std::getline(std::cin, entrada);
            if (entrada.empty()) break;
            novaDataChegada.setValor(entrada);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\n";
        }
    }

    // Edita Data Partida
    while (true) {
        try {
            std::cout << "Nova Data de Partida (atual: " << reservaExistente->getDataPartida().getValor() << ", DD-MMM-AAAA, Enter para manter): ";
            std::getline(std::cin, entrada);
            if (entrada.empty()) break;
            novaDataPartida.setValor(entrada);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\n";
        }
    }
    
    // Recalcula o valor da reserva (simplificado, poderia ser mais complexo)
    long absChegada = calcularDiasAbsolutos(novaDataChegada.getValor());
    long absPartida = calcularDiasAbsolutos(novaDataPartida.getValor());
    long diasDif = absPartida - absChegada;

    if (diasDif <= 0) {
        std::cerr << "Erro: Data de partida deve ser posterior a data de chegada.\n";
        return;
    }

    // Buscar o quarto associado para pegar a diaria
    Quarto* quartoAssociado = reservaExistente->getQuarto();
    if (!quartoAssociado) {
        std::cerr << "Erro: Quarto associado a reserva nao encontrado.\n";
        return;
    }
    int diariaCentavos = quartoAssociado->getDiaria().getValor();
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


    Reserva reservaAtualizada(novaDataChegada, novaDataPartida, valorTotal, codigoOriginal);
    reservaAtualizada.setHospede(reservaExistente->getHospede()); // Mantem hospede e quarto originais
    reservaAtualizada.setQuarto(reservaExistente->getQuarto());


    if (this->servicoReserva->editarReserva(reservaAtualizada)) {
        std::cout << "\nReserva atualizada com sucesso!\n";
    } else {
        std::cerr << "Erro ao atualizar reserva.\n";
    }
}

void CntrApresentacaoReserva::excluirReserva(Gerente* gerenteLogado) { // MODIFIED
    std::cout << "\n--- EXCLUIR RESERVA ---\n";
    std::string codigoReserva;
    std::string confirmacao;

    std::vector<Reserva> listaReservasDoGerente = this->servicoReserva->listarReservas();
    listaReservasDoGerente.erase(std::remove_if(listaReservasDoGerente.begin(), listaReservasDoGerente.end(), 
                                                  [gerenteLogado](const Reserva& r){
                                                      return r.getQuarto() == nullptr || r.getQuarto()->getHotel() == nullptr || r.getQuarto()->getHotel()->getGerente() == nullptr || r.getQuarto()->getHotel()->getGerente()->getEmail().getValor() != gerenteLogado->getEmail().getValor();
                                                  }), 
                                   listaReservasDoGerente.end());

    if (listaReservasDoGerente.empty()) {
        std::cout << "Nenhuma reserva cadastrada por voce para excluir.\n";
        return;
    }

    // Mostrar apenas as reservas do gerente logado
    std::cout << "\nSuas Reservas Disponiveis para Exclusao:\n";
    for(const auto& r : listaReservasDoGerente) {
        std::cout << "Cod: " << r.getCodigo().getValor() 
                  << " | Hospede: " << r.getHospede()->getNome().getValor() 
                  << " | Hotel: " << r.getQuarto()->getHotel()->getNome().getValor()
                  << " | Quarto: " << r.getQuarto()->getNumero().getValor() << "\n";
    }


    std::cout << "\nInforme o Codigo da Reserva a ser excluida (ou 0 para cancelar): ";
    std::getline(std::cin >> std::ws, codigoReserva);

    if (codigoReserva == "0") {
        std::cout << "Exclusao cancelada.\n";
        return;
    }

    std::vector<Reserva> todasReservas = this->servicoReserva->listarReservas();
    Reserva* reservaExistente = nullptr;

    for (auto& r : todasReservas) {
        if (r.getCodigo().getValor() == codigoReserva) {
            reservaExistente = &r;
            break;
        }
    }

    if (!reservaExistente || reservaExistente->getQuarto() == nullptr || reservaExistente->getQuarto()->getHotel() == nullptr || reservaExistente->getQuarto()->getHotel()->getGerente() == nullptr || reservaExistente->getQuarto()->getHotel()->getGerente()->getEmail().getValor() != gerenteLogado->getEmail().getValor()) { // Ownership check
        std::cerr << "Erro: Reserva com codigo " << codigoReserva << " nao encontrada ou nao pertence a um dos seus hoteis.\n";
        return;
    }
    
    std::cout << "Tem certeza que deseja excluir a reserva '" << codigoReserva << "' do hospede '" << reservaExistente->getHospede()->getNome().getValor() << "'? (s/n): ";
    std::cin >> confirmacao;

    if (confirmacao == "s" || confirmacao == "S") {
        if (this->servicoReserva->excluirReserva(codigoReserva)) {
            std::cout << "\nReserva excluida com sucesso!\n";
        } else {
            std::cerr << "Erro ao excluir reserva.\n";
        }
    } else {
        std::cout << "Exclusao cancelada.\n";
    }
}
