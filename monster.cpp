#include "monster.h"
#include "voc.h"
#include "dice.h"
#include "armor.h"
#include "wpn.h"
#include <vector>
Monster::Monster()
:CreatureClass("")
{
}
Monster::Monster(string name)
:CreatureClass(name)
{
}
Monster::~Monster()
{
    
}
void Monster::Write(ostream& stream) const
{
    CreatureClass::Write(stream);
    //stream <<  Armor() << '#' << Weapon() << '#' << endl;    
} 
