/*
This pattern is best suited if we are trying to couple two heterogenous systems. This can be explianed by a use case

Use Case: Imagine we have an application which uses xml file as medium of data transfer. There is a system which processes a set of
transactions and gives the output as an xml file.Our application will use this xml file to give as input for another system which does
post transaction operations like alerting other systems and commiting in to data store etc.
One day the post processing system had stopped accepting xml file and mandates every client to send data in JSON format. This means that
we are getting the results from Transaction system as xml format but the post processing system requires JSON format. To solve this issue we have to solutions

0) Ask the Transaction processing system to provide the result in JSON format(unlikely)
1) Introduce an adapter which does xml to json conversio and send the result to post processing system

We will consider the second option here.
Note: We have two flavour of adapter pattern viz Class adapter pattern (inheritance) object adapter pattern (composition).
Here we consider composition adapter pattern

Here - TransactionSystem (Interfaced by ITransactionSystem) produces xml output (this will be adaptee)
       PostProcessSystem (Interface by IPostProcessSystem) consumes in JSON format
       TransToPostProcAdapter  will be the adapter which does the conversion

*/

#include <iostream>

using namespace std; //never using this

//Stub class for file operation
struct myfstream
{
	
};

class ITransactionSystem
{
	public:
		virtual myfstream getTransactionOutPut() = 0;
		virtual ~ITransactionSystem() = default;
		
};

class TransactionSystem:public ITransactionSystem
{
	public:
		myfstream getTransactionOutPut()
		{
			
			myfstream XMLFile;
			cout<<"\n"<<"Creating XML file inside TransactionSystem"<<"\n";
			//Assume some meaningful operations happen here
			//and the xml file is generated
			return XMLFile;
		}
		
};


class IPostProcessSystem
{
	public:
		virtual  bool processTransactionInput(myfstream& JSONInputFile) = 0;
		virtual ~IPostProcessSystem() = default;
		
};

class PostProcessSystem:public IPostProcessSystem
{
	public:
		bool processTransactionInput(myfstream& JSONInputFile)
		{
			//Assume some meaningful operations happen here
			//and JSON file is processed
			cout<<"\n"<<"Processed JSON file inside PostProcessSystem"<<"\n";
			return true;
		}
		
};

//Our Adapter
class TransToPostProcAdapter
{
	private:
		ITransactionSystem* m_pTransactionSystem;
		IPostProcessSystem* m_pPostProcessSystem;
		void XMLtoJSONConversion(const auto& xmlFile, auto& JSONFile)
		{
			//do conversion from XML to JSON here
		}
	public:
		TransToPostProcAdapter(ITransactionSystem* pTransactionSystem,IPostProcessSystem* pPostProcessSystem):m_pTransactionSystem(pTransactionSystem),
		m_pPostProcessSystem(pPostProcessSystem)
		{
		}
	
		bool processTransactionInput(myfstream& JSONInputFile)
		{
			auto xmlFile = 	m_pTransactionSystem->getTransactionOutPut();
			//do the conversion here
			this->XMLtoJSONConversion(xmlFile,JSONInputFile);
			//Now the conversion is done and we have populated JSON here.
			//we can forward it to post process system
			m_pPostProcessSystem->processTransactionInput(JSONInputFile);
			return true;
		}
		
};


int main()
{
	ITransactionSystem* pTransactionSystem = new TransactionSystem;
	IPostProcessSystem* pPostProcessSystem = new PostProcessSystem;

	TransToPostProcAdapter TA(pTransactionSystem, pPostProcessSystem);
	myfstream JSONFile;
	TA.processTransactionInput(JSONFile);
	
}


