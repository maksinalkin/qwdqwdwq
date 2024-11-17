#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <sstream>
#include "supply_struct.h"
#include "stuff.h"
#include "checkInput.h"
#include <unordered_map>
#define NUMBER_OF_ELEMENTS_TO_FIND 3
// �����, ���������� ��������� Supplier
void SortSuppliersByAddress(std::vector<std::shared_ptr<Supplier>>& suppliers) {
	std::sort(suppliers.begin(), suppliers.end(),
		[](const std::shared_ptr<Supplier>& a, const std::shared_ptr<Supplier>& b) {
			return a->address < b->address;
		}); // ���������� � ������� ������ sort � ����������� � ���� ������ �������
}

void SearchSupplierByPhone(std::vector<std::shared_ptr<Supplier>>& suppliers) {
	
	FindMaxLengthSupplier(suppliers, SUPPLIER::fields);
	std::cout << "������� ����� ��������, �� �������� ������ ����� ����������\n";
	std::string phone;
	bool found = false;
	phone = PhoneInput();
	

	for (auto& value : suppliers){
	
		if (phone == value->phone) {
			PrintOneSupplier(value, SUPPLIER::fields, SUPPLIER::namings, !found);
			if (!found) {
				found = true;
			}
		}
	}
	if (!found) {
		std::cout << "��������� � ����� ������� �������� �� ������." << std::endl;
	}
	ClearConsoleEnter();
}

void SearchSupplierByAdress(std::vector<std::shared_ptr<Supplier>>& suppliers) {
	
	FindMaxLengthSupplier(suppliers, SUPPLIER::fields);

	std::cout << "������� ����� �����, �� �������� ������ ����� ����������\n";
	std::string adress;
	bool found = false;
	adress = StringInput();

	for (auto& value : suppliers) {
		if (adress == value->address) {
			PrintOneSupplier(value, SUPPLIER::fields, SUPPLIER::namings, !found);
			if (!found) {
				found = true;
			}
		}
	}
	if (!found) {
		std::cout << "��������� � ����� ������� �� ������." << std::endl;
	}
	ClearConsoleEnter();
}

/********************************************************************************************/

// �����, ������, ���������� ��������� Parts
void SearchPartsByName(std::vector<std::shared_ptr<Parts>>& parts) {
	
	FindMaxLengthParts(parts, PARTS::fields);

	std::cout << "������� �������� ������, ������� �� ������ �����\n";
	std::string name{ "" };
	name = StringInput();
	std::cout << std::endl << std::endl;
	bool found{ false };

	for (auto& value : parts) {
		if (name == value->name) {
			PrintOnePart(value, PARTS::fields, PARTS::namings, !found);
			if (!found) {
				found = true;
			}
		}
	}
	if (found == false) {
		std::cout << "���� ������ ���� �� ����� �������� ������.\n";
	}
	ClearConsoleEnter();
}

void SearchPartsByVendorCode(std::vector<std::shared_ptr<Parts>>& parts) {
	
	FindMaxLengthParts(parts, PARTS::fields);
	std::cout << "������� ������� ������, ������� �� ������ �����\n";
	int vendor_code{ 0 };
	vendor_code = IntInput();
	std::cout << std::endl << std::endl;
	bool found{ false };

	for (auto& value : parts) {
		if (vendor_code == value->vendor_code) {
			PrintOnePart(value, PARTS::fields, PARTS::namings, !found);
			if (!found) {
				found = true;
			}
		}
	}
	if (found == false) {
		std::cout << "���� ������ ���� �� ����� �������� ������.\n";
	}
	ClearConsoleEnter();
}

void SearchPartsByPrice(std::vector<std::shared_ptr<Parts>>& parts) {

	FindMaxLengthParts(parts, PARTS::fields);
	std::cout << "������� ���� ������, ������� �� ������ �����\n";
	double price{ 0.0 };
	price = DoubleInput();
	std::cout << std::endl << std::endl;
	bool found{ false };

	for (auto& value : parts) {
		if (price == value->price) {
			PrintOnePart(value, PARTS::fields, PARTS::namings, !found);
			if (!found) {
				found = true;
			}

		}
	}
	if (found == false) {
		std::cout << "���� ������ ���� �� ����� �������� ������.\n";
	}
	ClearConsoleEnter();
}

