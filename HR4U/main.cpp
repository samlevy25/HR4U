#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <iostream>
#include <json.hpp>
#include <jsoncons_ext/jmespath/jmespath.hpp>
#include <jsoncons_ext/jsonpath/jsonpath.hpp>
#include <jsoncons_ext/jsonpointer/jsonpointer.hpp>
#include <ctime>
#include <stdexcept>
#include <string>
#include <vector>
#include <map>
#include <fstream>

using namespace jsoncons::jsonpointer;
using namespace jsoncons::jsonpath;
using namespace jsoncons;
using namespace std;

//**********************************************************************
//**PASSWORDS&USERNAME GENERATOR!**
static const char alphnum[] = "0123456789" "!@#$%^&*" "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz";
int strLen = sizeof(alphnum) - 1;
char GenRand()
{
	return alphnum[rand() % strLen];
}

string GenRandomChars(int n)
{
	int c = 0, s = 0;
	srand(time(0));
N:
	char C;
	string password;
	for (int z = 0; z < n; z++)
	{
		C = GenRand();
		password += C;
		if (isdigit(C))
		{
			c++;
		}
		if (C == '!' || C == '@' || C == '$' || C == '%' || C == '^' || C == '&' || C == '*' || C == '#')
		{
			s++;
		}
	}
	if (n > 2 && (s == 0 || c == 0))
	{
		goto N;
	}
	return password;
}

void createpassword(const string& name) {
	//add the option to check if the user name already exists or not.!
	string username = name + GenRandomChars(2);
	string password = GenRandomChars(8);
	cout << username << endl;
	cout << password << endl;
	//	string username_password[2] = { username,password };
	//	return username_password;
}
//**********************************************************************


//**FUNCTION FOR RE-WRITING THE FILE (with all changes&updates) **//
void write_to_file(json jsonf, string path) 
{
	ofstream db; 
	db.open(path, std::ofstream::trunc); //destroy the last file,and opens a path
	if (!db.is_open()) {
		std::cout << "Cannot open " << path << std::endl;
		return;
	}
	else {
		db << pretty_print(jsonf); //prints to the json file 
		db.close();
	}
}
//**************************************************************//


bool check_phone(string phone) {
	if (phone.length() == 10)
	{
		int counter = 0;
		for (int i = 0; i < phone.length(); ++i)
		{
			if (phone[i] >= 0 || phone[i] <= 9) //checks wether the phone number contains only digits 0-9
				counter++;
		}
		if (counter == 10)
			return true;
	}
	else {
		cout << "phone number invalid.please enter 10 digits phone number" << endl;
		return false;
	}
}

bool check_email(string email) {
	int counter1=0, counter2 = 0;
	for (int i = 0; i < email.length(); ++i)
	{
		if (email[i] == '@') //checks wether the phone number contains '@'
			counter1++;
		else if (email[i] == '.') //checks wether the phone number contains '.'
			counter2++;
	}
	if (counter1 == 1 && counter2>=1)
		return true;
	else {
		cout << "phone number invalid.please enter 10 digits phone number" << endl;
		return false;
	}
}

