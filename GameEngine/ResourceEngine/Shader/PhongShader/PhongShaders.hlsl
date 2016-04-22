cbuffer cameraConstantBuffer  : register(b0)
{

	matrix view;
	matrix projection;
	float4 camPos;
	float4 mousePos;
	//float3 camLook;

};
cbuffer worldConstantBuffer : register(b1)
{
	matrix world;
};

cbuffer lightBuffer : register(b2)
{
	
};
cbuffer textureSampleBuffer : register(b3)
{	
	bool diffuseMap;
	bool normalMap;
	bool specularMap;
	bool glowMap;
};


struct VS_IN
{
	float3 Pos			 : POSITION;
	float3 Normal		 : TEXCOORD0;
	float2 Uv			 : TEXCOORD1;
	float2 BiTangent	 : TEXCOORD2;
	float2 Tangent		 : TEXCOORD3;
};

struct VS_OUT
{

	float4 Pos			 : SV_POSITION;
	float3 Normal		 : TEXCOORD0;
	float2 Uv			 : TEXCOORD1;
	float3 BiTangent	 : TEXCOORD2;
	float3 Tangent		 : TEXCOORD3;
};

//Vertex shader
VS_OUT VS_main( VS_IN input)
{
	VS_OUT output;
	output.Pos				 = float4(input.Pos, 1.0f);
	output.Normal			 = input.Normal ;
	output.Uv				 = input.Uv;
	output.BiTangent		 = float3(input.BiTangent, 1.0f);	//z value NEEDS TO BE CALCULATED (1 is just a placeholder!!)
	output.Tangent			 = float3(input.Tangent, 1.0f);		//z value NEEDS TO BE CALCULATED (1 is just a placeholder!!)

	return output;
}


struct GS_OUT
{
	float4 Pos			: SV_POSITION;
	float3 Normal		: TEXCOORD0;
	float2 Uv			: TEXCOORD1;
	float3 BiTangent	: TEXCOORD2;
	float3 Tangent		: TEXCOORD3;


	float4 wPos			: WORLDPOS;
	float4 camPos		: CAMERAPOS;
	float4 mousePos		: MOUSEPOS;

};

[maxvertexcount(3)]
//Geometry shader!
void GS_main(
	triangle VS_OUT input[3],
	inout TriangleStream< GS_OUT > output)
{
	//combining the matrices for simpler use, also more efficient
	matrix combinedMatrix = mul(world, mul(view, projection));

	for (uint i = 0; i < 3; i++)
	{
		GS_OUT element;
		element.Pos			 = mul(input[i].Pos,combinedMatrix);
		element.Normal		 = input[i].Normal;
		element.Uv			 = input[i].Uv;
		element.BiTangent	 = input[i].BiTangent;
		element.Tangent		 = input[i].Tangent;





		element.wPos	 = mul(input[i].Pos,world);
		element.camPos	 = camPos;
		element.mousePos = mousePos;
		output.Append(element);
	}


}

SamplerState SampleType;

Texture2D shaderTexture : register(t0);

float4 PS_main(GS_OUT input) : SV_TARGET
{

float attenuation	= 0.05;
float4 playerPos	= { input.camPos.x,0.0,input.camPos.z + 10.0f ,1.0 };


float4 col			 = {1.0,1.0,1.0,1.0};
float4 pixelPos		 = {input.wPos.x, 0.0 , input.wPos.z, 1.0 };


float4 lightOne		 = { 20.0, 0.0, -20, 1.0};
col.y				+= 1.0 - saturate(abs(distance(lightOne, pixelPos) * attenuation));


float4 lightTwo		 = { -20.0, 0.0, 20.0, 1.0 };
col.z += 1.0 - saturate(abs(distance(lightTwo, pixelPos) * attenuation));


float4 lightThree	 = { -20.0, 0.0, -20.0, 1.0 };
col.xz += 1.0 - saturate(abs(distance(lightThree, pixelPos) * attenuation));


float4 lightFour	 = {  20.0, 0.0,  20.0, 1.0 };
col.xy += 1.0 - saturate(abs(distance(lightFour, pixelPos) * attenuation));


//float dist			 = distance(playerPos.xz,pixelPos.xz);
float dist			 = distance(input.mousePos.xz, pixelPos.xz);

col.xyz			    -= saturate(	abs( dist )	* 0.3	);  //player color fade 

col.y				+= saturate(input.wPos.y);			// green color, (for the objects)

if (diffuseMap == true)
{

	float3 textureSample = shaderTexture.Sample(SampleType, input.Uv).xyz;
	col.xyz = textureSample;
}




return col;
}





