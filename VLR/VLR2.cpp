#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;
string file_name = "data.txt";
vector<int> stdnos;
vector<int> empnos;
void fill_vectors() {
	ifstream file(file_name);
	int x;
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			stringstream ss(line);
			string first_word;
			ss >> first_word;
			if (first_word == "std") {
				ss >> x;
				stdnos.push_back(x);
			}
			else if (first_word == "emp") {
				ss >> x;
				empnos.push_back(x);
			}
		}
	}
}

void insert_student(int stdno, string name, float mark, int age) {
	auto it = find(stdnos.begin(), stdnos.end(), stdno);

	if (it != stdnos.end()) {
		cout << "Invalid student id."<< endl;
		return;
	}

	stdnos.push_back(stdno);
	string tm = to_string(mark), ta = to_string(age), tn = name;
	if (tn == "NA") tn = " ";
	if (mark == -999) tm = " ";
	if (age == -999) ta = " ";
	string record = "std " + to_string(stdno) + " " + tn + " " + tm + " " + ta;
	int rec_len = record.length();
	for (int i = 0; i < (99 - rec_len); i++)
		record += " ";
	record += "-";
	ofstream file(file_name, ios::app);

	if (file.is_open()) {
		file << record << endl;
		file.close();
		cout << "Added." << endl;
	}
}

void delete_student(int stdno) {
	ifstream file(file_name);
	streampos pos;
	int x;
	string alt = "";
	for (int i = 0; i <= 100; i++)
		alt += " ";
    if (file.is_open()) {
        string line;
		pos = file.tellg();
        while (getline(file, line)) {
            stringstream ss(line);
            string first_word;
            ss >> first_word;
			//cout << "pos is: " << pos << endl;
			if (first_word == "std") {
				ss >> x;
				//cout << "student id is: " << x << endl;
				if (x == stdno) {
					fstream output(file_name);
					output.seekg(pos, std::ios::beg);
					output << alt;
					output.close();
					return;
				}
			}
			pos = file.tellg();
        }
        file.close();
		cout << "No record.\n";
    }
    else {
        cout << "Unable to open the file." << endl;
    }
}

streampos select_student(int stdno) { // if -1 No record!
	ifstream file(file_name);
	streampos pos;
	int x;
	string o = "";
	if (file.is_open()) {
		string line;
		pos = file.tellg();
		while (getline(file, line)) {
			stringstream ss(line);
			string first_word;
			ss >> first_word;
			//cout << "pos is: " << pos << endl;
			if (first_word == "std") {
				ss >> x;
				//cout << "student id is: " << x << endl;
				if (x == stdno) {
					while (o != "-") {
						ss >> o;
						cout << o << " ";
					}
					cout << endl;
					return pos;
				}
			}
			pos = file.tellg();
		}
		return -1;
	}
}

void update_student(int stdno, string name, float mark, int age) {
	streampos pos = select_student(stdno);
	if (pos == -1) {
		cout << "No record.";
		return;
	}
	string tm = to_string(mark), ta = to_string(age), tn = name;
	if (tn == "NA") tn = " ";
	if (mark == -999) tm = " ";
	if (age = -999) ta = " ";
	string record = "std " + to_string(stdno) + " " + tn + " " + tm + " " + ta;
	int rec_len = record.length();
	for (int i = 0; i < (99 - rec_len); i++)
		record += " ";
	record += "-";
	fstream output(file_name);
	output.seekg(pos, std::ios::beg);
	output << record;
	output.close();
}

void insert_emp(int empno, string empname, float salary) {
	auto it = find(empnos.begin(), empnos.end(), empno);

	if (it != empnos.end()) {
		cout << "Invalid employee id." << endl;
		return;
	}

	empnos.push_back(empno);

	string ts = to_string(salary), tn = empname;
	if (empname == "NA") tn = " ";
	if (salary == -999) ts = " ";
	string record = "emp " + to_string(empno) + " " + tn + " " + ts;

	int rec_len = record.length();
	for (int i = 0; i < (99 - rec_len); i++)
		record += " ";
	record += "-";
	ofstream file(file_name, ios::app);

	if (file.is_open()) {
		file << record << endl;
		file.close();
		cout << "Added." << endl;
	}
}

