#include "Servidor.h"

using namespace std;

Servidor::Servidor(int usuarioDonoId, std::string nome){
  this->usuarioDonoId = usuarioDonoId;
  this->nome = nome;
}

int Servidor::getId(){ return usuarioDonoId;}

string Servidor::getName(){ return nome;}

string Servidor::getDesc(){ return descricao;}

void Servidor::setDesc(std::string descricao){ this->descricao = descricao;}
