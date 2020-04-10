/*
Protype pattern is best suited when there are multitudes of similar objects to be created and can remove the creational complexities 
by cloning itself. The abstract class will provide clone method which willbe implemented by concrete children classes.
The main hurdle with this pattern is that the copy constructor should implement deep copy since any memory created in heap should be exclusive

Use case: A large scale financial enterprise which has thousands of employees under their payroll is migrating to an automated payroll and HR management system.
To include all the employees, all the employees are generally categorized under three category. They are Upper Management, Middle Management and lower Management.
Every employee will fall under one among the three categories. Since it is costly to instantiate all the thousands of employees from scratch, one instance
of each category will be created under each concrete class and will clone the required category object whenever the client requires an object.

The main difference between a factory pattern and protype pattern is that in factory pattern the new operator is called by the concrete factory children
but in prototype, th new operator is called by the final product class itself.

The main danger with prototype pattern is shallow copy. Since we return a copy of the existing object, if that original object has some
pointer meber variable, we should do deep copy and remove the pointer copying.

*/

#include <iostream>
#include <string.h>
using namespace std;
class Employee
{
	protected:
		//simulate a pointer member dependency
		char* employeeName;

	public:
		
		char* getName()
		{
			return employeeName;
		}
		
		virtual void setName(const char* name) = 0;
		
		//Our clone method
		virtual Employee* clone() = 0;
		virtual ~Employee()
		{
			delete [] employeeName;
		}
};

class UpperManagementEmployee:public Employee
{
	public:
		UpperManagementEmployee() = default;
		UpperManagementEmployee(const UpperManagementEmployee& rhs)
		{
			employeeName = NULL;
		}
		Employee* clone()
		{
			Employee* ptr = new  UpperManagementEmployee(*this); //this calls the copy constructor

		}
		
		void setName(const char* name)
		{
			cout<<"\n"<<"Setting name for Upper management guy"<<"\n";
			this->employeeName = new char[strlen(name)+1];
			strcpy(this->employeeName, name);
		}
};

class MiddleManagementEmployee:public Employee
{
	public:
		MiddleManagementEmployee()=default;
		MiddleManagementEmployee(const MiddleManagementEmployee& rhs)
		{
			employeeName = NULL;
		}
		Employee* clone()
		{
			Employee* ptr = new MiddleManagementEmployee(*this); //this calls the copy constructor
		}
		
		void setName(const char* name)
		{
			cout<<"\n"<<"Setting name for mid management guy"<<"\n";
			this->employeeName = new char[strlen(name)+1];
			strcpy(this->employeeName, name);
		}
};

class LowerManagementEmployee:public Employee
{
	public:
		LowerManagementEmployee() = default;
		LowerManagementEmployee(const LowerManagementEmployee& rhs)
		{
			employeeName = NULL;
		}
		Employee* clone()
		{
			
			Employee* ptr = new LowerManagementEmployee(*this); //this calls the copy constructor
			//now set the values for the cloned guy		
		}
		
		void setName(const char* name)
		{
			cout<<"\n"<<"Setting name for lower management guy"<<"\n";
			this->employeeName = new char[strlen(name)+1];
			strcpy(this->employeeName, name);
		}
};

//Now our abstract class

class EmployeeCloner
{

	public:
		virtual Employee* cloneEmployee() = 0;
		virtual ~EmployeeCloner() = default;
};


class UpperMgmtCloner: public EmployeeCloner
{

    private:
    	static Employee* employee;
	public:
		
		Employee* cloneEmployee()
		{
			if (!employee)
			{
				employee = new UpperManagementEmployee();
			}
			return (employee->clone());
		}
		
};

Employee* UpperMgmtCloner::employee = NULL;

class MidMgmtCloner: public EmployeeCloner
{
    private:
    	static Employee* employee;
	public:

		Employee* cloneEmployee()
		{
			if (!employee)
			{
				employee = new MiddleManagementEmployee();
			}
			return (employee->clone());
		}
		
};
Employee* MidMgmtCloner::employee = NULL;

class LowMgmtCloner: public EmployeeCloner
{
    private:
    	static Employee* employee;
	public:

		Employee* cloneEmployee()
		{
			if (!employee)
			{
				employee = new LowerManagementEmployee();
			}
			return (employee->clone());
		}
		
};
Employee* LowMgmtCloner::employee = NULL;

int main()
{
	EmployeeCloner* upperMgmt = new UpperMgmtCloner();
	EmployeeCloner* midMgmt   = new MidMgmtCloner();
	EmployeeCloner* lowMgmt   = new LowMgmtCloner();
	
	//create a CEO,CFO and a COO from a single clonable stub;
	Employee* ceo = upperMgmt->cloneEmployee();
	ceo->setName("I_AM_THE_CEO");
	
	Employee* cto = upperMgmt->cloneEmployee();
	cto->setName("I_AM_THE_CTO");
	
	Employee* coo = upperMgmt->cloneEmployee();
	coo->setName("I_AM_THE_COO");
	
	//create two engineers
	Employee* engr1 = lowMgmt->cloneEmployee();
	engr1->setName("I_AM_ENGINER_1");
	
	Employee* engr2 = lowMgmt->cloneEmployee();
	engr2->setName("I_AM_ENGINER_2");
	
	
	//create one lead
	Employee* lead = midMgmt->cloneEmployee();
	lead->setName("I_AM_LEAD");
	
	//Though cloned from common stub object, each employee will
	//still have his own memory for the name 
	
	cout<<"\n"<<ceo->getName();
	cout<<"\n"<<coo->getName();	
	cout<<"\n"<<cto->getName();	
	cout<<"\n"<<engr1->getName();	
	cout<<"\n"<<engr2->getName();
	cout<<"\n"<<lead->getName();
	cout<<"\n";			
	
}
