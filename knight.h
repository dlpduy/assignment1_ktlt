#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "main.h"

void read(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown);
bool checkArthur(int &HP);
bool checkLancelot(int &HP);
void tinyevent(int &HP, int &remedy);
void frogevent(int &level, int &maidenkiss);
void fight(int &HP, int &level, int levelup, int &remedy, int &maidenkiss);
void rebirthevent(int &HP, int &phoenixdown, int &rescue);
void checkHP(int &HP);
void mush_ghost_1(int &HP);
void mush_ghost_2(int &HP);
void mush_ghost_3(int &HP);
void mush_ghost_4(int &HP);
void event0(int &rescue);
void event1_5(int &HP, int &level);
void event6(int &HP, int &level, int &remedy);
void event7(int &HP, int &level, int &maidenkiss);
void event11(int &HP, int &level, int &phoenixdown);    
void event12(int &HP);
void event13(int &HP, int &phoenixdown, int &rescue);
void event15(int &remedy);
void event16(int &maidenkiss);
void event17(int &phoenixdown); 
void event99(int &level, int &rescue);
void tinycountdown(int &HP, int &remedy);
void frogcountdown(int &level, int &maidenkiss);
void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue);
void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);

#endif // __KNIGHT_H__