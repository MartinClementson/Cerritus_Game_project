#pragma once
#include <vector>
#include "MeshData.h"
#include "MaterialData.h"
#include "LightData.h"
#include "SkeletonData.h"

namespace BRFImporterLib
{
	class FetchContainer
	{
	private:
		std::shared_ptr<MainHeader> mainData;
		std::vector<std::shared_ptr<MeshData>> meshes;
		std::shared_ptr<MaterialData> materialData;
		std::vector<std::shared_ptr<SkeletonData>> skeletons;
	public:
		MainHeader* getMain();
		MeshHeader* GetMeshHeader(unsigned int meshID);
		MeshData* GetMesh(unsigned int meshID);
		MaterialContainer* GetMaterial(unsigned int materialID);
		SkeletonData* GetSkeleton(unsigned int skeletonID);
		//CONDECON
		FetchContainer(
			std::shared_ptr<MainHeader> mainData,
			std::vector<std::shared_ptr<MeshData>> meshVector,
			std::shared_ptr<MaterialData> materialData,
			std::vector<std::shared_ptr<SkeletonData>> skeletonVector
			);
		~FetchContainer();
	};

	class Fetch
	{
	
	private:
		std::shared_ptr<FetchContainer> FetchDataContainer;
	public:
		MainHeader* Main();
		MeshData* Mesh(unsigned int meshID);
		MaterialContainer* Material(unsigned int materialID);
		SkeletonData* Skeleton(unsigned int skeletonID);
		AnimationHeader* Animation(unsigned int skeletonID, unsigned int animationID);
		//LightData* Light(unsigned int lightID);

		//CON DECON
		Fetch(std::shared_ptr<FetchContainer> fileFetch);

		Fetch();
		~Fetch();

	};
}
