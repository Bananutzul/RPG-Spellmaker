#include <iostream>

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
};

int Spell::noSpells = 0;

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


int main() {

    // char elem;
    //
    // std::cout << "Choose spell: ";
    // std::cin >> elem;
    //
    // Spell test(elem);

    
}
