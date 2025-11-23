# Projeto-TP1

//Listagem de hoteis
void Gerente::listarHoteis(){
    std::cout << "\nLista de Hoteis\n";
    //Teste para lista vazia
    if (hoteis.empty()) {
        std::cout << "Nenhum hotel cadastrado.\n";
        return;
    }

    for (size_t i = 0; i < hoteis.size(); ++i) {
        const Hotel& h = hoteis[i];
        std::cout << h.getNome()
                  << "\n  Endereco: " << h.getEndereco()
                  << "\n  Telefone: " << h.getTelefone()
                  << "\n  Codigo:   " << h.getCodigo()
                  << "\n";
    }
}

//Função auxiliar para achar o objeto hotel adequado
Hotel* Gerente::buscarHotelPorCodigo(const std::string& codigo){
    for (Hotel& hotel : hoteis) {
        if (hotel.getCodigo() == codigo) {
            return &hotel;
        }
    }
    return nullptr; // não encontrou
}

//Edição de hotel
void Gerente::editarHotel() {
    std::cout << "\nEditar Hotel\n";

    if (hoteis.empty()) {
        std::cout << "Nenhum hotel cadastrado.\n";
        return;
    }

    listarHoteis();

    Hotel* hotel = nullptr;
    std::string codigo;

    //LOOP PARA ENCONTRAR O HOTEL
    while (true) {
        std::cout << "\nInforme o código do hotel que deseja editar "
                     "(ou pressione ENTER para cancelar): ";
        std::getline(std::cin >> std::ws, codigo);

        if (codigo.empty()) {
            std::cout << "Edição cancelada.\n";
            return;
        }

        hotel = buscarHotelPorCodigo(codigo);

        if (hotel) break;

        std::cerr << "Código inválido. Nenhum hotel encontrado.\n";
    }

    //OBJETO TEMPORÁRIO PARA VALIDAÇÕES
    Hotel hotelTemp;

    std::string novoNome, novoEndereco, novoTelefone;

    std::cout << "\nEditando '" << hotel->getNome() << "'\n";

    //NOME
    do {
        std::cout << "Novo Nome (ou ENTER para manter): ";
        std::getline(std::cin >> std::ws, novoNome);

        if (novoNome.empty()) break;

        if (!hotelTemp.validarNome(novoNome)) {
            std::cerr << "Nome inválido. Tente novamente.\n";
        }

    } while (!novoNome.empty() && !hotelTemp.validarNome(novoNome));

    if (!novoNome.empty())
        hotel->setNome(novoNome);

    //ENDEREÇO
    do {
        std::cout << "Novo Endereço (ou ENTER para manter): ";
        std::getline(std::cin >> std::ws, novoEndereco);

        if (novoEndereco.empty()) break;

        if (!hotelTemp.validarEndereco(novoEndereco)) {
            std::cerr << "Endereço inválido. Tente novamente.\n";
        }

    } while (!novoEndereco.empty() && !hotelTemp.validarEndereco(novoEndereco));

    if (!novoEndereco.empty())
        hotel->setEndereco(novoEndereco);

    //TELEFONE
    do {
        std::cout << "Novo Telefone (ou ENTER para manter): ";
        std::getline(std::cin >> std::ws, novoTelefone);

        if (novoTelefone.empty()) break;

        if (!hotelTemp.validarTelefone(novoTelefone)) {
            std::cerr << "Telefone inválido. Tente novamente.\n";
        }

    } while (!novoTelefone.empty() && !hotelTemp.validarTelefone(novoTelefone));

    if (!novoTelefone.empty())
        hotel->setTelefone(novoTelefone);

    std::cout << "\nHotel atualizado com sucesso!\n";
}


