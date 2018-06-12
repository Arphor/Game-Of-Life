#ifndef FUNC_H
#define FUNC_H
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
class Life{
private:
  int longitude, latitude;
  
  bool **geracao_passada;

  bool **geracao_atual;

public:

  Life(int, int, bool**, bool**);

  void set_alive(bool**, bool**);

  void update();

  void print(std::ostream&, char);

  bool stable(bool**);

  bool extinct();

};
#endif
