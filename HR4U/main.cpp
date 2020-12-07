#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define WHITE "\033[0m"    //color reset to white
#define BLOCKCOLOR "\033[1;100;30m" //block of color
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
#include <windows.h>

using namespace jsoncons::jsonpointer;
using namespace jsoncons::jsonpath;
using namespace jsoncons;
using namespace std;
using std::cout;
using std::cin;


//declarations:
char GenRand();
string GenRandomChars(int n);
void Logo();
void changeColor(int desiredColor);
void print_title(string title);
void Login();
void write_to_file(json jsonf, string path);
json read_file();
bool check_card(string credit_card);
bool check_phone(string phone);
bool check_email(string email);
void Edit_Account(string user_id);
//employee
void Employee_Guide();
void Employee_Shift(string employee_id);
void Employee_Salary_History(string employee_id);
void Employee_Employment_History(string employee_id);
void Employee_Inquiries_Menu(string employee_id);
void Employee_All_Inquiries(string employee_id);
void Employee_Add_Inquiries(string employee_id);
void Employee_Menu(string employee_id);
float Employee_Rate(string employee_id);
string Get_employee_name(string employee_id);
void insert_employee_rating(string employee_id, int rate);
//manager
void Manager_Menu(string manager_id);
void Manager_Guide();
void Manage_Inquiries_Status();
void Manager_Edit_Employee(string employee_id);
void Manager_Statistics();
void Manager_Get_Employees_Details(string employee_id);
//employer
void Employer_Menu(string employer_id);
bool Employer_Check_Availability(string employee_id, string date, string proffesion, int hourly_wage);
void Employer_Edit_Account(string user_id);
void Employer_Employment_History(string employer_id);
void Employer_Search(string employer_id);
void Employer_rate_employee(string employer_id);
void Employer_Guide();
//dont forget to declar


//*******************************************************************************************************************
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
//*******************************************************************************************************************
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
//*******************************************************************************************************************
void changeColor(int desiredColor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), desiredColor);

}
void print_title(string title)
{
	for (int i = 0; title[i] != '\0'; i++)
	{
		if (title[i] == ' ')
			cout << " ";
		if (title[i] != ' ')
			cout << title[i];
		changeColor(i + 1);
	}
	cout << endl;
	cout << BLOCKCOLOR << "             " << WHITE << endl;
}

//READ&WRITE FILE ***************************************************************************************************

void write_to_file(json jsonf, string path) //**FUNCTION FOR RE-WRITING THE FILE (with all changes&updates) **//
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

json read_file() {   //**FUNCTION FOR READING THE FILE (and puts all data from the file into a json object) **//
	std::string path = "./database.json";
	std::fstream is(path);
	if (!is)
	{
		std::cout << "Cannot open " << path << std::endl;
		return 0;
	}
	json alldata = json::parse(is);
	return alldata;
}

//*******************************************************************************************************************
//CHECKING functions: credit-card/phone/email details

bool check_card(string credit_card) {
	if (credit_card.length() == 16)
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
			if (int(phone[i]) >= 0 && int(phone[i]) <= 9) //checks wether the phone number contains only digits 0-9
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
//general funcions***************************************************************************************************
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

	int choice, choice1 = 1;
	string user_name, password;
	string security_ans[3];
	bool all_answer_right = true;
	bool flag;

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
				flag = false;
				cout << "Enter user name: " << endl;
				cin >> user_name;
				cout << "Enter password: " << endl;
				cin >> password;
				for (std::size_t i = 0; i < alldata.size(); ++i)
				{
					json& data = alldata[i];
					if (contains(data, "/user name/"))
					{
						if (data["user name"] == user_name)
						{
							if (data["password"] == password)
							{
								system("color 2");
								string user_id = data["id"].as_string();
								if (data["type"] == "employee")
								{
									cout << endl << "#########################################################" << endl << endl;
									cout << endl << "welcome  " << data["first name"] << endl << endl;

									Employee_Menu(user_id);
								}
								if (data["type"] == "manager")
								{
									cout << endl << "#########################################################" << endl << endl;
									cout << endl << "welcome  " << data["first name"] << endl << endl;
									Manager_Menu(user_id);
								}
								if (data["type"] == "employer")
								{
									cout << endl << "#########################################################" << endl << endl;
									cout << endl << "welcome  " << data["first name"] << endl << endl;
									Employer_Menu(user_id);
								}
								flag = true;
								break;
							}
							else
							{
								system("color 4");
								cout << "Incorrect  password" << endl;
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
								flag = true;
								break;
							}

						}
					}
				}
				if (flag == false)
				{
					system("color 4");
					cout << endl << "Incorrect user name" << endl;
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
			} while (choice1 == 1);
			break;
		case 2:
			cout << "Please answer to your security questions " << endl;
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
					string new_user_name = data["first name"].as_string() + GenRandomChars(2);
					string new_password = GenRandomChars(8);
					cout << endl << "You answered all the questions correctly" << endl << "your new username and password: " << endl << endl;
					cout << "user name: " << new_user_name << endl;
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
						write_to_file(alldata, path); //updates password
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
		break;
	}

}

