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
    void excluirConta(Gerente* logado);
    Gerente* autenticar();
};

// Hotel
class CntrApresentacaoHotel {
private:
    IServicoHotel* servicoHotel;
public:
    void setServicoHotel(IServicoHotel* servico) { servicoHotel = servico; }
    void criarHotel(Gerente* logado);
    void listarHoteis();
    void editar(Gerente* logado);
    void excluir(Gerente* logado);
};

// Quarto
class CntrApresentacaoQuarto {
private:
    IServicoQuarto* servicoQuarto;
    IServicoHotel* servicoHotel; // Necessário para associar o quarto a um hotel existente
public:
    void setServicoQuarto(IServicoQuarto* sQuarto) { servicoQuarto = sQuarto; }
    void setServicoHotel(IServicoHotel* sHotel) { servicoHotel = sHotel; }
    
    void criarQuarto();
    void listarQuartos();
    void editarQuarto();
    void excluirQuarto();
};

// Hóspede
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
    IServicoHospede* servicoHospede; // Para associar hóspede
    IServicoHotel* servicoHotel;     // Para selecionar hotel
public:
    void setServicoReserva(IServicoReserva* sReserva) { servicoReserva = sReserva; }
    void setServicoQuarto(IServicoQuarto* sQuarto) { servicoQuarto = sQuarto; }
    void setServicoHospede(IServicoHospede* sHospede) { servicoHospede = sHospede; }
    void setServicoHotel(IServicoHotel* sHotel) { servicoHotel = sHotel; }

    void criarReserva();
    void editarReserva();
    void listarReservas();
    void excluirReserva();
};

#endif