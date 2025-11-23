#include <iostream>
#include "dominios.hpp"
#include "entidades.hpp"
#include "interfaces.hpp"
#include "containers.hpp"   // Camada de Serviço (Implementação)
#include "controladoras.hpp" // Camada de Apresentação

using namespace std;

int main() {
    // 1. INSTANCIAR A CAMADA DE SERVIÇO (BANCO DE DADOS EM MEMÓRIA)
    ContainerGerente containerGerente;
    ContainerHotel containerHotel;
    ContainerQuarto containerQuarto;
    ContainerHospede containerHospede;
    ContainerReserva containerReserva;

    // 2. INSTANCIAR A CAMADA DE APRESENTAÇÃO (CONTROLADORAS)
    CntrApresentacaoGerente cntrGerente;
    CntrApresentacaoHotel cntrHotel;
    CntrApresentacaoQuarto cntrQuarto;
    CntrApresentacaoHospede cntrHospede;
    CntrApresentacaoReserva cntrReserva;

    // 3. INJEÇÃO DE DEPENDÊNCIA (LIGAR APRESENTAÇÃO -> SERVIÇO)
    cntrGerente.setServicoGerente(&containerGerente);
    
    cntrHotel.setServicoHotel(&containerHotel);
    
    cntrQuarto.setServicoQuarto(&containerQuarto);
    cntrQuarto.setServicoHotel(&containerHotel); // Quarto precisa saber dos Hoteis
    
    cntrHospede.setServicoHospede(&containerHospede);
    
    cntrReserva.setServicoReserva(&containerReserva);
    cntrReserva.setServicoQuarto(&containerQuarto);
    cntrReserva.setServicoHospede(&containerHospede);
    cntrReserva.setServicoHotel(&containerHotel);

    // 4. FLUXO PRINCIPAL DO PROGRAMA
    Gerente* gerenteLogado = nullptr;

    while (true) {
        if (gerenteLogado == nullptr) {
            // --- TELA DE LOGIN / CADASTRO ---
            int opcao;
            cout << "\n### SISTEMA HOTELEIRO - BEM VINDO ###\n";
            cout << "1. Login\n";
            cout << "2. Cadastrar Novo Gerente\n";
            cout << "0. Sair\n";
            cout << "Escolha: ";
            cin >> opcao;

            if (opcao == 0) break;
            else if (opcao == 1) {
                gerenteLogado = cntrGerente.autenticar();
            }
            else if (opcao == 2) {
                cntrGerente.criarConta();
            }
        } 
        else {
            // --- TELA LOGADA ---
            int opcao;
            cout << "\n### MENU PRINCIPAL (" << gerenteLogado->getNome().getValor() << ") ###\n";
            cout << "1. Gerenciar Hoteis\n";
            cout << "2. Gerenciar Quartos\n";
            cout << "3. Gerenciar Hospedes\n";
            cout << "4. Gerenciar Reservas\n";
            cout << "5. Logout\n";
            cout << "Escolha: ";
            cin >> opcao;

            switch(opcao) {
                case 1: // SUBMENU HOTEL
                    cout << "1. Criar Hotel | 2. Listar Hoteis | 0. Voltar: ";
                    int opHotel; cin >> opHotel;
                    if (opHotel == 1) cntrHotel.criarHotel(gerenteLogado);
                    else if (opHotel == 2) cntrHotel.listarHoteis();
                    break;
                case 2: // SUBMENU QUARTO
                    cntrQuarto.criarQuarto(); // Adapte para ter submenu igual ao hotel
                    break;
                case 3:
                    cntrHospede.criarHospede();
                    break;
                case 4:
                    cntrReserva.criarReserva();
                    break;
                case 5:
                    gerenteLogado = nullptr; // Logout
                    break;
            }
        }
    }

    return 0;
}