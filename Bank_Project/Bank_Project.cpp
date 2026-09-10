#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cstdlib>

using namespace std;
const string ClientFileName = "Client.txt";
struct SClient {

	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};

enum enTransactionsMeanueOptions { eDeposite = 1, eWithdraw = 2, eShowTotalBalance = 3, eShowMainMenue = 4 };
enum enMainMenueOptions { eListClients = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6, eExit = 7 };
void ShowMainMenue();
void ShowTransactionsMenue();

//*******************************************Functions using for Show Client on screen***********************************************
//Functions using for Show Client on screen( Go through the next stages->filter Words from words and delimete->keep words in vector
//->packing them in struct->load them from file using the pervious function->print them).
vector <string >SplitString(string S1, string Delim)
{//------------------------ LOGIC IS=>search then substr ,erease ,loop =>repeat---------------------------------
	short pos = 0;
	string sword;
	vector<string> Vstring;
	while ((pos = S1.find(Delim)) != std::string::npos)//nopo=< no postion mean in that postion tht is no value.
	{
		sword = S1.substr(0, pos);
		if (sword != " ")//here important!!! cause if there are 2 or 3 space don't print it 
		{
			Vstring.push_back(sword);
		}
		S1.erase(0, pos + Delim.length());//mean erease from index 0 +pos=>hold avalue or index of space +delit.length =1
		//SO=>EXM shaima  =>pos=6wth space we count from 0 then to also delete space +delit.length that we declare it in fun=>6+1=7.
	}
	if (S1 != " ")
	{
		Vstring.push_back(S1);
	}
	return Vstring;
}
SClient ConvertLinetoRecord(string SLine, string Seprator = "#//#")
{
	SClient Client;
	vector<string>VClientData = SplitString(SLine, Seprator);
	Client.AccountNumber = VClientData[0];
	Client.PinCode = VClientData[1];
	Client.Name = VClientData[2];
	Client.Phone = VClientData[3];
	Client.AccountBalance = stod(VClientData[4]);//cast string to double

	return Client;
}
vector<SClient> LoadClientsDataFromFile(string FileName)
{
	vector<SClient> VClient;
	SClient Client;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read mode 
	if (MyFile.is_open())
	{
		string Line;
		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecord(Line, "#//#");
			VClient.push_back(Client);
		}
		MyFile.close();

	}
	return VClient;
}
void PrintClientsRecord(SClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;

}
void ShowAllClientsScreen()
{
	vector <SClient> VClients = LoadClientsDataFromFile(ClientFileName);
	SClient clints;
	cout << "\n\t\t\t\t\t Client List (" << VClients.size() << ") Client(s).\n\n";

	cout << "\n----------------------------------------------------------------";
	cout << "--------------------------------------------------\n" << endl;

	cout << "| " << setw(15) << left << "AccountNumber";
	cout << "| " << setw(10) << left << "PinCode";
	cout << "| " << setw(40) << left << "Name";
	cout << "| " << setw(12) << left << "Phone";
	cout << "| " << setw(12) << left << "AccountBalance";
	cout << "\n----------------------------------------------------------------";
	cout << "--------------------------------------------------\n" << endl;
	if (VClients.size() == 0)
		cout << "\t\t No Clients Available In the System!";
	else
		for (SClient Client : VClients)
		{
			PrintClientsRecord(Client);
			cout << endl;
		}
	cout << "\n----------------------------------------------------------------";
	cout << "--------------------------------------------------\n" << endl;
}
//*******************************Function To Add New Client****************************************
//Function To Add New Client ( Go through the next stages->read data from user ->check client if it is exists ->take the struct that fill with onfo
// and convert it to line string->add data to file from ).
/*string Checkclient()//vector<SClient>VClient
{
	vector<SClient>VClient;
	VClient = LoadClientsDataFromFile(ClientFileName);
	SClient Client;
	string AccountNumbers = Client.AccountNumber;
	cout << " Enter Account Number ? ";
	bool Flag = true;
	do
	{
		 Flag = true;
		getline(cin >> ws, AccountNumbers);//ws use to ignore whitespace ==line after line by  enter button or  \n
		for (SClient Clien : VClient)
		{
			if (Clien.AccountNumber == AccountNumbers)
			{
				cout << "Client with [" << Clien.AccountNumber << "] already exists, Enter another Account Number ? ";
				Flag = false;
				break;
			}

		}

	 } while (Flag ==false);
	 return AccountNumbers;
}
SClient ReadNewClient() {
	SClient clientinfo;
  clientinfo.AccountNumber=Checkclient();//use fun Checkclient to be sure accountnumber is not exists yet
	cout << " Enter PinCode ? ";
	getline(cin, clientinfo.PinCode);
	cout << " Enter Name ? ";
	getline(cin, clientinfo.Name);
	cout << "Enter Phone ? ";
	getline(cin, clientinfo.Phone);
	cout << "\n Enter AccountBalance ? ";
	cin >> clientinfo.AccountBalance;
	return clientinfo;
}*/
bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
	vector<SClient>VClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		SClient Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecord(Line);
			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}
			VClients.push_back(Client);
		}
		MyFile.close();
	}
	return false;
}
SClient ReadNewClient() {
	SClient clientinfo;
	cout << " Enter Account Number ? ";
	//ws use to ignore whitespace ==line after line by  enter button or  \n
	getline(cin >> ws, clientinfo.AccountNumber);
	while (ClientExistsByAccountNumber(clientinfo.AccountNumber, ClientFileName))
	{
		cout << "Client with [" << clientinfo.AccountNumber << "] already exists, Enter another Account Number ? ";
		getline(cin >> ws, clientinfo.AccountNumber);
	}
	cout << " Enter PinCode ? ";
	getline(cin, clientinfo.PinCode);
	cout << " Enter Name ? ";
	getline(cin, clientinfo.Name);
	cout << "Enter Phone ? ";
	getline(cin, clientinfo.Phone);
	cout << "\n Enter AccountBalance ? ";
	cin >> clientinfo.AccountBalance;
	return clientinfo;
}
string ConvertRecordToLine(SClient  ReadClientData, string Seprator = "#//#")
{
	string ClientRecord = "";
	ClientRecord += ReadClientData.AccountNumber + Seprator;
	ClientRecord += ReadClientData.PinCode + Seprator;
	ClientRecord += ReadClientData.Name + Seprator;
	ClientRecord += ReadClientData.Phone + Seprator;
	ClientRecord += to_string(ReadClientData.AccountBalance);
	return ClientRecord;

}
void AddDataLineToFile(string FileName, string SDataLine)
{
	fstream FClientData;
	FClientData.open(FileName, ios::out | ios::app);
	if (FClientData.is_open())
	{

		FClientData << SDataLine << endl;
		FClientData.close();
	}
}
void AddNewClient()
{
	SClient Client;
	Client = ReadNewClient();
	AddDataLineToFile(ClientFileName, ConvertRecordToLine(Client));
}
void AddNewClients()
{
	char AddMore;
	do
	{
		cout << "\nAdding New Client :\n";
		AddNewClient();
		cout << "\n\n Client Added Successfully,do you want to add more clients? ";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}
void ShowAddNewClientsScreen()
{
	cout << "\n------------------------------------------------\n";
	cout << "\tAdd New Clients Screen\n";
	cout << "------------------------------------------------\n";
	AddNewClients();
}
//*******************************Function To Delete  Client****************************************
//Function ToDelete Client ( Go through the next stages->read AccountNumber from user  that i wanna to delete the record of it
// ->print the record of this accountnumber->use fun MarkClientForDeleteByAccountNumber to ignor and delete the record of this account number
// by helping another fun  ).
string ReadClientAccountNumber()
{
	string AccountNumber;
	cout << "Please enter AccountNumber? ";
	cin >> AccountNumber;
	return AccountNumber;
}
void PrintClientCard(SClient Client)
{
	cout << "\n\nThe following are the client details:\n";
	cout << "\nAccountNumber : " << Client.AccountNumber;
	cout << "\nPinCode       : " << Client.PinCode;
	cout << "\nName          : " << Client.Name;
	cout << "\nPhone         : " << Client.Phone;
	cout << "\nAccountBalance: " << Client.AccountBalance;
}
bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<SClient>& VClient)
{
	for (SClient& C : VClient)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}