void FilterPartsByPrice(std::vector<std::shared_ptr<Parts>>& parts) {
	
	FindMaxLengthParts(parts, PARTS::fields);
	double min_price{ 0.0 }, max_price = { 0.0 };
	std::cout << "������� ����������� ����: ";
	min_price = DoubleInput();
	std::cout << "������� ������������ ����: ";
	max_price = DoubleInput();
	std::cout << std::endl << std::endl;
	bool found{ false };

	for (auto& value : parts) {
		if (min_price <= value->price and value->price <= max_price) {
			PrintOnePart(value, PARTS::fields, PARTS::namings, !found);
			if (!found) {
				found = true;
			}
		}
	}
	if (found == false) {
		std::cout << "���� ������ ���� �� ����� �������� ������.\n";
	}
	ClearConsoleEnter();
}

void FilterPartsByVendorCode(std::vector<std::shared_ptr<Parts>>& parts) {

	FindMaxLengthParts(parts, PARTS::fields);
	int min_vendor_code{ 0 }, max_vendor_code = { 0 };
	std::cout << "������� ������� (������ �������): ";
	min_vendor_code = IntInput();
	std::cout << "������� ������� (������� �������): ";
	max_vendor_code = IntInput();
	std::cout << std::endl << std::endl;
	bool found{ false };

	for (auto& value : parts) {
		if (min_vendor_code <= value->vendor_code and value->vendor_code <= max_vendor_code) {
			PrintOnePart(value, PARTS::fields, PARTS::namings, !found);
			if (!found) {
				found = true;
			}
		}
	}
	if (found == false) {
		std::cout << "���� ������ ���� �� ����� �������� ������.\n";
	}
	ClearConsoleEnter();
}

void SortPartsByName(std::vector<std::shared_ptr<Parts>>& parts) {
	std::sort(parts.begin(), parts.end(),
		[](const std::shared_ptr<Parts>& a, const std::shared_ptr<Parts>& b) {
			return a->name < b->name;
		}); // ���������� � ������� ������ sort � ����������� � ���� ������ �������
}

void SortPartsByPrice(std::vector<std::shared_ptr<Parts>>& parts) {
	std::sort(parts.begin(), parts.end(),
		[](const std::shared_ptr<Parts>& a, const std::shared_ptr<Parts>& b) {
			return a->price < b->price;
		}); // ���������� � ������� ������ sort � ����������� � ���� ������ �������
}

void SortPartsByVendorCode(std::vector<std::shared_ptr<Parts>>& parts) {
	std::sort(parts.begin(), parts.end(),
		[](const std::shared_ptr<Parts>& a, const std::shared_ptr<Parts>& b) {
			return a->vendor_code < b->vendor_code;
		}); // ���������� � ������� ������ sort � ����������� � ���� ������ �������
}

/********************************************************************************************/

// �����, ������, ���������� ��������� Supply
void SearchSupplyByDate(std::vector<std::shared_ptr<Supply>>& supply) {
	
	FindMaxLengthSupply(supply, SUPPLY::fields);
	std::cout << "������� ����, �� ������� �� ������ ����� ��������\n";
	std::string date{ "" };
	date = DateInput();
	std::cout << std::endl << std::endl;
	bool found{ false };

	for (auto& value : supply) {
		if (date == value->date) {
			PrintOneSupply(value, SUPPLY::fields, SUPPLY::namings, !found);
			if (!found) {
				found = true;
			}
		}
	}
	if (found == false) {
		std::cout << "���� ������ ���� �� ����� �������� ������.\n";
	}
	ClearConsoleEnter();
}

void SearchSupplyByQuantity(std::vector<std::shared_ptr<Supply>>& supply) {

	FindMaxLengthSupply(supply, SUPPLY::fields);
	std::cout << "������� ���������� �������, �� �������� �� ������ ����� ��������\n";
	int quantity{ 0 };
	quantity = IntInput();
	std::cout << std::endl << std::endl;
	bool found{ false };

	for (auto& value : supply) {
		if (quantity == value->quantity) {
			PrintOneSupply(value, SUPPLY::fields, SUPPLY::namings, !found);
			if (!found) {
				found = true;
			}
		}
	}
	if (found == false) {
		std::cout << "���� ������ ���� �� ����� �������� ������.\n";
	}
	ClearConsoleEnter();
}

bool CompareDates(std::shared_ptr<Supply>& date1, std::shared_ptr<Supply>& date2) {
	std::istringstream ss1(date1->date);
	std::istringstream ss2(date2->date);
	char dot;

	int day1, month1, year1, day2, month2, year2;

	ss1 >> day1 >> dot >> month1 >> dot >> year1;
	ss2 >> day2 >> dot >> month2 >> dot >> year2;

	if (year1 != year2) {
		return year1 <= year2;
	}
	if (month1 != month2) {
		return month1 <= month2;
	}

	return day1 <= day2;
}

