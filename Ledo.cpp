#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

//function prototypes
void load_users();
void update_users();
void menu();
bool login();
void create_account();
void load_donations();
void verify_donation();
void update_donations();
void report_donation();
void cancel_donation();


//user account arrays
vector<string> first = {};
vector<string> last = {};
vector<string> tNum = {};
vector<string> users = {};
vector<string> pssw = {};

//user account variables
string fName;
string lName;
string taxNum;
string user_name;
string password;

//donation arrays
vector<string> business = {};
vector<string> address = {};
vector<string> project = {};
vector<string> description = {};
vector<float> amount = {};
vector<string> date = {};
vector<int> dNum;

//donation variables
string bName;
string bAddress;
string pName;
string desc;
float amt;
string dDate;
int num;





//gloabl variables
int option;
int counter = 0;
bool loginCheck = false;

int main() {

	//read current users
	load_users();

	menu:

		do {
			
			system("CLS");

			menu();


			switch (option) {

				//create a new taxpayer account
			case 1:

				create_account();
				cout << endl << endl;

				cout << "Press ENTER to continue." << endl;
				cin.ignore();
				cin.ignore();

				break;

				//report a donation to Ledo
			case 2:

				if (loginCheck == true) {

					report_donation();

					cout << endl << endl;

					cout << "Press ENTER to continue." << endl;
					cin.ignore();
					cin.ignore();

					goto menu;
				}

				if (loginCheck == false) {
					login();
				}

				break;

				//verify a dontation to Ledo
			case 3:

				if (loginCheck == true) {

					verify_donation();

					cout << endl << endl;

					cout << "Press ENTER to continue." << endl;
					cin.ignore();
					cin.ignore();

					goto menu;
				}

				if (loginCheck == false) {
					login();
				}

				break;

				//cancel a donation to ledo
			case 4:

				if (loginCheck == true) {

					cancel_donation();

					cout << endl << endl;

					cout << "Press ENTER to continue." << endl;
					cin.ignore();
					cin.ignore();

					goto menu;
				}

				if (loginCheck == false) {
					login();
				}
								
				break;

			//Login

			case 5:

				if (loginCheck == true) {
					cout << "You are already logged in!" << endl << endl;
					
					cout << "Press ENTER to continue." << endl;
					cin.ignore();
					cin.ignore();

					goto menu;
				}

				if (loginCheck == false) {
					login();
					
					cout << "Press ENTER to continue." << endl;
					cin.ignore();
					cin.ignore();

					goto menu;
				}
				
				break;

			//Logout
			case 6:

				cout << "Thank you for using the Ledo donation program " << user_name << ". Goodbye!" << endl;

				exit(1);
				

			default:

				break;
			}

		} while (option != 6);
		

}


void load_users() {
	ifstream inFile;
	inFile.open("users.txt");

	//reads data in the users file
	if (inFile.is_open()) {
		while (inFile >> fName >> lName >> taxNum >> user_name >> password) {

			first.push_back(fName);
			last.push_back(lName);
			tNum.push_back(taxNum);
			users.push_back(user_name);
			pssw.push_back(password);
		}
	}

	inFile.close();
}

void update_users() {
	ofstream outFile;
	outFile.open("users.txt");

	//updates data in the users file.
	for (int i = 0; i < users.size(); i++) {

		outFile << first.at(i) << " ";
		outFile << last.at(i) << " ";
		outFile << tNum.at(i) << " ";
		outFile << users.at(i) << " ";
		outFile << pssw.at(i) << " ";
		outFile << endl;
	}

	outFile.close();
}

void load_donations() {
	ifstream inFile;
	inFile.open("donations.txt");

	//reads data from the donations file.
	if (inFile.is_open()) {
		while (inFile >> bName >> bAddress >> pName >> desc >> amt >> dDate >> num) {

			business.push_back(bName);
			address.push_back(bAddress);
			project.push_back(pName);
			description.push_back(desc);
			amount.push_back(amt);
			date.push_back(dDate);
			dNum.push_back(num);
		}
	}

	inFile.close();
}

void update_donations() {
	ofstream outFile;
	outFile.open("donations.txt");

	//updates the data in the donations file.
	for (int i = 0; i < dNum.size(); i++) {

		outFile << business.at(i) << " ";
		outFile << address.at(i) << " ";
		outFile << project.at(i) << " ";
		outFile << description.at(i) << " ";
		outFile << amount.at(i) << " ";
		outFile << date.at(i) << " ";
		outFile << dNum.at(i) << " ";
		outFile << endl;
	}

	outFile.close();
}

void menu() {

	menuTop:

	cout << "1 --> Create a new taxpayer account." << endl;
	cout << "2 --> Report a donation to Ledo." << endl;
	cout << "3 --> Verify a donation to Ledo." << endl;
	cout << "4 --> Cancel a donation to Ledo." << endl;
	cout << "5 --> Login." << endl;
	cout << "6 --> Logout/Exit." << endl << endl;

	cout << "Please select a menu option: ";
	cin >> option;

	if (!cin || option < 1 || option > 6) {
		cout << "Invaild input!" << endl << endl;
		cout << "Press ENTER to continue." << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin.ignore();
		system("CLS");
		goto menuTop;
	}

	cout << endl << endl;

}


