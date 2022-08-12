#ifndef assertion_as_included
#define assertion_as_included

#include "result_format.as"

#module

#define global __init_msg "Assertion was failed"
#define global assertTrue(%1, %2=__init_msg) if (%1)==0:mes get_fail_result_format(__line__,%2):return
#define global assertFalse(%1, %2=__init_msg) if (%1)!=0:mes get_fail_result_format(__line__,%2):return
#define global assertEqual(%1, %2, %3=__init_msg) if (%1)!=(%2):mes get_fail_result_format(__line__,%3):return
#define global assertNear(%1, %2, %3=0.0001, %4=__init_msg) if absf(double(%1)-double(%2))>(%3):mes get_fail_result_format(__line__,%3):return

#global

#endif