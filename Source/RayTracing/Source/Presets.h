#pragma once

#include "RenderSettings.h"
#include "hittable_list.h"

class Presets
{
public:
	static RenderSettings CreateSettings(int ID);
	static hittable_list CreateWorld(int ID);

private:
	static void CreateSmallSpheres(hittable_list& world);
	static void CreateBigSpheres(hittable_list& world);
	static void CreateStackedSpheres(hittable_list& world);
};