void SaveClientsDataToFile(string FileName, vector<SClient>VSClient)
{
	fstream FClientData;
	FClientData.open(FileName, ios::out);
	if (FClientData.is_open())
	{
		string DataLine;
		for (SClient& c : VSClient)
		{
			if (c.MarkForDelete == false)
			{
				//we only write records that are not marked for delete .
				DataLine = ConvertRecordToLine(c);
				FClientData << DataLine << endl;
			}
		}
		FClientData.close();
	}
}
bool FindClientByAccountNumber(string AccountNumber, vector<SClient>VSClient, SClient& Client)
{
	vector<SClient>VSClients = LoadClientsDataFromFile(ClientFileName);
	;
	for (SClient c : VSClients)
	{

		if (c.AccountNumber == AccountNumber)
		{
			Client = c;
			return true;
		}


	}
	return false;

}
bool DeleteClientByAccountNumber(string AccountNumber, vector<SClient>& VClient)
{
	SClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, VClient, Client))
	{
		PrintClientCard(Client);
		cout << "\n\nAre you sure you want delete this client> y/n >";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, VClient);//to delete the the line that has accountnumber;
			SaveClientsDataToFile(ClientFileName, VClient);
			//Refresh Client
			VClient = LoadClientsDataFromFile(ClientFileName);
			cout << "\n\nClient Deleted Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\n Client with Account (" << AccountNumber << ") Not Found!\n";
		return false;
	}
}
void ShowDeleteClientScreen()
{
	cout << "\n------------------------------------------------\n";
	cout << "\tDelete Client Screen\n";
	cout << "------------------------------------------------\n" << endl;
	vector<SClient>VClient;
	VClient = LoadClientsDataFromFile(ClientFileName);
	string AccountNumber = ReadClientAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, VClient);

}
SClient ChangeClientRecord(string AccountNumber) {
	SClient clientinfo;
	clientinfo.AccountNumber = AccountNumber;
	cout << " Enter PinCode ? ";
	getline(cin >> ws, clientinfo.PinCode);
	cout << " Enter Name ? ";
	getline(cin, clientinfo.Name);
	cout << "Enter Phone ? ";
	getline(cin, clientinfo.Phone);
	cout << "\n Enter AccountBalance ? ";
	cin >> clientinfo.AccountBalance;
	return clientinfo;
}
bool UpdateClientByAccountNumber(string AccountNumber, vector<SClient>& VClient)
{
	SClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, VClient, Client))
	{
		PrintClientCard(Client);
		cout << "\n\nAre you sure you want  Update this client> y/n >";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			for (SClient& C : VClient)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;//not needed to compilate cause i find the record that i wanna update it
				}
			}
			SaveClientsDataToFile(ClientFileName, VClient);
			cout << "\n\nClient update Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\n Client with Account (" << AccountNumber << ") Not Found!\n";
		return false;
	}
}
void ShowUpdateClientScreen()
{
	cout << "\n------------------------------------------------\n";
	cout << "\tUpdate Client Info Screen\n";
	cout << "------------------------------------------------\n";
	vector<SClient>VClient = LoadClientsDataFromFile(ClientFileName);
	string AccountNumber = ReadClientAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, VClient);

}
void ShowFindClientScreen()
{
	cout << "\n------------------------------------------------\n";
	cout << "\t Find Client Screen\n";
	cout << "------------------------------------------------\n";
	vector<SClient>VSClients = LoadClientsDataFromFile(ClientFileName);
	string AccountNumber = ReadClientAccountNumber();
	SClient Client;
	if (FindClientByAccountNumber(AccountNumber, VSClients, Client))
	{

		PrintClientCard(Client);
		cout << endl;
	}
	else
	{
		cout << "\n Client with Account (" << AccountNumber << ") Not Found!\n";
	}
}
short ReadMainMenueOption()
{
	short Choice;
	do
	{
		cout << "Choose what do you want to do? [1 to 7]?";
		cin >> Choice;
	} while (Choice < 1 || Choice>7);
	return Choice;
}
void ShowEndScreen()
{
	cout << "\n------------------------------------------------\n";
	cout << "\t Program Ends :-) ";
	cout << "------------------------------------------------\n" << endl;
}
void GoBackToMenue()
{
	cout << "\npress any key to go back to Main Menue...";
	system("pause>0");
	ShowMainMenue();
}
double ReadClientAccountBalance(string Massege)
{
	double AccountBalance;
	cout << Massege;
	cin >> AccountBalance;
	return AccountBalance;
}

