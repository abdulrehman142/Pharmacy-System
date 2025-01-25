#include"Store.h"
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
using namespace std;

//Function for Integer input
void InputInt(int& num) {
	double input;
	while (!(cin >> input) || static_cast<int>(input) != input) {
		cout << "Incorrect Datatype:Please try again\n";
		cin.clear();
		cin.ignore(1000000000, '\n');
	}
	num = input;
}

//Function for double input
void inputInt(double& input) {
	while (!(cin >> input)) {
		cout << "Incorrect Datatype:Please try again\n";
		cin.clear();
		cin.ignore(1000000000, '\n');
	}
}

Medicine::Medicine() {
	name = nullptr;
	formula = nullptr;
	dosage = nullptr;
	man_date = nullptr;
	exp_date = nullptr;
	price = nullptr;
	quantity = nullptr;
}

Medicine::Medicine(string* n, string* f, string* d, string* man, string* exp, double* pri, double* quant) {
	name = n;
	formula = f;
	dosage = d;
	man_date = man;
	exp_date = exp;
	price = pri;
	quantity = quant;
}

prescription::prescription() :Medicine() {
	size = 0;
}

void prescription::readfromfile() {
	ifstream file;
	file.open("prescription.txt");
	if (!file.is_open()) {
		cout << "Unable to load from file\n";
	}
	string line;
	size = 0;
	while (getline(file, line)) {
		size++;
	}
	file.close();
	file.open("prescription.txt");

	name = new string[size];
	formula = new string[size];
	dosage = new string[size];
	man_date = new string[size];
	exp_date = new string[size];
	price = new double[size];
	quantity = new double[size];

	for (int i = 0; i < size; i++) {
		file >> name[i];
		file >> formula[i];
		file >> dosage[i];
		file >> man_date[i];
		file >> exp_date[i];
		file >> price[i];
		file >> quantity[i];
	}
	file.close();

}

nonprescription::nonprescription() :Medicine() {
	size2 = 0;
}

void nonprescription::readfromfile() {
	ifstream file;
	file.open("nonprescription.txt");
	if (!file.is_open()) {
		cout << "Unable to load from file\n";
	}
	string line;
	size2 = 0;
	while (getline(file, line)) {
		size2++;
	}
	file.close();
	file.open("nonprescription.txt");

	name = new string[size2];
	formula = new string[size2];
	dosage = new string[size2];
	man_date = new string[size2];
	exp_date = new string[size2];
	price = new double[size2];
	quantity = new double[size2];

	for (int i = 0; i < size2; i++) {
		file >> name[i];
		file >> formula[i];
		file >> dosage[i];
		file >> man_date[i];
		file >> exp_date[i];
		file >> price[i];
		file >> quantity[i];

	}
	file.close();
}

void prescription::display() {
	cout << endl;
	cout << "Name\t\t\tFormula\t\tDosage\t\tManufacture-Date\tExpiry-Date\t\tPrice\t\tQuantity" << endl;
	for (int i = 0; i < size; i++) {
		cout << name[i] << "\t\t" << formula[i] << "\t\t" << dosage[i] << "\t\t";
		cout << man_date[i] << "\t\t" << exp_date[i] << "\t\t";
		cout << price[i] << "\t\t" << quantity[i] << endl;
	}
	cout << endl;
}

void nonprescription::display() {
	cout << endl;
	cout << "Name\t\t\tFormula\t\tDosage\t\tManufacture-Date\tExpiry-Date\t\tPrice\t\tQuantity" << endl;
	for (int i = 0; i < size2; i++) {
		if (i > 33) {
			cout << name[i] << "\t\t\t" << formula[i] << "\t\t" << dosage[i] << "\t\t";
			cout << man_date[i] << "\t\t" << exp_date[i] << "\t\t";
			cout << price[i] << "\t\t" << quantity[i] << endl;
		}
		else {
			cout << name[i] << "\t\t" << formula[i] << "\t\t" << dosage[i] << "\t\t";
			cout << man_date[i] << "\t\t" << exp_date[i] << "\t\t";
			cout << price[i] << "\t\t" << quantity[i] << endl;
		}
	}
	cout << endl;
}

bool prescription::find(string Name, double Quantity) {
	readfromfile();
	bool found = false;
	for (int i = 0; i < size; i++) {
		if (Name == name[i]) {
			if (quantity[i] >= Quantity) { // Ensure there is enough stock
				quantity[i] -= Quantity;   // Update the quantity
				found = true;
			}
			else {
				cout << "Not enough stock available." << endl;
				return false;
			}
			break;
		}
	}
	if (found) {
		updatefile(); // Save all data to file after modifying the quantity
		return true;
	}
	return false;
}

