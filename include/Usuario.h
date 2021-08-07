//! @file Usuario.h
#ifndef USUARIO_H
#define USUARIO_H
#include <string>
#include <memory>

class Usuario{
private:
	int id;
	static int currentId;
	std::string name;
	std::string email;
	std::string password;

public:

	/*! The class's constructor.
	  @param email A string containing the user's email address.
	  @param password A string containing the user's password.
	  @param name A string containing the user's name. */
	Usuario(std::string email, std::string password, std::string name);

    /*! Creates a unique id for the user and sets it in the integer id. */
	void setId();

	/*! Set the user's name.
	  @param name A string containing the user's name to be changed. */
	void setName(std::string name);

	/*! Set the user's email address.
	  @param email A string containing the user's email address to be changed. */
	void setEmail(std::string email);

	/*! Set the user's password.
	  @param password A string containing the user's email address to be changed. */
	void setPassword(std::string password);

	/*! Get the user's owner id.
	  @return A integer containing the user's owner id. */
	int getId();

	/*! Get the user's name.
	  @return A integer containing the user's name. */
	std::string getName();

	/*! Get the user's email.
	  @return A integer containing the user's email. */
	std::string getEmail();

	/*! Get the user's password.
	  @return A integer containing the user's password. */
	std::string getPassword();

	/*! See if the user's email is valid.
	  @return True if the email is valid. False otherwise. */
	bool validateEmail();

	/*! See if the user's password is valid.
	  @return True if the password is valid. False otherwise. */
	bool validatePassword();
};

#endif
