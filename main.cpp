#include <iostream>
#include <string.h>

class Spell {
private:
    static int noSpells;
    const int spell_ID;
    char* spell_Name;
    int nr_hits;
    float damage;
    double mana_Cost;
    bool can_crit;

public:
    Spell();
    Spell(char);
    Spell(const Spell&);
    Spell& operator=(const Spell&);
    ~Spell();
};

int Spell::noSpells = 0;

// Spell constructors //

Spell::Spell() :spell_ID(++noSpells) { // Init constructor
    spell_Name = strcpy(new char[12], "Placeholder");
    nr_hits = 0;
    damage = 0;
    mana_Cost = 0;
    can_crit = false;
}


Spell::Spell(char chosen_element) :spell_ID(++noSpells) { // Parameterized constructor
    switch(chosen_element) {
        case 'F':
            std::cout << "Fire\n";
            this->spell_Name = strcpy(new char[5], "Fire");
            damage = 20;
            nr_hits = 1;
            mana_Cost = 10;
            can_crit = false;
            break;
        case 'E':
            std::cout << "Earthquake\n";
            this->spell_Name = strcpy(new char[11], "Earthquake");
            damage = 9.5;
            nr_hits = 5;
            mana_Cost = 15;
            can_crit = false;
            break;
        case 'L':
            std::cout << "Lightning\n";
            this->spell_Name = strcpy(new char[10], "Lightning");
            damage = 35;
            mana_Cost = 30;
            nr_hits = 1;
            can_crit = true;
            break;
        case 'T':
            std::cout << "Tornado\n";
            this->spell_Name = strcpy(new char[8], "Tornado");
            damage = 10;
            mana_Cost = 5;
            nr_hits = 2;
            can_crit = false;
            break;
        case 'I':
            std::cout << "Invisibility\n";
            this->spell_Name = strcpy(new char[13], "Invisibility");
            damage = 0;
            mana_Cost = 20;
            nr_hits = 0;
            can_crit = false;
            break;
        default:
            spell_Name = strcpy(new char[12], "Placeholder");
            damage = 0;
            nr_hits = 0;
            mana_Cost = 0;
            can_crit = false;
            std::cout << "Invalid element chosen.\n";
    }
}

Spell::Spell(const Spell& spell) :spell_ID(++noSpells){
    this->spell_Name = strcpy(new char[strlen(spell.spell_Name) + 1], spell.spell_Name);
    this->nr_hits = spell.nr_hits;
    this->damage = spell.damage;
    this->mana_Cost = spell.mana_Cost;
    this->can_crit = spell.can_crit;
}

Spell& Spell::operator=(const Spell& spell) {
    if (this == &spell)
        return *this;

    delete[] spell_Name;
    spell_Name = strcpy(new char[strlen(spell.spell_Name) + 1], spell.spell_Name);

    nr_hits = spell.nr_hits;
    damage = spell.damage;
    mana_Cost = spell.mana_Cost;
    can_crit = spell.can_crit;

    return *this;
}

Spell::~Spell() {
    delete[] spell_Name;
}


class Player {
private:
    char* name;
    double mana;
    int intelligence; // stat that scales damage
    Spell* spells;
    const int max_Spells;

public:
    // constructors
    Player();

    // setters
    void setName(char*);

    // methods

    void chooseSpells();
};

// Player constructor //

Player::Player() :max_Spells(3){
    name = strcpy(new char[6], "Player");
}


// Player setters //

void Player::setName(char* name) {
    if (this->name != NULL)
        delete[] this->name;
    this->name = strcpy(new char[strlen(name) + 1], name);
}

// Player methods //


class Boss {
private:
    char* name;
    double hp;
    float defense;
    char* attackList;
    const int nrAttacks = 15;

};



class Game {
    Player player;
    Boss boss;
    bool gameWon;
};


int main() {

    Spell a, b('F');
    Spell c = b;
    Spell d;
    d = a;
}
