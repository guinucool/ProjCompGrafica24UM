#ifndef UNVALUES_HPP
#define UNVALUES_HPP

#include <exception>
#include <string>

/* Inicialização do namespace usado para definir a exceção */
namespace customException 
{

    /* Definição da exceção undefined_value */
    class undefined_value : public std::exception {

        private:

            /* Definição das propriedades da exceção */
            std::string message;

        public:

            /* Construtor padrão da exceção */
            undefined_value(const std::string& msg);

            /* Emite a mensagem de erro customizada */
            const char* what() const noexcept;
    };
}

#endif
