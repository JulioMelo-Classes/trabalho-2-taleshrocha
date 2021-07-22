#include "Usuario.h"

using namespace std;

int Usuario::currentId; // Has to be here for some reason

Usuario::Usuario(string email, string keyword, string name){
  Name = name;
  Email = email;
  Keyword = keyword;
}

void Usuario::Set_Id(){
  Id = currentId++;
}

void Usuario::Set_Name(string name){ // TODO: can't have numbers
  Name = name;
}

void Usuario::Set_Email(string email){ //TODO: validation
  Email = email;
}

void Usuario::Set_keyword(string keyword){ // TODO: keyword size most be bigger than 8 char
  Keyword = keyword;
}

int Usuario::Get_Id(){
  return Id;
}

string Usuario::Get_Name(){
  return Name;
}

string Usuario::Get_Email(){
  return Email;
}

string Usuario::Get_Keyword(){
  return Keyword;
}
