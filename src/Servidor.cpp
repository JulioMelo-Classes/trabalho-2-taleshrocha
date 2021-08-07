#include "Servidor.h"
#include <iostream>
#include <sstream>

using namespace std;

Servidor::Servidor(int usuarioDonoId, std::string nome){
  this->usuarioDonoId = usuarioDonoId;
  this->nome = nome;
}

void Servidor::setDesc(string descricao){
  this->descricao = descricao;
}

void Servidor::setInviteCode(string codigoConvite){
  this->codigoConvite = codigoConvite;
}

void Servidor::addParticipant(int id){
  this->participantesIds.push_back(id);
}

void Servidor::addTextChannel(std::shared_ptr<CanalTexto> canal){
  this->canaisTexto.push_back(canal);
}

void Servidor::removeParticipant(int id){
  for(auto id_ = participantesIds.begin(); id_ != participantesIds.end(); id_++){
    if(*id_ == id){
      this->participantesIds.erase(id_);
      id_--; // For some reason
    }
  }
}

int Servidor::getId(){
  return usuarioDonoId;
}

string Servidor::getName(){
  return nome;
}

string Servidor::getDesc(){
  return descricao;
}

string Servidor::getInviteCode(){
  return codigoConvite;
}

bool Servidor::existParticipant(int id){
  for(int id_ : participantesIds){
    if(id_ == id){
      return true;
    }
  }
  return false;
}

bool Servidor::existTextChannel(string name){
  for(shared_ptr<CanalTexto> canal : canaisTexto){
    if(canal->getName() == name){
      return true;
    }
  }
  return false;
}

shared_ptr<CanalTexto> Servidor::getChannel(string name){
  for(shared_ptr<CanalTexto> canal : canaisTexto){
    if(canal->getName() == name){
      return canal;
    }
  }
  return nullptr;
}

bool Servidor::listTextChannels(){
  int i = 1; // Just to enumerate the list

  for(shared_ptr<CanalTexto> canal  : canaisTexto){
    cout << i << ") " << canal->getName() << endl;
    i++;
  }

  if(i != 1){
    return true;
  }
  else{
    return false;
  }
}