void prescription::updatefile() {
	ofstream file;
	file.open("prescription.txt", ios::trunc); // Truncate the file to overwrite with new data
	if (!file.is_open()) {
		cout << "Failed to open file for writing." << endl;
		return;
	}
	for (int i = 0; i < size; i++) {
		file << name[i] << " "
			<< formula[i] << " "
			<< dosage[i] << " "
			<< man_date[i] << " "
			<< exp_date[i] << " "
			<< price[i] << " "
			<< quantity[i] << "\n";
	}
	file.close();
}

bool nonprescription::Find(string Name, double Quantity) {
	readfromfile();
	bool found = false;
	for (int i = 0; i < size2; i++) {
		if (Name == name[i]) {
			if (quantity[i] >= Quantity) { // Ensure there is enough stock
				quantity[i] -= Quantity;   // Update the quantity
				found = true;
			}
			else {
				cout << "Not enough stock available." << endl;
				return false;
			}
			break;
		}
	}
	if (found) {
		updatefile(); // Save all data to file after modifying the quantity
		return true;
	}
	return false;
}

void nonprescription::updatefile() {
	ofstream file;
	file.open("nonprescription.txt", ios::trunc); // Truncate the file to overwrite with new data
	if (!file.is_open()) {
		cout << "Failed to open file for writing." << endl;
		return;
	}
	for (int i = 0; i < size2; i++) {
		file << name[i] << " "
			<< formula[i] << " "
			<< dosage[i] << " "
			<< man_date[i] << " "
			<< exp_date[i] << " "
			<< price[i] << " "
			<< quantity[i] << "\n";
	}
	file.close();
}

double prescription::total(string Name) {
	readfromfile();
	double sum = 0;
	for (int i = 0; i < size; i++) {
		if (Name == name[i]) {
			sum = price[i];
		}
	}
	return sum;
}

double nonprescription::Total(string Name) {
	readfromfile();
	double sum = 0;
	for (int i = 0; i < size2; i++) {
		if (Name == name[i]) {
			sum = price[i];
		}
	}
	return sum;
}

Discount::Discount() {
	discount = 0;
}

double Discount::percent(double bill) {
	double total = 0;
	//Discount of 0 percent
	if (bill < 200) {
		return bill;
	}
	//Discount of 5 percent
	else if (bill >= 200 && bill < 500) {
		total = bill * (5.0 / 100);
		bill = bill - total;
		return bill;
	}
	//Discount of 10 percent
	else if (bill >= 500 && bill < 1000) {
		total = bill * (10.0 / 100);
		bill = bill - total;
		return bill;
	}
	//Discount of 15 percent
	else if (bill >= 1000) {
		total = bill * (15.0 / 100);
		bill = bill - total;
		return bill;
	}
}

Cart::Cart() {
	Name = nullptr;
	quantity = nullptr;
	type = 0;
	sum = 0;
	bill = 0;
	size = 0;
}

void Cart::add() {
	//files for cart
	int choice;
	double count;
	ofstream file;
	file.open("cart.txt", ios::app);
	file << "------------------------------------------------------\n";
	do {
		count = 0;
		string* temp1 = new string[size + 1];
		double* temp2 = new double[size + 1];
		for (int i = 0; i < size; i++) {
			temp1[i] = Name[i];
			temp2[i] = quantity[i];
		}

		cout << "The type of medicine you want to add:\n";
		cout << "1, Prescription\n";
		cout << "2, Non-Prescription\n";
		cin >> type;
		while (type != 1 && type != 2) {
			cout << "Wrong input-Enter again: ";
			cin >> type;
		}

		cout << "Enter name of Medicine: ";
		cin >> temp1[size];
		cout << "Enter quantity: ";
		cin >> temp2[size];

		if (type == 1) {
			if (find(temp1[size], temp2[size])) {
				cout << "Item added\n";
				file << "Item: " << temp1[size] << "  Quantity: " << temp2[size] << "\n";
				count += total(temp1[size]);
				count *= temp2[size];
				sum += count;
			}
			else {
				cout << "Item not found\n";
				temp1[size] = "", temp2[size] = 0;
			}
		}
		else if (type == 2) {
			if (Find(temp1[size], temp2[size])) {
				cout << "Item added\n";
				file << "Item: " << temp1[size] << "  Quantity: " << temp2[size] << "\n";
				count += Total(temp1[size]);
				count *= temp2[size];
				sum += count;
			}
			else {
				cout << "Item not found\n";
				temp1[size] = "", temp2[size] = 0;
			}
		}
		cout << "Press -1 if you don't want to add else press 1: ";
		cin >> choice;
		while (choice != -1 && choice != 1) {
			cout << "Wrong input-Enter again: ";
			cin >> choice;
		}

		delete[] Name;
		delete[] quantity;
		Name = temp1;
		quantity = temp2;
		size++;

	} while (choice != -1);

	Discount* d1;
	d1 = new Discount;
	bill = d1->percent(sum);

	file << "Total bill = " << sum << "PKR\n";
	file << "Total bill after discount = " << bill << "PKR\n";
	file.close();

	delete d1;
}

