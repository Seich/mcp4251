#ifndef _MCP4251
#define _MCP4251

#include <Arduino.h>
#include <SPI.h>

namespace seich {
	enum class Address {
		//       Baaaaccxx 
		Wiper0 = B00000000,
		Wiper1 = B00010000,
		TCON   = B01000000,
		Status = B01010000
	};

	enum class Command {
	    //          Baaaaccxx 
		Write     = B00000000,
		Read      = B00001100,
		Increment = B00000100,
		Decrement = B00001000
	};

	byte operator|(Address i, Command c) {
		return byte(i) | byte(c);
	}

	class mcp4251
	{
	public:
		int CS;
		int SHDN;

		mcp4251(int _CS = 10, int _SHDN = 7) : CS(_CS), SHDN(_SHDN) {
			pinMode(CS, OUTPUT);
			pinMode(SHDN, OUTPUT);
			
			on();
			SPI.begin();
		}

		uint16_t transaction(Address address, Command command, int data) {
			SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
			digitalWrite(CS, LOW);

			uint16_t request = 0;
			request = (((request << 8) | byte(address) | byte(command)) << 8) | data;

			uint16_t response = SPI.transfer16(request);

			digitalWrite(CS, HIGH);
			SPI.endTransaction();

			return response;
		}

		void set(Address address, int value) {
			transaction(address, Command::Write, value);
		}

		int read(Address address) {
			return lowByte(transaction(address, Command::Read, 0));
		}

		void increment(Address address) {
			transaction(address, Command::Increment, 0);
		}

		void decrement(Address address) {
			transaction(address, Command::Decrement, 0);
		}

		void on() {
			digitalWrite(SHDN, HIGH);
		}

		void off() {
			digitalWrite(SHDN, LOW);
		}
	};
}


#endif
