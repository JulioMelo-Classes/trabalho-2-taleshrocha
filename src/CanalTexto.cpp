#include "CanalTexto.h"
#include <iostream>

using namespace std;

CanalTexto::CanalTexto(std::string name){
  this->name = name;
}

void CanalTexto::addMessage(std::shared_ptr<Mensagem> message){
  this->messages.push_back(message);
}

string CanalTexto::getName(){
  return name;
}

void CanalTexto::listMessages(){
  int i = 1;
  for(shared_ptr<Mensagem> message : this->messages){
    cout << i << ") " << message->getOwnerName() << message->getDate() << ": " << message->getContent() << endl;
    i++;
  }
}
