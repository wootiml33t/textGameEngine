//Over loaded << doe snot work
#ifndef _CC
#define _CC
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include "voc.h"
#include "dice.h"
#include "armor.h"
#include "wpn.h"
class CreatureClass
{    
    protected:
    static const int NUMBER_OF_ABILITIES;
    static const int DISABLED_HP;
    static const int DEAD_HP;
    static const int HP_START;
    static const int VOC_MAX;
    CreatureClass(string name);
    CreatureClass(const CreatureClass& c);
    void CopyIntoMe(const CreatureClass& c);
    void InitName(string name);
    void InitSkills(vector<string> sk);
    void InitHP(int val);
    void InitAbilities(vector<int> abil);
    int RollHitDie(int numRolls, int faces, int mod) const;
    CreatureClass& operator=(const CreatureClass& c);
    WeaponClass* creatureWeapon;
    ArmorClass* creatureArmor;
             
    
    public:
    ~CreatureClass();
    enum AbilityType
    {
        DEX,
        CON, 
        INT,
        CHA,
        STR,
        WIS
    };

    string Name() const;
    int Row() const;
    int Col() const;
    int HP() const;
    int Ability(AbilityType abil) const;
    vector<int> Abilities() const;
    int AbilityMod(AbilityType ability) const;
    string Weapon() const;
    string Armor() const;
    vector<string> Skills() const;
    bool Active() const;
    bool Dead() const;
    bool Dying() const;
    bool Disabled() const;
    bool HasWeapon() const;
    bool HasArmor() const;
    int UpdateHP(int mod);
    bool SetCell(int row, int col);
    int SkillCheck(string skill) const;
    bool ValidSkill(string skill) const;
    bool AddSkill(string skill);
    void Amnesia();
    //virtual vector<string> EquipIntitialList() const =0;
    WeaponClass* LoseWeapon();
    ArmorClass* LoseArmor();
    virtual EquipClass* FindEquipment(EquipClass* equipment) =0;
    virtual WeaponClass* FindWeapon(WeaponClass* wpn);
    virtual ArmorClass* FindArmor(ArmorClass* armor);
    int InitiativeCheck() const;
    virtual int AttackRoll() const =0;
    virtual int SavingThrow(SavingThrowType kind) const =0;
    int Defense() const;
    int Damage() const;
    virtual void Write(ostream& out) const;
    bool operator==(CreatureClass& c) const;
    bool operator!=(CreatureClass& c) const;
    bool operator<(CreatureClass& c) const;
    bool operator<=(CreatureClass& c) const;
    bool operator>(CreatureClass& c) const;
    bool operator>=(CreatureClass& c) const;  
    
    private:
    struct SkillRec
    {
        string skill;
        AbilityType abil;
    };
    static const int ROW_START;
    static const int COL_START;
    void SkillInit();
    string name;
    int row;
    int col;
    int hp;
    vector<int> abilities;
    vector<pair<string,AbilityType> > sktable;
    vector<string> skills;
    CreatureClass();
    vector<SkillRec> SkillsTable;
    static const string DEF_NAME;
};
#endif