//MÉTODOS AUXILIARES PARA EXCLUSÃO AUTOMATICA
Quarto* Gerente::buscarQuartoPorCodigo(const std::string& codigo) const {
    for (const Hotel& h : hoteis) {
        for (const Quarto& q : h.getQuartos()) {
            if (q.getCodigo() == codigo) {
                // retorna ponteiro modificável
                return const_cast<Quarto*>(&q);
            }
        }
    }
    return nullptr;
}

Reserva* Gerente::buscarReservaPorCodigo(const std::string& codigo) const {
    for (const Hotel& h : hoteis) {
        for (const Quarto& q : h.getQuartos()) {
            for (const Reserva& r : q.getReservas()) {
                if (r.getCodigo() == codigo) {
                    return const_cast<Reserva*>(&r);
                }
            }
        }
    }
    return nullptr;
}


//EXCLUIR HOTEL
void Gerente::excluirHotel() {
    std::cout << "\nExcluir Hotel\n";

    if (hoteis.empty()) {
        std::cout << "Nenhum hotel cadastrado.\n";
        return;
    }

    listarHoteis();

    std::string codigo;
    std::cout << "\nInforme o código do hotel a excluir: ";
    std::cin >> codigo;

    // Busca simples
    Hotel* hotel = buscarHotelPorCodigo(codigo);

    if (!hotel) {
        std::cerr << "Código inválido. Nenhum hotel encontrado.\n";
        return;
    }

    // Antes de excluir, precisamos achar o índice
    size_t indice = 0;
    while (indice < hoteis.size() && hoteis[indice].getCodigo() != codigo) {
        indice++;
    }

    // ====================== EXCLUSÃO EM CASCATA
    for (Quarto& q : hotel->getQuartos()) {

        // excluir reservas do quarto
        for (const Reserva& r : q.getReservas()) {
            excluirReservaPorCodigo(this, r.getCodigo());
        }

        // excluir o próprio quarto
        excluirQuartoPorCodigo(this, q.getCodigo());
    }

    hoteis.erase(hoteis.begin() + indice);

    std::cout << "Hotel excluído com sucesso!\n";

}

//QUARTOS
//Listar os quartos de um hotel
void Hotel::listarQuartos() const {
    if (quartos.empty()) {
        std::cout << "Nenhum quarto cadastrado neste hotel.\n";
        return;
    }

    for (size_t i = 0; i < quartos.size(); ++i) {
        //Acesso aos quartos
        const Quarto& q = quartos[i]; 

        std::cout << "Numero: " << q.getNumero()
                  << "\nRamal: " << q.getRamal()
                  << "\nCapacidade: " << q.getCapacidade()
                  << "\nDiaria: R$ " << q.getDiaria();

        // Verifica se tem reserva
        if (q.getReserva() != nullptr) {
            std::cout << "\nReservado";
        } else {
            std::cout << "\nLivre";
        }
        std::cout << "\n";
    }
}

//Listar todos os Quartos
void Gerente::listarQuartos() {
    std::cout << "\n--- LISTAGEM GERAL DE QUARTOS ---\n";

    if (hoteis.empty()) {
        std::cout << "Nenhum hotel cadastrado.\n";
        return;
    }

    // ITERADOR EXPLÍCITO
    for (std::vector<Hotel>::iterator it = hoteis.begin(); it != hoteis.end(); ++it) {
        it->listarQuartos(); 
    }
}

