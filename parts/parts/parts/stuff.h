#pragma once
#define NOMINMAX
#include <iostream>
#include <string> // ��� getline
#include <sstream> // ��� stringstream
#include <locale> // ��� RussianLanguage()
#include <Windows.h> // ��� RussianLanguage()
#include <fstream> // ��� ������
#include <vector> // ��� int getSpareID()
#include <algorithm> // ��� bool containsIntVector()
#include <memory> // smart pointers

#define ADMIN_FILE "admins.txt"
#define USER_FILE "users.txt"
#define SUPPLIERS_FILE "suppliers.txt"
#define PART_FILE "parts.txt"
#define SUPPLY_FILE "supply.txt"

/***********************��������� ��������� �������*******************/

void RussianLanguage() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
}

size_t lengthOfDouble(double d) {
	// ������� ���������� ����� ����� � ��������� ������
	std::stringstream ss("");
	ss.clear();
	ss << d;

	std::string str = ss.str();

	size_t length = str.length();
	return length;
}

bool containsIntVector(std::vector<int>& IDs, int& id) {
	
	// ������� ��������� ���� �� ����� � �������
	
	auto it = std::find(IDs.begin(), IDs.end(), id);
	if (it != IDs.end()) {
		return true;
	}
	else {
		return false;
	}
}

int getSpareID(std::string filename) {
	/* ������� ��� ��������� ����������� ID. 
	* ������� ��������� ����, � ����� �� ����� ��������� ������ ����� (�� �������), 
	* ������� �������� ID (�.�. � ������ ���� ��������� � ������ ������ ���� ������� ID, 
	* � ����� ��������� ����������).
	* ����� ��� ID ��������� � std::vector<int> � ����� ������� ������� ������ ��������� (����������)
	* id, ������� � ����� ��������� �� �������.
	*/
	
	std::ifstream input_file(filename); // �������� �����
	std::string line;
	std::vector<int> lines_id;
	int id{ 0 };

	if (!input_file.is_open()) { // ��������
		std::cout << "������ �������� ����� " << filename << std::endl;
	}

	while (getline(input_file, line)) { // ��������� id

		std::stringstream ss(line);
		ss >> id;
		lines_id.push_back(id); // ������� id � ������
		ss.clear();
	}
	while (true) { // ���� �� ������ ��������� id ���������� �����
		++id;
		if (containsIntVector(lines_id, id)) {
			continue;
		}
		else {
			return id;
		}
	}
	lines_id.clear();
	input_file.close();
}

void replaceChars(std::string& str, char oldChar, char newChar) {
	/* ������� ��� ������ ������ ������� �� ������,
	* �������� ������ "hello world", ���� char oldChar == 'o', char newChar == '1',
	* ����� ������� ����� hell1 w1rld
	*/
	for (char& c : str) {
		if (c == oldChar) {
			c = newChar;
		}
	}
}

void tryToCreateFile(const std::string& filename) { 
	/* ���� ����� (������) ���������� ���,
	*  �� ���� ����� ������� ������ ����
	*/
	std::ifstream input_file(filename);
	if (!input_file.is_open()) {
		std::ofstream createFile(filename, std::ios::trunc);
		createFile.close();
	}
	input_file.close();
}

void makeFiles() {
	tryToCreateFile(USER_FILE);
	tryToCreateFile(ADMIN_FILE);
	tryToCreateFile(SUPPLIERS_FILE);
	tryToCreateFile(SUPPLY_FILE);
	tryToCreateFile(PART_FILE);
}

std::string strip(std::string& str) {
	size_t start = str.find_first_not_of(" \t\n");
	size_t end = str.find_last_not_of(" \t\n");

	if (start == std::string::npos || end == std::string::npos) {
		return "";
	}

	return str.substr(start, end - start + 1);
}

namespace SUPPLIER {

	std::string id{ "id" };
	std::string address{ "�����" };
	std::string phone{ "�������" };
	
	std::vector<std::string> namings =
	{ id, address, phone };

	std::vector<size_t> fields = 
	{ id.length(), address.length(), (size_t) 15  }; // +375(44)12345 - 15 ��������
}

namespace PARTS {
	std::string id{ "id" };
	std::string name{ "��������" };
	std::string vendor_code{ "�������" };
	std::string price{ "����" };
	std::string note{ "����������" }; // 5 �����
	std::vector<std::string> namings =
	{ id, name, vendor_code, price, note };

	std::vector<size_t> fields = 
	{ id.length(), name.length(), vendor_code.length(),
		price.length(), note.length() };
}

namespace USER {
	
	std::string login = "�����";
	std::string password = "������"; // 2 ������
	std::vector<std::string> namings =
	{ login, password };

	std::vector <size_t> fields = 
	{ login.length(), password.length() };
}

namespace SUPPLY {
	std::string supplier_id{ "id ����������" };
	std::string part_id{ "id ������" };
	std::string quantity{ "����������" };
	std::string date{ "����" };
	std::vector<std::string> namings =
	{ supplier_id, part_id, quantity, date };

	std::vector <size_t> fields =
	{ supplier_id.length(), part_id.length(), quantity.length(),
		date.length() };
}

void resetValuesNamespace() {
	SUPPLIER::fields[0] = SUPPLIER::id.length();
	SUPPLIER::fields[1] = SUPPLIER::address.length();
	SUPPLIER::fields[2] = (size_t)15;
	PARTS::fields[0] = PARTS::id.length();
	PARTS::fields[1] = PARTS::name.length();
	PARTS::fields[2] = PARTS::vendor_code.length();
	PARTS::fields[3] = PARTS::price.length();
	PARTS::fields[4] = PARTS::note.length();
	USER::fields[0] = USER::login.length();
	USER::fields[1] = USER::password.length();
	SUPPLY::fields[0] = SUPPLY::supplier_id.length();
	SUPPLY::fields[1] = SUPPLY::part_id.length();
	SUPPLY::fields[2] = SUPPLY::quantity.length();
	SUPPLY::fields[3] = SUPPLY::date.length();
}

void ClearVectorsNamespace() {
	SUPPLIER::fields.clear();
	SUPPLIER::namings.clear();
	PARTS::namings.clear();
	PARTS::namings.clear();
	USER::namings.clear();
	USER::namings.clear();
	SUPPLY::namings.clear();
	SUPPLY::namings.clear();
}