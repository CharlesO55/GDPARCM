#include "EngineTime.h"
#include "Debugger.h"

EngineTime* EngineTime::i = NULL;

const float minDelta = 1 / 60.f;


void EngineTime::Init()
{
    if (i != NULL) {
        Debugger::Print("[Duplicate] EngineTime", EnumMsg::WARNING);
        return;
    }

    i = new EngineTime();

    i->m_Clock.restart();
}

void EngineTime::Update()
{
    if (i->m_Tick) {
        i->m_Tick = false;
        i->m_DeltaTime = 0;
    }

    float d = i->m_Clock.restart().asSeconds();

    i->m_DeltaTime += d;

    if (i->m_DeltaTime > minDelta) {
        i->m_Tick = true;
        i->m_FPS = 1 / i->m_DeltaTime;
    }
}

void EngineTime::Destroy()
{
    delete i;
    Debugger::Print("[Destroy] EngineTime", EnumMsg::WARNING);
}

bool EngineTime::IsTick()
{
    return i->m_Tick;
}

const float EngineTime::GetDelta()
{
    return i->m_DeltaTime;
}

const float EngineTime::GetFPS()
{
    return i->m_FPS;
}
