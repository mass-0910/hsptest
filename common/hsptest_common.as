#ifndef test_as_included
#define test_as_included

#runtime "hsp3cl"
#include "hsptest_result_format.as"

goto *__test_as_end

*__testinit
    onerror goto *__error
    #include "hsptest_exception_code.as"
    dim __errline, 1024
    sdim __errfile, 32, 1024
    sdim __output_buf, 1024
    __stdout_handle = GetStdHandle(-11)
    return

*__error
    __output_buf = get_fail_result_format(__errline@(__sublev@), __errfile@(__sublev@), errmsg(wparam)) + "\n"
    WriteFile __stdout_handle, __output_buf, strlen(__output_buf), 0, 0
    repeat __sublev@
        __output_buf = get_callstack_format(__errfile@(cnt + 1), __errline@(cnt + 1), cnt) + "\n"
        WriteFile __stdout_handle, __output_buf, strlen(__output_buf), 0, 0
    loop
    end wparam

*__test_as_end

#endif