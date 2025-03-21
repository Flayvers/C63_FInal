#ifndef __CUSTOMMACRO_H
#define __CUSTOMMACRO_H

#define NATURAL_NUMBER 2.73f
#define FIBONNACCI_NUMBER 1.618f
#define WIERD_NUMBER NATURAL_NUMBER + FIBONNACCI_NUMBER

#undef WIERD_NUMBER

#define WIERD_NUMBER (NATURAL_NUMBER + FIBONNACCI_NUMBER)

#define LOG(message) std::cout << "In " << __FILE__ << " at line " << __LINE__ << " " << message;

#endif