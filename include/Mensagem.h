//! file Mensagem.h
#ifndef MENSAGEM_H_
#define MENSAGEM_H_
#include <string>

class Mensagem{
 private:
  int name;
  int ownerId;
  std::string date;
  std::string ownerName;
  std::string content;
  bool editedDate;
  bool isEdited;
 public:

  /*! The class's constructor.
    @param  owner A integer containing the message's owner id.
    @param content A string containing the message's contant.
    @param date A string containing the message's date of sending. */
  Mensagem(int ownerId, std::string ownerName, std::string date, std::string content);

  /*! Set the message's content. Edit the message.
    @param content A string containing the new content of the message. */
  void setContent(std::string content);

  /*! Get the message's sending date.
    @return A string containing the message's sending date. */
  std::string getDate();

  /*! Get the message's owner id.
    @return A integer containing the message's owner id. */
  int getOwnerId();

  /*! Get the message's owner name.
    @return A string containing the message's owner name. */
  std::string getOwnerName();

  /*! Get the message's content.
    @return A string containing the message's content. */
  std::string getContent();
};

#endif // MENSAGEM_H_
