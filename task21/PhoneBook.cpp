#include "PhoneBook.h"
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cctype>

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

void PhoneBook::SearchByName(const PhoneBook book[], int count) 
{
	if (count == 0) 
	{
		cout << "\nТелефонная книга пуста!\n";
		return;
	}

	char query[100];
	cout << "\nВведите часть ФИО для поиска: ";
	cin.getline(query, sizeof(query));

	if (query[0] == '\0') 
	{
		cout << "Поиск отменён.\n";
		return;
	}

	bool foundAny = false;
	cout << "\nРезультаты поиска:\n";

	for (int i = 0; i < count; i++) 
	{
		const char* fname = book[i].GetFullName();
		if (fname && fname[0] != '\0' && ContainsIgnoreCase(fname, query)) 
		{
			cout << "\nКонтакт #" << (i + 1) << ":\n";
			book[i].Output();
			foundAny = true;
		}
	}

	if (!foundAny) 
	{
		cout << "Ничего не найдено.\n";
	}
}

void PhoneBook::DeleteContact(PhoneBook book[], int& count) 
{
	if (count == 0) 
	{
		cout << "\nТелефонная книга пуста!\n";
		return;
	}

	int num;
	cout << "\nВсего контактов: " << count << "\n";
	cout << "Введите номер контакта для удаления (1 - " << count << "): ";
	cin >> num;
	cin.ignore(10000, '\n');

	if (num < 1 || num > count) 
	{
		cout << "Неверный номер!\n";
		return;
	}

	int index = num - 1;

	cout << "\nУдаляется контакт:\n";
	book[index].Output();

	cout << "\nПодтвердить удаление? (y / n): ";
	char confirm;
	cin >> confirm;
	cin.ignore(10000, '\n');

	if (confirm != 'y' && confirm != 'Y') 
	{
		cout << "Удаление отменено.\n";
		return;
	}

	for (int i = index; i < count - 1; i++) 
	{
		book[i] = book[i + 1];
	}

	count--;
	cout << "Контакт удалён.\n";
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

bool PhoneBook::ContainsIgnoreCase(const char* str, const char* substr) 
{
	if (!str || !substr || substr[0] == '\0')
	{
		return false;
	}

	char buf1[512] = { 0 };
	char buf2[512] = { 0 };

	int i = 0;
	while (str[i] && i < 511) 
	{
		buf1[i] = (char)tolower((unsigned char)str[i]);
		i++;
	}
	buf1[i] = '\0';

	i = 0;
	while (substr[i] && i < 511) 
	{
		buf2[i] = (char)tolower((unsigned char)substr[i]);
		i++;
	}
	buf2[i] = '\0';

	return strstr(buf1, buf2) != nullptr;
}

char* PhoneBook::CopyString(const char* src) const 
{
	if (!src) return nullptr;
	size_t len = strlen(src) + 1;
	char* dst = new char[len];
	strcpy_s(dst, len, src);
	return dst;
}

int PhoneBook::StringLength(const char* str) const 
{
	return str ? static_cast<int>(strlen(str)) : 0;
}
