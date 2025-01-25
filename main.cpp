#include "Store.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<ctime>
#include<iomanip>
#include<windows.h>
#include<thread>
#include<chrono>
using namespace std;

//Function for Integer input
void InputInt(int& num);

//Function to store time
string currentDateTime() {
	auto now = chrono::system_clock::now(); // Get current time as a time_point
	time_t now_time = chrono::system_clock::to_time_t(now); // Convert to time_t

	tm bt{};
	localtime_s(&bt, &now_time); // Secure version of localtime

	stringstream ss;
	ss << put_time(&bt, "%Y-%m-%d %H:%M:%S");
	return ss.str();
}

// Function to set console text color
void SetConsoleColor(int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void Input(string& word) {
	word.clear();  // Ensure the string is empty before filling it
	char input;
	while ((input = cin.get()) != '\n') {
		word += input;
	}
}

int Customer::numOfCustomers;
int worker::workersNum;
void loadCustomers(Customer*& cs1) {
	ifstream file("customers.txt");
	int size;
	file >> size;
	file.ignore();
	Customer::numOfCustomers = size;
	cs1 = new Customer[size]();
	for (int i = 0; i < size; i++) {
		cs1[i].readFromFile(file);
	}
	file.close();
}
void saveCustomer(Customer*& cs1) {
	ofstream file("customers.txt");
	file << Customer::numOfCustomers;
	file << endl;
	for (int i = 0; i < Customer::numOfCustomers; i++) {
		cs1[i].saveToFile(file);
	}
	file.close();
}
void loadWorker(worker*& cs1,Customer*& cs2) {
	ifstream file("Employee.txt");
	int size;
	file >> size;
	file.ignore();
	worker::workersNum = size;
	cs1 = new worker[size]();
	for (int i = 0; i < size; i++) {
		cs1[i].readFromFile(file);
		cs1[i].setCustomer(cs2);
	}
	file.close();
}
void saveWorker(worker*& cs1) {
	ofstream file("Employee.txt");
	file << worker::workersNum;
	file << endl;
	for (int i = 0; i < worker::workersNum; i++) {
		cs1[i].saveToFile(file);
	}
	file.close();
}
void displayCus(Customer*& cs1) {
	cout << "Name" << "\t\t\t" << "Age" << "\t\t\t" << "Email" << "\t\t\t\t" << "Address" << "\t\t"
		<< "Rank" << "\t\t" << "EXP"<<"\t\t"<<"Passcode" << endl;
	for (int i = 0; i < Customer::numOfCustomers; i++) {
		cs1[i].Display();
	}
}
void displayworker(worker*& cs1) {
	cout << "Name" << "\t\t\t" << "Age" << "\t\t\t" << "Email" << "\t\t\t" << "Address" << "\t\t"
		<< "LoginId" << "\t\t" << "Passcode" << endl;
	for (int i = 0; i < worker::workersNum; i++) {
		cs1[i].Display();
	}
}
void AddnewAcc(Customer*& cs1,worker*& cs2) {
	Customer* temp = cs1;
	cs1 = new Customer[Customer::numOfCustomers + 1]();
	for (int i = 0; i < Customer::numOfCustomers; i++) {
		cs1[i] = temp[i];
	}
	delete[] temp;
	cin >> cs1[Customer::numOfCustomers];
	for (int i = 0; i < worker::workersNum; i++) {
		cs2[i].setCustomer(cs1);
	}
	Customer::numOfCustomers++;
}
void AddWorkerACC(Customer*& cs1, worker*& cs2) {
	worker* temp = cs2;
	cs2 = new worker[worker::workersNum + 1]();
	for (int i = 0; i < worker::workersNum; i++) {
		cs2[i] = temp[i];
	}
	delete[] temp;
	cin >> cs2[worker::workersNum];
	cs2[worker::workersNum].setCustomer(cs1);
	worker::workersNum++;
}

bool find(worker*& cs2,string log, string& Name, string& pass, int index) {
	for (int i = 0; i < worker::workersNum; i++) {
		if (cs2[i].getlog() == log) {
			Name = cs2[i].getname();
			pass += cs2[i].getpasscode();
			index = i;
			return true;
		}
	}
	return false;
}

bool find(Customer*& cs2, string& Name, string& pass, int& index) {
	for (int i = 0; i < Customer::numOfCustomers; i++) {
		if (cs2[i].find(Name, pass)) {
			index = i;
			return true;
		}
	}
	return false;
}


void deleteAcc(Customer*& cs1,worker*& cs2) {
	Customer* temp = cs1;
	cs1 = new Customer[Customer::numOfCustomers - 1]();
	for (int i = 0; i < Customer::numOfCustomers - 1; i++) {
		cs1[i] = temp[i];
	}
	for (int i = 0; i < worker::workersNum; i++) {
		cs2[i].setCustomer(cs1);
	}
	delete[] temp;
	Customer::numOfCustomers -= 1;
}

void deleteAcc(worker*& cs1, Customer*& cs2) {
	worker* temp = cs1;
	cs1 = new worker[worker::workersNum - 1]();
	for (int i = 0; i < worker::workersNum - 1; i++) {
		cs1[i] = temp[i];
	}
	delete[] temp;
	worker::workersNum -= 1;
}

int main()
{
	// Loading screen
	SetConsoleColor(14); //Light Yellow color
	cout << "\n\n\n\n\n\n\n\n\n";
	cout << " __      __       .__                                ___________     \n";
	cout << "/  \\    /  \\ ____ |  |   ____  ____   _____   ____   \\__    ___/___  \n";
	cout << "\\   \\/\\/   // __ \\|  | _/ ___\\/  _ \\ /     \\_/ __ \\    |    | /  _ \\ \n";
	cout << " \\        /\\  ___/|  |_\\  \\__(  <_> )  Y Y  \\  ___/    |    |(  <_> )\n";
	cout << "  \\__/\  /  \\___  >____/\\___  >____/|__|_|  /\\___  >   |____| \\____/ \n";
	cout << "       \\/       \\/          \\/            \\/     \\/                 \n";
	cout << "\t\t\t\t\t\t\t\t________         .__  .__                  _________ __                        \n";
	cout << "\t\t\t\t\t\t\t\t\\_____  \\   ____ |  | |__| ____   ____    /   _____//  |_  ___________   ____  \n";
	cout << "\t\t\t\t\t\t\t\t /   |   \\ /    \\|  | |  |/    \\_/ __ \\   \\_____  \\\\   __\\/  _ \\_  __ \\_/ __ \\ \n";
	cout << "\t\t\t\t\t\t\t\t/    |    \\   |  \\  |_|  |   |  \\  ___/   /        \\|  | (  <_> )  | \\/\\  ___/ \n";
	cout << "\t\t\t\t\t\t\t\t\\_______  /___|  /____/__|___|  /\\___  > /_______  /|__|  \\____/|__|    \\___  >\n";
	cout << "\t\t\t\t\t\t\t\t        \\/     \\/             \\/     \\/          \\/                         \\/ \n";
	cout << "\n\n\n\n";
	SetConsoleColor(6); //Yellow color
	this_thread::sleep_for(std::chrono::milliseconds(2000));
	cout << "Loading ";
	for (int i = 0; i < 100; ++i) {
		std::cout << ".";
		std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Shorter delay (500 milliseconds)
	}
	SetConsoleColor(15); //Reset color
	cout << "\033[2J\033[1;1H"; // This is a Unix-like system command to clear the screen


	//Code
    srand(time(NULL));
	prescription p1;
	nonprescription p2;
	Cart c1;
	Customer* cs1;
	worker* cs2;
	loadCustomers(cs1);
	loadWorker(cs2,cs1);
	string login;
	string Name;
	string passcode;
	int index = 0;
	SetConsoleColor(12); //light red
	cout << "\nEnter your login id: ";
	cin >> login;
	while (!find(cs2, login, Name, passcode,index)) {
		cout << "Incorrect email:Please try Again\n";
		cout << "Enter your login id: ";
		cin >> login;
	}
	string password;
	cout << "Enter your password: ";
	cin >> password;
	while (passcode != password) {
		cout << "Incorrect:Please try again\n";
		cout << "Enter your password:";
		cin >> password;
	}
	cout << "\nWelcome " << Name << "!\n";

	int select;
	do {
		int choice;
		SetConsoleColor(6); //Yellow color
		cout << "\nMenu:\n\n";
		cout << "---------------------------------------" << endl;
		cout << "1:  Prescription Medicine\n";
		cout << "2:  NonPrescription Medicine\n"
			 << "3:  Add to Cart\n"
			 << "4:  Delete from Cart\n"
			 << "5.  View Cart\n"
			 << "6:  Final Bill\n"
			 << "7:  Add an Employee Account\n"
			 << "8:  Employess Information\n"
			 << "9:  Get a Subscription card\n"
			 << "10: Subscription Members Info\n"
			 << "11: Transactions\n"
			 << "12: Exit\n";
		cout << "---------------------------------------" << endl;
		SetConsoleColor(9); //Blue color
		cout << "Select option from above: ";
		InputInt(choice);

		if (choice == 1) {
			system("cls");
			SetConsoleColor(2); // green
			p1.readfromfile();
			p1.display();
		}
		else if (choice == 2) {
			system("cls");
			SetConsoleColor(2); // green
			p2.readfromfile();
			p2.display();
		}
		else if (choice == 10) {
			system("cls");
			SetConsoleColor(14); //Light Yellow color
			displayCus(cs1);
		}
		else if (choice == 8) {
			system("cls");
			SetConsoleColor(14); //Light Yellow color
			displayworker(cs2);
		}
		else if (choice == 9) {
			system("cls");
			SetConsoleColor(14); //Light Yellow color
			AddnewAcc(cs1, cs2);
			if (!cs2[index].Approveaccount()) {
				deleteAcc(cs1, cs2);
			}
		}
		else if (choice == 3) {
			SetConsoleColor(14); //Light Yellow color
			c1.add();
		}
		else if (choice == 4) {
			SetConsoleColor(4);//red
			c1.remove();
		}
		else if (choice == 5) {
			system("cls");
			SetConsoleColor(9); //Blue color
			c1.display();
		}
		else if (choice == 6) {
			system("cls");
			SetConsoleColor(6); //Yellow color
		    char get;
			cout << "Are you a subscription member?(y/n):";
			cin >> get;
			while (get != 'y' && get != 'n') {
				cout << "incorrect Input:Please try again\n";
				cout << "Are you a subscription member?(y/n):";
				cin >> get;
			}
			if (get == 'y') {
				string Name,pass,password;
				int index;
				cout << "Enter your name:";
				cin.ignore();
				Input(Name);
				while (!find(cs1, Name, pass, index)) {
					cout << "Account not found\n"
						<< "Please try again\n";
					Input(Name);
				}
				cout << "Enter your passcode:";
				Input(password);
				while (pass != password) {
					cout << "Incorrect Password:Try again\n";
					cout << "Enter your passcode:";
					Input(password);
				}
				double amount = c1.getbil() - (c1.getbil()/100) * cs1[index].getDis();
				c1.setbil(amount);
				double total = amount;
				amount /= 10;
				cs1[index].increasexp(amount,pass);
				fstream record;
				record.open("record.txt", ios::app);
				string line;
				ifstream file;
				file.open("cart.txt");
				while (getline(file, line)) {
					record << line << endl;
				}
				file.close();
				record << "Name: " << Name << '\n' << "Age: " << cs1[index].getAge() << endl;
				record << "Final bill: = " << total << "PKR\n";
				record << "Time of Payment: " << currentDateTime() << endl;
				record.close();
			}
			else {
				string name;
				int age;
				cout << "Enter your name:";
				cin.ignore();
				Input(name);
				cout << "Enter your age:";
				cin >> age;
				while (age <= 0 || age > 100) {
					cout << "Incorrect age:Please try again\n";
					cin >> age;
				}
				fstream record;
			    record.open("record.txt", ios::app);
				string line;
				ifstream file;
				file.open("cart.txt");
				while (getline(file,line)) {
					record << line << endl;
				}
				file.close();
				record << "Name: " << name << '\n' << "Age: " << age << endl;
				record << "Final bill: = " << c1.getbil() << "PKR\n";
				record << "Time of Payment: " << currentDateTime() << endl;
				record.close();
			}
			c1.display();
		}
		else if (choice == 11) {
			system("cls");
			SetConsoleColor(6); //Yellow color
			record r1;
			r1.display();
		}
		else if (choice == 12) {
			system("cls");
			SetConsoleColor(14); //Light Yellow color
			saveCustomer(cs1);
			saveWorker(cs2);
			ofstream clearFile("cart.txt", ios::trunc);  //for clearing cart after program starts
			clearFile.close();
			return 0;
		}
		else if (choice == 7) {
			system("cls");
			SetConsoleColor(14); //Light Yellow color
			AddWorkerACC(cs1, cs2);
			if (!cs2[index].ApproveWorker(cs2[worker::workersNum - 1])) {
				deleteAcc(cs2, cs1);
			}
		}
		SetConsoleColor(12); //light red
		cout << "Enter 1 to go to menu else press anything: ";
		cin >> select;
	} while (select == 1);
}