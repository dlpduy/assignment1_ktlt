#include "knight.h"

bool lancelot;
ifstream infile;
short maxHP, countEvent = 0, levelO, tiny = 0, frog = 0, levelbefore, n2;
int mush_ghost_input[100];
float baseDamage[6] {0,1,1.5,4.5,7.5,9.5};
string file_mush_ghost, file_merlin_pack, file_asclepius_pack, eventcode, line2;

void read(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown) {
    ifstream ifs;
    ifs.open(file_input);
    ifs >> HP >> level >> remedy >> maidenkiss >> phoenixdown;
    getline(ifs, line2);
    getline(ifs, line2);
    getline(ifs, file_merlin_pack);
    int index;
    index = file_merlin_pack.find(",");
    file_mush_ghost = file_merlin_pack.substr(0,index);
    file_merlin_pack = file_merlin_pack.substr(index+1);
    index = file_merlin_pack.find(",");
    file_asclepius_pack = file_merlin_pack.substr(0,index);
    file_merlin_pack = file_merlin_pack.substr(index+1);
}

bool checkArthur(int &HP) {
    if (HP == 999) return 1;
    else return 0;
}

bool checkLancelot(int &HP) {
    for (short i = 2; i < sqrt(HP); i++)
        if (HP % i == 0) return 0;
    if (HP != 1) return 1;
    else return 0;
}

void tinyevent(int &HP, int &remedy) {
    HP /= 5;
    if (remedy > 0) {
        remedy--;
        HP *= 5;
    }
    else tiny = 3;
}

void frogevent(int &level, int &maidenkiss) {
    if (maidenkiss > 0) maidenkiss--;
    else {
        levelbefore = level;
        level = 1;
        frog = 3;
    }
}

void fight(int &HP, int &level,   int levelup, int &remedy, int &maidenkiss) {
    if (lancelot) level += levelup;
    else {
       short b = countEvent%10;
        levelO = countEvent > 6?(b > 5?b : 5) : b;
        if (level > levelO) level += levelup;
        else if (eventcode >= "1" && eventcode <= "5") HP -= baseDamage[eventcode[0] - '0'] * levelO * 10;
        else if (eventcode == "6") tinyevent(HP, remedy);
        else if (eventcode == "7") frogevent(level, maidenkiss);
    }
    if (level > 10) level = 10;
}

void rebirthevent(int &HP, int &phoenixdown, int &rescue) {
    if (HP <= 0) 
        if (phoenixdown = 0) 
            rescue = 0;
        else {
            phoenixdown--;
            HP = maxHP;
            tiny = 0;
        }
}

void checkHP(int &HP) {
    if (HP > maxHP) HP = maxHP;
}

void mush_ghost_1(int &HP) {
    short maxi = 0, mini = 0;
    for (short i = 1; i < n2; i++) {
        if (mush_ghost_input[i] > mush_ghost_input[maxi]) maxi = i;
        if (mush_ghost_input[i] < mush_ghost_input[mini]) mini = i;
    }
    HP -= maxi + mini;
}

void mush_ghost_2(int &HP) {
    bool decrease = false;
    short mtx = mush_ghost_input[n2 - 1], mti = n2;
    for (short i = 1; i < n2; i++) {
        if ((decrease && mush_ghost_input[i] > mush_ghost_input[i - 1]) || mush_ghost_input[i] == mush_ghost_input[i - 1]) {
            mtx = -2;
            mti = -3;
        }
        else if (!decrease && mush_ghost_input[i] < mush_ghost_input[i - 1]) {
            mtx = mush_ghost_input[i - 1];
            mti = i - 1;
            decrease = true;
        }
    }
    HP -= mtx + mti;
}

void event0(int &rescue) {
    rescue = 1;
}

void event1_5(int &HP, int &level, int &remedy, int &maidenkiss) {
    fight(HP, level, 1, remedy, maidenkiss);
}

void event6(int &HP, int& level, int &remedy, int &maidenkiss) {
    if (tiny && frog) fight(HP, level, 2, remedy, maidenkiss);
}

