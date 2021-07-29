#include "Servidor.h"
#include <iostream>

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
