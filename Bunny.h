#pragma once
//to pack/unpack stuctures 
//#pragma pack(push,1)
//
//#pragma push(pop)


#include <string>
#include <vector>
typedef unsigned int uint; 

class Bunny
{
public:
	enum Color:uint {White, Brown, Black, Spotted};
	enum Cond:uint {
		IsFemale = 0x01,
		IsAdult  = 0x02,
		IsMutant = 0x04};
public:
	static Bunny* Init();
	static void Release(Bunny& x);

public:
	Bunny* CreateNew(const Bunny& Father);
	std::string Name() const;
	std::string Details() const;
	std::string FormatedDetails() const;
	uint GetFeatures() const {return m_Features;};
	uint GetAge() const {return m_Age;}
	void BitNeighbor(Bunny& Victim);
	void AddAge();

private:
	Bunny(void);
	Bunny(const Bunny &x); //ban to copy objects
	Bunny& operator=(Bunny &x);
	~Bunny(void);

private:
	int generateRandom(int x);
	void setFeatures();

private:
	//Sex m_Sex;
	Color m_Color;
	uint m_Age; //0-10
	std::string m_strFirstName;
	std::string m_strLastName;
	//bool m_radioactive_mutant_bunny;
	uint m_Features;
	//more interesting to implement struct with bit fields
	struct Feature {
		unsigned char _is_female : 1;
		unsigned char _is_adult  : 1;
		unsigned char _is_mutant : 1;
		//probaly here need overloaded operator=()
	} m_Features1; 
	//in this case all work doing compiler

private:
	std::vector<Bunny*> m_vDescendants;
	Bunny *m_pMother;
	Bunny *m_pFather;
};

