/*
- mc/FixPigmanCD.cpp
*/
#include "mc.h"
#include "../hooks/Hooks.h"

namespace nya_tools::mc
{
    void FixPigmanCD(bool bl)
    {
        nya_tools::hooks::RegisterFixPigmanCDHook(bl);
    }
}