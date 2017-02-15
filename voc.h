// voc.h
// Voc Rules for the Quest for Elgeon
//  - provides look up for Hit Die, XP needed for a level Promotion, 
//    Saving throw, Base Attack Bonus, Base Saving Throw Bonus
//    
#ifndef _VOCH
#define _VOCH

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "gamespace.h"

using namespace std;
using namespace GameSpace;

class VocRules
{
  public:

// ********************************************* Public Constants      
    static const int VOC_MAX = 6;
    // Number of different vocations
        
    static const int LEVEL_MAX = 20;
    // Number of levels for each vocation

// ********************************************* VocType
    enum VocType {NNE, BBN, CLR, FTR, ROG, WIZ};
    // Datatype for describing the vocations
    // Barbarian:BBN, Cleric:CLR, Fighter:FTR, Rogue:ROG, Wizard:WIZ

    static const string VOC_STR[6];
    // string equivalents for VocType
        
    static VocType StrToVoc(string s);
    // Convert string to a VocType
    // pre:  s must have string
    // "Barbarian" or "BBN", "Cleric" or "CLR", 
    // "Fighter" or "FTR", "Rogue" or "ROG", "Wizard" or "WIZ"
    // post: return VocType based on string

    static string VocToStr( VocType s);
    // Converts s to a string
    // pre:  s must have a VocType value
    // post: return value of matching string
    // "BBN", "CLR","FTR", "ROG", "WIZ"


/*Moved to Gamespace
            
// ********************************************* SavingThrowType
    enum SavingThrowType {FORT=1, REFLEX, WILL};
    // Datatype for describing the saving throws
    // Fortitude:FORT, Reflex: REFLEX, Will:WILL
    
    static SavingThrowType StrToSavingThrow(string s);
    // Convert string to a SavingThrow type
    // pre:  s must have string
    // s = should be "FORTITUDE" or "FORT", "REFLEX", "WILL"
    // post: return SavingThrowType based on string

    static string SavingThrowToStr( SavingThrowType s);
    // Converts s to a string
    // pre:  s must have a SavingThrowType value
    // post: return value of matching string
    // s = will be "FORT", "REFLEX", "WILL"
*/
    
// ********************************************* LookUp Methods
    static long XPforPromotion(int level);
    // Looks up and returns the XP value needed for promotion to a level
    // Pre: Level must be between 1 and 20
    // Post: returns the XP needed for promotion
    
    int BaseAttackBonus(VocType v, int level) const;
    // Looks up and returns the BaseAttackBonus for a vocation and level
    // pre: level must be between 1 and 20
    // post: returns the attack bonus
    
    int BaseSaveBonus(VocType v, int level, SavingThrowType r) const;
    // Looks up the base saving throw bonus
    // pre: level must be between 1 and 20
    // post: returns base saving throw bonus
    
    int HitDie(VocType v) const;
    // Looks up the hit die for a specific vocation
    // pre:  v has the vocation
    // post: returns the hit die (number of sided die to use)
    
// ********************************************* Singleton Methods      
    static VocRules* GetVocRules( );
    // Creates the single VocRules instance (singleton)
    // pre:  none
    // post: a pointer to the instance is returned

    static void DeleteVocRules( );    
    // Deletes the instance of VocRules
    // pre: none
    // post: instance has been deleted

// ********************************************* PRIVATE  
private:
    static VocRules* vr;
    // pointer to the singleton

    VocRules( );  //constructor
    // Creates the instance by loading from file

    ~VocRules( ); //destructor

    //Making singleton non copyable
    VocRules(const VocRules&); //no copy constructor
    VocRules& operator=(const VocRules&); //no assignment

    static const int RULE_MAX = 4;
    // rules in voc rules
    
    static const int BASE_ATTACK_BONUS;
    //Index for base_attack_bonus
    
    static const long PROMOTION_TABLE[21]; 
    // Table of XP values for promotion

    int table[VOC_MAX][LEVEL_MAX+1][RULE_MAX];   
    // table for the rules
    
    int hitdie[VOC_MAX]; 
    // table for the hitdie     


};


#endif




