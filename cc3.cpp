#include "cc3.h"
using namespace std;
const int CreatureClass::ROW_START = -1;
const int CreatureClass::COL_START = -1;
const int CreatureClass::DEAD_HP = -10;
const int CreatureClass::DISABLED_HP = 0;
const int CreatureClass::HP_START = 0;
const int CreatureClass::NUMBER_OF_ABILITIES = 6;
const int CreatureClass::VOC_MAX = NUMBER_OF_ABILITIES;
const string CreatureClass::DEF_NAME = "DEFAULT";
CreatureClass::CreatureClass()
{
}
void CreatureClass::SkillInit()
{
        const char DEL = '#';
        string mod, skillin;
        pair<string, AbilityType> temppair;    
        //vector<pair<string,AbilityType> > sktable;
        ifstream file;
        file.open("skills.in");
        getline(file,skillin,DEL);
 //zimmer edit
 //   skillin = GameSpace::Ucase(TrimStr(skillin));
 //   mod = GameSpace::Ucase(mod);
        while(!file.eof())
        {
            getline(file,mod);  // this needs to be before you Ucase it ... WHY?
            skillin = GameSpace::Ucase(TrimStr(skillin));
            mod = GameSpace::Ucase(TrimStr(mod));
// zimmer added code
//    cout << "skillck: " << skill << " " << skillin << "-"<<mod<<endl;
 //       getline(file,mod);
 
            temppair.first = skillin;
            if (mod == "DEX")
            {
                temppair.second = DEX;
            }
            else if (mod == "STR")
            {
                temppair.second = STR;
            }
            else if(mod == "WIS")
            {
                temppair.second = WIS;
            }
            else if(mod == "CHA")
            {
                temppair.second = CHA;
            }
            else if(mod == "INT")
            {
                temppair.second = INT;
            }
            else if(mod == "CON")
            {
                temppair.second = CON;
            }
            else
            { 
                throw GameSpace::INVALID_ABILITY; 
            }
            this->sktable.push_back(temppair);
            getline(file,skillin,DEL);
//        skillin = GameSpace::Ucase(skillin);
       ///        cout << "READING IN FILE " << Name() << endl;     
        }
        file.close();
}

