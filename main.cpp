#include <iostream>

class Spell {
private:
    static int noSpells;
    const int spell_ID;
    char* spell_Name;
    char* element;
    float damage;
    // double mana_Cost;
    bool special_Effect;

public:
    Spell(char);
};

int Spell::noSpells = 0;

Spell::Spell(char chosen_element) :spell_ID(++noSpells) {
    switch(chosen_element) {
        case 'F':
            std::cout << "Fire\n";
            break;
        default:
            std::cout << "Invalid element chosen.\n";
    }
}


int main() {

    char elem;

    std::cout << "Element: ";
    std::cin >> elem;

    Spell('F');
}
