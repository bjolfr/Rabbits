#include <iostream>
#include <agents.h>

#include "BunnyList.h"
#include "Resources.h"

class RabbitColony: public Concurrency::agent{
	public:
		RabbitColony(){
			std::cout << "RabbitColony constructor: " << this << std::endl; }
		virtual ~RabbitColony(){Concurrency::agent::wait(this);Clear();}
		
		void PrintStatistics(){
			if(!m_Colony.Size()){
				std::cout << "Colony was destoyed!" << std::endl; 
				return;
			}
			std::cout	<<	"Turnes were "		 << m_Colony.CurrentTurn() 	<< ", " <<
							"Colony size is "	 << m_Colony.Size()			<< ", " << 
							"Adults number is "	 << m_Colony.AdultsNumber()	<< ", " <<
							"Mutants number is " << m_Colony.MutantsNumber()	<< std::endl;
		}
		
		void Clear(){m_Colony.End();}
	private:
		void run(){
			m_Colony.Start();
			do{
				m_Colony.NextTurn();
			}while((m_Colony.AdultsNumber()>0) && (m_Colony.AdultsNumber() < MAX_LIST_SIZE));
			done();
		}
	private:
		BunnyList m_Colony;
};

void PressEnter(){
	std::cout << "Press ENTER to continue" << std::flush;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void PrintStatistics(BunnyList &Colony){
	std::cout	<< "Total turnes were "		<< Colony.CurrentTurn() 	<< ", " <<
				   "Colony size is "	<< Colony.Size()			<< ", " << 
				   "Adults number is "	<< Colony.AdultsNumber()	<< ", " <<
				   "Mutants number is " << Colony.MutantsNumber()	<< std::endl;
}

int main(){
	std::cout << "----------------" << std::endl;
	BunnyList colony;
	colony.Start();
	do{
		PressEnter(); colony.NextTurn();
		std::cout << ">>> Turn " << colony.CurrentTurn() << std::endl;
		PrintStatistics(colony);
	}while((colony.AdultsNumber()>0) && (colony.AdultsNumber() < MAX_LIST_SIZE));
	colony.End(); 
	PrintStatistics(colony);
	
	std::cout << "----------------" << std::endl;
	std::cout << "Game over" << std::endl;
	PressEnter();
	return 0;
}