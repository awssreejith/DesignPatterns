/*
Bridge Pattern is mainly used to alleviate the problem of creating a large number of concerete classes out interfaces. The main aim of 
bridge pattern is to reduce the generalization(inheritance) to the maximum and leverage the power of composition. It can be exemplified as below.

Problem: Imagine we want to define certain airraft class according to the type of the aircraft and purpose. A typical generalized version of the same is 
as below

			Framework
			/------------------------------------------------------------------------------------------------\
		WebFramework	                     			 											DeskTopAppFrameWork
		/-----------------------------\																	/-------------------\
	WebFWForJAVA    				 WebFWForPython					 							DeskTopFWForJAVA		DeskTopFWForJAVA
	   /									\---------------/-----------------\							/						\
	 OpenSourceWebFMJAVA  ProperiteryWebFMJAVA     OpenSourceWebFMPython  ProperiteryWebFMPython     -------				--------
	
If we closely monitor each level will be exponentially increasing as we create generalizations down. For example, for types of framework (web and desktopt)
there are 4 children inherited. And thus the new classes will be expanding in exponential manner horizontally.

Solution: Use composition as an alternative.

*/

/*
We gonna do a small refactoring here. We gonna have 3 sets of classes. Framework, Language and License. Let Framework class compose the license type and
language. This means that we will have a framework which has language dependency and license type. (e.g Django frame work which has Python as language
and BSD license.
*/

#include <iostream>
#include <string.h>
using namespace std;

class Language
{
	public:
		public:
			virtual void setLanguage() = 0;
			virtual void getLanguage() = 0;
			virtual ~Language() = default;
		protected:
			string language;
};

class Java:public Language
{
	public:
		public:
			void setLanguage()
			{
				language.assign("Java");
			}
			
			void getLanguage()
			{
				cout<<"\n"<<"Though this is java frame work..simple redisplaying FW AS "<<language<<"\n";
			}

};

class Python:public Language
{
	public:
		public:
			void setLanguage()
			{
				language.assign("Python");
			}
			
			void getLanguage()
			{
				cout<<"\n"<<"Though this is Python frame work..simple redisplaying FW AS "<<language<<"\n";
			}

};

class License
{
	public:
		public:
			virtual void setLicense() = 0;		
			virtual void getLicense() = 0;
			virtual ~License() = default;
	protected:
		string licenseType;

};


class OpenSource:public License
{
	public:
		public:
			void setLicense()
			{
				licenseType.assign("Opensource");
			}
			
			void getLicense()
			{
				cout<<"\n"<<"Though this is open source frame work..simple redisplaying FW AS "<<licenseType<<"\n";
			}

};


class ClosedSource:public License
{
	public:
		public:
			void setLicense()
			{
				licenseType.assign("ClosedSource"); 
			}
			
			void getLicense()
			{
				cout<<"\n"<<"Though this is closed source frame work..simple redisplaying FW AS "<<licenseType<<"\n";
			}

};

class Framework
{
	public:
		public:
			virtual void setType() = 0;		
			virtual void getType() = 0;
			virtual void setLangAndLicese(Language* , License* ) = 0;
			virtual void getAllDetils() = 0;
			virtual ~Framework() = default;
			
	protected:
		string frameWorkType;
		License* license;
		Language* lang;
		

};


class DeskTopApp:public Framework
{
	public:
		public:
			void setType()
			{
				frameWorkType.assign("Desk Top Application");
			}
			
			void getType()
			{
				cout<<"\n"<<"Though this is a desk top app..simple redisplaying FW AS "<<frameWorkType<<"\n";
			}
			
			void setLangAndLicese(Language* plang, License* plic)
			{
				cout<<"\n"<<"Setting both license and language for desktop application";
				license = plic;
				lang = plang;
			}
			
			void getAllDetils()
			{
				cout<<"\n"<<"Getting all details for DeskTop Application";
				license->getLicense();
				lang->getLanguage();
				this->getType();
				cout<<"\n";
			}
		

};


class WebApp:public Framework
{
	public:
		public:
			void setType()
			{
				frameWorkType.assign("Desk Top Application");
			}
			
			void getType()
			{
				cout<<"\n"<<"Though this is a desk top app..simple redisplaying FW AS "<<frameWorkType<<"\n";
			}
			
			void setLangAndLicese(Language* plang, License* plic)
			{
				cout<<"\n"<<"Setting both license and language for web application";
				license = plic;
				lang = plang;
			}
			
			void getAllDetils()
			{
				cout<<"\n"<<"Getting all details for Web Application";
				license->getLicense();
				lang->getLanguage();
				this->getType();
				cout<<"\n";
			}

};


int main()
{
	//we need a webframework for Python which is opensource
	Language* lang = new Python();
	lang->setLanguage();
	
	License* license= new OpenSource();
	license->setLicense();
	
	Framework* django = new WebApp();
	django->setType();
	django->setLangAndLicese(lang,license);
	
	django->getAllDetils();
	
	/*Likewise we can create any combination of language/license/application type
	python - web application     - closed source
	python - desktop application - closed source
	python - web application     - open source
	python - desktop application - open source
	JAVA   - web application     - closed source
	JAVA   - desktop application - closed source
	JAVA   - web application     - open source
	JAVA  - desktop application  - open source
	.......
	.......
	.......
	*/
}


