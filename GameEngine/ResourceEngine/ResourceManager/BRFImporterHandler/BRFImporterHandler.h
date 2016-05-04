#pragma once
#include <BRFImporterStructs.h>
#include <FileData.h>
#include <Fetch.h>
#include <MeshData.h>
#include <MaterialData.h>
#include <SkeletonData.h>

#include "../MeshManager/MeshManager.h"
#include "../ShaderManager/ShaderManager.h"
#include "../../ObjectNode/Mesh/Mesh.h"
#include "../../../Structs/DataTypes.h"
#include "../MaterialManager/MaterialManager.h"

class BRFImporterHandler
{
private:
	unsigned int materialID;
	//unsigned int offsetMaterial;

	BRFImporterLib::FileData* currentFile;
	MeshManager* meshManager;
	MaterialManager* materialManager;
public:
	BRFImporterHandler();
	~BRFImporterHandler();

	void LoadFile(std::string fileName, bool mesh, bool material, bool skeleton, bool isScene);

	void Initialize(MeshManager* meshManager, MaterialManager* materialManager);
	void Release();
};

