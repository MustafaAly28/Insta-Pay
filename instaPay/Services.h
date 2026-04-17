#pragma once
#include<iostream>
#include<string>
#include"DataLayer.h"
#include"FilesLayer.h"
using namespace std;





// This Code For Test My Features (From: Yousef Ehab)


namespace Login
{
	string ReadUserName()
	{
		string UserName = "";

		cout << "Enter Your UserName : \n";
		getline(cin >> ws, UserName);

		return UserName;
	}

	string ReadPassword()
	{
		string PassWord = "";
		cout << "Enter Your PassWord : \n";
		getline(cin >> ws, PassWord);

		return PassWord;
	}

	bool IsUserExactlyExist(const StUser Users[USERS_COUNT], const StUser& User)
	{
		bool IsUserExist = true;

		for (int PositionUser = 0; PositionUser < USERS_COUNT; PositionUser++)
		{
			if (Users[PositionUser].UserName == User.UserName && Users[PositionUser].Password == User.Password)
				return IsUserExist;
		}
		return !IsUserExist;
	}

	bool LogInUser(StUser Users[USERS_COUNT], StUser& User)
	{
		bool IsLogIn = true;

		if (IsUserExactlyExist(Users, User))
			return IsLogIn;

		return !IsLogIn;
	}

	void LogIn(StUser& User, StUser Users[USERS_COUNT])
	{
		system("cls");

		cout << "\t\t =====================================\n";
		cout << "\t\t =========== Log In Screen ===========\n";
		cout << "\t\t =====================================\n";

		do
		{
			User.UserName = ReadUserName();
			User.Password = ReadPassword();

			if (LogInUser(Users, User))
			{
				cout << "Done Log In \n";
				return;
			}
				

			cout << "\n===============================================\n";
			cout << "\nInValid Data, UserName Or Password Is Not Right \n";
			cout << "\n===============================================\n\n";

		} while (true);

	}

}

namespace Print
{
	void PrintDataUser(const StUser& User)
	{
		cout << "\n_______________________________________________________________________________\n";
		cout << "Address Data Of Client : \n";
		cout << "-----------------------\n";
		cout << "Street Address : " << User.Address.Street << endl;
		cout << "City Name      : " << User.Address.City << endl;
		cout << "Home Number    : " << User.Address.HomeNumber << endl;

		cout << "=======================\n";

		cout << "Account Data Of Client \n";
		cout << "-----------------------\n";
		cout << "Bank Name   : " << User.Account.BankName << endl;
		cout << "Card Number : " << User.Account.CardNumber << endl;
		cout << "CVV Code    : " << User.Account.CVVCode << endl;
		cout << "Holder Name : " << User.Account.HolderName << endl;
		cout << "Expiration Date : " << User.Account.ExpirationDate << endl;

		cout << "=======================\n";

		cout << "Personal Data Of Client \n";
		cout << "-----------------------\n";
		cout << "Name  : " << User.UserName << endl;
		cout << "Id    : " << User.Id << endl;
		cout << "PassWord : " << User.Password << endl;
		cout << "Email : " << User.Email << endl;
		cout << "Phone : " << User.Phone << endl;

		cout << "=======================\n";
		cout << "\n_______________________________________________________________________________\n";
	}

	void PrintDataTransaction(const StTransactions& TransactionHistory)
	{
		cout << "\n __________________________________________________________________ \n";
		cout << "FROM    :- " << TransactionHistory.PhoneNumber_From << endl;
		cout << "TO      :- " << TransactionHistory.PhoneNumber_To<< endl;
		cout << "Date    :- " << TransactionHistory.Date << endl;
		cout << "Amount  :- " << TransactionHistory.Amount << endl;
		cout << "\n __________________________________________________________________ \n";
	}
}

namespace TransactionService
{
	int GetUserIndexByPhoneNumber(const string& Phone)
	{
		for (int i = 0; i < AddingUsersCounter; i++)
		{
			if (Users[i].Phone == Phone)
				return i;
		}
		return - 1;
	}

	void Transfer()
	{
		StTransactions Transaction;

		cout << "enter The phone number : From :- ";
		getline(cin >> ws, Transaction.PhoneNumber_From); // 01012345678 (Now Balance = 14500.750000$) Ahmed Ali

		cout << "Enter The Phone Number (To) :- ";
		getline(cin >> ws, Transaction.PhoneNumber_To); // 01123456789 (Now Balance = 8,700 $) Sara 

		cout << "Enter The Balance To Transafer To : " << Transaction.PhoneNumber_To << " : ";
		cin >> Transaction.Amount; // 100

		int IndexFrom = GetUserIndexByPhoneNumber(Transaction.PhoneNumber_From);
		int IndexTo = GetUserIndexByPhoneNumber(Transaction.PhoneNumber_To);

		Users[IndexFrom].Account.Balance -= Transaction.Amount;
		Users[IndexTo].Account.Balance += Transaction.Amount;

		File::Access_AddTransactionHistoryToFile(Transaction);
	}
}