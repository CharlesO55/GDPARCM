#include "AppWindow.h"

#include "ImageLoader.h"
#include "EngineTime.h"

int main()
{
    AppWindow app;

    EngineTime::Init();
    ImageLoader::Init();

    app.Init();

    while (app.Run()) {
        EngineTime::Update();
    }

    app.Close();
    ImageLoader::Destroy();
    EngineTime::Destroy();

    return 0;
}