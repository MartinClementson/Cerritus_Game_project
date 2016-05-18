#pragma once
#include "../../../Structs/RenderInfo.h"
#include "../../../Source/Constants.h"
#include "../../../Source/LibIncluder.h"
#include "../../ObjectNode/Mesh/Mesh.h"
#include "../../../Enumerations/Enumerations.h"
#include "../../ObjectNode/QuadTree/QuadTree.h"


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
#pragma region Animation related
	/*
		We use blend shape animation.
		Every mesh that is a "source",( that is the visible geometry we are rendering and animating)
		Is in the animatedMeshes array.
		
		An animated mesh can have multiple animations and every animation is made up of keyframes.
		Each keyframe is a mesh. So every animation has an array of meshes.

		blendShapeMeshes is a 2d array that contains animation and the meshes for each keyframe

		blendShapeMeshes
		|____-Array of animations [vector<mesh>] 
		|_________- Each vector<mesh> has n amount of meshes, (keyframes)
				
		For every animation, we need a buffer and a related resource view to be bound to the gpu.

		So all the keyframes will be in one array in the gpu.

		the function CreateAnimationFromMeshes() 
		Takes a source mesh and n amount of animations and puts them into the corresponding arrays

		*/
						
	
	
	std::vector<Mesh>*					      animatedMeshes	 =  nullptr;
	std::vector<std::vector<Mesh*>>*		  blendShapeMeshes   =  nullptr;	//2d array. first is animations, then in each animation is every mesh(aka keyframe)
	
	std::vector<ID3D11ShaderResourceView*>	  morphAnimStructuredBuffersSRV;
	std::vector<ID3D11Buffer*>				  morphAnimStructuredBuffers;

	std::vector<ID3D11ShaderResourceView*>	  animFrameStructuredBuffersSRV; //structured buffers for the frame data
	std::vector<ID3D11Buffer*>				  animFrameStructuredBuffers;


	ID3D11ShaderResourceView*	  animHeaderStructuredBuffersSRV;
	ID3D11Buffer*				  animHeaderStructuredBuffers;
#pragma endregion

	int   animationBufferCount = 0;
	void  CreatePlaceHolder();
	void  CreatePlaceHolderPlane();
	Mesh* CreatePlaceHolderBlendShape();
	Mesh* CreateBlendShape(BlendShapeVert* vertices,unsigned int amount);
	void  CreateFullScreenQuad();
	void  CreatePlaceHolderAnimation();
	std::vector<Mesh>* gameMeshes		= nullptr;
	std::vector<Mesh>* sceneMeshes		= nullptr;
	Mesh placeHolder;
	Mesh placeHolderPlane;
	Mesh fullScreenQuad;
	Mesh killCountQuad;
	Mesh waveCountQuad;
	Mesh waveCompleteQuad;
	void CreateKillCountQuad();
	void CreateWaveCountQuad();
	void CreateWaveCompleteQuad();

public:
	QuadTree* quadTree;
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
		std::vector<UINT> indices,
		bool isScene
		);
	//UVoffset offset;
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

	std::vector<Mesh>* GetSceneMeshes() { return this->sceneMeshes; }
	void CreateQuadTree();
	void GetMeshRenderInfo(MeshEnum* meshEnum, RenderInstructions* toRender);

	
	void GetKillCountQuadInfoHud(UITextures * uiEnum, RenderInstructions* toRender);
	void GetWaveCountQuadInfoHud(UITextures*uiEnum, RenderInstructions*toRender);

};

