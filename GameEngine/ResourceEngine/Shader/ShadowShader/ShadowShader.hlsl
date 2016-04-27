
cbuffer worldConstantBuffer : register(b1)
{
	matrix world;
};
cbuffer lightBuffer : register(b2)
{
	float4 lightPosition;
	matrix lightView;
	matrix lightProjection;
	float4 lightDir;
	float4 lightDiffuse;
	float intensity;
};

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




SHADOW_VS_OUT SHADOW_VS_main( SHADOW_VS_IN input ) : SV_POSITION
{
	SHADOW_VS_OUT output = (SHADOW_VS_OUT)0;
	output.position = input.position;

	return output;
}

[maxvertexcount(30)]
//Geometry shader!
void SHADOW_GS_main( //GO THROUGH VARIABLES
	triangle SHADOW_VS_OUT input[3],
	inout TriangleStream< SHADOW_GS_OUT > output)
{
	//matrix combinedMatrix = mul(world, mul(view, projection));

	SHADOW_GS_OUT element;
	for (uint rt_Index = 0; rt_Index < 4; rt_Index++)
	{

		element.rtIndex = rt_Index;

		//Get light matrix from array here
		// LightStruct light = lightArray[rt_index]

		[unroll]for (int i = 0; i < 3; i++)
		{	
			matrix combinedMatrix = mul(world, mul(lightView, lightProjection));
			element.position = mul(input[i].position, combinedMatrix);

			output.Append(element);
		}
		output.RestartStrip();


	}


}