void FilterSupplyByDate(std::vector<std::shared_ptr<Supply>>& supply) {
	
	FindMaxLengthSupply(supply, SUPPLY::fields);
	std::string min_date{ "" }, max_date{ "" };
	std::cout << "������� ���� (������ �������): ";
	min_date = DateInput();
	std::cout << "������� ���� (������� �������): ";
	max_date = DateInput();
	std::cout << std::endl << std::endl;
	bool found{ false };
	std::shared_ptr<Supply> date1 = std::make_shared<Supply>();
	std::shared_ptr<Supply> date2 = std::make_shared<Supply>();
	date1->date = min_date;
	date2->date = max_date;

	for (auto& value : supply) {
		if (CompareDates(date1, value) and CompareDates(value, date2)) {
			PrintOneSupply(value, SUPPLY::fields, SUPPLY::namings, !found);
			if (!found) {
				found = true;
			}
		}
	}
	if (found == false) {
		std::cout << "���� ������ ���� �� ����� �������� ������.\n";
	}
	ClearConsoleEnter();
}

void FilterSupplyByQuantity(std::vector<std::shared_ptr<Supply>>& supply) {

	FindMaxLengthSupply(supply, SUPPLY::fields);
	double min_quantity{ 0.0 }, max_quantity{ 0.0 };
	std::cout << "������� ���������� ���������� (������ �������): ";
	min_quantity = DoubleInput();
	std::cout << "������� ������������ ���������� (������� �������): ";
	max_quantity = DoubleInput();
	std::cout << std::endl << std::endl;
	bool found{ false };


	for (auto& value : supply) {
		if (min_quantity <= value->quantity and value->quantity <= max_quantity) {
			PrintOneSupply(value, SUPPLY::fields, SUPPLY::namings, !found);
			if (!found) {
				found = true;
			}
		}
	}
	if (found == false) {
		std::cout << "���� ������ ���� �� ����� �������� ������.\n";
	}
	ClearConsoleEnter();
}

void SortSupplyByDate(std::vector<std::shared_ptr<Supply>>& supply) {

	std::sort(supply.begin(), supply.end(), CompareDates);
}

void SortSupplyByQuantity(std::vector<std::shared_ptr<Supply>>& supply) {
	std::sort(supply.begin(), supply.end(), 
		[](const std::shared_ptr<Supply>& a, const std::shared_ptr<Supply>& b) {
			return a->quantity < b->quantity;
		});
}

/********************************************************************************************/

/***********************************�������**************************************************/
/*
*
*  ������� ������ �� 3 ����� �������������� ������� � ���� ����
*
*/

std::vector<int> findTop3Frequent(const std::vector<int>& nums, const int& k) {
	
	std::unordered_map<int, int> freqMap;

	for (int num : nums) {
		freqMap[num]++;
	}

	std::vector<std::pair<int, int>> freqVec(freqMap.begin(), freqMap.end());
	std::sort(freqVec.begin(), freqVec.end(),
		[](const std::pair<int, int>& a, const std::pair<int, int>& b) {
			return a.second > b.second;
		});

	std::vector<int> result;
	for (int i = 0; i < k && i < freqVec.size(); i++) {
		result.push_back(freqVec[i].first);
	}

	return result;
}

bool contains(const std::vector<int>& parts, int elementToFind) {
	return std::find(parts.begin(), parts.end(), elementToFind) != parts.end();
}

void FindFrequentParts() {
    /* ����� �������������� ������ - ��, �������
	* ���� ����� ����������� � ���������, �������
	* � ������� � ���������� ���� �� ID �������, 
	* ������� ����������� ���� �����, � ����� �������
	* �� �� �����.
	*/
	std::vector<std::shared_ptr<Supply>> vector;
	ReadSupplyFromFile(vector, SUPPLY_FILE);

	std::vector<int> part_id, top3;
	for (auto& value : vector) {
		part_id.push_back(value->part_id);
	}
	top3 = findTop3Frequent(part_id, NUMBER_OF_ELEMENTS_TO_FIND);
	for (auto& value : top3) {		
	}
	std::vector<std::shared_ptr<Parts>> parts;
	ReadPartsFromFile(parts, PART_FILE);
	FindMaxLengthParts(parts, PARTS::fields);

	bool found = { false };
	for (auto& value : parts) {
		if (contains(top3, value->part_id)) {
			PrintOnePart(value, PARTS::fields, PARTS::namings, !found);
			if (!found)
				found = true;
		}
	}
	
	ClearConsoleEnter();
}