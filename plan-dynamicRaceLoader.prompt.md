## Plan: Dynamic JSON-Based Race Loading System

Build a flexible race system using nlohmann/json to load race definitions from JSON files at runtime, eliminating hard-coded race classes and enabling easy addition of new races without recompilation.

**TL;DR**: Replace the hard-coded Race class hierarchy with a data-driven system. Load all JSON race files at startup, merge inheritance chains (base_race), and apply race benefits dynamically through Character's existing methods (`updateAbilityScore`, `updateParamMax`). Keep the current factory pattern but populate it from JSON rather than hard-coded classes.

---

### Steps

**Phase 1: Setup & Data Structures** *(parallel with Phase 2)*

1. Add nlohmann/json to project - download single-header library from https://github.com/nlohmann/json (json.hpp) to include/ directory or use package manager
2. Create RaceData structure in new header `include/raceData.h` - define structs to mirror JSON schema:
   - `AbilityModifier` (ability, mod, action)
   - `ParamModifier` (param, mod, action)
   - `Language` (name, speak, read, write, action)
   - `DarkVision` (has_darkvision, dim_light_eq, darkness_eq)
   - `Resilience` (affliction, has_advantage, has_resistance, immune)
   - `Trait` (name, action, trigger_condition, allow_action, etc.) //todo later
   - `Proficiency` (weapons, armors, tools with choose/options/action)
   - `RaceData` (aggregate struct containing all above plus name, is_abstract, base_race, age, alignment, size, speed, etc.)

**Phase 2: JSON Parser Implementation** *(parallel with Phase 1)*

3. Create `src/raceLoader.cpp` and `include/raceLoader.h` with RaceLoader class containing:
   - `loadAllRaces(const std::string& directory_path)` - scans game_data/race/, loads all .json files
   - `parseRaceJson(const nlohmann::json& j)` - converts JSON object to RaceData struct
   - `resolveInheritance(RaceData& race)` - recursively merges base_race data (if race has base_race, load parent and merge)
   - Private member: `std::map<std::string, RaceData> m_raceRegistry` - stores all loaded races keyed by name
   - `getRaceData(const std::string& race_name)` - retrieves merged RaceData

**Phase 3: Race Class Refactoring** *(depends on 1-4)*

4. Simplify Race class in `include/race.h`:
   - Remove all subclasses (Dwarf, HillDwarf, HighElf, etc.)
   - Race becomes single concrete class (not abstract)
   - Add private member: `RaceData m_data`
   - Constructor: `Race(Character* t_character, const RaceData& data)`
   - Implement `raceBenifitsCharacterCreation()` to apply m_data modifications to Character
   - Implement `levelUp()` to apply per-level benefits (e.g., param_mods with "add_per_level" action)
   - Remove virtual inheritance - single class suffices

**Phase 4: Benefit Application Logic** *(depends on 4)*

5. Implement `Race::raceBenifitsCharacterCreation()` to:
   - Iterate through `m_data.ability_mods`, call `t_character->updateAbilityScore` for each
   - Iterate through `m_data.param_mods` with action "add", call `t_character->updateParamMax`
   - Store traits, proficiencies, languages in new Character data structures (requires extending Character class)
   - Apply resilience, darkvision, and other special properties (may require new Character storage fields)
6. Implement `Race::levelUp()` - apply param_mods where action is "add_per_level" (e.g., hill_dwarf hit_point +1 per level)

**Phase 5: Factory & Initialization** *(depends on 3, 4)*

7. Update `raceFactory` function in race.h:
   - Replace hard-coded string matching with lookup in RaceLoader's registry
   - `RaceLoader::getInstance().getRaceData(t_race)` → pass to Race constructor
   - Remove CustomRace handling (superseded by JSON system)
8. Add global initialization - create static RaceLoader instance that calls `loadAllRaces("./game_data/race")` at program start (before any Character creation)

**Phase 6: Character Extension** *(parallel with Phase 5)*

9. Extend Character class in `include/character.h` to store race-specific data not currently tracked:
   - `std::vector<Language> m_languages`
   - `std::vector<Trait> m_traits`
   - `std::vector<std::string> m_proficiencies`
   - `DarkVision m_darkVision`
   - `std::vector<Resilience> m_resiliences`
   - Add getter methods for these new fields

**Phase 7: Verification** *(depends on all previous)*

10. Build and test with existing JSON files (human, elf, dwarf, halfling, and all subraces)
11. Verify hill_dwarf gets +1 HP per level (param_mods with add_per_level)
12. Verify inheritance merging - high_elf should have both elf abilities (+2 dex) and high_elf abilities (+1 int)
13. Create a new race JSON file (e.g., tiefling.json) without recompiling - verify it loads and applies correctly

---

### Relevant files

- `include/race.h` - Race class hierarchy to be simplified, raceFactory function to update
- `include/character.h` - Character class with updateAbilityScore, updateParamMax, updateParamCurr methods; needs extension for traits/languages/proficiencies
- `game_data/race/*.json` - 14 JSON files defining all races, inheritance patterns via base_race field
- `include/defines.h` - Contains g_abilitiesVector, g_characterParamsVector, g_racesVector global definitions
- New files to create:
  - `include/raceData.h` - Data structures mirroring JSON schema
  - `include/raceLoader.h` - RaceLoader class declaration
  - `src/raceLoader.cpp` - RaceLoader implementation with nlohmann/json parsing

---

### Verification

1. **Build test** - Add nlohmann/json, compile with new race system, ensure no build errors
2. **Unit test for RaceLoader** - Write test in tests/utests/ that loads human.json, verifies parsed data matches expected values
3. **Inheritance test** - Load high_elf.json, verify ability_mods contains both elf's +2 dex and high_elf's +1 int
4. **Character creation test** - Update tests/utests/character/humanCharacterTests.cpp to create character with JSON-loaded race, verify abilities and params applied correctly
5. **Per-level benefit test** - Create hill_dwarf character, level up, verify hit_point max increases by 1
6. **Dynamic race addition** - Create custom race JSON with new race definition, load without recompiling, verify factory can create it

---

### Decisions

- **Inheritance merging strategy**: Child race fields override or append to parent's (e.g., ability_mods with "action": "add" appends, no action overrides)
- **Scope boundary**: This plan handles loading and applying race benefits at character creation and level-up. Does NOT include runtime trait triggering (e.g., halfling "lucky" reroll mechanic) - that remains for future work
- **Error handling**: RaceLoader should throw exceptions for missing files, invalid JSON, or unresolved base_race references
- **Factory behavior**: Remove g_racesVector checks - any race in JSON directory is valid
- **CustomRace class**: Remove entirely, replaced by JSON system

---

### Further Considerations

1. **Storage of complex traits** - Traits like "lucky" have trigger_condition and allow_action. Should we create a Trait handler system now, or just store JSON data for future implementation? **Recommendation**: Store as RaceData for now, implement trigger logic in separate future task.
2. **Proficiency application** - Some races grant weapon/armor proficiency. Character class doesn't currently track proficiencies. Should we add full proficiency system now? **Recommendation**: Add storage fields to Character, but don't implement proficiency-checking logic yet.
3. **nlohmann/json version** - Use single-header v3.11.3 (latest stable) or system package manager? **Recommendation**: Single-header for portability unless project already uses package manager for dependencies.
