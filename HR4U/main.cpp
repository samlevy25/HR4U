#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include <cstdlib>
#include <iostream>
#include <json.hpp>
#include <jsoncons_ext/jmespath/jmespath.hpp>
#include<ctime>
#include <stdexcept>
#include <string>
#include <vector>
#include <map>
#include <jsoncons_ext/jsonpointer/jsonpointer.hpp>
#include <fstream>

using namespace jsoncons;
using namespace std;


void first_example_a()
{
	std::string path = "C:/Users/Bar Sela/source/repos/HR4U/HR4U/database.json";
	std::fstream is(path);
	if (!is)
	{
		std::cout << "Cannot open " << path << std::endl;
		return;
	}
	json books = json::parse(is);

	for (std::size_t i = 0; i < books.size(); ++i)
	{
		try
		{
			json& book = books[i];
			std::string author = book["author"].as<std::string>();
			std::string title = book["title"].as<std::string>();
			double price = book["price"].as<double>();
			std::cout << author << ", " << title << ", " << price << std::endl;
		}
		catch (const std::exception & e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}
int main()
{
	first_example_a();
	return 0;
}



