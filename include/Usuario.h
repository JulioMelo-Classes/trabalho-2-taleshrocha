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
	Usuario(std::string email, std::string keyword, std::string name);

	void setId();

	void setName(std::string name);

	void setEmail(std::string email);

	void setKeyword(std::string keyword);

	int getId();

	std::string getName();

	std::string getEmail();

	std::string getKeyword();
};


#endif
