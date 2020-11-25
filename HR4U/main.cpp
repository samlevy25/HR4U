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

/*
void first_example_a() 
{
	std::string path = "C:/Users/Bar Weizman/source/repos/HR4U/HR4U/database.json";
	std::fstream is(path);
	if (!is)
	{
		std::cout << "Cannot open " << path << std::endl;
		return;
	}
	json alldata = json::parse(is);

	for (std::size_t i = 0; i < alldata.size(); ++i)
	{
		try
		{
			json& data = alldata[i];
			std::string firstname = data["first name"].as<std::string>();
			std::string lastname = data["last name"].as<std::string>();
			double hourlywage = data["hourly wage"].as<double>();
			std::cout << firstname << ", " << lastname << ", " << hourlywage << std::endl;
		}
		catch (const std::exception & e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}
*/

void write_to_file(json jsonf, string path) //re-writes the file!!(with all changes&updates)
{
	ofstream db;
	db.open(path, std::ofstream::trunc); //destroy the last file,and open the path
	if (!db.is_open()) {
		std::cout << "Cannot open " << path << std::endl;
		return;
	}
	else {
		db << pretty_print(jsonf); //print to the json file 
		db.close();
	}
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

void Employee_All_Inquiries(string employee_id) {
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

	int main()
	{
		string employee_id = "22345682";
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

//	string employee_id = "22345682";
//	Employee_Edit_Account(employee_id);
	return 0;
}