bool Available_Date(string employee_id, string date)
{
	string path = "./database.json";
	fstream is(path);
	if (!is)
	{
		cout << "Cannot open " << path << endl;
		return false;
	}
	json alldata = json::parse(is);

	int length = 0;
	for (std::size_t i = 0; i < alldata.size(); ++i) //runs all objectss
	{
		json& data = alldata[i];
		if (data["id"] == employee_id)
		{
			length = (int)(data["unavailability"].size());
			for (int i = 0;i < length;i++)
			{
				if (data["unavailability"][i] == date)
					return false;
			}
			break;
		}
	}
	return true;
}

//employee functions**************************************************************************************************
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
		cout << "6.User guide" << endl;
		cout << "7.EXIT SYSTEM" << endl;
		cin >> choice;
		system("color 9");
		switch (choice) {
		case 1:
			Edit_Account(employee_id);
			break;
		case 2:
			//print history
			break;
		case 3:
			Employee_Inquiries_Menu(employee_id);
			break;
		case 4:
			Employee_Employment_History(employee_id);
			//Employee_Salary_History(employee_id);
			break;
		case 5:
			Employee_Shift(employee_id);
			break;
		case 6:
			Employee_Guide();
			break;
		case 7:
			break;
		default:
			break;
		}
	} while (choice != 7);
}

void Employee_Guide()
{
	cout << "Hello, I will teach you now how to use the system." << endl << endl
		<< "First of all, the main menu: " << endl
		<< "1.Edit Account  ->  Gives you the ability to edit your details (Address, Mail and more..)" << endl
		<< "2.Salary  ->  Shows you all the details of your salary this month, all the hours you have been worked and your final salary" << endl
		<< "3.Inquiries  ->  With inquiries you can add new inquirie or see all of your inquiries" << endl
		<< "4.History  ->  With history you can see all of your working days this month (When you arrived to work and when you end your day)" << endl
		<< "5.Exit/Enter shift  ->  By clicking Exit shift, it says to the system that you finished your day of working, and by clicking Enter shift , the system will understand that you are now started your day at the work" << endl << endl << endl
		<< "Now you're going to learn about the inquiries menu." << endl << endl
		<< "1.All Inquiries  ->  Shows you all of the inquiries you have been sent and see all the details about them" << endl
		<< "2.Add Inquiry  ->  Gives you the ability to send new inquirie" << endl << endl
		<< "Now I belive you are ready to use the system" << endl
		<< "Have a great day HR4U" << endl<<endl;
	cout<<"-----------------------------------"<< endl << endl;

}

void Employee_Inquiries_Menu(string employee_id) {
	int choice;
	do {
		cout << "****************************************************************" << endl;
		cout << "Inquiries MENU! ADD/ALL" << endl;
		cout << "Enter your choice:" << endl;
		cout << "1.All Inquiries" << endl;
		cout << "2.Add Inquiry" << endl;
		cout << "3.Back" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			Employee_All_Inquiries(employee_id);
			break;
		case 2:
			Employee_Add_Inquiries(employee_id);
			break;
		default:
			cout << "Invalid input.Please try again,Enter your choice 1-3:" << endl;
			cin >> choice;
			break;
		}
	} while (choice != 3);
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
			cout << "ID:" << employee_id << endl;
			if (data["inquiries subject"].size() != 0)
			{
				for (int i = 0; i < data["inquiries subject"].size(); ++i)
				{
					cout << "Inquiry number " << i << ":" << endl;
					cout << "Subject: " << data["inquiries subject"][i] << endl;
					cout << "Body: " << data["inquiries body"][i] << endl;
					cout << "Status: " << data["inquiries status"][i] << endl;
					cout << "-------------------------------------------------" << endl;
				}
			}
			else if (data["inquiries subject"].size() == 0)
			{
				cout << "No inquiries have been found." << endl;
				cout << "-------------------------------------------------" << endl;
			}
		}
	}
}

void Employee_Add_Inquiries(string employee_id)
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
		if (data["id"] == employee_id)
		{
			int choice;
			do {
				cout << "****************************************************************" << endl;
				cout << "Add inquiries:" << endl;
				cout << "enter your choice:" << endl;
				cout << "1.add new inquiry" << endl;
				cout << "2.back" << endl;
				cin >> choice;
				switch (choice)
				{
				case 1: {
					string body;
					string subject;
					const string status = "in process";
					cout << "please enter your inquiry subject" << endl;
					cin.ignore();
					getline(cin, subject);
					cout << "please specify your inquiry:(up to 250 letters)" << endl;
					cin.ignore();
					getline(cin, body);

					while (subject.length() > 250)
					{
						cout << "your inquiry body is way too long. please try again" << endl;
						cout << "please specify your inquiry:(up to 250 letters)" << endl;
						cin >> body;
					}
					data["inquiries subject"].push_back(subject);
					data["inquiries body"].push_back(body);
					data["inquiries status"].push_back(status);
					cout << "INQUIRY DETAILS SAVED, we`re working on it. thank you." << endl;
					write_to_file(alldata, path);
				}
					  break;
				case 2:
					cout << "thank you.back to inquiries menu" << endl;
					break;
				default:
					cout << "invalid input.please try again.please enter your choice 1-2 only:" << endl;
					break;
				}
			} while (choice != 2);
		}
	}
}

