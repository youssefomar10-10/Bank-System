
// Bank Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <fstream>
#include <iomanip>
using namespace std;
const string StringFileName = "Clients";
void TheMenu();
void TheTransactionMenu();

enum enMenueList { eClientList = 1, eAddClient = 2, eDeleteClient = 3, eUpdateCllient = 4, eFindClients = 5,etransaction=6,eExit = 7 };
enum enTranscationMenu{ eDeposite=1, eWithdeaw =2,eTotalBalances=3,eMaiMenu=4};
struct stClientInfo
{
    string AccountNumber;
    string PINCode;
    string ClientName;
    string PhoneNumber;
    double AccountBalance;
    bool MarkDelete = false;

};
vector<string>StringSplit(string Line, string Delim)
{
    short pos = 0;
    string SWord = "";
    vector<string>VClient;
    while ((pos = Line.find(Delim)) != std::string::npos)
    {
        SWord = Line.substr(0, pos);
        if (SWord != "")
        {
            VClient.push_back(SWord);
        }
        Line.erase(0, pos + Delim.length());
    }
    if (Line != "")
    {
        VClient.push_back(Line);
    }
    return VClient;
}
stClientInfo ConvertLineToRecord(string Line)
{
    vector <string>VClient;
    VClient = StringSplit(Line, "#//#");
    stClientInfo Client;
    Client.AccountNumber = VClient[0];
    Client.PINCode = VClient[1];
    Client.ClientName = VClient[2];
    Client.PhoneNumber = VClient[3];
    Client.AccountBalance = stod(VClient[4]);
    return Client;
}
string ConvertFromRecordToLine(stClientInfo Client, string Delim = "#//#")
{
    string Line;
    Line += Client.AccountNumber + Delim;
    Line += Client.PINCode + Delim;
    Line += Client.ClientName + Delim;
    Line += Client.PhoneNumber + Delim;
    Line += to_string(Client.AccountBalance);
    return Line;
}
vector <stClientInfo> LoadFromFileToRecord(string FileName)
{
    fstream ClientFile;
    ClientFile.open(FileName, ios::in);
    vector<stClientInfo> VClient;
    if (ClientFile.is_open())
    {
        string Line;
        stClientInfo Client;
        while (getline(ClientFile, Line))
        {
            if (Line != "")
            {
                Client = ConvertLineToRecord(Line);
                VClient.push_back(Client);
            }
        }
        ClientFile.close();
    }
    return VClient;
}
bool AccountExisit(string AccountNum, string FileName)
{
    fstream ClientFile;
    vector<stClientInfo>VClient;
    ClientFile.open(FileName, ios::in);
    if (ClientFile.is_open())
    {
        string Line;
        stClientInfo Client;
        while (getline(ClientFile, Line))
        {
            Client = ConvertLineToRecord(Line);
            if (Client.AccountNumber == AccountNum)
            {
                ClientFile.close();
                return true;
                }
            VClient.push_back(Client);

        }
        ClientFile.close();
        
    }
    return false;
}
stClientInfo AddNewClient()
{
    stClientInfo Client;
    cout << "Please Enter Account Number: ";
    getline(cin>>ws, Client.AccountNumber);
    while (AccountExisit(Client.AccountNumber,StringFileName))
    {
        cout << "The Account Number " << Client.AccountNumber << " is already exissted, Please enter different Account Name\n";
        getline(cin >> ws, Client.AccountNumber);
    }
    cout << "\n\nPlease Enter PIN code: ";
    getline(cin, Client.PINCode);
    cout << "\n\nPlease Enter Client Name: ";
    getline(cin, Client.ClientName);
    cout << "\n\nPlease Enter Phone Number: ";
    getline(cin, Client.PhoneNumber);
    cout << "\n\nPlease Enter Account Balance: ";
    cin>> Client.AccountBalance;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max());
        cout << "Invalid number, try again: ";
        cin >> Client.AccountBalance;

    }
    
    return Client;
}
void PrintSingleClient(stClientInfo Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code : " << Client.PINCode;
    cout << "\nName : " << Client.ClientName;
    cout << "\nPhone : " << Client.PhoneNumber;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n-----------------------------------\n";
}
stClientInfo FillStruct(vector<string>VClients)
{
    stClientInfo Client;
    Client.AccountNumber = VClients[0];
    Client.PINCode = VClients[1];
    Client.ClientName = VClients[2];
    Client.PhoneNumber = VClients[3];
    Client.AccountBalance = stod(VClients[4]);
    return Client;
}


