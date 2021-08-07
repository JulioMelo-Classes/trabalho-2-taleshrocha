//! file Executor.h
#ifndef EXECUTOR_H
#define EXECUTOR_H
#include "Sistema.h"
#include <istream>
#include <ostream>
#include <sstream>

class Executor{
private:
  Sistema * sistema;
  std::stringstream ss;
  bool sair = false;

public:
  /*! Construtor. Recebe uma referência ao sistema que vai operar  Guarda o seu endereço para executar as operações. */
  Executor(Sistema &sistema);

  /*! Inicia o processamento dos comentarios.
    Esse método recebe por exemplo o "cin" e o "cout" no main
    Dessa forma ele faz o necessário para ler 1 comando por linha e
    o processar corretamente, colocando no stream de saída o resultado de cada um. */
  void iniciar(std::istream &in, std::ostream &out);

  /*! Método responsável por processar cada linha, capturando o nome do comando
    e seus parâmetros em variáveis e executar o método correspondente no sistema */
  std::string processarLinha(std::string linha);

  /*! Função de apoio que recebe um istringstream e le todo texto restante até o fim da linha. */
  std::string restoDe(std::istringstream &ss);

};

#endif
