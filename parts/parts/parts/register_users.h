#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <conio.h>
#include "screen_cleaner.h"
#include "user_struct.h"
#include "print_file.h"
#include "file_handler.h"

#define MAX_ATTEMPTS 3

std::string& PasswordInput(std::string& password) {
	std::cout << "������� ������:\n";
	char ch;
	while ((ch = _getch()) != '\r') { // ������ ������� �� ������� ������� Enter
		if (ch == '\b') { // ���� ������ ������� Backspace
			if (!password.empty()) {
				std::cout << "\b \b"; // ������� ������ �� ������
				password.pop_back(); // ������� ��������� ������ �� ������
			}
		}
		else {
			std::cout << '*'; // ������� ��������� ������ ���������� �������
			password += ch; // �������� ������ � ������
		}
	}
	std::cout << std::endl;
	return password;
}

bool CheckPasswordInDatabase(std::string& username, std::string& password,
	const std::string& filename, bool& isValid, struct User& user) {

	std::ifstream inputFile2(filename);
	bool isAuthenticated = false;
	while (inputFile2 >> username >> password) {
		if (username == user.login && password == user.password) {

			if (isValid = true) {
				std::cout << "�������������� �������." << std::endl;
				isAuthenticated = true;
			}
			else {
				std::cout << "��� ������� ������������." << std::endl;
				ClearConsoleEnter();
				break;
			}
		}
	}
	inputFile2.close();
	return isAuthenticated;
}

bool CheckUsernameInDatabase(std::string& username, std::string& password,
	const std::string& filename, const std::string& login) {

	std::ifstream inputFile1(filename);
	bool validUsername = false;

	while (inputFile1 >> username >> password) {
		if (username == login) {
			validUsername = true;
			break;
		}
	}
	inputFile1.close();
	return validUsername;
}

bool AuthenticateUser(std::string filename) {
	struct User user;
	int attempts = 0;
	bool isAuthenticated = false, isValidUsername = false;
	std::string username{ "" }, password{ "" };

	// ������ ������
	std::cout << "������� �����: ";
	getline(std::cin, user.login);

	isValidUsername = CheckUsernameInDatabase(username, password, filename, user.login);

	if (isValidUsername == false) {
		std::cout << "����� ��������. �������������� ����������." << std::endl;
		ClearConsoleEnter();
		return false;
	}

	while (attempts < MAX_ATTEMPTS) {
		// ������ ������	
		user.password = PasswordInput(user.password);

		isAuthenticated = CheckPasswordInDatabase(username, password, filename, isValidUsername, user);

		// �������� ����� ��� �������� ��������������
		if (isAuthenticated == true) {
			break;
		}
		else {
			attempts++;
			std::cout << "������ ��������. ����������, ��������� �������." << std::endl;
			user.password.clear();
			user.password = "";
			ClearConsoleEnter();
		}
	}

	// �������� ���������� ���������� �������
	if (attempts == MAX_ATTEMPTS) {
		std::cout << "��������� ������������ ������ �������. �������������� ����������" << std::endl;
		ClearConsoleEnter();
	}

	return isAuthenticated;
}

void RegisterUser(std::string filename) {

	std::string username, password, fileUsername, filePassword;
	bool usernameExists = false;
	std::ifstream inputFile(filename);
	// ������ ������ � ������
	std::cout << "������� �����: ";
	getline(std::cin, username);

	// �������� �� ������� �������� � ������
	if (username.find(' ') != std::string::npos) {
		std::cout << "����� �� ������ ��������� �������." << std::endl;
		ClearConsoleEnter();
		return;
	}
	else {
		password = PasswordInput(password);

		// �������� ����� ������
		if (password.length() < 8) {
			std::cout << "������ ������ �������� �� ����� ��� �� 8 ��������."
				<< std::endl;
			ClearConsoleEnter();
			return;
		}
	}

	// �������� ������� ������ � �����
	usernameExists = CheckUsernameInDatabase(fileUsername, filePassword, filename, username);

	//registerUserOtherInfo(user);
	// ����������� ������ ������������ ��� ��������� �� ������, ���� ����� ��� ����������
	if (!usernameExists) {
		std::ofstream outputFile(filename, std::ios::app);
		outputFile << username << " " << password << " " << std::endl;
		outputFile.close();
		std::cout << "������������ ���������������." << std::endl;
		ClearConsoleEnter();
	}
	else {
		std::cout << "������������ � ����� ������� ��� ����������." << std::endl;
		ClearConsoleEnter();
	}
}

void DeleteUser(const std::string& filename) {
	
	ViewUsersFromFile(filename, false);

	std::cout << "������� ��� ������������ ��� ��������: ";
	std::string usernameToDelete{ "" };
	getline(std::cin, usernameToDelete);

	const char* temp_file = "temp.txt";

	std::ifstream input_temp_file(filename);
	if (!input_temp_file.is_open()) {
		std::cout << "������ �������� �����!" << std::endl;
		return;
	}

	std::ofstream output_temp_file(temp_file);
	if (!output_temp_file.is_open()) {
		std::cout << "������ �������� ���������� �����!" << std::endl;
		input_temp_file.close();
		return;
	}

	std::string line;
	bool userDeleted = false;
	while (getline(input_temp_file, line)) {
		std::stringstream ss(line);
		std::string username;
		ss >> username;
		if (username != usernameToDelete) {
			output_temp_file << line << std::endl; // ���������� ������ �� ��������� ����, ���� ��� ������������ �� ���������
		}
		else {
			userDeleted = true; // ������������� ����, ��� ������������ ��� ������
		}
	}

	input_temp_file.close();
	output_temp_file.close();

	if (remove(filename.c_str()) != 0) {
		std::cout << "������ �������� �����!" << std::endl;
		return;
	}
	if (rename(temp_file, filename.c_str()) != 0) {
		std::cout << "������ �������������� ���������� �����!" << std::endl;
		return;
	}

	if (userDeleted) {
		pressEnterMessage("������������ ������� ������.");
	}
	else {
		std::string line{ "" };
		std::stringstream ss(line);
		ss << "������������ � ������ " << usernameToDelete << " �� ������.";
		pressEnterMessage(ss.str());
		ss.clear();
		line.clear();
	}
}