#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include "dominios.hpp"

using namespace std;

// FUNÇÕES AUXILIARES
int converterStringParaInt(const std::string& s) {
    int resultado = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];
        if (!isdigit(c)) {
            throw std::invalid_argument("A data deve conter apenas digitos nos campos numericos.");
        }
        // Lógica ASCII: '0' é 48. '3' - '0' = 3.
        resultado = resultado * 10 + (c - '0');
    }
    return resultado;
}

//VALIDAÇÕES DAS CLASSES DOMÍNIO
//Nome
void Nome::validar(std::string v) {

    // Valida o número mínimo e máximo de caracteres
    if (v.size() < 5 || v.size() > 20)
        throw std::invalid_argument("Nome deve ter entre 5 e 20 caracteres.");

    // Último caracter não pode ser um espaço
    if (v.back() == ' ')
        throw std::invalid_argument("Nome nao pode terminar com espaco.");

    for (size_t i = 0; i < v.size(); ++i) {
        // Caracteres devem ser letras ou espaço
        if (!isalpha(v[i]) && v[i] != ' ')
            throw std::invalid_argument("Nome deve conter apenas letras e espacos.");

        // Valida se o primeiro elemento está em maiúsculo
        if (i == 0 && !isupper(v[i]))
            throw std::invalid_argument("Primeira letra deve ser maiuscula.");

        // Valida se tem espaço seguido de espaço e se seguido de um espaço o elemento é maiúsculo
        if (v[i] == ' ' && (i == v.size() - 1 || !isupper(v[i + 1])))
            throw std::invalid_argument("Formato de espacos ou maiusculas invalido.");
    }
}

void Nome::setValor(std::string v) {
    validar(v);
    this->valor = v;
}

//Endereço
void Endereco::validar(std::string v) {
    // Valida se a quantidade de caracteres está no intervalo permitido
    if (v.size() < 5 || v.size() > 30)
        throw std::invalid_argument("Endereco deve ter entre 5 e 30 caracteres.");

    for (size_t i = 0; i < v.size(); ++i) {
        // Criação de variável para comparação na validação
        char c = v[i];
        
        // Caracteres devem ser alphanuméricos, virgulas, pontos ou espaços
        if (!isalnum(c) && c != ',' && c != '.' && c != ' ')
            throw std::invalid_argument("Endereco contem caractere invalido.");

        // Valida-se os caracteres iniciais/finais são alphanuméricos
        // (Ajustei levemente sua lógica do 'endereco[0]' para 'i == 0' para garantir que funcione corretamente)
        if ((c == ',' || c == '.' || c == ' ') && (i == v.size() - 1))
             throw std::invalid_argument("Endereco nao pode terminar com ponto, virgula ou espaco.");
        
        if ((c == ',' || c == '.' || c == ' ') && (i == 0))
             throw std::invalid_argument("Endereco nao pode comecar com ponto, virgula ou espaco.");

        // Valida-se os caracteres especiais aceitos estão seguidos conforme as regras estabelecidas
        // Verifica se i+1 existe antes de acessar para evitar erro de memória, embora seu loop garanta i < size
        if (i < v.size() - 1) {
            if ((c == ',' && (v[i + 1] == ',' || v[i + 1] == '.')) ||
                (c == '.' && (v[i + 1] == ',' || v[i + 1] == '.')) ||
                (c == ' ' && (v[i + 1] == ',' || v[i + 1] == '.'))) {
                throw std::invalid_argument("Sequencia de pontuacao invalida no endereco.");
            }
        }
    }
}

void Endereco::setValor(std::string v) {
    validar(v);
    this->valor = v;
}

// Telefone
void Telefone::validar(std::string v) {
    // Valida se a quantidade de caracteres é 14
    if (v.size() != 14) {
        throw std::invalid_argument("Telefone deve ter 14 caracteres.");
    }
    // Primeiro elemento de telefone deve ser '+'
    if (v[0] != '+'){
        throw std::invalid_argument("Telefone deve iniciar com '+'");
    }
    // Valida se o telefone é composto apenas por números (com exceção do primeiro elemento)
    for (size_t i = 1; i < v.size(); ++i) {
        if (!isdigit(v[i])) {
            throw std::invalid_argument("Telefone deve conter apenas dígitos apos o '+'.");
        }
    }
}

