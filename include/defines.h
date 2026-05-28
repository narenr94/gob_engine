#pragma once

#include "log.h"

#include <vector>
#include <string>

#define ABILITY_SCORE_MAX 20

#define DEFAULT_PARAM_DIE 8

class Character; //Forward declaration

enum class SizeCategory{
    Tiny,
    Small,
    Medium,
    Large,
    Huge,
    Garg
};

enum class ProficiencyType{
    Weapons,
    Armors,
    Tools,
    Skills,
    SavingThrows
};

enum class IlluminationType{
    Normal,
    Dim,
    Dark
};

//------Level enum

enum class Level{
    Lvl1,
    Lvl2,
    Lvl3,
    Lvl4,
    Lvl5,
    Lvl6,
    Lvl7,
    Lvl8,
    Lvl9,
    Lvl10,
    Lvl11,
    Lvl12,
    Lvl13,
    Lvl14,
    Lvl15,
    Lvl16,
    Lvl17,
    Lvl18,
    Lvl19,
    Lvl20
};

//------Alignment

enum class Alignment{

    lawful_good,
    lawful_neutral,
    lawful_evil,

    neutral_good,
    neutral_neutral,
    neutral_evil,

    chaotic_good,
    chaotic_neutral,
    chaotic_evil

};

//------All items list
enum class ItemType{
    Minor_Health_Potion,
    Minor_Stamina_Potion,
    Minor_Mana_Potion
};


//-----Item Utility

enum class ItemUtility{
    Consumable,
    CraftingIngredient,
    Armor,
    Weapon,
    Quest,
    NonCombat
};

//------JSON Keys

enum class JsonKeys{
    name,
    is_abstract,
    base_race,
    ability_mods,
    param_mods,
    ability,
    param,
    mod,
    age,
    maturity,
    life_span,
    alignment,
    size,
    category,
    avg_height_m,
    avg_weight_kg,
    speed_mps,
    languages,
    speak,
    read,
    write,
    dark_vision,
    has_darkvision,
    dim_light_eq,
    as_ambient,
    distance_m,
    darkness_eq,
    resilience,
    affliction,
    immune,
    has_advantage,
    has_resistance,
    proficiency,
    weapons,
    tools,
    armors,
    skills,
    options,
    choose,
    all,
    choices,
    sleep_duration_hrs,
    abilities,
    params,
    saving_throws,
    attribute,
    arguments,
    conditional,
    condition,
    todo,
    pack,
    item,
    count

};

enum class conditionsType{
    if_character_has_item
};


//--------Lookup Tables

const std::vector<std::pair<Level, unsigned int>> g_expPointsLookupTable = {
    {Level::Lvl1, 0},
    {Level::Lvl2, 300},
    {Level::Lvl3, 900},
    {Level::Lvl4, 2700},
    {Level::Lvl5, 6500},
    {Level::Lvl6, 14000},
    {Level::Lvl7, 23000},
    {Level::Lvl8, 34000},
    {Level::Lvl9, 48000},
    {Level::Lvl10, 64000},
    {Level::Lvl11, 85000},
    {Level::Lvl12, 100000},
    {Level::Lvl13, 120000},
    {Level::Lvl14, 140000},
    {Level::Lvl15, 165000},
    {Level::Lvl16, 195000},
    {Level::Lvl17, 225000},
    {Level::Lvl18, 265000},
    {Level::Lvl19, 305000},
    {Level::Lvl20, 355000}

};

const std::vector<std::pair<Level, unsigned short int>> g_proficiencyBonusLookupTable = {
    {Level::Lvl1, 2},
    {Level::Lvl2, 2},
    {Level::Lvl3, 2},
    {Level::Lvl4, 2},
    {Level::Lvl5, 3},
    {Level::Lvl6, 3},
    {Level::Lvl7, 3},
    {Level::Lvl8, 3},
    {Level::Lvl9, 4},
    {Level::Lvl10, 4},
    {Level::Lvl11, 4},
    {Level::Lvl12, 4},
    {Level::Lvl13, 5},
    {Level::Lvl14, 5},
    {Level::Lvl15, 5},
    {Level::Lvl16, 5},
    {Level::Lvl17, 6},
    {Level::Lvl18, 6},
    {Level::Lvl19, 6},
    {Level::Lvl20, 6}
};

