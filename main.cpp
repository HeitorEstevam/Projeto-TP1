#include <iostream>
#include <limits> // Added
#include "dominios.hpp"
#include "entidades.hpp"
#include "interfaces.hpp"
#include "containers.hpp"
#include "controladoras.hpp"

using namespace std;

int main() {

    // 1. INSTANCIAR A CAMADA DE SERVIÇO (BANCO DE DADOS EM MEMÓRIA)
    // Instanciar ContainerReserva primeiro, pois é uma dependência
    ContainerReserva containerReserva;
    // Instanciar ContainerQuarto e ContainerHospede, passando containerReserva
    ContainerQuarto containerQuarto(&containerReserva);
    ContainerHospede containerHospede(&containerReserva);
    // Instanciar ContainerHotel, passando containerQuarto e containerReserva
    ContainerHotel containerHotel(&containerQuarto, &containerReserva);
    // ContainerGerente não tem dependências de outros serviços
    ContainerGerente containerGerente;

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

            cout << "\n MENU PRINCIPAL (" << gerenteLogado->getNome().getValor() << ")\n";
            cout << "1. Gerenciar minha Conta\n";
            cout << "2. Gerenciar Hoteis\n";
            cout << "3. Gerenciar Quartos\n";
            cout << "4. Gerenciar Hospedes\n";
            cout << "5. Gerenciar Reservas\n";
            cout << "0. Logout\n"; 
            cout << "Escolha: ";
            cin >> opcao;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch(opcao) {
                case 1: { // Gerenciar minha Conta
                    int opConta;
                    cout << "1. Editar Conta | 2. Excluir Conta | 0. Voltar: ";
                    cin >> opConta;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (opConta == 1) {
                        cntrGerente.editarConta(gerenteLogado);
                    } else if (opConta == 2) {
                        cntrGerente.excluirConta(gerenteLogado);
                        if (gerenteLogado == nullptr) {
                            cout << "Sua conta foi excluída. Você foi desconectado.\n";
                            break;
                        }
                    }
                    break;
                }
                case 2: { // SUBMENU HOTEL
                    int opHotel;
                    cout << "1. Criar Hotel | 2. Listar Hoteis | 3. Editar Hotel | 4. Excluir Hotel | 0. Voltar: ";
                    cin >> opHotel;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
                    if (opHotel == 1) cntrHotel.criarHotel(gerenteLogado);
                    else if (opHotel == 2) cntrHotel.listarHoteis();
                    else if (opHotel == 3) cntrHotel.editar(gerenteLogado);
                    else if (opHotel == 4) cntrHotel.excluir(gerenteLogado);
                    break;

                }
                case 3: { // SUBMENU QUARTO
                    int opQuarto;
                    cout << "1. Criar Quarto | 2. Listar Quartos | 3. Editar Quarto | 4. Excluir Quarto | 0. Voltar: ";
                    cin >> opQuarto;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (opQuarto == 1) cntrQuarto.criarQuarto();
                    else if (opQuarto == 2) cntrQuarto.listarQuartos();
                    else if (opQuarto == 3) cntrQuarto.editarQuarto();
                    else if (opQuarto == 4) cntrQuarto.excluirQuarto();
                    break;
                }
                case 4: { // SUBMENU HOSPEDE
                    int opHospede;
                    cout << "1. Criar Hospede | 2. Listar Hospedes | 3. Editar Hospede | 4. Excluir Hospede | 0. Voltar: ";
                    cin >> opHospede;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (opHospede == 1) cntrHospede.criarHospede();
                    else if (opHospede == 2) cntrHospede.listarHospedes();
                    else if (opHospede == 3) cntrHospede.editarHospedde();
                    else if (opHospede == 4) cntrHospede.excluirHospede();
                    break;
                }
                case 5: { // SUBMENU RESERVA
                    int opReserva;
                    cout << "1. Criar Reserva | 2. Listar Reservas | 3. Editar Reserva | 4. Excluir Reserva | 0. Voltar: ";
                    cin >> opReserva;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (opReserva == 1) cntrReserva.criarReserva();
                    else if (opReserva == 2) cntrReserva.listarReservas();
                    else if (opReserva == 3) cntrReserva.editarReserva();
                    else if (opReserva == 4) cntrReserva.excluirReserva();
                    break;
                }
                case 0:
                    gerenteLogado = nullptr; // Logout
                    break;
            }
        }
    }

    return 0;
}