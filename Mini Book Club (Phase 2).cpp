#include <iostream>
#include <fstream>
#include <iomanip>
#include <String>

using namespace std;
int memberID[100];
string memberName[100];
int memberTelephoneNumber[100];
char membershipType[100];
char paymentType[100];
string dueDate[100], paymentDate[100];

void menu()
{
	cout << "       Main Book Club Membership Mangement System\n";
	cout << "------------------------------------------------------------\n";
	cout << "\n Please choose what you would like to do:\n\n";
	cout << "1- Add a New Member\n";
	cout << "2- Edit a Members Information\n";
	cout << "3- Delete a Member\n";
	cout << "4- Generate a Membership Bill for all Members\n";
	cout << "5- Generate a Membership Bill for Penalized Members\n";
	cout << "6- Exit\n\n";
	cout << "Enter your choice:";
}

void loadMembersFromFile()
{
	ifstream infile("members.txt");

	int i = 0;
	for (int i = 0; i < 100; i++)
	{
		memberID[i] = 0;
	}
	while (!infile.eof())
	{
		infile >> memberID[i];
		infile >> memberName[i];
		infile >> memberTelephoneNumber[i];
		infile >> membershipType[i];
		infile >> paymentType[i];
		infile >> dueDate[i];
		infile >> paymentDate[i];

		if (infile.eof())
			break;
		i++;
	}

	infile.close();
}
int numberOfMembersInFile()
{
	ifstream infile("members.txt");
	string temp;

	int count = 0;

	while (getline(infile, temp))
	{
		count++;
	}

	return count;
}

void addNewMember() {
	ofstream outfile;
	outfile.open("members.txt", ios::app);

	string name, dDate, pDate;
	int id, telephoneNumber;
	char pType, mType;

	bool anotherMember = true;

	do {
		cout << "Please input a member ID or -1 to return to main menu:";
		cin >> id;
		if (id == -1) {
			break;
		}
		cout << "Please input a member name:";
		cin >> name;
		cout << "Please input a telephone number:";
		cin >> telephoneNumber;
		cout << "Please input a member type 'S' for student or 'G' for graduate:";
		cin >> mType;
		while (mType != 's' && mType != 'S' && mType != 'g' && mType != 'G')
		{
			cout << "Invalid Choice!\n";
			cout << "Please input a member type 'S' for student or 'G' for graduate:";
			cin >> mType;
		}
		cout << "Please input payment type 'A' for Annual or 'M' for monthly:";
		cin >> pType;
		while (pType != 'a' && pType != 'A' && pType != 'm' && mType != 'M')
		{
			cout << "Invalid Choice!\n";
			cout << "Please input payment type 'A' for Annual or 'M' for monthly:";
			cin >> pType;
		}
		cout << "Please input the due date in the format YYYYMMDD:";
		cin >> dDate;
		cout << "Please input the payment date in the format YYYYMMDD:";
		cin >> pDate;
	
		outfile << left << setw(15) << id << left << setw(15) << name << left << setw(10) << telephoneNumber << left << setw(3) << mType << left << setw(3) << pType << left << setw(10) << dDate << pDate << endl;
	} while (id!=-1);
	outfile.close();
}

void editAMembersInfo()
{
	loadMembersFromFile();
	int id;
	cout << "\nEnter the id of the Member to be edited:";
	cin >> id;
	bool memberFound = false;

	int choice;
	char again;

	for (int i = 0; i < numberOfMembersInFile(); i++)
	{
		if (memberID[i] == id)
		{
			memberFound = true;
			do {
				cout << "\n1)Member Name";
				cout << "\n2)Member Telephone";
				cout << "\n3)Membership Type";
				cout << "\n4)Payment Type";
				cout << "\n5)Due Date";
				cout << "\n6)Payment Date";

				cout << "\nWhat feild would you like to change:";
				cin >> choice;

				switch (choice)
				{
				case 1:
					cout << "Please enter a new name:";
					cin >> memberName[i];
					break;
				case 2:
					cout << "Please enter a new telephone number:";
					cin >> memberTelephoneNumber[i];
					break;
				case 3:
					cout << "Please enter a new membership type:";
					cin >> membershipType[i];
					while (membershipType[i] != 's' && membershipType[i] != 'S' && membershipType[i] != 'g' && membershipType[i] != 'G')
					{
						cout << "Invalid Choice!\n";
						cout << "Please input a member type 'S' for student or 'G' for graduate:";
						cin >> membershipType[i];
					}
					break;
				case 4:
					cout << "Please enter a new payment type:";
					cin >> paymentType[i];
					while (paymentType[i] != 'a' && paymentType[i] != 'A' && paymentType[i] != 'm' && paymentType[i] != 'M')
					{
						cout << "Invalid Choice!\n";
						cout << "Please input payment type 'A' for Annual or 'M' for monthly:";
						cin >> paymentType[i];
					}
					break;
				case 5:
					cout << "Please enter a new due date:";
					cin >> dueDate[i];
					break;
				case 6:
					cout << "Please enter a new payment:";
					cin >> paymentDate[i];
					break;
				default: cout << "\n!INVALID INPUT TRY AGAIN!\n";
				}
				cout << "\nEnter Y/y to change another feild or any other char to return to the main menu:";
				cin >> again;

			} while (again=='y' || again=='Y');
			break;
		}
	}

	if(!memberFound)
		cout<< "\nMEMBER NOT FOUND!\n\n";
	else
	{
		int numOfMembers = numberOfMembersInFile();
		ofstream outfile("members.txt");
		for (int i = 0; i < numOfMembers; i++)
		{
			if (memberID[i]!=0)
			{
				outfile << left << setw(15) << memberID[i] << left << setw(15) << memberName[i] << left << setw(10) << memberTelephoneNumber[i] << left << setw(3) << membershipType[i] << left << setw(3) << paymentType[i] << left << setw(10) << dueDate[i] << paymentDate[i] << endl;
			}
			
		}
		outfile.close();
	}

}