CreatureClass::CreatureClass(string name)
{
    if (name.length() > 10)
    {
        name.resize(10);
    }
    if (name == "")
    {
        throw GameSpace::INVALID_NAME;
    }
// Zimmer edit - this whole thing can go
//    vector<char> temp;
    /*bool hit = false;
    int index = 0;
    int front, back;*/
/*    for (int i = 0; i < name.length(); i++)
    {
        if(name[i] != ' ')
        {
            temp.push_back(name[i]);
        }
    }
    */
    /*
    while(!hit)
    {
        if(name[index] != ' ')
        {
            front = index;
            hit = true;
            index = 0;
        }
        index++;
    } 
    hit = false;
    index = name.size();
    while (!hit)
    {
        if (name[index] != ' ')
        {
            back = index;
            hit = true;
            index = 0;
        }
        index--;
    }
    for (int i = front; i < back; i++)
    {
        temp.push_back(name[i]);
    }*/
    //name = string(temp.begin(),temp.end());
    //CreatureClass::  // zimmer edit... you want it in the local variabl       
    name = GameSpace::TrimStr(name);
    this->name = name;
    row = ROW_START;
    col = COL_START;
    hp = HP_START;
    creatureWeapon = NULL;
    creatureArmor = NULL;
    for (int i =0; i < NUMBER_OF_ABILITIES; i++)
    {
        abilities.push_back(0);
    }
    // I fill the abilities with 0's just for saftey
    SkillInit();
}    
CreatureClass::~CreatureClass()
{
    delete creatureWeapon;
    delete creatureArmor;
    creatureWeapon = NULL;
    creatureArmor = NULL;
    //SkillInit();
}
void CreatureClass::CopyIntoMe(const CreatureClass& c)
{    
    name = c.name;   
    if (c.creatureArmor)
    {
         creatureArmor = new ArmorClass(*c.creatureArmor);
    }
    else
    {
         creatureArmor = NULL;
    }
    if (c.creatureWeapon)
    {
         creatureWeapon = new WeaponClass(*c.creatureWeapon);
    }
    else
    {
         creatureWeapon = NULL;
    }
    skills = c.skills;
    row = c.row;
    col = c.col;
    hp = c.hp;
    abilities = c.abilities;
}
CreatureClass::CreatureClass(const CreatureClass &c)// zimmer edit - set all ptrs to NULL!!!
{
    SkillInit();
    creatureWeapon = NULL;
    creatureArmor = NULL;
    CopyIntoMe(c);
}
CreatureClass& CreatureClass::operator=(const CreatureClass &c) 
{
// zimmer edit: missing the required if
// missing the deallocation of amr and wpn  before you call CopyIntoMe...
    if(this != &c)
    {
        CopyIntoMe(c);
    }
    return *this;
}
string CreatureClass::Weapon() const
{
    string name;
    if (creatureWeapon)
    {
        name = creatureWeapon -> Name();
    }
    else
    {
        name = "";
    }
    return name;
}
string CreatureClass::Armor() const
{
    string name;
    if (creatureArmor)
    {
        name = creatureArmor -> Name();
    }
    else
    {
        name = "";
    }
    return name;
}
bool CreatureClass::HasWeapon() const
{
    return (creatureWeapon);
}
bool CreatureClass::HasArmor() const
{
    return (creatureArmor);
}
WeaponClass* CreatureClass::FindWeapon(WeaponClass * wpn)
{
    WeaponClass* wpnPtr = NULL;
    //WeaponClass* tempptr = NULL;
    if (wpn)
    {
        if (!((this -> Dead()) || (this -> Disabled())))
        {
            wpnPtr = creatureWeapon;
           // creatureWeapon = wpn;
          // pack.push_back(wpnPtr);
           creatureWeapon = wpn;
        //   wpnPtr = NULL;
        }
        else
        {
            wpnPtr = wpn;
        }
    }
    return wpnPtr;
}
ArmorClass* CreatureClass::FindArmor(ArmorClass * armor)
{
    ArmorClass* armorPtr = NULL;
    if (armor)
    {
        if (!((this -> Dead()) || (this -> Disabled())))
        {
            armorPtr = creatureArmor;
            creatureArmor = armor;
           // pack.push_back(armorPtr);
           // armorPtr = NULL;
        }
        else
        {
            armorPtr = armor;
        }
    }
    return armorPtr;
   // return NULL;
}
WeaponClass* CreatureClass::LoseWeapon()
{
    WeaponClass* weptoret = NULL;
    if (creatureWeapon)
    {
        weptoret = creatureWeapon;
        creatureWeapon = NULL;
    }
    else
    {
        weptoret = NULL;
    }
    return weptoret;
}
ArmorClass* CreatureClass::LoseArmor()
{
    ArmorClass* armtoret = NULL;
    if (creatureArmor)
    {
        armtoret = creatureArmor;
        creatureArmor = NULL;
    }
    else
    {
        armtoret = NULL;
    }
    return armtoret;
}
int CreatureClass::SkillCheck(string skill) const //////////////////////////////////
{
    // zimmer edit - make sure you are comparing same case
    skill = Ucase(TrimStr(skill));   
    int toret = 0;
    if (!Dead())
    {
        for (int i = 0; i < sktable.size(); i++)
        {
            if (sktable[i].first == skill)
            {
                toret += Dice::Roll(Name(), GameSpace::SKCK, 1, 20) + AbilityMod(sktable[i].second); 
            } 
        }
    }           
    return toret;    
}
bool CreatureClass::ValidSkill(string skill) const
{
    skill = Ucase(skill);
    skill = TrimStr(skill);
    bool isValid = false;      
    ifstream in("skills.in");
    string contents((istreambuf_iterator<char>(in)),
    istreambuf_iterator<char>());
    contents = Ucase(contents);
    contents = TrimStr(contents);
                                
    for (int i = 0; i < contents.length(); i++)
    {
        if ((contents[i] == skill[0]) && (contents[i + 1] == skill[1]))
        {
             isValid = true;
        }
    }
    return isValid;
}
bool CreatureClass::AddSkill(string skill)
{
    bool knows = false;
    for (int i = 0; i < skills.size(); i++)
    {
        if (GameSpace::Ucase(skills[i]) == GameSpace::Ucase(skill))
        {
            knows = true;
        }
    }
    if ((ValidSkill(skill)) && !knows)
    {
        skills.push_back(skill);
    }
    return ((ValidSkill(skill) && (!knows)));
}
void CreatureClass::Amnesia()
{
    skills.clear();
}
vector<string> CreatureClass::Skills() const
{
    vector<string> sktmp;
    for (int i = 0; i < skills.size(); i++)
    {
        if (skills[i] != "@")
        {
            sktmp.push_back(skills[i]);
        }
    }
    return sktmp;
}
vector<int> CreatureClass::Abilities() const
{
    return abilities;
}
string CreatureClass::Name() const
{
    return name;
}
int CreatureClass::Row() const
{
    return row;
}
int CreatureClass::Col() const
{
    return col;
}
int CreatureClass::HP() const
{
    return hp;
}
bool CreatureClass::Dead() const
{
    return (hp <= DEAD_HP);
}
bool CreatureClass::Dying() const
{
    return ((!(this->Dead())) && (hp < DISABLED_HP));
}
bool CreatureClass::Disabled() const
{
    return ((hp <= DISABLED_HP)||(abilities[CON] <= 0));
}           
bool CreatureClass::SetCell(int newRow, int newCol)
{
    bool success = true;
    if ((((newRow > 0) && (newCol > 0)) && ((newRow < GameSpace::NUMROWS) && (newCol < GameSpace::NUMCOLS))) || ((newCol == -1) && (newRow == -1)))
    {
        row = newRow;
        col = newCol;
    }
    else
    {
        success = false;
    }
    return success;
}
int CreatureClass::UpdateHP(int modification)
{
    return (hp+= modification);
}
void CreatureClass::InitName(string mod)
{
    if (mod.length() > 10)
    {
        mod.resize(10);
    }
    if (mod == "")
    {
        mod = DEF_NAME;
    }
    mod = GameSpace::TrimStr(mod);
    name = mod;
}
void CreatureClass::InitSkills(vector<string> sk)
{
    skills = sk;
}
void CreatureClass::InitHP(int mod)
{
    hp = mod;
   // zimmer added cout<< "inithp: " <<hp<<endl;
}
void CreatureClass::InitAbilities(vector<int> abil)
{
    abilities = abil;
}
int CreatureClass::Ability(AbilityType ability) const
{
    switch(ability)
    {
        case DEX:
        case CON:
        case STR:
        case INT:
        case CHA:
        case WIS:
            break;
        default:
            throw GameSpace::INVALID_ABILITY;
    }
    return abilities[ability];// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ segfault
}
int CreatureClass::AbilityMod(AbilityType abil) const
{
    return ((Ability(abil)/2)-5);
}
int CreatureClass::InitiativeCheck() const
{
    return ((Dice::Roll(name, GameSpace::INIT, 1, 20)) + AbilityMod(DEX));
   //  return 1;
}
int CreatureClass::Defense() const
{
    int toret =0;
    if (HasArmor())
    {
        toret += creatureArmor->Bonus();
    }
    toret += ((10)+(AbilityMod(DEX))/*+(creatureArmor->Bonus())*/);
    return toret;
}
bool CreatureClass::Active() const
{
    return(!((Dead())||(Disabled())||(Dying())));
}
int CreatureClass::Damage() const
{
    int toRet = 0;
    if(HasWeapon())
    {
        if ((Active())&&(creatureWeapon->IsMelee()))
        {
            toRet += (creatureWeapon->Damage(name));
            toRet += (AbilityMod(STR));
        }
    }
    else if (Active())
    {
        toRet = AbilityMod(STR);
    }
    return toRet;
}
void CreatureClass::Write(ostream& out) const
{
    out << name << "#" << "(" << this->Row() << "," << this->Col() << ")" 
    << "#" << this->HP() << "#[" <<this->Ability(DEX) << "#" << 
    this->Ability(CON) << "#" << this->Ability(INT) << "#" 
    << this->Ability(CHA) << "#" << this->Ability(STR) << "#" 
    << this->Ability(WIS) << "]#(";                 
    for(int i = 0; i < skills.size(); i++)
    {
        if(skills[i] != "@")
        {
            out << skills[i];
        }
        if (i != ((skills.size() - 1))/*&&(skills[i-1] != " ")*/)
        {
            if (skills[i+1] != "@")
            {      
                out << ",";
            }
        }
    }
    out << ")#"  << this->Armor() << "#" << this->Weapon() << "#";
}
bool CreatureClass::operator==(CreatureClass &c) const
{
    string n1 = name;
    string n2 = c.name;
    n1 = Ucase(n1);
    n1 = TrimStr(n1);
              
    n2 = Ucase(n2);
    n2 = TrimStr(n2);
    return (n1 == n2);
}
bool CreatureClass::operator!=(CreatureClass &c) const
{    
    string n1 = name;
    string n2 = c.name;
    n1 = Ucase(n1);
    n1 = TrimStr(n1);
                                            
    n2 = Ucase(n2);
    n2 = TrimStr(n2);
    return (n1 != n2);
}
ostream& operator<< (ostream &out, const CreatureClass &c) 
{
    c.Write(out);
    return out;
}
bool CreatureClass::operator<(CreatureClass& c) const
{
    string n1 = name;
    string n2 = c.name;
    n1 = Ucase(n1);
    n1 = TrimStr(n1);
                                                   
    n2 = Ucase(n2);
    n2 = TrimStr(n2);
    return (n1 < n2);
}
bool CreatureClass::operator<=(CreatureClass &c) const
{
    string n1 = name;
    string n2 = c.name;
    n1 = Ucase(n1);
    n1 = TrimStr(n1);
                                                                                                           
    n2 = Ucase(n2);
    n2 = TrimStr(n2);
    return (n1 <= n2);
}
bool CreatureClass::operator>(CreatureClass &c) const
{
    string n1 = name;
    string n2 = c.name;
    n1 = Ucase(n1);
    n1 = TrimStr(n1);
                                                                                                                                       
    n2 = Ucase(n2);
    n2 = TrimStr(n2);
    return (n1 > n2);
}
bool CreatureClass::operator>=(CreatureClass &c) const
{
    string n1 = name;
    string n2 = c.name;
    n1 = Ucase(n1);
    n1 = TrimStr(n1);
                
    n2 = Ucase(n2);
    n2 = TrimStr(n2);
    return (n1 >= n2);
}
