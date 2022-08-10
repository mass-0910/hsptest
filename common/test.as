#runtime "hsp3cl"
#include "exception_code.as"

goto *__test_as_end

*__testinit
    onerror goto *__error
    #include "exception_code.as"
    return

*__error
    mes "&RESULT&{" + "FAIL" + "," + lparam + "," + wparam + "," + errmsg(wparam - 1) + "}"
    end wparam

*__test_as_end