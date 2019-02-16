# EMS
Employee Management System
There is a file, employee.dat, reads all employee records, creates Employee objects and make a list.
After reading employee.dat, shows the following menu repeatedly until menu 7 (Exit) is selected.
1.	Enter new record
2.	Display all employees
3.	Search employee(s)
4.	Update employee info
5.	Delete employee info
6.	Schedule weekly jobs
7.	Exit

First, enter a new record of an employee with his/her unique ID.
If the employee is the first one (there is no existing employee list), his/her ID is starting with 8001.
If not, the new employee’s ID will be assigned to the highest ID of existing ones + 1.
The unique ID is automatically assigned by the system, not user input. Enter all other employee info manually.

Second, displays all employee records to screen. The list is sorted by department and position.

Third, searches employee(s) with either department or ID. 
If department is entered, displays all members of the department. If employee ID is entered, displays the record of the employee.

Fourth, updates employee record with employee ID. All information except ID can be updated.

Fifth, deletes employee record with employee ID. This process needs a confirmation to delete the record of selected employee.

Sixth, schedules weekly jobs. There is a job queue for all employees.
Each employee has a certain amount of task to do, which should take a certain amount of time. The time is randomly generated 20 to 40 hours.
With this time, each employee will receive his/her weekly paycheck (time * hourly pay rate). 

Seventh, exits the program. All record of current employees will be saved to employee.dat before exiting.
