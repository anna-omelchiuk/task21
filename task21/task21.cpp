#include <iostream>
#include <windows.h>
#include "PhoneBook.h"

using namespace std;

const int CONTACT_MAX = 100;
const char* FILENAME = "phonebook.dat";

int main()
{
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);

	PhoneBook book[CONTACT_MAX + 1];
	int count = 0;
	int choice;

	do {
		cout << "\nТелефонная книга\n";
		cout << "\n1. Добавить контакт\n";
		cout << "2. Показать все контакты\n";
		cout << "3. Сохранить в файл\n";
		cout << "4. Загрузить из файла\n";
		cout << "0. Выход\n";
		cout << "\nВыберите действие: ";
		cin >> choice;
		cin.ignore();

		switch (choice) 
		{
			case 1:
				if (count >= CONTACT_MAX) 
				{
					cout << "\nТелефонная книга заполнена. Нельзя добавить новый контакт.\n";
				}
				else 
				{
					book[count].Input(book, count, CONTACT_MAX);
				}
				break;

			case 2:
				if (count == 0) 
				{
					cout << "\nТелефонная книга пуста!\n";
				}
				else 
				{
					for (int i = 0; i < count; i++) 
					{
						cout << "\nКонтакт #" << (i + 1) << ":\n";
						book[i].Output();
					}
				}
				break;

			case 3:
				PhoneBook::SaveToFile(book, count, FILENAME);
				break;

			case 4:
				PhoneBook::LoadFromFile(book, count, CONTACT_MAX, FILENAME);
				break;

			case 0:
				cout << "\nВыход из программы.\n";
				break;

			default:
				cout << "\nНеверный выбор. Попробуйте снова.\n";
				break;
		}
	} while (choice != 0);

	return 0;
}
