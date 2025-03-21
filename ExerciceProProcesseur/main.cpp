#include <iostream>
#include <raylib.h>
#include "custommacro.h"
#include "custommacro.h"

int main(void)
{   

    LOG("NATURAL_NUMBER : " << NATURAL_NUMBER << std::endl);
    LOG("FIBONNACCI_NUMBER : " << FIBONNACCI_NUMBER << std::endl);
    LOG("WIERD_NUMBER : " << WIERD_NUMBER << std::endl);
    LOG("2.0f * NATURAL_NUMBER + WIERD_NUMBER : " << 2.0f * NATURAL_NUMBER + WIERD_NUMBER << std::endl);
    LOG("2.0f * WIERD_NUMBER : " << 2.0f * WIERD_NUMBER << std::endl);

    return 0;
}
