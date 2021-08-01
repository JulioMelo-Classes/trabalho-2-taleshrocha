#include "Sistema.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cctype>

using namespace std;

/* COMANDOS */
bool Sistema::quit() {
  int lineCount = 0;
  int randomQuote_int = 0;
  string line = "";
  string quitMenssage = "Sair? [Y]es / [N]o";
  char quit = 'Y';
  vector<std::string> randomQuote_vect;
  ifstream quoteFile ("../data/quotes.txt");
  srand(time(NULL));

  if(quoteFile.is_open()){
    while(!quoteFile.eof()){
      getline(quoteFile, line);
      if(line != " "){
        randomQuote_vect.push_back(line);
        lineCount++;
      }
    }
    randomQuote_int = rand() % (lineCount - 1);
    cout << randomQuote_vect[randomQuote_int] << " " << quitMenssage << endl;
    quoteFile.close();
  }
  else{
    cout << "Error. Unable to open a funny quote :(." << endl;
  }

  cin >> quit;

  while(!(toupper(quit) == 'Y')){
    if(toupper(quit) == 'N'){
      return false;
    }
    cout << quitMenssage << endl;
    cin >> quit;
  }
  return true;
}

string Sistema::create_user (const string email, const string senha, const string nome) {
  if(nome.empty() or email.empty() or senha.empty()){
    return "create_user: faltam informações para a criar o usuário.";
  }

  for(Usuario user : usuarios){ //<! Checks if the user name or email already exists
    if(nome == user.getName()){
      return "create_user: nome de usuário já existente.";
    }
    else if(email == user.getEmail()){
      return "create_user: email já usado.";
    }
  }

  Usuario user(email, senha, nome);
  user.setId();
  usuarios.push_back(user); //<! Adds the user in the Sistema's usuarios vector only if he doesn't exists
  return "create_user: usuário criado com sucesso.";
}

string Sistema::login(const string email, const string senha){
  for(Usuario u : usuarios){
    if(email == u.getEmail() and senha == u.getKeyword()){ //<! Checks if the user email and keyword exists
      if(!usuariosLogados.contains(u.getId())){ //<! See if the user is not already logged
        usuariosLogados.insert(make_pair(u.getId(), make_pair("--", "--")));
        return "login: logado como " + email;
      }
      else{
        return "login: usuário com email: " + email + ", já logado!";
      }
    }
  }
  return "login: senha ou usuário inválidos"; //<! In case the user doesn't exists
}

string Sistema::disconnect(int id) {

  // Just to get the user name:
  string userName;
  for(Usuario user : usuarios){
    if(user.getId() == id){
      userName = user.getName();
    }
  }

  // To disconnect the user:
  if(usuariosLogados.contains(id)){ // See if the user is logged in
    auto el = usuariosLogados.find(id);
    usuariosLogados.erase(el);
    return "disconnect: usuário [" + userName + "] desconectado com sucesso.";
  }
  return "disconnect: usuário não conectado ou não existente!";
}

string Sistema::create_server(int id, const string nome) {
  if(usuariosLogados.contains(id)){ // See if the user is logged
    Servidor server(id, nome);
    for(Servidor server : servidores) // Seek for a existing server name in the user domain
      if(nome == server.getName() and id == server.getId()){
        return "create_server: já existe um servidor com esse nome!";
      }

    servidores.push_back(server);
    return "create-server: servidor criado com sucesso.";
  }
  else{
    return "create-server: usuário não existente ou não conectado!";
  }
}

string Sistema::set_server_desc(int id, const string nome, const string descricao) {
  if(usuariosLogados.contains(id)){ // See if the user is logged
    for(Servidor server : servidores){ // Seek for a existing server name in the user domain
      if(nome == server.getName()){
        if(id == server.getId()){
          server.setDesc(descricao);
          return "set_server_desc: descrição do servidor [" + nome + "] modificada.";
        }
        else return "set_server_desc: você não pode alterar a descrição de um servidor que não foi criado por você!";
      }
      else return "set_server_desc: servidor [" + nome + "] não existe!";
    }
  }
  return "set_server_desc: usuário não existe ou não conectado!";
}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {
  if(usuariosLogados.contains(id)){ // See if the user is logged
    for(Servidor &server : servidores){ // Seek for a existing server name in the user domain
      if(nome == server.getName()){
        if(id == server.getId()){
          server.setInviteCode(codigo);
          if(codigo.empty()){
            return "set_server_invite_code: codigo de convite do servidor [" + nome + "] removido.";
          }
          else{
            return "set_server_invite_code: codigo de convite do servidor [" + nome + "] modificado.";
          }
        }
        else
          return "set_server_invite_code: você não pode alterar o convite de um servidor que não foi criado por você!";
      }
      else{
        return "set_server_invite_code: servidor [" + nome + "] não existe!";
      }
    }
  }
  return "set_server_invite_code: usuário não existe ou não conectado!";
}

