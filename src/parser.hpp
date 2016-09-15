#include <iostream>

class LittleParser{
  public:
    void parse(std::istream* stream);
    bool accepted();
  private:
    bool accept;
}
