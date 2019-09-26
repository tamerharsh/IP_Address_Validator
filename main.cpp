// IP_Address_Validator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include<string>
#include<vector>
#include<utility>
#include<algorithm>
#include<exception>

using  TestDataType=std::vector<std::pair<std::string, bool>>;

TestDataType test_func()
{
	TestDataType  true_result
	{	std::make_pair("192.16.169.1:1054 : 1526", true),
		std::make_pair("0.0.0.0:0: 0", true),
		std::make_pair("125.125.125.125:4231:2258", true),
		std::make_pair("255.255.255.255:65535:65535", true),
		std::make_pair("1255.-255.255.255:65535:65535", false),
		std::make_pair("a.-255.255.255:65535:65535", false),
		std::make_pair("a.82505.8255.8255:865535:865535", false),
		std::make_pair("88.82505.8255.8255:865535:865535", false),
	};
	return true_result;
}
bool validator(const std::vector<std::string>& ip_part,int min, int max)
{
	bool result=true;
	for (auto x : ip_part)
	{
		 int num=stoi(x);
		if ((num-max)*(num - min) <= 0) { result = true; }
		else return false;
	}
	
	return result;
}
bool ip_validator(const std::string& input_ip)
{
	
	int count = 0, pos = 0;
	std::string delimiter_1 = ".", delimiter_2 = ":";
	size_t found=0, loc_delimiter_1, loc_delimiter_2;
	std::vector<std::string> temp_res1,temp_res2;
	
	//string parsing
	std::string temp1 = input_ip.substr(0, input_ip.find(":"));
	std::string temp2 = input_ip.substr(input_ip.find(":")
	+1);

	//string ip
	while (count < 4)
	{
		loc_delimiter_1 = temp1.find(delimiter_1, pos);
		std::string tokenized_data=temp1.substr(pos, loc_delimiter_1-pos);
		temp_res1.push_back(tokenized_data);
		pos = ++loc_delimiter_1;
		count++;
	}
	
	//for ports 
	int count_ = 0;
	while (count_ < 2)
	{
		loc_delimiter_2=temp2.find(":", found);
		std::string tokenized_data=temp2.substr(found , loc_delimiter_2-found);
		temp_res2.push_back(tokenized_data);
		found = ++loc_delimiter_2;
		count_++;
		
	}
	
	// validator
	auto final_result = validator(temp_res1, 0, 255) && validator(temp_res2, 0, 65535);
	if (final_result)
	{
		return true;
	}
	else 
	{
		return false;
	}
	
	
}
int main()
{
	try 
	{
		auto res = test_func();
		std::cout << std::boolalpha;

		for (auto x : res)
		{
			std::cout << "Candidate Ip : " << x.first << " Desired ->" << x.second << " Test_Result->" << ip_validator(x.first) << std::endl;
			std::cout << "\n======================================================================\n";
		}
	
	}
	catch (std::exception &e)
	{
		 std::exception("Error found in converison ");
	}
	
	return 0;
}
