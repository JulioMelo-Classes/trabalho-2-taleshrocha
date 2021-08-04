#include "CanalTexto.h"
#include <iostream>

using namespace std;

CanalTexto::CanalTexto(std::string name){
  this->name = name;
}

void CanalTexto::setName(string name){
  this->name = name;
}

void CanalTexto::addMessage(Mensagem message){
  //cout << "ahhhhhh" << endl;
  //cout << message.getContent() << endl;
  this->messages.push_back(message);
  for(Mensagem message : this->messages){
    cout << message.getContent() << endl;
  }
}

string CanalTexto::getName(){
  return name;
}

void CanalTexto::listMessages(){
  cout << "list" << endl;
  for(Mensagem &message : this->messages){
    cout << message.getOwnerName() << message.getDate() << ": " << message.getContent() << endl;
  }
}
