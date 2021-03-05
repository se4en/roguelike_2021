#ifndef MENU_H
#define MENU_H

#include "Image.h"

enum Page 
{
  MN_FIRST, 
  MN_AFTER1, 
  MN_1TO2,
  MN_AFTER2,
  MN_2TOFINISH
};

struct Menu
{
  Menu(Image* Screen);

  Page GetPage() {return curPage;}
  void GetPage(Page newPage) {curPage = newPage;}

  void Up();
  void Down();
  void Enter();
private:
  Page curPage;
};


#endif