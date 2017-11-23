#include <time.h>
#include <fstream>
#include "ruleta.h"

Ruleta::Ruleta(Crupier crupier){
    srand(time(NULL));
    bola_ = -1;
    nBola_ = 0;
    banca_ = 1000000;
    crupier_ = crupier;
}

bool Ruleta::setBanca(int banca){
    if(banca > 0)
        banca_ = banca;
    return(banca > 0);
}

bool Ruleta::setBola(int bola){
    if(bola >= 0 && bola <= 36){
        bola_ = bola;
        nBola_++;
    }
    return(bola >= 0 && bola <= 36);
}

bool Ruleta::addJugador(Jugador jugador){
    //checks if player' DNI alredy exists
    for(std::list<Jugador>::iterator it = jugadores_.begin(); it != jugadores_.end(); ++it){
        if(it->getDNI() == jugador.getDNI())
            return false;
    }

    //enters the new player
    jugadores_.push_back(jugador);

    std::ifstream f(jugador.getDNI() + ".txt");
    if(f)
        return true;
    else{
        f.open(jugador.getDNI() + ".txt");
        f.close();
    }
    return true;
}

int Ruleta::deleteJugador(std::string dni){
    if(jugadores_.empty())
        return -1;

    //checks if player's DNI is on the list, to delete it
    for(std::list<Jugador>::iterator it = jugadores_.begin(); it != jugadores_.end(); ++it){
        if(it->getDNI() == dni){
            jugadores_.erase(it);
            return 1;
        }
    }

    //if player is not on the list
    return -2;
}

int Ruleta::deleteJugador(Jugador jugador){
    return deleteJugador(jugador.getDNI());
}

void Ruleta::escribeJugadores(std::string path){
    std::ofstream f;
    f.open(path);

    //writes all players one by one on a text file
    for(std::list<Jugador>::iterator it = jugadores_.begin(); it != jugadores_.end(); ++it)
        f << it->getDNI() << "," << it->getCodigo() << "," << it->getNombre() << ","
        << it->getApellidos() << "," << it->getDireccion() << "," << it->getLocalidad() << ","
        << it->getProvincia() << "," << it->getPais() << "," << it->getDinero() << std::endl;

    f.close();
}

void Ruleta::leeJugadores(std::string path){
    std::ifstream f;
    Jugador aux("", "");
    std::string stream;

    jugadores_.clear();

    //read text file and creates new players
    f.open(path);
    while(getline(f, stream, ',')){
        aux.setDNI(stream);

        getline(f, stream, ',');
        aux.setCodigo(stream);

        getline(f, stream, ',');
        aux.setNombre(stream);

        getline(f, stream, ',');
        aux.setApellidos(stream);

        getline(f, stream, ',');
        aux.setDireccion(stream);

        getline(f, stream, ',');
        aux.setLocalidad(stream);

        getline(f, stream, ',');
        aux.setProvincia(stream);

        getline(f, stream, ',');
        aux.setPais(stream);

        getline(f, stream, '\n');
        aux.setDinero(atoi(stream.c_str()));

        jugadores_.push_back(aux);
    }
}

void Ruleta::giraRuleta(){
    setBola(rand() % 37);
}

//TODO fix the getPremios mess
void Ruleta::getPremios(bool toRead){
    std::list<Jugador>::iterator jugadorIt;
    std::list<Apuesta>::iterator apuestaIt;

    for(jugadorIt = jugadores_.begin(); jugadorIt != jugadores_.end(); ++jugadorIt){
        //read each player's bet file if necessary
        if(toRead)
            jugadorIt->setApuestas();

        std::list<Apuesta> apuestaList = jugadorIt->getApuestas();
        for(apuestaIt = apuestaList.begin(); apuestaIt != apuestaList.end(); ++apuestaIt){
            switch(apuestaIt->tipo){
                case 1:
                    if(getBola() == stoi(apuestaIt->valor)){
                        jugadorIt->setDinero(jugadorIt->getDinero() + 35 * apuestaIt->cantidad);
                        setBanca(getBanca() - 35 * apuestaIt->cantidad);
                    }else{
                        jugadorIt->setDinero(jugadorIt->getDinero() - apuestaIt->cantidad);
                        setBanca(getBanca() + apuestaIt->cantidad);
                    }
                break;

                case 2:
                    if((colorBola(getBola()) == apuestaIt->valor) && (getBola() != 0)){
                        jugadorIt->setDinero(jugadorIt->getDinero() + apuestaIt->cantidad);
                        setBanca(getBanca() - apuestaIt->cantidad);
                    }else{
                        jugadorIt->setDinero(jugadorIt->getDinero() - apuestaIt->cantidad);
                        setBanca(getBanca() + apuestaIt->cantidad);
                    }
                break;

                case 3:
                    if(parBola(getBola()) == apuestaIt->valor && (getBola() != 0)){
                        jugadorIt->setDinero(jugadorIt->getDinero() + apuestaIt->cantidad);
                        setBanca(getBanca() - apuestaIt->cantidad);
                    }else{
                        jugadorIt->setDinero(jugadorIt->getDinero() - apuestaIt->cantidad);
                        setBanca(getBanca() + apuestaIt->cantidad);
                    }
                break;

                case 4:
                    if(posicionBola(getBola()) == apuestaIt->valor && (getBola() != 0)){
                        jugadorIt->setDinero(jugadorIt->getDinero() + apuestaIt->cantidad);
                        setBanca(getBanca() - apuestaIt->cantidad);
                    }else{
                        jugadorIt->setDinero(jugadorIt->getDinero() - apuestaIt->cantidad);
                        setBanca(getBanca() + apuestaIt->cantidad);
                    }
                break;
            }
        }
    }
}

void Ruleta::getPlayerListApuesta(std::string path){
    std::list<Jugador>::iterator jugadorIt;

    //gets the bets from each player's bet file
    for(jugadorIt = jugadores_.begin(); jugadorIt != jugadores_.end(); ++jugadorIt)       
        jugadorIt->setApuestas(path);
}

std::string Ruleta::colorBola(int bola){
    switch(bola){
        case 1:
        case 3:
        case 5:
        case 7:
        case 9:
        case 12:
        case 14:
        case 16:
        case 18:
        case 19:
        case 21:
        case 23:
        case 25:
        case 27:
        case 30:
        case 32:
        case 34:
        case 36:
            return "rojo";
        default:
            return "negro";
    }
}

std::string Ruleta::parBola(int bola){
    return ((bola % 2 == 0) ? "par" : "impar");
}

std::string Ruleta::posicionBola(int bola){
    return((bola >= 19 && bola <= 36) ? "alto" : "bajo");
}

void Ruleta::getEstadoRuleta(int &nJugadores, int &dineroTotal, int &nBola, int &dineroBanca){
    nJugadores = jugadores_.size();

    dineroTotal = 0;
    for(std::list<Jugador>::iterator jugadorIt = jugadores_.begin(); jugadorIt != jugadores_.end(); ++jugadorIt)
        dineroTotal += jugadorIt->getDinero();
    dineroTotal += getBanca();

    nBola = getNumberBola();

    dineroBanca = getBanca() - 1000000;
}
