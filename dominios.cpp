#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include "dominios.hpp"

using namespace std;

// FUNÇÕES AUXILIARES
static int converterStringParaInt(const std::string& s) {
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
            throw std::invalid_argument("Telefone deve conter apenas digitos apos o '+'");
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
    bool dobrar = false;

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

    // Se o módulo da soma por 10 não for 0, o cartão é inválido
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
        throw std::invalid_argument("Mes invalido. Verifique a grafia (ex: JAN, FEV...).");
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
        throw std::invalid_argument("Email deve conter @");
    }
    // Não pode começar ou terminar com @
    if (posArroba == 0 || posArroba == v.size() - 1) {
        throw std::invalid_argument("Email invalido (posicao do @)");
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
            throw std::invalid_argument("Parte local contem caractere invalido.");
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
                throw std::invalid_argument("Dominio pontos consecutivos ou mal posicionados");
            }

            // Não pode iniciar ou terminar com hífen
            if (parteAtual.front() == '-' || parteAtual.back() == '-') {
                throw std::invalid_argument("Parte do dominio nao pode iniciar ou terminar com hifen.");
            }

            // Validar caracteres da parte
            for (char cp : parteAtual) {
                // cada parte pode conter letra (a-z), dígito (0-9) ou hífen (-)
                if (!isalnum(cp) && cp != '-') {
                    throw std::invalid_argument("Dominio contem caractere invalido.");
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