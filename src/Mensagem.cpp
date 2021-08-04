#include "Mensagem.h"
#include <iostream>
#include <sstream>

using namespace std;

Mensagem::Mensagem(int ownerId, string ownerName, string date, string content){
  this->ownerId = ownerId;
  this->ownerName = ownerName;
  this->date = date;
  this->content = content;
}

void Mensagem::setContent(std::string content){
  this->content = content;
}

std::string Mensagem::getDate(){
  return date;
}

int Mensagem::getOwnerId(){
  return ownerId;
}

string Mensagem::getOwnerName(){
  return ownerName;
}

string Mensagem::getContent(){
 return content;
}
