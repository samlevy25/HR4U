#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include <cstdlib>
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


void Employee_Edit_Account(string employee_id)
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
						std::cout << ec.message() << std::endl;
					}
					else
					{
						std::cout << data << std::endl;
					}

				//	jsonpath::json_replace(data,"$.[].adress", newadress);
				//	alldata["adress"] = newadress; //PROBLEM! NEED TO SOLVE
				}
					break;
				case 2:
					//edit email
					break;
				case 3:
					//edit phone-number
					break;
				case 4:
					//edit emergency contact details
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




int main()
{
	string employee_id = "22345682";
	Employee_Edit_Account(employee_id);
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
