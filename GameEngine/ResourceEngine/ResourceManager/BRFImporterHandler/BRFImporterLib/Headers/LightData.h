#pragma once
#include <memory>
#include "BRFImporterStructs.h"

namespace BRFImporterLib
{
	class LightData
	{
	protected:
		LightHeader lightData;
		SpotLightHeader* spotLightData;
		AreaLightHeader* areaLightData;
		PointLightHeader* pointLightData;
		DirLightHeader* dirLightData;
	public:
		LightHeader GetLightData();
		SpotLightHeader* GetSpotLightData();
		AreaLightHeader* GetAreaLightData();
		PointLightHeader* GetPointLightData();
		DirLightHeader* GetDirLightData();

		//CON DECON
		LightData();
		~LightData();
	};
}