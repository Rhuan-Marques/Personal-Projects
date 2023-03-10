#include<bits/stdc++.h>
using namespace std;

/*
*WORK IN PROGRESS
-- THIS IS A FIRE EMBLEM COMBAT SIMULATOR USED BY A GROUP OF FRIENDS TO EASE CALCULATIONS--
-- FEEL FREE TO USE THIS AND EXPAND/CHANGE FOR WHATEVER YOUR NEEDS MAY BE!--
Weapons have Atk, Hit, Type and Range.
Weapons can only attack ranges that they can reach, and a weapon can have multiple ranges
Weapon type stat determines stats used in combat (1 = Physical | 0 = Magical)

Characters have a lot of stats, including a equiped weapon of their owns

---- FUNCTIONS ---
GENERAL:
filesave() //Receives a string and save the character or weapon in a file with that name, on their respective folders
fileload() //Receives a string and loads the character or weapon of that name
create_weapon() & create_char() //Opens a special menu to create weapons/characters easily

WEAPONS:
change_range() //Receives a string and changes the possible ranges accordinly
               //Example: receivig the string "1234" makes the range 1~4
get_hit() //Returns weapon hit stat
get_atk() //Returns weapon attack stat
get_type() //Returns weapon type
get_range() //Returns weapon set of ranges
compare_range() //receives a integer and checks if the weapon can attach at that range

CHARACTERS:
print_chara() //Prints out all the characters stats, good for debugging
atk() //Calculates and returns character total atk
hit_rate() //Calculates and returns character hit rate
avoid_rate() //Calculates and returns character avoid rate
prot() //Receives weapon type of receiving damage and returns correct defensive stat number
alive() //Returns 1 if the character is alive and 0 if it's dead;

change_weapon() //Receives string with weapon name and changes equiped weapon to weapon with that file name
get_str() //Returns character strenght stat
get_mag() //Returns character magic stat
get_max_hp() //Returns character max hp stat
get_hp() //Returns character current hp
get_spd() //Returns character speed stat
get_skill() //Returns character skill stat
get_luck() //Returns character luck stat
get_def() //Returns character def stat
get_res() //Returns character res stat
get_equip() //Returns character equiped weapon

OTHER:
battle(char, char, int) //simulates battle logistics from the first char attacking the seccond, with an integer range
attack(char, char) // makes calculations of damage of each attack turn in a battle.
doubling(char, char) //checks if first chars speed is enough to double attack the seccond
*/

class weapon{
    private:
        string name;
        bool type; //0=mag, 1=phys
        int atk, hit;
        set<int> range;

        void change_range(string range_string){
            for (char i : range_string){
                if(isdigit(i)) range.insert(i - '0');
            }
        }
    public:
        weapon(string name, bool type, int atk, int hit, string range_string){
            change_range(range_string);
        }
        weapon(){
            atk=0;
            type=1;
            hit=0;
        }
        void filesave(string weapon_name){
            string file_name = "weapon_" + weapon_name + ".bin";
            ofstream outfile("Weapons/" + file_name, ios::binary | ios::out);
            if (!outfile.is_open()) {
                throw runtime_error("Error: could not open file");
            }
            outfile.write(reinterpret_cast<const char*>(this), sizeof(*this));
            outfile.close();
        }
        void fileload(string weapon_name){
            string file_name = "weapon_" + weapon_name + ".bin";
            ifstream infile("Weapons/" + file_name, ios::binary | ios::in);
            if (!infile.is_open()) {
                throw runtime_error("Error: could not open file");
            }
            infile.read(reinterpret_cast<char*>(this), sizeof(*this));
            infile.close();
        }
        void create_weapon(){
            string aux;
            cout << "weapon name: "; cin >> name;
            cout << "weapon atk: "; cin >> atk;
            cout << "weapon type: "; cin >> type;
            cout << "weapon hit: "; cin >> hit;
            cout << "weapon range: "; cin >> aux;
            change_range(aux);
            filesave(name);
        }
        int get_hit(){
            return hit;
        }
        int get_atk(){
            return atk;
        }
        bool get_type(){
            return type;
        }
        set<int> get_range(){
            return range;
        }
        bool compare_range(int check){
            return range.count(check);
        }
};

class chara{
    private:
        string name;
        int str, mag, spd, skill, luck, def, res, max_hp, hp;
        weapon equip;