void Employee_Employment_History(string employee_id)
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
		if (data["id"] == employee_id)
		{
			int length_of_work = data["working hours"].size();
			for (size_t j = 0; j < length_of_work; j++)
			{
				cout << "Work Number " << j << ":" << endl;
				cout << "Date: " << data["day working"][j] << "/" << data["month working"][j] << "/" << data["year working"][j] << endl;
				cout << "Total working hours: " << data["working hours"][j] << endl;
				//total_working_hour += data["working hours"][j].as_double();
			}
		}
	}
}

float Employee_Rate(string employee_id)
{
	double amount;
	double number_of_rating;
	float average_rating = 0;
	std::string path = "./database.json";
	std::fstream is(path);
	if (!is)
	{
		std::cout << "Cannot open " << path << std::endl;
		return 0;
	}
	json alldata = json::parse(is);

	for (std::size_t i = 0; i < alldata.size(); ++i)
	{
		json& data = alldata[i];
		if (data["id"] == employee_id)
		{
			amount = data["amount of rating"].as_double();
			number_of_rating = data["number of rating"].as_double();
			average_rating = (float)(amount / number_of_rating);
		}
	}

	return average_rating;
}

void Employee_Shift(string employee_id)
{
	int choice;
	int start_hour, end_hour, start_minute, end_minute;
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
			do
			{
				cout << "1.Enter shift" << endl;
				cout << "2.Exit shift" << endl;
				cout << "3.Exit" << endl;
				cin >> choice;
				switch (choice) {
				case 1:
				{
					if (data["shift flag"] == true)
					{
						data["shift flag"] = false;
						time_t t = time(NULL);
						tm* tPtr = localtime(&t);
						int day = tPtr->tm_mday;
						int year = tPtr->tm_year + 1900;
						int month = tPtr->tm_mon + 1;
						int size = data["working hours"].size();
						for (size_t k = 0; k < size; k++)
						{
							if (data["day working"][k] == day && data["month working"][k] == month && data["year working"][k] == year)
							{
								cout << "You can enter shift once a day" << endl;
								cout << "You are move to employee menu" << endl;
								return Employee_Menu(employee_id);
							}
						}
						cout << "Date: " << day << "/" << month << "/" << year << " Start working: " << tPtr->tm_hour << ":" << tPtr->tm_min << ":" << tPtr->tm_sec << endl;
						start_hour = tPtr->tm_hour;
						start_minute = tPtr->tm_min;
						data["day working"].push_back(day);
						data["month working"].push_back(month);
						data["year working"].push_back(year);
						data["start hour working"].push_back(start_hour);
						data["start minute working"].push_back(start_minute);
						//we need to write to json file day month year and hour
						write_to_file(alldata, path);
						break;
					}
					else
					{
						cout << "You did not exit please do it now " << endl;
						break;
					}
				}
				case 2:
				{
					if (data["shift flag"] == false)
					{
						data["shift flag"] = true;
						time_t t = time(NULL);
						tm* tPtr = localtime(&t);
						int day = tPtr->tm_mday;
						int year = tPtr->tm_year + 1900;
						int month = tPtr->tm_mon + 1;
						cout << "Date: " << day << "/" << month << "/" << year << " End working: " << tPtr->tm_hour << ":" << tPtr->tm_min << ":" << tPtr->tm_sec << endl;
						//we need to write to json file day month year and hour
						//after that we need to calculate total working hour and write to file (TEnd->hour-TStart->hour)
						end_hour = tPtr->tm_hour;
						end_minute = tPtr->tm_min;
						data["end hour working"].push_back(end_hour);
						data["end minute working"].push_back(end_minute);
						int total_hours, total_minute;
						float total_time;
						int Start_hour_length = data["start hour working"].size();
						total_minute = data["end minute working"][Start_hour_length - 1].as_double() - data["start minute working"][Start_hour_length - 1].as_double();
						total_hours = data["end hour working"][Start_hour_length - 1].as_double() - data["start hour working"][Start_hour_length - 1].as_double();
						if (total_minute < 0)
						{
							total_minute = 60 + total_minute;
							total_hours = total_hours - 1;
							total_time = total_hours + (total_minute / 60);
						}
						else
						{
							total_time = total_hours + (total_minute / 60);
						}
						if (total_time > 10)
						{
							total_time = 0;
							cout << "Yod did not exit from work at time please add inquiries to managaer that change you the working hours \n(For this time working hours for this date is 0)" << endl;
							data["working hours"].push_back(total_time);
							write_to_file(alldata, path);
							break;
						}
						else
						{
							data["working hours"].push_back(total_time);
							write_to_file(alldata, path);
							break;
						}
					}
					else
					{
						cout << "You must enter shift before exit" << endl;
					}
				}
				case 3:
					break;
				default:
					cout << "Invalid value. Please try again. Enter your choice: 1-3." << endl;
					cin >> choice;
					break;
				}
			} while (choice != 3);
		}
	}
}

