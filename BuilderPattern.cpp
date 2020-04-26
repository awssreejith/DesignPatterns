/*
Builder pattern will abstract the complex building procedure of an object out of client in to concrete implementators.
An abstract builder will define the set of building steps while the concrete children class will implement the actual
building logic. The main difference between abstract factory and builder is that Abstract factory builds a set of 
related objects and it's the client who is going to construct the final product out of these built components.But in builder pattern
client will contact a director who will receive the final product type to be built and delegate the appropriate builder worker object
to build that final product type.Once built, the director will handover the final product to the client. Thus the client needen't worry about the
complex building steps and will only receive the final built product.

Use Case: Client requires different type of jet aircrafts to be delivered for their airforce.There are mainly three types of jet aircrafts
he is interested in. They are Fighter Jet, Bomber Jet and Transport Jet. Each aircraft type has it's own engine variant, landing gear variant,
wing type etc.

Solution: All the aircraft will be of a common type. There will be an abstract builder who will have set of functions to build the
final product. The concrete subclasses will implement these functions. The request will be received by a builder director and will delegate
one of these concrete builder worker classes to build the final object and hand it over to client.

*/

#include <iostream>
#include <string>
using namespace std; //Never use this

//Aircraft type 
enum class AircraftType
{
	FIGHTER=1,
	BOMBER,
	TRANSPORT
};

//Base for all aircraft type

class JetAircraft
{
	public:
		virtual void setType(const string& ) = 0;
		virtual void setEngine(const string& ) = 0;
		virtual void setLandingGear(const string& ) = 0;
		virtual void setWings(const string& ) = 0;

		string getType(){return this->m_type;}
		string getEngine() {return this->m_engine;}
		string getLandingGear() {return this->m_landingGear;}
		string getWings() {return this->m_wings;}
		virtual ~JetAircraft() = default;
				
		protected:
			string m_type;
			string m_engine;
			string m_landingGear;
			string m_wings;
			
};

class FighterJet : public JetAircraft
{
	public:
		void setType(const string& type )
		{
			cout<<"\n"<<"Setting type for fighter aircraft"<<"\n";
			m_type = type;
		}
		
		void setEngine(const string& engine)
		{
			cout<<"\n"<<"Setting engine for fighter aircraft"<<"\n";
			m_engine = engine;
		}
		
		void setLandingGear(const string& lgear)
		{		
			cout<<"\n"<<"Setting Landing gear for fighter aircraft"<<"\n";
			m_landingGear = lgear;
		}
		
		void setWings(const string& wings)
		{
			cout<<"\n"<<"Setting wings for fighter aircraft"<<"\n";
			m_wings = wings;
		}
			
};


class BomberJet : public JetAircraft
{
	public:
		void setType(const string& type )
		{
			cout<<"\n"<<"Setting type for bomber aircraft"<<"\n";
			m_type = type;
		}
		
		void setEngine(const string& engine)
		{
			cout<<"\n"<<"Setting engine for bomber aircraft"<<"\n";
			m_engine = engine;
		}
		
		void setLandingGear(const string& lgear)
		{		
			cout<<"\n"<<"Setting Landing gear for bomber aircraft"<<"\n";
			m_landingGear = lgear;
		}
		
		void setWings(const string& wings)
		{
			cout<<"\n"<<"Setting wings for bomber aircraft"<<"\n";
			m_wings = wings;
		}			
				
};

class TransportJet : public JetAircraft
{
	public:
		void setType(const string& type )
		{
			cout<<"\n"<<"Setting type for Transporter aircraft"<<"\n";
			m_type = type;
		}
		
		void setEngine(const string& engine)
		{
			cout<<"\n"<<"Setting engine for Transporter aircraft"<<"\n";
			m_engine = engine;
		}
		
		void setLandingGear(const string& lgear)
		{		
			cout<<"\n"<<"Setting Landing gear for Transporter aircraft"<<"\n";
			m_landingGear = lgear;
		}
		
		void setWings(const string& wings)
		{
			cout<<"\n"<<"Setting wings for Transporter aircraft"<<"\n";
			m_wings = wings;
		}			
				
};

