#include "humanoid_races.h"
//using namespace std;
const string Human::RACE = "HUMAN";
int Human::ABILITY_ADJ[6] =
{
    0,0,0,0,0,0
}; 
const string Human::INIT_EQUIP[6][NUM_INIT_EQUIP] =
{
    {"STUDDED LEATHER", "DAGGER", "SHORT BOW"},
    {"LARGE WOODEN SHIELD", "CROSSBOW", "MACE"},
    {"LARGE WOODEN SHIELD", "SWORD", ""},
    {"LEATHER JACKET", "RAPIER", "SHORT BOW"},
    {"CLUB", "DAGGER", "LIGHT CROSSBOW"}
};
Human::~Human()
{
}
Human::Human()
:Humanoid("", DEFAULT_VOC)
{
    vector<int> tempabils;
    for (int i = 0; i < NUMBER_OF_ABILITIES; i++)
    {
       GameSpace::RollType abilityenum = static_cast<GameSpace::RollType>(i);
       tempabils.push_back((Dice::Roll(Name(), abilityenum, SKILL_DIE_NUM, SKILL_DIE_FACES)) + ABILITY_ADJ[i]);
    }           
    InitAbilities(tempabils);
    /*                                          
    EquipClass* ePtr = NULL;
    for (int i = 0; i < NUM_INIT_EQUIP; i++)
    {
        if (WeaponClass::IsEquipment(INIT_EQUIP[DEFAULT_VOC][i])) //Weapon
        {
            ePtr = reinterpret_cast<EquipClass*>(WeaponClass::StrToWeapon(INIT_EQUIP[DEFAULT_VOC][i])); //reinterprut m,ay not work how i like
            Humanoid::FindEquipment(ePtr);
        }
        else //Armor
        {
            ePtr = reinterpret_cast<EquipClass*>(ArmorClass::StrToArmor(INIT_EQUIP[DEFAULT_VOC][i]));
            Humanoid::FindEquipment(ePtr);
        }
    }
    */
    VocRules *vrPtr = VocRules::GetVocRules();
    //VocRules::VocType vocenum = static_cast<VocRules::VocType>(Voc());
    //CreatureClass::InitHP((Dice::Roll(Name(), GameSpace::HP, HUMANOID_HP_DIE_NUM, vrPtr->HitDie(DEFAULT_VOC)) + AbilityMod(CON)));
    int hptemp = (Dice::Roll(Name(), GameSpace::HP, HUMANOID_HP_DIE_NUM, vrPtr->HitDie(DEFAULT_VOC)) + AbilityMod(CON));
    if (hptemp <= 0)
    {
        hptemp = 1;
    }
    CreatureClass::InitHP(hptemp);
    Humanoid::InitXP(0);                     
}
Human::Human(string name, VocRules::VocType voc/* = DEFAULT_VOC*/)
:Humanoid(name, voc)
{  
/* 
    cout << voc << " " << name << endl;
    vector<int> tempabils;
    for (int i = 0; i < NUMBER_OF_ABILITIES; i++)
    {
       GameSpace::RollType abilityenum = static_cast<GameSpace::RollType>(i);
       tempabils.push_back((Dice::Roll(Name(), abilityenum, SKILL_DIE_NUM, SKILL_DIE_FACES)) + ABILITY_ADJ[i]);
    }           
    InitAbilities(tempabils);
    /*             
    EquipClass* ePtr = NULL;
    for (int i = 0; i < NUM_INIT_EQUIP; i++)
    {
             
        if (WeaponClass::IsEquipment(INIT_EQUIP[DEFAULT_VOC][i])) //Weapon
        {
             
            ePtr = reinterpret_cast<EquipClass*>(WeaponClass::StrToWeapon(INIT_EQUIP[Humanoid::Voc()][i]));
            //cout << "poop" << endl;
            //Humanoid::FindEquipment(ePtr); SEGFAULTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTt
            
        }
        else //Armor
        {
             
            ePtr = reinterpret_cast<EquipClass*>(ArmorClass::StrToArmor(INIT_EQUIP[Humanoid::Voc()][i]));
            //cout << "poop" << endl;
            //Humanoid::FindEquipment(ePtr);
        }
    }
    */
    /*
    VocRules *vrPtr = VocRules::GetVocRules();
    VocRules::VocType vocenum = static_cast<VocRules::VocType>(Voc());
    int thp = 0;
    thp += Dice::Roll(Name(), GameSpace::HP, HUMANOID_HP_DIE_NUM, vrPtr->HitDie(vocenum));// + AbilityMod(CON))
    thp += Ability(CON);
    cout << thp << endl;
    CreatureClass::InitHP(thp);
    Humanoid::InitXP(0);
    */
    Humanoid::InitVoc(voc,voc);
    vector<int> tempabils;
    for (int i = 0; i < NUMBER_OF_ABILITIES; i++)
    {
       GameSpace::RollType abilityenum = static_cast<GameSpace::RollType>(i);
       tempabils.push_back((Dice::Roll(Name(), abilityenum, SKILL_DIE_NUM, SKILL_DIE_FACES)) + ABILITY_ADJ[i]);
    }           
    InitAbilities(tempabils);
    VocRules *vrPtr = VocRules::GetVocRules();
    int hptemp = (Dice::Roll(Name(), GameSpace::HP, HUMANOID_HP_DIE_NUM, ((vrPtr->HitDie(voc)) ? (vrPtr->HitDie(voc)) : 10 )/*this is a ternary operator, I should be able to remove this if I can get the exception thing to work*/ ) + AbilityMod(CON));
   // zimmer edit need to update after reset of hptemp
//    CreatureClass::InitHP(hptemp);
    if (hptemp <= 0)
    {
        hptemp = 1;
    }
    CreatureClass::InitHP(hptemp);
    //CreatureClass::InitHP(1);
    Humanoid::InitXP(0);                         
}
string Human::Race_Str() const
{
    return RACE;
}
vector<string> Human::EquipInitialList() const
{
    vector<string> equipList;
    for (int i = 0; i < NUM_INIT_EQUIP; i++) 
    {
        equipList.push_back(INIT_EQUIP[Humanoid::Voc()-1][i]);
    }
    return equipList;      
}

