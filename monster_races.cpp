#include "monster_races.h"
#include "voc.h"
#include "dice.h"
#include "armor.h"
#include "wpn.h"
EquipClass* Troll::FindEquipment(EquipClass* equipment)
{
// zimmer edited this method
// this should be in creatureClass!     
    if (Active())
    {
        WeaponClass* wptr = dynamic_cast<WeaponClass*>(equipment);
        ArmorClass* aptr = dynamic_cast<ArmorClass*>(equipment);
        if(aptr)
        {
            // this is local: aptr = creatureArmor;
            equipment = CreatureClass::FindArmor(aptr);
            //pack.push_back(aptr);
        }
        else if (wptr)
        {
            //wptr = creatureWeapon;
            equipment = CreatureClass::FindWeapon(wptr);
            //pack.push_back(wptr);
        }
    }
    else
    {
        return equipment;
    }
    return equipment;
}

const string Troll::RACE = "TROLL";
const int Troll::ABILITY_ADJ[6] =
{
    14,23,6,6,23,9
};
const int Troll::HIT_DIE[3] =
{
    6,8,36
};
const int Troll::SAVE_THROW[3] =
{
    11,4,3
};
const int Troll::BASE_ATT_BONUS[2] =
{
    9,1
};
const string Troll::INIT_EQUIP[2] =
{
    "THICK SKIN", "CLUB"
};
const string Troll::INIT_SKILLS[NUM_INIT_SK] =
{
    "LISTEN", "SPOT"
};
Troll::Troll()
:Monster("")
{  
    vector<string> tempsk;
    tempsk.push_back(INIT_SKILLS[0]);
    tempsk.push_back(INIT_SKILLS[1]);
    InitSkills(tempsk);
}
Troll::Troll(string name)
:Monster(name)
{
    vector<int> abilitiestobe;
    for(int i = 0; i < CreatureClass::NUMBER_OF_ABILITIES; i++)
    {        
        GameSpace::RollType abilityenum = static_cast<GameSpace::RollType>(i);
        abilitiestobe.push_back(ABILITY_ADJ[i]);
    }
    CreatureClass::InitAbilities(abilitiestobe);
    int thp = 0;
    thp += Dice::Roll(Name(), GameSpace::HP, HIT_DIE[0], HIT_DIE[1]);// + AbilityMod(CON))
    thp += HIT_DIE[2];
    CreatureClass::InitHP(thp);
    vector<string> tempsk;
    tempsk.push_back(INIT_SKILLS[0]);
    tempsk.push_back(INIT_SKILLS[1]);
    CreatureClass::InitSkills(tempsk);                           
    //Asssign wep and armor
    /*
    CreatureClass::FindWeapon(reinterpret_cast<WeaponClass*>(ArmorClass::StrToArmor(INIT_EQUIP[1])));
    CreatureClass::FindArmor(reinterpret_cast<ArmorClass*>(ArmorClass::StrToArmor(INIT_EQUIP[0])));
    */
}
vector<string> Troll::EquipInitialList() const
{
    vector<string> toRet;
    for (int i = 0; i < 2; i++)
    {
        toRet.push_back(INIT_EQUIP[i]);
    }
    return toRet;
}
int Troll::AttackRoll() const
{
    int toRet = 0;
    if (WeaponClass::IsRange(Weapon()))
    {
        toRet += ((BASE_ATT_BONUS[1])+(ABILITY_ADJ[CreatureClass::DEX]));
        toRet += Dice::Roll(CreatureClass::Name(), GameSpace::ATT, 1, 20);
    }
    else//is melee
    {
        toRet += ((BASE_ATT_BONUS[0])+(ABILITY_ADJ[CreatureClass::STR]));
        toRet += (Dice::Roll(CreatureClass::Name(), GameSpace::ATT, 1, 20));
    }
    return toRet;
}                                                                                                                                         
int Troll::SavingThrow(SavingThrowType kind) const
{
    int toRet = 0;
    switch (kind)
    {
        case FORT:
            toRet += AbilityMod(CON); 
            break;
        case REFLEX:
            toRet += AbilityMod(DEX);
            break;
        case WILL:
            toRet += AbilityMod(WIS);;
            break;
        default:
            throw GameSpace::INVALID_SAVINGTHROW; 
    }
    if(Active())
    {
       toRet += SAVE_THROW[kind-1];
       toRet += Dice::Roll(Name(),GameSpace::SVTH, 1, 20);
    }
    return toRet;
    //return 1;
}
void Troll::Write(ostream& out) const
{
// zimmer edit
// the race should output its character then call the next level up to do 
// the rest of the work... the next level does its work and then
// calls creatureclass.  CreatureClass does its work then returns... monster
//  does anything that might be left... then returns to race... and all that
// is left is the linefeed.

    out << this->Race_Str() << '#';
    Monster::Write(out);
    /*<< CreatureClass::Name() << '#' << '(' << CreatureClass::Row() << ',' << CreatureClass::Col() << ')' << '#' << CreatureClass::HP() << '#' << '[';
    for (int i = 0; i < 6; i++)
    {
        if (i < 5)
        {
            out << ABILITY_ADJ[i] << '#';
        }
        else 
        {
            out << ABILITY_ADJ[i] << "]#";
        }        
    }
    for (int i = 0; i < 2; i++)
    {
        if ( i < 1)
        {
            out << INIT_SKILLS[i] << ',';
        }
        else
        {
            out << INIT_SKILLS[i] << ")#";
        }
    }
    if (CreatureClass::HasArmor())
    {
        out << CreatureClass::Armor();
    }
    out << '#';
    if (CreatureClass::HasWeapon())
    {
        out << CreatureClass::Weapon();
    }*/
    out << endl;
    
}
string Troll::Race_Str() const
{
    return RACE;
}                                                      
/////////////////////////////////////////////////////////////////////////////////////
const string Ogre::RACE = "OGRE";
const int Ogre::ABILITY_ADJ[6] =
{
    8,15,6,7,21,10
};
const int Ogre::HIT_DIE[3] =
{
    4,8,8
};
const int Ogre::SAVE_THROW[3] =
{
    6,0,1
};
const int Ogre::BASE_ATT_BONUS[2] =
{
    8,1
};
const string Ogre::INIT_EQUIP[2] =
{
    "SPIKED BANDS", "SPEAR"
};
const string Ogre::INIT_SKILLS[NUM_INIT_SK] =
{
    "INTIMIDATE", "LISTEN", "SPOT"
};
//EquipClass* Ogre::FindEquipment(EquipClass* equipment)
EquipClass* Ogre::FindEquipment(EquipClass* equipment)
{
    if (Active())
    {//cout << "NAME: " << Name() << " ACTIVE" << endl;
        WeaponClass* wptr = dynamic_cast<WeaponClass*>(equipment);
        ArmorClass* aptr = dynamic_cast<ArmorClass*>(equipment);
        if(aptr)
        {
            aptr = FindArmor(aptr);
            //aptr = creatureArmor;//CreatureClass::FindArmor(aptr);
            //creatureArmor = equipment;
            //pack.push_back(aptr);
            return aptr;
        }
        else if (wptr)
        {
            wptr = FindWeapon(wptr);
            //wptr = creatureWeapon;//CreatureClass::FindWeapon(wptr);
            //creatureWeapon = equipment;
            //pack.push_back(wptr);
            return wptr;
        }
    }
    else
    {//cout << "NAME : " << Name() << "NOT ACTIVE" << endl;
        return equipment;
    }
    //return NULL;
}
Ogre::Ogre()
:Monster("")
{
    vector<string> tempsk;
    tempsk.push_back(INIT_SKILLS[0]);
    tempsk.push_back(INIT_SKILLS[1]);
    tempsk.push_back(INIT_SKILLS[2]);
    CreatureClass::InitSkills(tempsk);
}
Ogre::Ogre(string name)
:Monster(name)
{
    vector<int> abilitiestobe;
    for(int i = 0; i < CreatureClass::NUMBER_OF_ABILITIES; i++)
    {        
        GameSpace::RollType abilityenum = static_cast<GameSpace::RollType>(i);
        abilitiestobe.push_back(ABILITY_ADJ[i]);
    }
    CreatureClass::InitAbilities(abilitiestobe);
    int thp = 0;
    thp += Dice::Roll(Name(), GameSpace::HP, HIT_DIE[0], HIT_DIE[1]);// + AbilityMod(CON))
    thp += HIT_DIE[2];
    CreatureClass::InitHP(thp);
    vector<string> tempsk;
    tempsk.push_back(INIT_SKILLS[0]);
    tempsk.push_back(INIT_SKILLS[1]);
    tempsk.push_back(INIT_SKILLS[2]);
    CreatureClass::InitSkills(tempsk);
    /*
    WeaponClass* wptr = new WeaponClass(INIT_EQUIP[1]);
    ArmorClass* aptr = new ArmorClass(INIT_EQUIP[0]);;
    CreatureClass::FindWeapon(wptr);
    CreatureClass::FindArmor(aptr);
    */
}
vector<string> Ogre::EquipInitialList() const
{
    vector<string> toRet;
    for (int i = 0; i < 2; i++)
    {
        toRet.push_back(INIT_EQUIP[i]);
    }
    return toRet;
}                                                                                                                                         
int Ogre::SavingThrow(SavingThrowType kind) const
{
    int toRet = 0;
    switch (kind)
    {
        case FORT:
            toRet += AbilityMod(CON); 
            break;
        case REFLEX:
            toRet += AbilityMod(DEX);
            break;
        case WILL:
            toRet += AbilityMod(WIS);
            break; 
    }
    if(Active())
    {
       toRet += SAVE_THROW[kind-1];
       toRet += Dice::Roll(Name(),GameSpace::SVTH, 1, 20);
    }
    return toRet;
}
void Ogre::Write(ostream& out) const
{
 out << this->Race_Str() << '#';
    Monster::Write(out);
/*
    out << this->Race_Str() << '#'<< CreatureClass::Name() << '#' << '(' << CreatureClass::Row() << ',' << CreatureClass::Col() << ')' << '#' << CreatureClass::HP() << '#' << '[';
    for (int i = 0; i < 6; i++)
    {
        if (i < 5)
        {
            out << ABILITY_ADJ[i] << '#';
        }
        else 
        {
            out << ABILITY_ADJ[i] << "]#";
        }        
    }
    for (int i = 0; i < 3; i++)
    {
        if ( i < 2)
        {
            out << INIT_SKILLS[i] << ',';
        }
        else
        {
            out << INIT_SKILLS[i] << ")#";
        }
    }
    /*
    if (CreatureClass::HasArmor())
    {
        out << CreatureClass::Armor();
    }
    out << '#';
    if (CreatureClass::HasWeapon())
    {
        out << CreatureClass::Weapon();
    }*/
    //out << '#' << endl;
}
string Ogre::Race_Str() const
{
    return RACE;
}                                                                                    
int Ogre::AttackRoll() const
{
    int toRet = 0;
    if (WeaponClass::IsRange(Weapon()))
    {
        toRet += ((BASE_ATT_BONUS[1])+(ABILITY_ADJ[CreatureClass::DEX]));
        toRet += Dice::Roll(CreatureClass::Name(), GameSpace::ATT, 1, 20);
    }
    else//is melee
    {
        toRet += ((BASE_ATT_BONUS[0])+(ABILITY_ADJ[CreatureClass::STR]));
        toRet += (Dice::Roll(CreatureClass::Name(), GameSpace::ATT, 1, 20));
    }
    return toRet;
}                                                     
