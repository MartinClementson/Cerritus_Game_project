

//GBUFFER
Texture2D diffuseTex			 : register(t0);
Texture2D normalTex				 : register(t1);
Texture2D specularTex			 : register(t2);
Texture2D glowTex				 : register(t3);
Texture2DArray shadowTex		 : register(t6);

SamplerState linearSampler		 : register(s0);
SamplerState pointSampler		 : register(s1);

cbuffer cbufferPerFrame     : register(b0)
{

	matrix view;
	matrix projection;
	matrix invViewProjMatrix;
	float4 camPos;
	float4 mousePos;
	int numPointLights;
	int numSpotLights;
	int numDirLights;
	//float3 camLook;

};

cbuffer textureSampleBuffer		 : register(b2)
{
	bool diffuseMap;
	bool normalMap;
	bool specularMap;
	bool glowMap;
};



struct BILLBOARD_VS_IN
{
	float3 worldPos		 : POSITION;
	float3 direction	 : DIRECTION;
	float3 color		 : COLOR;
	float  height		 : HEIGHT;
	float  width		 : WIDTH;
};
struct BILLBOARD_VS_OUT
{
	float4 worldPos		 : SV_POSITION;
	float3 direction	 : DIRECTION;
	float3 color		 : COLOR;
	float  height		 : HEIGHT;
	float  width		 : WIDTH;
};

struct BILLBOARD_GS_OUT
{
	float4 Pos			: SV_POSITION;
	float3 color		: COLOR;
	float3 Normal		: TEXCOORD0;
	float2 Uv			: TEXCOORD1;
	float3 BiTangent	: TEXCOORD2;
	float3 Tangent		: TEXCOORD3;


	float4 wPos			: WORLDPOS;
	float4 camPos		: CAMERAPOS;
	float4 mousePos		: MOUSEPOS;
};

struct BILLBOARD_PS_OUT
{
	float4 diffuseRes	: SV_Target0;
	float4 specularRes	: SV_Target1;
	float4 normalRes	: SV_Target2;
	float4 depthRes		: SV_Target3;
	float4 positionRes	: SV_Target4;
	float4 glowRes		: SV_Target5;
};



BILLBOARD_VS_OUT BILLBOARD_VS(BILLBOARD_VS_IN input )
{
	BILLBOARD_VS_OUT output;
	output.worldPos		= float4(input.worldPos,1.0f);
	output.direction	= input.direction;
	output.color		= input.color;
	output.width		= input.width;
	output.height		= input.height;

	return output;
}



[maxvertexcount(4)]

void BILLBOARD_GS(point BILLBOARD_VS_OUT input[1],
	inout TriangleStream< BILLBOARD_GS_OUT > output)
{
	float3 vecToCam = (input[0].worldPos - camPos.xyz);
	vecToCam.x = 0.0f;
	vecToCam = normalize(vecToCam);
	float3 upVec = normalize(input[0].direction);
	//upVec.y = 0;
	upVec = normalize(upVec);
		
	float3 rightVec = normalize(cross(-vecToCam, upVec));

	//Get vertices for the quad
	float3 vert[4];
	vert[0] = input[0].worldPos - rightVec * input[0].width - upVec * input[0].height;
	vert[1] = input[0].worldPos - rightVec * input[0].width + upVec * input[0].height;
	vert[2] = input[0].worldPos + rightVec * input[0].width - upVec * input[0].height;
	vert[3] = input[0].worldPos + rightVec * input[0].width + upVec * input[0].height;

	//Get texture coordinates
	float2 texCoord[4];
	texCoord[3] = float2(0.0f, 1.0f);
	texCoord[2] = float2(0.0f, 0.0f);
	texCoord[1] = float2(1.0f, 1.0f);
	texCoord[0] = float2(1.0f, 0.0f);

	BILLBOARD_GS_OUT outputVert = (BILLBOARD_GS_OUT)0;
	[unroll]
	for (int i = 0; i < 4; i++)
	{
		outputVert.Pos		 = mul(mul(float4(vert[i], 1.0f), view), projection);
		outputVert.color	 = input[0].color;
		outputVert.Uv		 = texCoord[i];
		outputVert.Normal	 = -vecToCam;
		outputVert.BiTangent = float3(1.0f, 1.0f, 1.0f);
		outputVert.Tangent   = float3(1.0f, 1.0f, 1.0f);
		
		outputVert.wPos		= float4(vert[i], 1.0f);
		outputVert.camPos	= camPos;
		outputVert.mousePos = mousePos;


		output.Append(outputVert);
	}

}

