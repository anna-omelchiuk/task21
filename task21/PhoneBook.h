#pragma once

class PhoneBook 
{
private:
	char* fullName;
	char homePhone[15];
	char workPhone[15];
	char mobilePhone[15];
	char* extraInfo;

public:
	PhoneBook();
	PhoneBook(const char* name, const char* home, const char* work, const char* mobile, const char* extra);
	PhoneBook(const PhoneBook& other);

	~PhoneBook();

	PhoneBook& operator=(const PhoneBook& other);

	const char* GetFullName() const;
	const char* GetHomePhone() const;
	const char* GetWorkPhone() const;
	const char* GetMobilePhone() const;	
	const char* GetExtraInfo() const;

	void SetFullName(const char* name);
	void SetHomePhone(const char* home);
	void SetWorkPhone(const char* work);
	void SetMobilePhone(const char* mobile);
	void SetExtraInfo(const char* extra);

	void Output() const;
	void Input(PhoneBook book[], int& count, int max);

	static void SearchByName(const PhoneBook book[], int count);
	static void DeleteContact(PhoneBook book[], int& count);
	static void SaveToFile(const PhoneBook book[], int count, const char* filename);
	static void LoadFromFile(PhoneBook book[], int& count, int max, const char* filename);

	static bool ContainsIgnoreCase(const char* str, const char* substr);

private:
	char* CopyString(const char* src) const;
	int StringLength(const char* str) const;

};