void Employee_Salary_History(string employee_id)
{
	bool flag_help = false;
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
			int month, year;
			do
			{
				cout << "Enter month (1-12) and year to watch previous salary" << endl;
				cin >> month >> year;
			} while (month > 12 || month < 0);
			int montt_year_length = data["previous month for salary"].size();
			for (size_t j = 0; j < montt_year_length; j++)
			{
				if (data["previous month for salary"][j] == month & data["previous year for salary"][j] == year)
				{
					flag_help = true;
					cout << "Salary for month: " << month << " year: " << year << " is: " << data["previous salary"][j] << "$" << endl;
				}
			}
			if (!flag_help)
			{
				cout << "There is no salary information for this month and year" << endl;
			}
		}
	}
}

string Get_employee_name(string employee_id)
{
	string path = "./database.json";
	fstream is(path);
	if (!is)
	{
		cout << "Cannot open " << path << endl;
		return "Error";
	}
	json alldata = json::parse(is);
	string employee_name = "Error-no suce employee";
	for (std::size_t i = 0; i < alldata.size(); ++i)
	{
		json& data = alldata[i];
		if (data["id"] == employee_id)
		{
			employee_name = data["first name"].as_string() + " " + data["last name"].as_string();
		}
	}
	return employee_name;
}

void insert_employee_rating(string employee_id, int rate)
{
	string path = "./database.json";
	fstream is(path);
	if (!is)
	{
		cout << "Cannot open " << path << endl;
		return;
	}
	json alldata = json::parse(is);

	double new_amount_of_rating = 0;
	double new_number_of_rating = 0;

	for (std::size_t i = 0; i < alldata.size(); ++i)
	{
		json& data = alldata[i];
		if (data["id"] == employee_id)
		{
			new_amount_of_rating = data["amount of rating"].as_double();
			new_number_of_rating = data["number of rating"].as_double();

			new_number_of_rating++;
			new_amount_of_rating += (double)rate;

			std::error_code ec;
			replace(data, "/amount of rating", json(new_amount_of_rating), ec);
			if (ec)
			{
				cout << ec.message() << std::endl;
			}
			else
			{
				write_to_file(alldata, path);
			}
			replace(data, "/number of rating", json(new_number_of_rating), ec);
			if (ec)
			{
				cout << ec.message() << std::endl;
			}
			else
			{
				write_to_file(alldata, path);
			}
			break;
		}
	}
}

//manager functions**************************************************************************************************
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
		cout << "6.User guide" << endl;
		cout << "7.EXIT SYSTEM" << endl;
		cin >> choice;
		system("color 9");
		switch (choice) {
		case 1:
			Edit_Account(manager_id);
			break;
		case 2:
			Manager_Statistics();
			//statistics
			break;
		case 3:
			//Manage Inquiries
			Manage_Inquiries_Status();
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
				}
			}
			break;
		case 6:
			Manager_Guide();
			break;
		case 7:
			cout << "Back to login screen" << endl;
			break;
		default:
			cout << "Invalid value. Please try again. Enter your choice: 1-6." << endl;
			cin >> choice;
			break;
		}
	} while (choice != 7);
}

void Manager_Guide()
{
	cout << "Hello, I will teach you now how to use the system." << endl << endl
		<< "The main menu: " << endl
		<< "1.Edit your Account  ->  Gives you the ability to edit your details (Address, Mail and more..)" << endl
		<< "2.View company statistics  ->  Shows you everything you need to know about the company (Average hourly wage, Company employees and more..)" << endl
		<< "3.Manage Inquiries  ->  Gives you the ability to manage all the inquiries from your employees and send them your answers" << endl
		<< "4.View/edit employee details  ->  With this feature you can view every detail about all the employees in the company, and you can edit those details when you need" << endl
		<< "5.Add/Remove employee  ->  Gives you the ability to manage all the employees in the company, you can click add and add new employee or click remove and remove employee" << endl << endl
		<< "Now I belive you are ready to use the system" << endl
		<< "Have a great day HR4U" << endl;
	cout << "-----------------------------------" << endl << endl;
}

void Manager_Get_Employees_Details(string employee_id)
{
	bool flag = false;
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
			flag = true;
			cout << "-ID : " << data["id"] << endl;
			cout << "-First Name : " << data["first name"] << endl;
			cout << "-Last Name : " << data["last name"] << endl;
			cout << "-profession : " << data["profession"] << endl;
			//cout << "-Salary : " << Salary_Calc(employee_id) << "NIS" << endl ; // Need a Matan's function : "Salary_Calc"
		}

		if (flag)
			break;
	}
}

