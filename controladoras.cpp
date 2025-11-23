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
        std::cout << "\nConta criada com sucesso! Voce ja pode fazer login.\n";
    } else {
        std::cerr << "Erro: Este e-mail ja esta cadastrado no sistema.\n";
    }
}

// Autenticação
Gerente* CntrApresentacaoGerente::autenticar() {
    std::string email, senha;
    std::cout << "\nLOGIN\n";
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

    // Novo E-mail (chave primária, não editável diretamente)
    // Requisito: Não é possível editar dado que identifica registro (chave primária)
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
        // Atualiza o objeto logado para refletir as mudanças
        gerenteLogado->setNome(novoNome);
        gerenteLogado->setSenha(novaSenha);
        gerenteLogado->setRamal(novoRamal);
        std::cout << "\nConta atualizada com sucesso!\n";
    } else {
        std::cerr << "Erro ao atualizar conta.\n";
    }
}

void CntrApresentacaoGerente::excluirConta(Gerente* gerenteLogado) {
    std::cout << "\n--- EXCLUIR CONTA DE GERENTE ---\n";
    std::string confirmacao;
    std::cout << "Tem certeza que deseja excluir sua conta (" << gerenteLogado->getEmail().getValor() << ")? (s/n): ";
    std::cin >> confirmacao;

    if (confirmacao == "s" || confirmacao == "S") {
        if (this->servicoGerente->excluirGerente(gerenteLogado->getEmail().getValor())) {
            std::cout << "\nConta excluída com sucesso!\n";
            gerenteLogado = nullptr; // Força logout após exclusão
        } else {
            std::cerr << "Erro ao excluir conta.\n";
        }
    } else {
        std::cout << "Exclusão cancelada.\n";
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

    // ENDEREÇO
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

    // CÓDIGO
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

    // MUDANÇA: Usando this->servicoHotel
    this->servicoHotel->criarHotel(novoHotel); 
    
    std::cout << "\nHotel '" << novoHotel.getNome().getValor() << "' criado com sucesso!\n";
}

//Listar hoteis
void CntrApresentacaoHotel::listarHoteis() {
    std::cout << "\nLISTA DE HOTEIS\n";
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
void CntrApresentacaoHotel::editar(Gerente* gerenteLogado) {
    std::cout << "\n--- EDITAR HOTEL ---\n";
    std::string codigoHotel;
    std::string entrada;

    listarHoteis(); // Mostra os hotéis disponíveis

    std::cout << "\nInforme o Código do Hotel a ser editado (ou 0 para cancelar): ";
    std::getline(std::cin >> std::ws, codigoHotel);

    if (codigoHotel == "0") {
        std::cout << "Edição cancelada.\n";
        return;
    }

    Hotel* hotelExistente = this->servicoHotel->buscarHotel(codigoHotel);
    if (!hotelExistente) {
        std::cerr << "Erro: Hotel com código " << codigoHotel << " não encontrado.\n";
        return;
    }

    Nome novoNome = hotelExistente->getNome();
    Endereco novoEndereco = hotelExistente->getEndereco();
    Telefone novoTelefone = hotelExistente->getTelefone();
    Codigo codigoOriginal = hotelExistente->getCodigo(); // Código não é editável

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

    // Edita Endereço
    while (true) {
        try {
            std::cout << "Novo Endereço (atual: " << hotelExistente->getEndereco().getValor() << ", Enter para manter): ";
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
    hotelAtualizado.setGerente(gerenteLogado); // Mantém o mesmo gerente

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

    listarHoteis(); // Mostra os hotéis disponíveis

    std::cout << "\nInforme o Código do Hotel a ser excluído (ou 0 para cancelar): ";
    std::getline(std::cin >> std::ws, codigoHotel);

    if (codigoHotel == "0") {
        std::cout << "Exclusão cancelada.\n";
        return;
    }

    Hotel* hotelExistente = this->servicoHotel->buscarHotel(codigoHotel);
    if (!hotelExistente) {
        std::cerr << "Erro: Hotel com código " << codigoHotel << " não encontrado.\n";
        return;
    }
    
    std::cout << "Tem certeza que deseja excluir o hotel '" << hotelExistente->getNome().getValor() << "' (" << codigoHotel << ")? (s/n): ";
    std::cin >> confirmacao;

    if (confirmacao == "s" || confirmacao == "S") {
        if (this->servicoHotel->excluirHotel(codigoHotel)) {
            std::cout << "\nHotel excluído com sucesso!\n";
        } else {
            std::cerr << "Erro ao excluir hotel.\n";
        }
    } else {
        std::cout << "Exclusão cancelada.\n";
    }
}


// Quartos
//Criar quarto
void CntrApresentacaoQuarto::criarQuarto() {
    std::cout << "\nCriar Quarto\n";
    std::string entrada;
    
    // Associar ao hotel
    Hotel* hotelPai = nullptr;
    while (true) {
        std::cout << "Informe o codigo do Hotel deste quarto: ";
        std::getline(std::cin >> std::ws, entrada);
        
        // MUDANÇA: this->servicoHotel
        hotelPai = this->servicoHotel->buscarHotel(entrada);
        if (hotelPai) break;
        
        std::cerr << "Erro: Hotel nao encontrado.\n";

        std::cout << "\nHoteis Disponiveis\n";
        std::vector<Hotel> lista = this->servicoHotel->listarHoteis();
        
        if (lista.empty()) {
            std::cout << "Nenhum hotel cadastrado. Impossivel criar quarto.\n";
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
    std::cout << "\nLISTA DE QUARTOS\n";
    for(const auto& q : lista) {
        std::cout << "Hotel: " << q.getHotel()->getNome().getValor() 
                  << " | Quarto: " << q.getNumero().getValor() << "\n";
    }
}

// Stubs
void CntrApresentacaoQuarto::editarQuarto() {
    std::cout << "\n--- EDITAR QUARTO ---\n";
    std::string codigoHotel, numeroQuartoStr;
    std::string entrada;

    listarQuartos(); // Mostra os quartos disponíveis

    std::cout << "\nInforme o Código do Hotel ao qual o quarto pertence (ou 0 para cancelar): ";
    std::getline(std::cin >> std::ws, codigoHotel);

    if (codigoHotel == "0") {
        std::cout << "Edição cancelada.\n";
        return;
    }

    std::cout << "Informe o Número do Quarto a ser editado (ou 0 para cancelar): ";
    std::getline(std::cin, numeroQuartoStr);

    if (numeroQuartoStr == "0") {
        std::cout << "Edição cancelada.\n";
        return;
    }

    // Para editar, precisamos buscar o quarto existente. No momento, não há um buscarQuarto(codigoHotel, numeroQuarto)
    // na interface de serviço. Vamos listar todos e buscar localmente para obter um objeto Quarto completo.
    std::vector<Quarto> todosQuartos = this->servicoQuarto->listarQuartos();
    Quarto* quartoExistente = nullptr;

    for (auto& q : todosQuartos) {
        if (q.getHotel()->getCodigo().getValor() == codigoHotel &&
            q.getNumero().getValor() == numeroQuartoStr) {
            quartoExistente = &q;
            break;
        }
    }

    if (!quartoExistente) {
        std::cerr << "Erro: Quarto com número " << numeroQuartoStr << " no hotel " << codigoHotel << " não encontrado.\n";
        return;
    }

    // Copia os dados existentes para o objeto de edição
    Numero novoNumero = quartoExistente->getNumero(); // Número é chave, não editável
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

    // Edita Diária
    while (true) {
        try {
            std::cout << "Nova Diária (atual: " << (static_cast<double>(novaDiaria.getValor()) / 100.0) << ", Ex.: 152.99, Enter para manter): ";
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
    
    // Cria um novo objeto Quarto com os dados atualizados (mantendo a referência ao hotel original)
    Quarto quartoAtualizado(novoNumero, novaCapacidade, novaDiaria, novoRamal, quartoExistente->getHotel());

    if (this->servicoQuarto->editarQuarto(quartoAtualizado)) {
        std::cout << "\nQuarto atualizado com sucesso!\n";
    } else {
        std::cerr << "Erro ao atualizar quarto.\n";
    }
}

void CntrApresentacaoQuarto::excluirQuarto() {
    std::cout << "\n--- EXCLUIR QUARTO ---\n";
    std::string codigoHotel, numeroQuartoStr;
    std::string confirmacao;

    listarQuartos(); // Mostra os quartos disponíveis

    std::cout << "\nInforme o Código do Hotel ao qual o quarto pertence (ou 0 para cancelar): ";
    std::getline(std::cin >> std::ws, codigoHotel);

    if (codigoHotel == "0") {
        std::cout << "Exclusão cancelada.\n";
        return;
    }

    std::cout << "Informe o Número do Quarto a ser excluído (ou 0 para cancelar): ";
    std::getline(std::cin, numeroQuartoStr);

    if (numeroQuartoStr == "0") {
        std::cout << "Exclusão cancelada.\n";
        return;
    }

    std::cout << "Tem certeza que deseja excluir o quarto " << numeroQuartoStr << " do hotel " << codigoHotel << "? (s/n): ";
    std::cin >> confirmacao;

    if (confirmacao == "s" || confirmacao == "S") {
        if (this->servicoQuarto->excluirQuarto(codigoHotel, numeroQuartoStr)) {
            std::cout << "\nQuarto excluído com sucesso!\n";
        } else {
            std::cerr << "Erro ao excluir quarto.\n";
        }
    } else {
        std::cout << "Exclusão cancelada.\n";
    }
}


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

    // Endereço
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

    // Cartão
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
    
    // MUDANÇA: this->servicoHospede
    if (this->servicoHospede->criarHospede(novoHospede)) {
        std::cout << "\nHospede '" << novoHospede.getNome().getValor() << "' cadastrado com sucesso!\n";
    } else {
        std::cerr << "Erro: Hospede ja cadastrado (email duplicado).\n";
    }
}

// Listar Hóspedes
void CntrApresentacaoHospede::listarHospedes() {
    std::vector<Hospede> lista = this->servicoHospede->listarHospedes();
    std::cout << "\nLISTA DE HOSPEDES\n";
    for(const auto& h : lista) {
        std::cout << "Email: " << h.getEmail().getValor() 
                  << " | Nome: " << h.getNome().getValor() << "\n";
    }
}

// Stubs
void CntrApresentacaoHospede::editarHospedde() {
    std::cout << "\n--- EDITAR HÓSPEDE ---\n";
    std::string emailHospede;
    std::string entrada;

    listarHospedes(); // Mostra os hóspedes disponíveis

    std::cout << "\nInforme o Email do Hóspede a ser editado (ou 0 para cancelar): ";
    std::getline(std::cin >> std::ws, emailHospede);

    if (emailHospede == "0") {
        std::cout << "Edição cancelada.\n";
        return;
    }

    Hospede* hospedeExistente = this->servicoHospede->buscarHospede(emailHospede);
    if (!hospedeExistente) {
        std::cerr << "Erro: Hóspede com email " << emailHospede << " não encontrado.\n";
        return;
    }

    Nome novoNome = hospedeExistente->getNome();
    Email novoEmail = hospedeExistente->getEmail(); // Email é chave primária, não editável
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

    // Edita Endereço
    while (true) {
        try {
            std::cout << "Novo Endereço (atual: " << hospedeExistente->getEndereco().getValor() << ", Enter para manter): ";
            std::getline(std::cin, entrada);
            if (entrada.empty()) break;
            novoEndereco.setValor(entrada);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: " << e.what() << "\n";
        }
    }

    // Edita Cartão
    while (true) {
        try {
            std::cout << "Novo Cartão (atual: " << hospedeExistente->getCartao().getValor() << ", Enter para manter): ";
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
        std::cout << "\nHóspede atualizado com sucesso!\n";
    } else {
        std::cerr << "Erro ao atualizar hóspede.\n";
    }
}

void CntrApresentacaoHospede::excluirHospede() {
    std::cout << "\n--- EXCLUIR HÓSPEDE ---\n";
    std::string emailHospede;
    std::string confirmacao;

    listarHospedes(); // Mostra os hóspedes disponíveis

    std::cout << "\nInforme o Email do Hóspede a ser excluído (ou 0 para cancelar): ";
    std::getline(std::cin >> std::ws, emailHospede);

    if (emailHospede == "0") {
        std::cout << "Exclusão cancelada.\n";
        return;
    }

    Hospede* hospedeExistente = this->servicoHospede->buscarHospede(emailHospede);
    if (!hospedeExistente) {
        std::cerr << "Erro: Hóspede com email " << emailHospede << " não encontrado.\n";
        return;
    }
    
    std::cout << "Tem certeza que deseja excluir o hóspede '" << hospedeExistente->getNome().getValor() << "' (" << emailHospede << ")? (s/n): ";
    std::cin >> confirmacao;

    if (confirmacao == "s" || confirmacao == "S") {
        if (this->servicoHospede->excluirHospede(emailHospede)) {
            std::cout << "\nHóspede excluído com sucesso!\n";
        } else {
            std::cerr << "Erro ao excluir hóspede.\n";
        }
    } else {
        std::cout << "Exclusão cancelada.\n";
    }
}


// Reserva
// Criar reserva

void CntrApresentacaoReserva::criarReserva() {
    std::cout << "\nCriar Reserva\n";
    std::string entrada;

    // Seleção do hotel
    Hotel* hotelSelecionado = nullptr;
    while (true) {
        std::cout << "Informe o codigo do Hotel: ";
        std::getline(std::cin >> std::ws, entrada);
        
        // MUDANÇA: this->servicoHotel
        hotelSelecionado = this->servicoHotel->buscarHotel(entrada);
        if (hotelSelecionado) break;

        std::cerr << "Hotel nao encontrado. Hotéis disponiveis:\n";
        std::vector<Hotel> listaH = this->servicoHotel->listarHoteis();
        if (listaH.empty()) { std::cout << "Nenhum hotel cadastrado.\n"; return; }
        
        for(size_t i = 0; i < listaH.size(); ++i) 
            std::cout << " - " << listaH[i].getCodigo().getValor() << "\n";
    }

    // Seleção do hóspede
    Hospede* hospedeSelecionado = nullptr;
    while (true) {
        std::cout << "Informe o e-mail do Hospede: ";
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
        std::cout << "Informe o numero do Quarto: ";
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

    // MUDANÇA: this->servicoReserva
    if (this->servicoReserva->criarReserva(novaReserva)) {
        std::cout << "\nReserva criada com sucesso!\n";
    } else {
        std::cerr << "Erro: Codigo de reserva duplicado.\n";
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
void CntrApresentacaoReserva::editarReserva() {
    std::cout << "\n--- EDITAR RESERVA ---\n";
    std::string codigoReserva;
    std::string entrada;

    listarReservas(); // Mostra as reservas disponíveis

    std::cout << "\nInforme o Código da Reserva a ser editada (ou 0 para cancelar): ";
    std::getline(std::cin >> std::ws, codigoReserva);

    if (codigoReserva == "0") {
        std::cout << "Edição cancelada.\n";
        return;
    }

    // Para editar, precisamos buscar a reserva existente. Não há buscarReserva na interface de serviço.
    // Vamos listar todas e buscar localmente para obter um objeto Reserva completo.
    std::vector<Reserva> todasReservas = this->servicoReserva->listarReservas();
    Reserva* reservaExistente = nullptr;

    for (auto& r : todasReservas) {
        if (r.getCodigo().getValor() == codigoReserva) {
            reservaExistente = &r;
            break;
        }
    }

    if (!reservaExistente) {
        std::cerr << "Erro: Reserva com código " << codigoReserva << " não encontrada.\n";
        return;
    }

    // Copia os dados existentes para o objeto de edição
    Data novaDataChegada = reservaExistente->getDataChegada();
    Data novaDataPartida = reservaExistente->getDataPartida();
    Dinheiro novoValor = reservaExistente->getValor(); // Recalculado, não editável diretamente
    Codigo codigoOriginal = reservaExistente->getCodigo(); // Código é chave, não editável

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

    // Buscar o quarto associado para pegar a diária
    Quarto* quartoAssociado = reservaExistente->getQuarto();
    if (!quartoAssociado) {
        std::cerr << "Erro: Quarto associado à reserva não encontrado.\n";
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
    reservaAtualizada.setHospede(reservaExistente->getHospede()); // Mantém hóspede e quarto originais
    reservaAtualizada.setQuarto(reservaExistente->getQuarto());


    if (this->servicoReserva->editarReserva(reservaAtualizada)) {
        std::cout << "\nReserva atualizada com sucesso!\n";
    } else {
        std::cerr << "Erro ao atualizar reserva.\n";
    }
}

void CntrApresentacaoReserva::excluirReserva() {
    std::cout << "\n--- EXCLUIR RESERVA ---\n";
    std::string codigoReserva;
    std::string confirmacao;

    listarReservas(); // Mostra as reservas disponíveis

    std::cout << "\nInforme o Código da Reserva a ser excluída (ou 0 para cancelar): ";
    std::getline(std::cin >> std::ws, codigoReserva);

    if (codigoReserva == "0") {
        std::cout << "Exclusão cancelada.\n";
        return;
    }

    // Para excluir, precisamos buscar a reserva existente. Não há buscarReserva na interface de serviço.
    // Vamos listar todas e buscar localmente para obter um objeto Reserva completo.
    std::vector<Reserva> todasReservas = this->servicoReserva->listarReservas();
    Reserva* reservaExistente = nullptr;

    for (auto& r : todasReservas) {
        if (r.getCodigo().getValor() == codigoReserva) {
            reservaExistente = &r;
            break;
        }
    }

    if (!reservaExistente) {
        std::cerr << "Erro: Reserva com código " << codigoReserva << " não encontrada.\n";
        return;
    }
    
    std::cout << "Tem certeza que deseja excluir a reserva '" << codigoReserva << "' do hóspede '" << reservaExistente->getHospede()->getNome().getValor() << "'? (s/n): ";
    std::cin >> confirmacao;

    if (confirmacao == "s" || confirmacao == "S") {
        if (this->servicoReserva->excluirReserva(codigoReserva)) {
            std::cout << "\nReserva excluída com sucesso!\n";
        } else {
            std::cerr << "Erro ao excluir reserva.\n";
        }
    } else {
        std::cout << "Exclusão cancelada.\n";
    }
}