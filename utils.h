#pragma once
#include "pch.h"
#include <string>
#include <locale>
using namespace std;

extern inline string upper(string input)
{
	string ret;

	std::locale loc;
	for (unsigned int i = 0; i < input.length(); i++)
	{
		ret += std::toupper(input[i], loc);
	}

	
	return ret;
}

extern inline string trim(string line) {

	string trimmed = "";
	string trimlst;
	string exclude = " \t";

	if (line.empty()) {
		return line;
	}

	size_t pos = line.find_first_not_of(exclude);

	if (pos == string::npos) {
		return trimmed;
	}
	trimmed = line.substr(line.find_first_not_of(exclude));
	pos = trimmed.find_last_not_of(exclude);

	trimlst = trimmed.substr(0, pos + 1);
	if (pos == string::npos) {
		return trimmed;
	}
	return trimlst;
}
