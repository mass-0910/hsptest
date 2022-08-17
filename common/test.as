#ifndef test_as_included
#define test_as_included

#runtime "hsp3cl"
#include "result_format.as"

goto *__test_as_end

*__testinit
    onerror goto *__error
    #include "exception_code.as"
    return

*__error
    mes get_fail_result_format(__errline@, __errfile@, errmsg(wparam - 1))
    end wparam

*__test_as_end

#endif