float3 normalToWorldSpace(float3 normalMapSample, float3 normal, float3 tangent, float3 biTangent) //Function for normal mapping  
{

	// here we build the tbn basis. to transform the sampled normal to texture space
	//then we return the normal and use it with our calculations

	//Convert from [0,1] to [-1,1]
	float3 normalT = 2.0f * normalMapSample - 1.0f;

	//Build basis
	float3 N = normal;

	//Make sure tangent is completely orthogonal to normal
	float3 T = normalize(tangent - dot(tangent, N)* N); //Read page 582
	float3 B = biTangent;						//cross(N, T); //Bitangent

												//Create the "Texture Space" matrix
	float3x3 TBN = float3x3(T, B, N);

	//Convert normal from normal map to texture space and store in input.normal

	float3 bumpedNormal = mul(normalT, TBN);

	return normalize(bumpedNormal);

}


BILLBOARD_PS_OUT BILLBOARD_PS(BILLBOARD_GS_OUT input)
{

	BILLBOARD_PS_OUT output;


	float4 pixelPos    = { input.wPos.x, 0.0 , input.wPos.z, 1.0 };
	float4 col		   = { 1.0,0.0,0.0,1.0 };
	float laserFalloff = 0.4f;
	//float dist = distance(input.mousePos.xz, pixelPos.xz);






	float3 start			= camPos.xyz - float3(0.0f, 14.7f, -15.0f);
	float3 stop				= input.mousePos.xyz;
	stop.y = 0.0f;

	float3 position			= (start + stop) * 0.5f;

	float lajnLength		= length(start - stop);

	float3 toPixel			= input.wPos.xyz - position;
	float3 lajn				= normalize(stop - position);
	float3 projection		= dot(toPixel, lajn) * lajn;
	float3 toLajn			= toPixel - projection;

	float projectionLength = clamp(length(projection), 0.0f, lajnLength * 0.5f);
	float3 projectionLine = normalize(projection) * projectionLength;

	float dist = min(distance(input.mousePos.xyz, pixelPos.xyz), length(toPixel - projectionLine) * 6.0f);

	col.x -= saturate(abs(dist* laserFalloff));  //Laser color

	float4 ambientValue = float4(1, 1, 1, 1);

	float4 textureSample;

	if (diffuseMap)
	{
		textureSample = diffuseTex.Sample(linearSampler, input.Uv);
		if (textureSample.a < 0.3)
			clip(-1);
		textureSample.a = col.x; //laser pointer color
		output.diffuseRes = textureSample;
	}
	else
	{

		output.diffuseRes = float4(input.color, col.x); //Alpha == laserpointer color
	}


	if (normalMap)
	{

		float4 norMap;


		norMap = normalTex.Sample(linearSampler, input.Uv);
		norMap.xyz = normalToWorldSpace(norMap.xyz, input.Normal, input.Tangent, input.BiTangent);
		output.normalRes = norMap;
	}
	else
	{

		output.normalRes = float4(input.Normal, 1);
	}

	float4 specularSample;
	if (specularMap)
	{
		specularSample.rgba = float4(0, 0, 0, 0);
		specularSample = diffuseTex.Sample(linearSampler, input.Uv);
		output.specularRes = specularSample;
	}
	else
	{
		specularSample.rgba = float4(0.5, 0.5, 0.5, 0);
		output.specularRes = specularSample;
	}

	float4 glowSample;
	if (glowMap)
	{
		glowSample = glowTex.Sample(linearSampler, input.Uv);
		output.glowRes = glowSample;
	}
	else
	{
		//textureSample = diffuseTex.Sample(linearSampler, input.Uv);
		if (diffuseMap)
			output.glowRes = textureSample;
		else
		{
			glowSample = float4 (input.color, 0);
			output.glowRes = glowSample;
		}
		
	}


	output.positionRes = input.wPos;

	float depth = input.Pos.z / input.Pos.w;
	output.depthRes = float4(depth, depth, depth, 1.0);

	return output;
}