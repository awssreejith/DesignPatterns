/*
This implements singleton patterns. The idea is to ensure that only one instance of this class
is existing during at any given point of time within the process's address space.To do so we do

0) Make all constructors (default as well) overloaded assignment operators as private
1) Make destructor private (mostly singletons will persist till end of program)
2) provide a static variable which can be a self referential pointer to store a single instance
3) provide a static method to retrive the singleton whenever necessary
4) Make the access thread safe.

Note:we privatize assignment operator since anybody can malloc the class without calling constructor and
dereference it and replicate the copy.

Typical example of this pattern will be configuration classes or service layer which acts as a shield between
presentation layers and domain model. Another example can be data access layer. For all of these classes only one instance should be present. 
For example for a service layer, it should be responsible for session management, authentication services transaction process
and there should be only one instance of this layer which should cater for all transaction.
*/

#include <iostream>
using namespace std; //never use plain using statement. Using at this moment

//This is a stub function which act as a thread lock
void threadLock()
{
	cout<<"\n"<<"\t"<<"Lock acquired"<<"\n";
}

//This is a stub function which act as a thread unlock
void threadunLock()
{
	cout<<"\n"<<"\t"<<"Lock released"<<"\n";
}

class ServiceLayer //Singleton class
{
	
	public:
		static ServiceLayer* getInstance()
		{
			if (me == NULL)
			{
				//critical section starts here. Lock here one thread
				threadLock();
				if(me == NULL)
				{
					//do all creations and initializations
					me = new ServiceLayer();
				}
				threadunLock(); //CS end here
				
			}
		}
		
		void doSomeWork()
		{
			//do some work
		}
	private:
		//all defaults go here
		ServiceLayer() = default; //def const
		ServiceLayer(const ServiceLayer& ) = default; //def copy constr
		ServiceLayer(ServiceLayer&& ) = default; //def move constr
		ServiceLayer& operator=(const ServiceLayer&) = default; //def assignment operator
		ServiceLayer& operator=(ServiceLayer&&) = default; //def assignment operator
		~ServiceLayer() = default;
		
		//the self referential pointer
		static ServiceLayer* me;
	
};

//Initialize the static pointer to NULL.
ServiceLayer* ServiceLayer::me = NULL;

//main stub
int main()
{
	ServiceLayer* svcLyr = ServiceLayer::getInstance();
	svcLyr->doSomeWork();
	for(int i = 0;i<100;++i)
	{
		svcLyr = ServiceLayer::getInstance();
		cout<<"\n"<<"\t"<<svcLyr<<"\n";  //should return same address
	}
}
