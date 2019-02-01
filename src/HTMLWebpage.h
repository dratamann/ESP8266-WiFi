#ifndef webpage_h
#define webpage_h

#include "Arduino.h"

class Webpage {
  public:
    //Constructor
    Webpage();

    //Methods
    String html(String outputState1, String outputState2);
};

#endif
