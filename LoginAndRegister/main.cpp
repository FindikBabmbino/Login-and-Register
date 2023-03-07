#include<iostream>
#include<fstream>
#include<map>
using namespace std;

void AskForLoginOrRegister(char &choice);
void LoginUser(map<string,string> &infoMap);
void RegisterUser(map<string, string> &infoMap);
bool CheckIfValueExists(map<string, string> &infoMap,string str);
void SaveToTxtAndMap(map<string, string>& infoMap,string userName,string passWord);
void GetFromTxt(map<string,string> &infoMap);
bool QuitProgram();

int main()
{
	char choice;
	map<string, string> userInfoMap;
	

	GetFromTxt(userInfoMap);

	do
	{
		AskForLoginOrRegister(choice);
		if (choice == 'l') LoginUser(userInfoMap);
		else if (choice == 'r') RegisterUser(userInfoMap);

	} while (!QuitProgram());

	return 0;
}

void AskForLoginOrRegister(char &choice)
{
	bool loginOrRegisterInputFail;
	do
	{
		loginOrRegisterInputFail = false;
		cout << "Do you wish to login or register? (l/r): ";
		cin >> choice;
		choice = tolower(choice);
		if (choice != 'r' && choice != 'l')
		{
			cout << "Please enter a valid option." << endl;
			loginOrRegisterInputFail = true;
		}
	} while (loginOrRegisterInputFail);
}

void LoginUser(map<string, string> &infoMap)
{
	bool loginFail;
	string userName;
	string passWord;

	do
	{
		loginFail = false;
		cout << "Enter your username: ";
		cin >> userName;
		if (!infoMap.count(userName))
		{
			cout << "Username does not exist" << endl;
			loginFail = true;
			continue;
		}

		cout << "Enter your password: ";
		cin >> passWord;
		if(!CheckIfValueExists(infoMap,passWord))
		{
			cout << "Password does not exist. Enter your user name and password again" << endl;
			loginFail = true;
		}
		if (!loginFail)
			cout << "LOGIN SUCCESFUL" << endl;

	} while (loginFail);
}


void RegisterUser(map<string, string> &infoMap)
{
	bool registerFail;

	string userName;
	string passWord;
	do
	{
		registerFail = false;
		cout << "Enter an username: ";
		cin >> userName;
		if(infoMap.count(userName))
		{
			cout << "User name already in system. Retype your username and password" << endl;
			registerFail = true;
			continue;
		}

		cout << "Enter a passowrd: ";
		cin >> passWord;
		if(CheckIfValueExists(infoMap,passWord))
		{
			cout << "Password already in system. Retype your username and password" << endl;
			registerFail = true;
		}
		if(!registerFail)
			SaveToTxtAndMap(infoMap, userName, passWord);

	} while (registerFail);
}

void SaveToTxtAndMap(map<string, string>& infoMap, string userName, string passWord)
{
	ofstream infoText("info.txt",ios::app);
	infoMap.insert({ userName,passWord });
	infoText << endl;
	infoText << userName << " " << passWord;
	infoText.close();
}

void GetFromTxt(map<string, string>& infoMap)
{
	ifstream infoText("info.txt");
	string a, b;
	while (infoText >> a >> b)
	{
		infoMap.insert({ a,b });
	}
	infoText.close();
}

bool QuitProgram()
{
	char choice = ' ';
	while (choice != 'y'&& choice!= 'n')
	{
		cout << "Do you wish to quit? (y(es)/n(o)): ";
		cin >> choice;
		choice = tolower(choice);

		if (choice != 'y' && choice != 'n') cout << "Input a valid character." << endl;
	}
	if (choice == 'y') return true;
	else return false;
}

bool CheckIfValueExists(map<string, string> &infoMap,string str)
{
	for(auto var:infoMap)
	{
		if (str == var.second) return true;
	}
	return false;
}