void Telefone::setValor(std::string v) {
    validar(v);
    this->valor = v;
}

// Código
void Codigo::validar(std::string v) {
    // Quantidade de caracteres é 10
    if (v.size() != 10)
        throw std::invalid_argument("Codigo deve ter exatamente 10 caracteres.");

    for (char c : v){
        // Valida se os caracteres do código são alphanuméricos
        if (!isalnum(c)){
            throw std::invalid_argument("Codigo deve ser alfanumerico.");
        }
        // Valida se não tem nenhuma maiuscula
        if (isupper(c)){
            throw std::invalid_argument("Codigo nao pode ter letras maiusculas.");
        }
    }
}

void Codigo::setValor(std::string v) {
    validar(v);
    this->valor = v;
}

// Número
void Numero::validar(std::string v) {
    //Verifica se a quantidade de caracteres é 3
    if (v.size() != 3) 
        throw std::invalid_argument("Numero do quarto deve ter exatamente 3 digitos.");

    // Todos os caracteres devem ser dígitos
    for (char c : v) {
        if (!isdigit(c)) 
            throw std::invalid_argument("Numero do quarto deve conter apenas digitos.");
    }

    // Como tem 3 dígitos, comparação lexicográfica é segura e correta
    if (v < "001" || v > "999")
        throw std::invalid_argument("Numero do quarto deve estar entre 001 e 999.");
}

void Numero::setValor(std::string v) {
    validar(v);
    this->valor = v;
}

// Capacidade
void Capacidade::validar(int v) {
    // Capacidade somente 1 a 4
    if (v < 1 || v > 4) {
        throw std::invalid_argument("Capacidade deve ser 1, 2, 3 ou 4.");
    }
}

void Capacidade::setValor(int v) {
    validar(v);
    this->valor = v;
}

// Dinheiro
void Dinheiro::validar(int v) {
    // Diária armazenada em centavos:
    // Mínimo 0.01 -> 1 centavo
    // Máximo 1.000.000,00 -> 100.000.000 centavos
    if (v < 1 || v > 100000000) {
        throw std::invalid_argument("Valor deve estar entre 0,01 e 1.000.000,00 reais.");
    }
}

void Dinheiro::setValor(int v) {
    validar(v);
    this->valor = v;
}

// Ramal
void Ramal::validar(std::string v) {
    //Verifica se a quantidade de caracteres é 2
    if (v.size() != 2) 
        throw std::invalid_argument("Ramal deve ter exatos 2 digitos.");
    //Verifica se são dígitos
    for (char c : v) {
        if (!isdigit(c)) 
            throw std::invalid_argument("Ramal deve conter apenas digitos.");
    }

    // Comparação lexicográfica
    if (v < "00" || v > "50")
        throw std::invalid_argument("Ramal deve estar entre 00 e 50.");
}

void Ramal::setValor(std::string v) {
    validar(v);
    this->valor = v;
}

// Cartão
void Cartao::validar(std::string v) {
    // Verifica se tem 16 caracteres
    if (v.length() != 16) {
        throw std::invalid_argument("Cartao deve ter exatamente 16 digitos.");
    }

    // Verifica se contém apenas dígitos
    for (size_t i = 0; i < v.length(); ++i) {
        if (!isdigit(v[i])) {
            throw std::invalid_argument("Cartao deve conter apenas digitos.");
        }
    }

    // Algoritmo de Luhn
    int soma = 0;
    bool dobrar = false; // Começamos do último dígito (que é o verificador), então não dobramos o primeiro

    // Percorre a string de trás para frente
    for (int i = 15; i >= 0; --i) {
        // Converte char para int ('0' -> 0, '9' -> 9)
        int digito = v[i] - '0';

        if (dobrar) {
            digito = digito * 2;
            if (digito > 9) {
                digito = digito - 9;
            }
        }

        soma += digito;
        dobrar = !dobrar; // Alterna entre dobrar e não dobrar
    }

    // Se o módulo da soma por 10 NÃO for 0, o cartão é inválido
    if (soma % 10 != 0) {
        throw std::invalid_argument("Numero de cartao invalido (falha na verificacao Luhn).");
    }
}

