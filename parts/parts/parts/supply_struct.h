#pragma once
#include <iostream>

struct Supplier { // ����������
	int supplier_id{ 0 }; // id
	std::string address{ "" }; // �����
	std::string phone{ "" }; // ���������� �����
}; // 3

struct Parts { // ������
	int part_id{ 0 }; // id
 	std::string name{ "" }; // ��������
	int vendor_code{ 0 }; // �������
	double price{ 0.0 }; // ����
	std::string note{ "" }; // ����������
}; // 5

struct Supply { // ��������
	int supplier_id{ 0 }; // id ����������
	int part_id{ 0 }; // id ������
	int quantity{ 0 }; // ���������� �������
	std::string date{ "" }; // ���� 
}; // 4
