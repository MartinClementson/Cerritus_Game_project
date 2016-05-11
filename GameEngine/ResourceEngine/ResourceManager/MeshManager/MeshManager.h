#pragma once
#include "../../../Structs/RenderInfo.h"
#include "../../../Source/Constants.h"
#include "../../../Source/LibIncluder.h"
#include "../../ObjectNode/Mesh/Mesh.h"
#include "../../../Enumerations/Enumerations.h"
class MeshManager
{

private:
	ID3D11Device		*	 gDevice			 = nullptr;
	ID3D11DeviceContext	*	 gDeviceContext		 = nullptr;

	//This vector will be indexed with the enum "Meshes"
	std::vector<Mesh>*		  gameMeshes		 =	nullptr;
	Mesh					  placeHolder;
	Mesh					  placeHolderPlane;
	Mesh					  fullScreenQuad;

	std::vector<Mesh>*		  animatedMeshes	 =  nullptr;
	std::vector<std::vector<Mesh*>>*		  blendShapeMeshes; //2d array. first is animations, then in each animation is every mesh(aka keyframe)
	std::vector<ID3D11ShaderResourceView*> morphAnimStructuredBuffersSRV;
	std::vector<ID3D11Buffer*>			   morphAnimStructuredBuffers;
	int animationBufferCount = 0;
	void CreatePlaceHolder();
	void CreatePlaceHolderPlane();
	Mesh* CreatePlaceHolderBlendShape();
	Mesh* CreateBlendShape(BlendShapeVert* vertices,unsigned int amount);
	void CreateFullScreenQuad();
public:
	MeshManager();
	~MeshManager();
	
	void Initialize(ID3D11Device *gDevice, ID3D11DeviceContext* gDeviceContext);
	void Release();

	void AddMesh(
		bool hasSkeleton,
		unsigned int skeletonID,
		int materialID,
		unsigned int vertexCount,
		UINT indexCount,
		std::vector<Vertex> vertices,
		std::vector<AnimVert> aniVertices,
		std::vector<UINT> indices
		);

	std::vector<Mesh>* GetMeshes() { return this->gameMeshes; }
	void GetMeshRenderInfo			(MeshEnum* meshEnum, RenderInstructions* toRender);

	void GetPlaceHolderMeshInfo		(RenderInstructions* toRender);
	void GetPlaceHolderPlaneInfo	(RenderInstructions* toRender);
	void GetFullScreenQuadInfo		(RenderInstructions* toRender);
	void GetFullScreenQuadInfoUI	(UITextures* uiEnum, RenderInstructions* toRender);
	
	void CreateAnimationFromMeshes(
		std::vector<Vertex> sourceMesh,
		std::vector<AnimationInfo> animations
		);

};

