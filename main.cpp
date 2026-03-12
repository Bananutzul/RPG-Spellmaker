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
    char* special_effect;
    bool can_crit = false;

public:
    Spell(char); // can only create spells by specifying the element
    Spell(const Spell&); // Copy constructor
};

int Spell::noSpells = 0;

// Spell constructors //

Spell::Spell(char chosen_element) :spell_ID(++noSpells) {
    switch(chosen_element) {
        case 'F':
            std::cout << "Fire\n";
            this->spell_Name = strcpy(new char[5], "Fire");
            damage = 20;
            nr_hits = 1;
            mana_Cost = 10;
            break;
        case 'E':
            std::cout << "Earthquake\n";
            this->spell_Name = strcpy(new char[11], "Earthquake");
            damage = 9.5;
            nr_hits = 5;
            mana_Cost = 15;
            break;
        case 'L':
            std::cout << "Lightning\n";
            this->spell_Name = strcpy(new char[10], "Lightning");
            damage = 35;
            mana_Cost = 30;
            can_crit = true;
            break;
        case 'T':
            std::cout << "Tornado\n";
            this->spell_Name = strcpy(new char[8], "Tornado");
            damage = 10;
            mana_Cost = 5;
            break;
        case 'I':
            std::cout << "Invisibility\n";
            this->spell_Name = strcpy(new char[13], "Invisibility");
            damage = 0;
            mana_Cost = 20;
            break;
        default:
            std::cout << "Invalid element chosen.\n";
    }
}

Spell::Spell(const Spell& spell) :spell_ID(++noSpells){
    this->spell_Name = strcpy(new char[strlen(spell.spell_Name) + 1], spell.spell_Name);
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



int main() {

    // char elem;
    //
    // std::cout << "Choose spell: ";
    // std::cin >> elem;
    //
    // Spell test(elem);

    int option;
    bool player_created = false;
    while (true) {
        std::cout << "-----------------------RPG-SpellMaker-----------------------\n\n";
        std::cout << "1. Create player.\n";
        std::cout << "2. Choose spells.\n";
        std::cout << "3. Upgrade spells.\n";
        std::cout << "4. See character specs.\n";
        std::cout << "5. Start fight.\n";
        std::cout << "0. Exit.\n";
        std::cin >> option;

        if (option == 0) break;

        switch (option) {
            case 1:
                if (player_created == false) {
                    Player player;

                    std::cout << "Enter your name:\n";
                    char* name;
                    std::cin >> name;

                    player.setName(name);

                    player_created = true;
                }else {
                    std::cout << "You have already created your player.\n\n";
                }
                break;
            case 2:
                if (player_created == false) {
                    std::cout << "You must create a player first.\n\n";
                }else {
                    int nr_spells = 0;
                    while (nr_spells != 3) {
                        std::cout << "You have " << 3 - nr_spells << " left to choose.\n";

                        std::cout << "You can choose from the following (case sensitive):\n";
                        std::cout << "Fire[F]/Earthquake[E]/Lightning[L]/Tornado[T]/Invisibility[I]\n";

                        char elem;

                        std::cin >> elem;



                        nr_spells++;
                    }
                }
                break;
        }
    }

}
