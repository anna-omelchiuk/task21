#include "PhoneBook.h"
#include <cstring>
#include <iostream>
#include <cstdio>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

PhoneBook::PhoneBook() : fullName(nullptr), extraInfo(nullptr)
{
	homePhone[0] = '\0';
	workPhone[0] = '\0';
	mobilePhone[0] = '\0';
}

PhoneBook::PhoneBook(const char* name, const char* home, const char* work, const char* mobile, const char* extra) : fullName(nullptr), extraInfo(nullptr)
{
	SetFullName(name);
	SetHomePhone(home);
	SetWorkPhone(work);
	SetMobilePhone(mobile);
	SetExtraInfo(extra);
}

PhoneBook::PhoneBook(const PhoneBook& other) : fullName(nullptr), extraInfo(nullptr)
{
	*this = other;
}

PhoneBook::~PhoneBook()
{
	delete[] fullName;
	delete[] extraInfo;
}

PhoneBook& PhoneBook::operator=(const PhoneBook& other)
{
	if (this == &other) return *this;

	delete[] fullName;
	delete[] extraInfo;

	fullName = CopyString(other.fullName);
	extraInfo = CopyString(other.extraInfo);

	strncpy_s(homePhone, other.homePhone, sizeof(homePhone) - 1);
	homePhone[sizeof(homePhone) - 1] = '\0';

	strncpy_s(workPhone, other.workPhone, sizeof(workPhone) - 1);
	workPhone[sizeof(workPhone) - 1] = '\0';

	strncpy_s(mobilePhone, other.mobilePhone, sizeof(mobilePhone) - 1);
	mobilePhone[sizeof(mobilePhone) - 1] = '\0';

	return *this;
}

///////////////////// Геттеры ///////////////////////////


const char* PhoneBook::GetFullName() const
{
	return fullName ? fullName : "";
}

const char* PhoneBook::GetHomePhone() const
{
	return homePhone;
}

const char* PhoneBook::GetWorkPhone() const
{
	return workPhone;
}

const char* PhoneBook::GetMobilePhone() const
{
	return mobilePhone;
}

const char* PhoneBook::GetExtraInfo() const
{
	return extraInfo ? extraInfo : "";
}


//////////////////// Сеттеры ///////////////////////////


void PhoneBook::SetFullName(const char* name)
{
	delete[] fullName;
	fullName = CopyString(name);
}

void PhoneBook::SetHomePhone(const char* home)
{
	strncpy_s(homePhone, home ? home : "", sizeof(homePhone) - 1);
	homePhone[sizeof(homePhone) - 1] = '\0';
}

void PhoneBook::SetWorkPhone(const char* work)
{
	strncpy_s(workPhone, work ? work : "", sizeof(workPhone) - 1);
	workPhone[sizeof(workPhone) - 1] = '\0';
}

void PhoneBook::SetMobilePhone(const char* mobile)
{
	strncpy_s(mobilePhone, mobile ? mobile : "", sizeof(mobilePhone) - 1);
	mobilePhone[sizeof(mobilePhone) - 1] = '\0';
}

void PhoneBook::SetExtraInfo(const char* extra)
{
	delete[] extraInfo;
	extraInfo = CopyString(extra);
}


////////////////// Служебные функции //////////////////


void PhoneBook::Output() const
{
	cout << "Полное имя: " << (fullName ? fullName : "(не указано)") << endl;
	cout << "Домашний телефон: " << homePhone << endl;
	cout << "Рабочий телефон: " << workPhone << endl;
	cout << "Мобильный телефон: " << mobilePhone << endl;
	cout << "Дополнительная информация: " << (extraInfo ? extraInfo : "(не указано)") << endl;
}

void PhoneBook::Input(PhoneBook book[], int& count, int max)
{
	if (count >= max) 
	{
		cout << "Телефонная книга заполнена!\n";
		return;
	}

	char name[100]{}, home[30]{}, work[30]{}, mobile[30]{}, extra[200]{};

	cout << "Введите данные для новой записи:\n";

	cout << "ФИО: ";
	cin.getline(name, 100);

	cout << "Домашний телефон: ";        
	cin.getline(home, 30);

	cout << "Рабочий телефон: ";     
	cin.getline(work, 30);

	cout << "Мобильный телефон: ";       
	cin.getline(mobile, 30);

	cout << "Дополнительная информация: ";        
	cin.getline(extra, 200);

	book[count].SetFullName(name);
	book[count].SetHomePhone(home);
	book[count].SetWorkPhone(work);
	book[count].SetMobilePhone(mobile);
	book[count].SetExtraInfo(extra);

	count++;
	cout << "Данные добавлены!\n";
}

void PhoneBook::SaveToFile(const PhoneBook book[], int count, const char* filename)
{
	FILE* file = nullptr;
	if (fopen_s(&file, filename, "wb") != 0 || !file) 
	{
		cout << "Не удалось открыть файл для записи!\n";
		return;
	}
	fwrite(&count, sizeof(int), 1, file);
	for (int i = 0; i < count; i++) 
	{
		int len = book[i].fullName ? strlen(book[i].fullName) + 1 : 0;
		fwrite(&len, sizeof(int), 1, file);

		if (len > 0) fwrite(book[i].fullName, 1, len, file);

		fwrite(book[i].homePhone, 1, sizeof(book[i].homePhone), file);
		fwrite(book[i].workPhone, 1, sizeof(book[i].workPhone), file);
		fwrite(book[i].mobilePhone, 1, sizeof(book[i].mobilePhone), file);

		len = book[i].extraInfo ? strlen(book[i].extraInfo) + 1 : 0;
		fwrite(&len, sizeof(int), 1, file);
		if (len > 0) fwrite(book[i].extraInfo, 1, len, file);
	}
	fclose(file);
	cout << "Данные сохранены в файл!\n";
}

void PhoneBook::LoadFromFile(PhoneBook book[], int& count, int max, const char* filename)
{
	FILE* file = nullptr;
	if (fopen_s(&file, filename, "rb") != 0 || !file) 
	{
		cout << "Не удалось открыть файл для чтения!\n";
		return;
	}
	int FileCount;
	fread(&FileCount, sizeof(int), 1, file);

	count = 0;
	for (int i = 0; i < FileCount && count < max; i++) 
	{
		int len;

		fread(&len, sizeof(int), 1, file);

		if (len > 0) 
		{
			char* buffer = new char[len];
			fread(buffer, 1, len, file);
			book[count].SetFullName(buffer);
			delete[] buffer;
		}
		else 
		{
			book[count].SetFullName("");
		}

		fread(book[count].homePhone, 1, sizeof(book[count].homePhone), file);
		fread(book[count].workPhone, 1, sizeof(book[count].workPhone), file);
		fread(book[count].mobilePhone, 1, sizeof(book[count].mobilePhone), file);

		fread(&len, sizeof(int), 1, file);

		if (len > 0) 
		{
			char* buffer = new char[len];
			fread(buffer, 1, len, file);
			book[count].SetExtraInfo(buffer);
			delete[] buffer;
		}
		else 
		{
			book[count].SetExtraInfo("");
		}

		count++;
	}
	fclose(file);
	cout << "Данные загружены из файла!\n";
}

char* PhoneBook::CopyString(const char* src) const
{
	if (!src || src[0] == '\0')
		return nullptr;

	int length = StringLength(src);
	char* dest = new char[length + 1];
	strcpy_s(dest, length + 1, src);
	return dest;
}



int PhoneBook::StringLength(const char* str) const
{
	int length = 0;
	while (str && str[length] != '\0')
		length++;
	return length;
}
