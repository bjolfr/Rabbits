#include "BunnyList.h"

#include <time.h>  /* time */
#include <iostream>
#include <algorithm>

BunnyList::BunnyList(void):m_TurnNumber(0){
	//for debbuging
	std::cout << "Constructor: BunnyList " << this << std::endl;
}


BunnyList::~BunnyList(void){
	End();
	std::cout << "Destructor: BunnyList " << this << std::endl << std::flush;
}

void BunnyList::Start() {
	// initialize random seed:
	uint s = (uint)(time(NULL));
	std::srand (s);
	for(int i=0; i<=4; ++i) lstRabbits.push_back(Bunny::Init()); //first five rabbits
	std::cout << "Colony has been initialized!" << std::endl;
}

uint BunnyList::Size() const { return lstRabbits.size();}

uint BunnyList::MutantsNumber() const {return lstMutants.size();}

//Radioactive vampire bunnies are excluded from regular breeding and do not count as adult bunnies.
uint BunnyList::AdultsNumber() const {return (lstRabbits.size()-lstMutants.size());}

uint BunnyList::CurrentTurn()const{return m_TurnNumber;}

void BunnyList::NextTurn() {
	if(!lstRabbits.size()){
		std::cout << "Colony has died!" << std::endl;
		return;
		//Start();
	}	
	Reproduction();
	Mutation();
	Extinction();
	IncreaseAge();
	m_TurnNumber++;
}

//must be separatly in the end of turn
void BunnyList::IncreaseAge(){
	if(!lstRabbits.size()) return;
	for(auto it=lstRabbits.begin(); it!=lstRabbits.end(); ++it){
		Bunny* x = (*it);
		uint xAge = x->GetAge(); //one time involve functions
		uint xFeatures = x->GetFeatures();
		if(((xAge>=MAX_BUNNY_AGE) && !(xFeatures & Bunny::IsMutant)) ||
		   ((xAge>=MAX_MUTANT_AGE) &&  (xFeatures & Bunny::IsMutant))) {
			   lstDeleted.push_back(*it);
			   std::cout << "\t" << x->Name() << "\twas died of old it was aged " << xAge << std::endl << std::flush;
		}
		x->AddAge();
		
		//checking for new mutation
		//it must be 
		if(x->GetFeatures()&Bunny::IsMutant){ 
			auto itMutant = find(lstMutants.begin(), lstMutants.end(), *it);
			if(itMutant == lstMutants.end()) lstMutants.push_back(*it);
		}
	}
}

void BunnyList::Reproduction(){
	if(!lstRabbits.size()) return;
	for(auto it=lstRabbits.begin(); it!=lstRabbits.end(); ++it){
		Bunny* x = (*it);
		std::cout << x->Details() << std::endl << std::flush;
		if(x->GetFeatures()!=0x2) continue;
		for(auto itFemales=lstRabbits.begin(); itFemales!=lstRabbits.end(); ++itFemales){
			Bunny *y = (*itFemales);
			if (y->GetFeatures()==(Bunny::IsFemale|Bunny::IsAdult)){ // Adult Female, no Mutant 
				Bunny *chl = y->CreateNew(*x);
				std::cout << "\t   ->" << chl->Details() << " was born!" << std::endl << std::flush; 
				lstNewBunnies.push_back(chl);
			}  
		} // the end of the journey
		//} //Adult Male, no Mutant
	} //main cycle 

	lstRabbits.insert(lstRabbits.end(), lstNewBunnies.begin(), lstNewBunnies.end());
	lstNewBunnies.clear();
}

void BunnyList::Mutation(){
	if(!lstMutants.size()) return;
	for(auto itMutant=lstMutants.begin(); itMutant!=lstMutants.end(); ++itMutant){ //every mutant will bit one neighbor
		uint i = std::rand()%lstRabbits.size();
		Bunny* xVictim = lstRabbits[i];
		if( ((*itMutant) == xVictim) ||
			(xVictim->GetFeatures() & Bunny::IsMutant)){ //-> to die of starvation
			lstDeleted.push_back(*itMutant);
			std::cout << "\t" << (*itMutant)->Name() << "\twas died of starvation by " << xVictim->Name() << std::endl << std::flush;
		}
		else{
			(*itMutant)->BitNeighbor(*xVictim);
			std::cout << "\t" << xVictim->Name() << "\twas bitted by " << (*itMutant)->Name() << std::endl << std::flush;
		}
	}//mutations
}

void BunnyList::Extinction(){
	if(!lstDeleted.size()) return;
	for(auto itDead = lstDeleted.begin(); itDead!=lstDeleted.end(); ++itDead){ //destroy
		Bunny* xDead = (*itDead);
		
		if(lstMutants.size()>0){
			auto itMutant = find(lstMutants.begin(), lstMutants.end(), xDead);
			if(itMutant != lstMutants.end()) lstMutants.erase(itMutant);
		}

		auto itRabbit = find(lstRabbits.begin(), lstRabbits.end(), xDead);
		if(itRabbit != lstRabbits.end()) lstRabbits.erase(itRabbit);
		Bunny::Release(*xDead);
	}
	lstDeleted.clear();
}

//move to dead list to extintion afterward
void BunnyList::End(){
	if(!lstRabbits.size()) return;
	lstMutants.clear();
	lstDeleted.clear();
	for(auto it=lstRabbits.begin(); it!=lstRabbits.end(); ++it) Bunny::Release(**it);
	lstRabbits.clear();
}