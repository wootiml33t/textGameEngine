#ifndef _HUMANOID
#define _HUMANOID
#include "cc3.h"
#include "voc.h"
#include "dice.h"
#include "armor.h"
#include "wpn.h"
#include <vector>
#include <string>
class Humanoid: public CreatureClass
{
    private:
    static const int NUM_INIT_SK;/////////////////////////////
    static const string INITSKILLS[5][3];
    
    VocRules::VocType voc;
    int level;
    long gp;
    long xp;
    vector<EquipClass*> pack;    
    Humanoid();
    int AttackBonus() const;
    //bool CkPromotion() const; //Prolly dont need this but whynot
    
    protected:
    static const int SKILL_DIE_NUM;
    static const int SKILL_DIE_FACES;
    static const int GP_DIE_NUM;
    static const int GP_DIE_FACES;
    static const int HUMANOID_HP_DIE_NUM;
    static const int LEVEL_START; 
    static const int XP_START;
    Humanoid(string name, VocRules::VocType voc);
    Humanoid(const Humanoid& h);
    void CopyIntoMe(const Humanoid& h);
    void InitVoc(VocRules::VocType v, VocRules::VocType defVoc);
    //void InitAbilities(int abilAdj);
    void InitLevel(int mod);
    void InitGP(int mod);
    void InitXP(int mod);
    void InitHP(int mod);
    void InitSkills(vector<string> skills);
    int HitDie() const;
    EquipClass* FindAndRemoveFromPack(string item);
    EquipClass* SwapAndMoveToPack(EquipClass* equip);
    void EmptyPack();
    
    public:
    ~Humanoid();
    int Voc() const;
    string Voc_Str() const;
    int Level() const;
    long GP() const;
    long XP() const;
    vector<string> Pack() const;
    vector<string> EquipInventory() const;
    virtual vector<string> EquipInitialList() const =0;
    EquipClass* FindEquipment(EquipClass* equipment);
    virtual WeaponClass* FindWeapon(WeaponClass* wpn);
    virtual ArmorClass* FindArmor(ArmorClass* armor);
    bool ChangeEquipment(string equipname);
    EquipClass* BuyEquipment(EquipClass* equip);
    EquipClass* SellEquipment(string name);
    int AttackRoll() const;
    int SavingThrow(SavingThrowType kind) const;
    long UpdateGP(long val);
    long UpdateXP(long val);
    virtual void Write(ostream& stream) const;
    Humanoid& operator=(const Humanoid& h);
    void CopyHelp(const Humanoid& h);
};
#endif
