// armor.h
// Used in EquipClass inheritance hierarchy

#ifndef _ARMORH
#define _ARMORH

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>
#include <climits>
#include <cctype>
#include <map>
#include "equip.h"
#include "gamespace.h"

using namespace std;
using namespace GameSpace;

class ArmorClass:public EquipClass
{
  public:
//*******datatypes
    enum ArmorType {NOARMOR, CLOTH, LEATHER, MAIL, PLATE};
    // types of armor
    
    static ArmorType StrToArmor(string str);
    // converts a string to the ArmorType
    
    static string ArmorToStr(ArmorType type);
    // converts an ArmorType to a string

    struct ArmorRec
    {
       int cost;
       int wt;
       int penalty;
       int bonus;
       int speed;
       ArmorType style;
    };
    
//*******constructor
    ArmorClass(string name);
    // Set data for armor with name 
    // pre: name should be an armor
    // post: armor is created        
    
//*******getters
//    string Name( ) const;
    // Returns the armor name
    // pre: none
    // post: the armor name is returned
    
    int Cost( ) const;
    // Returns the armor cost
    // pre: none
    // post: the armor cost is returned
    
    int Wt( ) const;
    // Returns the armor weight
    // pre: none
    // post: the armor weight is returned
    
    int Penalty( ) const;
    // Returns the armor penalty
    // pre:  none
    // post: the armor penalty is returned

    int Bonus( ) const;
    // returns the armor bonus 
    // pre:  none.
    // post: the armor bonus is returned
    
    int Speed( ) const;
    // returns the armor speed
    // pre:  none.
    // post: the armor speed is returned

    ArmorType Style( ) const;
    // returns the armor style
    // pre:  none.
    // post: the armor style is returned

//*******lookup methods
    ArmorRec LookUpStats( ) const;
    // Looks up and returns stats of the current armor
    // pre: none
    // post: the entire armor record is returned
    
    static int LookUpCost(string name);
    // Looks up the cost of a specific armor
    // pre:  name should be the name of an armor
    // post: returns the cost of the armor, zero if not found

    static int LookUpWt(string name);
    // Looks up the weight of a specific armor
    // pre:  name should be the name of an armor
    // post: returns the weight of the armor, zero if not found
    
    static ArmorRec LookUpStats(string name);
    // Looks up and returns the stats for a given armor
    // pre: name should be the name of an armor
    // post: returns the entire armor record
    
    static bool IsEquipment(string name);
    // Checks whether a name is a type of armor
    // pre: none
    // post: returns true if name is an armor, false otherwise
    
//*******relational operators
    // Relational operators comparing name
/*    bool operator==(const ArmorClass &a) const;
    bool operator!=(const ArmorClass &a) const;
    bool operator<(const ArmorClass &a) const;
    bool operator<=(const ArmorClass &a) const;
    bool operator>(const ArmorClass &a) const;
    bool operator>=(const ArmorClass &a) const;
*/    

//*******output
    void Write(ostream& stream) const;
    // Writes the armor data to an output stream
    // order:
    //       ARMOR#name#cost#weight#penalty#bonus#speed#style#
    // pre:  stream must be open, headers already printed
    //       if necessary.
    // post: all member data in the armor object has been inserted
    //       into output stream.

  private:
    ArmorClass( );        // no default construction

    static void Load( );  // Loads wpn data from ARMOR_FILE

    static bool Read(istream& stream,string& name, ArmorRec& data);
    // Reads the armor object data from an input stream
    // order:
    //       name#cost#weight#penalty#bonus#speed#style
    // pre:  stream must be open.
    // post: data extracted from stream,
    //       if valid - data members have updated value, return true
    //       else data members unchanged, return false

//*******DATA
//    string name;                        // armor name
    static map <string,ArmorRec> armor; // data about armor
    static const string DEF_NAME ; // default armor name (invalid)
};



#endif