void delete_emp(int empno) {
	ifstream file(file_name);
	streampos pos;
	int x;
	string alt = "";
	for (int i = 0; i <= 100; i++)
		alt += " ";
	if (file.is_open()) {
		string line;
		pos = file.tellg();
		while (getline(file, line)) {
			stringstream ss(line);
			string first_word;
			ss >> first_word;
			if (first_word == "emp") {
				ss >> x;
				if (x == empno) {
					fstream output(file_name);
					output.seekg(pos, std::ios::beg);
					output << alt;
					output.close();
					return;
				}
			}
			pos = file.tellg();
		}
		file.close();
		cout << "No record.\n";
	}
	else {
		cout << "Unable to open the file." << endl;
	}
}
streampos select_emp(int empno) { // if -1 No record!
	ifstream file(file_name);
	streampos pos;
	int x;
	string o = "";
	if (file.is_open()) {
		string line;
		pos = file.tellg();
		while (getline(file, line)) {
			stringstream ss(line);
			string first_word;
			ss >> first_word;
			if (first_word == "emp") {
				ss >> x;
				if (x == empno) {
					while (o != "-") {
						ss >> o;
						cout << o << " ";
					}
					cout << endl;
					return pos;
				}
			}
			pos = file.tellg();
		}
		return -1;
	}
}

void update_emp(int empno, string empname, float salary) {
	streampos pos = select_emp(empno);
	if (pos == -1) {
		cout << "No record.";
		return;
	}
	string ts = to_string(salary), tn = empname;
	if (empname == "NA") tn = " ";
	if (salary == -999) ts = " ";
	string record = "emp " + to_string(empno) + " " + tn + " " +ts;
	int rec_len = record.length();
	for (int i = 0; i < (99 - rec_len); i++)
		record += " ";
	record += "-";
	fstream output(file_name);
	output.seekg(pos, std::ios::beg);
	output << record;
	output.close();
}
void display_students() {
	ifstream file(file_name);
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			if (line.substr(0, 3) == "std") {
				cout << line << endl;
			}
		}
		file.close();
	}
}
void display_employees() {
	ifstream file(file_name);
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			if (line.substr(0, 3) == "emp") {
				cout << line << endl;
			}
		}
		file.close();
	}
}
void show_options() {
	fill_vectors();
	cout << "1- Insert student\n";
	cout << "2- Insert employee\n";
	cout << "3- delete student\n";
	cout << "4- delete employee\n";
	cout << "5- update student\n";
	cout << "6- update employee\n";
	cout << "7- select student\n";
	cout << "8- select employee\n";
	cout << "9- Display all students\n";
	cout << "10- Display all employees\n";
	cout << "11- Exit\n";
	int x, stdno, empno, age;
	float mark, salary;
	string empname, stdname;
	streampos b;
	cout << "Choose an option: ";
	cin >> x;
	switch (x) {
	case 1:
		cout << "Enter student number:\n";
		cin >> stdno;
		cout << "Enter student name: (if null Enter NA)\n";
		cin >> stdname;
		cout << "Enter student mark (if null Enter -999):\n";
		cin >> mark;
		cout << "Enter student age(if null Enter -999):\n";
		cin >> age;
		insert_student(stdno, stdname, mark, age);
		break;
	case 2:
		cout << "Enter employee number:\n";
		cin >> empno;
		cout << "Enter employee name(if null Enter NA):\n";
		cin >> empname;
		cout << "Enter employee salary(if null Enter -999):\n";
		cin >> salary;
		insert_emp(empno, empname, salary);
		break;
	case 3:
		cout << "Enter student number:\n";
		cin >> stdno;
		delete_student(stdno);
		break;
	case 4:
		cout << "Enter employee number:\n";
		cin >> empno;
		delete_emp(empno);
		break;
	case 5:
		cout << "Enter student number:\n";
		cin >> stdno;
		cout << "Enter student name(if null Enter NA):\n";
		cin >> stdname;
		cout << "Enter student mark(if null Enter -999):\n";
		cin >> mark;
		cout << "Enter student age(if null Enter -999):\n";
		cin >> age;
		update_student(stdno, stdname, mark, age);
		break;
	case 6:
		cout << "Enter employee number:\n";
		cin >> empno;
		cout << "Enter employee name(if null Enter NA):\n";
		cin >> empname;
		cout << "Enter employee salary(if null Enter -999):\n";
		cin >> salary;
		update_emp(empno, empname, salary);
		break;
	case 7:
		cout << "Enter student number:\n";
		cin >> stdno;
		b = select_student(stdno);
		if (b == -1) cout << "No record!\n";
		break;
	case 8:
		cout << "Enter employee number:\n";
		cin >> empno;
		b = select_emp(empno);
		if (b == -1) cout << "No record!\n";
		break;
	case 9:
		display_students();
		break;
	case 10:
		display_employees();
		break;
	case 11:
		break;
	default:
		cout << "Invalid choice." << endl;
		break;
	}
}

int main() {
	cout << "Enter data file name:";
	cin >> file_name;
	ifstream file(file_name);
	if (file.is_open())
		show_options();
	else
		cout << "Could not open file.";
	return 0;
}