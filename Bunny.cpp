#include "Bunny.h"
#include "Resources.h"

#include <random>  /* srand, rand */
#include <sstream>
#include <iomanip>

//for debbuging
#include <iostream>


Bunny* Bunny::Init(){
	Bunny *tmp = new Bunny;
	tmp->setFeatures();
	return tmp;
}

void Bunny::Release(Bunny& x){
	Bunny* tmp = &x;
	delete tmp;
}

//one female rabbit can create another rabbit from father
//better to have reference because it must be initialize
//pointer to created object to avoid shallow copy
Bunny* Bunny::CreateNew(const Bunny& Father){
	//use new to allocate object in heap
	Bunny *tmp = new Bunny;
	tmp->m_pMother = this;
	if(&Father!=nullptr)
		tmp->m_pFather = const_cast<Bunny*>(&Father);
	//not uni- one rabbit can has many children
	//but every one has a mother and father
	tmp->setFeatures();
	m_vDescendants.push_back(tmp);
	return tmp;
}

Bunny::Bunny(void): m_Color(Bunny::White),
					m_Age(0),
					m_strFirstName(""),
					m_strLastName(""),
					m_pMother(0),
					m_pFather(0),
					m_Features(IsFemale){
}

//copy ctor do nothing
//we need to make it private to prevent copy
Bunny::Bunny(const Bunny &x){ std::cout << "Copy-Constructor: Bunny " << &x << " and copy "<< this << std::endl;}

Bunny::~Bunny(void){}

int Bunny::generateRandom(int x){
	return (std::rand() % x);
}

void Bunny::setFeatures(){
	int s = generateRandom(2);//1-Female
	if(!s) m_Features = m_Features^IsFemale;

	this->m_Color = static_cast<Color>(generateRandom(4));
	
	int i = generateRandom(10); //Generate name
	m_strFirstName = m_Features&IsFemale?Res::strFemaleFirstNames[i] : Res::strMaleFirstNames[i];
		
	if(!m_pFather) //Choose or generate last name
		m_strLastName = Res::strLastNames[i];
	else
		m_strLastName = m_pFather->m_strLastName;

	if(m_pMother) //child must have a mother's color
		m_Color = m_pMother->m_Color;

	i = generateRandom(100); //Generate radioactive_mutant_bunny
	if(i<=MUTATION_CHANCE){
		uint MASK =  ~(IsMutant|IsAdult|IsFemale);
		m_Features =  ((m_Features & MASK) | IsMutant);
		m_Features1._is_mutant = true; //IsMutant;
		m_Features1._is_adult = 0;
		m_Features1._is_female = 0;
	}
}

void Bunny::BitNeighbor(Bunny& Victim){
	uint MASK = ~(IsMutant|IsAdult|IsFemale);
	Victim.m_Features = ((Victim.m_Features & MASK) | IsMutant);
}

std::string Bunny::Details() const{
	std::string strColor = Res::strColourList[static_cast<int>(m_Color)];
	std::ostringstream ss;
	ss  << (m_Features&IsMutant? "[!] ":"[ ] ") <<
		   m_strFirstName				 << " " << 
		   m_strLastName				 << ":" <<
		   Res::strGender[m_Features]	 << ":" <<
		   strColor						 << ":" <<
		   std::dec << m_Age;
	return ss.str();
}

std::string Bunny::FormatedDetails() const{
	std::string strColor = Res::strColourList[static_cast<int>(m_Color)];
	std::ostringstream ss;
	ss  << setiosflags(std::ios::left) <<
		   std::setw(10) << m_strFirstName		<< " " << 
		   std::setw(10) << m_strLastName		<< ":" <<
		   std::setw(1)  << (m_Features&IsFemale?"F":"M")		<< ":" << 
		   std::setw(7)  << strColor			<< ":" <<
		   resetiosflags(std::ios::left) <<
		   std::setw(2)  << std::dec << m_Age	<< ":" <<
		   (m_Features&IsMutant? "->0<-":"");
	return ss.str();
}

std::string Bunny::Name() const{
	std::ostringstream ss;
	ss <<  m_strFirstName << " " << m_strLastName;
	return ss.str();
}

void Bunny::AddAge(){
	m_Age++;
	if(m_Age>2) m_Features|=IsAdult;
}