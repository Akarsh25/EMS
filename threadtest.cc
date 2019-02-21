#include "kernel.h"
#include "main.h"
#include "thread.h"
#include <iostream>
#include <fstream>
#include "list.h"
#include "employee.h"
#include <stdlib.h>
#include <sstream>
#include <cstdlib>
#include <string>

using namespace std;

//method to sort the employee list according to department and position
int
compare(employee* emp1, employee* emp2) {
	if (emp1->getDepartment() < emp2->getDepartment()) {
		return -1;
	}
	else if (emp1->getDepartment() == emp2->getDepartment()) {
		if (emp1->getPosition() < emp2->getPosition()) {
			return -1;
		}
		else if (emp1->getPosition() == emp2->getPosition()) {
			return 0;
		}
		else {
			return 1;
		}
	}
	else {
		return 1;
	}
}

//method to sort paylist according to salary
int 
salcompare(employee* emp1,employee* emp2){
    if((emp1->getHours()*emp1->getSalary()) > (emp2->getHours()*emp2->getSalary())){
        return -1;
    }
    else if ((emp1->getHours()*emp1->getSalary()) == (emp2->getHours()*emp2->getSalary())){
        return 1;
    }
    else{
        return 0;
    }
    
}
SortedList<employee*>empList(compare);
SortedList<employee*>payList(salcompare);
int empID = 8001;

//method to retrieve information from file and assigning it to the list
void
File_Retrieve(string filename){
    ifstream ifile(filename.c_str());
    printf("Retrieving records from file, the records in file are:\n");
    printf("=====ID,Name,Department,Position,Hours,Pay=====\n");
    while(ifile.good()){
        
        string line;
        string ID;
        string name;
        string dept;
        string pos;
        string hours;
        string pay;
        getline(ifile,ID,',');
        getline(ifile,name,',');
        getline(ifile,dept,',');
        getline(ifile,pos,',');
        getline(ifile,hours,',');
        getline(ifile,pay,'\n');
        if(ID == ""){
            break;
        }
        int ID_int=atoi(ID.c_str());
        if (ID_int>empID){
            empID=ID_int;
        }
        float hours_float=atof(hours.c_str());
        float pay_float=atof(pay.c_str());
        employee* emp=new employee();
        emp->setUniqueID(ID_int);
        emp->setName(name);
        emp->setDepartment(dept);
        emp->setPosition(pos);
        emp->setHours(hours_float);
        emp->setSalary(pay_float);
        empList.Insert(emp);
        printf("%d",emp->getUniqueID());
        cout<<", "+emp->getName()+","+emp->getDepartment()+", "+ emp->getPosition()+", ";
        printf("%.2f, %.2f \n",emp->getHours(),emp->getSalary());


    }
    //assigning a unique ID to a new employee to be created.
    if (empID>=8001){
    empID+=1;
}


}

//method to insert new employee details
void
NewRecord(){
    
    string name;
    string dept;
    string pos;
    float pay;
    cout<<"Enter name of the employee\n";
    cin>>name;
    cout<<"Enter department of the employee\n";
    cin>>dept;
    cout<<"Enter position of the  employee\n";
    cin>>pos;
    cout<<"Enter payrate of the employee\n";
    cin>>pay;
    employee *emp=new employee();
    emp->setUniqueID(empID);
    emp->setName(name);
    emp->setDepartment(dept);
    emp->setPosition(pos);
    emp->setHours(0.0);
    emp->setSalary(pay);
    empList.Insert(emp);	
    printf("Created employee: %d",emp->getUniqueID());
    cout<<", "+ emp->getName()+","+emp->getDepartment()+", "+ emp->getPosition()+", ";
    printf("%.2f, %.2f",emp->getHours(),emp->getSalary());
	empID += 1;
}

//method to display employee records
void
display(){
    ListIterator<employee*> rec(&empList);
    while (!rec.IsDone()) {
		employee* emp = rec.Item();
        printf("%d",emp->getUniqueID());
        cout<<", "+emp->getName()+","+emp->getDepartment()+", "+ emp->getPosition()+", ";
        printf("%.2f, %.2f",emp->getHours(),emp->getSalary());
        printf("\n");
		rec.Next();
	}

}