    public:
        chara(){
            name = "???";
            str = mag = spd = skill = luck = def = res = max_hp = hp = 1;
        }
        chara(string name, int str, int mag, int spd, int skill, int luck, int def, int res, int max_hp, string weapon_name){
            hp = max_hp;
            equip.fileload(weapon_name);
        }
        void print_chara(){
            cout << "---" << name << "---" << endl;
            cout << "Max HP: " << max_hp << endl;
            cout << "HP: " << hp << endl;
            cout << "Str: " << str << endl;
            cout << "Mag: " << mag << endl;
            cout << "Spd: " << spd << endl;
            cout << "Def: " << def << endl;
            cout << "Res: " << res << endl;
            cout << "Skill: " << skill << endl;
            cout << "Luck: " << luck << endl << endl;
            cout << "Weapon Atk: " << equip.get_atk() << endl;
            cout << "Weapon Hit: " << equip.get_hit() << endl;
            cout << "Weapon Type: " << equip.get_type() << endl << endl;
            cout << "Atk: " << atk() << endl;
            cout << "Hit Rate: " << hit_rate() << endl;
            cout << "Avoid Rate: " << avoid_rate() << endl;
            cout << "Crit Rate: " << crit_rate() << endl;
        }
        void filesave(string character_name){
            string file_name = "char_" + character_name + ".bin";
            ofstream outfile("Chars/" + file_name, ios::binary | ios::out);
            if (!outfile.is_open()) {
                throw runtime_error("Error: could not open file");
            }
            outfile.write(reinterpret_cast<const char*>(this), sizeof(*this));
            outfile.close();
        }
        void fileload(string character_name){
            string file_name = "char_" + character_name + ".bin";
            ifstream infile("Chars/" + file_name, ios::binary | ios::in);
            if (!infile.is_open()) {
                throw runtime_error("Error: could not open file");
            }
            infile.read(reinterpret_cast<char*>(this), sizeof(*this));
            infile.close();
        }
        void create_char(){
            cout << "---------- CHAR ---------" << endl;
            cout << "name: "; cin >> name;
            cout << "max hp: "; cin >> max_hp;
            hp = max_hp;
            cout << "mag: "; cin >> mag;
            cout << "str: "; cin >> str;
            cout << "spd: "; cin >> spd;
            cout << "def: "; cin >> def;
            cout << "res: "; cin >> res;
            cout << "skill: "; cin >> skill;
            cout << "luck: "; cin >> luck;
            filesave(name);
        }
        string get_name(){
            return name;
        }
        int get_hp(){
            return hp;
        }
        int get_maxhp(){
            return max_hp;
        }
        int get_str(){
            return str;
        }
        int get_mag(){
            return mag;
        }
        int get_spd(){
            return spd;
        }
        int get_skill(){
            return skill;
        }
        int get_luck(){
            return luck;
        }
        int get_def(){
            return def;
        }
        int get_res(){
            return res;
        }
        weapon get_equip(){
            return equip;
        }
        int hit_rate(){
            return (skill * 2) + (equip.get_hit()) + (luck/2);
        }
        int avoid_rate(){
            return ((spd * 2) + luck);
        }
        int crit_rate(){
            return (skill/2);
        }
        int atk(){
            int aux = equip.get_atk();
            if(equip.get_type()) aux+=str;
            else aux+=mag;

            return aux;
        }
        int prot(bool type){
            if(type) return def;
            else return res;
        }
        void change_weapon(string weapon_name){
            equip.fileload(name);
        }
        bool alive(){
            return (hp > 0);
        }
};

bool doubling(chara* a, chara* b){
    return (a->get_spd() - b->get_spd() >= 5);
}


void attack(chara* a, chara* b){
    int dmg;
    dmg = a->atk() - b->prot(a->get_equip().get_type());

    int hchance = a->hit_rate() - b->avoid_rate();
    if(hchance > 100) hchance = 100;

    int cchance = a->crit_rate() - b->get_luck();
    if(cchance > 100) cchance = 100;

    cout << "Hit Chance: " << hchance << endl;
    cout << "Crit Chance: " << cchance << endl;
    cout << a->get_name() << "--" << dmg << "-> " << b->get_name() << endl;
}


void battle(chara* a, chara* b, int battle_range){
    attack(a, b);
    bool counter = b->get_equip().compare_range(battle_range);
    counter -= b->alive();
    if(counter){
        attack(b, a);
    }
    if(a->alive() && doubling(a, b)){
            attack(a, b);
    }
    if(counter && b->alive() && doubling(b, a)){
            attack(b, a);
    }
    return;
}




int main(){
    int input;
    chara a, b;
    cout << "Hi, what do you need today?" << endl;
    cout << "1 - Battle" << endl;
    cout << "2 - Add character" << endl;
    cout << "3 - Add weapon" << endl;
    cin >> input;
    switch(input){
        case 1:{
            string aux;
            int range;
            cout << "Whats the name of the participants" << endl << "Attacker:";
            cin >> aux;
            a.fileload(aux);
            cout << "Defender:";
            cin >> aux;
            b.fileload(aux);
            cout << "At what range is the attack?";
            cin >> range;
            battle(&a, &b, range);
            break;
        }
        case 2:
            a.create_char();
            break;
        case 3:
            a.get_equip().create_weapon();
            break;
    }
}