//Editar quarto
void Gerente::editarQuarto() {
    std::cout << "\nEditar Quarto\n";

    if (hoteis.empty()) {
        std::cerr << "Nenhum hotel cadastrado.\n";
        return;
    }

    listarHoteis();

    // SELECIONAR HOTEL
    std::string codigoHotel;
    Hotel* hotel = nullptr;

    while (true) {
        std::cout << "\nInforme o código do hotel a que o quarto pertence (ou ENTER para cancelar): ";
        std::getline(std::cin >> std::ws, codigoHotel);

        if (codigoHotel.empty()) {
            std::cout << "Edição cancelada.\n";
            return;
        }

        hotel = buscarHotelPorCodigo(codigoHotel);
        if (hotel) break;

        std::cerr << "Código inválido. Tente novamente.\n";
    }

    // VERIFICAR SE HOTEL TEM QUARTOS
    if (hotel->getQuartos().empty()) {
        std::cerr << "Este hotel não possui quartos cadastrados.\n";
        return;
    }

    // Exibir quartos
    hotel->listarQuartos();

    // BUSCAR O QUARTO
    std::string numeroStr;
    Quarto* quarto = nullptr;

    while (true) {
        std::cout << "\nInforme o número do quarto a editar (ex.: 015): ";
        std::getline(std::cin >> std::ws, numeroStr);

        // busca no vetor usando iterator
        for (std::vector<Quarto>::iterator it = hotel->getQuartos().begin();
             it != hotel->getQuartos().end();
             it++)
        {
            if (numeroStr == it->getNumero()) {
                quarto = &(*it);
                break;
            }
        }

        if (quarto) break;

        std::cerr << "Número de quarto não encontrado. Tente novamente.\n";
    }

    // OBJETO TEMPORÁRIO PARA VALIDAR
    Quarto quartoTemp;

    std::string novoRamal;
    int novaCapacidade = 0;
    int novaDiaria = 0;

    std::cout << "\nEditando Quarto de número " << quarto->getNumero() << "\n";

    //EDITAR CAPACIDADE
    do {
        std::string capStr;
        std::cout << "Nova Capacidade (ENTER para manter): ";
        std::getline(std::cin >> std::ws, capStr);

        if (capStr.empty()) break;

        if (!quartoTemp.validarCapacidade(novaCapacidade)) {
            std::cerr << "Capacidade deve ser entre 1 e 4.\n";
            continue;
        }

        quarto->setCapacidade(novaCapacidade);
        break;

    } while (true);

    //EDITAR DIÁRIA
    do {
        std::cout << "Nova Diária (ex.: 350.75 — ENTER para manter): ";

        std::string diariaStr;
        std::getline(std::cin >> std::ws, diariaStr);

        if (diariaStr.empty()) break;

        novaDiaria = 0;
        bool ok = true;
        bool aposVirgula = false;
        int casas = 0;

        for (char c : diariaStr) {
            if (c == '.' || c == ',') {
                aposVirgula = true;
                continue;
            }
            if (!isdigit(c)) {
                ok = false;
                break;
            }
            novaDiaria = novaDiaria * 10 + (c - '0');
            if (aposVirgula) casas++;
        }

        if (casas == 0) novaDiaria *= 100;
        else if (casas == 1) novaDiaria *= 10;
        else if (casas > 2) ok = false;

        if (!ok || !quartoTemp.validarDiaria(novaDiaria)) {
            std::cerr << "Diária inválida. Deve estar entre 0,01 e 1.000.000,00.\n";
            continue;
        }

        quarto->setDiaria(novaDiaria);
        break;

    } while (true);

    //EDITAR RAMAL
    do {
        std::cout << "Novo Ramal (00-50, ENTER para manter): ";
        std::getline(std::cin >> std::ws, novoRamal);

        if (novoRamal.empty()) break;

        if (!quartoTemp.validarRamal(novoRamal)) {
            std::cerr << "Ramal deve estar entre 00 e 50.\n";
            continue;
        }

        quarto->setRamal(novoRamal);
        break;

    } while (true);

    std::cout << "\nQuarto editado com sucesso!\n";
}

