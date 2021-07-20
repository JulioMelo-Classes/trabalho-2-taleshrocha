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

	std::string Is_User_Ok();

	void Set_Id();

	void Set_Name(std::string name);

	void Set_Email(std::string email);

	void Set_keyword(std::string keyword);

	int Get_Id();

	std::string Get_Name();

	std::string Get_Email();

	std::string Get_Keyword();
};


#endif