//Now our abstract builder class. this has abstract logic
//of how to build an aircraft step by step

class JetAircraftBuilder

{
	public:
		//the real builder function which knows what to build and how to build
		virtual JetAircraft* manufactureAircraft() = 0;
		virtual ~JetAircraftBuilder() = default;
		
};

class JetFighterBuilder : public JetAircraftBuilder
{
	public:
		virtual JetAircraft* manufactureAircraft()
		{
			//we can even use an abstract factory to delegate the creation.
			JetAircraft* aircraft = new FighterJet();
			aircraft->setType("Fighter interceptor");
			aircraft->setEngine("Pratt and Whitney Turbojet");
			aircraft->setLandingGear("Safran Fighter Jet Landing system");
			aircraft->setWings("Lockheed Martin Swept wings");
			return aircraft;
		}
};




class BomberAircraftBuilder : public JetAircraftBuilder
{
	public:
		virtual JetAircraft* manufactureAircraft()
		{
			//we can even use an abstract factory to delegate the creation.
			JetAircraft* aircraft = new BomberJet();
			aircraft->setType("Intercontinental Bomber");
			aircraft->setEngine("Rolls Royce Turbofan");
			aircraft->setLandingGear("Safran heavy landing system");
			aircraft->setWings("Boeing Fixed wings");
			return aircraft;
		}	
};

class TransportAircraftBuilder : public JetAircraftBuilder
{
	public:
		virtual JetAircraft* manufactureAircraft()
		{
			//we can even use an abstract factory to delegate the creation.
			JetAircraft* aircraft = new TransportJet();
			aircraft->setType("Heavy Transporter");
			aircraft->setEngine("GE 9X Turbofan");
			aircraft->setLandingGear("Raytheon Landing gear system");
			aircraft->setWings("BAE Fixed wings");
			return aircraft;
		}	
};

//Directory which will take the order and delivers the final product
class Director
{
	JetAircraftBuilder* fighterBuilder;
	JetAircraftBuilder* bomberBuilder;
	JetAircraftBuilder* transportBuilder;
	
	public:
		Director()
		{
			fighterBuilder = new JetFighterBuilder();
			bomberBuilder = new BomberAircraftBuilder();
			transportBuilder = new TransportAircraftBuilder();
		}
		
		JetAircraft* deliverAnAircraft(AircraftType aType)
		{
			switch(aType)
			{
				case AircraftType::FIGHTER:
					return (fighterBuilder->manufactureAircraft());
					break;
					
				case AircraftType::BOMBER:
					return (bomberBuilder->manufactureAircraft());
					break;
					
				case AircraftType::TRANSPORT:
					return (transportBuilder->manufactureAircraft());
					break;
			}
		}
};


//Client code

int main()
{
	//create the director upfront
	Director director;
	
	//need a bomber here
	JetAircraft* aircraft = director.deliverAnAircraft(AircraftType::BOMBER);
	cout<<"\n"<<aircraft->getType()<<"\n";
	cout<<"\n"<<aircraft->getEngine()<<"\n";
	cout<<"\n"<<aircraft->getLandingGear()<<"\n";
	cout<<"\n"<<aircraft->getWings()<<"\n";
	
	//destroy the aircraft once done.
	delete aircraft;
	
	//need a figther here;
	aircraft = director.deliverAnAircraft(AircraftType::FIGHTER);
	cout<<"\n"<<aircraft->getType()<<"\n";
	cout<<"\n"<<aircraft->getEngine()<<"\n";
	cout<<"\n"<<aircraft->getLandingGear()<<"\n";
	cout<<"\n"<<aircraft->getWings()<<"\n";
	
	//destroy the aircraft once done.
	delete aircraft;
	
	//need a transporter here;
	aircraft = director.deliverAnAircraft(AircraftType::TRANSPORT);
	cout<<"\n"<<aircraft->getType()<<"\n";
	cout<<"\n"<<aircraft->getEngine()<<"\n";
	cout<<"\n"<<aircraft->getLandingGear()<<"\n";
	cout<<"\n"<<aircraft->getWings()<<"\n";
	
	//destroy the aircraft once done.
	delete aircraft;
}



