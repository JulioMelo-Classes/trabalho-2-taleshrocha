#include "Sistema.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cctype>
#include <ctime>

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

string Sistema::create_user(const string email, const string senha, const string nome) {
  if(nome.empty() or email.empty() or senha.empty()){
    return "create-user: faltam informações para a criar o usuário.";
  }

  for(shared_ptr<Usuario> user : usuarios){ //<! Checks if the user name or email already exists
    if(nome == user->getName()){
      return "create-user: nome de usuário já existente.";
    }
    else if(email == user->getEmail()){
      return "create-user: email já usado.";
    }
  }

  shared_ptr<Usuario> user(new Usuario(email, senha, nome));
  if(!user->validateKeyword()){
    return "create-user: senha inválida. Ela deve ter pelo menos 8 caracters e um caractere especial (Ex.: senhamassa#)";
  }
  user->setId();
  usuarios.push_back(user); //<! Adds the user in the Sistema's usuarios vector only if he doesn't exists
  return "create-user: usuário criado com sucesso.";
}

string Sistema::login(const string email, const string senha){
  for(shared_ptr<Usuario> user : usuarios){
    if(email == user->getEmail() and senha == user->getKeyword()){ //<! Checks if the user email and keyword exists
      if(!usuariosLogados.contains(user->getId())){ //<! See if the user is not already logged
        shared_ptr<string> n1(new string("--"));
        shared_ptr<string> n2(new string("--"));
        usuariosLogados.insert(make_pair(user->getId(), make_pair(n1, n2)));
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
  for(shared_ptr<Usuario> user : usuarios){
    if(user->getId() == id){
      userName = user->getName();
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
    shared_ptr<Servidor> server(new Servidor(id, nome));
    for(shared_ptr<Servidor> server : this->servidores) // Seek for a existing server name in the user domain
      if(nome == server->getName() and id == server->getId()){
        return "create-server: já existe um servidor com esse nome!";
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
    for(shared_ptr<Servidor> server : servidores){ // Seek for a existing server name in the user domain
      if(nome == server->getName()){
        if(id == server->getId()){
          server->setDesc(descricao);
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
    for(shared_ptr<Servidor> &server : servidores){ // Seek for a existing server name in the user domain
      if(nome == server->getName()){
        if(id == server->getId()){
          server->setInviteCode(codigo);
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
  if(usuariosLogados.contains(id)){ // See if the user is logged
    int i = 1;
    cout << "list-servers: for user " << id << ":" << endl;

    // Get all the servers belonging to the id and put them into "ss"
    for(auto &server : servidores){
      if(server->getId() == id){
        cout << i << ") " << server->getName() << endl;
        i++;
      }
    }

    if(i == 1){
      return "list-servers: não foram encontrados servidores para esse usuário!";
    }

    return "Fim dos servidores.";
  }
  return "list-servers: usuário não existe ou não conectado!";
}

string Sistema::remove_server(int id, const string nome) {
  if(usuariosLogados.contains(id)){ // See if the user is logged
    for(auto server = servidores.begin(); server != servidores.end(); server++){
      if((*server)->getName() == nome){
        if((*server)->getId() == id){
          for(auto &[key, value] : usuariosLogados){
            // See if the server that the user are seeing are equal to the server to be deleted
            if(*(value.first) == (*server)->getName()){
              *(value.first) = "--";  // Removes the deleted server from the user view
              *(value.second) = "--"; // Removes the deleted server's channel from the user view
            }
          }
          servidores.erase(server);
          return "remove_server: servidor [" + (*server)->getName() + "] removido.";
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
    for(shared_ptr<Servidor> &server : servidores){
      if(nome == server->getName()){
        if(server->existParticipant(id) or server->getInviteCode().empty() or codigo == server->getInviteCode() or id == server->getId()){
          server->addParticipant(id);
          for(auto& [key, value] : usuariosLogados){
            if(key == id){
              *(value.first) = nome;
            }
          }
          return "enter-server: você está no servidor [" + nome + "].";
        }
        else{
          return "enter-server: código de convite nulo ou errado!";
        }
      }
    }
    return "enter-server: servidor não existe!";
  }
  return "enter-server: usuário não existe ou não conectado!";
}

string Sistema::leave_server(int id, const string nome) {
  if(usuariosLogados.contains(id)){ // See if the user is logged
    for(shared_ptr<Servidor> &server : servidores){
      if(nome == server->getName()){
        if(server->existParticipant(id)){
          server->removeParticipant(id);
          for(auto& [key, value] : usuariosLogados){
            if(key == id){
              *(value.first) = "--";
              *(value.second) = "--";
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
    int i = 1; //<! Just to enumerate the list
    string serverName;

    // To get the server name that the user are seeing
    for(const auto& [key, value] : usuariosLogados){
      if(key == id){
        serverName = *(value.first);
        break;
      }
    }

    if(serverName == "--"){ //<! If the user is not in any server
      return "list-participants: o usuário não está em nenhum servidor!";
    }

    cout << "list-participants: for user " << id << " in server [" << serverName << "]:" << endl;

    // Now we are going to get all the user's names that are in the server
    for(shared_ptr<Servidor> server : servidores){
      if(server->getName() == serverName){
        for(shared_ptr<Usuario> user : usuarios){
          if(server->existParticipant(user->getId())){
            cout << i << ") " << user->getName() << endl;
            i++;
          }
        }
        break; // After i get the right server, i don't need to look the others
      }
    }

    return "Fim dos participantes.";
  }
  return "list-participants: usuário não existe ou não conectado!";
}

string Sistema::list_channels(int id) {
  // TODO: comments.
  if(usuariosLogados.contains(id)){ // See if the user is logged
    string serverName;
    bool areChannels;

    // To get the server name that the user are seeing
    for(const auto& [key, value] : usuariosLogados){
      if(key == id){
        serverName = *(value.first);
        break;
      }
    }

    if(serverName == "--"){ //<! If the user is not in any server
      return "list-channels: o usuário não está em nenhum servidor!";
    }

    cout << "list-channels: for user " << id << " in server [" << serverName << "]:" << endl;

    // Now we are going to get all the user's names that are in the server
    for(shared_ptr<Servidor> server : servidores){
      if(server->getName() == serverName){
        areChannels = server->listTextChannels();
        break; // After i get the right server, i don't need to look the others
      }
    }

    if(!areChannels){
      return "Não existem canais para " + serverName + ".";
    }

    return "Fim dos canais.";
  }
  return "list-channels: usuário não existe ou não conectado!";
}

string Sistema::create_channel(int id, const string nome) {
  // TODO: comments.
  string serverName;
  shared_ptr<CanalTexto> canal(new CanalTexto(nome));
  if(usuariosLogados.contains(id)){ // See if the user is logged
    for(const auto& [key, value] : usuariosLogados){
      if(key == id){
        serverName = *(value.first);
        break;
      }
    }
    if(serverName == "--"){
      return "create-channel: não podes criar o canal ["+ canal->getName() +"]! Primeiro entre em um servidor.";
    }
    for(shared_ptr<Servidor> server : servidores){//TODO server ou &server?
      if(id != server->getId() and server->getName() == serverName){
        return "create-channel: não podes criar o canal ["+ canal->getName() +"] em um servidor que não é seu [" + serverName + "]!";
      }
      if(server->getName() == serverName and server->existTextChannel(canal->getName())){
        return "create-channel: já existe um canal com o nome [" + canal->getName() + "] no servidor [" + serverName + "]!";
      }
      if(server->getName() == serverName){
        server->addTextChannel(canal);
        return "create-channel: canal [" + canal->getName() + "] criado com sucesso no servidor ["+ serverName +"].";
      }
    }
  }
  return "create-channel: usuário não existente ou não conectado!";
}

string Sistema::enter_channel(int id, const string nome) {
  string serverName;
  if(usuariosLogados.contains(id)){ // See if the user is logged
    for(const auto& [key, value] : usuariosLogados){
      if(key == id){
        serverName = *(value.first);
        break;
      }
    }
    if(serverName == "--"){
      return "enter-channel: primeiro, entre em um servidor.";
    }
    for(shared_ptr<Servidor> server : servidores){
      if(serverName == server->getName() and server->existTextChannel(nome)){
        for(auto& [key, value] : usuariosLogados){
          if(key == id){
            *(value.second) = nome;
          }
        }
        return "enter-channel: você está no canal: [" + nome + "] do servidor: [" + serverName + "].";
      }
    }
    return "enter-channel: canal: [" + nome + "] não existe no servidor: [" + serverName + "]!";
  }
  return "enter-channel: usuário não existe ou não conectado!";
}

string Sistema::leave_channel(int id) {
  string serverName;
  string channelName;
  if(usuariosLogados.contains(id)){ // See if the user is logged
    for(const auto& [key, value] : usuariosLogados){
      if(key == id){
        channelName = *(value.second);
        serverName = *(value.first);
        break;
      }
    }
    if(serverName == "--"){
      return "leave-channel: primeiro, entre em um servidor.";
    }
    for(shared_ptr<Servidor> server : servidores){
      if(serverName == server->getName() and channelName != "--"){
        for(auto& [key, value] : usuariosLogados){
          if(key == id){
            *(value.second) = "--";
          }
        }
        return "leave-channel: você saiu do canal: [" + channelName + "] do servidor: [" + serverName + "].";
      }
    }
    return "leave-channel: você já não está em nenhum canal do servidor: [" + serverName + "]!";
  }
  return "leave-channel: usuário não existe ou não conectado!";
}

string Sistema::send_message(int id, const string mensagem) {
  string serverName;
  string channelName;
  string userName;
  for(shared_ptr<Usuario> user : usuarios){
    if(user->getId() == id){
      userName = user->getName();
    }
  }
  if(usuariosLogados.contains(id)){ // See if the user is logged
    for(const auto &[key, value] : usuariosLogados){
      if(key == id){
        serverName = *(value.first);
        channelName = *(value.second);
        break;
      }
    }
    if(channelName == "--"){
      return "send-message: você deve estar em um canal->";
    }
    // Creates the current time string.
    char buffer[100];
    time_t time = std::time(nullptr);
    for(shared_ptr<Servidor> server : servidores){//TODO: server ou &server?
      if(serverName == server->getName() and server->existTextChannel(channelName)){
        if(strftime(buffer, sizeof(buffer), "<%d/%m/%y - %R>", localtime(&time))){
          string s = buffer;
          shared_ptr<Mensagem> message(new Mensagem(id, userName, s, mensagem));
          shared_ptr<CanalTexto> canal = server->getChannel(channelName);
          canal->addMessage(message);
          //cout << mensagem << endl;
          return "send-message: mensagem enviada com sucesso em " + s + ".";
        }
        return "send-message: não foi possível ter a data e hora de envio da mensagem. Verifique o seu sistema!";
      }
      return "send-message: existe um erro no servidor ou canal->";
    }
  }

  return "send-message: usuário não existe ou não conectado!";
}

string Sistema::list_messages(int id) {
  if(usuariosLogados.contains(id)){ // See if the user is logged
    string serverName;
    string channelName;

    // To get the server name that the user are seeing
    for(const auto& [key, value] : usuariosLogados){
      if(key == id){
        serverName = *(value.first);
        channelName = *(value.second);
        break;
      }
    }

    if(serverName == "--"){ //<! If the user is not in any server
      return "list-messages: o usuário não está em nenhum servidor!";
    }

    cout << "list-messages: for user " << id << " in server [" << serverName << "] and channel [" << channelName  << "]:" << endl;

    // Now we are going to get all the user's names that are in the server
    for(shared_ptr<Servidor> server : servidores){
      if(server->getName() == serverName and server->existTextChannel(channelName)){
        shared_ptr<CanalTexto> channel = server->getChannel(channelName);
        channel->listMessages();
        break; // After i get the right server, i don't need to look the others
      }
    }

    return "Fim das mensagens.";
  }
  return "list-messages: usuário não existe ou não conectado!";
}
