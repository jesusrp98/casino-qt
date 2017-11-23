#ifndef RULETA_H
#define RULETA_H

#include <list>
#include <string>
#include "crupier.h"
#include "jugador.h"

class Ruleta{
    private:
        int banca_, bola_, nBola_;
        std::list <Jugador> jugadores_;
        Crupier crupier_{"", ""};
        std::string colorBola(int bola);
        std::string parBola(int bola);
        std::string posicionBola(int bola);

    public:
        //constructor de la clase
        Ruleta(Crupier crupier);

        //bloque de funciones que devuelven las variables privadas
        inline int getBanca() const {return banca_;}
        inline int getBola() const {return bola_;}
        inline int getNumberBola() const {return nBola_;}
        inline Crupier getCrupier(){return crupier_;}
        inline std::list<Jugador> getJugadores() const {return jugadores_;}

        //funcion que modifica variables privadas
        bool setBanca(int banca);
        bool setBola(int bola);
        inline void setCrupier(Crupier crupier){crupier_ = crupier;}

        //funciones que modifican la lista de jugadores
        bool addJugador(Jugador jugador);
        int deleteJugador(std::string dni);
        int deleteJugador(Jugador jugador);

        //funciones que escribe/lee la lista de jugadores en un fichero
        void escribeJugadores(std::string path = "jugadores.txt");
        void leeJugadores(std::string path = "jugadores.txt");

        //simula el giro de la ruleta, generando un no aleatorio
        void giraRuleta();

        //actualiza el dinero de los jugadores y de la banca a corde con las apuestas realizadas
        //y del resultado de girar la ruleta
        void getPremios(bool toRead);

        //carga todas las apuestas de los jugadores desde los ficheros de texto
        void getPlayerListApuesta(std::string = "");

        //funcion que guarda por referencia diversos parametros:
        //numero de jugadores, dinero total, numero de veces que ha girado la bola
        //y el dinero que posee la banca
        void getEstadoRuleta(int &nJugadores, int &dineroTotal, int &nBola, int &dineroBanca);
};

#endif
