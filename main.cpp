#include <iostream>
#include <string.h>
#include <ctime>

using namespace std;

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
    int focus; // stat that scales mana
    Spell* spells;
    int upgrade_points;
    const int max_Spells;

public:
    // constructors
    Player();
    Player(const char*);
    Player(const Player&);
    Player& operator=(const Player&);
    ~Player();

    // setters
    void setName(const char*);

    //getters
    const char* getName() const;

};

// Player constructors //

Player::Player() :max_Spells(3){
    name = strcpy(new char[6], "Player");
    mana = 100;
    intelligence = 10;
    focus = 8;
    upgrade_points = 15;
    spells = new Spell[max_Spells];
}

Player::Player(const char* name) :max_Spells(3) {
    this->name = strcpy(new char[strlen(name) + 1], name);
    mana = 100;
    intelligence = 10;
    focus = 8;
    upgrade_points = 15;
    spells = new Spell[max_Spells];
}

Player::Player(const Player& player) :max_Spells(3){
    name = strcpy(new char[strlen(player.name) + 1], player.name);
    mana = 100;
    intelligence = 10;
    focus = 8;
    upgrade_points = 15;

    spells = new Spell[max_Spells];

    for (int i = 0; i < max_Spells; i++) 
        spells[i] = player.spells[i];
}

Player& Player::operator=(const Player& player) {
    if (this == &player) 
        return *this;

    delete[] name;
    name = strcpy(new char[strlen(player.name) + 1], player.name);

    mana = player.mana;
    intelligence = player.intelligence;
    focus = player.focus;
    upgrade_points = player.upgrade_points;

    delete[] spells;
    spells = new Spell[max_Spells];

    for (int i = 0; i < max_Spells; i++) 
        spells[i] = player.spells[i];

    return *this;
}

Player::~Player() {
    delete[] name;
    delete[] spells;
}


// Player setters //

void Player::setName(const char* name) {
    if (this->name != NULL)
        delete[] this->name;
    this->name = strcpy(new char[strlen(name) + 1], name);
}

// Player getters // 

const char* Player::getName() const{
    return name;
}

// Player methods //


class Boss {
private:
    const int boss_ID;
    char* name;
    double hp;
    float defense;
    char* attackList;
    const int nrAttacks;

public:

    // Constructors

    Boss();
    Boss(const char*);
    Boss(const Boss&);
    Boss& operator=(const Boss&);
    ~Boss();

};

// Boss constructors //

Boss::Boss() :boss_ID(time(nullptr)), nrAttacks(5){
    name = strcpy(new char[strlen("The Lich") + 1], "The Lich");
    hp = 500;
    defense = 0.5;

    attackList = new char[nrAttacks + 1];
    attackList[0] = '\0'; // initialize the attack list string with terminator, so it doesn't contain garbage
}

Boss::Boss(const char* name) :boss_ID(time(nullptr)), nrAttacks(5){
    this->name = strcpy(new char[strlen(name) + 1], name);
    hp = 500;
    defense = 0.5;

    attackList = new char[nrAttacks + 1];
    attackList[0] = '\0';
}

Boss::Boss(const Boss& boss) :boss_ID(time(nullptr)), nrAttacks(5){
    name = strcpy(new char[strlen(boss.name) + 1], boss.name);
    hp = boss.hp;
    defense = boss.defense;

    attackList = strcpy(new char[nrAttacks + 1], boss.attackList);

}

Boss& Boss::operator=(const Boss& boss){
    if (this == &boss)
        return *this;

    delete[] name;
    name = strcpy(new char[strlen(boss.name) + 1], boss.name);
    hp = boss.hp;
    defense = boss.defense;

    delete[] attackList;
    attackList = strcpy(new char[nrAttacks + 1], boss.attackList);

    return *this;
}

Boss::~Boss() {
    delete[] name;
    delete[] attackList;
}


class Game {
    Player player;
    Boss boss;
    bool gameWon;
};


int main() {

    char nume[10];

    std::cout << "Intoduceti un nume: ";

    std::cin >> nume;

    std::cout << "Nume introdus\n";

    Player player(nume);

    std::cout << player.getName();
}
