#include <iostream>
#include <string.h>
#include <ctime>
#include <cstdlib>

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

class Player;
class Boss; // forward declaration so I can use player and boss in damage-calculation function etc

class Spell
{
private:
    static int noSpells;
    const int spell_ID;
    char *spell_Name;
    int nr_hits;
    float damage;
    double mana_Cost;
    bool can_crit;

public:
    // constructors
    Spell();
    Spell(char);
    Spell(const Spell &);
    Spell &operator=(const Spell &);
    ~Spell();

    // methods
    double calculateDamage(const Player &);
};

int Spell::noSpells = 0;

// Spell constructors //

Spell::Spell() : spell_ID(++noSpells)
{ // Init constructor
    spell_Name = strcpy(new char[12], "Placeholder");
    nr_hits = 0;
    damage = 0;
    mana_Cost = 0;
    can_crit = false;
}

Spell::Spell(char chosen_element) : spell_ID(++noSpells)
{ // Parameterized constructor
    switch (chosen_element)
    {
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

Spell::Spell(const Spell &spell) : spell_ID(++noSpells)
{
    this->spell_Name = strcpy(new char[strlen(spell.spell_Name) + 1], spell.spell_Name);
    this->nr_hits = spell.nr_hits;
    this->damage = spell.damage;
    this->mana_Cost = spell.mana_Cost;
    this->can_crit = spell.can_crit;
}

Spell &Spell::operator=(const Spell &spell)
{
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

Spell::~Spell()
{
    delete[] spell_Name;
}

// Spell methods

class Player
{
private:
    char *name;
    double mana;
    int intelligence; // stat that scales damage
    int focus;        // stat that scales mana
    Spell *spells;
    int upgrade_points;
    const int max_Spells;
    int nrSpells;

public:
    // constructors
    Player();
    Player(const char *);
    Player(const Player &);
    Player &operator=(const Player &);
    ~Player();

    // setters
    void setName(const char *);

    // getters
    const char *getName() const;
    const int getIntelligence() const;

    // methods
    void chooseSpells();
    void upgradeStats();
};

// Player constructors //

Player::Player() : max_Spells(3)
{
    name = strcpy(new char[6], "Player");
    mana = 100;
    intelligence = 10;
    focus = 8;
    upgrade_points = 15;
    nrSpells = 0;
    spells = new Spell[max_Spells];
}

Player::Player(const char *name) : max_Spells(3)
{
    this->name = strcpy(new char[strlen(name) + 1], name);
    mana = 100;
    intelligence = 10;
    focus = 8;
    upgrade_points = 15;
    nrSpells = 0;
    spells = new Spell[max_Spells];
}

Player::Player(const Player &player) : max_Spells(3)
{
    name = strcpy(new char[strlen(player.name) + 1], player.name);
    mana = 100;
    intelligence = 10;
    focus = 8;
    upgrade_points = 15;
    nrSpells = player.nrSpells;

    spells = new Spell[max_Spells];

    for (int i = 0; i < max_Spells; i++)
        spells[i] = player.spells[i];
}

Player &Player::operator=(const Player &player)
{
    if (this == &player)
        return *this;

    delete[] name;
    name = strcpy(new char[strlen(player.name) + 1], player.name);

    mana = player.mana;
    intelligence = player.intelligence;
    focus = player.focus;
    upgrade_points = player.upgrade_points;
    nrSpells = player.nrSpells;

    delete[] spells;
    spells = new Spell[max_Spells];

    for (int i = 0; i < max_Spells; i++)
        spells[i] = player.spells[i];

    return *this;
}

Player::~Player()
{
    delete[] name;
    delete[] spells;
}

// Player setters //

void Player::setName(const char *name)
{
    if (this->name != NULL)
        delete[] this->name;
    this->name = strcpy(new char[strlen(name) + 1], name);
}

// Player getters //

const char *Player::getName() const
{
    return name;
}

const int Player::getIntelligence() const
{
    return intelligence;
}

// Player methods //

void Player::chooseSpells()
{

    if (nrSpells == max_Spells)
        std::cout << "\nYou have already chosen all your spells. Go fight!\n";
    else
    {

        bool quit = false;

        while (nrSpells < max_Spells)
        {
            if (quit)
                break;

            std::cout << "Choose a spell from the following:\n";
            std::cout << "Fire[F]/Earthquake[E]/Lightning[L]/Tornado[T]/Invisibiity[I]/Quit[Q]\n";

            std::cout << "You currently have: " << this->nrSpells << " spell(s). Max spells: " << this->max_Spells << "\n";

            char option;

            std::cin >> option;

            switch (option)
            {
            case 'F':
            {
                clearScreen();
                std::cout << "Fire chosen.\n";
                Spell newspell('F');
                this->spells[nrSpells] = newspell;
                nrSpells++;
                break;
            }
            case 'E':
            {
                clearScreen();
                std::cout << "Earthquake chosen.\n";
                Spell newspell('E');
                this->spells[nrSpells] = newspell;
                nrSpells++;
                break;
            }
            case 'L':
            {
                clearScreen();
                std::cout << "Lightning chosen.\n";
                Spell newspell('L');
                this->spells[nrSpells] = newspell;
                nrSpells++;
                break;
            }
            case 'T':
            {
                clearScreen();
                std::cout << "Tornado chosen.\n";
                Spell newspell('T');
                this->spells[nrSpells] = newspell;
                nrSpells++;
                break;
            }
            case 'I':
            {
                clearScreen();
                std::cout << "Invisibility chosen.\n";
                Spell newspell('I');
                this->spells[nrSpells] = newspell;
                nrSpells++;
                break;
            }
            case 'Q':
            {
                clearScreen();
                std::cout << "Spell choosing menu has been quit\n";
                quit = true;
                break;
            }
            default:
            {
                clearScreen();
                std::cout << "Invalid spell chosen.\n";
                break;
            }
            }
        }
    }
}

void Player::upgradeStats()
{

    if (upgrade_points == 0)
        std::cout << "\nYou have already allocated all of your points.\n";
    else
    {

        int running = true;

        while (running)
        {
            if (upgrade_points == 0) {
                clearScreen();
                std::cout << "\nYou have allocated all of your points.\n";
                break;
            }   
            char option;
            
            clearScreen();

            std::cout << "\nYou currently have " << upgrade_points << " points left.\n";
            std::cout << "Choose which stat you would like to upgrade: Intelligence[I]/Focus[F]/Quit[Q]\n";
            std::cout << "Intelligence: increases spell damage.\n"
                      << "Focus: decreases mana cost of spells.\n";

            std::cin >> option;

            switch (option)
            {
            case 'Q':
            {
                clearScreen();
                running = false;
                break;
            }
            case 'I':
            {
                clearScreen();
                std::cout << "\nChoose how many points you want to allocate: ";

                int points;

                std::cin >> points;

                std::cout << "\n";

                if (points >= upgrade_points)
                    std::cout << "You don't have enough points left.\n";
                else
                {
                    intelligence += points;
                    upgrade_points -= points;
                }

                break;
            }
            case 'F':
            {
                clearScreen();
                std::cout << "\nChoose how many points you want to allocate: ";

                int points;

                std::cin >> points;

                std::cout << "\n";

                if (points > upgrade_points)
                    std::cout << "You don't have enough points left.\n";
                else
                {
                    focus += points;
                    upgrade_points -= points;
                }

                break;
            }
            default:
            {
                std::cout << "Invalid option.\n";
                break;
            }
            }
        }
    }
}

// Spell method that uses player int stat

double Spell::calculateDamage(const Player &player)
{
    if (this->spell_Name == "Invisibility")
        return 0;

    double final_damage = this->damage;
    final_damage *= this->nr_hits;

    // int scaling
    final_damage *= 1 + (0.1 * player.getIntelligence());

    // crit chance
    if (this->can_crit)
    {
        int chance = rand() % 100;

        if (chance < 30)
        {
            final_damage *= 2;
            std::cout << "Crit!\n";
        }
    }

    return final_damage;
}

class Boss
{
private:
    const int boss_ID;
    char *name;
    double hp;
    float defense;
    char *attackList;
    const int nrAttacks;

public:
    // Constructors

    Boss();
    Boss(const char *);
    Boss(const Boss &);
    Boss &operator=(const Boss &);
    ~Boss();

    // Setters

    void setName(const char *);
};

// Boss constructors //

Boss::Boss() : boss_ID(time(nullptr)), nrAttacks(5)
{
    name = strcpy(new char[strlen("The Lich") + 1], "The Lich");
    hp = 500;
    defense = 0.5;

    attackList = new char[nrAttacks + 1];
    attackList[0] = '\0'; // initialize the attack list string with terminator, so it doesn't contain garbage
}

Boss::Boss(const char *name) : boss_ID(time(nullptr)), nrAttacks(5)
{
    this->name = strcpy(new char[strlen(name) + 1], name);
    hp = 500;
    defense = 0.5;

    attackList = new char[nrAttacks + 1];
    attackList[0] = '\0';
}

Boss::Boss(const Boss &boss) : boss_ID(time(nullptr)), nrAttacks(5)
{
    name = strcpy(new char[strlen(boss.name) + 1], boss.name);
    hp = boss.hp;
    defense = boss.defense;

    attackList = strcpy(new char[nrAttacks + 1], boss.attackList);
}

Boss &Boss::operator=(const Boss &boss)
{
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

Boss::~Boss()
{
    delete[] name;
    delete[] attackList;
}

// Boss setters //

void Boss::setName(const char *name)
{
    if (this->name != NULL)
        delete[] this->name;

    this->name = strcpy(new char[strlen(name) + 1], name);
}

class Game
{
private:
    const int game_ID;
    Player player;
    Boss boss;
    bool gameWon;
    int turn_Number;

public:
    // Constructors / operator = //
    Game();
    Game(const char *, const char *);
    Game(const Game &);
    Game &operator=(const Game &);

    // Methods //

    void run();
    void setup_Menu();
};

// Game constructors //

Game::Game() : game_ID(time(nullptr))
{
    gameWon = false;
    turn_Number = 0;
}

Game::Game(const char *player_name, const char *boss_name) : game_ID(time(nullptr)), player(player_name), boss(boss_name)
{
    gameWon = false;
    turn_Number = 0;
}

Game::Game(const Game &game) : game_ID(time(nullptr))
{
    player = game.player;
    boss = game.boss;
    gameWon = game.gameWon;
    turn_Number = game.turn_Number;
}

Game &Game::operator=(const Game &game)
{
    if (this == &game)
        return *this;

    player = game.player;
    boss = game.boss;
    gameWon = game.gameWon;
    turn_Number = game.turn_Number;

    return *this;
}

// Methods //

void Game::setup_Menu()
{
    int option;

    bool running = true;

    while (running)
    {
        std::cout << "----------Setup Menu----------\n";
        std::cout << "\n1. Choose name.\n";
        std::cout << "2. Allocate upgrade points.\n";
        std::cout << "3. Choose spells.\n";
        std::cout << "4. Choose boss name.\n";
        std::cout << "0. Return to main menu.\n";

        std::cin >> option;

        switch (option)
        {
        case 1:
        {
            clearScreen();
            std::cout << "Choose your name: ";

            char player_name[50];

            std::cin.ignore();
            std::cin.getline(player_name, 50);
            player.setName(player_name);

            break;
        }
        case 2:
        {
            clearScreen();
            player.upgradeStats();
            break;
        }
        case 3:
        {
            clearScreen();
            this->player.chooseSpells();
            break;
        }
        case 4:
        {
            clearScreen();

            std::cout << "Choose boss name: ";

            char boss_name[50];

            std::cin.ignore();
            std::cin.getline(boss_name, 50);
            boss.setName(boss_name);

            break;
        }
        case 0:
        {
            clearScreen();
            running = false;
            break;
        }
        default:
        {
            clearScreen();
            std::cout << "Invalid option.\n";
            break;
        }
        }
    }
}

void Game::run()
{
    int option;

    bool running = true;

    std::cout << "----------RPG-SpellMaker----------\n";

    while (running)
    {

        std::cout << "\n----------Main Menu----------\n";
        std::cout << "1. Setup menu.\n";
        std::cout << "2. See created player.\n";
        std::cout << "3. Start fight.\n";
        std::cout << "0. Exit.\n";

        std::cin >> option;

        switch (option)
        {
        case 0:
        {
            clearScreen();
            std::cout << "Game has been quit.\n\n";
            running = false;
            break;
        }
        case 1:
        {
            clearScreen();
            this->setup_Menu();
            break;
        }

        case 2:
        {
            clearScreen();
            std::cout << "Test\n\n";
            break;
        }
        case 3:
        {
            clearScreen();
            std::cout << "Battle started\n";
            break;
        }
        default:
        {
            clearScreen();
            std::cout << "Invalid option.\n";
            break;
        }
        }
    }
}

int main()
{

    // char nume[10];

    // std::cout << "Intoduceti un nume: ";

    // std::cin >> nume;

    // std::cout << "Nume introdus\n";

    // Player player(nume);

    // std::cout << player.getName();

    std::srand(std::time(nullptr)); // seed RNG

    Game game;
    game.run();
}
