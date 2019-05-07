#include "pch.h"
#include <iostream>
#include <string>
#include <vector>


//Using Prototype
class Prototype
{
public:
	virtual Prototype* clone() = 0;
};


//Character's class where your location and name
class Character
{
public:
	std::string location;
	std::string name;
	Character(std::string location, std::string name)
	{
		this->location = location;
		this->name = name;
	}
};

//Class for person with your name & characteristic which may change while you play. Here you can clone your pers
class Person : public Prototype
{
public:
	std::string name;
	std::vector<Character> elements;

	Person(std::string name)
	{
		this->name = name;
	}

	Person(const Person& person)
	{
		this->name = person.name;
		this->elements = person.elements;
	}

	Prototype* clone() override
	{
		return new Person(*this);
	}
};

//Class for QuickSave where you can do that and watch your history of adventure
class QuickSave
{
public:
	Person* person;
	std::vector<Prototype*> saveState;

	QuickSave(Person* person)
	{
		this->person = person;
	}

	void save()
	{
		saveState.emplace_back(person->clone());
	}

	void seeQuickSave()
	{
		std::cout << "Quick save for " << person->name << std::endl << "-----------" << std::endl;
		for (auto& states : saveState)
		{
			std::cout << "Great adventure of " << person->name << ":\n" << std::endl;
			for (auto& it : ((Person*)states)->elements)
			{
				std::cout << it.name << " was in " << it.location << std::endl;
			}
			std::cout << std::endl;
		}
	}
};

int main()
{
	std::string name;
	std::cout << "Choose your character's name: ";
	std::cin >> name;
	std::cout << "\nHi, " << name << "\nLet's look for your quickSave history:\n\n";
	Person* person = new Person(name);
	QuickSave quicksave(person);
	person->elements.emplace_back(Character("Dawnstar", person->name));
	person->elements.emplace_back(Character("Markarth", person->name));
	quicksave.save();

	person->elements.emplace_back(Character("Solitude", person->name));
	quicksave.save();

	person->elements.emplace_back(Character("Riften", person->name));
	person->elements.emplace_back(Character("Windhelm", person->name));
	quicksave.save();

	quicksave.seeQuickSave();

	return 0;
}
