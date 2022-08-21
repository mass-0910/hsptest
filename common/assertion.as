#ifndef assertion_as_included
#define assertion_as_included

#include "result_format.as"

#module

#define global __init_msg "Assertion was failed"
#define global assertTrue(%1, %2=__init_msg) __errline_a=__errline@(sublev):__errfile_a=__errfile@(sublev):if (%1)==0:mes get_fail_result_format(__errline_a,__errfile_a,%2):end 1
#define global assertFalse(%1, %2=__init_msg) __errline_a=__errline@(sublev):__errfile_a=__errfile@(sublev):if (%1)!=0:mes get_fail_result_format(__errline_a,__errfile_a,%2):end 1
#define global assertEqual(%1, %2, %3=__init_msg) __errline_a=__errline@(sublev):__errfile_a=__errfile@(sublev):if (%1)!=(%2):mes get_fail_result_format(__errline_a,__errfile_a,%3):end 1
#define global assertNear(%1, %2, %3=0.0001, %4=__init_msg) __errline_a=__errline@(sublev):__errfile_a=__errfile@(sublev):if absf(double(%1)-double(%2))>(%3):mes get_fail_result_format(__errline_a,__errfile_a,%3):end 1

#global

#endif