void Cart::display() {
	cout << "\n\n";
	cout << "Cart:\n";
	ifstream file;
	file.open("cart.txt");
	string line;
	while (getline(file, line)) {
		cout << line << endl;
	}
	file.close();
}

void Cart::updatecart(double total) {
	ofstream file;
	file.open("cart.txt", ios::trunc); // Truncate the file to overwrite with new data
	file << "------------------------------------------------------\n";
	if (!file.is_open()) {
		cout << "Failed to open file for writing." << endl;
		return;
	}
	for (int i = 0; i < size; i++) {
		file << "Item: " << Name[i] << "  Quantity: " << quantity[i] << "\n";
	}
	file << "Total bill = " << sum << "PKR\n";
	file << "Total bill after discount = " << bill << "PKR\n";
	file << "Total bill after removing = " << total << "PKR\n";
	bill = total;
	file.close();
}

void Cart::remove() {
	string name;
	double amount;
	cout << "Enter name of medicine you want to remove: ";
	cin >> name;
	cout << "Enter quantity of medicine you want to remove: ";
	cin >> amount;

	double count = 0;
	double final = bill;
	if (find(name, -amount)) {
		count = total(name);
		count *= amount;
		final -= count;
	}
	else if (Find(name, -amount)) {
		count = Total(name);
		count *= amount;
		final -= count;
	}

	for (int i = 0; i < size; i++) {
		if (name == Name[i]) {
			quantity[i] -= amount;
			updatecart(final);
		}
	}
}

double Cart::getbil() {
	return bill;
}

void Cart::setbil(double a) {
	updatecart(a);
}

void record::display() {
	ifstream file;
	file.open("record.txt");
	string line;
	while (getline(file, line)) {
		cout << line << endl;
	}
	file.close();
}

void level:: display() {
	cout << "Exp:" << exp << "\nDiscount:" << discount << "\nPasscode:" << passcode;
}

double level::getexp() {
	return exp;
}

void level::setPasscode(string code) {
	passcode = code;
}

double level::getDiscount() {
	return discount;
}

string level:: getPasscode() {
	return passcode;
}

void level:: increaseExp(double ex) {
	exp += ex;
}

double level::getMaxExp() {
	return maxExp;
}

level:: level(){}

bronze::bronze() {
	discount = 5;
	exp = 0;
	maxExp = 100;
}

string bronze::getname() {
	return "bronze";
}

silver::silver() {
	discount = 10;
	exp = 0;
	maxExp = 300;
}

string silver::getname() {
	return "silver";
}

gold::gold() {
	discount = 15;
	exp = 0;
	maxExp = 600;
}

string gold::getname() {
	return "gold";
}

platinum::platinum() {
	discount = 20;
	exp = 0;
	maxExp = 0;
}

string platinum::getname() {
	return "plat";
}

