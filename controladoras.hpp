#ifndef CONTROLADORAS_HPP
#define CONTROLADORAS_HPP

#include "interfaces.hpp"
#include "dominios.hpp"
#include "entidades.hpp"

// Gerente
class CntrApresentacaoGerente {
private:
    IServicoGerente* servicoGerente;
public:
    void setServicoGerente(IServicoGerente* servico) { servicoGerente = servico; }
    void criarConta();
    void editarConta(Gerente* logado);
    void excluirConta(Gerente*& logado);
    Gerente* autenticar();
};

// Hotel
class CntrApresentacaoHotel {
private:
    IServicoHotel* servicoHotel;
public:
    void setServicoHotel(IServicoHotel* servico) { servicoHotel = servico; }
    void criarHotel(Gerente* logado);
    void listarHoteis(Gerente* gerenteLogado); // MODIFIED
    void editar(Gerente* logado);
    void excluir(Gerente* logado);
};

// Quarto
class CntrApresentacaoQuarto {
private:
    IServicoQuarto* servicoQuarto;
    IServicoHotel* servicoHotel; // Necessario para associar o quarto a um hotel existente
public:
    void setServicoQuarto(IServicoQuarto* sQuarto) { servicoQuarto = sQuarto; }
    void setServicoHotel(IServicoHotel* sHotel) { servicoHotel = sHotel; }
    
    void criarQuarto(Gerente* gerenteLogado); // MODIFIED
    void listarQuartos(Gerente* gerenteLogado); // MODIFIED
    void editarQuarto(Gerente* gerenteLogado); // MODIFIED
    void excluirQuarto(Gerente* gerenteLogado); // MODIFIED
};

// Hospede
class CntrApresentacaoHospede {
private:
    IServicoHospede* servicoHospede;
public:
    void setServicoHospede(IServicoHospede* servico) { servicoHospede = servico; }
    void criarHospede();
    void editarHospedde();
    void excluirHospede();
    void listarHospedes();
};

// Reserva
class CntrApresentacaoReserva {
private:
    IServicoReserva* servicoReserva;
    IServicoQuarto* servicoQuarto;   // Para verificar disponibilidade
    IServicoHospede* servicoHospede; // Para associar hospede
    IServicoHotel* servicoHotel;     // Para selecionar hotel
public:
    void setServicoReserva(IServicoReserva* sReserva) { servicoReserva = sReserva; }
    void setServicoQuarto(IServicoQuarto* sQuarto) { servicoQuarto = sQuarto; }
    void setServicoHospede(IServicoHospede* sHospede) { servicoHospede = sHospede; }
    void setServicoHotel(IServicoHotel* sHotel) { servicoHotel = sHotel; }

    void criarReserva(Gerente* gerenteLogado); // MODIFIED
    void editarReserva(Gerente* gerenteLogado); // MODIFIED
    void listarReservas(Gerente* gerenteLogado); // MODIFIED
    void excluirReserva(Gerente* gerenteLogado); // MODIFIED
};

#endif
