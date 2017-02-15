#ifndef _MR
#define _MR
#include "monster.h"
#include "voc.h"
#include "dice.h"
#include "armor.h"
#include "wpn.h"
#include <vector>
#include <string>
class Troll: public Monster
{
    protected:
    //
    
    public:
    Troll(string name);
    string Race_Str() const;
    /*
     * Pre: None.
     * Post: Race is returned as a string.
    */
    virtual vector<string> EquipInitialList() const;
    /*
     * Pre: None.
     * Post: Initial equip list is returned as a vector of strings.
    */
    virtual int AttackRoll() const;
    /*
     * Pre: None.
     * Post: Attack roll is returned.
    */
    virtual int SavingThrow(SavingThrowType kind) const;
    /*
     * Pre: None.
     * Post: Saving throw roll is returned.
    */
    virtual void Write(ostream& stream) const;
    /*
     * Pre: Ostream.
     * Post: Race info is printed.
    */
     virtual EquipClass* FindEquipment(EquipClass* equipment);
    private:
    static const string RACE;
    static const int ABILITY_ADJ[6];
    static const int HIT_DIE[3];
    static const int SAVE_THROW[3];
    static const int BASE_ATT_BONUS[2];
    static const string INIT_EQUIP[2];
    static const int NUM_INIT_SK = 2;
    static const string INIT_SKILLS[2];
    Troll();
};
class Ogre: public Monster
{
    protected:
    //
    
    public:
    Ogre(string name);
    string Race_Str() const;
    /*
     * Pre: None.
     * Post: Race is returned as a string.
    */
    virtual vector<string> EquipInitialList() const;
    /*
     * Pre: None.
     * Post: Initial equip list is returned as a vector of strings.
    */
    virtual int AttackRoll() const;
    /*
     * Pre: None.
     * Post: Attack roll is returned.
    */
    virtual int SavingThrow(SavingThrowType kind) const;
    /*
     * Pre: None.
     * Post: Saving throw roll is returned.
    */
    virtual void Write(ostream& stream) const;
    /*
     * Pre: Ostream.
     * Post: Race info is printed.
    */
    virtual EquipClass* FindEquipment(EquipClass* equipment);

    private:
    static const string RACE;
    static const int ABILITY_ADJ[6];
    static const int HIT_DIE[3];
    static const int SAVE_THROW[3];
    static const int BASE_ATT_BONUS[2];
    static const string INIT_EQUIP[2];
    static const int NUM_INIT_SK = 3;
    static const string INIT_SKILLS[3];
    Ogre();
};
#endif
 