void Customer::readFromFile(ifstream& f) {
	getline(f, name, '\t');
	f >> age;
	f.ignore();
	getline(f, email, '\t');
	getline(f, address, '\t');
	string lev;
	getline(f, lev, '\t');
	if (lev == "bronze") {
		r = new bronze();
	}
	else if (lev == "silver") {
		r = new silver();
	}
	else if (lev == "gold") {
		r = new gold();
	}
	else{
		r = new platinum();
	}
	double exp;
	f >> exp;
	r->increaseExp(exp);
	f.ignore();
	getline(f, lev, '\n');
	r->setPasscode(lev);
}
void Customer::saveToFile(ofstream& of) {
	of << name << '\t' << age << '\t' << email << '\t' << address << '\t' 
	   << r->getname() << '\t' << r->getexp() << '\t' << r->getPasscode() << endl;
}
void Customer::increaseLevel(double exp,string pass) {
	if (r->getMaxExp() != 0) {
		if (r->getname() == "bronze") {
			delete r;
			r = new silver();
			r->increaseExp(exp);
		}
		else if (r->getname() == "silver") {
			int exp = 0;
			delete r;
			r = new gold();
			r->increaseExp(exp);
		}
		else if (r->getname() == "gold") {
			int exp = 0;
			delete r;
			r = new platinum();
			r->increaseExp(exp);
		}
		r->setPasscode(pass);
		cout << "Horray!!!Your rank increased to " << r->getname() << endl;
	}
}
int Customer::getAge() {
	return age;
}
void Customer::Display() {
	cout << name << "\t\t" << age << "\t\t" << email << "\t\t" << address << "\t\t" 
		 << r->getname() << "\t\t" << r->getexp() << "\t\t" << r->getPasscode() << endl;
}
void Customer::Displaynew() {
	cout << name << "\t\t" << age << "\t\t" << email << "\t\t" << address << "\t\t"
		<< endl;
}
string Person::getname() {
	return name;
}
bool Person::approveName(string& Name) {
	for (int i = 0; i < Name.length(); i++) {
		if (Name[i] > 122 || (Name[i] < 97 && Name[i]>90) || (i == 0 && Name[i] < 65 && Name[i] == ' ')) {
			return false;
		}
		else if (i != 0 && Name[i - 1] == ' ' && Name[i] >= 97) {
			return false;
		}
		else if (i != 0 && ((Name[i] < 97 && Name[i] > 90) && Name[i - 1] != ' ')) {
			return false;
		}
	}
	return true;
}
bool Person::approveAge(int& age) {
	if (age <= 18 || age >= 100) {
		return false;
	}
	return true;
}
bool Person::approveEmail(string& Email) {
	bool check = false;
	int index = 0, index2 = 0;
	string sub;
	sub = Email.substr(Email.length() - 4, Email.length());
	if (sub != ".com") {
		return false;
	}
	for (int i = 0; i < Email.length() - 4; i++) {
		if (Email[i] == '@' && !check || check) {
			if (!check) {
				check = true;
				index = i;
			}else if (i > index && Email[i] >= 65 && Email[i] <= 90) {
				return false;
			}
		}
	}
	if (!check) {
		return false;
	}
	else {
		return true;
	}
}

void worker::readFromFile(ifstream& f) {
	getline(f, name, '\t');
	f >> age;
	f.ignore();
	getline(f, email, '\t');
	getline(f, address, '\t');
	string lev;
	getline(f, login, '\t');
	getline(f, passcode, '\n');
}
void worker::saveToFile(ofstream& of) {
	of << name << '\t' << age << '\t' << email << '\t' << address << '\t'
		<< login << '\t' << passcode << endl;
}
void worker::Display() {
	cout << name << "\t\t" << age << "\t\t" << email << "\t\t" << address << "\t\t"
		<< login << "\t\t" << passcode << endl;
}
void worker::DisplayNew() {
	cout << name << "\t\t" << age << "\t\t" << email << "\t\t" << address << endl;
}
string worker::getpasscode() {
	return passcode;
}
string worker::getlog() {
	return login;
}
void worker::setCustomer(Customer*& obj) {
	c = obj;
}

void Customer::generateAcc() {
	r = new bronze();
	int pass = 0;
	for (int i = 0; i < 3; i++) {
		pass *= 10;
		pass += rand() % 10;
	}
	r->setPasscode(to_string(pass));
}

bool Customer::find(string& Name, string& pass) {
	if (Name == this->name) {
		pass.clear();
		pass += r->getPasscode();
		return true;
	}
	return false;
}

double Customer::getDis() {
	return r->getDiscount();
}

void Customer::increasexp(double exp,string pass) {
	double remanent;
	r->increaseExp(exp);
	if (r->getexp() >= r->getMaxExp()) {
		remanent = r->getexp() - r->getMaxExp();
		increaseLevel(remanent,pass);
	}
}

bool worker::Approveaccount() {
	char app;
	c[Customer::numOfCustomers - 1].Displaynew();
	cout << "Do you want to approve this account(y/n):";
	cin >> app;
	while (app != 'y' && app != 'n') {
		cout << "Incorrect option:please try Again\n";
		cin >> app;
	}
	if (app == 'y') {
		c[Customer::numOfCustomers - 1].generateAcc();
		cout << "Account successfully generated\n";
		return true;
	}
	else {
		return false;
	}
}

bool worker::ApproveWorker(worker& obj) {
	char app;
	obj.DisplayNew();
	cout << "Do you want to approve this account(y/n):";
	cin >> app;
	while (app != 'y' && app != 'n') {
		cout << "Incorrect option:please try Again\n";
		cin >> app;
	}
	if (app == 'y') {
		obj.generateAcc();
		cout << "Account successfully generated\n";
		return true;
	}
	else {
		return false;
	}
}

void worker::generateAcc() {
	cin.ignore();
	cout << "Enter your login:";
	Input(login);
	cout << "Enter your password:";
	Input(passcode);
}