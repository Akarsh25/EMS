#include "employee.h"

employee::employee() {
	Name = "";
	uniqueID = 0;
	Position = "";
	Department = "";
    hours=0.0;
	Salary = 0.0;
}
string
employee::getName() {
	return Name;
}

void
employee::setName(string n) {
	Name = n;
}

int
employee::getUniqueID() {
	return uniqueID;
}

void
employee::setUniqueID(int id) {
	uniqueID = id;
}

string
employee::getPosition() {
	return Position;
}

void
employee::setPosition(string pos) {
	Position = pos;
}

string
employee::getDepartment() {
	return Department;
}

void
employee::setDepartment(string dept) {
	Department = dept;
}
float
employee::getHours(){
    return hours;
}
void
employee::setHours(float hrs){
    hours=hrs;
}
float
employee::getSalary() {
	return Salary;
}

void
employee::setSalary(float sal) {
	Salary = sal;
}
