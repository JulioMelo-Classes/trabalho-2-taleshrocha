#include "CanalTexto.h"

using namespace std;

CanalTexto::CanalTexto(std::string name){
  this->name = name;
}

void CanalTexto::setName(string name){
  this->name = name;
}

void CanalTexto::addMessage(Mensagem message){
  messages.push_back(message);
}

string CanalTexto::getName(){
  return name;
}
