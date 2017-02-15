#ifndef _HR
#define _HR
#include "humanoid.h"
#include "voc.h"
#include "dice.h"
#include "armor.h"
#include "wpn.h"
#include <vector>
//#include "humanoid.cpp"
//using namespace std;
class Human: public Humanoid
{
    protected:
    //
    
    public:
    Human(string name, VocRules::VocType voc = DEFAULT_VOC);
    /*virtual*/ vector<string> EquipInitialList() const;
    /*
     * Pre: None.
     * Post: Initial equip list is returned as a vector of strings.
    */
    virtual void Write(ostream& stream) const;
    /*
     * Pre: Ostream.
     * Post: Race info is printed.
    */
    string Race_Str() const;
    /*
     * Pre: None.
     * Post: Race is returned as a string.
    */
    ~Human();
    
    private:
    static const string RACE;
    static int ABILITY_ADJ[6];
    static const VocRules::VocType DEFAULT_VOC = VocRules::FTR;
    static const int NUM_INIT_EQUIP = 3;
    static const string INIT_EQUIP[6][3];
    Human();
};

class Elf: public Humanoid
{
     protected:
    //
    
    public:
    Elf(string name, VocRules::VocType voc = DEFAULT_VOC);
    /*virtual*/ vector<string> EquipInitialList() const;
    /*
     * Pre: None.
     * Post: Initial equip list is returned as a vector of strings.
    */
     virtual void Write(ostream& stream) const;
     /*
     * Pre: Ostream.
     * Post: Race info is printed.
    */
    string Race_Str() const;
    /*
     * Pre: None.
     * Post: Race is returned as a string.
    */
    ~Elf();
    
    private:
    static const string RACE;
    static int ABILITY_ADJ[6];
    static const VocRules::VocType DEFAULT_VOC = VocRules::WIZ;
    static const int NUM_INIT_EQUIP = 3;
    static const string INIT_EQUIP[6][3];
    Elf();
};

class HalfElf: public Humanoid
{
     protected:
    //
    
    public:
    HalfElf(string name, VocRules::VocType voc = DEFAULT_VOC);
    /*virtual*/ vector<string> EquipInitialList() const;
    /*
     * Pre: None.
     * Post: Initial equip list is returned as a vector of strings.
    */
     virtual void Write(ostream& stream) const;
     /*
     * Pre: Ostream.
     * Post: Race info is printed.
    */
    string Race_Str() const;
    /*
     * Pre: None.
     * Post: Race is returned as a string.
    */
    ~HalfElf();
    
    private:
    static const string RACE;
    static int ABILITY_ADJ[6];
    static const VocRules::VocType DEFAULT_VOC = VocRules::ROG;
    static const int NUM_INIT_EQUIP = 3;
    static const string INIT_EQUIP[6][3];
    HalfElf();
};

class Orc: public Humanoid
{
     protected:
    //
    
    public:
    Orc(string name, VocRules::VocType voc = DEFAULT_VOC);
    /*virtual*/ vector<string> EquipInitialList() const;
    /*
     * Pre: None.
     * Post: Initial equip list is returned as a vector of strings.
    */
    void virtual Write(ostream& stream) const;
     /*
     * Pre: Ostream.
     * Post: Race info is printed.
    */
    string Race_Str() const;
    /*
     * Pre: None.
     * Post: Race is returned as a string.
    */
    ~Orc();
    
    private:
    static const string RACE;
    static int ABILITY_ADJ[6];
    static const VocRules::VocType DEFAULT_VOC = VocRules::BBN;
    static const int NUM_INIT_EQUIP = 4;
    static const string INIT_EQUIP[6][4];
    Orc();
};
#endif
