#ifndef CRUPIER_H
#define CRUPIER_H

#include "persona.h"

class Crupier : public Persona{
    private:
        std::string codigo_;

    public:
        //constructor de la clase
        Crupier(std::string dni,
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
            pais){codigo_ = codigo;}

        //funcion que modifica variables privadas
        inline void setCodigo(std::string aux){codigo_ = aux;}

        //funcion que devuelve variables privadas
        inline std::string getCodigo() const {return codigo_;}
};

#endif
