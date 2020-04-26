/*
This is a re-implementation of Simple Factory using Factory method pattern.Here unlike the single factory class which doesn't have any interface or parent
in the Factory pattern we will have an abstract factory class with a method which will return the desired product type. But the actual
implemenation of this method should be within the concrete children classes derived from this abstract factory class.
Note: This type of pattern is best suited if the creational complexity of the object is higher when compared to simple factory pattern.Moreover
it is best suited when the client knows what concrete implementation it has to use but dont know how to create the final product.
Here we can derive different children from the abstract factory which gonna give different specialized product.
*/

/*
Use case -> The client requires different types of rifles during run time. But client doesn't know how to create those.There are three
types of rifles. Manual load, Semi Automatic and fully automatic rifles. Each rifle has its own complexities but have common functionalities
and attributes like range, total bullets(rounds), bullet caliber and effective kill range
Note: This is a superficial example since semi automatic can be fired in fully automaic mode also nowadays. but for time being
just pretend that such functionality isn't available.
*/

#include <iostream>
#include <string>

using namespace std; //never use this. 

//Abstract type. This will be the final product type
class Rifle
{
	public:
		Rifle(		int    prange,
					int    ptotalBullets,
					float  pbulletCaliber
					):range(prange),totalBullets(ptotalBullets),bulletCaliber(pbulletCaliber){}
		
		virtual void setBoltAction() = 0; //this should be set by concrete class
		virtual void setrifleType() = 0; //this should be set by concrete class
		virtual const string getBoltAction() = 0; //this should be set by concrete class
		virtual const string getrifleType() = 0; //this should be set by concrete class
		virtual const string getBullPupMode() = 0; //This is only applicable for semi automatic or fully automatic rifles
		~Rifle() = default;
		void getSpecs(string& irifleType,string& iboltAction,int& itotalBullets,int& ibulletCaliber,int& iRange)
		{
			irifleType = rifleType; iboltAction = boltAction; itotalBullets = totalBullets; ibulletCaliber = bulletCaliber;
			iRange = range;
		}
	protected:
		string boltAction; //this defines whether a rifle is auto or not
		string rifleType; //can be an enum also
	private:
		
		int    range;
		int    totalBullets;
		float  bulletCaliber;
};

//Concrete class-1: Non automatic manual load rifle
class ManualLoadRifle : public Rifle
{
	public:
		~ManualLoadRifle() = default;
		ManualLoadRifle(int prange,int ptotalBullets, float pbulletCaliber):Rifle(prange,ptotalBullets,pbulletCaliber){}
	
	    void setBoltAction()
		{
			boltAction = "Manual cocking and Release Bolt type";
		}
		
		void setrifleType()
		{
			rifleType = "Fully Manual loading/unloading rifle type";
		}
		
		const string getBullPupMode()	
		{
			return ("No bullPup fixed butt rifle");
		}
		
		const string getBoltAction() 
		{
			return boltAction;
		}
		
		const string getrifleType()
		{
			return rifleType;
		}
		
};


//Concrete class-2: Semi automatic rifle
class SemiAutomaticRifle : public Rifle
{
	~SemiAutomaticRifle() = default;
	public:
		SemiAutomaticRifle(int prange,int ptotalBullets, float pbulletCaliber):Rifle(prange,ptotalBullets,pbulletCaliber){}
	
	    void setBoltAction()
		{
			boltAction = "Manual cocking and Automatic Release Bolt type";
		}
		
		void setrifleType()
		{
			rifleType = "Semi Manual loading/unloading rifle type";
		}
		
		const string getBullPupMode()	
		{
			return ("No bullPup foldable butt rifle");
		}
		
		const string getBoltAction() 
		{
			return boltAction;
		}
		
		const string getrifleType()
		{
			return rifleType;
		}
		
};

//Concrete class-2: Semi automatic rifle
class FullyAutomaticRifle : public Rifle
{
	~FullyAutomaticRifle() = default;
	public:
		FullyAutomaticRifle(int prange,int ptotalBullets, float pbulletCaliber):Rifle(prange,ptotalBullets,pbulletCaliber){}
	
	    void setBoltAction()
		{
			boltAction = "Auto cocking and Automatic Release Bolt type";
		}
		
		void setrifleType()
		{
			rifleType = "Fully auto loading/unloading rifle type";
		}
		
