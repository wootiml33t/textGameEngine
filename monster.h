#ifndef _MONSTER
#define _MONSTER
#include "cc3.h"
#include "voc.h"
#include "dice.h"
#include "armor.h"
#include "wpn.h"
#include <vector>
class Monster: public CreatureClass
{
    private:
    Monster();
    
    protected:
    Monster(string name);
    //int SavingThrow(SavingThrowType kind, int[] savingThrows) const;
    
    public:
    ~Monster();
    virtual vector<string> EquipInitialList() const =0;
    virtual void Write(ostream& stream) const;
};
#endif
