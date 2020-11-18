#define _CRT_SECURE_NO_WARNINGS
#pragma once
#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include "person.h"
#include <string>
using namespace std;

class person {
public:
	//***SET METHODS**//
	virtual void set_ID() = 0;
	virtual void set_firstname() = 0;
	virtual void set_lastname() = 0;
	virtual void set_username() = 0;
	virtual void set_password() = 0;
	virtual void set_email() = 0;
	virtual void set_adress() = 0;
	virtual void set_phone() = 0;
	//***GET METHODS**//
	virtual void get_ID() = 0;
	virtual void get_firstname() = 0;
	virtual void get_lastname() = 0;
	virtual void get_username() = 0;
	virtual void get_password() = 0;
	virtual void get_email() = 0;
	virtual void get_adress() = 0;
	virtual void get_phone() = 0;
private:
	string ID;
	string firstname;
	string lastname;
	string username;
	string password;
	string email;
	string adress;
	string phone;
};











#endif