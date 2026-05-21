#pragma once

#include "defines.h"

class Character; //Forward declaration

class Race {
    private:
        Character* m_character;

    protected:

        virtual void raceBenifitsCharacterCreation() = 0;

    public:
        Race(Character* t_character) : m_character(t_character){

        }

        virtual ~Race() = default;

        virtual void levelUp() = 0;

        virtual CharacterRace getRace() = 0;

        
        
};


//--------------------Dwarves

class Dwarf : public Race{

    protected:

        void raceBenifitsCharacterCreation();

    public:
        Dwarf(Character* t_character) : Race(t_character){

        }

        virtual CharacterRace getRace() = 0;
};

class HillDwarf : public Dwarf{
    
    protected:

        void raceBenifitsCharacterCreation();

    public:
        HillDwarf(Character* t_character) : Dwarf(t_character){
            Dwarf::raceBenifitsCharacterCreation();
            raceBenifitsCharacterCreation();
        }

        CharacterRace getRace(){
            return CharacterRace::Hill_Dwarf;
        }
};


class MountainDwarf : public Dwarf{
    
    protected:

        void raceBenifitsCharacterCreation();

    public:
        MountainDwarf(Character* t_character) : Dwarf(t_character){
            Dwarf::raceBenifitsCharacterCreation();
            raceBenifitsCharacterCreation();
        }

        CharacterRace getRace(){
            return CharacterRace::Mountain_Dwarf;
        }
};


//---------------------Elves


class Elf : public Race{
    protected:

        void raceBenifitsCharacterCreation();

    public:
        Elf(Character* t_character) : Race(t_character){

        }

        virtual CharacterRace getRace() = 0;
};

class HighElf : public Elf{
    protected:

        void raceBenifitsCharacterCreation();

    public:
        HighElf(Character* t_character) : Elf(t_character){
            Elf::raceBenifitsCharacterCreation();
            raceBenifitsCharacterCreation();
        }

        CharacterRace getRace(){
            return CharacterRace::High_Elf;
        }
};

class WoodElf : public Elf{
    protected:

        void raceBenifitsCharacterCreation();

    public:
        WoodElf(Character* t_character) : Elf(t_character){
            Elf::raceBenifitsCharacterCreation();
            raceBenifitsCharacterCreation();
        }

        CharacterRace getRace(){
            return CharacterRace::Wood_Elf;
        }
};

class DarkElf : public Elf{
    protected:

        void raceBenifitsCharacterCreation();

    public:
        DarkElf(Character* t_character) : Elf(t_character){
            Elf::raceBenifitsCharacterCreation();
            raceBenifitsCharacterCreation();
        }

        CharacterRace getRace(){
            return CharacterRace::Dark_Elf;
        }
};


//-----------------------Halflings


class Halfling : public Race{
    protected:

        void raceBenifitsCharacterCreation();

    public:
        Halfling(Character* t_character) : Race(t_character){

        }

        virtual CharacterRace getRace() = 0;
};


class LightfootHalfling : public Halfling{
    protected:

        void raceBenifitsCharacterCreation();

    public:
        LightfootHalfling(Character* t_character) : Halfling(t_character){
            Halfling::raceBenifitsCharacterCreation();
            raceBenifitsCharacterCreation();
        }

        CharacterRace getRace(){
            return CharacterRace::Lightfoot_Halfling;
        }
};


class StoutHalfling : public Halfling{
    protected:

        void raceBenifitsCharacterCreation();

    public:
        StoutHalfling(Character* t_character) : Halfling(t_character){
            Halfling::raceBenifitsCharacterCreation();
            raceBenifitsCharacterCreation();
        }

        CharacterRace getRace(){
            return CharacterRace::Stout_Halfling;
        }
};



//-----------------Human

class Human : public Race{
    protected:

        void raceBenifitsCharacterCreation();

    public:
        Human(Character* t_character) : Race(t_character){

        }

        CharacterRace getRace(){
            return CharacterRace::Human;
        }
};

//----------------Custom Race

class CustomRace : public Race{
    protected:

        void raceBenifitsCharacterCreation();

    public:
        CustomRace(Character* t_character, CustomRaceData* t_customData): 
        Race(t_character)
        {

        }

        CharacterRace getRace(){
            return CharacterRace::Human;
        }
};