void Manage_Inquiries_Status() {
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

		if (data["type"] == "employee")
		{
			string employee_id = data["id"].as_string();
			Employee_All_Inquiries(employee_id);
		}
	}
	string employee_id;
	cout << "Enter the id you want to edit:" << endl;
	cin >> employee_id;
	for (std::size_t i = 0; i < alldata.size(); ++i)
	{
		json& data = alldata[i];

		if (data["id"] == employee_id)
		{
			int inquiries_length = data["inquiries status"].size(); //inquiries array length
			if (inquiries_length == 0)
			{
				cout << "Manager,please PAY ATTENTION! this employee has no inquiries yet." << endl;
				break; //means no inquiries have been found for this employee
			}
			else {
				cout << "Enter the inquiry number you would like to update (by status)" << endl;
				int i; //choice of specific inquiry index
				cin >> i;
				while (i > inquiries_length) { //checks the if the inquiry number is in the range
					cout << "Error. Inquiry number doesn`t exist. please try again" << endl;
					cin >> i;
				}

				string ans;
				cout << "Enter your choice (approved/disapproved)" << endl;
				cin >> ans;

				std::error_code ec;
				string inquiry_to_replace = "/inquiries status/";
				inquiry_to_replace += to_string(i);
				cout << inquiry_to_replace; //what inquiry status we want to replace

				jsonpointer::replace(data, inquiry_to_replace, json(ans), ec); //changes specific inquiry status
				if (ec)
				{
					cout << ec.message() << std::endl;
				}
				else
				{
					cout << "Changes saved.Thank you,Manager." << endl;
					write_to_file(alldata, path); //updates inquiries in file
				}
			}
		}


	}

}

void Manager_Edit_Employee(string employee_id)
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
		bool changed = false;
		json& data = alldata[i];
		if (data["id"] == employee_id)
		{
			changed = true;
			int choice;
			do
			{
				cout << "Please choose which employee details you xant to change :" << endl;
				cout << "1.First Name" << endl;
				cout << "2.Last Name" << endl;
				cout << "3.ID" << endl;
				cout << "4.Hourly Wage" << endl;
				cout << "5.Type" << endl;
				cout << "6.Exit" << endl;
				cin >> choice;

				while (1)
				{
					if (!(choice >= 1 && choice <= 6))
						cout << "Bad input : Enter again , your choise must be between 1 and 6" << endl;
					else
						break;
					cin >> choice;
				}

				switch (choice)
				{
				case 1:
				{
					//edit first name
					cout << "Enter the first name:" << endl;
					string new_first_name;
					cin >> new_first_name;
					std::error_code ec;
					jsonpointer::replace(data, "/first name", json(new_first_name), ec);
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
					//edit last name
					cout << "Enter the last name:" << endl;
					string new_last_name;
					cin >> new_last_name;
					std::error_code ec;
					jsonpointer::replace(data, "/last name", json(new_last_name), ec);
					if (ec)
						cout << ec.message() << std::endl;
					else
					{
						write_to_file(alldata, path); //updates the file(actually,re-writes it)! 
						cout << "Data updated successfully ! " << endl;
					}
				}
				break;

				case 3:
				{
					//edit id
					cout << "Enter the new id /:" << endl;
					string new_id;
					cin >> new_id;
					while (1)//while the id is invaild.
					{
						if (new_id.length() == 9)
						{
							int counter = 0;
							for (int i = 0; i < new_id.length(); ++i)
							{
								if (new_id[i] >= '0' && new_id[i] <= '9') //checks wether the id contains only digits 0-9
									++counter;
							}
							if (counter == 9)
								break;
						}
						else
							cout << "ID number invalid.Please enter 9 digits ID:" << endl;
						cin >> new_id;
					}
					std::error_code ec;
					jsonpointer::replace(data, "/id", json(new_id), ec);
					if (ec)
						cout << ec.message() << std::endl;
					else
					{
						write_to_file(alldata, path); //updates the file(actually,re-writes it)! 
						cout << "Data updated successfully ! " << endl;
					}
				}
				break;

				case 4:
				{
					//edit hourly wage
					cout << "Enter the new hourly wage:" << endl;
					int new_hourly_wage;
					cin >> new_hourly_wage;
					while (1)
					{
						if (new_hourly_wage <= 0)
							cout << "Bad input : Enter again , hourly wage must be a positve number" << endl;
						else
							break;
						cin >> new_hourly_wage;
					}
					std::error_code ec;
					jsonpointer::replace(data, "/hourly wage", json(new_hourly_wage), ec);
					if (ec)
						cout << ec.message() << std::endl;
					else
					{
						write_to_file(alldata, path); //updates the file(actually,re-writes it)! 
						cout << "Data updated successfully ! " << endl;
					}
				}
				break;

				case 5:
				{
					//edit type
					cout << "Enter the new type:" << endl;
					string new_type;
					cin >> new_type;
					std::error_code ec;
					jsonpointer::replace(data, "/type", json(new_type), ec);
					if (ec)
						cout << ec.message() << std::endl;
					else
					{
						write_to_file(alldata, path); //updates the file(actually,re-writes it)! 
						cout << "Data updated successfully ! " << endl;
					}
				}
				break;

				case 6:
					cout << "Good Bye.";
					break;

				default:
					cout << "Invalid value. Please try again. Enter your choice: 1-5." << endl;
					cin >> choice;
				}

			} while (choice != 6); // end of while	
		} // end of "if"

		if (changed)
			break;

	} // end of "for"
} // end of "Manager_Edit_Employee"

