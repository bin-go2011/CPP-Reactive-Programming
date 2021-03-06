// SimpleJSON.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>
#include <random>

#include "cpprest/json.h"
#include "cpprest/http_listener.h"
#include "cpprest/uri.h"
#include "cpprest/asyncrt_utils.h"

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#else
# include <sys/time.h>
#endif

///////////////////////////////////
// A Console Application to demonstrate JSON API
// available as part of the C++ SDK
//
//
using namespace std;
using namespace web;
using namespace utility;
using namespace http;
using namespace web::http::experimental::listener;

///////////////////////////////////////
// Define a Simple struct to demonstrate the 
// Working of JSON API
//
struct EMPLOYEE_INFO
{
	utility::string_t name;
	int age;
	double salary;
	/////////////////////////////////
	// Convert a JSON Object to a C++ Struct
	//
	static EMPLOYEE_INFO JSonToObject(const web::json::object & object)
	{
		EMPLOYEE_INFO result;
		result.name = object.at(U("name")).as_string();
		result.age = object.at(U("age")).as_integer();
		result.salary = object.at(U("salary")).as_double();
		return result;
	}

	///////////////////////////////////////////
	// Convert a C++ struct to a Json Value
	//
	web::json::value ObjectToJson() const
	{
		web::json::value result = web::json::value::object();
		result[U("name")] = web::json::value::string(name);
		result[U("age")] = web::json::value::number(age);
		result[U("salary")] = web::json::value::number(salary);
		return result;
	}
};



//////////////////////////////////////////
//
// Create a Json Object group and Embed and 
// Array in it...
//

void MakeAndShowJSONObject()
{
	// Create a JSON object (the group)
	json::value group;
	group[L"Title"] = json::value::string(U("Native Developers"));
	group[L"Subtitle"] = json::value::string(U("C++ devekioers on Windws/GNU LINUX"));
	group[L"Description"] = json::value::string(U("A Short Description here "));


	// Create a JSON object (the item)
	json::value item;
	item[L"Name"] = json::value::string(U("Praseed Pai"));
	item[L"Skill"] = json::value::string(U("C++ / java "));
	// Create a JSON object (the item)
	json::value item2;
	item2[L"Name"] = json::value::string(U("Peter Abraham"));
	item2[L"Skill"] = json::value::string(U("C++ / C# "));
	// Create the items array
	json::value items;
	items[0] = item;
	items[1] = item2;

	// Assign the items array as the value for the Resources key
	group[L"Resources"] = items;

	// Write the current JSON value to wide char string stream
	utility::stringstream_t stream;
	group.serialize(stream);

	// Display the string stream
	std::wcout << stream.str();
}

///////////////////////////////
//
//
//

int wmain(int argc, wchar_t *argv[])
{
	EMPLOYEE_INFO dm;
	dm.name = L"Sabhir Bhatia";
	dm.age = 50;
	dm.salary = 10000;
	wcout << dm.ObjectToJson().serialize() << endl;



	
	utility::string_t port = U("{\"Name\": \"Alex Stepanov\",\"Age\": 55,\"salary\":20000}");;
	
	web::json::value json_par;

	json::value obj = json::value::parse(port);
	
	wcout << obj.serialize() << endl;

	
	MakeAndShowJSONObject();
	getchar();
	return 0;
}
