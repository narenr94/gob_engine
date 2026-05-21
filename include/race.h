#pragma once

#include "defines.h"

class Character; //Forward declaration

class Race {
    private:
        Character* m_character;

        std::string m_race;

    protected:

        virtual void raceBenifitsCharacterCreation() = 0;

    public:
        Race(Character* t_character, const std::string& t_race) :
        m_character(t_character), m_race(t_race)
        {

        }

        virtual ~Race() = default;

        virtual void levelUp() = 0;

        std::string getRace() const {
            return m_race;
        }

        
        
};


//--------------------Dwarves

class Dwarf : public Race{

    protected:

        void raceBenifitsCharacterCreation();

    public:
        Dwarf(Character* t_character, const std::string& t_race) : 
        Race(t_character, t_race)
        {

        }

        virtual std::string getRace() = 0;
};

class HillDwarf : public Dwarf{
    
    protected:

        void raceBenifitsCharacterCreation();

    public:
        HillDwarf(Character* t_character, const std::string& t_race) : 
        Dwarf(t_character, t_race)
        {
            Dwarf::raceBenifitsCharacterCreation();
            raceBenifitsCharacterCreation();
        }
};


class MountainDwarf : public Dwarf{
    
    protected:

        void raceBenifitsCharacterCreation();

    public:
        MountainDwarf(Character* t_character, const std::string& t_race) : 
        Dwarf(t_character, t_race)
        {
            Dwarf::raceBenifitsCharacterCreation();
            raceBenifitsCharacterCreation();
        }
};


//---------------------Elves


class Elf : public Race{
    protected:

        void raceBenifitsCharacterCreation();

    public:
        Elf(Character* t_character, const std::string& t_race) : 
        Race(t_character, t_race)
        {

        }

        virtual std::string getRace() = 0;
};

class HighElf : public Elf{
    protected:

        void raceBenifitsCharacterCreation();

    public:
        HighElf(Character* t_character, const std::string& t_race) : 
        Elf(t_character, t_race)
        {
            Elf::raceBenifitsCharacterCreation();
            raceBenifitsCharacterCreation();
        }
};

class WoodElf : public Elf{
    protected:

        void raceBenifitsCharacterCreation();

    public:
        WoodElf(Character* t_character, const std::string& t_race) : 
        Elf(t_character, t_race)
        {
            Elf::raceBenifitsCharacterCreation();
            raceBenifitsCharacterCreation();
        }
};

class DarkElf : public Elf{
    protected:

        void raceBenifitsCharacterCreation();

    public:
        DarkElf(Character* t_character, const std::string& t_race) : 
        Elf(t_character, t_race)
        {
            Elf::raceBenifitsCharacterCreation();
            raceBenifitsCharacterCreation();
        }
};


//-----------------------Halflings


class Halfling : public Race{
    protected:

        void raceBenifitsCharacterCreation();

    public:
        Halfling(Character* t_character, const std::string& t_race) : Race(t_character, t_race)
        {

        }

        virtual std::string getRace() = 0;
};


class LightfootHalfling : public Halfling{
    protected:

        void raceBenifitsCharacterCreation();

    public:
        LightfootHalfling(Character* t_character, const std::string& t_race) : 
        Halfling(t_character, t_race)
        {
            Halfling::raceBenifitsCharacterCreation();
            raceBenifitsCharacterCreation();
        }
};


class StoutHalfling : public Halfling{
    protected:

        void raceBenifitsCharacterCreation();

    public:
        StoutHalfling(Character* t_character, const std::string& t_race) : 
        Halfling(t_character, t_race){
            Halfling::raceBenifitsCharacterCreation();
            raceBenifitsCharacterCreation();
        }
};



//-----------------Human

class Human : public Race{
    protected:

        void raceBenifitsCharacterCreation();

    public:
        Human(Character* t_character, const std::string& t_race) : 
        Race(t_character, t_race)
        {

        }
};

//----------------Custom Race

class CustomRace : public Race{
    protected:

        void raceBenifitsCharacterCreation();

    public:
        CustomRace(Character* t_character, const std::string& t_race, CustomRaceData* t_customData): 
        Race(t_character, t_race)
        {

        }
};