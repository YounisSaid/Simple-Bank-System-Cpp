#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

const string ClientsFileName = "Clients.txt";
void ShowMainMenu();
struct Sclient
{
	string AccountNumber;
	string Pincode;
	string Name;
	string Phone;
	double AccountBalance;
	bool Mark = false;
};
vector<string>SplitString(string Line, string delim = "#//#")
{
	vector<string>Vstring;
	short pos = 0;
	string Sword;
	while ((pos = Line.find(delim)) != string::npos)
	{
		Sword = Line.substr(0, pos);
		if (Sword != "")
		{
			Vstring.push_back(Sword);
			Line.erase(0, pos + delim.length());
		}
	}
	if (Line != "")
	{
		Vstring.push_back(Line);
	}

	return Vstring;
}
Sclient ConvertLineToRecord(string Line)
{
	vector<string>Vstring = SplitString(Line);
	Sclient Client;

	Client.AccountNumber = Vstring[0];
	Client.Pincode = Vstring[1];
	Client.Name = Vstring[2];
	Client.Phone = Vstring[3];
	Client.AccountBalance = stod(Vstring[4]);
	return Client;

}
vector<Sclient>LoadClientDataFromFile(string ClientsFileName)
{

	fstream Myfile;
	vector<Sclient>Vclients;
	Myfile.open(ClientsFileName, ios::in);
	if (Myfile.is_open())
	{
		Sclient Client;
		string Line;

		while (getline(Myfile, Line))
		{
			Client = ConvertLineToRecord(Line);
			Vclients.push_back(Client);
		}
	}
	Myfile.close();
	return Vclients;
}
void ShowClientList(Sclient Client)
{
	cout << "| " << left << setw(15) << Client.AccountNumber;
	cout << "| " << left << setw(10) << Client.Pincode;
	cout << "| " << left << setw(40) << Client.Name;
	cout << "| " << left << setw(12) << Client.Phone;
	cout << "| " << left << setw(12) << Client.AccountBalance;
}
void ShowClientsList()
{
	vector<Sclient>Vclients = LoadClientDataFromFile(ClientsFileName);
	cout << "\n\t\t\t\t\tClient List (" << Vclients.size() << ")Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	for (Sclient& C : Vclients)
	{
		ShowClientList(C);
		cout << endl;
	}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

}
Sclient FindClientByAccountNumber(string AccountNumber)
{

	vector<Sclient> Vclients = LoadClientDataFromFile(ClientsFileName);
	Sclient Client;
	for (Sclient& C : Vclients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;

		}
	}
	return Client;
}

bool Isclientexists(string AccountNumber)
{

	vector<Sclient> Vclients = LoadClientDataFromFile(ClientsFileName);
	Sclient Client;
	for (Sclient& C : Vclients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;

}
void GoBackToMainMenue()
{
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowMainMenu();
}
void returntoClientScreen(string AccountNumber)
{
	if (Isclientexists(AccountNumber))
	{
		cout << "AccountNumber is Taken Please try Something Else";
		GoBackToMainMenue();
	}
}
Sclient ReadNewClient()
{
	Sclient Client;
	cout << "==================================================================================\n";
	cout << "\t\t\t\tAddClientScreen\n";
	cout << "==================================================================================\n";
	cout << "Please Enter Accout Number : ";
	getline(cin >> ws, Client.AccountNumber);
	returntoClientScreen(Client.AccountNumber);
	cout << "\nPlease Enter pin Code : ";
	getline(cin, Client.Pincode);
	cout << "\nPlease Enter Client Name : ";
	getline(cin, Client.Name);
	cout << "\nPlease Enter Client Phone : ";
	getline(cin, Client.Phone);
	cout << "\nPlease Enter Account Balance : ";
	cin >> Client.AccountBalance;
	cout << "Client Added Suceccfully, Do You Want To Add More ? (Y,N)";
	return Client;
}
string ConvertRecordToLine(Sclient Client, string delim = "#//#")
{

	string SClient;
	SClient += Client.AccountNumber + delim;
	SClient += Client.Pincode + delim;
	SClient += Client.Name + delim;
	SClient += Client.Phone + delim;
	SClient += to_string(Client.AccountBalance);
	return SClient;

}

void LoadClientDataToFile(string ClientsFileName, Sclient Client)
{
	fstream Myfile;
	string NewClient = ConvertRecordToLine(Client);
	Myfile.open(ClientsFileName, ios::out | ios::app);
	if (Myfile.is_open())
	{
		Myfile << NewClient << endl;
	}
	Myfile.close();
}
void AddNewClient()
{
	Sclient Client = ReadNewClient();
	LoadClientDataToFile(ClientsFileName, Client);
}
void AddClients()
{
	char Answer = 'Y';
	do
	{
		AddNewClient();
		cin >> Answer;
	} while (toupper(Answer) == 'Y');
}
void PrintClientCard(Sclient Client)
{
	cout << "\nThe following are the client details:\n";
	cout << "\nAccout Number: " << Client.AccountNumber;
	cout << "\nPin Code : " << Client.Pincode;
	cout << "\nName : " << Client.Name;
	cout << "\nPhone : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
}

string ClientAccountNumber()
{
	string AccountNumber;
	cout << "Enter Account Number : ";
	cin >> AccountNumber;
	return AccountNumber;
}

vector< Sclient> MarkClientToDeleteOrUpdate(string AccountNumber)
{
	vector<Sclient> Vclients = LoadClientDataFromFile(ClientsFileName);
	for (Sclient& C : Vclients)
	{
		if (C.AccountNumber == AccountNumber)
		{

			C.Mark = true;

		}
	}
	return Vclients;
}
vector<Sclient>SaveClientDataToFileAndDelete(string ClientsFileName, string AccountNumber)
{
	vector<Sclient>Vclients = MarkClientToDeleteOrUpdate(AccountNumber);
	fstream Myfile;
	Myfile.open(ClientsFileName, ios::out);
	if (Myfile.is_open())
	{
		string line;
		for (Sclient& C : Vclients)
		{

			if (C.Mark == false)
			{

				line = ConvertRecordToLine(C);
				Myfile << line << endl;
			}
		}
	}
	Myfile.close();
	Vclients = LoadClientDataFromFile(ClientsFileName);
	return Vclients;
}
void DeleteClientRecordByAccountNumber()
{
	char Answer = 'Y';
	cout << "==================================================================================\n";
	cout << "\t\t\t\tDelete Screen\n";
	cout << "==================================================================================\n";

	string AccountNumber = ClientAccountNumber();
	cout << "Are You Sure You want To Delete This Client ? (Y,N)";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		SaveClientDataToFileAndDelete(ClientsFileName, AccountNumber);
		cout << "Clinet Deleted Sucussefully";
	}

}

