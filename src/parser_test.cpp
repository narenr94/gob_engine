#include "jsonRaceParser.h"

#define RACE_JSON_DIR "/home/user/gob_engine/game_data/race"

bool isAbstractClass(const json& j){
    if (j.contains("is_abstract"))
    {
        return j["is_abstract"];
    }
    else
    {
        throw std::runtime_error("Key 'is_abstract' not found in JSON.");
    }
    return false; // Default return value if key is not found
}

bool hasBaseRace(const json& j, std::string& baseRace){
    if (j.contains("base_race"))
    {
        baseRace = j["base_race"];
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{

    // for(const auto& entry : std::filesystem::directory_iterator(RACE_JSON_DIR)){
    //     json j;
    //     if(readJsonFile(entry.path().string(), j)){
    //         printJson(j);
    //     }
    // }

    //reading if abstract or base class

    json j;
    if (readJsonFile(RACE_JSON_DIR + std::string("/hill_dwarf.json"), j)){
        try {
            bool isAbstract = isAbstractClass(j);
            std::cout << "Is abstract class: " << std::boolalpha << isAbstract << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    //reading ability mods

    // json j;
    // if (readJsonFile(RACE_JSON_DIR + std::string("/dwarf.json"), j))
    // {
    //     if (j.contains("ability_mods"))
    //     {
    //         for (const auto& mod : j["ability_mods"]) {
    //             std::string ability = mod["ability"];
    //             int value = mod["mod"];
    //             // Process additive intent...
    //         }
    //     }
    // }

    return 0;
}