const std::vector<std::pair<Alignment,std::string>> alignmentStrMap = {
    {Alignment::lawful_good, "lawful_good"},
    {Alignment::lawful_neutral, "lawful_neutral"},
    {Alignment::lawful_evil, "lawful_evil"},
    {Alignment::neutral_good, "neutral_good"},
    {Alignment::neutral_neutral, "neutral_neutral"},
    {Alignment::neutral_evil, "neutral_evil"},
    {Alignment::chaotic_good, "chaotic_good"},
    {Alignment::chaotic_neutral, "chaotic_neutral"},
    {Alignment::chaotic_evil, "chaotic_evil"},
};

const std::vector<std::pair<SizeCategory, std::string>> sizeCategoryStrMap = {
    {SizeCategory::Tiny, "tiny"},
    {SizeCategory::Small, "small"},
    {SizeCategory::Medium, "medium"},
    {SizeCategory::Tiny, "tiny"},
    {SizeCategory::Large, "large"},
    {SizeCategory::Huge, "huge"},
    {SizeCategory::Garg, "gargantuan"},
};

const std::vector<std::pair<IlluminationType, std::string>> illumincationTypeStrMap = {
    {IlluminationType::Normal, "normal"},
    {IlluminationType::Dim, "dim"},
    {IlluminationType::Dark, "dark"}
};


const std::vector<std::pair<ProficiencyType, std::string>> proficiencyTypeStrMap = {
    {ProficiencyType::Weapons, "weapons"},
    {ProficiencyType::Armors, "armors"},
    {ProficiencyType::Tools, "tools"},
    {ProficiencyType::Skills, "skills"},
    {ProficiencyType::SavingThrows, "saving_throws"}
};

const std::vector<std::pair<conditionsType, std::string>> conditionsTypeStrMap = {
    {conditionsType::if_character_has_item, "if_character_has_item"}
};

const std::vector<std::pair<JsonKeys, std::string>> jsonKeysStrMap = {
    {JsonKeys::name, "name"},
    {JsonKeys::is_abstract, "is_abstract"},
    {JsonKeys::base_race, "base_race"},
    {JsonKeys::ability_mods, "ability_mods"},
    {JsonKeys::param_mods, "param_mods"},
    {JsonKeys::ability, "ability"},
    {JsonKeys::param, "param"},
    {JsonKeys::mod, "mod"},
    {JsonKeys::age, "age"},
    {JsonKeys::maturity, "maturity"},
    {JsonKeys::life_span, "life_span"},
    {JsonKeys::alignment, "alignment"},
    {JsonKeys::size, "size"},
    {JsonKeys::category, "category"},
    {JsonKeys::avg_height_m, "avg_height_m"},
    {JsonKeys::avg_weight_kg, "avg_weight_kg"},
    {JsonKeys::speed_mps, "speed_mps"},
    {JsonKeys::languages, "languages"},
    {JsonKeys::speak, "speak"},
    {JsonKeys::read, "read"},
    {JsonKeys::write, "write"},
    {JsonKeys::dark_vision, "dark_vision"},
    {JsonKeys::has_darkvision, "has_darkvision"},
    {JsonKeys::dim_light_eq, "dim_light_eq"},
    {JsonKeys::as_ambient, "as_ambient"},
    {JsonKeys::distance_m, "distance_m"},
    {JsonKeys::darkness_eq, "darkness_eq"},
    {JsonKeys::resilience, "resilience"},
    {JsonKeys::affliction, "affliction"},
    {JsonKeys::immune, "immune"},
    {JsonKeys::has_advantage, "has_advantage"},
    {JsonKeys::has_resistance, "has_resistance"},
    {JsonKeys::proficiency, "proficiency"},
    {JsonKeys::weapons, "weapons"},
    {JsonKeys::tools, "tools"},
    {JsonKeys::armors, "armors"},
    {JsonKeys::skills, "skills"},
    {JsonKeys::options, "options"},
    {JsonKeys::choose, "choose"},
    {JsonKeys::all, "all"},
    {JsonKeys::choices, "choices"},
    {JsonKeys::sleep_duration_hrs, "sleep_duration_hrs"},
    {JsonKeys::abilities, "abilities"},
    {JsonKeys::params, "params"},
    {JsonKeys::saving_throws, "saving_throws"},
    {JsonKeys::attribute, "attribute"},
    {JsonKeys::arguments, "arguments"},
    {JsonKeys::conditional, "conditional"},
    {JsonKeys::condition, "condition"},
    {JsonKeys::todo, "todo"},
    {JsonKeys::pack, "pack"},
    {JsonKeys::item, "item"},
    {JsonKeys::count, "count"}
};

