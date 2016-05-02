cbuffer cbufferPerFrame  : register(b0)
{

	matrix view;
	matrix projection;
	matrix invViewProjMatrix;
	float4 camPos;
	float4 mousePos;
	int numPointLights;
	int numSpotLights;
	int numDirLights;
	float pad;

};



cbuffer worldConstantBuffer : register(b1)
{
	matrix world;
};

struct PointLight
{
	float4 lightPosition;
	matrix lightView;
	matrix lightProjection;
	float4 lightLookAt;
	float4 lightDiffuse;
	float intensity;
	float3 padI;
	float lightRange;
	float3 padR;
	float attenuation;
	float3 padA;
	bool castShadow;
};


struct DirectionalLight
{
	float4 lightPosition;
	matrix lightView;
	matrix lightProjection;
	float4 lightLookAt;
	float4 lightDiffuse;

	float intensity;
	float3 padI;

	bool castShadow;
	float3 padShadow;

};

StructuredBuffer<PointLight>		pointlights  : register(t8);
StructuredBuffer<DirectionalLight>  dirLights    : register(t9);

struct SHADOW_VS_IN
{
	float4 position		: POSITION;
};
struct SHADOW_VS_OUT
{
	float4 position		: SV_POSITION;
};
struct SHADOW_GS_OUT
{
	float4 position		: SV_POSITION;
	uint rtIndex		: SV_RenderTargetArrayIndex;
};




SHADOW_VS_OUT SHADOW_VS_main(SHADOW_VS_IN input) : SV_POSITION
{
	SHADOW_VS_OUT output = (SHADOW_VS_OUT)0;
output.position = input.position;

return output;
}



static const uint MAX_SHADOWMAP_AMOUNT = 4;


[maxvertexcount(200)]
//Geometry shader!
void SHADOW_GS_main( //GO THROUGH VARIABLES
	triangle SHADOW_VS_OUT input[3],
	inout TriangleStream< SHADOW_GS_OUT > output)
{
	//matrix combinedMatrix = mul(world, mul(view, projection));
	SHADOW_GS_OUT element;
	uint rt_index = 0; //Current shadow map to write to

	for (int d = 0; d < numDirLights; d++) // go through all the direction lights
	{

		if (dirLights[d].castShadow != 0) //if the light casts shadows
		{
			if (rt_index < MAX_SHADOWMAP_AMOUNT) //check that we havent reached maximum shadowmaps
			{

				[unroll]
				for (int i = 0; i < 3; i++) //loop through the verts of the face
				{
					element.rtIndex = rt_index;
					matrix combinedMatrix = mul(world, mul(dirLights[d].lightView, dirLights[d].lightProjection));
					element.position = mul(input[i].position, combinedMatrix);

					output.Append(element);
				}
				output.RestartStrip();
				rt_index += 1; // add 1 to the shadowmap index.
			}
		}

	}
	for (int i = 0; i < numPointLights; i++)
	{
		if (pointlights[i].castShadow != 0)
		{


			if (rt_index < MAX_SHADOWMAP_AMOUNT) //check that we havent reached maximum shadowmaps
			{

				[unroll]
				for (int j = 0; j < 3; j++) //loop through the verts of the face
				{
					element.rtIndex = rt_index;
					matrix combinedMatrix = mul(world, mul(pointlights[i].lightView, pointlights[i].lightProjection));
					element.position = mul(input[j].position, combinedMatrix);

					output.Append(element);
				}
				output.RestartStrip();
				rt_index += 1; // add 1 to the shadowmap index.
			}
		}

	}



	//for (uint rt_Index = 0; rt_Index < 4; rt_Index++) //4 is the LIGHT_SHADOW_AMOUNT
	//{

	//	element.rtIndex = rt_Index;

	//	//Get light matrix from array here
	//	// LightStruct light = lightArray[rt_index]


	//	[unroll]for (int i = 0; i < 3; i++)
	//	{	
	//		matrix combinedMatrix = mul(world, mul(lightView, lightProjection));
	//		element.position = mul(input[i].position, combinedMatrix);

	//		output.Append(element);
	//	}
	//	output.RestartStrip();


	//}


}