string Sistema::list_servers(int id) {
  stringstream ss;
  ss << "list_servers: for user " << id << ":" << endl;

  // Get all the servers belonging to the id and put them into "ss"
  for(auto &server : servidores){
    if(server.getId() == id){
      ss << server.getName() << endl;
    }
  }

  string s = ss.str();

  if(s.empty()){
    return "list_servers: não foram encontrados servidores para esse usuário!";
  }

  s.pop_back(); // Removes the last endl from the string
  return s;
}

string Sistema::remove_server(int id, const string nome) {
  if(usuariosLogados.contains(id)){ // See if the user is logged
    for(auto server = servidores.begin(); server != servidores.end(); server++){
      if(server->getName() == nome){
        if(server->getId() == id){
          for(auto& [key, value] : usuariosLogados){
            // See if the server that the user are seeing are equal to the server to be deleted
            if(value.first == server->getName()){
              value.first = "--";  // Removes the deleted server from the user view
              value.second = "--"; // Removes the deleted server's channel from the user view
            }
          }
          servidores.erase(server);
          return "remove_server: servidor [" + server->getName() + "] removido.";
        }
        else{
          return "remove_server: você não pode remover um servidor que não é seu!";
        }
      }
      else{
        return "remove_server: nome de servidor não encontrado!";
      }
    }
  }
  return "remove-server: usuário não existe ou não conectado!";
}

string Sistema::enter_server(int id, const string nome, const string codigo) {
  if(usuariosLogados.contains(id)){ // See if the user is logged
    for(Servidor &server : servidores){
      //cout << "in enter " << server.getName() << " " << "[" << server.getInviteCode() << "]"<< endl; // DEBUG
      if(nome == server.getName()){
        if(server.getInviteCode().empty() or codigo == server.getInviteCode() or id == server.getId()){
          //cout << "in enter " << server.getName() << " " << "[" << server.getInviteCode() << "]"<< endl; // DEBUG
          server.addParticipant(id);
          for(auto& [key, value] : usuariosLogados){
            //cout << key << " " << value.first << " " << value.second << endl; // DEBUG
            if(key == id){
              value.first = nome;
            }
          }
          return "enter_server: você está no servidor [" + nome + "].";
        }
        else{
          return "enter_server: código de convite nulo ou errado!";
        }
      }
    }
    return "enter_server: servidor não existe!";
  }
  return "enter-server: usuário não existe ou não conectado!";
}

string Sistema::leave_server(int id, const string nome) {
  if(usuariosLogados.contains(id)){ // See if the user is logged
    for(Servidor &server : servidores){
      if(nome == server.getName()){
        if(server.existParticipant(id)){
          server.removeParticipant(id);
          for(auto& [key, value] : usuariosLogados){
            //cout << key << " " << value.first << " " << value.second << endl; // BUG
            if(key == id){
              value.first = "--";
              value.second = "--";
              //cout << key << " " << value.first << " " << value.second << endl; // BUG
            }
          }
          return "leave-server: saindo do servidor [" + nome + "].";
        }
        else{
          return "leave-server: você já não estava no servidor [" + nome + "]!";
        }
      }
    }
      return "leave-server: servidor [" + nome + "] não existe!";
  }
  return "enter-server: usuário não existe ou não conectado!";
}

string Sistema::list_participants(int id){
  if(usuariosLogados.contains(id)){ // See if the user is logged
    stringstream ss;
    int i = 1; //<! Just to enumerate the list
    string serverName;

    // To get the server name that the user are seeing
    for(const auto& [key, value] : usuariosLogados){
      if(key == id){
        serverName = value.first;
        break;
      }
    }

    if(serverName == "--"){ //<! If the user is not in any server
      return "list-participants: o usuário não está em nenhum servidor!";
    }

    ss << "list-participants: for user " << id << " in server [" << serverName << "]:" << endl;

    // Now we are going to get all the user's names that are in the server
    for(Servidor server : servidores){
      if(server.getName() == serverName){
        for(Usuario user : usuarios){
          if(server.existParticipant(user.getId())){
            ss << i << ") " << user.getName() << endl;
            i++;
          }
        }
        break; // After i get the right server, i don't need to look the others
      }
    }

    string s = ss.str();
    s.pop_back(); // Removes the last endl from the string
    return s;
  }
  return "list-participants: usuário não existe ou não conectado!";
}

string Sistema::list_channels(int id) {
  return "list_channels NÃO IMPLEMENTADO";
}

string Sistema::create_channel(int id, const string nome) {
  return "create_channel NÃO IMPLEMENTADO";
}

string Sistema::enter_channel(int id, const string nome) {
  return "enter_channel NÃO IMPLEMENTADO";
}

string Sistema::leave_channel(int id) {
  return "leave_channel NÃO IMPLEMENTADO";
}

string Sistema::send_message(int id, const string mensagem) {
  return "send_message NÃO IMPLEMENTADO";
}

string Sistema::list_messages(int id) {
  return "list_messages NÃO IMPLEMENTADO";
}




/* IMPLEMENTAR MÉTODOS PARA OS COMANDOS RESTANTES */
