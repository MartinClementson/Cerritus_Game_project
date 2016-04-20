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


struct VS_IN
{
	float3 Pos		: POSITION;
	//float2 Uv		: TEXCOORD0;
	//float3 Normal	: NORMAL;
	//float3 Tangent	: TANGENT;
};

struct VS_OUT
{

	float4 Pos		 : SV_POSITION;
	//float2 Uv		 : TEXCOORD0;
	//float3 Normal	 : NORMAL;
	//float3 Tangent	 : TANGENT;

};

//Vertex shader
VS_OUT VS_main( VS_IN input)
{
	VS_OUT output;
	output.Pos = float4(input.Pos, 1.0f);

	
	return output;
}


struct GS_OUT
{
	float4 Pos			: SV_POSITION;
	//float2 Uv			: TEXCOORD0;
	//float3 Normal		: NORMAL;
	float4 wPos			: WORLDPOS;
	float4 camPos		: CAMERAPOS;
	float4 mousePos		: MOUSEPOS;
	//float3 Tangent		: TANGENT;

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
		element.Pos		 = mul(input[i].Pos,combinedMatrix);
		element.wPos	 = mul(input[i].Pos,world);
		element.camPos	 = camPos;
		element.mousePos = mousePos;
		output.Append(element);
	}


}


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

col.xyz			    -= saturate(	abs( dist )	* 0.0005	);  //player color fade 

col.y				+= saturate(input.wPos.y);			// green color, (for the objects)






return col;
}