void Employee_Edit_Account(string employee_id)
{
	string path = "./database.json";
	fstream is(path);
	if (!is)
	{
		cout << "Cannot open " << path << endl;
		return;
	}
	json alldata = json::parse(is);

	for (std::size_t i = 0; i < alldata.size(); ++i) //runs all objectss
	{
		json& data = alldata[i];
		if (data["id"]==employee_id)
		{
			int choice;
			do {
				cout << "Edit Account By Employee:Choose what details would you like to edit:" << endl;
				cout << "1.Edit Adress" << endl;
				cout << "2.Edit Email" << endl;
				cout << "3.Edit Phone number" << endl;
				cout << "4.Edit Emergency contact" << endl;
				cout << "5.Back" << endl;
				cin >> choice;
				switch (choice) {
				case 1:
				{
					//edit adress
					cout << "Enter your new adress:" << endl;
					string newadress;
					cin >> newadress;
					std::error_code ec;
					jsonpointer::replace(data, "/address", json(newadress), ec);
					if (ec)
					{
						cout << ec.message() << std::endl;
					}
					else
					{
						write_to_file(alldata, path); //updates the file(actually,re-writes it)! 
						cout << "Data updated successfully ! "<<endl;
					}
				}
					break;
				case 2:
				{
					//edit email
					cout << "Enter your new email:" << endl;
					string newemail;
					cin >> newemail;
					while (!check_email(newemail)) //while email is invalid
						cin >> newemail;
					std::error_code ec;
					jsonpointer::replace(data, "/email", json(newemail), ec);
					if (ec)
					{
						cout << ec.message() << std::endl;
					}
					else
					{
						write_to_file(alldata, path); //updates the file(actually,re-writes it)! 
						cout << "Data updated successfully ! " << endl;
					}
				}
					break;
				case 3:
				{
					//edit phone-number
					cout << "Enter your new phone number:" << endl;
					string newphone;
					cin >> newphone;
					while (!check_phone(newphone)) //while the phone number is invaild.
						cin >> newphone;

					std::error_code ec;
					jsonpointer::replace(data, "/phone", json(newphone), ec);
					if (ec)
					{
						cout << ec.message() << std::endl;
					}
					else
					{
						write_to_file(alldata, path); //updates the file(actually,re-writes it)! 
						cout << "Data updated successfully ! " << endl;
					}
				}
					break;
				case 4:
				{
					//edit emergency contact details
					cout << "Enter your new emergency contact name:" << endl;
					string newname;
					cin >> newname;
					cout << "Enter your new emergency contact pone:" << endl;
					string newphone;
					cin >> newphone;
					while (!check_phone(newphone)) //while the phone number is invaild.
						cin >> newphone;

					std::error_code ec;
					jsonpointer::replace(data, "/emergency contact name", json(newname), ec);
					jsonpointer::replace(data, "/emergency contact phone", json(newphone), ec);
					if (ec)
					{
						cout << ec.message() << std::endl;
					}
					else
					{
						write_to_file(alldata, path); //updates the file(actually,re-writes it)! 
						cout << "Data updated successfully ! " << endl;
					}
				}
					break;
				case 5:
					cout << "Back to employee menu" << endl;
					break;
				default:
					cout << "Invalid value. Please try again. Enter your choice: 1-5." << endl;
					cin >> choice;
				}
			} while (choice != 5);
		}
	}
}

void Employee_All_Inquiries(string employee_id) {//the inquires detail has been changed. we need to deside what is the best way.
	std::string path = "./database.json";
	std::fstream is(path);
	if (!is)
	{
		std::cout << "Cannot open " << path << std::endl;
		return;
	}
	json alldata = json::parse(is);

	for (std::size_t i = 0; i < alldata.size(); ++i)
	{
		json& data = alldata[i];
		if (data["id"] == employee_id)
		{
			if (data["inquiries"].size() != 0)
			{
				cout << "Date \t Subject \t Status" << endl;
				for (int i = 0; i < data["inquiries"].size(); ++i)
				{
					cout << data["inquiries dates"][i] << data["inquiries"][i] << data["inquiries status"][i];
				}
			}
			else
				cout << "No inquiries have been found.";
		}
	}
}


void Employee_Add_Inquiries(string employee_id) {

}

void Employee_Menu(string employee_id){
	int choice;
	do {
		cout << "Employee Menu!" << endl;
		cout << "Please enter your choice:" << endl;
		cout << "1.Edit Account" << endl;
		cout << "2.Salary" << endl;
		cout << "3.Inquiries" << endl;
		cout << "4.History" << endl;
		cout << "5.Exit/Enter shift" << endl;
		cout << "6.EXIT SYSTEM" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			Employee_Edit_Account(employee_id);
			break;
		case 2:
			break;
		case 3:
			cout << "Enter your choice:" << endl;
			cout << "1.All Inquiries" << endl;
			cout << "2.Add Inquiry" << endl;
			cin >> choice;
			switch (choice) {
			case 1:
				Employee_All_Inquiries(employee_id);
				break;
			case 2:
				Employee_Add_Inquiries(employee_id);
				break;
			default:
				cout << "Invalid input.Please try again,Enter your choice 1-2:" << endl;
				cin >> choice;
			}
		case 4:
			break;
		case 5:
			break;
		default:
			break;
		}
	} while (choice != 6);
}


int main(){
	string employee_id = "22345682";
	Employee_Menu(employee_id);
	return 0;
}

