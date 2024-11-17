#pragma once
#include <iostream>

/******************������� ������, ����� ���������*********************/
void ClearConsole() {
	system("cls");
}

void ClearConsoleEnter() {
	std::cout << "\n������� ���� ����� ����������." << std::endl;
	std::cin.get();
	ClearConsole();
}

void pressEnterMessage(std::string message) {
	ClearConsole();
	std::cout << message << "\n\n";
	ClearConsoleEnter();
}

void NoSuchOption() {
	std::cout << "\n��� ������ ��������, ������� ������:\n";
	ClearConsoleEnter();
}
/*********************************************************************/