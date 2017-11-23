#include "jugador.h"
#include <fstream>

void Jugador::setApuestas(std::string path){
    std::ifstream file;
    std::string stream;
    Apuesta aux;

    lista_.clear();

    file.open(path + Jugador::getDNI() + ".apu");

    //gets the bets from bet file
    while(getline(file, stream, ',')){
        aux.tipo = atoi(stream.c_str());

        getline(file, stream, ',');
        aux.valor = stream;

        getline(file, stream, '\n');
        aux.cantidad = atoi(stream.c_str());

        lista_.push_back(aux);
    }
    file.close();
}

void Jugador::addApuesta(Apuesta apuesta){
    lista_.push_back(apuesta);
}

void Jugador::writeApuestas(std::string path){
    std::ofstream f;
    f.open(path + getDNI() + ".apu");

    //write all player's bets to the bet file
    for(std::list<Apuesta>::iterator it = lista_.begin(); it != lista_.end(); ++it)
        f << it->tipo << "," << it->valor << "," << it->cantidad << "\n";

    f.close();
}
