#ifndef MENSAGEM_H_
#define MENSAGEM_H_
#include <string>

// TODO: implement methods.
class Mensagem{
 private:
  std::string date;
  int owner;
  std::string content;
  bool isEdited;
  bool editedDate;
 public:

  /*! The class's constructor.
    @param  owner A integer containing the message's owner id.
    @param content A string containing the message's contant.
    @param date A string containing the message's date of sending. */
  Mensagem(int owner, std::string date, std::string content);

  /*! Set the message's content. Edit the message.
    @param content A string containing the new content of the message. */
  void setContent(std::string content);

  /*! Get the message's sending date.
    @return A string containing the message's sending date. */
  std::string getDate();

  /*! Get the message's owner id.
    @return A integer containing the message's owner id. */
  int getOwner();

  /*! Get the message's content.
    @return A string containing the message's content. */
  std::string getContent();
};

#endif // MENSAGEM_H_
