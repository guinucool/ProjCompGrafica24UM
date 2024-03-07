/* Inclusão do cabeçalho que define a estrutura da exceção */
#include "../../inc/exception/unvalues.hpp"

/* Inicialização do namespace usado para a definição da exceção */
namespace customException
{
    /* Construtor padrão da exceção */
    undefined_value::undefined_value(const std::string& msg) : message(msg) {}

    /* Emissão da mensagem de erro da exceção */
    const char* undefined_value::what() const noexcept {
        return this->message.c_str();
    }
}