#include <iostream>
#include "dominios.hpp"
#include "entidades.hpp"
#include "interfaces.hpp"
#include "containers.hpp"
#include "controladoras.hpp"

using namespace std;

int main() {
    // Instanciações das classes serviço
    ContainerGerente containerGerente;
    ContainerHotel containerHotel;
    ContainerQuarto containerQuarto;
    ContainerHospede containerHospede;
    ContainerReserva containerReserva;

    // Instaciações das classes de apresentação
    CntrApresentacaoGerente cntrGerente;
    CntrApresentacaoHotel cntrHotel;
    CntrApresentacaoQuarto cntrQuarto;
    CntrApresentacaoHospede cntrHospede;
    CntrApresentacaoReserva cntrReserva;

    // Associação da camada de apresentação com de serviço
    cntrGerente.setServicoGerente(&containerGerente);
    
    cntrHotel.setServicoHotel(&containerHotel);
    
    cntrQuarto.setServicoQuarto(&containerQuarto);
    cntrQuarto.setServicoHotel(&containerHotel);
    
    cntrHospede.setServicoHospede(&containerHospede);
    
    cntrReserva.setServicoReserva(&containerReserva);
    cntrReserva.setServicoQuarto(&containerQuarto);
    cntrReserva.setServicoHospede(&containerHospede);
    cntrReserva.setServicoHotel(&containerHotel);

    //Fluxo do programa
    Gerente* gerenteLogado = nullptr;

    while (true) {
        if (gerenteLogado == nullptr) {
            //Tela inicial para cadastro/login/saída
            int opcao;
            cout << "\n SISTEMA HOTELEIRO \n";
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
            // Tela logada
            int opcao;
            cout << "\nMENU PRINCIPAL (" << gerenteLogado->getNome().getValor() << ")\n";
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
                    cntrQuarto.criarQuarto();
                    break;
                case 3: // SUBMENU HOSPEDE
                    cntrHospede.criarHospede();
                    break;
                case 4: // SUBMENU RESERVA
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