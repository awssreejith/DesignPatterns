/*
This is an implementation of simple factory pattern. The fatory pattern itself has 3 varieties viz Factory pattern(AKA Simple factory),
Factory method and Abstract factory.
This pattern is used when the final object to be created is simple and doesn't include much creational complexities.
Here the client request the factory for a specific type of object by passing any argument which defines that type
and the factory will create the concrete type casted to the base type and return the final object.
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
Now our factory class which gonna build one among these rifles when client ask to do so.
Note that for a simple factory pattern (or "Factory Pattern"), the factory class won't be having
any interface or parent. It is just a simple class which simply takes the request and return one of the
rifle type.
*/

//We define an enum for the client to pass with the creation request to the factory
enum class RifleType
{
	MANUAL=1,
	SEMIAUTOMATIC,
	FULLYAUTOMATIC	
};

class RifleFactory
{
	public:
		//Anyhow it doesn't make sense to pass specifications for a rifles by client.But for the time being
		//passing specifications by client and we set default values as well.
		Rifle* makeRifle(RifleType rifleType,int range=50, int totalbullets=13, float bulletCaliber=.50)
		{
			Rifle* rifle = NULL;
			switch (rifleType)
			{
				case RifleType::MANUAL :
					rifle= new ManualLoadRifle(range, totalbullets, bulletCaliber);
					rifle->setBoltAction();
					rifle->setrifleType();
					break;
					
				case RifleType::SEMIAUTOMATIC :
					rifle= new SemiAutomaticRifle(range, totalbullets, bulletCaliber);
					rifle->setBoltAction();
					rifle->setrifleType();
					break;
					
				case RifleType::FULLYAUTOMATIC :
					rifle= new FullyAutomaticRifle(range, totalbullets, bulletCaliber);
					rifle->setBoltAction();
					rifle->setrifleType();
					break;
					
				default:
					cout<<"\n"<<"\t"<<"Wrong Choice"<<"\n";
					break;
			}
			return rifle;
		}
};

int main()
{
	//client code. 1st make a factory object
	RifleFactory rFactory;
	/*
	---
	---do some work
	---
	*/
	//we need a semi automatic here
	Rifle* semi = rFactory.makeRifle(RifleType::SEMIAUTOMATIC,150,37,.9);
	cout<<"\n"<<"\t"<<semi->getBullPupMode()<<"\n";
	cout<<"\n"<<"\t"<<semi->getrifleType()<<"\n";
	//use here and if required delete it.
	if (semi)
	{
		delete semi;
		semi = NULL;
	}
	
	//we need a Fully automatic at this point;
    semi = rFactory.makeRifle(RifleType::FULLYAUTOMATIC,250,48,.75);
	cout<<"\n"<<"\t"<<semi->getBullPupMode()<<"\n";
	cout<<"\n"<<"\t"<<semi->getrifleType()<<"\n";
	//use here and if required delete it.
	if (semi)
	{
		delete semi;
		semi = NULL;
	}
	
	//end of world. lets fight with stick and bows;
    semi = rFactory.makeRifle(RifleType::MANUAL,100,10,.45);
	cout<<"\n"<<"\t"<<semi->getBullPupMode()<<"\n";
	cout<<"\n"<<"\t"<<semi->getrifleType()<<"\n";
	//use here and if required delete it.
	if (semi)
	{
		delete semi;
		semi = NULL;
	}
	
	//One final with all defaults;
    semi = rFactory.makeRifle(RifleType::MANUAL);
	cout<<"\n"<<"\t"<<semi->getBullPupMode()<<"\n";
	cout<<"\n"<<"\t"<<semi->getrifleType()<<"\n";
	//use here and if required delete it.
	if (semi)
	{
		delete semi;
		semi = NULL;
	}
}
