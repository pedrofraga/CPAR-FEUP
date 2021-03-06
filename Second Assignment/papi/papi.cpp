#include "papi.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int EventSet = PAPI_NULL;
long long values[2];

void handle_error(int retval) {
  printf("PAPI error %d: %s\n", retval, PAPI_strerror(retval));
  exit(1);
}
void init_papi() {
  int retval = PAPI_library_init(PAPI_VER_CURRENT);
  if (retval != PAPI_VER_CURRENT && retval < 0) {
    printf("PAPI library version mismatch!\n");
    exit(1);
  }
  if (retval < 0) handle_error(retval);

  cout << "PAPI Version Number: MAJOR: " << PAPI_VERSION_MAJOR(retval)
            << " MINOR: " << PAPI_VERSION_MINOR(retval)
            << " REVISION: " << PAPI_VERSION_REVISION(retval) << "\n";
}

int init_papi_events() {
  int ret;

  ret = PAPI_library_init( PAPI_VER_CURRENT );
	if ( ret != PAPI_VER_CURRENT )
	cout << "FAIL" << endl;

  ret = PAPI_create_eventset(&EventSet);
	if (ret != PAPI_OK) cout << "ERRO: create eventset" << endl;


	ret = PAPI_add_event(EventSet,PAPI_L1_DCM );
	if (ret != PAPI_OK) cout << "ERRO: PAPI_L1_DCM" << endl;


	ret = PAPI_add_event(EventSet,PAPI_L2_DCM);
	if (ret != PAPI_OK) cout << "ERRO: PAPI_L2_DCM" << endl;

  // Start counting
  ret = PAPI_start(EventSet);
  if (ret != PAPI_OK) cout << "ERRO: Start PAPI" << endl;

  return ret;
}
int print_papi_events() {
  int ret;

  ret = PAPI_stop(EventSet, values);
  if (ret != PAPI_OK) cout << "ERRO: Stop PAPI" << endl;
  return ret;
}
long long get_l1_dcm() {
  return values[0];
}
long long get_l2_dcm() {
  return values[1];
}
int stop_papi_events() {
  int ret;
  ret = PAPI_reset(EventSet);
  if (ret != PAPI_OK)
    cout << "FAIL reset" << endl;

  return ret;
}