void Manager_Statistics()
{
	int choice;
	float average_hourly_wage = 0;
	int counter_total_employee = 0;
	float counter_employee = 0;
	int counter_manager = 0;
	float total_working_hour = 0;
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
		if (data["type"] == "employee")
		{
			counter_total_employee++;
			counter_employee++;
			int hour_length = data["working hours"].size();
			cout << hour_length << endl;
			average_hourly_wage += data["hourly wage"].as_double();
			for (size_t j = 0; j < hour_length; j++)
			{
				total_working_hour += data["working hours"][j].as_double();
			}
		}
		if (data["type"] == "manager")
		{
			counter_total_employee++;
			counter_manager++;
		}
	}
	do
	{
		cout << "1.Total Employee In company" << endl;
		cout << "2.Total working Hours" << endl;
		cout << "3.Average Hourly Wage" << endl;
		cout << "4.Exit" << endl;
		cin >> choice;
		if (choice == 1)
		{
			cout << "Total Manager: " << counter_manager << endl;
			cout << "Total Regular Employee: " << counter_employee << endl;
			cout << "Total Employee(manager and regular employee): " << counter_total_employee << endl;
		}
		else if (choice == 2)
		{
			cout << "Total working hours is: " << total_working_hour << "hours" << endl;
		}
		else if (choice == 3)
		{
			cout << "Average Hourly Wage: " << (average_hourly_wage / counter_employee) << " $" << endl;
		}
		else if (choice == 4)
		{
			break;
		}
		else
		{
			cout << "Invalid value. Please try again. Enter your choice: 1-4." << endl;
			cin >> choice;
			break;
		}
	} while (choice != 4);
}

//employer functions*************************************************************************************************
void Employer_Guide()
{
	cout << "Hello, I will teach you now how to use the system." << endl << endl
		<< "First of all, the main menu: " << endl
		<< "1.Search & book employees  ->  Gives you the ability look for an employee by the proffesion you want in a date you choose and set the price you would like to pay for him, by click Search you will see all the results in a page called Results" << endl
		<< "2.Rate employee  ->  Gives you the ability to rate employee by his ID in a scale from 1 to 5 (5 is the best rate employee can get)" << endl
		<< "3.Hiring history  ->  Gives you the ability to see all of the hiring you have been made" << endl << endl << endl
		<< "Now you're going to learn about the Results page." << endl << endl
		<< "In the result page, you will see all the employees you can hire by filtering you've been made in the Search page, the results will be shown by the name of the employee, his job, his rating and than you will have the option to hire him by clicking book" << endl << endl
		<< "Now I belive you are ready to use the system" << endl
		<< "Have a great day HR4U" << endl;
	cout << "-----------------------------------" << endl << endl;
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

void Employer_Menu(string employer_id)
{
	string title = "Employer menu";
	print_title(title);//only for printing colourful title
	int choice;
	do
	{
		cout << "Please enter your choice:" << endl;
		cout << "1. Search & book employees" << endl;
		cout << "2. Rate employee" << endl;
		cout << "3. Watch hiring history" << endl;
		cout << "4. Edit account" << endl;
		cout << " 5.User guide" << endl;
		cout << "6. Exit system(back to login screen)" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			Employer_Search(employer_id);
			break;
		case 2:
			Employer_rate_employee(employer_id);
			break;
		case 3:
			Employer_Employment_History(employer_id);
			break;
		case 4:
			Employer_Edit_Account(employer_id);
			break;
		case 5:
			Employer_Guide();
			break;
		case 6:
			cout << "Back to login screen" << endl;
			break;
		default:
			cout << "Wrong choice, try again" << endl;
			break;
		}
	} while (choice != 6);
}

bool Employer_Check_Availability(string employee_id, string date, string profession, int hourly_wage)//Checking an employee's availability on the selected date 
{
	string path = "./database.json";
	fstream is(path);
	if (!is)
	{
		cout << "Cannot open " << path << endl;
		return false;
	}
	json alldata = json::parse(is);

	for (std::size_t i = 0; i < alldata.size(); ++i) //runs all objectss
	{
		json& data = alldata[i];
		if (data["id"] == employee_id)
		{
			if (data["profession"] == profession)
			{
				if (data["hourly wage"] <= hourly_wage)
				{
					if (Available_Date(employee_id, date))
						return true;

				}
			}
			break;
		}

	}
	return false;

}

