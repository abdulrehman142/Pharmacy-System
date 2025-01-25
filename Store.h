#pragma once
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

//function for operator overloading
void Input(string& word);

class Medicine
{
protected:
	string* name;
	string* formula;
	string* dosage;
	string* man_date;
	string* exp_date;
	double* price;
	double* quantity;
public:
	Medicine();
	Medicine(string* n, string* f, string* d, string* man, string* exp, double* pri, double* quant);
	virtual void readfromfile() = 0;
	virtual void display() = 0;
	virtual void updatefile() = 0;
};

class prescription :public Medicine {
private:
	int size;
public:
	prescription();
	void readfromfile();
	void display();
	void updatefile();
	bool find(string Name, double Quantity);
	double total(string Name);
};

class nonprescription :public Medicine {
private:
	int size2;
public:
	nonprescription();
	void readfromfile();
	void display();
	void updatefile();
	bool Find(string Name, double Quantity);
	double Total(string Name);
};

class Cart :public prescription, public nonprescription {
private:
	string* Name;
	int type;
	double* quantity;
	double sum;
	double bill;
	int size;
public:
	Cart();
	void add();
	double getbil();
	void setbil(double a);
	void remove();
	void display();
	void updatecart(double a);
};

class Discount {
	double discount;
public:
	Discount();
	double percent(double a);
};

class record : public Cart {
public:
	void display();
};

class level {
protected:
	double exp = 0;
	double maxExp;
	double discount;
	string passcode;
public:
	level();
	void display();
	double getexp();
	void setPasscode(string code);
	double getDiscount();
	double getMaxExp();
	string getPasscode();
	virtual string getname() = 0;
	void increaseExp(double ex);
};
class bronze :public level {
public:
	bronze();
	virtual string getname();
};
class silver : public level {
public:
	silver();
	virtual string getname();
};
class gold : public level {
public:
	gold();
	virtual string getname();
};
class platinum : public level {
public:
	platinum();
	virtual string getname();
};

class Person {
protected:
	string name;
	int age;
	string email;
	string address;
public:
	Person() :name(), age(), email(), address() {}
	virtual void readFromFile(ifstream& f) = 0;
	virtual void saveToFile(ofstream& of) = 0;
	virtual void Display() = 0;
	virtual void generateAcc() = 0;
	bool approveName(string& Name);
	bool approveAge(int& age);
	bool approveEmail(string& Email);
	string getname();
};

class Customer :public Person {
private:
	level* r;
public:
	static int numOfCustomers;
	Customer() :Person(), r(nullptr) {}
	virtual void readFromFile(ifstream& f);
	virtual void saveToFile(ofstream& f);
	void increaseLevel(double exp,string pass);
	double getDis();
	int getAge();
	virtual void Display();
	void Displaynew();
	virtual void generateAcc();
	void increasexp(double exp,string pass);
	
	bool find(string& Name, string& pass);
	friend istream& operator>>(istream& is, Customer& obj) {
		cout << "Enter your name:";
		cin.ignore();
		Input(obj.name);
		while (!obj.approveName(obj.name)) {
			cout << "Incorrect Format:Try again\n";
			cout << "Enter your name:";
			Input(obj.name);
		}
		cout << "Enter your Age:";
		is >> obj.age;
		while (!obj.approveAge(obj.age)) {
			cout << "Incorrect Age:Please try again\n";
			cout << "Enter your Age:";
			is >> obj.age;
		}
		cin.ignore();
		cout << "Enter your email address:";
		Input(obj.email);
		while (!obj.approveEmail(obj.email)) {
			cout << "Incorrect Email:Please Check again\n";
			cout << "Enter your email address:";
			Input(obj.email);
		}
		cout << "Enter your address:";
		Input(obj.address);
		return is;
	}
};

class worker :public Person {
	Customer* c = nullptr;
	string login;
	string passcode = "";
public:
	static int workersNum;
	virtual void readFromFile(ifstream& f);
	virtual void saveToFile(ofstream& f);
	virtual void Display();
	virtual void DisplayNew();
	string getlog();
	string getpasscode();
	void setCustomer(Customer*& obj);
	bool Approveaccount();
	bool ApproveWorker(worker& obj);
	virtual void generateAcc();
	friend istream& operator>>(istream& is, worker& obj) {
		cout << "Enter your name:";
		cin.ignore();
		Input(obj.name);
		while (!obj.approveName(obj.name)) {
			cout << "Incorrect Format:Try again\n";
			cout << "Enter your name:";
			Input(obj.name);
		}
		cout << "Enter your Age:";
		is >> obj.age;
		while (!obj.approveAge(obj.age)) {
			cout << "Incorrect Age:Please try again\n";
			cout << "Enter your Age:";
			is >> obj.age;
		}
		cin.ignore();
		cout << "Enter your email address:";
		Input(obj.email);
		while (!obj.approveEmail(obj.email)) {
			cout << "Incorrect Email:Please Check again\n";
			cout << "Enter your email address:";
			Input(obj.email);
		}
		cout << "Enter your address:";
		Input(obj.address);
		return is;
	}
};