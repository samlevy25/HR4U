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
	int counter1, counter2 = 0;
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



/*{
  "employees": [ //array
	{
	  "206902355": { //element=object
		"first name": "bar", //members : values
		"last name": "sela",
		"profession": "gardener",
		"email": "barsela03@gmail.com",
		"address": "rehovot",
		"phone": "0526761996",
		"rating": 5.0,
		"hourly wage": 60,
		"emergency contact name": "shalom",
		"emergency contact phone": "0535516767",
		"user name": "bar12",
		"password": "po8877234",
		"unavailability": [ "04.05.2020", "06.07.2021" ]
	  }
	},
	{
	  "1234567": {
		"first name": "israel",
		"last name": "israeli",
		"profession": "plumer",
		"email": "israelisraeli@gmail.com",
		"address": "bat yam",
		"phone": "0526264596",
		"rating": 3.5,
		"hourly wage": 40,
		"emergency contact name": "rahel",
		"emergency contact phone": "0535454567",
		"user name": "israel92",
		"password": "yh553524",
		"unavailability": [ "14.06.2022", "06.06.2021" ]
	  }
	},
	{
	  "6734781": {
		"first name": "yamit",
		"last name": "bat galim",
		"profession": "carpenter",
		"email": "yamit1221@gmail.com",
		"address": "hadera",
		"phone": "0526443396",
		"rating": 2.6,
		"hourly wage": 30,
		"emergency contact name": "lior",
		"emergency contact phone": "0535455987",
		"user name": "yamit85",
		"password": "667ttr21",
		"unavailability": []
	  }
	}
  ],
  "managers": [
	{
	  "776630042": {
		"first name": "ron",
		"last name": "cohen",
		"email": "ronch10@gmail.com",
		"address": "tel aviv",
		"phone": "0526732516",
		"hourly wage": 30,
		"emergency contact name": "alon",
		"emergency contact phone": "0535500127",
		"user name": "ron87",
		"password": "77ik2331"
	  }
	}

  ],
  "employers": [
	{
	  "993321213": {
		"first name": "lona",
		"last name": "bravo",
		"email": "lona5550@gmail.com",
		"address": "gan yavne",
		"phone": "0526700219",
		"credit card number": "998641122423",
		"user name": "lona11",
		"password": "j3j3w122"
	  }
	},
	{
	  "342241876": {
		"first name": "noa",
		"last name": "shvili",
		"email": "boas120@gmail.com",
		"address": "ranana",
		"phone": "0528844216",
		"credit card number": "3534511223",
		"user name": "noa43",
		"password": "7789844"
	  }
	}
  ],
  "Inquiries": [
	{
	  "1": {
		"subject": "day off",
		"id": "1234567",
		"content": "I have a birthday on 8.9.2021 and I want a holiday on this day",
		"status": "awaiting response"
	  }
	},
	{
	  "2": {
		"subject": "raise",
		"id": "206902355",
		"content": "I want a pay raise",
		"status": "awaiting response"
	  }
	}

  ]

}
 */
