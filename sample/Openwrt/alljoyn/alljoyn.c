#define false 0
#define true 1
typedef int bool; // or #define bool int

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <ctype.h>

#include <alljoyn_c/BusAttachment.h>
#include <alljoyn_c/Init.h>
#include <alljoyn_c/Observer.h>

/*constants*/
static const char* INTERFACE_NAME = "org.allseen.smarthome.device.airbox.AirboxInterface";
static const char* OBJECT_NAME =    "org.allseen.smarthome.device.airbox";
static const char* OBJECT_PATH = "/device/airbox/AirboxService";
static const alljoyn_sessionport SERVICE_PORT = 69;

char serviceName[100] = {0};
int  busflag = 0;

/** Static top level message bus object */
static alljoyn_busattachment g_msgBus = NULL;
static QCC_BOOL s_joinComplete = QCC_FALSE;
static alljoyn_sessionid s_sessionId = 0;

/* Static BusListener */
static alljoyn_buslistener g_busListener;


/* FoundAdvertisedName callback */
void found_advertised_name(const void* context, const char* name, alljoyn_transportmask transport, const char* namePrefix)
{
	printf("found_advertised_name(name=%s, prefix=%s)\n", name, namePrefix);
	if (0 != strstr(name, OBJECT_NAME)) {
		
		strcpy(serviceName, name);
		/* We found a remote bus that is advertising basic service's  well-known name so connect to it */
		alljoyn_sessionopts opts = alljoyn_sessionopts_create(ALLJOYN_TRAFFIC_TYPE_MESSAGES, QCC_FALSE, ALLJOYN_PROXIMITY_ANY, ALLJOYN_TRANSPORT_ANY);
		QStatus status;
		busflag = 1;

		/* enable concurrent callbacks so joinsession can be called 
		alljoyn_busattachment_enableconcurrentcallbacks(g_msgBus);
		status = alljoyn_busattachment_joinsession(g_msgBus, name, SERVICE_PORT, NULL, &s_sessionId, opts);

		if (ER_OK != status) {
			printf("alljoyn_busattachment_joinsession failed (status=%s)\n", QCC_StatusText(status));
		}
		else {
			printf("alljoyn_busattachment_joinsession SUCCESS (Session id=%d)\n", s_sessionId);
			strcpy(serviceName, name);
			s_joinComplete = QCC_TRUE;

		}*/
		alljoyn_sessionopts_destroy(opts);
	}
	
}

/* NameOwnerChanged callback */
void name_owner_changed(const void* context, const char* busName, const char* previousOwner, const char* newOwner)
{
	if (newOwner && (0 == strcmp(busName, OBJECT_NAME))) {
		printf("name_owner_changed: name=%s, oldOwner=%s, newOwner=%s\n",
			busName,
			previousOwner ? previousOwner : "<none>",
			newOwner ? newOwner : "<none>");
	}
}