//method to search details of employee based on ID and Department
void
search_emp(){
    int option;
    int ID;
    string dept;
    bool flag=false;
    ListIterator<employee*> rec(&empList);
    printf("Employee search by : 1.ID  2.Deparment\n");
    printf("Choose option 1 or 2: ");
    cin>>option;
    if(option==1){
        printf("Enter the employee ID you want to search for: \n ");
        cin>>ID;
        while(!rec.IsDone()){
            if (rec.Item()->getUniqueID()==ID){
                employee* emp=rec.Item();
                printf("Employee details of searched ID:%d\n",ID);
                printf("%d",emp->getUniqueID());
                cout<<", "+emp->getName()+","+emp->getDepartment()+", "+ emp->getPosition()+", ";
                printf("%.2f, %.2f",emp->getHours(),emp->getSalary());
                printf("\n");
                flag=true;
                break;
            }
            rec.Next();
        }
        if(flag==false){
            printf("\n!!!!!Employee Not Found!!!!!\n");
        }
    }
    else if(option==2){
        printf("Enter the department to search for: \n");
        cin>>dept;
        printf("Employee details of searched department: \n");
        while(!rec.IsDone()){
            if (rec.Item()->getDepartment()==dept){
                employee* emp=rec.Item();
                
                printf("%d",emp->getUniqueID());
                cout<<", "+emp->getName()+","+emp->getDepartment()+", "+ emp->getPosition()+", ";
                printf("%.2f, %.2f",emp->getHours(),emp->getSalary());
                printf("\n");
                flag=true;  
            }
            rec.Next();
        }
        if (flag==false){
            printf("\n!!!!Entered department not found!!!!!\n");
        }


    }

}

//method to update a employee info based on given ID
void 
update(){
    ListIterator<employee*> rec(&empList);
    int ID;
    string name;
    string dept;
    string pos;
    float hrs;
    float pay;
    bool flag=false;
    printf("Enter ID of the employee to be updated:");
    cin>>ID;
    while(!rec.IsDone()){
        if(rec.Item()->getUniqueID()==ID){
            employee* emp=rec.Item();
            printf("Record to be updated is:\n");
            printf("%d",emp->getUniqueID());
            cout<<", "+emp->getName()+","+emp->getDepartment()+", "+ emp->getPosition()+", ";
            printf("%.2f, %.2f",emp->getHours(),emp->getSalary());
            printf("\nUpdate the following fields:\n");
            printf("Name: ");
            cin>>name;
            printf("Department: ");
            cin>>dept;
            printf("Position: ");
            cin>>pos;
            printf("Hours: ");
            cin>>hrs;
            printf("Pay per hour: ");
            cin>>pay;
            emp->setName(name);
            emp->setDepartment(dept);
            emp->setPosition(pos);
            emp->setHours(hrs);
            emp->setSalary(pay);
            printf("Record updated!\n");
            flag=true;
            break;
        }
        rec.Next();
    }
    if (flag==false){
        printf("There is no record with ID: %d\n",ID);
    }
}

//method to schedule a random number of hours worked to each employee
void
schedule(employee* emp){
    float hours=rand()%21 + 20;
    emp->setHours(hours);
}

//method to delete an employee record
void 
Delete(){
    ListIterator<employee*> rec(&empList);
    int ID;
    string choice;
    bool flag=false;
    printf("Enter Employee ID for which the record has to be deleted:");
    cin>>ID;
    while(!rec.IsDone()){
        if(rec.Item()->getUniqueID()==ID){
            employee* emp=rec.Item();
            printf("Record to be deleted is: ");
            printf("%d",emp->getUniqueID());
            cout<<", "+emp->getName()+","+emp->getDepartment()+", "+ emp->getPosition()+", ";
            printf("%.2f, %.2f",emp->getHours(),emp->getSalary());
            printf("\n");
            printf("Do you want to delete the above record?(Y/N) \n");
            cin>>choice;
            if (choice=="Y"){
                empList.Remove(emp);
                printf("Record deleted!!");
            }
            else if(choice=="N"){
                printf("Record with ID %d was asked not be deleted\n",ID);
            }
            else{
                printf("Enter Y or N");
            }
            flag=true;
            break;
            }
        rec.Next();
        }
    if (flag==false){
        printf("ID:%d not in the records",ID);
    }
        


    }

