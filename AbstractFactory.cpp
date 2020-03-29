/*
The main difference between a Factory Method pattern and an abstract factory is that the factory Method pattern constructs only one type of
product, but abstract factory creates multiple types of related products.Thus the abstract factory class will be having more than one makeProduct() function
which makes different types of products which are related and the final product is configured and sent it back to the client as a single product.

Use case --> The  client requires different types of projectile weapons, but don't know how to manufacture these weapons.The final weapons
comprises of the main weapons and associated parts. We have to devise a solution where the client will ask for the final finished product and
we should be manufacuturing the final product which comprises of the main weapon as well as all the accesories.

For this example we are going to manufacture some thing called projectile weapon. A projectile weapon is a type of weapon which fires and projectile
to a greater distance. Examples of a projectile weapon are rifles, artillery guns and mortars. Every projectile weapon has a main weapon (for example
Rifle has the main Rifle body), a projectile (for example rifle has bullet as projectile) and casing (for example a rifle has catridge as casing for its bullet).

In our example we are going to manufacture three types of projectile weapon viz Rifle, Artillery Gun and Mortar. All three weapons has main weapon, projectile and casing
Note: Casing for a mortar is superficial since mortar is fired as a single piece and exploded as a single unit unlike bullet and tank shell
where the casing remain while the bullet or explosive charge gets fired.For this example lets consider like that.
*/

#include <iostream>
#include <string>
using namespace std; //never use this

//First lets define our weapon components
class MainWeapon
{
	public:
		virtual void setMainWeapon() = 0;
		virtual void kill() = 0;
};

class Projectile
{
	public:
		virtual void setprojectile() = 0;
};

class Casing
{
	public:
		virtual void setCasing() = 0;
};

//Now concerete implemenatations of componenets

class Rifle:public MainWeapon
{
	public:
		void setMainWeapon()
		{
			cout<<"\n"<<"\t"<<"Main weapon is set as Rifle"<<"\n";
		}
		void kill()
		{
			cout<<"\n"<<"\t"<<"Bang..headshot"<<"\n";
		}
};

class ArtilleryGun:public MainWeapon
{
	public:
		void setMainWeapon()
		{
			cout<<"\n"<<"\t"<<"Main weapon is set as Artillery Gun"<<"\n";
		}
		
		void kill()
		{
			cout<<"\n"<<"\t"<<"Boom..Shrapnel explosion"<<"\n";
		}
};

class Mortar:public MainWeapon
{
	public:
		void setMainWeapon()
		{
			cout<<"\n"<<"\t"<<"Main weapon is set as Mortar"<<"\n";
		}
		
				void kill()
		{
			cout<<"\n"<<"\t"<<"Dhooom...macabre explosion"<<"\n";
		}
};

class Bullet:public Projectile
{
	public:
		void setprojectile()
		{
			cout<<"\n"<<"\t"<<"Projectile is set as bullet"<<"\n";
		}
};

class ArtilleryShell:public Projectile
{
	public:
		void setprojectile()
		{
			cout<<"\n"<<"\t"<<"Projectile is set as Artillery Shell"<<"\n";
		}
};

class MortarShell:public Projectile
{
	public:
		void setprojectile()
		{
			cout<<"\n"<<"\t"<<"Projectile is set as Mortar Shell"<<"\n";
		}
};

class Catridge:public Casing
{
	public:
		void setCasing()
		{
			cout<<"\n"<<"\t"<<"Casing is set as catridge"<<"\n";
		}
};

class ShellCase:public Casing
{
	public:
		void setCasing()
		{
			cout<<"\n"<<"\t"<<"Casing is set as Shell case"<<"\n";
		}
};

class MortarCase:public Casing
{
	public:
		void setCasing()
		{
			cout<<"\n"<<"\t"<<"Casing is set as Mortar case"<<"\n";
		}
};

//Now our Factories
class WeaponFactory
{
	public:
	virtual MainWeapon* makeMainWeapon() = 0;
	virtual Projectile* makeProjectile() = 0;
	virtual Casing*     makeCasing()     = 0;
};

class RifleFactory:public WeaponFactory
{
	public:
	MainWeapon* makeMainWeapon()
	{
		return (new Rifle());
	}
	
	Projectile* makeProjectile()
	{
		return (new Bullet());
	}
	
	Casing* makeCasing()
	{
		return (new Catridge());
	}
};

class ArtilleryGunFactory:public WeaponFactory
{
	public:
	MainWeapon* makeMainWeapon()
	{
		return (new ArtilleryGun());
	}
	
	Projectile* makeProjectile()
	{
		return (new ArtilleryShell());
	}
	
	Casing* makeCasing()
	{
		return (new ShellCase());
	}
};


class MortarFactory:public WeaponFactory
{
	public:
	MainWeapon* makeMainWeapon()
	{
		return (new Mortar());
	}
	
	Projectile* makeProjectile()
	{
		return (new MortarShell());
	}
	
	Casing* makeCasing()
	{
		return (new MortarCase());
	}
};

int main()
{
	/*
	---
	---Start doing some work
	---
	Here we require an Artillery gun to kill some intruders in the border
	*/
	WeaponFactory* wFactory = new ArtilleryGunFactory();
	//Now get all the necessary stuffs and fire a shell
	MainWeapon* weapon = wFactory->makeMainWeapon();
	Projectile* projectile = wFactory->makeProjectile();
	Casing* casing = wFactory->makeCasing();
	
	weapon->setMainWeapon();
	projectile->setprojectile();
	casing->setCasing();
	
	weapon->kill();
	
	//delete if you want
	delete wFactory;
	delete weapon;
	delete projectile;
	delete casing;
	
	//get a nice rifle and kill some
	 wFactory = new RifleFactory();
	//Now get all the necessary stuffs and fire a shell
	weapon = wFactory->makeMainWeapon();
	projectile = wFactory->makeProjectile();
	casing = wFactory->makeCasing();
	
	weapon->setMainWeapon();
	projectile->setprojectile();
	casing->setCasing();
	
	weapon->kill();
	
}