void Cartao::setValor(std::string v) {
    validar(v);
    this->valor = v;
}

//Data
void Data::validar(std::string v) {
    // Validação de Formato
    if (v.size() != 11) 
        throw std::invalid_argument("Data deve ter o formato DD-MMM-AAAA (11 caracteres).");

    if (v[2] != '-' || v[6] != '-') 
        throw std::invalid_argument("Data deve ter hifens na posicao 3 e 7.");

    //Divisão da data em dia, mês e ano
    std::string diaStr = v.substr(0, 2);
    std::string mesStr = v.substr(3, 3);
    std::string anoStr = v.substr(7, 4);

    // Conversão de string para int para comparação
    int dia = converterStringParaInt(diaStr);
    int ano = converterStringParaInt(anoStr);

    // Verificação se o ano digitado está no intervalo aceito
    if (ano < 2000 || ano > 2999) 
        throw std::invalid_argument("Ano deve estar entre 2000 e 2999.");

    // Validação do Mês
    //Vetor contendo os valores aceitos
    std::vector<std::string> meses;
    meses.push_back("JAN"); meses.push_back("FEV"); meses.push_back("MAR");
    meses.push_back("ABR"); meses.push_back("MAI"); meses.push_back("JUN");
    meses.push_back("JUL"); meses.push_back("AGO"); meses.push_back("SET");
    meses.push_back("OUT"); meses.push_back("NOV"); meses.push_back("DEZ");

    int indiceMes = -1;
    for (size_t i = 0; i < meses.size(); ++i) {
        if (meses[i] == mesStr) {
            indiceMes = (int)i;
            break;
        }
    }
    //Caso do mês digitado não ser encontrato
    if (indiceMes == -1) {
        throw std::invalid_argument("Mês inválido. Verifique a grafia (ex: JAN, FEV...).");
    }

    // Dias por mês
    int diasNoMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Ajuste para anos bissextos
    if (indiceMes == 1) { // Fevereiro
        // Regra clássica: div por 4 E (não div por 100 OU div por 400)
        bool bissexto = (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
        if (bissexto) {
            diasNoMes[1] = 29;
        }
    }

    // Validação do dia com relação ao mês
    if (dia < 1 || dia > diasNoMes[indiceMes]) {
        throw std::invalid_argument("Dia invalido para o mes informado.");
    }
}

void Data::setValor(std::string v) {
    validar(v);
    this->valor = v;
}

// Senha
void Senha::validar(std::string v) {
    // Confirma se o tamanho é de 5 caracteres
    if (v.size() != 5) {
        throw std::invalid_argument("Senha deve ter exatamente 5 caracteres.");
    }

    // Definição dos caracteres especiais permitidos
    std::string especiais = "!\"#$%&?";
    
    // Flags para verificar a presença de cada tipo
    bool temMaiuscula = false;
    bool temMinuscula = false;
    bool temDigito = false;
    bool temEspecial = false;

    for (size_t i = 0; i < v.size(); ++i) {
        char c = v[i];

        // Verifica o tipo do caracter atual
        bool ehLetra = isalpha(c);
        bool ehDigito = isdigit(c);
        bool ehEspecial = false;
        
        // Verificação se é um dos caracteres especiais permitidos
        for (char esp : especiais) {
            if (c == esp) {
                ehEspecial = true;
                break;
            }
        }

        // Validação se é um caractere válido
        if (!ehLetra && !ehDigito && !ehEspecial) {
            throw std::invalid_argument("Senha contem caractere invalido.");
        }

        // Atualiza as flags de composição
        if (isupper(c)) temMaiuscula = true;
        if (islower(c)) temMinuscula = true;
        if (ehDigito) temDigito = true;
        if (ehEspecial) temEspecial = true;

        // Verifica se as regras especiais de letra e dígito estão sendo respeitadas
        if (i > 0) {
            char anterior = v[i-1];
            
            // Letra seguida de letra
            if (isalpha(anterior) && ehLetra) {
                throw std::invalid_argument("Senha invalida: letra nao pode ser seguida por letra.");
            }

            // Dígito seguido de dígito
            if (isdigit(anterior) && ehDigito) {
                throw std::invalid_argument("Senha invalida: digito nao pode ser seguido por digito.");
            }
        }
    }

    // Confirma se tem todos os tipos de caracteres solicitados
    if (!temMaiuscula || !temMinuscula || !temDigito || !temEspecial) {
        throw std::invalid_argument("Senha deve conter pelo menos uma maiuscula, uma minuscula, um digito e um especial.");
    }
}

void Senha::setValor(std::string v) {
    validar(v);
    this->valor = v;
}

// Email
void Email::validar(std::string v) {
    // Verifica formato básico e separa as partes
    size_t posArroba = v.find('@');
    if (posArroba == std::string::npos) {
        throw std::invalid_argument("Email deve conter @.");
    }
    // Não pode começar ou terminar com @
    if (posArroba == 0 || posArroba == v.size() - 1) {
        throw std::invalid_argument("Email inválido (posicao do @).");
    }

    std::string parteLocal = v.substr(0, posArroba);
    std::string dominio = v.substr(posArroba + 1);

    // VALIDAÇÃO DA PARTE LOCAL
    // Comprimento máximo é 64 caracteres
    if (parteLocal.size() > 64) {
        throw std::invalid_argument("Parte local do email excede 64 caracteres.");
    }

    // Não pode iniciar ou terminar com ponto ou hífen
    if (parteLocal.front() == '.' || parteLocal.front() == '-' || 
        parteLocal.back() == '.' || parteLocal.back() == '-') {
        throw std::invalid_argument("Parte local nao pode iniciar ou terminar com ponto ou hifen.");
    }

    for (size_t i = 0; i < parteLocal.size(); ++i) {
        char c = parteLocal[i];

        bool ehAlfanumerico = isalnum(c);
        bool ehPontoOuHifen = (c == '.' || c == '-');

        // Verifica se tem apenas os caracteres permitidos: letra (a-z), dígito (0-9) ou ponto(.) ou hífen (-)
        if (!ehAlfanumerico && !ehPontoOuHifen) {
            throw std::invalid_argument("Parte local contem caractere inválido.");
        }

        // Regra: ponto ou hífen deve ser seguido por letra(s) ou dígito(s)
        if (ehPontoOuHifen) {
            if (!isalnum(parteLocal[i + 1])) {
                throw std::invalid_argument("Ponto ou hifen na parte local deve ser seguido por letra ou digito.");
            }
        }
    }

    // VALIDAÇÃO DO DOMÍNIO

    // Comprimento máximo é 255 caracteres
    if (dominio.size() > 255) {
        throw std::invalid_argument("Dominio do email excede 255 caracteres.");
    }

    std::string parteAtual;
    
    // Adiciona um ponto virtual ao final para processar a última parte no loop
    std::string dominioProcessar = dominio + '.'; 

    for (size_t i = 0; i < dominioProcessar.size(); ++i) {
        char c = dominioProcessar[i];

        if (c == '.') {
            // Fim de uma parte. Vamos validar a 'parteAtual'.
            
            // Se parte vazia, significa pontos consecutivos (ex: a..b) ou ponto no inicio/fim original
            if (parteAtual.empty()) {
                throw std::invalid_argument("Domínio pontos consecutivos ou mal posicionados");
            }

            // Não pode iniciar ou terminar com hífen
            if (parteAtual.front() == '-' || parteAtual.back() == '-') {
                throw std::invalid_argument("Parte do domínio não pode iniciar ou terminar com hifen.");
            }

            // Validar caracteres da parte
            for (char cp : parteAtual) {
                // cada parte pode conter letra (a-z), dígito (0-9) ou hífen (-)
                if (!isalnum(cp) && cp != '-') {
                    throw std::invalid_argument("Domínio contem caractere inválido.");
                }
            }

            // Limpa para a próxima parte
            parteAtual = "";
        } else {
            parteAtual += c;
        }
    }
}

void Email::setValor(std::string v) {
    validar(v);
    this->valor = v;
}

// Criação de hotel
void Gerente::criarHotel() {
    std::string nome, endereco, telefone, codigo;

    std::cout << "\nCriar Hotel" << std::endl;

    //Objeto temporário para validações
    Hotel hotelTemporario;

    //Nome
    do {
        std::cout << "Nome do hotel: ";
        std::getline(std::cin >> std::ws, nome);
        if (!hotelTemporario.validarNome(nome)) {
            std::cerr << "Erro ao criar hotel: nome inválido.\n";
            std::cerr << "Informe um novo nome (5 a 20 caracteres, letras e espaços, "
                      << "primeira letra de cada termo deve ser maiúscula, sem espaço final).\n";
        }
    } while (!hotelTemporario.validarNome(nome));

    //Endereço
    do {
        std::cout << "Endereço: ";
        std::getline(std::cin, endereco);
        if (!hotelTemporario.validarEndereco(endereco)) {
            std::cerr << "Erro ao criar hotel: endereço inválido.\n";
            std::cerr << "Informe um novo endereço (5 a 30 caracteres; letras, dígitos, vírgula, ponto e espaço são aceitos; "
                      << "sem vírgulas, pontos ou espaços consecutivos; sem começar/terminar com vírgula, ponto ou espaço).\n";
        }
    } while (!hotelTemporario.validarEndereco(endereco));

    //Telefone
    do {
        std::cout << "Telefone (+DDDDNXXXXXXXX): ";
        std::getline(std::cin, telefone);
        if (!hotelTemporario.validarTelefone(telefone)) {
            std::cerr << "Erro ao criar hotel: telefone inválido.\n";
            std::cerr << "Informe um novo telefone válido (ex: +5511999999999).\n";
        }
    } while (!hotelTemporario.validarTelefone(telefone));

    //Código
    do {
        std::cout << "Código (10 caracteres alfanuméricos): ";
        std::getline(std::cin, codigo);
        if (!hotelTemporario.validarCodigo(codigo)) {
            std::cerr << "Erro ao criar hotel: código inválido.\n";
            std::cerr << "Informe um novo código com exatamente 10 caracteres (letras minúsculas ou números).\n";
        }
    } while (!hotelTemporario.validarCodigo(codigo));

    //Criação final
    Hotel novoHotel(nome, endereco, telefone, codigo, this);
    hoteis.push_back(novoHotel);

    std::cout << "\nHotel '" << novoHotel.getNome()
              << "' criado e associado ao gerente '" << getNome()
              << "' com sucesso!\n";
}

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
//Criar hóspede
void Gerente::criarHospede() {
    std::string nome, email, endereco, cartao;

    std::cout << "\nCriar Hospede" << std::endl;

    Hospede hospedeTemporario;

    //Nome
    do {
        std::cout << "Nome do hospede: ";
        std::getline(std::cin >> std::ws, nome);
        
        if (!hospedeTemporario.validarNome(nome)) {
            std::cerr << "Erro: Nome inválido.\n";
            std::cerr << "Regra: 5 a 20 caracteres, apenas letras e espaços, iniciais maiúsculas.\n";
        }
    } while (!hospedeTemporario.validarNome(nome));

    // Email
    do {
        std::cout << "Email: ";
        std::getline(std::cin, email);

        if (!hospedeTemporario.validarEmail(email)) {
            std::cerr << "Erro: Email inválido.\n";
        }
    } while (!hospedeTemporario.validarEmail(email));

    // Endereço
    do {
        std::cout << "Endereço: ";
        std::getline(std::cin, endereco);

        if (!hospedeTemporario.validarEndereco(endereco)) {
            std::cerr << "Erro: Endereço inválido.\n";
            std::cerr << "Regras:\n"
                      << " - Entre 5 e 30 caracteres.\n"
                      << " - Apenas letras, dígitos, vírgula, ponto e espaço.\n"
                      << " - Sem pontuação consecutiva (ex: ',,', ' .').\n"
                      << " - Não pode começar ou terminar com pontuação/espaço.\n";
        }
    } while (!hospedeTemporario.validarEndereco(endereco));

    //Cartão
    do {
        std::cout << "Cartão de Crédito (16 dígitos): ";
        std::getline(std::cin, cartao);

        if (!hospedeTemporario.validarCartao(cartao)) {
            std::cerr << "Erro: Cartão inválido.\n";
            std::cerr << "Regras:\n"
                      << " - Deve conter exatamente 16 dígitos numéricos.\n"
                      << " - Deve ser válido segundo o algoritmo de Luhn.\n";
        }
    } while (!hospedeTemporario.validarCartao(cartao));

    // Criação final do objeto e adição ao vetor
    Hospede novoHospede(nome, email, endereco, cartao);
    
    // Adiciona ao vetor de hóspedes da classe Gerente
    hospedes.push_back(novoHospede); 

    std::cout << "\nHospede '" << novoHospede.getNome() 
              << "' cadastrado com sucesso!\n";
}

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


//RESERVAS
//Criar reserva
void Gerente::criarReserva() {
    std::cout << "\nCriar Reserva\n";

    // Verificações iniciais
    if (hoteis.empty()) {
        std::cerr << "Nenhum hotel cadastrado.\n";
        return;
    }

    if (hospedes.empty()) {
        std::cerr << "Nenhum hóspede cadastrado.\n";
        return;
    }

    // Seleção de hotel
    std::string codigoHotel;
    Hotel* hotel = nullptr;
    listarHoteis();

    while (true) {
        std::cout << "\nInforme o código do hotel (ou ENTER para cancelar): ";
        std::getline(std::cin >> std::ws, codigoHotel);

        if (codigoHotel.empty()) {
            std::cout << "Operação cancelada.\n";
            return;
        }

        hotel = buscarHotelPorCodigo(codigoHotel);
        if (hotel) break;

        std::cerr << "Código inválido. Tente novamente.\n";
    }

    if (hotel->getQuartos().empty()) {
        std::cerr << "Este hotel não possui quartos cadastrados.\n";
        return;
    }

    hotel->listarQuartos();

    // Seleção de hóspede
    std::string nomeHospede;
    Hospede* hospedeSelecionado = nullptr;
    listarHospedes();

    while (true) {
        std::cout << "\n\nInforme o nome do hospede para reserva (ou ENTER para cancelar): ";
        std::getline(std::cin >> std::ws, nomeHospede);

        if (nomeHospede.empty()) {
            std::cout << "Operação cancelada.\n";
            return;
        }

        // busca no vetor usando iterator
        for (std::vector<Hospede>::iterator it = hospedes.begin();
            it != hospedes.end();
            it++)
        {
            if (it->getNome() == nomeHospede) {
                hospedeSelecionado = &(*it);
                break;
            }
        }

        if (hospedeSelecionado) break;

        std::cerr << "Hóspede não encontrado. Tente novamente.\n";
    }


    // Verificar se já existe reserva
    if (quarto->getReserva() != nullptr) {
        std::cerr << "Erro: este quarto já possui uma reserva ativa.\n";
        return;
    }

    // DATA DE CHEGADA
    int diaC, anoC;
    std::string mesC;

    do {
        std::cout << "\nDia de chegada (1-31): ";
        std::cin >> diaC;
    } while (!validarDia(diaC));

    do {
        std::cout << "Mês de chegada (JAN/FEV/.../DEZ): ";
        std::cin >> mesC;
    } while (!validarMes(mesC) || !validarDiaMesAno(diaC, mesC, 2024));

    do {
        std::cout << "Ano de chegada (2000-2999): ";
        std::cin >> anoC;
    } while (!validarAno(anoC) || !validarDiaMesAno(diaC, mesC, anoC));

    std::string chegada = montarDataFinal(diaC, mesC, anoC);


    // DATA DE PARTIDA
    int diaP, anoP;
    std::string mesP;

    do {
        std::cout << "\nDia de partida (1-31): ";
        std::cin >> diaP;
    } while (!validarDia(diaP));

    do {
        std::cout << "Mês de partida (JAN/FEV/.../DEZ): ";
        std::cin >> mesP;
    } while (!validarMes(mesP));

    do {
        std::cout << "Ano de partida (2000-2999): ";
        std::cin >> anoP;
    } while (!validarAno(anoP));

    if (!validarDiaMesAno(diaP, mesP, anoP)) {
        std::cerr << "Data de partida inválida.\n";
        return;
    }

    std::string partida = montarDataFinal(diaP, mesP, anoP);

    // GARANTIR CHEGADA < PARTIDA
    // ==========================================================
    auto converterMes = [](const std::string& mes) {
        static std::map<std::string, int> tabela = {
            {"JAN",1},{"FEV",2},{"MAR",3},{"ABR",4},{"MAI",5},{"JUN",6},
            {"JUL",7},{"AGO",8},{"SET",9},{"OUT",10},{"NOV",11},{"DEZ",12}
        };
        return tabela.at(mes);
    };

    int mesCNum = converterMes(mesC);
    int mesPNum = converterMes(mesP);

    if (anoP < anoC ||
       (anoP == anoC && mesPNum < mesCNum) ||
       (anoP == anoC && mesPNum == mesCNum && diaP <= diaC)) {
        std::cerr << "Erro: data de partida deve ser depois da chegada.\n";
        return;
    }

    // ==========================================================
    // CÁLCULO DE DIAS E VALOR FINAL
    // ==========================================================
    int chegadaAbs = anoC*360 + mesCNum*30 + diaC;
    int partidaAbs = anoP*360 + mesPNum*30 + diaP;
    int dias = partidaAbs - chegadaAbs;

    int valorFinal = quarto->getDiaria() * dias;
    if (valorFinal <= 0) {
        std::cerr << "Erro interno no cálculo do valor.\n";
        return;
    }

    // ==========================================================
    // CÓDIGO DA RESERVA
    // ==========================================================
    std::string codigoReserva;
    Reserva temp;

    do {
        std::cout << "Código da reserva (10 caracteres): ";
        std::getline(std::cin >> std::ws, codigoReserva);
    } while (!temp.validarCodigo(codigoReserva));

    // ==========================================================
    // CRIAÇÃO FINAL DA RESERVA
    // ==========================================================
    Reserva* nova = new Reserva(chegada, partida, valorFinal, codigoReserva);
    nova->setHospede(hospedeSelecionado);
    nova->setQuarto(quarto);

    quarto->associarReserva(nova);

    std::cout << "\nReserva criada com sucesso!\n";
}


void Gerente::editarReserva() {
    cout << "\n=== Editar Reserva ===" << endl;
    cout << "Funcionalidade pendente.\n";
}

void Gerente::excluirReserva() {
    cout << "\n=== Excluir Reserva ===" << endl;
    cout << "Funcionalidade pendente.\n";
}

void Gerente::listarReservas() {
    cout << "\n=== Listar Reservas ===" << endl;
    cout << "Funcionalidade pendente (requer lista global de reservas).\n";
}

//Conta do gerente
void Gerente::lerConta() {
    cout << "\n=== Dados da Conta ===" << endl;
    cout << "Nome: " << getNome() << endl;
    cout << "Email: " << getEmail() << endl;
    cout << "Ramal: " << ramal << endl;
}

void Gerente::editarConta() {
    cout << "\n=== Editar Conta ===" << endl;
    cout << "Funcionalidade de edicao simples.\n";
    cout << "Nova senha: ";
    string novaSenha;
    getline(cin >> ws, novaSenha);

    if (validarSenha(novaSenha)) {
        setSenha(novaSenha);
        cout << "Senha atualizada com sucesso!\n";
    } else {
        cout << "Senha invalida. Nao foi atualizada.\n";
    }
}

void Gerente::excluirConta() {
    cout << "\n=== Excluir Conta ===" << endl;
    cout << "Conta excluida logicamente (em um sistema real, removeria o gerente).\n";
}

//Validações do Gerente
bool Gerente::validarSenha(const string& senha) const {
    // Regra: 5 caracteres, alternando entre letra e numero, contendo
    // 1 minúscula, 1 maiúscula, 1 dígito e 1 caractere especial (!"#$%&?)
    if (senha.size() != 5)
        return false;

    bool temMinuscula = false, temMaiuscula = false, temNumero = false, temEspecial = false;
    string especiais = "!\"#$%&?";

    for (size_t i = 0; i < senha.size(); ++i) {
        char c = senha[i];
        if (islower(c)) temMinuscula = true;
        else if (isupper(c)) temMaiuscula = true;
        else if (isdigit(c)) temNumero = true;
        else if (especiais.find(c) != string::npos) temEspecial = true;

        if (i > 0) {
            bool ambosLetras = isalpha(c) && isalpha(senha[i-1]);
            bool ambosNumeros = isdigit(c) && isdigit(senha[i-1]);
            if (ambosLetras || ambosNumeros) return false;
        }
    }

    return temMinuscula && temMaiuscula && temNumero && temEspecial;
}