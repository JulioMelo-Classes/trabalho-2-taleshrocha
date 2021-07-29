#include "Usuario.h"

using namespace std;

int Usuario::currentId; // Has to be here for some reason

Usuario::Usuario(string email, string keyword, string name){
  Name = name;
  Email = email;
  Keyword = keyword;
}

void Usuario::setId(){
  Id = currentId++;
}

void Usuario::setName(string name){ // TODO: can't have numbers
  Name = name;
}

void Usuario::setEmail(string email){ //TODO: validation
  Email = email;
}

void Usuario::setKeyword(string keyword){ // TODO: keyword size most be bigger than 8 char
  Keyword = keyword;
}

int Usuario::getId(){
  return Id;
}

string Usuario::getName(){
  return Name;
}

string Usuario::getEmail(){
  return Email;
}

string Usuario::getKeyword(){
  return Keyword;
}