//Excluir Quarto
void Gerente::excluirQuarto() {
    std::cout << "\n=== Excluir Quarto ===\n";

    // Listar todos os quartos
    for (Hotel& h : hoteis) {
        for (Quarto& q : h.getQuartos()) {
            std::cout << "Hotel: " << h.getNome()
                      << " (Código: " << h.getCodigo() << ")"
                      << " | Quarto número: " << q.getNumero() << "\n";
        }
    }

    std::string codigoHotel;
    int numeroQuarto;

    std::cout << "\nInforme o código do hotel: ";
    std::cin >> codigoHotel;
    std::cout << "Informe o número do quarto: ";
    std::cin >> numeroQuarto;

    excluirQuartoInterno(this, codigoHotel, numeroQuarto);

    std::cout << "\nQuarto excluído com sucesso (incluindo reservas associadas).\n";
}

//Hóspedes
//Listar hóspedes
void Gerente::listarHospedes() {
    std::cout << "\nLista de Hóspedes\n";

    // Teste para lista vazia
    if (hospedes.empty()) {
        std::cout << "Nenhum hóspede cadastrado.\n";
        return;
    }

    for (size_t i = 0; i < hospedes.size(); ++i) {
        const Hospede& h = hospedes[i];

        std::cout << h.getNome()
                  << "\n  Email:    " << h.getEmail()
                  << "\n  Endereco: " << h.getEndereco()
                  << "\n  Cartão:   " << h.getCartao()
                  << "\n";
    }
}

//Editar hóspede
void Gerente::editarHospede() {
    std::cout << "\nEditar Hospede\n";

    // Confere se a lista esta vazia
    if (hospedes.empty()) {
        std::cerr << "Nenhum hospede cadastrado.\n";
        return;
    }

    listarHospedes();

    //Busca hospede pelo e-mail
    std::string emailAlvo;
    Hospede* hospede = nullptr;

    while (true) {
        std::cout << "\nInforme o email do hospede a editar (ou ENTER para cancelar): ";
        std::getline(std::cin >> std::ws, emailAlvo);

        if (emailAlvo.empty()) {
            std::cout << "Edição cancelada.\n";
            return;
        }

        // Busca no vetor usando iterator
        for (std::vector<Hospede>::iterator it = hospedes.begin(); it != hospedes.end(); ++it) {
            if (it->getEmail() == emailAlvo) {
                hospede = &(*it);
                break;
            }
        }

        if (hospede) break;

        std::cerr << "Email não encontrado. Tente novamente.\n";
    }

    std::cout << "\nEditando dados de: " << hospede->getNome() << "\n";

    //OBJETO TEMPORÁRIO PARA VALIDAR
    Hospede hospedeTemp;

    // Editar nome
    do {
        std::string novoNome;
        std::cout << "Novo Nome [ENTER para manter]: ";
        std::getline(std::cin, novoNome);

        if (novoNome.empty()) break;

        if (!hospedeTemp.validarNome(novoNome)) {
            std::cerr << "Nome inválido. Use apenas letras e inicie com maiúscula.\n";
            continue;
        }

        hospede->setNome(novoNome);
        break;

    } while (true);

    // Editar endereço
    do {
        std::string novoEndereco;
        std::cout << "Novo Endereço [ENTER para manter]: ";
        std::getline(std::cin, novoEndereco);

        if (novoEndereco.empty()) break;

        if (!hospedeTemp.validarEndereco(novoEndereco)) {
            std::cerr << "Endereço inválido.\n";
            std::cerr << "Regras: 5-30 chars, sem pontuação consecutiva ou no início/fim.\n";
            continue;
        }

        hospede->setEndereco(novoEndereco);
        break;

    } while (true);

    // Editar cartão
    do {
        std::string novoCartao;
        std::cout << "Novo Cartão (ENTER para manter): "; 
        std::getline(std::cin, novoCartao);

        if (novoCartao.empty()) break;

        if (!hospedeTemp.validarCartao(novoCartao)) {
            std::cerr << "Cartão inválido (Verifique os 16 dígitos e o algoritmo de Luhn).\n";
            continue;
        }

        hospede->setCartao(novoCartao);
        break;

    } while (true);

    std::cout << "\nHospede editado com sucesso!\n";
}

//Excluir hóspede
void Gerente::excluirHospede();