#include <string>
#include "persona.h"

Persona::Persona(std::string dni, std::string nombre, std::string apellidos,
std::string direccion, std::string localidad, std::string provincia, std::string pais){
    dni_ = dni;
    nombre_ = nombre;
    apellidos_ = apellidos;
    direccion_ = direccion;
    localidad_ = localidad;
    provincia_ = provincia;
    pais_ = pais;
}