bool DepostBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector<SClient>& VClient)
{
	char Answer = 'n';
	cout << "\n\nAre you sure you want Perform this transaction ? y/n ?";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		for (SClient& C : VClient) {
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += Amount;
				SaveClientsDataToFile(ClientFileName, VClient);
				cout << "\n\n Done Successfully. New balance is :  " << C.AccountBalance;
				return true;

			}
		}
	}
	return false;
}

void ShowDepositScreen()
{
	cout << "\n------------------------------------------------\n";
	cout << "\t Deposite Screen\n";
	cout << "------------------------------------------------\n";
	SClient Client;
	vector<SClient> VClient = LoadClientsDataFromFile(ClientFileName);
	string AccountNumber = ReadClientAccountNumber();
	while (!FindClientByAccountNumber(AccountNumber, VClient, Client))
	{
		cout << "\n Client with Account (" << AccountNumber << ") Not Found!\n";
		AccountNumber = ReadClientAccountNumber();
	}
	PrintClientCard(Client);
	double Amount = 0;
	cout << "\nplease enter Deposite Amount ? ";
	cin >> Amount;
	DepostBalanceToClientByAccountNumber(AccountNumber, Amount, VClient);
}
void ShowWithdrawScreen()
{
	cout << "\n------------------------------------------------\n";
	cout << "\t Withdraw Screen\n";
	cout << "------------------------------------------------\n";
	SClient Client;
	vector<SClient> VClient = LoadClientsDataFromFile(ClientFileName);
	string AccountNumber = ReadClientAccountNumber();
	while (!FindClientByAccountNumber(AccountNumber, VClient, Client))
	{
		cout << "\n Client with Account (" << AccountNumber << ") Not Found!\n";
		AccountNumber = ReadClientAccountNumber();
	}
	PrintClientCard(Client);
	double Amount = 0;
	cout << "\nplease enter withdraw Amount ? ";
	cin >> Amount;
	while (Amount > Client.AccountBalance)
	{
		cout << "\nAmout Exceeds the balance, you can withdraw up to " << Client.AccountBalance;
		cout << "\nplease enter another amount? ";
		cin >> Amount;
	}
	DepostBalanceToClientByAccountNumber(AccountNumber, Amount * -1, VClient);
}
void PrintClientsRecordBalancesLine(SClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.AccountBalance;

}
void ShowTotalBlances()
{
	vector <SClient> VClients = LoadClientsDataFromFile(ClientFileName);
	SClient clints;

	cout << "\n\t\t\t\t\t Balances List (" << VClients.size() << ") Client(s).\n\n";

	cout << "\n----------------------------------------------------------------";
	cout << "--------------------------------------------------\n" << endl;

	cout << "| " << setw(15) << left << "AccountNumber";
	cout << "| " << setw(40) << left << "Client Name";
	cout << "| " << setw(12) << left << "Balance";
	cout << "\n----------------------------------------------------------------";
	cout << "--------------------------------------------------\n" << endl;
	double TotalBalances = 0;
	if (VClients.size() == 0)
		cout << "\t\t No Clients Available In the System!";
	else

		for (SClient Client : VClients)
		{
			PrintClientsRecordBalancesLine(Client);
			TotalBalances += Client.AccountBalance;
			cout << endl;
		}
	cout << "\n----------------------------------------------------------------";
	cout << "--------------------------------------------------\n" << endl;
	cout << "Total Balances = " << TotalBalances;
}
void ShowTotalBlancesScreen()
{
	ShowTotalBlances();
}
void GoBackToTransactionsMenue()
{
	cout << "\npress any key to go back to Main Menue...";
	system("pause>0");
	ShowTransactionsMenue();
}
void PerformTransactionsMenueOption(enTransactionsMeanueOptions TransactionsMeanueOptions)
{
	switch (TransactionsMeanueOptions)
	{
	case enTransactionsMeanueOptions::eDeposite:
		system("cls");
		ShowDepositScreen();
		GoBackToTransactionsMenue();
		break;
	case enTransactionsMeanueOptions::eWithdraw:
		system("cls");
		ShowWithdrawScreen();
		GoBackToTransactionsMenue();
		break;
	case enTransactionsMeanueOptions::eShowTotalBalance:
		system("cls");
		ShowTotalBlancesScreen();
		GoBackToTransactionsMenue();
		break;
	case enTransactionsMeanueOptions::eShowMainMenue:
		ShowMainMenue();
		break;
	}
}
short ReadTransctionsMenueOption()
{
	short Choice;
	do
	{
		cout << "Choose what do you want to do? [1 to 4]?";
		cin >> Choice;
	} while (Choice < 1 || Choice>4);
	return Choice;
}
void ShowTransactionsMenue()
{
	system("cls");
	cout << "=============================================\n";
	cout << "\n \t\t Transactions Menue SCreen \n";
	cout << "=============================================\n";
	cout << "\t [1] Deposite Screen.\n";
	cout << "\t [2] Withdraw Screen.\n";
	cout << "\t [3] Total Balances.\n";
	cout << "\t [4] Main Menue.\n";
	cout << "=============================================\n";

	PerformTransactionsMenueOption((enTransactionsMeanueOptions)ReadTransctionsMenueOption());
}
void PerformMainMenue(enMainMenueOptions MainMenueOption)
{
	switch (MainMenueOption)
	{
	case enMainMenueOptions::eListClients:
		system("cls");
		ShowAllClientsScreen();
		GoBackToMenue();
		break;
	case  enMainMenueOptions::eAddNewClient:
		system("cls");
		ShowAddNewClientsScreen();
		GoBackToMenue();
		break;
	case  enMainMenueOptions::eDeleteClient:
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMenue();
		break;
	case enMainMenueOptions::eUpdateClient:
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMenue();
		break;
	case enMainMenueOptions::eFindClient:
		system("cls");
		ShowFindClientScreen();
		GoBackToMenue();
		break;
	case enMainMenueOptions::eShowTransactionsMenue:
		system("cls");
		ShowTransactionsMenue();
		break;
	case enMainMenueOptions::eExit:
		system("cls");
		ShowEndScreen();
		break;
	}
}
void ShowMainMenue()
{
	system("cls");
	cout << "=============================================\n";
	cout << "\n \t\t Main MenueSCreen \n";
	cout << "=============================================\n";
	cout << "\t [1] Show Client List.\n";
	cout << "\t [2] Add New Client.\n";
	cout << "\t [3] Delete Client.\n";
	cout << "\t [4] Update Client Info.\n";
	cout << "\t [5] Find Client.\n";
	cout << "\t [6] Transactions.\n";
	cout << "\t [7] Exit.\n";
	cout << "=============================================\n";

	PerformMainMenue((enMainMenueOptions)ReadMainMenueOption());
}

int main()
{
	ShowMainMenue();
}
