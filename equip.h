// equipment.h

#ifndef _EQUIPH
#define _EQUIPH

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>
#include <climits>
#include <cctype>
#include "gamespace.h"

using namespace std;
using namespace GameSpace;

class EquipClass
{
  public:
//*******destructor
    virtual ~EquipClass() {};
    
//*******getters
    string Name( ) const;
    // Returns the equipment name
    // pre: none
    // post: the equipment name is returned
    
    virtual int Cost( ) const = 0;
    // Returns the equipment cost
    // pre: none
    // post: the equipment cost is returned
    
    virtual int Wt( ) const = 0;
    // Returns the equipment weight
    // pre: none
    // post: the equipment weight is returned
    

    
//*******relational operators
    // Relational operators comparing name
    bool operator==(const EquipClass &a) const;
    bool operator!=(const EquipClass &a) const;
    bool operator<(const EquipClass &a) const;
    bool operator<=(const EquipClass &a) const;
    bool operator>(const EquipClass &a) const;
    bool operator>=(const EquipClass &a) const;
    
//*******output
    virtual void Write(ostream& stream) const;
    // Writes the name of the equipment to an output stream
    // pre:  stream must be open, headers already printed
    //       if necessary.
    // post: name of the equipment object has been inserted
    //       into output stream.

  protected:

//*******constructor - protected
    EquipClass(string name);
    // Set data for equipment with name 
    // pre: name should be an equipment
    // post: equipment is created        
    

  private:
//*******constructors - private
    EquipClass( );        // no default construction
    
//*******data
    string name;

};



#endif