void Employer_Search(string employer_id)
{
	string path = "./database.json";
	fstream is(path);
	if (!is)
	{
		cout << "Cannot open " << path << endl;
		return;
	}
	json alldata = json::parse(is);
	int hourly_wage, counter;
	string date, proffesion, choice2;
	int choice;
	bool flag;
	do
	{
		counter = 0;
		flag = false;
		cout << "Please enter selected date (XX.XX.XXXX):     ";
		cin >> date;
		cout << "Enter profession:     ";
		cin >> proffesion;
		cout << "Enter employee's maximum hourly wage:     ";
		cin >> hourly_wage;
		cout << endl << "Results:" << endl << endl;
		cout << "date: " << date << "      " << "proffesion: " << proffesion << endl << endl;
		cout << "-------------------------------------------------------------------" << endl;
		for (std::size_t i = 0; i < alldata.size(); ++i)
		{
			json& data = alldata[i];
			if (data["type"] == "employee")
			{

				if (Employer_Check_Availability(data["id"].as_string(), date, proffesion, hourly_wage))
				{
					counter++;
					cout << "ID:" << data["id"].as_string() << "     Name:" << data["first name"].as_string() << " " << data["last name"].as_string() << "     Hourly wage:" << data["hourly wage"].as_string() << endl << endl;
				}

			}
		}
		if (counter != 0)
		{
			cout << "About" << counter << " results" << endl << endl;
			cout << "Enter the ID number of the employee you would like to hire:" << endl;
			cout << "OR Enter:" << endl;
			cout << "1. Search again" << endl;
			cout << "2. Back to menu" << endl;
			cin >> choice2;
			if (choice2 != "1")
			{
				if (choice2 == "2")
				{
					cout << " You chose Back to menu" << endl;
					return;
				}
				else
				{
					do
					{
						for (std::size_t i = 0; i < alldata.size(); ++i)
						{
							json& data = alldata[i];
							if (data["type"] == "employee")
							{
								if (data["id"] == choice2)
								{
									data["unavailability"].push_back(date);//update employee
									write_to_file(alldata, path);
									//update employer
									for (std::size_t i = 0; i < alldata.size(); ++i)
									{
										if (data["id"] == employer_id)
										{
											data["hierd id"].push_back(choice2);
											data["hierd proffesion"].push_back(proffesion);
											data["hiring date"].push_back(date);
											data["hiring rate"].push_back(0);//temp rate until he will rate after the employee will finish the job
											write_to_file(alldata, path);
										}
									}
									flag = true;
									break;
								}
							}
						}
						if (flag)
						{
							cout << "Employee hiring completed successfully! Do not forget to rate according to your satisfaction at the end!" << endl << endl;
							cout << "Please select from the following options: " << endl;
							cout << "1. Search again" << endl;
							cout << "2. Back to manu" << endl;
							cin >> choice;
							if (choice != 1 && choice != 2)
							{
								do
								{
									cout << "Error! Invalid input. Try again" << endl << endl;
									cout << "Please select from the following options: " << endl;
									cout << "1. Search again" << endl;
									cout << "2. Back" << endl;
									cin >> choice;
								} while (choice != 1 && choice != 2);
							}
							choice2 = "1";

						}
						else
						{


							cout << "Error!No employee with this ID number" << endl << endl;
							cout << "Enter the ID number of the employee you would like to hire:" << endl;
							cout << "OR Enter:" << endl;
							cout << "1. Search again" << endl;
							cout << "2. Back to menu" << endl;
							cin >> choice2;


						}

					} while (choice2 != "1" && choice2 != "2");
					if (choice2 == "2")
					{
						cout << " You chose Back to menu" << endl;
						return;
					}


				}
			}
			else
			{
				choice = 1;
			}

		}
		else
		{
			cout << "No results were found" << endl << endl;
			cout << "Please select from the following options: " << endl;
			cout << "1. Search again" << endl;
			cout << "2. Back to manu" << endl;
			cin >> choice;
			if (choice != 1 && choice != 2)
			{
				do
				{
					cout << "Error! Invalid input. Try again" << endl << endl;
					cout << "Please select from the following options: " << endl;
					cout << "1. Search again" << endl;
					cout << "2. Back" << endl;
					cin >> choice;
				} while (choice != 1 && choice != 2);
			}

		}
	} while (choice != 2);


}

