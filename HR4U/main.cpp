#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <iostream>
#include <json.hpp>
#include<ctime>

using namespace jsoncons;
using namespace std;


static const char alphnum[] = "0123456789" "!@#$%^&*" "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz";
int strLen = sizeof(alphnum) - 1;
char GenRand()
{
	return alphnum[rand() % strLen];
}

string randompass()
{
	int n, c = 0, s = 0;
	srand(time(0));
	n = rand() % 10 + 1000; //randoms a 6 digits password
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

string* createpassword(const string& name) {
	string username = name + to_string(rand() % 1000);
	string password = randompass();
	string username_password[2] = { username,password };
	return username_password;
}

int check()
{

	string name = "bar";
	string* passwordgen = createpassword(name);
	cout << "your username is:";
	cout << "your password is:";

}

int main()
{
	cout << "Hello World\n";
	cout << "bar & bar test";
	// hello
	return 0;
}