		const string getBullPupMode()	
		{
			return ("BullPup foldable butt rifle");
		}
		
		const string getBoltAction() 
		{
			return boltAction;
		}
		
		const string getrifleType()
		{
			return rifleType;
		}
		
};

/*
Unlike the Factory pattern, here we will have an abstract class with a method which gonna return the concrete
rifle. But what rifle it gonna return will be implemented by the children of this class
*/

/*
Unlike the Factory pattern we don't need an enum for rifle type because client knows what concrete factory
it have to use during run time to get a particular rifle class. But client don't know how to manufature those rifle and
its the duty of concrete children to manufacture that rifle category on behalf of client
*/

class IRifleFactory
{
	public:
		
		//This is our factory method. This function will be implemented by all the children		
		virtual Rifle* makeRifle(int range=50, int totalbullets=13, float bulletCaliber=.50) = 0;
};

//Concrete factory class for manual rifle
class ManualRifleFactory : public IRifleFactory
{
	public:
		Rifle* makeRifle(int range=50, int totalbullets=13, float bulletCaliber=.50)
		{
			Rifle* rifle = new ManualLoadRifle(range,totalbullets,bulletCaliber);
			rifle->setBoltAction();
			rifle->setrifleType();
			return rifle;
		}
};

//Concrete factory class for semi automatic rifle
class SemiAutomaticRifleFactory : public IRifleFactory
{
	public:
		Rifle* makeRifle(int range=50, int totalbullets=13, float bulletCaliber=.50)
		{
			Rifle* rifle = new SemiAutomaticRifle(range,totalbullets,bulletCaliber);
			rifle->setBoltAction();
			rifle->setrifleType();
			return rifle;
		}
};

//Concrete factory class for semi automatic rifle
class FullyAutomaticRifleFactory : public IRifleFactory
{
	public:
		Rifle* makeRifle(int range=50, int totalbullets=13, float bulletCaliber=.50)
		{
			Rifle* rifle = new FullyAutomaticRifle(range,totalbullets,bulletCaliber);
			rifle->setBoltAction();
			rifle->setrifleType();
			return rifle;
		}
};

int main()
{
	//client code knows what are all concrete rifle factories to use
	IRifleFactory* pManualRifleFactory    = new ManualRifleFactory();
	IRifleFactory* pSemiAutoRifleFactory  = new SemiAutomaticRifleFactory();
	IRifleFactory* pFullyAutoRifleFactory = new FullyAutomaticRifleFactory();
	Rifle* 		  rifle				      = NULL;
	/*
	---
	---do some work
	---
	*/
	//we need a semi automatic here
	rifle = pSemiAutoRifleFactory->makeRifle(150,37,.9);
	cout<<"\n"<<"\t"<<rifle->getBullPupMode()<<"\n";
	cout<<"\n"<<"\t"<<rifle->getrifleType()<<"\n";
	//use here and if required delete it.
	if (rifle)
	{
		delete rifle;
		rifle = NULL;
	}
	
	//we need a Fully automatic at this point;
    rifle = pFullyAutoRifleFactory->makeRifle(250,48,.75);
	cout<<"\n"<<"\t"<<rifle->getBullPupMode()<<"\n";
	cout<<"\n"<<"\t"<<rifle->getrifleType()<<"\n";
	//use here and if required delete it.
	if (rifle)
	{
		delete rifle;
		rifle = NULL;
	}
	
	//end of world. lets fight with stick and bows;
    rifle = pManualRifleFactory->makeRifle(100,10,.45);
	cout<<"\n"<<"\t"<<rifle->getBullPupMode()<<"\n";
	cout<<"\n"<<"\t"<<rifle->getrifleType()<<"\n";
	//use here and if required delete it.
	if (rifle)
	{
		delete rifle;
		rifle = NULL;
	}
	
	//One final for manual rifle with all defaults;
    rifle = pManualRifleFactory->makeRifle();
	cout<<"\n"<<"\t"<<rifle->getBullPupMode()<<"\n";
	cout<<"\n"<<"\t"<<rifle->getrifleType()<<"\n";
	//use here and if required delete it.
	if (rifle)
	{
		delete rifle;
		rifle = NULL;
	}
	
	//cleanUp everyting once done with creation
}