void deleteMember() {

	ofstream outfileDeleted;
	outfileDeleted.open("deletedMembers.txt", ios::app);

	loadMembersFromFile();
	int id;
	cout << "\nEnter the id of the Member to be Deleted:";
	cin >> id;
	bool memberFound = false;

	int choice;
	char again;

	for (int i = 0; i < numberOfMembersInFile(); i++)
	{
		if (memberID[i] == id)
		{
			memberFound = true;
			outfileDeleted << left << setw(15) << memberID[i] << left << setw(15) << memberName[i] << left << setw(10) << memberTelephoneNumber[i] << left << setw(3) << membershipType[i] << left << setw(3) << paymentType[i] << left << setw(10) << dueDate[i] << paymentDate[i] << endl;
			memberID[i] = 0;
			cout << "\nMember Deleted!\n";
			break;
		}
	}
	outfileDeleted.close();
	if (!memberFound)
		cout << "\nMEMBER NOT FOUND!\n\n";
	else
	{
		int numOfMembers = numberOfMembersInFile();
		ofstream outfile("members.txt");
		for (int i = 0; i < numOfMembers; i++)
		{
			if (memberID[i] != 0)
			{
				outfile << left << setw(15) << memberID[i] << left << setw(15) << memberName[i] << left << setw(10) << memberTelephoneNumber[i] << left << setw(3) << membershipType[i] << left << setw(3) << paymentType[i] << left << setw(10) << dueDate[i] << paymentDate[i] << endl;
			}

		}
		outfile.close();
	}
}
void generateMembershipBillforAllMembers()
{
	int months[100];
	double feeForMember[100];
	double allMembersTotal=0;
	loadMembersFromFile();
	cout << endl;
	for (int i = 0; i < numberOfMembersInFile(); i++)
	{
		cout << "Hello " << memberName[i] << " please input the number of months you have a had membership:";
		cin >> months[i];

		if (membershipType[i] == 's' || membershipType[i] == 'S')
		{
			if (paymentType[i] == 'a' || paymentType[i] == 'A')
				feeForMember[i] = (300.0 * months[i]) - (300.0 * 0.25 * months[i]);
			else if (paymentType[i] == 'm' || paymentType[i] == 'M')
				feeForMember[i] = (300.0 * months[i]) - (300.0 * 0.05 * months[i]);
		}
		else if (membershipType[i] == 'g' || membershipType[i] == 'G')
		{
			if (paymentType[i] == 'a' || paymentType[i] == 'A')
				feeForMember[i] = (300.0 * months[i]) - (300.0 * 0.10 * months[i]);
			else if (paymentType[i] == 'm' || paymentType[i] == 'M')
				feeForMember[i] = (300.0 * months[i]) - (300.0 * 0.03 * months[i]);
		}
		if (stoi(dueDate[i]) - stoi(paymentDate[i]) < 0)
			feeForMember[i] += 100.0;
		
		allMembersTotal += feeForMember[i];
	}
	cout << endl;
	cout << left << setw(15) << "ID" << left << setw(15) << "Name" << left << setw(12) << "Telelphone" << left << setw(7) << "M Type" << left << setw(7) << "p Type" << left << setw(10) << "Due Date" << left << setw(10) << "P Date" << "Fee per Month" << endl;
	cout << "---------------------------------------------------------------------------------------\n";

	for (int i = 0; i < numberOfMembersInFile(); i++)
	{
		cout << left << setw(15) << memberID[i] << left << setw(15) << memberName[i] << left << setw(12) << memberTelephoneNumber[i] << left << setw(7) << membershipType[i] << left << setw(7) << paymentType[i] << left << setw(10) << dueDate[i] << left << setw(10) << paymentDate[i] <<fixed <<setprecision(2) << feeForMember[i] <<"QR"<< endl;
	}
	double avgMonthlyCharge = allMembersTotal / numberOfMembersInFile();
	cout << "\nThe total monthly membership fees are = " << allMembersTotal <<"QR"<< endl;
	cout << "The avg monthly membership fees are = " << avgMonthlyCharge <<"QR"<< endl << endl;
}

