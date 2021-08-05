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

void Servidor::addTextChannel(CanalTexto canal){
  this->canaisTexto.push_back(canal);
}

void Servidor::removeParticipant(int id){
  for(auto id_ = participantesIds.begin(); id_ != participantesIds.end(); id_++){
    //cout << "removeParticipant0: " << id << " " << *id_ << endl;
    //cout << "removeParticipant0: " << participantesIds.size() << endl;
    if(*id_ == id){
      //cout << "removeParticipant1: " << id << " " << *id_ << endl;
      this->participantesIds.erase(id_);
      id_--; // For some reason
      //cout << "removeParticipant2: " << id << " " << *id_ << endl;
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
    //cout << id << id_ << endl;
    if(id_ == id){
      //cout << "true" << endl;
      return true;
    }
  }
  //cout << "false" << endl;
  return false;
}

bool Servidor::existTextChannel(string name){
  //cout << canaisTexto.size() << endl;
  for(CanalTexto canal : canaisTexto){
    //cout << "Nomes: " << canal_.getName() << " " << canal.getName() << endl;
    if(canal.getName() == name){
      //cout << "true" << endl;
      return true;
    }
  }
  //cout << "false" << endl;
  return false;
}

CanalTexto* Servidor::getChannel(string name){
  CanalTexto c("----");
  for(CanalTexto &canal : canaisTexto){
    if(canal.getName() == name){
      return &canal;
    }
  }
  return &c;
}

bool Servidor::listTextChannels(){
  int i = 1; //<! Just to enumerate the list

  for(CanalTexto canal  : canaisTexto){
    cout << i << ") " << canal.getName() << endl;
    i++;
  }

  if(i != 1){
    return true;
  }
  else{
    return false;
  }
}