//method to create paylist according to salary
void 
createPayList(){
    ListIterator<employee*> rec(&empList);
    while(!rec.IsDone()){
        payList.Insert(rec.Item());
        rec.Next();
    }
}


//method printing salary and details of employee
void
printPaycheck(){

    ListIterator<employee*> rec1(&payList);
    int order=1;
    while(!rec1.IsDone()){
        printf("Order No: %d\n",order);
        printf("Employee ID :%d\n",rec1.Item()->getUniqueID());
        cout<<"Name: "+rec1.Item()->getName() + "\n";
        printf("Number of hours worked: %.2f\n",rec1.Item()->getHours());
        printf("PayCheck: %.2f\n",rec1.Item()->getHours()*rec1.Item()->getSalary());
        printf("\n\n");
        rec1.Next();
        order+=1;

    }
}

//method to write back all the employee records to the file
void
WriteToFile(string filename){
    int ID;
    string name;
    string dept;
    string pos;
    float hours;
    float pay;
    stringstream str1;
    fstream file_write;
    file_write.open(filename.c_str());
    ListIterator<employee*> rec(&empList);
    while(!rec.IsDone()){
        ID=rec.Item()->getUniqueID();
        name=rec.Item()->getName();
        dept=rec.Item()->getDepartment();
        pos=rec.Item()->getPosition();
        hours=rec.Item()->getHours();
        pay=rec.Item()->getSalary();
        str1.str("");
        str1<<ID;
        string IDs=str1.str();
        str1.str("");
        str1<<hours;
        string hoursS=str1.str();
        str1.str("");
        str1<<pay;
        string payS=str1.str();
        file_write<<IDs+","+name+","+dept+","+pos+","+hoursS+","+payS+"\n";
        rec.Next();
    }
    file_write.close();
}
void
EMS()
{   
    File_Retrieve("../threads/employee.dat");
    char option;
    for(;option!='7';){
        cout<<"\n*******Menu********";
        cout<<endl<<"Enter your option";
        cout<<endl<<"1 => Enter new record";
        cout<<endl<<"2 => Display all employees";
        cout<<endl<<"3 => Search Employee";
        cout<<endl<<"4 => Update Employee Info";
        cout<<endl<<"5 => Delete Employee Info";
        cout<<endl<<"6 => Schedule Weekly jobs";
        cout<<endl<<"7 => Exit"<<endl;
        cout<<"********************"<<endl;
        cin>>option;
        switch(option){
            case '1':
                NewRecord();
                break;
            case '2':
                printf("Displaying employee records in the format:\n");
                printf("=====ID,Name,Department,Position,Hours,Pay=====\n");
                display();
                break;
            case '3':
                search_emp();
                break;
            case '4':
                update();
                break;
            case '5':
                Delete();
                break;
            case '6':
                empList.Apply(schedule);
                createPayList();
                printPaycheck();
                break;
            case '7':
                WriteToFile("../threads/employee.dat");
                printf("Thank you for using EMS Application");
                break;
                
            
            default:printf("Enter valid choice!!\n");
        
           

               
        }
    // int num;
    
    // for (num = 0; num < 5; num++) {
    //     printf("*** thread %d looped %d times\n", which, num);
    //     kernel->currentThread->Yield();
    // }
    }
}
void
ThreadTest()
{  

    Thread *t = new Thread("forked thread");
    t->Fork((VoidFunctionPtr) EMS, (void *) 1);
    
    // SimpleThread(0);
}
