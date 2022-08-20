#ifndef test_as_included
#define test_as_included

#runtime "hsp3cl"
#include "result_format.as"

goto *__test_as_end

*__testinit
    onerror goto *__error
    #include "exception_code.as"
    dim __errline, 1024
    sdim __errfile, 32, 1024
    return

*__error
    mes get_fail_result_format(__errline@(__sublev@), __errfile@(__sublev@), errmsg(wparam - 1))
    end wparam

*__test_as_end

#endif