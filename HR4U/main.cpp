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
#include <json/value.h>
#include <json/writer.h>



using namespace jsoncons::jsonpointer;
using namespace jsoncons::jsonpath;
using namespace jsoncons;
using namespace std;
using std::cout;
using std::cin;
//declarations:
void Employee_Menu(string employee_id);
string GenRandomChars(int n);
void write_to_file(json jsonf, string path);
void Edit_Account(string user_id);
//dont forget to declar


//**********************************************************************
static const char alphnum[] = "0123456789" "!@#$%^&*" "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz";
int strLen = sizeof(alphnum) - 1;
char GenRand()
{
	return alphnum[rand() % strLen];
}
void Logo()
{
	system("color 9");
	cout << endl;
	cout << "                           #     #       # # # #         #       #       #       # " << endl;
	cout << "                           #     #       #      #        #       #       #       # " << endl;
	cout << "                           #     #       #      #        #       #       #       # " << endl;
	cout << "                           # # # #       # # # #         # # # # #       #       # " << endl;
	cout << "                           #     #       #     #                 #       #       # " << endl;
	cout << "                           #     #       #      #                #       #       # " << endl;
	cout << "                           #     #       #       #               #        # # # #  " << endl;
	cout << endl;
}
void Login()
{
	string path = "./database.json";
	fstream is(path);
	if (!is)
	{
		cout << "Cannot open " << path << endl;
		return;
	}
	json alldata = json::parse(is);

	int choice,choice1=1;
	string user_name,password;
	string security_ans[3];
	bool all_answer_right = true;

	do
	{
		cout << endl;
		cout << "Please enter your choice:" << endl;
		cout << "1.Login with username and password" << endl;
		cout << "2.Forgot user name/password?" << endl;
		cout << "3.New here? register  as employer" << endl;
		cout << "4.exit" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			do
			{
				cout << "Enter user name: " << endl;
				cin >> user_name;
				cout << "Enter password: " << endl;
				cin >> password;
				for (std::size_t i = 0; i < alldata.size(); ++i)
				{
					json& data = alldata[i];
					if (data["user name"] == user_name && data["password"] == password)
					{
						system("color 2");
						string user_id = data["id"].as_string();
						if (data["type"] == "employee")
						{
							cout << endl << "#########################################################"<< endl << endl;
							cout << endl<<"welcome  " << data["first name"] << endl<<endl;
							
							Employee_Menu(user_id);
						}
						if (data["type"] == "manager")
						{
							cout << endl << "#########################################################" << endl << endl;
							cout << endl << "welcome  " << data["first name"] << endl << endl;
							//manager_menu(user_id)
						}
						if (data["type"] == "employer")
						{
							cout << endl << "#########################################################" << endl << endl;
							cout << endl << "welcome  " << data["first name"] << endl << endl;
							//employer_menu(user_id)
						}
					}
					else
					{
						system("color 4");
						cout << "Incorrect user name or password" << endl;
						cout << "1.try again" << endl;
						cout << "2.back" << endl;
						cin >> choice1;
						system("color 9");
						if (choice1 != 1 && choice1 != 2)
						{
							do
							{
								cout << "Invalid value. Please try again. Enter your choice: 1 or 2." << endl;
								cin >> choice1;
							} while (choice1 != 1 && choice1 != 2);
						}

					}
					break;
				}
			} while (choice1 == 1);
			break;
		case 2:
			cout << "Please answer to your security questions "<<endl;
			cout << "1.What is your mother`s name?" << endl;
			cin >> security_ans[0];
			cout << "2.What is your date of birth?(format:XX.XX.XXXX)" << endl;
			cin >> security_ans[1];
			cout << "3.What's your main hobby?" << endl;
			cin >> security_ans[2];
			for (std::size_t i = 0; i < alldata.size(); ++i)
			{
				json& data = alldata[i];
				for (int i = 0;i < 3;i++)
				{
					if (data["reset password details"][i] != security_ans[i])
					{
						all_answer_right = false;
					}
				}
				if (all_answer_right)
				{
					string new_user_name= data["first name"].as_string() + GenRandomChars(2);
					string new_password = GenRandomChars(8);
					cout << endl<<"You answered all the questions correctly"<<endl<<"your new username and password: " << endl<<endl;
					cout <<"user name: "<< new_user_name << endl;
					cout << "password: " << new_password << endl;
					std::error_code ec;
					jsonpointer::replace(data, "/user name", json(new_user_name), ec);
					if (ec)
					{
						cout << ec.message() << std::endl;
					}
					else
					{
						write_to_file(alldata, path); //updates user name 
					}
					jsonpointer::replace(data, "/password", json(new_password), ec);
					if (ec)
					{
						cout << ec.message() << std::endl;
					}
					else
					{
						write_to_file(alldata, path); //updates user name 
					}
					
				}
				else
				{
					cout << "You answered one of the questions incorrectly" << endl << "You are returned to the login screen " << endl;
				}
				break;

			}

			break;
		case 3:

		//add new employer
			break;
		case 4:
			cout << "Thank you for using HR4U!" << endl << "bye bye" << endl;
			break;
		default:
			cout << "Invalid value. Please try again. Enter your choice: 1-4." << endl;
			cin >> choice;
			break;
		}
	} while (choice != 4);

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
bool check_card(string credit_card) {
	if (credit_card.length()== 16)
	{
		int counter = 0;
		for (int i = 0; i < credit_card.length(); ++i)
		{
			if (credit_card[i] >= 0 || credit_card[i] <= 9) //checks wether the phone number contains only digits 0-9
				counter++;
		}
		if (counter == 16)
			return true;
	}
	else {
		cout << "credit card number invalid.please enter 16 digits " << endl;
	}
	return false;
}
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
	}
	return false;
}
bool check_email(string email) {
	int counter1 = 0, counter2 = 0;
	for (int i = 0; i < email.length(); ++i)
	{
		if (email[i] == '@') //checks wether the phone number contains '@'
			counter1++;
		else if (email[i] == '.') //checks wether the phone number contains '.'
			counter2++;
	}
	if (counter1 == 1 && counter2 >= 1)
		return true;
	else {
		cout << "phone number invalid.please enter 10 digits phone number" << endl;
		return false;
	}
}
void Edit_Account(string user_id)
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
		if (data["id"] == user_id)
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
						cout << "Data updated successfully ! " << endl;
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
					cout << "Back to menu" << endl;
					break;
				default:
					cout << "Invalid value. Please try again. Enter your choice: 1-5." << endl;
					cin >> choice;
				}
			} while (choice != 5);
		}
	}
}
void Employer_Edit_Account(string user_id)
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
		if (data["id"] == user_id)
		{
			int choice;
			do {
				cout << "Edit Account By Employee:Choose what details would you like to edit:" << endl;
				cout << "1.Edit Adress" << endl;
				cout << "2.Edit Email" << endl;
				cout << "3.Edit Phone number" << endl;
				cout << "4.Edit Emergency contact" << endl;
				cout << "5.Edit credit card number" << endl;
				cout << "6.Edit user name" << endl;
				cout << "7.Edit password" << endl;
				cout << "8.Back" << endl;
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
						cout << "Data updated successfully ! " << endl;
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
				{	//edit phone-number
					cout << "Enter your new credit card number:" << endl;
					string newcard;
					cin >> newcard;
					while (!check_card(newcard)) //while the phone number is invaild.
						cin >> newcard;

					std::error_code ec;
					jsonpointer::replace(data, "/credit card number", json(newcard), ec);
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
				case 6:
				{
					string new_user_name = data["first name"].as_string() + GenRandomChars(2);
					cout << "Your new user name: " << new_user_name << endl;
					std::error_code ec;
					jsonpointer::replace(data, "/user name", json(new_user_name), ec);
					if (ec)
					{
						cout << ec.message() << std::endl;
					}
					else
					{
						write_to_file(alldata, path); //updates user name 
					}

				}
				break;
				case 7:
				{
					string new_password = GenRandomChars(8);
					cout << "Yuor new password: " << new_password << endl;
					std::error_code ec;
					jsonpointer::replace(data, "/password", json(new_password), ec);
					if (ec)
					{
						cout << ec.message() << std::endl;
					}
					else
					{
						write_to_file(alldata, path); //updates user name 
					}
				}
				break;
				case 8:
				{
					cout << "Back to employer menu" << endl;
				}
				break;
				default:
					cout << "Invalid value. Please try again. Enter your choice: 1-5." << endl;
					cin >> choice;
				}
			} while (choice != 8);
		}
	}
}
void Employee_All_Inquiries(string employee_id) {//the inquires detail has been changed. we need to deside what is the best way.g
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
void Employee_Add_Inquiries(string employee_id)
{
}
void Employee_Menu(string employee_id) {
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
		system("color 2");
		switch (choice) {
		case 1:
			Edit_Account(employee_id);
			break;
		case 2:
			//print history
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
			break;
		case 4:
			break;
		case 5:
			break;
		default:
			break;
		}
	} while (choice != 6);
}
void Manager_Menu(string manager_id)
{
	int choice;
	do {
		cout << "Manager Menu!" << endl;
		cout << "Please enter your choice:" << endl;
		cout << "1.Edit your Account" << endl;
		cout << "2.View company statistics" << endl;
		cout << "3.Manage Inquiries" << endl;
		cout << "4.View/edit employee details" << endl;
		cout << "5.Add/Remove employee" << endl;
		cout << "6.EXIT SYSTEM" << endl;
		cin >> choice;
		system("color 2");
		switch (choice) {
		case 1:
			Edit_Account(manager_id);
			break;
		case 2:
			//statistics
			break;
		case 3:
			//Manage Inquiries
			break;
		case 4:
			//View/edit employee details
			break;
		case 5:
			cout << "Enter your choice:" << endl;
			cout << "1.Add employee" << endl;
			cout << "2.Remove employee" << endl;
			cout << "3.Exit" << endl;
			cin >> choice;
			if (choice != 3)
			{
				switch (choice) {
				case 1:
					//add employee
					break;
				case 2:
					//remove employee
					break;
				default:
					cout << "Invalid input.Please try again,Enter your choice 1-3:" << endl;
					cin >> choice;
				}
			}
			break;
		case 6:
			cout << "Back to login screen" << endl;
			break;
		default:
			cout << "Invalid value. Please try again. Enter your choice: 1-6." << endl;
			cin >> choice;
			break;
		}
	} while (choice != 6);
}


int main() {
	Logo();
	Login();
	return 0;
}

