# Arduino MCP4251

A small library to use the MCP4251 Digital Potentiometer with the arduino
platform.

## Example:

```cpp
#include <Arduino.h>
#include <mcp4251.h>

using namespace seich;

mcp4251* pot;

void setup() {
    pot = new mcp4251();
    pot->set(Address::Wiper1, 5);
}

int current = 5;
int direction = 0;

void loop() {
    current = pot->read(Address::Wiper1);

    if (current <= 5) {
        pot->decrement(Address::Wiper1);
    } else if (current >= 250) {
        pot->increment(Address::Wiper1);
    }

    delay(10);
}
```
