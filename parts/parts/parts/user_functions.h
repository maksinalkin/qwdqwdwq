#pragma once
#include <vector>
#include <memory>
#include "register_users.h"
#include "checkInput.h"
#include "sorting.h"
#include "file_handler.h"
#include "print_file.h"
#include "supply_struct.h"

void admin_functions();

void user_functions_sort() {

	char choice;
	std::string hint =
		"����������:\n"
		"1.����������� �� ������ (���������� �������)\n"
		"������:\n"
		"2.����������� �� ��������\n"
		"3.����������� �� ����\n"
		"4.����������� �� ��������\n"
		"��������:\n"
		"5.����������� ����\n"
		"6.����������� �� ����������\n"
		"0.�����\n";

	std::vector<std::shared_ptr<Supply>> supply;
	std::vector<std::shared_ptr<Supplier>> supplier;
	std::vector<std::shared_ptr<Parts>> parts;
	ReadSuppliersFromFile(supplier, SUPPLIERS_FILE);
	ReadSupplyFromFile(supply, SUPPLY_FILE);
	ReadPartsFromFile(parts, PART_FILE);

	while (1) {

		choice = CharInput(hint);
		ClearConsole();
		switch (choice) {

		case '1': {

			SortSuppliersByAddress(supplier);
			PrintSuppliersFromVector(supplier, true);
			break;
		}
		case '2': {

			SortPartsByName(parts);
			PrintPartsFromVector(parts, true);
			break;
		}
		case '3': {

			SortPartsByPrice(parts);
			PrintPartsFromVector(parts, true);
			break;
		}
		case '4': {

			SortPartsByVendorCode(parts);
			PrintPartsFromVector(parts, true);
			break;
		}
		case '5': {

			SortSupplyByDate(supply);
			PrintSupplyFromVector(supply, true);
			break;
		}
		case '6': {

			SortSupplyByQuantity(supply);
			PrintSupplyFromVector(supply, true);
			break;
		}

		case '0': {
			supply.clear();
			supplier.clear();
			parts.clear();
			return;
		}
		default: {
			std::cout << "\n��� ������ ��������, ������� ������:\n";
		}

		}
	}	
}

void user_functions_find_filter() {
	int choice;
	std::string hint =
		"����������:\n"
		"1.������ �� ������\n"
		"2.������ �� ��������\n"
		"������:\n"
		"3.������ �� �����\n"
		"4.������ �� ��������\n"
		"5.������ �� ����\n"
		"6.����������� �� ����\n"
		"7.����������� �� ��������\n"
		"��������:\n"
		"8.������ �� ����\n"
		"9.������ �� ����������\n"
		"10.����������� �� ����\n"
		"11.����������� �� ����������\n"
		"12.������� ������ �� 3 ����� �������������� �������\n"
		"0.�����\n";

	std::vector<std::shared_ptr<Supply>> supply;
	std::vector<std::shared_ptr<Supplier>> supplier;
	std::vector<std::shared_ptr<Parts>> parts;
	ReadSuppliersFromFile(supplier, SUPPLIERS_FILE);
	ReadSupplyFromFile(supply, SUPPLY_FILE);
	ReadPartsFromFile(parts, PART_FILE);
	
	while (1) {
		std::cout << hint;
		choice = IntInputWithBounds(0, 12);
		ClearConsole();
		switch (choice) {

		case 1: {

			SearchSupplierByAdress(supplier);
			break;

		}
		case 2: {

			SearchSupplierByPhone(supplier);
			break;
		}
		case 3: {

			SearchPartsByName(parts);
			break;
		}
		case 4: {
			SearchPartsByVendorCode(parts);
			break;
		}
		case 5: {
			SearchPartsByPrice(parts);
			break;
		}
		case 6: {
			FilterPartsByPrice(parts);
			break;
		}
		case 7: {
			FilterPartsByVendorCode(parts);
			break;
		}
		case 8: {
			SearchSupplyByDate(supply);
			break;
		}
		case 9: {
			SearchSupplyByQuantity(supply);
			break;
		}
		case 10: {
			FilterSupplyByDate(supply);
			break;
		}
		case 11: {
			FilterSupplyByQuantity(supply);
			break;
		}
		case 12: {
			FindFrequentParts();
			break;
		}
		case 0: {
			supply.clear();
			supplier.clear();
			parts.clear();
			return;
		}
		}
	}
}

void admin_functions() {
	
	std::string hint1 = "1.����������\n2.�����/������\n";	
	std::string hint =
		"1.����������/������/�����\t"
		"2.����������� ���� �������������\t"
		"3.������� ������������\n"
		"4.���������������� ������������\t"
		"5.���������������� ��������������\t"
		"6.���������� �����\n" //(����������, ������, ��������)
		"7.�������� ����������\t\t"
		"8.�������� ������\t\t\t"
		"9.�������� ��������\n"
		"10.�������� ����������\t\t"
		"11.�������� ������\t\t\t"
		"12.�������� ��������\n"
		"13.������� ����������\t\t"
		"14.������� ������\t\t\t"
		"15.������� ��������\n"
		"0.�����\n";

	std::vector<std::shared_ptr<Supply>> supply;
	std::vector<std::shared_ptr<Supplier>> supplier;
	std::vector<std::shared_ptr<Parts>> parts;
	ReadSuppliersFromFile(supplier, SUPPLIERS_FILE);
	ReadSupplyFromFile(supply, SUPPLY_FILE);
	ReadPartsFromFile(parts, PART_FILE);

	while (1) {
		std::cout << hint;
		switch (IntInput()) {
		case 0:
			supply.clear();
			supplier.clear();
			parts.clear();
			return;
		case 1: {
			ClearConsole();
			switch (CharInput(hint1)) {
			case '1':
				user_functions_sort();
				break;
			case '2':
				user_functions_find_filter();
				break;
			default:
				NoSuchOption();
				break;
			}
			break;
		}
		case 2:
			ViewUsersFromFile(USER_FILE, true);
			break;
		case 3:
			DeleteUser(USER_FILE);
			break;
		case 4:
			RegisterUser(USER_FILE);
			break;
		case 5:
			RegisterUser(ADMIN_FILE);
			break;
		case 6:
			ClearConsole();
			ViewSupplierFromFile(SUPPLIERS_FILE, true);
			ViewPartsFromFile(PART_FILE, true);
			ViewSupplyFromFile(SUPPLY_FILE, true);
			break;
		case 7:
			AddSupplierToFile(SUPPLIERS_FILE);
			break;
		case 8:
			AddPartsToFile(PART_FILE);
			break;
		case 9:
			AddSupplyToFile(SUPPLY_FILE);
			break;
		case 10:
			EditSupplier(SUPPLIERS_FILE);
			break;
		case 11:
			EditParts(PART_FILE);
			break;
		case 12:
			EditSupply(SUPPLY_FILE);
			break;
		case 13:
			DeleteSupplierFromFile(SUPPLIERS_FILE);
			break;
		case 14:
			DeletePartsFromFile(PART_FILE);
			break;
		case 15:
			DeleteSupplyFromFile(SUPPLY_FILE);
			break;
		default:
			NoSuchOption();
			break;
		}
	}
}