void PrintClientRecord(stClientInfo Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PINCode;
    cout << "| " << setw(40) << left << Client.ClientName;
    cout << "| " << setw(12) << left << Client.PhoneNumber;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}
void PrintAllClientsData()
{
    vector <stClientInfo> vClients = LoadFromFileToRecord(StringFileName);
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Clients(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (stClientInfo& C : vClients)
    {
        PrintClientRecord(C);
        cout << endl;
    }
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}
void AddFromRecordToFile(string Line, string FileName)
{

    fstream ClientFile;

    ClientFile.open(FileName, ios::out | ios::app);
    if (ClientFile.is_open())
    {
        
             

            ClientFile << Line << endl;
            
        ClientFile.close();

    }

}

string AskToEnterAccountNum()
{
    string AccNum;
    cout << "Please Enter The Account Number: ";
    cin >> AccNum;
    return AccNum;
}
bool FindClient(vector<stClientInfo> &VClient,stClientInfo& Client,string AccountNumber)
{
    
    for (stClientInfo &C : VClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;

        }
  }
    return false;
}
vector <stClientInfo> SaveafterDelete(string FileName, vector<stClientInfo>& VClient)
{
    fstream ClientFile;
    ClientFile.open(FileName, ios::out);
    
    if (ClientFile.is_open())
    {
        string Line;
        
        for(stClientInfo&C:VClient)
        {
            if (C.MarkDelete == false)
            {
                Line = ConvertFromRecordToLine(C);
                ClientFile << Line << endl;
                
            }
        }
        ClientFile.close();
    }
    return VClient;
}