void Employer_rate_employee(string employer_id)
{
	string path = "./database.json";
	fstream is(path);
	if (!is)
	{
		cout << "Cannot open " << path << endl;
		return;
	}
	json alldata = json::parse(is);

	string employee_id;
	int length, rate;
	string rate_to_replace = "/hiring rate/";
	double rating;
	string print_rating;
	int choice;
	int select = 2;

	do
	{
		cout << "List of employees you employed:" << endl << endl;
		for (std::size_t i = 0; i < alldata.size(); ++i)
		{
			json& data = alldata[i];
			if (data["id"] == employer_id)
			{
				int j = 0;
				length = data["hierd id"].size();
				for (;j < length;j++)
				{
					cout << "Row number      DATE               ID            SATISFACTION             PROFESSION" << endl << endl;


					rating = data["hiring rate"][j].as_double();
					if (rating == 0)
						print_rating = "No rating";
					else
						print_rating = data["hiring rate"][j].as_string();

					cout << j + 1 << "              " << data["hiring date"][j].as_string() << "       " << data["hierd id"][j].as_string() << "            " << print_rating << "                    " << data["hierd proffesion"][j].as_string() << endl << endl << endl;

				}
				cout << "---------------------------------------------------" << endl << endl;
				j -= 1;
				cout << "Enter the number in the line that shows the employee you hired on a specific date that you would like to rank: " << endl;
				cin >> choice;
				choice -= 1;

				if (choice > j || choice < 0)
				{
					do
					{
						if(j==0)
							cout<< "Error! Invalid input" << endl;
						else
							cout << "Error! not a number between " << 1 << " to " << j + 1 << endl;
						cin >> choice;
						choice -= 1;

					} while (choice > (j - 1) || choice < 1);
				}

				rating = data["hiring rate"][choice].as_double();
				if (rating == 0)//not ranked this employee yet
				{
					employee_id = data["hierd id"][choice].as_string();
					cout << "You choose to rank " << Get_employee_name(employee_id) << ". The date you hired " << Get_employee_name(employee_id) << " is: " << data["hiring date"] << endl << endl;
					cout << "What is your level of satisfaction with the service? " << endl;
					cout << "The rating is between 1 and 5 stars" << endl << "1 - Not satisfied at all" << endl << "5 - Very satisfied " << endl;
					cin >> rate;
					if (rate > 5 || rate < 1)
					{
						do
						{
							cout << "Error! not a number between 1 to 5";
							cout << "What is your level of satisfaction with the service? " << endl;
							cout << "The rating is between 1 and 5 stars" << endl << "1 (Not satisfied at all)  to 5 (Very satisfied) " << endl;
							cin >> rate;
						} while (rate > 5 || rate < 1);
					}
					insert_employee_rating(employee_id, rate);
					rate_to_replace += to_string(choice);
					error_code ec;
					replace(data, rate_to_replace, json(rate), ec);
					if (ec)
					{
						cout << ec.message() << std::endl;
					}
					else
					{
						cout << "The rating was successfully received! Thank you, your opinion is important to us" << endl << endl;
						write_to_file(alldata, path);
						cout << "Choose from the following options:" << endl;
						cout << "1.Rank another employee" << endl;
						cout << "2.back to menu" << endl;
						cin >> select;
						if (select != 1 && select != 2)
						{
							do
							{
								cout << "Error!Invalid input" << endl;
								cout << "Choose from the following options:" << endl;
								cout << "1.Rank another employee" << endl;
								cout << "2.back to menu" << endl;
								cin >> select;
							} while (select != 1 && select != 2);
						}

					}
				}
				else//already ranked this employee
				{
					cout << "You have already rated the employee you selected on that specific work day." << endl << endl;
					cout << "Choose from the following options:" << endl;
					cout << "1.Rank different employee" << endl;
					cout << "2.back to menu" << endl;
					cin >> select;
					if (select != 1 && select != 2)
					{
						do
						{
							cout << "Error!Invalid input" << endl;
							cout << "Choose from the following options:" << endl;
							cout << "1.Rank another employee" << endl;
							cout << "2.back to menu" << endl;
							cin >> select;
						} while (select != 1 && select != 2);
					}
				}


			}
		}

	} while (select != 2);
}

void Employer_Employment_History(string employer_id)
{
	std::string path = "./database.json";
	std::fstream is(path);
	if (!is)
	{
		std::cout << "Cannot open " << path << std::endl;
		return;
	}
	json alldata = json::parse(is);
	bool flag = false;
	double rating;
	string print_rating;
	for (std::size_t i = 0; i < alldata.size(); ++i)
	{
		json& data = alldata[i];
		if (data["id"] == employer_id)
		{
			flag = true;

			int lenght = (int)(data["hierd id"].size());

			cout << "DATE                 ID             SATISFACTION                 PROFESSION" << endl << endl;

			for (int y = 0; y < lenght; ++y)
			{
				rating = data["hiring rate"][y].as_double();
				if (rating == 0)
					print_rating = "No rating";
				else
					print_rating = data["hiring rate"][y].as_string();

				cout << data["hiring date"][y].as_string() << "       " << data["hierd id"][y].as_string() << "            " << print_rating << "                    " << data["hierd id"][y].as_string() << endl;
			}
		}
		if (flag)
			break;
	}
}


//main
int main()
{
	Employer_rate_employee("985621855");
	Logo();
	Login();
	return 0;
}