void event7(int &HP, int& level, int &remedy, int &maidenkiss) {
    if (tiny && frog) fight(HP, level, 2, remedy, maidenkiss);
}

void event11(int &HP, int &level, int &phoenixdown) {
    short s1 = 0;
    for (int i = 99; i > 99 - ((level + phoenixdown) % 5 + 1) * 3 * 2; i -= 2) 
        s1 += i;
    HP += s1 & 100;;
    if (HP > maxHP) HP = maxHP;
}

void event12(int &HP) {
    short f1 = 1, f0 = 1;
    while (f1 <= HP) {
        f1 = f1 + f0;
        f0 = f1 - f0;
    }
    HP = f0;
}

void event13(int &HP, int &phoenixdown, int &rescue) {
    infile.open(file_mush_ghost);
    infile >> n2;
    infile.ignore();
    for (int i = 0; i < n2; i++) 
        infile >> mush_ghost_input[i];
    infile.close();
    for (int i = 2; i < eventcode.length(); i++) {
        (eventcode[i] == '1')? mush_ghost_1(HP) :
        mush_ghost_2(HP);
        // (eventcode[i] == '3')? mush_ghost_3(HP) :
        //                       mush_ghost_4(HP);
        rebirthevent(HP, phoenixdown, rescue);
    }
}

void event15(int &remedy) {
    remedy++;
}

void event16(int &maidenkiss) {
    maidenkiss++;
}

void event17(int &phoenixdown) {
    phoenixdown++;
}

void event99(int &level, int &rescue) {
    if ((lancelot && level >= 8) || level == 10) 
        level = 10;
    else rescue = 0;
        
}

void tinycountdown(int &HP, int &remedy) {
    if (tiny > 0) {
        tiny--;
        if (tiny == 0 || remedy > 0) {
            HP *= 5;
            if (HP > maxHP) HP = maxHP;
            if (tiny > 0) {
                remedy--;
                tiny = 0;
            }
        }
    }
}

void frogcountdown(int &level, int &maidenkiss) {
    if (frog > 0) {
        frog--;
        if (frog == 0 || maidenkiss > 0) {
            level = levelbefore;
            if (frog > 0) {
                maidenkiss--;
                frog = 0;
            }
        }
    }
}

void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue) {
    cout << "HP=" << HP
        << ", level=" << level
        << ", remedy=" << remedy
        << ", maidenkiss=" << maidenkiss
        << ", phoenixdown=" << phoenixdown
        << ", rescue=" << rescue << endl;
}

void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue) {
    read(file_input, HP, level, remedy, maidenkiss, phoenixdown);
    if (checkArthur(HP)) rescue = 1;
    else {
        lancelot = checkLancelot(HP);
        maxHP = HP;
        rescue = -1;
        line2 += " ";
        int index = line2.find(' ');
        while (index != -1) {
           // eventcode = line2.substr(0, index);
            stringstream ss(line2);
            ss >> eventcode;
            countEvent++;
            (eventcode == "0")? event0(rescue) :
            (eventcode >= "1" && eventcode <= "5")? event1_5(HP, level, remedy, maidenkiss) :
            (eventcode == "6")? event6(HP, level, remedy, maidenkiss) :
            (eventcode == "7")? event7(HP, level,remedy, maidenkiss) :
            (eventcode == "11")? event11(HP, level, phoenixdown) :
            (eventcode == "12")? event12(HP) :
            (eventcode[1] == '3')? event13(HP, phoenixdown, rescue) :
            (eventcode == "15")? event15(remedy) :
            (eventcode == "16")? event16(maidenkiss) :
            (eventcode == "17")? event17(phoenixdown) :   
                                 event99(level, rescue);       
            
            rebirthevent(HP, phoenixdown, rescue);
            tinycountdown(HP, remedy);
            frogcountdown(level, maidenkiss);
            if (rescue != -1) break;
            display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
        }
    }
    display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
}