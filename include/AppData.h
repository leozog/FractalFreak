#pragma once
#include "ff/Animation.h"
#include "ff/FractalParameters.h"
#include "ff/FractalGenerator.h"
#include "FractalsDefinitions.h"

class AppData
{
public:
    std::unique_ptr<Animation> animation;
    AppData()
    {
    }
};