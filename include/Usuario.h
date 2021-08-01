//! @file Usuario.h
#ifndef USUARIO_H
#define USUARIO_H
#include <string>

class Usuario{
private:
	int Id;
	static int currentId;
	std::string Name;
	std::string Email;
	std::string Keyword;

public:

	/*! The class's constructor.
	  @param email A string containing the user's email address.
	  @param keyword A string containing the user's keyword.
	  @param name A string containing the user's name. */
	Usuario(std::string email, std::string keyword, std::string name);

    /*! Creates a unique id for the user and sets it in the integer id. */
	void setId();

	/*! Set the user's name.
	  @param name A string containing the user's name to be changed. */
	void setName(std::string name);

	/*! Set the user's email address.
	  @param email A string containing the user's email address to be changed. */
	void setEmail(std::string email);

	/*! Set the user's keyword.
	  @param keyword A string containing the user's email address to be changed. */
	void setKeyword(std::string keyword);

	/*! Get the user's owner id.
	  @return A integer containing the user's owner id. */
	int getId();

	/*! Get the user's name.
	  @return A integer containing the user's name. */
	std::string getName();

	/*! Get the user's email.
	  @return A integer containing the user's email. */
	std::string getEmail();

	/*! Get the user's keyword.
	  @return A integer containing the user's keyword. */
	std::string getKeyword();
};

#endif