bool login() {
	cout << "Please login with your username and password." << endl << endl;

relogin:

	cout << "Username: ";
	cin >> user_name;

	cout << "Password: ";
	cin >> password;
	cout << endl;

	//checks to see if user exists
	for (int i = 0; i < users.size(); i++) {
		if (user_name == users.at(i) && password == pssw.at(i)) {
			loginCheck = true;
			cout << "Welcome " << user_name << " to the Ledo donation application!" << endl << endl;
			counter = 0;

			load_donations();

			break;
		}
	}

	//login unsuccessfull
	if (!loginCheck) {

		cout << "Invalid Login" << endl << endl;

		counter++;

		//boots user for entering wrong info
		if (counter > 2) {
			cout << "You have enterd invalid login credentials more than 3 times. Goodbye!" << endl;
			exit(1);
		}

		else {
			goto relogin;
		}
	}

	return loginCheck;

}

void create_account() {

	//makse sure there are no two user nmes the same
	bool unique = true;

	cout << "Thank you for wanting to create an account with Ledo." << endl;
	cout << "Please enter the following information: " << endl << endl;

	cout << "First Name: ";
	cin >> fName;
	cout << endl;

	cout << "Last Name: ";
	cin >> lName;
	cout << endl;

	cout << "Tax Account Number: ";
	cin >> taxNum;
	cout << endl;

	//if user name exists
	choose:

	cout << "User Name: ";
	cin >> user_name;
	cout << endl;


	//checks for a unique user name
	for (int i = 0; i < users.size(); i++) {

		if (users.at(i) == user_name) {

			cout << "The username is already taken. Please choose another one." << endl;
			unique = false;

			goto choose;
		}


	}

	cout << "Password: ";
	cin >> password;
	cout << endl;

	//if user does not currently exist
	if (unique == true) {
		first.push_back(fName);
		last.push_back(lName);
		tNum.push_back(taxNum);
		users.push_back(user_name);
		pssw.push_back(password);

		update_users();
	}

	cout << "Account created." << endl;

}

void report_donation() {

	cout << "Thank you for wanting to report a donation with Ledo." << endl;
	cout << "Please enter the following information: " << endl << endl;

	cin.clear();

	cout << "Business Name: ";
	getline(cin, bName);
	cin.ignore(numeric_limits <streamsize>::max(), '\n');
	business.push_back(bName);
	cout << endl;
	
	cout << "Business Address: ";
	getline(cin, bAddress);
	cin.ignore(numeric_limits <streamsize>::max(), '\n');
	address.push_back(bAddress);
	cout << endl;

	cout << "Project Name: ";
	getline(cin, pName);
	cin.ignore(numeric_limits <streamsize>::max(), '\n');
	project.push_back(pName);
	cout << endl;

	cout << "Project Description: ";
	getline(cin, desc);
	cin.ignore(numeric_limits <streamsize>::max(), '\n');
	description.push_back(desc);
	cout << endl;

	cout << "Donation Amount: ";
	cin >> amt;
	cin.ignore();
	amount.push_back(amt);
	cout << endl;
	
	cout << "Donation Date: ";
	cin >> dDate;
	date.push_back(dDate);
	cout << endl;

	num = 1;

	if (dNum.size() == 0) {
		goto initial;
	}

	//unique reservation number
	for (int i = 0; i < dNum.size(); i++) {
		if (num == dNum.at(i)) {
			num++;
		}
		
	}

	initial:

	cout << "Congragulations your Ledo Reservation number is: " << num << endl;
	dNum.push_back(num);

	update_donations();

}

void verify_donation() {

	bool check = false;
	cout << "Please enter the number of the donation to verify: ";
	cin >> num;
	cout << endl;

	//checks to see if a reservation is there
	for (int i = 0; i < dNum.size(); i++) {
		if (num == dNum.at(i)) {
			cout << "Your LEDO Reservation Number is Valid. The following donation has been verified." << endl << endl;

			cout << "Business: " << business.at(i) << endl;
			cout << "Address: " << address.at(i) << endl;
			cout << "Project: " << project.at(i) << endl;
			cout << "Description: " << description.at(i) << endl;
			cout << "Amount: " << amount.at(i) << endl;
			cout << "Date: " << date.at(i) << endl;
			cout << "Reservation Num: " << dNum.at(i) << endl;
			cout << endl;

			check = true;
			break;
		}
	}

	if (!check) {
		cout << "The reservation number entered is not valid!" << endl;
	}
}

void cancel_donation() {

	bool check2 = false;
	cout << "Please enter the number of the donation to cancel: ";
	cin >> num;

	//deletes all donation info
	for (int i = 0; i < dNum.size(); i++) {
		if (num == dNum.at(i)) {

			business.erase(business.begin() + i);
			address.erase(address.begin() + i);
			project.erase(project.begin() + i);
			description.erase(description.begin() + i);
			amount.erase(amount.begin() + i);
			date.erase(date.begin() + i);
			dNum.erase(dNum.begin() + i);

			cout << "The reservation has been cancled!" << endl;
			check2 = true;

			update_donations();

			break;

		}


	}

	if (!check2) {
		cout << "The reservation number entered is not valid!" << endl;
	}
}