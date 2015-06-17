#pragma once

static const int MAX_BUNNY_AGE = 10;
static const int MAX_MUTANT_AGE = 50;
static const int MAX_LIST_SIZE = 1000;
static const int MUTATION_CHANCE = 2;

namespace Res{
static std::string strMaleFirstNames[] =
{
    "Slobodan",
    "Miroslav",
    "Vladimir",
    "Zoran",
    "Ivan",
    "Jovan",
    "Nikola",
    "Marko",
    "Milan",
    "Mihajlo"
};

static std::string strFemaleFirstNames[] =
{
    "Kate",
    "Ivana",
    "Lisa",
    "Vlada",
    "Zorana",
    "Sophia",
    "Ana",
    "Slobodanka",
    "Nikoleta",
    "Gorana"
};

static std::string strLastNames[] =
{
    "Abramovic",
    "Divac",
    "Bajic",
    "Damljanovic",
    "Stankovic",
    "Vucic",
    "Nikolic",
    "Antic",
    "Begovic",
    "Ekmecic"
};

static std::string strColourList[] =
{
    "White",
    "Brown",
    "Black",
    "Spotted"
};

//juvenile males with m, adult males w/ M,
//juvenile females w/ f, adult femails w/ F
//radioactive mutant vampire bunnies with X
static std::string strGender[7] = 
{"m","f","M","F","X","?","?"};
} /* Res */