void UpdateScreen()
{


	cout << "==================================================================================\n";
	cout << "\t\t\t\tUpdate Screen\n";
	cout << "==================================================================================\n";
	cout << "Please Enter Account Number : ";




}

Sclient PutClientRecord(string AccountNumber)
{
	Sclient Data;
	Data.AccountNumber = AccountNumber;
	cout << "\nPlease Enter your pincode : ";
	getline(cin >> ws, Data.Pincode);
	cout << "\nPlease Enter your name : ";
	getline(cin, Data.Name);
	cout << "\nPlease Enter your Phone : ";
	getline(cin, Data.Phone);
	cout << "\nPlease Enter your Account Balane : ";
	cin >> Data.AccountBalance;

	return Data;
}
vector<Sclient>SaveClientDataToFileAndUpdate()
{
	UpdateScreen();
	string AccountNumber;
	cin >> AccountNumber;
	Sclient Client = FindClientByAccountNumber(AccountNumber);
	PrintClientCard(Client);
	cout << "Are you sure you Want to Update This Client ? (Y,N) ";
	char Answer = 'n';
	cin >> Answer;
	vector<Sclient>Vclients = MarkClientToDeleteOrUpdate(AccountNumber);
	if (Answer == 'y' || Answer == 'Y')
	{
		fstream Myfile;
		Myfile.open(ClientsFileName, ios::out);
		if (Myfile.is_open())
		{
			string line;
			for (Sclient& C : Vclients)
			{

				if (C.Mark == false)
				{

					line = ConvertRecordToLine(C);
					Myfile << line << endl;
				}
				else
				{
					C = PutClientRecord(AccountNumber);
					line = ConvertRecordToLine(C);
					Myfile << line << endl;
				}
			}
		}
		Myfile.close();

	}

	return Vclients;
}

void findClient()
{
	cout << "==================================================================================\n";
	cout << "\t\t\t\tFind Screen\n";
	cout << "==================================================================================\n";
	cout << "Please Enter Account Number : ";
	string AccountNumber;
	cin >> AccountNumber;
	Sclient Client = FindClientByAccountNumber(AccountNumber);
	if (Client.AccountNumber == "")
	{
		cout << "\nClient is not Found :(\n";
		return;
	}
	PrintClientCard(Client);
}
void ShowEndScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tProgram Ends :-)";
	cout << "\n-----------------------------------\n";
}

short ReadMainMenueOption()
{
	cout << "Choose what do you want to do? [1 to 6]? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}

void PerfromMainMenueOption()
{
	short num = 0;
	cin >> num;
	switch (num)
	{
	case 1:
	{
		system("cls");
		ShowClientsList();
		GoBackToMainMenue();
		break;
	}

	case 2:
	{
		system("cls");
		AddClients();
		GoBackToMainMenue();
		break;
	}

	case 3:
	{
		system("cls");
		DeleteClientRecordByAccountNumber();
		GoBackToMainMenue();
		break;
	}

	case 4:
	{
		system("cls");
		SaveClientDataToFileAndUpdate();
		GoBackToMainMenue();
		break;
	}

	case 5:
	{
		system("cls");
		findClient();
		GoBackToMainMenue();
		break;
	}

	case 6:
	{
		system("cls");
		ShowEndScreen();
		break;
	}

	}
}

void ShowMainMenu()
{
	system("cls");
	cout << "==================================================================================\n";
	cout << "\t\t\t\tMain Menu Screen\n";
	cout << "==================================================================================\n";
	cout << "\t[1] Show Client List\n";
	cout << "\t[2] Add New Client\n";
	cout << "\t[3] Delete Client \n";
	cout << "\t[4] Update Client \n";
	cout << "\t[5] Find Client \n";
	cout << "\t[6] Exit\n";
	cout << "==================================================================================\n";
	cout << "Choose What You Want To Do [1 to 6] ?";

	PerfromMainMenueOption();

}

int main()
{
	ShowMainMenu();
	system("pause>0");
	return 0;
}
