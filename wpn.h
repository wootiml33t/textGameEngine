// wpn.h
// used in EquipClass inheritance hierarchy

#ifndef _WPNH
#define _WPNH

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>
#include <cctype>
#include <climits>
#include <map>
#include "equip.h"
#include "gamespace.h"
#include "dice.h"

using namespace std;
using namespace GameSpace;

class WeaponClass:public EquipClass
{
  public:
//*******datatypes
    enum WeaponType {NOWPN, BALLISTIC, BLUDGEONING, ENERGY, PIERCING, SLASHING};
    // types of wpn
    
    static WeaponType StrToWeapon(string str);
    // converts a string to the WeaponType
    
    static string WeaponToStr(WeaponType type);
    // converts an WeaponType to a string

    struct WeaponRec
    {
       int cost;
       int wt;
       int critical;
       int damRolls;
       int damFaces;
       int size;
       WeaponType style;
       bool strength;
    };

//*******constructor
    WeaponClass(string name);
    // Set data for wpn with name
        
//*******getters
//    string Name( ) const;
    // Returns the wpn name
    // pre: none
    // post: the wpn name is returned
    
    int Cost( ) const;
    // Returns the wpn cost
    // pre: none
    // post: the wpn cost is returned
    
    int Wt( ) const;
    // Returns the wpn weight
    // pre: none
    // post: the wpn weight is returned

    int Critical( ) const;
    // Returns the wpn critical range
    // pre:  none
    // post: the wpn's critical range is returned

    int Damage(string CreatureName) const;
    // returns the wpn's rolled damage value 
    //			(needs creature name to roll)
    // pre:  name of creature rolling damage
    // post: the wpn's damage is returned
    
    int Size( ) const;
    // returns the wpn size
    // pre:  none.
    // post: the wpn size is returned

    WeaponType Style( ) const;
    // returns the wpn style
    // pre:  none.
    // post: the wpn style is returned

    bool IsMelee( ) const;
    // returns true when melee wpn
    // pre:  none.
    // post: returns true if melee, false otherwise

    bool IsRange( ) const;
    // returns true when range wpn
    // pre:  none.
    // post: returns true if range, false otherwise

    
//*******lookup methods
    WeaponRec LookUpStats( ) const;
    // Looks up and returns stats of the current wpn
    // pre: none
    // post: the entire wpn record is returned
    
    static int LookUpCost(string name);
    // Looks up the cost of a specific wpn
    // pre:  name should be the name of an wpn
    // post: returns the cost of the wpn, zero if not found

    static int LookUpWt(string name);
    // Looks up the weight of a specific wpn
    // pre:  name should be the name of an wpn
    // post: returns the weight of the wpn, zero if not found
    
    static WeaponRec LookUpStats(string name);
    // Looks up and returns the stats for a given wpn
    // pre: name should be the name of an wpn
    // post: returns the entire wpn record
    
    static bool IsEquipment(string name);
    // Checks whether a name is a type of wpn
    // pre: none
    // post: returns true if name is an wpn, false otherwise

    static bool IsMelee(string name );
    // returns true when melee wpn
    // pre:  none.
    // post: returns true if melee, false otherwise

    static bool IsRange(string name ) ;
    // returns true when range wpn
    // pre:  none.
    // post: returns true if range, false otherwise


//*******relational operators
    // Relational operators comparing name
/*    bool operator==(const WeaponClass &w) const;
    bool operator!=(const WeaponClass &w) const;
    bool operator<(const WeaponClass &w) const;
    bool operator<=(const WeaponClass &w) const;
    bool operator>(const WeaponClass &w) const;
    bool operator>=(const WeaponClass &w) const;
*/    
//*******output
    void Write(ostream& stream) const;
    // Writes the wpn data to an output stream
    // order:
    //       name#cost#weight#critical#ndf#size#style#
    // pre:  stream must be open, headers already printed
    //       if necessary.
    // post: all member data in the wpn object has been inserted
    //       into output stream.
    

  private:
    WeaponClass( );          // no default construction
         
    static void Load( );  // loads the data from WPN_FILE
    
    static bool Read(istream& stream,string& name, WeaponRec& data);
    // Reads the wpn object data from an input stream
    // order:
    //       name#cost#weight#critical#ndf#size#style#
    // pre:  stream must be open.
    // post: data extracted from stream,
    //       if valid - data members have updated value, return true
    //       else data members unchanged, return false

//*******DATA
    static map <string,WeaponRec> wpns; // data about wpns
    static const string DEF_NAME; //default wpn name (invalid)

};



#endif


