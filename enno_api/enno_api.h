#ifndef _ENNO_API_H
#define _ENNO_API_H

#ifdef __cplusplus
#include <cstdint>
extern "C" {
#else
#include <stdint.h>
#endif // __cplusplus

#include <stdlib.h>
#ifdef _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif
#include <stdbool.h>
#include "azure_c_shared_utility/socketio.h"
#include "azure_c_shared_utility/platform.h"
#include "azure_c_shared_utility/tickcounter.h"


#define PORT_NUM_UNENCRYPTED        1883
#define PORT_NUM_ENCRYPTED          8883
#define PORT_NUM_ENCRYPTED_CERT     8884


/**
* @brief IoT Error enum
*
* Enumeration of return values from the IoT_* functions within the SDK.
*/

typedef enum {
	NONE_ERROR = 0,
	/** Success return value - no error occurred. */
	GENERIC_ERROR = -1,
	/** A generic error.  A placeholder for a more specific error. */
	NULL_VALUE_ERROR = -2,
	/** A required parameter was passed as null. */
	CONNECTION_ERROR = -3,
	/** A connection could not be established. */
	SUBSCRIBE_ERROR = -4,
	/** The subscribe failed.  A SUBACK was not returned from the service. */
	PUBLISH_ERROR = -5,
	/** The publish failed.  In the case of a QoS 1 message a PUBACK was not received. */
	DISCONNECT_ERROR = -6,
	/** The disconnect failed.  The disconnect control packet could not be sent. */
	YIELD_ERROR = -7,
	/** An error occurred when yielding to the IoT MQTT client.  A possible cause is an unexpected TCP socket disconnect. */
	TCP_CONNECT_ERROR = -8,
	/** The TCP socket could not be established. */
	UNSUBSCRIBE_ERROR = -15,            /** The unsubscribe failed.  The unsubscribe control packet could not be sent. */

} Error_t;




typedef enum {
	ENNO_INIT = 0,
	ENNO_CONNECTING,
	ENNO_CONNECTED,
	ENNO_RETRY,
	ENNO_UNKOWN
}EnnoState_t;

typedef void(*ON_ENNO_CONNECTED_CALLBACK)(void *pClient);
typedef void(*ON_ENNO_MESSAGE_CALLBACK)(void *pClient, const char* topic, char* message, int length);
typedef struct ENNO_CLIENT_TAG
{
	char* host;
	short port;
	char* deviceid;
	char* oter;
	char* token;
	uint8_t* cer;
	int keepAliveInterval;
	char* subscrib[2];

	TICK_COUNTER_HANDLE packetTickCntr;
	uint64_t			current_ms;

	EnnoState_t   gState;		// continue or not
	void*		mqttHandle;


	LOGGER_LOG fn_log;
	ON_ENNO_CONNECTED_CALLBACK on_connected;
	ON_ENNO_MESSAGE_CALLBACK on_message;

} ENNO_CLIENT;


/**
* @brief Connection Function
*
* Called to establish an connection with the Enno IoT Service
*
* @param:  HostURL the website address to connect
*          port    listening port
*          appKey  a key for authentication
* @return An IoT Error Type defining successful/failed connection
*/
extern Error_t enno_init(ENNO_CLIENT *pClient);



/**
 * @brief Connection Function
 *
 * Called to establish an connection with the Enno IoT Service
 *
 * @param:  HostURL the website address to connect
 *          port    listening port
 *          appKey  a key for authentication
 * @return An IoT Error Type defining successful/failed connection
 */
extern Error_t enno_connect(ENNO_CLIENT *pClient);


/**
 * @brief Publish a message to a path
 *
 * Called to publish a message to a path.
 *
 * @param:	path           the destination of message sent to
 *          messages_enno  Pointer to the published message
 * @return An IoT Error Type defining successful/failed publish
 */
extern Error_t enno_publish(ENNO_CLIENT *pClient, char* path, char** value, int count);




/**
 * @brief Yield to the  client
 *
 * Called to yield the current thread to the underlying  client.
 *
 * @param timeout Maximum number of milliseconds to pass thread execution to the client.
 * @return An IoT Error Type defining successful/failed client processing.
 */
extern Error_t enno_loop(ENNO_CLIENT *pClient);



/**
* @brief Yield to the  client
*
* Called to yield the current thread to the underlying  client.
*
* @param timeout Maximum number of milliseconds to pass thread execution to the client.
* @return An IoT Error Type defining successful/failed client processing.
*/
extern bool enno_timeout(ENNO_CLIENT *pClient, uint32_t time_ms);


#ifdef __cplusplus
}
#endif // __cplusplus


#endif //_ENNO_API_H