struct Data{
    virtual void printData() const = 0;
    virtual void applyData(Character* t_character) const = 0;

    virtual ~Data() = default;
};

struct AgeData : public Data{
    unsigned short int maturityAge = 18;
    unsigned short int avgLifespan = 100;

    void printData() const;
    void applyData(Character* t_character) const;
}; 

struct AlignmentData : public Data{
    Alignment alignment = Alignment::neutral_neutral;

    void printData() const;
    void applyData(Character* t_character) const;
};

struct SpeedData : public Data{
    float speed = 0.0f;

    void printData() const;
    void applyData(Character* t_character) const;
};

struct SleepDurationData : public Data{
    float sleepDurationHrs = 0.0f;

    void printData() const;
    void applyData(Character* t_character) const;
};

struct SizeData : public Data{
    SizeCategory category = SizeCategory::Medium;
    std::pair<float, float> dimensions = {1.6, 60}; //height in meters, weight in kgs

    void printData() const;
    void applyData(Character* t_character) const;
};

struct LanguageData : public Data{
    std::string language = "";
    bool speak = false;
    bool read = false;
    bool write = false;

    void printData() const;
    void applyData(Character* t_character) const;
};

struct ProficiencyData : public Data{

    std::vector<std::string> weaponProficiencies = {};
    std::vector<std::string> armorProficiencies = {};
    std::vector<std::string> toolProficiencies = {};
    std::vector<std::string> skillProficiencies = {};
    std::vector<std::string> savingThrowsProficiencies = {};

    void printData() const;
    void applyData(Character* t_character) const;

};

struct ResilienceData : public Data{
    std::string affliction = "";
    bool immune = false;
    bool hasAdvantage = false;
    bool hasResistance = false;

    void printData() const;
    void applyData(Character* t_character) const;
};

struct DarkvisionData : public Data{
    bool hasDarkvision = false;
    IlluminationType dim_light_eq = IlluminationType::Dim;
    float dim_light_eq_dist = 0.0f;
    IlluminationType darkvision_eq = IlluminationType::Dark;
    float darkvision_eq_dist = 0.0f;

    void printData() const;
    void applyData(Character* t_character) const;
};

struct AbilityModData : public Data{
    std::pair<std::string, int> abilityMod;
    
    void printData() const;
    void applyData(Character* t_character) const;
    
};

struct ParamModData : public Data{
    std::pair<std::string, int> paramMod;
    
    void printData() const;
    void applyData(Character* t_character) const;
    
};

struct ItemData : public Data{
    std::pair<std::string, unsigned short int> itemData; //item name, count

    void printData() const;
    void applyData(Character* t_character) const;
};

struct PackData : public Data{
    std::string packData = "";

    void printData() const;
    void applyData(Character* t_character) const;
};

struct ConsolidatedData : public Data{

    std::vector<Data*> data = {};
    
    void printData() const;
    void applyData(Character* t_character) const;
};


struct OptionData{
    virtual void printOption() = 0;
    virtual void realizeOptions(Character* t_character, bool enablePlayerInput) = 0;

    virtual ~OptionData() = default;
};

struct ProficiencyOptionData : public OptionData{
    ProficiencyType type = ProficiencyType::Weapons;
    std::vector<std::string> choices = {};
    unsigned short int chooseCount = 0;

    void printOption();
    void realizeOptions(Character* t_character, bool enablePlayerInput);
};


struct LanguageOptionData : public OptionData{
    std::vector<std::string> choices = {};
    unsigned short int chooseCount = 0;
    bool speak = false;
    bool read = false;
    bool write = false;

    void printOption();
    void realizeOptions(Character* t_character, bool enablePlayerInput);
};

struct ItemOptionData : public OptionData{
    std::vector<std::pair<std::string, unsigned short int>> choices = {}; //item name, count
    unsigned short int chooseCount = 0;

    void printOption();
    void realizeOptions(Character* t_character, bool enablePlayerInput);
};

struct PackOptionData : public OptionData{
    std::vector<std::string> choices = {};
    unsigned short int chooseCount = 0;

    void printOption();
    void realizeOptions(Character* t_character, bool enablePlayerInput);
};

struct ConsolidatedOptionsData : public OptionData{

    std::vector<OptionData*> options = {};

    void printOption();
    void realizeOptions(Character* t_character, bool enablePlayerInput);

};

struct ifCharacterHasItemArg{
    std::string ind;
    unsigned short int count;
    Character* character;
};


