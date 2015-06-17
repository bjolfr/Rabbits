#pragma once

#include"Bunny.h"
#include"Resources.h"

#include<string>
#include<vector>

class BunnyList
{
public:
	BunnyList(void);
	~BunnyList(void);

public:
	void Start();
	void NextTurn();
	void End();
	uint CurrentTurn()const;
	uint Size()const;
	uint MutantsNumber()const;
	uint AdultsNumber()const;

private:
	BunnyList(BunnyList& lst){} //ban to shallow copy lists
	BunnyList& operator=(BunnyList& lst){}

private:
	void Reproduction();
	void Mutation();
	void Extinction();
	void IncreaseAge();

private:
	uint m_TurnNumber;
	std::vector<Bunny*> lstRabbits;
	std::vector<Bunny*> lstNewBunnies;
	std::vector<Bunny*> lstMutants;
	std::vector<Bunny*> lstDeleted;
};