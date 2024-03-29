#ifndef assertion_as_included
#define assertion_as_included

#include "hsptest_result_format.as"

#module

#define global __init_msg "Assertion was failed"
#define global assertTrue(%1, %2=__init_msg) __errline_a=__errline@(sublev):__errfile_a=__errfile@(sublev):if (%1)==0:WriteFile __stdout_handle@,get_fail_result_format(__errline_a,__errfile_a,%2)+"\n",strlen(get_fail_result_format(__errline_a,__errfile_a,%2)+"\n"),0,0:end 1
#define global assertFalse(%1, %2=__init_msg) __errline_a=__errline@(sublev):__errfile_a=__errfile@(sublev):if (%1)!=0:WriteFile __stdout_handle@,get_fail_result_format(__errline_a,__errfile_a,%2)+"\n",strlen(get_fail_result_format(__errline_a,__errfile_a,%2)+"\n"),0,0:end 1
#define global assertEqual(%1, %2, %3=__init_msg) __errline_a=__errline@(sublev):__errfile_a=__errfile@(sublev):if (%1)!=(%2):WriteFile __stdout_handle@,get_fail_result_format(__errline_a,__errfile_a,%3)+"\n",strlen(get_fail_result_format(__errline_a,__errfile_a,%3)+"\n"),0,0:end 1
#define global assertNear(%1, %2, %3=0.0001, %4=__init_msg) __errline_a=__errline@(sublev):__errfile_a=__errfile@(sublev):if absf(double(%1)-double(%2))>(%3):WriteFile __stdout_handle@,get_fail_result_format(__errline_a,__errfile_a,%4)+"\n",strlen(get_fail_result_format(__errline_a,__errfile_a,%4)+"\n"),0,0:end 1

#global

#endif