void airbox_init(void)
{
	QStatus status = ER_OK;

	//char* connectArgs = "unix:abstract=alljoyn";
	char* connectArgs = NULL;
	alljoyn_interfacedescription testIntf = NULL;
	/* Create a bus listener */
	alljoyn_buslistener_callbacks callbacks = {
		NULL,
		NULL,
		&found_advertised_name,
		NULL,
		&name_owner_changed,
		NULL,
		NULL,
		NULL
	};

	status = alljoyn_init();
	if (ER_OK != status) {
		printf("alljoyn_init failed (%s)\n", QCC_StatusText(status));
		return 1;
	}

/*	status = alljoyn_routerinit();
	if (ER_OK != status) {
		printf("alljoyn_routerinit failed (%s)\n", QCC_StatusText(status));
		alljoyn_shutdown();
		return 1;
	}
	*/

	printf("AllJoyn Library version: %s\n", alljoyn_getversion());
	printf("AllJoyn Library build info: %s\n", alljoyn_getbuildinfo());

	/* Create message bus */
	g_msgBus = alljoyn_busattachment_create("QQHaierAlljoynClient", QCC_TRUE);

	/* Add org.alljoyn.Bus.method_sample interface */
	status = alljoyn_busattachment_createinterface(g_msgBus, INTERFACE_NAME, &testIntf);
	if (status == ER_OK) {
		printf("Interface Created.\n");

		alljoyn_interfacedescription_addproperty(testIntf, "Version", "u", ALLJOYN_PROP_ACCESS_READ);
		alljoyn_interfacedescription_addmethod(testIntf, "infr_ctr cmd_len", "yay", "y", "cmd_len,cmd,out_value", NULL, NULL);
		alljoyn_interfacedescription_addsignal(testIntf, "TempValueChanged", "q", "tempValue", NULL, NULL);
		alljoyn_interfacedescription_addsignal(testIntf, "HumValueChanged", "q", "humValue", NULL, NULL);
		alljoyn_interfacedescription_addsignal(testIntf, "VocLevelChanged", "y", "vocLevel", NULL, NULL);
		alljoyn_interfacedescription_addsignal(testIntf, "VocValueChanged", "q", "vocValue", NULL, NULL);
		alljoyn_interfacedescription_addsignal(testIntf, "PM25LevelChanged", "y", "pm25Level", NULL, NULL);

		alljoyn_interfacedescription_addproperty(testIntf, "TempValue", "q", ALLJOYN_PROP_ACCESS_READ);
		alljoyn_interfacedescription_addproperty(testIntf, "HumValue", "q", ALLJOYN_PROP_ACCESS_READ);
		alljoyn_interfacedescription_addproperty(testIntf, "VocLevel", "y", ALLJOYN_PROP_ACCESS_READ);
		alljoyn_interfacedescription_addproperty(testIntf, "VocValue", "q", ALLJOYN_PROP_ACCESS_READ);
		alljoyn_interfacedescription_addproperty(testIntf, "PM25Level", "y", ALLJOYN_PROP_ACCESS_READ);


		/*intf->AddProperty("Version", "u", PROP_ACCESS_READ);
		intf->AddMethod("infr_ctr cmd_len", "yay", "y", "cmd_len,cmd,out_value", 0);
		intf->AddSignal("TempValueChanged", "q", "tempValue", 0);
		intf->AddSignal("HumValueChanged", "q", "humValue", 0);
		intf->AddSignal("VocLevelChanged", "y", "vocLevel", 0);
		intf->AddSignal("VocValueChanged", "q", "vocValue", 0);
		intf->AddSignal("PM25LevelChanged", "y", "pm25Level", 0);
		intf->AddProperty("TempValue", "q", PROP_ACCESS_READ);
		intf->AddProperty("HumValue", "q", PROP_ACCESS_READ);
		intf->AddProperty("VocLevel", "y", PROP_ACCESS_READ);
		intf->AddProperty("VocValue", "q", PROP_ACCESS_READ);
		intf->AddProperty("PM25Level", "y", PROP_ACCESS_READ);
		intf->Activate();

		alljoyn_interfacedescription_addmember(testIntf, ALLJOYN_MESSAGE_METHOD_CALL, "flash", "du", "du", "brightnessIn,frequencyIn,brightnessOut,frequencyOut", 0);
		alljoyn_interfacedescription_addmember(testIntf, ALLJOYN_MESSAGE_METHOD_CALL, "on", "d", "du", "brightnessIn,brightnessOut,frequencyOut", 0);
		alljoyn_interfacedescription_addmember(testIntf, ALLJOYN_MESSAGE_METHOD_CALL, "off", NULL, "du", "brightnessOut,frequencyOut", 0);
		alljoyn_interfacedescription_addmember(testIntf, ALLJOYN_MESSAGE_METHOD_CALL, "status", NULL, "du", "brightnessOut,frequencyOut", 0);*/
		alljoyn_interfacedescription_activate(testIntf);
	}
	else {
		printf("Failed to create interface 'org.alljoyn.Bus.method_sample'\n");
	}


	/* Start the msg bus */
	if (ER_OK == status) {
		status = alljoyn_busattachment_start(g_msgBus);
		if (ER_OK != status) {
			printf("alljoyn_busattachment_start failed\n");
		}
		else {
			printf("alljoyn_busattachment started.\n");
		}
	}

	/* Connect to the bus */
	if (ER_OK == status) {
		status = alljoyn_busattachment_connect(g_msgBus, connectArgs);
		if (ER_OK != status) {
			printf("alljoyn_busattachment_connect(\"%s\") failed\n", connectArgs);
		}
		else {
			printf("alljoyn_busattachment connected to \"%s\"\n", alljoyn_busattachment_getconnectspec(g_msgBus));
		}
	}

	g_busListener = alljoyn_buslistener_create(&callbacks, NULL);

	/* Register a bus listener in order to get discovery indications */
	if (ER_OK == status) {
		alljoyn_busattachment_registerbuslistener(g_msgBus, g_busListener);
		printf("alljoyn_buslistener Registered.\n");
	}

	/* Begin discovery on the well-known name of the service to be called */
	if (ER_OK == status) {
		status = alljoyn_busattachment_findadvertisedname(g_msgBus, OBJECT_NAME);
		if (status != ER_OK) {
			printf("alljoyn_busattachment_findadvertisedname failed (%s))\n", QCC_StatusText(status));
		}
	}



	return;
}


