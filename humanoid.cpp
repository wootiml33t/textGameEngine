#include "humanoid.h"
#include "voc.h"
#include "dice.h"
#include "armor.h"
#include "wpn.h"
//const int Humanoid::VOC_MAX = 6;
const int Humanoid::NUM_INIT_SK = 3;
const int Humanoid::SKILL_DIE_NUM = 3;
const int Humanoid::SKILL_DIE_FACES = 6;
const int Humanoid::GP_DIE_NUM = 1;
const int Humanoid::GP_DIE_FACES = 4;
const int Humanoid::HUMANOID_HP_DIE_NUM = 1;
const int Humanoid::LEVEL_START = 1; 
const int Humanoid::XP_START = 0; 
const string Humanoid::INITSKILLS[5][3] =
{
    {"CLIMB", "LISTEN", "SWIM"},
    {"HEAL", "USE MAGIC DEVICE", "@"},
    {"INTIMIDATE", "SWIM", "@"},
    {"BLUFF", "CLIMB", "HIDE"},
    {"CONCENTRATION", "HIDE", "USE MAGIC DEVICES"}
};
Humanoid::Humanoid()
:CreatureClass("")
{
}
Humanoid::Humanoid(string name, VocRules::VocType vocin)
:CreatureClass(name)
{
   switch (vocin)
   {
       case VocRules::BBN:
       case VocRules::CLR:
       case VocRules::FTR:
       case VocRules::ROG:
       case VocRules::WIZ:
           voc = vocin;
           break;
       default:
           throw GameSpace::INVALID_VOC;
           break;
   }
   level = LEVEL_START;
   gp = Dice::Roll(name, GameSpace::GP, GP_DIE_NUM, GP_DIE_FACES);
   vector<string> tempsk;
   for( int i = 0; i < 3; i++)
   {
       tempsk.push_back(INITSKILLS[(Humanoid::voc)-1][i]);
   }
   CreatureClass::InitSkills(tempsk);                                           
}
void Humanoid::InitVoc(VocRules::VocType vocin, VocRules::VocType v)
{
    voc = vocin; 
}
Humanoid::~Humanoid()
{
    for(int i = 0; i < pack.size(); i++)
    {
        delete(pack[i]);
    }
    pack.clear();
} 
EquipClass* Humanoid::FindEquipment(EquipClass* equipment)
{
    if (Active())
    {//cout << "NAME: " << Name() << "ALIVE" << endl;
        WeaponClass* wptr = dynamic_cast<WeaponClass*>(equipment);
        ArmorClass* aptr = dynamic_cast<ArmorClass*>(equipment);
        if(aptr)
        {
            aptr = CreatureClass::FindArmor(aptr);
            // zimmer edit - need to check if null before putting in pack
            if(aptr != NULL)
            {
                pack.push_back(aptr);
            }
        }
        else if (wptr)
        {
            wptr = CreatureClass::FindWeapon(wptr);
            // zimmer edit - need to check if null before putting in pack
            if (wptr != NULL)
            {
                pack.push_back(wptr);
            }
        }
    }
    else 
    {//cout << "NAME : " << Name() << "NOT ALIVE" << endl;
        return equipment;
    }
//    GameSpace::Sort(pack);
    return NULL;
    /*
    Creature finds equipment on the ground. 
    If equipment is not NULL the equipment that is passed in replaces the equipment 
    being worn or carried.  The equipment replaced is put back into the pack. 
    NULL is returned.  Creatures disabled or dying or dead cannot use found 
    equipment and should return the equipment sent in.
    */
}
void Humanoid::CopyHelp(const Humanoid& h)
{
    if(this != &h)
    {
        WeaponClass* wptr;
        ArmorClass* aptr;
        voc = h.voc;
        gp = h.gp;
        xp = h.xp;
        level = h.level;  
        for(int i = 0; i < pack.size(); i++)
        {
            delete pack[i];
        }
        pack.clear();
cout << pack.size() <<endl;
        for(int i =0; i < h.pack.size(); i++)
        {
            wptr = dynamic_cast<WeaponClass*>(h.pack[i]);
            aptr = dynamic_cast<ArmorClass*>(h.pack[i]);
            if(wptr)
            {
                pack.push_back(new WeaponClass(*wptr));
            }
            else if(aptr)
            {
                pack.push_back(new ArmorClass(*aptr));   
            }
            cout << pack.size()<<endl;
        }
    }
    return;
}
Humanoid& Humanoid::operator=(const Humanoid& h)
{
    CopyHelp(h);
    return *this;
}
Humanoid::Humanoid(const Humanoid& h)
:CreatureClass(h)
{
    CopyHelp(h);        
}    
long Humanoid::UpdateGP(long value)
{
    if (!((gp + value) < 0))
    {
        gp += value;
    }
    return gp;
}
long Humanoid::UpdateXP(long value)
{
    //VocRules::VocType voc = VocRules::FTR;                          // scope datatype and enumerated values
    VocRules *vrPtr = VocRules::GetVocRules();                      // Get ptr to singleton instance of VocRules
    int hitdie = vrPtr->HitDie(this->voc);                                // Use instance ptr to call instance method
    int xpNeeded = VocRules::XPforPromotion(level);                 // scope to call static method
    VocRules::VocType vocenum = static_cast<VocRules::VocType>(this->voc);
    if(value > 0)
    {
        xp += value;
        while((xp >= VocRules::XPforPromotion(level + 1)) && (level < 20))
        {
        // zimmer edit - use UpdateHP!
            CreatureClass::UpdateHP(AbilityMod(CON) + Dice::Roll(CreatureClass::Name(),GameSpace::HP,HUMANOID_HP_DIE_NUM, vrPtr->HitDie(vocenum)));
            if (this->HP() <= DISABLED_HP)
            {
                CreatureClass::InitHP(DISABLED_HP + 1);
            }
            InitLevel((this->Level()) + 1);
        }
    }
    return xp;
}
long Humanoid::XP() const
{
    return xp;
}
long Humanoid::GP() const
{
    return gp;
}
int Humanoid::Level() const
{
    return level;
}
int Humanoid::Voc() const
{
    return voc;
}
bool Humanoid::ChangeEquipment(string equipmentName)
{
    WeaponClass* wptr = NULL;
    ArmorClass* aptr = NULL;
    int index;
    bool has = false;
    string uppername = GameSpace::Ucase(equipmentName);
    if((uppername == this->Weapon())||(uppername == this->Armor()))
    {
        return true;
    }    
    if(Active())
    {
        for(int i = 0; i < pack.size(); i++)
        {
            if(pack[i])
            {
                if((pack[i]->Name())== uppername)
                {
                    has = true;
                    index = i;                   
                }
            }
        }
        if(has)
        {
            wptr = dynamic_cast<WeaponClass*>(pack[index]);
            aptr = dynamic_cast<ArmorClass*>(pack[index]);
            if(wptr)
            {
                pack.erase(pack.begin()+index);
                FindWeapon(wptr);
            }
            if(aptr)
            {
                pack.erase(pack.begin()+index);
                FindArmor(aptr);
            }
        }
        return has;
    }
           
}
EquipClass* Humanoid::BuyEquipment(EquipClass* equipment)
{
    EquipClass* toret = NULL;
    if((Active())&&(equipment))
    {
        if((GP()) >= (equipment->Cost()))
        {
            UpdateGP((-1)*(equipment->Cost()));
            FindEquipment(equipment);
        }
        else
        {
            toret = equipment;
        }
    }
    if(!Active())
    {
        toret = equipment;
    }
    return toret;
}
EquipClass* Humanoid::SellEquipment(string equipmentName)
{
    EquipClass* toret = NULL;
    string uppername = GameSpace::Ucase(equipmentName);
    bool has = false;
    int index;
    WeaponClass* wptr = NULL;
    ArmorClass* aptr = NULL;
    if (Active())
    {
        for(int i = 0; i < pack.size(); i++)
        {
            if(pack[i])
            {
                if((pack[i]->Name())== uppername)
                {
                    has = true;
                    index = i;     
                   // cout << "FOUND IN PACK" << endl << endl;              
                }
            }
        }
        if(has)
        {
            wptr = dynamic_cast<WeaponClass*>(pack[index]);
            aptr = dynamic_cast<ArmorClass*>(pack[index]);
            if(wptr)
            {
                pack.erase(pack.begin()+index);
                toret = wptr;
            }
            if(aptr)
            {
                pack.erase(pack.begin()+index);
                toret = aptr;
            }
        }
        else
        {
            if(uppername == Weapon())
            {
                toret = LoseWeapon();
            }
            else if(uppername == Armor())
            {
                toret = LoseArmor();
            }
            else
            {
           // cout << "NOT FOUND ANYWHERE" << endl << endl;
            }
            
        }
        if(toret)
        {//cout << "update gp" << endl << endl;
            UpdateGP(toret->Cost());
        }
      
    }
    return toret;
}                                                                 
vector<string> Humanoid::Pack() const
{
    vector<string> toRet;
    for (int i = 0; i < pack.size(); i++)
    {
        if(pack[i])
        {
            toRet.push_back(pack[i]->Name());
        }
    }
    GameSpace::Sort(toRet);
    return toRet;
}
vector<string> Humanoid::EquipInventory() const
{
    vector<string> temp;
    for (int i = 0; i < pack.size();i++)
    {
        if(pack[i])
        {
            temp.push_back(pack[i]->Name());
        }
    }
    if(HasWeapon())
    {
        temp.push_back(this->Weapon());
    }
    if(HasArmor())
    {
        temp.push_back(this->Armor());
    }
    return temp;
}
int Humanoid::AttackRoll() const
{
    VocRules *vrPtr = VocRules::GetVocRules();  
    int toRet = 0;
  //  if(Active()) //Despite documentation, there appears to be no test for this.
   // {
        if (WeaponClass::IsRange(CreatureClass::Weapon()))
        {
            //toRet = ((vrPtr->BaseAttackBonus(this->voc,this->level))+(CreatureClass::Ability(DEX))+(Dice::Roll(CreatureClass::Name(), GameSpace::ATT, 1, 20)));
            toRet += (vrPtr->BaseAttackBonus(this->voc,this->level));
            toRet += (Dice::Roll(CreatureClass::Name(), GameSpace::ATT, 1, 20));
            toRet += (CreatureClass::Ability(DEX)); 
        
         }
         else//is melee
        {
            toRet = ((vrPtr->BaseAttackBonus(this->voc,this->level))+(CreatureClass::Ability(STR))+(Dice::Roll(CreatureClass::Name(), GameSpace::ATT, 1, 20)));
        }
//    }
    return toRet;
}
int Humanoid::SavingThrow(SavingThrowType kind) const
{
    VocRules *vptr = VocRules::GetVocRules();
    int retval = 0;
    if(Active())
    {//cout << "IS ACTIVE!!!!!!!!!" << endl << endl;
        switch(kind)
        {
            case GameSpace::FORT:
                retval += AbilityMod(CON);
                break;
            case GameSpace::REFLEX:
                retval += AbilityMod(DEX);
                break;
            case GameSpace::WILL:
                retval += AbilityMod(WIS);
                break;
            default:
                throw GameSpace::INVALID_SAVINGTHROW;
        }   
        retval += vptr->BaseSaveBonus(voc, level, kind);
        retval += Dice::Roll(Name(), GameSpace::SVTH, 1, 20);
    }
    //cout << "RET VAL : " << retval << endl << endl;
    return retval;
//   return 11;
}
void Humanoid::InitLevel(int mod)
{
    level = mod;
}
void Humanoid::InitXP(int mod)
{
    xp = mod;
}
void Humanoid::Write(ostream& stream) const
{
    stream << Voc_Str() << '#';
    CreatureClass::Write(stream);
    stream << endl << "\t" << Level() << '#' << XP() << '#' << GP() << "#(";
    vector<string> toprint = this->Pack();
    for (int i = 0; i < toprint.size(); i++)
    {
        stream << toprint[i];
        if (i != (toprint.size() - 1))
        {
            stream << ',';
        }      
    }
    stream << ")#" << endl;
}
string Humanoid::Voc_Str() const
{
    string toRet;
    switch (voc)
    {
        case VocRules::FTR:
            toRet = "FTR";
            break;
        case VocRules::ROG:
            toRet = "ROG";
            break;
        case VocRules::BBN:
            toRet = "BBN";
            break;
        case VocRules::CLR:
            toRet = "CLR";
            break;
        case VocRules::WIZ:
            toRet = "WIZ";
            break;
    }
    return toRet;
}
WeaponClass* Humanoid::FindWeapon(WeaponClass * wpn)
{
    EquipClass* wpnPtr = NULL;
    //WeaponClass* tempptr = NULL;
    if (wpn)
    {
        if (!((this -> Dead()) || (this -> Disabled())))
        {//    cout << "NAME: " <<Name() << "ACTIVE" << endl;
        //wpnPtr = dynamic_cast<EquipClass*>(creatureWeapon);
            wpnPtr = creatureWeapon;
            if(wpnPtr)
            {
                //pack.push_back(new EquipClass(*wpnPtr));
                pack.push_back(wpnPtr);
            }
            creatureWeapon = wpn;
            wpnPtr = NULL;
         }
         else
         {
//           cout << "NAME : " << Name() << "NOT ACTIVE" <<endl;
             wpnPtr = wpn;
         }
      }
  // GameSpace::Sort(pack);
   return dynamic_cast<WeaponClass*>(wpnPtr);                                                                                                                                             
}
ArmorClass* Humanoid::FindArmor(ArmorClass * armor)
{
    EquipClass* ptr = NULL;
    //WeaponClass* tempptr = NULL;
    if (armor)
    {
         if (!((this -> Dead()) || (this -> Disabled())))
         {
             ptr = dynamic_cast<EquipClass*>(creatureArmor);
             //armorPtr = creatureArmor;
             // creatureWeapon = wpn;
             if(ptr)
             {
                 pack.push_back(ptr);
             }
             creatureArmor = armor;
             ptr = NULL;
         }
         else
         {
             ptr = armor;
         }
    }
//    GameSpace::Sort(pack);
    return dynamic_cast<ArmorClass*>(ptr);                                                                                                                                              
}