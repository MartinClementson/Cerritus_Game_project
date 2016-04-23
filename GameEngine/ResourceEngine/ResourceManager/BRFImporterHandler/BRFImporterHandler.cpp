#include "BRFImporterHandler.h"

BRFImporterHandler::BRFImporterHandler()
{
}

BRFImporterHandler::~BRFImporterHandler()
{
}

void BRFImporterHandler::LoadFile(std::string fileName, bool mesh, bool material, bool skeleton)
{
	
	this->currentFile->LoadFile(fileName, mesh, skeleton, material);

#pragma region Loop for reading mesh info & provide to meshManager.
	unsigned int size = currentFile->fetch->Main()->meshAmount;
	for (unsigned int i = 0; i < size; i++)
	{

#pragma region Statements handling skeletons.

		bool tempHasSkeleton = currentFile->fetch->Mesh(i)->GetMeshData()->hasSkeleton;
		unsigned int tempSkeletonID;
		if (tempHasSkeleton == true && skeleton == true)			//If mesh has skeleton & we wanted to load skeletons
		{
			tempSkeletonID = currentFile->fetch->Skeleton(i)->GetSkeletonData()->skeletonID;
		}
		else if (tempHasSkeleton == true && skeleton == false)		//If mesh has skeleton but we didnt want to load skeletons
		{
			tempHasSkeleton = false;
			tempSkeletonID = 0;
		}
		else														//If mesh doesnt have skeleton and/or we didnt want to load skeletons
		{
			tempHasSkeleton = false;
			tempSkeletonID = 0;
		}

#pragma endregion

#pragma region Statements handling material.

		unsigned int tempMaterialID;
		if (material == true)					//If we wanted to load materials.
		{
			tempMaterialID = currentFile->fetch->Material(i)->Id;
		}
		else									//IF we didnt want to load materials.
		{
			tempMaterialID = 0;
		}

#pragma endregion

#pragma region Statements handling vertices.

		unsigned int tempVertexCount = currentFile->fetch->Mesh(i)->GetMeshData()->vertexCount;
		std::vector<Vertex> tempVertices;
		std::vector<AnimVert> tempAniVertices;
		if (tempHasSkeleton == true)
		{
			
			int k = 4;
			for (unsigned int j = 0; j < tempVertexCount; j++)			//Goes through every vertex individually, copies pos Data then adds to a vertices vector.
			{
				AnimVert tempVert;
				tempVert.position = {
					(float)currentFile->fetch->Mesh(i)->GetVertexData(j).pos[0],
					(float)currentFile->fetch->Mesh(i)->GetVertexData(j).pos[1],
					(float)currentFile->fetch->Mesh(i)->GetVertexData(j).pos[2],
				};
				tempVert.normal = {
					(float)currentFile->fetch->Mesh(i)->GetVertexData(j).normal[0],
					(float)currentFile->fetch->Mesh(i)->GetVertexData(j).normal[1],
					(float)currentFile->fetch->Mesh(i)->GetVertexData(j).normal[2],
				};
				tempVert.uv = {
					(float)currentFile->fetch->Mesh(i)->GetVertexData(j).uv[0],
					(float)currentFile->fetch->Mesh(i)->GetVertexData(j).uv[1]
				};
				tempVert.tangent = {
					(float)currentFile->fetch->Mesh(i)->GetVertexData(j).tangent[0],
					(float)currentFile->fetch->Mesh(i)->GetVertexData(j).tangent[1]
				};
				tempVert.biTangent = {
					(float)currentFile->fetch->Mesh(i)->GetVertexData(j).biTangent[0],
					(float)currentFile->fetch->Mesh(i)->GetVertexData(j).biTangent[1]
				};
				tempVert.weights = {
					(float)currentFile->fetch->Mesh(i)->GetWeightData(j * k).influence,
					(float)currentFile->fetch->Mesh(i)->GetWeightData(j * k + 1).influence,
					(float)currentFile->fetch->Mesh(i)->GetWeightData(j * k + 2).influence,
					(float)currentFile->fetch->Mesh(i)->GetWeightData(j * k + 3).influence,
				};
				tempVert.jointID = {
					(unsigned int)currentFile->fetch->Mesh(i)->GetWeightData(j * k).jointID,
					(unsigned int)currentFile->fetch->Mesh(i)->GetWeightData(j * k + 1).jointID,
					(unsigned int)currentFile->fetch->Mesh(i)->GetWeightData(j * k + 2).jointID,
					(unsigned int)currentFile->fetch->Mesh(i)->GetWeightData(j * k + 3).jointID,
				};
				tempAniVertices.push_back(tempVert);
			}
			tempAniVertices.shrink_to_fit();
		}
		else
		{
			for (unsigned int j = 0; j < tempVertexCount; j++)			//Goes through every vertex individually, copies pos Data then adds to a vertices vector.
			{
				Vertex tempVert;
				tempVert.position = {
					(float)currentFile->fetch->Mesh(i)->GetVertexData(j).pos[0],
					(float)currentFile->fetch->Mesh(i)->GetVertexData(j).pos[1],
					(float)currentFile->fetch->Mesh(i)->GetVertexData(j).pos[2],
				};
				tempVert.normal = {
					(float)currentFile->fetch->Mesh(i)->GetVertexData(j).normal[0],
					(float)currentFile->fetch->Mesh(i)->GetVertexData(j).normal[1],
					(float)currentFile->fetch->Mesh(i)->GetVertexData(j).normal[2],
				};
				tempVert.uv = {
					(float)currentFile->fetch->Mesh(i)->GetVertexData(j).uv[0],
					(float)currentFile->fetch->Mesh(i)->GetVertexData(j).uv[1]
				};
				tempVert.tangent = {
					(float)currentFile->fetch->Mesh(i)->GetVertexData(j).tangent[0],
					(float)currentFile->fetch->Mesh(i)->GetVertexData(j).tangent[1]
				};
				tempVert.biTangent = {
					(float)currentFile->fetch->Mesh(i)->GetVertexData(j).biTangent[0],
					(float)currentFile->fetch->Mesh(i)->GetVertexData(j).biTangent[1]
				};
				tempVertices.push_back(tempVert);
			}
			tempVertices.shrink_to_fit();
		}

#pragma endregion

#pragma region Statements handling indices.

		UINT tempIndexCount = currentFile->fetch->Mesh(i)->GetMeshData()->indexCount;
		std::vector<UINT> tempIndices;
		for (unsigned int j = 0; j < tempIndexCount; j++)
		{
			UINT tempIndex;
			tempIndex = currentFile->fetch->Mesh(i)->GetIndexData(j).vertIndex;
			tempIndices.push_back(tempIndex);
		}
		tempIndices.shrink_to_fit();

#pragma endregion

		this->meshManager->AddMesh(tempHasSkeleton, tempSkeletonID, tempMaterialID, tempVertexCount, tempIndexCount, tempVertices, tempAniVertices, tempIndices);					//Keep me!
	}
#pragma endregion
#pragma region Loop for reading material info & provide to materialManager.
	//temporary vector for the materials
	std::vector<importedMaterial> importedMaterials;

	size = currentFile->fetch->Main()->materialAmount;
	for (unsigned int i = 0; i < size; i++)
	{
		importedMaterial tempMaterial;
		tempMaterial.materialName = (std::string)currentFile->fetch->Material(i)->matName;

		tempMaterial.materialID = currentFile->fetch->Material(i)->Id;

		//getting the diffuse values
		tempMaterial.diffuseValue = {
			(float)currentFile->fetch->Material(i)->diffuseVal[0],
			(float)currentFile->fetch->Material(i)->diffuseVal[1],
			(float)currentFile->fetch->Material(i)->diffuseVal[2] };

		//getting the specular values
		tempMaterial.specularValue = { 
			(float)currentFile->fetch->Material(i)->specularVal[0],
			(float)currentFile->fetch->Material(i)->specularVal[1],
			(float)currentFile->fetch->Material(i)->specularVal[2] };

		//getting all the maps
		tempMaterial.diffuseTex = (std::string)currentFile->fetch->Material(i)->diffMap;
		tempMaterial.specularTex = (std::string)currentFile->fetch->Material(i)->specMap;
		tempMaterial.normalTex = (std::string)currentFile->fetch->Material(i)->normalMap;
		tempMaterial.glowTex = (std::string)currentFile->fetch->Material(i)->glowMap;

		importedMaterials.push_back(tempMaterial);
	}
	importedMaterials.shrink_to_fit();
	// materialmannager func here!
#pragma endregion

}

void BRFImporterHandler::Initialize(MeshManager * meshManager, MaterialManager* materialManager)
{
	this->currentFile = new BRFImporterLib::FileData;
	this->meshManager = meshManager;
	this->materialManager = materialManager;
}

void BRFImporterHandler::Release()
{
	delete this->currentFile;
}