void generateMembershipBillforPenalizedMembers()
{
	int months[100];
	double feeForMember[100];
	double allMembersTotal = 0;
	int numOfPenalizedMemebrs = 0;
	loadMembersFromFile();
	double highestBill,lowestBill;
	string highestBillMember = "No Bills", lowestBillMember = "No Bills";
	int found = 0;

	cout << endl;
	for (int i = 0; i < numberOfMembersInFile(); i++)
	{
		if (stoi(dueDate[i]) - stoi(paymentDate[i]) < 0) {
			cout << "Hello " << memberName[i] << " please input the number of months you have a had membership:";
			cin >> months[i];
			found++;

			if (membershipType[i] == 's' || membershipType[i] == 'S')
			{
				if (paymentType[i] == 'a' || paymentType[i] == 'A')
					feeForMember[i] = (300.0 * months[i]) - (300.0 * 0.25 * months[i]);
				else if (paymentType[i] == 'm' || paymentType[i] == 'M')
					feeForMember[i] = (300.0 * months[i]) - (300.0 * 0.05 * months[i]);
			}
			else if (membershipType[i] == 'g' || membershipType[i] == 'G')
			{
				if (paymentType[i] == 'a' || paymentType[i] == 'A')
					feeForMember[i] = (300.0 * months[i]) - (300.0 * 0.10 * months[i]);
				else if (paymentType[i] == 'm' || paymentType[i] == 'M')
					feeForMember[i] = (300.0 * months[i]) - (300.0 * 0.03 * months[i]);
			}
			feeForMember[i] += 100.0;
			
			if (found == 1) {
				lowestBill = feeForMember[i];
				highestBill = feeForMember[i];
				highestBillMember = memberName[i];
				lowestBillMember = memberName[i];
			}
			else if (feeForMember[i] > highestBill) {
				highestBill = feeForMember[i];
				highestBillMember = memberName[i];
			}
			else if (feeForMember[i] < lowestBill) {
				lowestBill = feeForMember[i];
				lowestBillMember = memberName[i];
			}

			allMembersTotal += feeForMember[i];
			numOfPenalizedMemebrs++;
		}
	}
	cout << endl;
	cout << left << setw(15) << "ID" << left << setw(15) << "Name" << left << setw(12) << "Telelphone" << left << setw(7) << "M Type" << left << setw(7) << "p Type" << left << setw(10) << "Due Date" << left << setw(10) << "P Date" << "Fee per Month" << endl;
	cout << "---------------------------------------------------------------------------------------\n";

	for (int i = 0; i < numberOfMembersInFile(); i++)
	{
		if (stoi(dueDate[i]) - stoi(paymentDate[i]) < 0)
			cout << left << setw(15) << memberID[i] << left << setw(15) << memberName[i] << left << setw(12) << memberTelephoneNumber[i] << left << setw(7) << membershipType[i] << left << setw(7) << paymentType[i] << left << setw(10) << dueDate[i] << left << setw(10) << paymentDate[i] << fixed << setprecision(2) << feeForMember[i] << "QR" << endl;
	}
	double avgMonthlyCharge = allMembersTotal / numOfPenalizedMemebrs*1.0;
	cout << "\nThe total monthly membership fees are = " << allMembersTotal << "QR" << endl;
	cout << "The avg monthly membership fees are = " << avgMonthlyCharge << "QR" << endl;
	cout << "The lowest bill belongs to " << lowestBillMember << " = " << fixed << setprecision(2) << lowestBill<<"QR"<<endl;
	cout << "The highest bill belongs to " << highestBillMember << " = " << fixed << setprecision(2) << highestBill << "QR" << endl<<endl;
}

int main()
{
	
	bool again = true;
	do {
		menu();
		int choice;
		cin >> choice;
		switch (choice) {
		case 1: addNewMember();
			break;
		case 2: editAMembersInfo();
			break;
		case 3: deleteMember();
			break;
		case 4: generateMembershipBillforAllMembers();
			break;
		case 5:generateMembershipBillforPenalizedMembers();
			break;
		case 6:
			cout << "\nThank you for using the Mini Book Club Membership System!\n";
			again = false;
			break;
		default:
			cout << "\n!INVALID INPUT RETURNING TO THE MAIN MENU!\n";
		}
	} while (again);
}

