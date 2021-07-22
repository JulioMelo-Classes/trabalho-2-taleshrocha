#include "Servidor.h"

using namespace std;

Servidor::Servidor(int usuarioDonoId, std::string nome){
  this->usuarioDonoId = usuarioDonoId;
  this->nome = nome;
}

void Servidor::setDesc(string descricao){ this->descricao = descricao;}

void Servidor::setInviteCode(string codigoConvite){ this->codigoConvite = codigoConvite;}

int Servidor::getId(){ return usuarioDonoId;}

string Servidor::getName(){ return nome;}

string Servidor::getDesc(){ return descricao;}

string Servidor::getInviteCode(){ return codigoConvite;}