void airbox_delete(void)
{
	QStatus status = ER_OK;
	/* Deallocate bus */
	if (g_msgBus) {
		alljoyn_busattachment deleteMe = g_msgBus;
		g_msgBus = NULL;
		alljoyn_busattachment_destroy(deleteMe);
	}

	/* Deallocate bus listener */
	alljoyn_buslistener_destroy(g_busListener);

	printf("basic client exiting with status %d (%s)\n", status, QCC_StatusText(status));
}

void airbox_loop(void)
{
	if (1 == busflag) {
		alljoyn_proxybusobject remoteObj = alljoyn_proxybusobject_create(g_msgBus, serviceName, OBJECT_PATH, s_sessionId);
		const alljoyn_interfacedescription alljoynTestIntf = alljoyn_busattachment_getinterface(g_msgBus, INTERFACE_NAME);
		assert(alljoynTestIntf);
		alljoyn_proxybusobject_addinterface(remoteObj, alljoynTestIntf);

		doStatus(&remoteObj);

		alljoyn_proxybusobject_destroy(remoteObj);
	}
	else
	{
		return;
	}
}


void doStatus(alljoyn_proxybusobject *remoteObj)
{
	QStatus status = ER_OK;
	alljoyn_msgarg inputs;
	int num = 0;
	int16_t temp = 0;
	int16_t hum = 0;


	inputs = alljoyn_msgarg_create();
	status = alljoyn_proxybusobject_getproperty(*remoteObj, INTERFACE_NAME, "Version", inputs);
	if (ER_OK == status) {
		status = alljoyn_msgarg_get(inputs, "u", &num);
	}
	alljoyn_msgarg_destroy(inputs);

	inputs = alljoyn_msgarg_create();
	status = alljoyn_proxybusobject_getproperty(*remoteObj, INTERFACE_NAME, "TempValue", inputs);
	if (ER_OK == status) {
		status = alljoyn_msgarg_get(inputs, "q", &temp);
		temp = (temp - 300);
		extern int Gtemp;
		Gtemp = temp;
	}
	alljoyn_msgarg_destroy(inputs);

	inputs = alljoyn_msgarg_create();
	status = alljoyn_proxybusobject_getproperty(*remoteObj, INTERFACE_NAME, "HumValue", inputs);
	if (ER_OK == status) {
		status = alljoyn_msgarg_get(inputs, "q", &hum);
		extern int Ghum;
		Ghum = hum;
	}
	alljoyn_msgarg_destroy(inputs);
}

