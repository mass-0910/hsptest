#define __init_msg "Assertion was failed"
#define assertTrue(%1, %2=__init_msg) if (%1)==0:mes "&RESULT&{"+"FAIL"+","+__line__+",42,"+%2+"}":return
#define assertFalse(%1, %2=__init_msg) if (%1)!=0:mes "&RESULT&{"+"FAIL"+","+__line__+",42,"+%2+"}":return
#define assertEqual(%1, %2, %3=__init_msg) if (%1)!=(%2):mes "&RESULT&{"+"FAIL"+","+__line__+",42,"+%3+"}":return
#define assertNear(%1, %2, %3=0.0001, %4=__init_msg) if absf(double(%1)-double(%2))>(%3):mes "&RESULT&{"+"FAIL"+","+__line__+",42,"+%4+"}":return