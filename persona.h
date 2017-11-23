#ifndef PERSONA_H
#define PERSONA_H

#include <string>

class Persona{
    private:
        std::string dni_, nombre_, apellidos_, direccion_, localidad_, provincia_, pais_;

    public:
        //constructor de la clase
        Persona(std::string dni, std::string nombre = "", std::string apellidos = "", std::string direccion = "",
        std::string localidad = "", std::string provincia = "", std::string pais = "");

        //bloque de funciones que modifican las variables privadas de la clase
        inline void setDNI(std::string aux){dni_ = aux;}
        inline void setNombre(std::string aux){nombre_ = aux;}
        inline void setApellidos(std::string aux){apellidos_ = aux;}
        inline void setDireccion(std::string aux){direccion_ = aux;}
        inline void setLocalidad(std::string aux){localidad_ = aux;}
        inline void setProvincia(std::string aux){provincia_ = aux;}
        inline void setPais(std::string aux){pais_ = aux;}

        //bloque de funciones que devuelven las variables privadas
        inline std::string getDNI() const {return dni_;}
        inline std::string getNombre() const {return nombre_;}
        inline std::string getApellidos() const {return apellidos_;}
        inline std::string getDireccion() const {return direccion_;}
        inline std::string getLocalidad() const {return localidad_;}
        inline std::string getProvincia() const {return provincia_;}
        inline std::string getPais() const {return pais_;}
        inline std::string getApellidosyNombre() const {return (apellidos_ + ", " + nombre_);}
};

#endif
