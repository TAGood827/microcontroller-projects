#ifndef GENERAL_H
#define GENERAL_H

#include <stdint.h>
#include <FramedSerialProtocol.h>

//Generic messages are in 0x0X space...
#define MESSAGE_ANNOUNCE_CONTROL_ID				0x00
#define MESSAGE_SEND_ACKNOWLEDGE				0x01
#define MESSAGE_SEND_COMPLETE					0x02
#define MESSAGE_REQUEST_ENABLE_DEBUG			0x03
#define MESSAGE_REQUEST_DISABLE_DEBUG			0x04
#define MESSAGE_SEND_DEBUG						0x05
#define MESSAGE_REQUEST_BATTERY					0x06
#define MESSAGE_SEND_BATTERY					0x07

namespace digitalcave {
	class Chiindii; // forward declaration
	
	class General {
		private:
			Chiindii *chiindii;

		public:
			General(Chiindii *chiindii);

			void dispatch(FramedSerialMessage* message);
	};
}
#endif