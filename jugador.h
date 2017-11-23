#ifndef JUGADOR_H
#define JUGADOR_H

#include "persona.h"
#include <string>
#include <list>

//struct de una apuesta
struct Apuesta{
    int tipo;
    std::string valor;
    int cantidad;
};

class Jugador : public Persona{
    private:
        int dinero_;
        std::string codigo_;
        std::list <Apuesta> lista_;

    public:
        //constructor de la clase
        Jugador(std::string dni,
            std::string codigo,
            std::string nombre = "",
            std::string apellidos = "",
            std::string direccion = "",
            std::string localidad = "",
            std::string provincia = "",
            std::string pais = ""
        ) : Persona(dni,
            nombre,
            apellidos,
            direccion,
            localidad,
            provincia,
            pais){codigo_ = codigo; dinero_ = 1000;}

        //bloque de funciones que devuelven las variables privadas
        inline std::string getCodigo() const {return codigo_;}
        inline int getDinero() const {return dinero_;}
        inline std::list<Apuesta> getApuestas() const {return lista_;}

        //bloque de funciones que modifican las variables privadas de la clase
        inline void setCodigo(std::string codigo){codigo_ = codigo;}
        inline void setDinero(int dinero){dinero_ = dinero;}
        void setApuestas(std::string path = "");        
        void addApuesta(Apuesta apuesta);
        void writeApuestas(std::string path = "");
};

#endif