bool MarkDeletClient(string AccountNum, vector<stClientInfo>& VClient)
{
    for (stClientInfo& C : VClient)
    {
        if (C.AccountNumber == AccountNum)
        {
            C.MarkDelete = true;
            return true;
        }
    }
    return false;
}
bool AskToDlete()
{
    char Answer='n';
    cout << "\n Do you want to delete this account? [y/n] ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        return true;
    }
    return false;
}
void TheFindAccout(vector<stClientInfo>& VClient)
{
    string AccountNum = AskToEnterAccountNum();
    stClientInfo Client;
        if (FindClient(VClient,Client, AccountNum))
        {
            PrintSingleClient(Client);
        }
        
    else
    {
        cout << "This Account " << AccountNum << " is not found\n";
    }
}
bool DeleteAcc(vector<stClientInfo>& VClient, string AccountNum)
{
     
    stClientInfo Client;
        if (FindClient(VClient,Client, AccountNum))
        {
            PrintSingleClient(Client);
            if (AskToDlete())
            {
                
                    MarkDeletClient(AccountNum,VClient);
                    SaveafterDelete(StringFileName, VClient);
                    VClient = LoadFromFileToRecord(StringFileName);
                    cout << "\nThe Client has beem deleted\n";
                    return true;
            }
        }

        else
        {
            cout << "This Account " << AccountNum << " is not found\n\n";
            return false;
        }
}
void AddClient()
{
    stClientInfo Client = AddNewClient();
    AddFromRecordToFile(ConvertFromRecordToLine(Client), StringFileName);

}
void AddClients()
{
    
    char Answer = 'y';
    
    
        
        
            
    while (toupper(Answer) == 'Y') {
        AddClient();
        cout << "\nThe Client has been Added, do you want to add more? [y/n] ";
        cin >> Answer;
        
        if (toupper(Answer) == 'Y')
        {
            system("cls");
        }
        
    }

        
    

}
stClientInfo NewInfo(string AccountNum)
{
    stClientInfo Client;
    Client.AccountNumber = AccountNum;
    cout << "Please Enter PIN Code: ",
        getline(cin >> ws, Client.PINCode);
    cout << "\nPlease Enter Client Name: ";
        getline(cin , Client.ClientName);
        cout << "\nPlease Enter Phone Number: ";
        getline(cin, Client.PhoneNumber);
        cout << "\nPlease Enter Account Balance: ",
        cin>> Client.AccountBalance;
        return Client;
}
void UpdateClient(string AccountNum,vector<stClientInfo>& VClient)
{
    
    char Answer='n';
    stClientInfo Client;
        if (FindClient(VClient,Client, AccountNum))
        {
            PrintSingleClient(Client);
            cout << "\n\nDo you want to update this client? [y/n] ";
            cin >> Answer;
            if (Answer=='y'|| Answer == 'Y')
            {
                for (stClientInfo& C : VClient)
                {
                    if (AccountNum == C.AccountNumber)
                    {
                        C = NewInfo(AccountNum);
                        break;
                    }
                }
                SaveafterDelete(StringFileName, VClient);
                cout << "\nThe Client has beem Updated\n";
            }
        }else
        {
            cout << "This Account " << AccountNum << " is not found\n";
        }
}
enMenueList ReadFromMenu()
{
    short Choise = 0;
    cout << "\nChoose what do you want to do? [1 to 7] ";
    cin >> Choise;
    return enMenueList(Choise);
} 
double TransactionOperation(double AccountBalance,double NewAmount)
{
    double Sum = 0;
    Sum = AccountBalance + NewAmount;
    return Sum;
}
bool AskConfirmation()
{
    char Answer = 'n';
    cout << "\n\n Are you sure you want perform this transaction? [y/n] ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        return true;
    }
    return false;
}
bool DepositeBalancetoClientByAccountNumber(string AccountNum, double DepositeAmount, vector<stClientInfo>& VClient)
{
    if (AskConfirmation())
    {
        for (stClientInfo& C : VClient)
        {
            if (AccountNum == C.AccountNumber)
            {

                C.AccountBalance = TransactionOperation(C.AccountBalance, DepositeAmount);
                SaveafterDelete(StringFileName, VClient);
                cout << "\nDone succssefully the New Balance is: \n" << C.AccountBalance;
                
                return true;
            }
        }
       
    }
    return false;
}

    
void PrintClientBalances(stClientInfo Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
   
    cout << "| " << setw(40) << left << Client.ClientName;
    
    cout << "| " << setw(12) << left << Client.AccountBalance;
}
void TheTotalAccountBalance()
{
    vector <stClientInfo> vClients = LoadFromFileToRecord(StringFileName);
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Clients(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    double Sum = 0;
    for (stClientInfo& C : vClients)
    {
        PrintClientBalances(C);
        cout << endl;
        Sum += C.AccountBalance;
    }
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "\t\t\t        Total Balances = " << Sum<<endl;
}
enTranscationMenu ReadFromTransactionMenu()
{
    short Choise = 0;
    cout << "\nChoose what do you want to do? [1 to 4] ";
    cin >> Choise;
    return enTranscationMenu(Choise);
}


void BackToMenu()
{
    cout << "\nPress any key to go back to Main Menu...";
    system("pause>0");
     TheMenu();
}
void BackToTransactionMenu()
{
    cout << "\nPress any key to go back to Transaction Menu...";
    system("pause>0");
    TheTransactionMenu();
}
void ShowFindClients()
{
    cout << "\n-----------------------------\n";
    cout << "          Finde Client ";
    cout << "\n-----------------------------\n";
    vector<stClientInfo>VClient = LoadFromFileToRecord(StringFileName);
    TheFindAccout(VClient);

}
void ShowUpdateClients()
{
    cout << "\n-----------------------------\n";
    cout << "          Update Client ";
    cout << "\n-----------------------------\n";
    vector<stClientInfo>VClient = LoadFromFileToRecord(StringFileName);
    string AccountNum = AskToEnterAccountNum();
    UpdateClient(AccountNum,VClient);

}
void ShowDeleteClients()
{
    cout << "\n-----------------------------\n";
    cout << "          Delete Client ";
    cout << "\n-----------------------------\n";
    vector<stClientInfo>VClient = LoadFromFileToRecord(StringFileName);
    string AccountNum = AskToEnterAccountNum();
    while (!DeleteAcc(VClient, AccountNum))
    {
        AccountNum = AskToEnterAccountNum();
    }

}
void ShowAddClients()
{
    cout << "\n-----------------------------\n";
    cout << "          Add Clients ";
    cout << "\n-----------------------------\n";
    AddClients();

}
void TheShowEndScreen()
{
    system("cls");
    cout << "\n-----------------------------\n";
    cout << "           Program Ends :-) ";
    cout << "\n-----------------------------\n";

}
void ShowDepositeSCreen()
{
    cout << "\n-----------------------------\n";
    cout << "          Deposite Screen ";
    cout << "\n-----------------------------\n";
    

        double DepositeAmount = 0;
        string AccountNum = AskToEnterAccountNum();
        vector<stClientInfo> VClient = LoadFromFileToRecord(StringFileName);
        stClientInfo Client;
        while (!FindClient(VClient, Client, AccountNum))
        {


            cout << "This Account " << AccountNum << " is not found\n";
            AccountNum = AskToEnterAccountNum();
        }
        PrintSingleClient(Client);
        cout << "\n\n Please enter deposite amount? ";
        cin >> DepositeAmount;
        while (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max());
            cout << "Invalid number, try again: ";
            cin >> DepositeAmount;
            
        }
        DepositeBalancetoClientByAccountNumber(AccountNum, DepositeAmount, VClient);

    

}
void ShowWithdrawSCreen()
{
    cout << "\n-----------------------------\n";
    cout << "          Withdraw Screen ";
    cout << "\n-----------------------------\n";
    double WithdrawAmount = 0;
    vector<stClientInfo>VClient = LoadFromFileToRecord(StringFileName);
    string AccountNum = AskToEnterAccountNum();

    stClientInfo Client;
    while (!FindClient(VClient, Client, AccountNum))
    {
        cout << "This Account " << AccountNum << " is not found\n";
        AccountNum = AskToEnterAccountNum();
    }
    PrintSingleClient(Client);
    cout << "\n\n Please enter withdraw amount? ";
    cin >> WithdrawAmount;
    while (WithdrawAmount > Client.AccountBalance)
    {
        cout << "The Amount Exceeds the balance, you can withdraw up to: " << Client.AccountBalance;
        cout << "\n\n Please enter another amount? ";
        cin >> WithdrawAmount;
        while (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max());
            cout << "Invalid number, try again: ";
            cin >> WithdrawAmount;

        }

    }

        DepositeBalancetoClientByAccountNumber(AccountNum, WithdrawAmount * -1, VClient);
   


}
void PerformTransactionMenuOption(enTranscationMenu enChoise)
{
    switch (enChoise)
    {
    case eDeposite:
    {
        system("cls");
        ShowDepositeSCreen();
         BackToTransactionMenu();
        break;
    }
    case eWithdeaw:
    {
        system("cls");
        ShowWithdrawSCreen();
        BackToTransactionMenu();
        break;
    }
    case eTotalBalances:
    {
        system("cls");
        TheTotalAccountBalance();
        BackToTransactionMenu();
        break;
    }
    case eMaiMenu:
    {
        system("cls");
        TheMenu();
        
        break;
    }
    default:
    {
        cout << "Invalid Choise!\n";
        BackToTransactionMenu();
        break;
    }
    }
}
void TheTransactionMenu()
{
    system("cls");
    cout << "===== Transaction Menu =====\n";
    cout << "[1] Deposite\n";
    cout << "[2] Withdraw\n";
    cout << "[3] Total Balances\n";
    cout << "[4] The Main Menu\n";
    cout << "\n=====================\n";
    PerformTransactionMenuOption((enTranscationMenu)ReadFromTransactionMenu());
}
void PerformMainMenuOption(enMenueList enChoise)
{
    
    
        switch(enChoise)
        {
        case eClientList:
        {
            system("cls");
            PrintAllClientsData();
            BackToMenu();
            break;
        }
        case eAddClient:
        {
            system("cls");
            
           
            ShowAddClients();

            BackToMenu();
            break;
        }
        case eDeleteClient:
        {
            system("cls");
            ShowDeleteClients();
            BackToMenu();
            break;
        }
        case eUpdateCllient:
        {
            system("cls");
            ShowUpdateClients();
            BackToMenu();
            break;
        }
        case eFindClients:
        {
            system("cls");
            ShowFindClients();
            BackToMenu();
            break;
        }
        case etransaction:
        {
            system("cls");
            TheTransactionMenu();
            break;

        }
        case eExit:
        {
            TheShowEndScreen();
            
            break;
        }
        default:
        {
            cout << "Invalid Choise!\n";
            BackToMenu();
            break;
        }
        }
     

}
void TheMenu()
{
    system("cls");
    cout << "===== Main Menu =====\n";
    cout << "[1] Show Clients\n";
    cout << "[2] Add Client\n";
    cout << "[3] Delete Client\n";
    cout << "[4] Update Client\n";
    cout << "[5] Find Client\n";
    cout << "[6] transaction\n";
    cout << "[7] Exit\n";
    cout << "\n=====================\n";
    PerformMainMenuOption((enMenueList)ReadFromMenu());
}
int main()
{
    TheMenu();
}

