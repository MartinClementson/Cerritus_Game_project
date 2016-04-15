#pragma once
#include "RenderInfo.h"
#include "LibIncluder.h"
#include "Constants.h"
#include "Mesh.h"
#include "Enumerations.h"
class MeshManager
{

private:
	ID3D11Device *gDevice = nullptr;
	ID3D11DeviceContext* gDeviceContext = nullptr;

	//This vector will be indexed with the enum "Meshes"
	std::vector<Mesh>* gameMeshes		=	nullptr;
	Mesh placeHolder;

	void CreatePlaceHolder();
public:
	MeshManager();
	~MeshManager();
	
	void Initialize(ID3D11Device *gDevice, ID3D11DeviceContext* gDeviceContext);
	void Release();

	void GetMeshRenderInfo(Meshes* meshEnum, RenderInstructions* toRender);

	void GetPlaceHolderMeshInfo(RenderInstructions* toRender);
};