void Human::Write(ostream& out) const
{
    out << Race_Str() << '#';
    Humanoid::Write(out);
  /*  vector<int> abil = Abilities();
    vector<string> skil = Skills();
    vector<string> pak = Pack();
    out << Race_Str() << "#" << Voc_Str()<< "#" << Name() << "#(" << Row()<< "," << Col() << ")#" << HP() << "[";
    for (int i = 0; i < 6; i++)
    {
        if(i != 5)
        {
            out << abil[i] << ",";
        }
        else
        {
            out << abil[i] << "]#(";
        }
    }
    for (int i = 0; i < skil.size(); i++)
    {
        if (i != ((skil.size())-1))
        {
            out << skil[i] << ",";
        }
        else
        {
            out << skil[i] << ")#";
        }
    }
    out << Armor() << "#" << Weapon() << "#" << '\n' << '\t' << Level() << "#" << XP() << "#" << GP() << "#(";
    for (int i = 0; i < pak.size(); i++)
    {
        if ( i != ((pak.size())-1))
        {
            out << pak[i] << ",";
        }
        else
        {
            out << pak[i] << ")#" << '\n';
        }
    }*/                                                                                                                                                                                                                               
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const string Elf::RACE = "ELF";
int Elf::ABILITY_ADJ[6] =
{
    2,-2,0,0,0,0
};
const string Elf::INIT_EQUIP[6][NUM_INIT_EQUIP] =
{
    {"STUDDED LEATHER", "DAGGER", "SHORT BOW"},
    {"LARGE WOODEN SHIELD", "LONG SWORD", "SHORT BOW"},
    {"SMALL WOODEN SHIELD", "SWORD", ""},
    {"LEATHER JACKET", "RAPIER", "SHORT BOW"},
    {"SHORT BOW", "QUARTER STAFF", ""}
};
Elf::~Elf()
{
}
Elf::Elf()
:Humanoid("",DEFAULT_VOC)
{/*
    vector<int> tempabils;
    for (int i = 0; i < NUMBER_OF_ABILITIES; i++)
    {
       GameSpace::RollType abilityenum = static_cast<GameSpace::RollType>(i);
       tempabils.push_back((Dice::Roll(Name(), abilityenum, SKILL_DIE_NUM, SKILL_DIE_FACES)) + ABILITY_ADJ[i]);
    }           
    InitAbilities(tempabils);
    /*
    EquipClass* ePtr = NULL;
    for (int i = 0; i < NUM_INIT_EQUIP; i++)
    {
        if (WeaponClass::IsEquipment(INIT_EQUIP[DEFAULT_VOC][i])) //Weapon
        {
            ePtr = reinterpret_cast<EquipClass*>(WeaponClass::StrToWeapon(INIT_EQUIP[DEFAULT_VOC][i])); //reinterprut m,ay not work how i like
            Humanoid::FindEquipment(ePtr);
        }
        else //Armor
        {
            ePtr = reinterpret_cast<EquipClass*>(ArmorClass::StrToArmor(INIT_EQUIP[DEFAULT_VOC][i]));
            Humanoid::FindEquipment(ePtr);
        }
    }
    *//*
    VocRules *vrPtr = VocRules::GetVocRules();
    VocRules::VocType vocenum = static_cast<VocRules::VocType>(Voc());
    int thp = 0;
    thp += Dice::Roll(Name(), GameSpace::HP, HUMANOID_HP_DIE_NUM, vrPtr->HitDie(vocenum));// + AbilityMod(CON))
    thp += Ability(CON);
    CreatureClass::InitHP(thp);
    Humanoid::InitXP(0); 
    
  */  
    VocRules *vrPtr = VocRules::GetVocRules();
    //VocRules::VocType vocenum = static_cast<VocRules::VocType>(Voc());
    CreatureClass::InitHP((Dice::Roll(Name(), GameSpace::HP, HUMANOID_HP_DIE_NUM, vrPtr->HitDie(DEFAULT_VOC)) + AbilityMod(CON)));
    Humanoid::InitXP(0);                    
}
Elf::Elf(string name, VocRules::VocType voc /* = DEFAULT_VOC*/)
:Humanoid(name, voc)
{
/*
    vector<int> tempabils;
    for (int i = 0; i < NUMBER_OF_ABILITIES; i++)
    {
       GameSpace::RollType abilityenum = static_cast<GameSpace::RollType>(i);
       tempabils.push_back((Dice::Roll(Name(), abilityenum, SKILL_DIE_NUM, SKILL_DIE_FACES)) + ABILITY_ADJ[i]);
    }           
    InitAbilities(tempabils);
    /*
    EquipClass* ePtr = NULL;
    for (int i = 0; i < NUM_INIT_EQUIP; i++)
    {
        if (WeaponClass::IsEquipment(INIT_EQUIP[DEFAULT_VOC][i])) //Weapon
        {
            ePtr = reinterpret_cast<EquipClass*>(WeaponClass::StrToWeapon(INIT_EQUIP[Humanoid::Voc()][i]));
            Humanoid::FindEquipment(ePtr);
        }
        else //Armor
        {
            ePtr = reinterpret_cast<EquipClass*>(ArmorClass::StrToArmor(INIT_EQUIP[Humanoid::Voc()][i]));
            Humanoid::FindEquipment(ePtr);
        }
    }
    *//*
    VocRules *vrPtr = VocRules::GetVocRules();
    VocRules::VocType vocenum = static_cast<VocRules::VocType>(Voc());
    int thp = 0;
    thp += Dice::Roll(Name(), GameSpace::HP, HUMANOID_HP_DIE_NUM, vrPtr->HitDie(vocenum));// + AbilityMod(CON))
    thp += Ability(CON); 
    CreatureClass::InitHP(thp);
    Humanoid::InitXP(0);
   */
    int hptemp = 0; 
    vector<int> tempabils;
    for (int i = 0; i < NUMBER_OF_ABILITIES; i++)
    {
       GameSpace::RollType abilityenum = static_cast<GameSpace::RollType>(i);
       tempabils.push_back((Dice::Roll(Name(), abilityenum, SKILL_DIE_NUM, SKILL_DIE_FACES)) + ABILITY_ADJ[i]);
    }           
    InitAbilities(tempabils);
    VocRules *vrPtr = VocRules::GetVocRules();
    hptemp = Dice::Roll(Name(), GameSpace::HP, HUMANOID_HP_DIE_NUM, vrPtr->HitDie(voc)) + AbilityMod(CON);
    if (hptemp <= 0)
    {
        hptemp = 1;
    }
    CreatureClass::InitHP(hptemp);
    Humanoid::InitXP(0);                      
}
string Elf::Race_Str() const
{
    return RACE;
}
vector<string> Elf::EquipInitialList() const
{
    vector<string> equipList;
    for (int i = 0; i < NUM_INIT_EQUIP; i++) 
    {
        equipList.push_back(INIT_EQUIP[Humanoid::Voc()-1][i]);
    }
    return equipList;      
}
void Elf::Write(ostream& out) const
{
    out << Race_Str() << '#';
    Humanoid::Write(out);
   /* vector<int> abil = Abilities();
    vector<string> skil = Skills();
    vector<string> pak = Pack();
    out << Race_Str() << "#" << Voc_Str()<< "#" << Name() << "#(" << Row()<< "," << Col() << ")#" << HP() << "[";
    for (int i = 0; i < 6; i++)
    {
        if(i != 5)
        {
            out << abil[i] << ",";
        }
        else
        {
            out << abil[i] << "]#(";
        }
    }
    for (int i = 0; i < skil.size(); i++)
    {
        if (i != ((skil.size())-1))
        {
            out << skil[i] << ",";
        }
        else
        {
            out << skil[i] << ")#";
        }
    }
    out << Armor() << "#" << Weapon() << "#" << '\n' << '\t' << Level() << "#" << XP() << "#" << GP() << "#(";
    for (int i = 0; i < pak.size(); i++)
    {
        if ( i != ((pak.size())-1))
        {
            out << pak[i] << ",";
        }
        else
        {
            out << pak[i] << ")#" << '\n';
        }
    }*/                                                                                                                                                                                                                               
}
    
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const string HalfElf::RACE = "HALFELF";
int HalfElf::ABILITY_ADJ[6] =
{
    0,0,0,0,0,0   
};
const string HalfElf::INIT_EQUIP[6][NUM_INIT_EQUIP] =
{
    {"STUDDED LEATHER", "DAGGER", "SHORT BOW"},
    {"SMALL WOODEN SHIELD", "LONG SWORD", ""},
    {"SMALL WOODEN SHIELD", "SWORD", ""},
    {"LEATHER JACKET", "RAPIER", "SHORT BOW"},
    {"CLUB", "LIGHT CROSSBOW", ""}
}; 
HalfElf::~HalfElf()
{
}
HalfElf::HalfElf()
:Humanoid("",DEFAULT_VOC)
{/*
    vector<int> tempabils;
    for (int i = 0; i < NUMBER_OF_ABILITIES; i++)
    {
       GameSpace::RollType abilityenum = static_cast<GameSpace::RollType>(i);
       tempabils.push_back((Dice::Roll(Name(), abilityenum, SKILL_DIE_NUM, SKILL_DIE_FACES)) + ABILITY_ADJ[i]);
    }           
    InitAbilities(tempabils);
    /*
    EquipClass* ePtr = NULL;
    for (int i = 0; i < NUM_INIT_EQUIP; i++)
    {
        if (WeaponClass::IsEquipment(INIT_EQUIP[DEFAULT_VOC][i])) //Weapon
        {
            ePtr = reinterpret_cast<EquipClass*>(WeaponClass::StrToWeapon(INIT_EQUIP[DEFAULT_VOC][i])); //reinterprut m,ay not work how i like
            Humanoid::FindEquipment(ePtr);
        }
        else //Armor
        {
            ePtr = reinterpret_cast<EquipClass*>(ArmorClass::StrToArmor(INIT_EQUIP[DEFAULT_VOC][i]));
            Humanoid::FindEquipment(ePtr);
        }
    }
    *//*
    VocRules *vrPtr = VocRules::GetVocRules();
    VocRules::VocType vocenum = static_cast<VocRules::VocType>(Voc());
    int thp = 0;
    thp += Dice::Roll(Name(), GameSpace::HP, HUMANOID_HP_DIE_NUM, vrPtr->HitDie(vocenum));// + AbilityMod(CON))
    thp += Ability(CON); 
    CreatureClass::InitHP(thp);
    Humanoid::InitXP(0); 
   */ 
    VocRules *vrPtr = VocRules::GetVocRules();
    //VocRules::VocType vocenum = static_cast<VocRules::VocType>(Voc());
    CreatureClass::InitHP((Dice::Roll(Name(), GameSpace::HP, HUMANOID_HP_DIE_NUM, vrPtr->HitDie(DEFAULT_VOC)) + AbilityMod(CON)));
    Humanoid::InitXP(0);                        
}
HalfElf::HalfElf(string name, VocRules::VocType voc /* = DEFAULT_VOC*/)
:Humanoid(name, voc)
{/*
    vector<int> tempabils;
    for (int i = 0; i < NUMBER_OF_ABILITIES; i++)
    {
       GameSpace::RollType abilityenum = static_cast<GameSpace::RollType>(i);
       tempabils.push_back((Dice::Roll(Name(), abilityenum, SKILL_DIE_NUM, SKILL_DIE_FACES)) + ABILITY_ADJ[i]);
    }           
    InitAbilities(tempabils);
    /*
    EquipClass* ePtr = NULL;
    for (int i = 0; i < NUM_INIT_EQUIP; i++)
    {
        if (WeaponClass::IsEquipment(INIT_EQUIP[DEFAULT_VOC][i])) //Weapon
        {
            ePtr = reinterpret_cast<EquipClass*>(WeaponClass::StrToWeapon(INIT_EQUIP[Humanoid::Voc()][i]));
            Humanoid::FindEquipment(ePtr);
        }
        else //Armor
        {
            ePtr = reinterpret_cast<EquipClass*>(ArmorClass::StrToArmor(INIT_EQUIP[Humanoid::Voc()][i]));
            Humanoid::FindEquipment(ePtr);
        }
    }
    *//*
    VocRules *vrPtr = VocRules::GetVocRules();
    VocRules::VocType vocenum = static_cast<VocRules::VocType>(Voc());
    int thp = 0;
    thp += Dice::Roll(Name(), GameSpace::HP, HUMANOID_HP_DIE_NUM, vrPtr->HitDie(vocenum));// + AbilityMod(CON))
    thp += Ability(CON); 
    CreatureClass::InitHP(thp);
    Humanoid::InitXP(0); 
  */  
    vector<int> tempabils;
    for (int i = 0; i < NUMBER_OF_ABILITIES; i++)
    {
       GameSpace::RollType abilityenum = static_cast<GameSpace::RollType>(i);
       tempabils.push_back((Dice::Roll(Name(), abilityenum, SKILL_DIE_NUM, SKILL_DIE_FACES)) + ABILITY_ADJ[i]);
    }           
    InitAbilities(tempabils);
    VocRules *vrPtr = VocRules::GetVocRules();
    CreatureClass::InitHP((Dice::Roll(Name(), GameSpace::HP, HUMANOID_HP_DIE_NUM, vrPtr->HitDie(voc)) + AbilityMod(CON)));
    Humanoid::InitXP(0);                    
}
string HalfElf::Race_Str() const
{
    return RACE;
}
vector<string> HalfElf::EquipInitialList() const
{
    vector<string> equipList;
    for (int i = 0; i < NUM_INIT_EQUIP; i++) 
    {
        equipList.push_back(INIT_EQUIP[Humanoid::Voc()-1][i]);
    }
    return equipList;      
}
void HalfElf::Write(ostream& out) const
{
    out << Race_Str() << '#';
    Humanoid::Write(out);
   /* vector<int> abil = Abilities();
    vector<string> skil = Skills();
    vector<string> pak = Pack();
    out << Race_Str() << "#" << Voc_Str()<< "#" << Name() << "#(" << Row()<< "," << Col() << ")#" << HP() << "[";
    for (int i = 0; i < 6; i++)
    {
        if(i != 5)
        {
            out << abil[i] << ",";
        }
        else
        {
            out << abil[i] << "]#(";
        }
    }
    for (int i = 0; i < skil.size(); i++)
    {
        if (i != ((skil.size())-1))
        {
            out << skil[i] << ",";
        }
        else
        {
            out << skil[i] << ")#";
        }
    }
    out << Armor() << "#" << Weapon() << "#" << '\n' << '\t' << Level() << "#" << XP() << "#" << GP() << "#(";
    for (int i = 0; i < pak.size(); i++)
    {
        if ( i != ((pak.size())-1))
        {
            out << pak[i] << ",";
        }
        else
        {
            out << pak[i] << ")#" << '\n';
        }
    } */                                                                                                                                                                                                                              
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string Orc::RACE = "ORC";
int Orc::ABILITY_ADJ[6] =
{
    0,0,-2,-2,2,-1
};
const string Orc::INIT_EQUIP[6][NUM_INIT_EQUIP] =
{
    {"STUDDED LEATHER", "DAGGER", "GREAT AXE", "SHORT BOW"},
    {"CROSSBOW", "SHORT SPEAR", "", ""},
    {"LARGE WOODEN SHIELD", "SWORD", "", ""},
    {"LEATHER JACKET", "RAPIER", "SHORT BOW", ""},
    {"CLUB", "LIGHT CROSSBOW", "", ""}
};
Orc::~Orc()
{
}
Orc::Orc()
:Humanoid("",DEFAULT_VOC)
{
/*    vector<int> tempabils;
    for (int i = 0; i < NUMBER_OF_ABILITIES; i++)
    {
       GameSpace::RollType abilityenum = static_cast<GameSpace::RollType>(i);
       tempabils.push_back((Dice::Roll(Name(), abilityenum, SKILL_DIE_NUM, SKILL_DIE_FACES)) + ABILITY_ADJ[i]);
    }           
    InitAbilities(tempabils);
    /*
    EquipClass* ePtr = NULL;
    for (int i = 0; i < NUM_INIT_EQUIP; i++)
    {
        if (WeaponClass::IsEquipment(INIT_EQUIP[DEFAULT_VOC][i])) //Weapon
        {
            ePtr = reinterpret_cast<EquipClass*>(WeaponClass::StrToWeapon(INIT_EQUIP[DEFAULT_VOC][i])); //reinterprut m,ay not work how i like
            Humanoid::FindEquipment(ePtr);
        }
        else //Armor
        {
            ePtr = reinterpret_cast<EquipClass*>(ArmorClass::StrToArmor(INIT_EQUIP[DEFAULT_VOC][i]));
            Humanoid::FindEquipment(ePtr);
        }
    }
    */
    /*
    VocRules *vrPtr = VocRules::GetVocRules();
    VocRules::VocType vocenum = static_cast<VocRules::VocType>(Voc());
    int thp = 0;
    thp += Dice::Roll(Name(), GameSpace::HP, HUMANOID_HP_DIE_NUM, vrPtr->HitDie(vocenum));// + AbilityMod(CON))
    thp += Ability(CON); 
    CreatureClass::InitHP(thp);
    Humanoid::InitXP(0);
    
    */
    VocRules *vrPtr = VocRules::GetVocRules();
    //VocRules::VocType vocenum = static_cast<VocRules::VocType>(Voc());
    CreatureClass::InitHP((Dice::Roll(Name(), GameSpace::HP, HUMANOID_HP_DIE_NUM, vrPtr->HitDie(DEFAULT_VOC)) + AbilityMod(CON)));
    Humanoid::InitXP(0);
            
}
Orc::Orc(string name, VocRules::VocType voc /* = DEFAULT_VOC*/)
:Humanoid(name, voc)
{/*
    vector<int> tempabils;
    for (int i = 0; i < NUMBER_OF_ABILITIES; i++)
    {
       GameSpace::RollType abilityenum = static_cast<GameSpace::RollType>(i);
       tempabils.push_back((Dice::Roll(Name(), abilityenum, SKILL_DIE_NUM, SKILL_DIE_FACES)) + ABILITY_ADJ[i]);
    }           
    InitAbilities(tempabils);
    /*
    EquipClass* ePtr = NULL;
    for (int i = 0; i < NUM_INIT_EQUIP; i++)
    {
        if (WeaponClass::IsEquipment(INIT_EQUIP[DEFAULT_VOC][i])) //Weapon
        {
            ePtr = reinterpret_cast<EquipClass*>(WeaponClass::StrToWeapon(INIT_EQUIP[Humanoid::Voc()][i]));
            Humanoid::FindEquipment(ePtr);
        }
        else //Armor
        {
            ePtr = reinterpret_cast<EquipClass*>(ArmorClass::StrToArmor(INIT_EQUIP[Humanoid::Voc()][i]));
            Humanoid::FindEquipment(ePtr);
        }
    }
    */
    /*
    VocRules *vrPtr = VocRules::GetVocRules();
    VocRules::VocType vocenum = static_cast<VocRules::VocType>(Voc());
    int thp = 0;
    thp += Dice::Roll(Name(), GameSpace::HP, HUMANOID_HP_DIE_NUM, vrPtr->HitDie(vocenum));// + AbilityMod(CON))
    thp += Ability(CON);
    CreatureClass::InitHP(thp);
    Humanoid::InitXP(0);
    */
    vector<int> tempabils;
    for (int i = 0; i < NUMBER_OF_ABILITIES; i++)
    {
       GameSpace::RollType abilityenum = static_cast<GameSpace::RollType>(i);
       tempabils.push_back((Dice::Roll(Name(), abilityenum, SKILL_DIE_NUM, SKILL_DIE_FACES)) + ABILITY_ADJ[i]);
    }           
    InitAbilities(tempabils);
    VocRules *vrPtr = VocRules::GetVocRules();
    CreatureClass::InitHP((Dice::Roll(Name(), GameSpace::HP, HUMANOID_HP_DIE_NUM, vrPtr->HitDie(voc)) + AbilityMod(CON)));
    Humanoid::InitXP(0);                     
}
string Orc::Race_Str() const
{
    return RACE;
}
vector<string> Orc::EquipInitialList() const
{
    vector<string> equipList;
    for (int i = 0; i < NUM_INIT_EQUIP; i++) 
    {
        equipList.push_back(INIT_EQUIP[Humanoid::Voc()-1][i]);
    }
    return equipList;      
}
void Orc::Write(ostream& out) const
{
    out << Race_Str() << '#';
    Humanoid::Write(out);
    /*
    vector<int> abil = Abilities();
    vector<string> skil = Skills();
    vector<string> pak = Pack();
    out << Race_Str() << "#" << Voc_Str()<< "#" << Name() << "#(" << Row()<< "," << Col() << ")#" << HP() << "[";
    for (int i = 0; i < 6; i++)
    {
        if(i != 5)
        {
            out << abil[i] << ",";
        }
        else
        {
            out << abil[i] << "]#(";
        }
    }
    for (int i = 0; i < skil.size(); i++)
    {
        if (i != ((skil.size())-1))
        {
            out << skil[i] << ",";
        }
        else
        {
            out << skil[i] << ")#";
        }
    }
    out << Armor() << "#" << Weapon() << "#" << '\n' << '\t' << Level() << "#" << XP() << "#" << GP() << "#(";
    for (int i = 0; i < pak.size(); i++)
    {
        if ( i != ((pak.size())-1))
        {
            out << pak[i] << ",";
        }
        else
        {
            out << pak[i] << ")#" << '\n';
        }
    } 
    */                                                                                                                                                                                                                              
}

