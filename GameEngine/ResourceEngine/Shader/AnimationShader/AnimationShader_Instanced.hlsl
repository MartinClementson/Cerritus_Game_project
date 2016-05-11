
struct BlendShapeVert
{
	float3 position;
	float  Padp;
	
	float3 normal;
	float padN;

	float2 biTangent;
	float2 tangent;
	float influence;
	float3 padI;
};

StructuredBuffer<BlendShapeVert>		animationOne	: register(t10);
StructuredBuffer<BlendShapeVert>		shapeTwo		: register(t11);


//ANIM
Texture2D diffuseTex			 : register(t0);
Texture2D normalTex				 : register(t1);
Texture2D specularTex			 : register(t2);
Texture2D glowTex				 : register(t3);
Texture2DArray shadowTex		 : register(t6);

SamplerState linearSampler		 : register(s0);
SamplerState pointSampler		 : register(s1);

cbuffer cbufferPerFrame			 : register(b0)
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



struct ANIM_VS_IN
{
	float3	 Pos			 : POSITION;
	float3	 Normal			 : TEXCOORD0;
	float2	 Uv				 : TEXCOORD1;
	float2	 BiTangent		 : TEXCOORD2;
	float2	 Tangent		 : TEXCOORD3;
	float4x4 WorldMatrix	 : WORLD;		   //Instanced
	uint	 Animation		 : ANIMATION;	   //Instanced
	float	 AnimationTime   : ANIMTIME;	   //Instanced
	uint	 VertexID		 : SV_VertexID;    

};
struct ANIM_VS_OUT
{
	float4 Pos			 : SV_POSITION;
	float3 Normal		 : TEXCOORD0;
	float2 Uv			 : TEXCOORD1;
	float3 BiTangent	 : TEXCOORD2;
	float3 Tangent		 : TEXCOORD3;
	float4 wPos			 : WORLDPOS;
	
};
struct ANIM_GS_OUT
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
struct ANIM_PS_OUT
{
	float4 diffuseRes	: SV_Target0;
	float4 specularRes	: SV_Target1;
	float4 normalRes	: SV_Target2;
	float4 overlayRes	: SV_Target3;
	float4 positionRes	: SV_Target4;
	float4 glowRes		: SV_Target5;
};

static const float AniTimeSec= 10.0f;
//Vertex shader
ANIM_VS_OUT ANIM_VS_main(ANIM_VS_IN input)
{

	ANIM_VS_OUT output;


	//shape x  vert i = VertexID + vertexAmount(constant)* frame
	// need some max frame count

	float3 animPos = input.Pos.xyz; //Just to avoid warnings
	//ANIMATE
	if (input.AnimationTime < 0.5f)
	{
		float normalizedTime = input.AnimationTime / 0.5f;
		 animPos		=  lerp(input.Pos.xyz, animationOne[input.VertexID ].position, normalizedTime);
	}
	else if (input.AnimationTime >= 0.5)
	{ //normalize the time between the current frames
		float normalizedTime = (input.AnimationTime - 0.5) / (1.0 - 0.5); // Time - B / (C - B);
		animPos		 = lerp(animationOne[input.VertexID].position, animationOne[input.VertexID + 8 * 1].position, normalizedTime);
	}
	

	output.Pos			= float4(animPos, 1.0f);


	output.Pos			= mul(output.Pos, input.WorldMatrix);
	output.wPos			= output.Pos;
	output.Pos			= mul(output.Pos, view);
	output.Pos			= mul(output.Pos, projection);

	output.BiTangent.xy = input.BiTangent.xy;
	output.Tangent.xy	= input.Tangent.xy;

	output.BiTangent.z  = sqrt(1 - pow(input.BiTangent.x, 2) + pow(input.BiTangent.y, 2));
	output.Tangent.z	= sqrt(1 - pow(input.Tangent.x, 2) + pow(input.Tangent.y, 2));







	output.Normal		 = normalize(mul(float4(input.Normal, 0.0f), input.WorldMatrix).xyz).xyz;
	output.BiTangent	 = normalize(mul(float4(output.BiTangent, 0.0f), input.WorldMatrix).xyz).xyz;
	output.Tangent		 = normalize(mul(float4(output.Tangent, 0.0f), input.WorldMatrix).xyz).xyz;
	output.Uv			 = input.Uv;

	return output;
}


[maxvertexcount(3)]
//Geometry shader!
void ANIM_GS_main(
	triangle ANIM_VS_OUT input[3],
	inout TriangleStream< ANIM_GS_OUT > output)
{


	for (uint i = 0; i < 3; i++)
	{


		ANIM_GS_OUT element;
		//element.Pos			 = mul(input[i].Pos, view);
		//element.Pos			 = mul(input[i].Pos, projection);
		element.Pos			 = input[i].Pos;
		element.Normal		 = input[i].Normal;
		element.BiTangent	 = input[i].BiTangent;
		element.Tangent		 = input[i].Tangent;
		element.Uv			 = input[i].Uv;
		element.wPos		 = input[i].wPos;
		element.camPos		 = camPos;
		element.mousePos	 = mousePos;

		output.Append(element);
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


//pixel shader
ANIM_PS_OUT ANIM_PS_main(ANIM_GS_OUT input)
{
	ANIM_PS_OUT output = (ANIM_PS_OUT)0;


	float4 pixelPos = { input.wPos.x, 0.0 , input.wPos.z, 1.0 };
	float4 col = { 1.0,0.0,0.0,1.0 };
	//float dist = distance(input.mousePos.xz, pixelPos.xz);
	float laserFalloff = 0.4f;






	float3 start = camPos.xyz - float3(0.0f, 9.7f, -14.0f);
	float3 stop = input.mousePos.xyz;
	stop.y = 0.0f;

	float3 position = (start + stop) * 0.5f;

	float lajnLength = length(start - stop);

	float3 toPixel = input.wPos.xyz - position;
	float3 lajn = normalize(stop - position);
	float3 projection = dot(toPixel, lajn) * lajn;
	float3 toLajn = toPixel - projection;

	float projectionLength = clamp(length(projection), 0.0f, lajnLength * 0.5f);
	float3 projectionLine = normalize(projection) * projectionLength;

	float dist = min(distance(input.mousePos.xyz, pixelPos.xyz), length(toPixel - projectionLine) * 6.0f);

	col.x -= saturate(abs(dist* laserFalloff));  //Laser color

	float4 ambientValue = float4(1, 1, 1, 1);

	float4 textureSample;

	if (diffuseMap)
	{
		textureSample = diffuseTex.Sample(linearSampler, input.Uv);
		if (textureSample.a < 0.1)
			clip(-1);
		output.diffuseRes = textureSample;
	}
	else
	{

		output.diffuseRes = float4(0.5, 0.5, 0.5, 1.0f); //Alpha == laserpointer color
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
		specularSample = specularTex.Sample(linearSampler, input.Uv);
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
		glowSample = float4 (0, 0, 0, 0);
		output.glowRes = glowSample;
	}


	output.positionRes = input.wPos; //position buffer

	float depth = input.Pos.z / input.Pos.w;
	output.normalRes.a = depth;
	output.overlayRes.r = 1.0f;
	output.overlayRes.a = col.x; //Alpha == laserpointer color
								 //output.depthRes = float4(depth, depth, depth, 1.0);

	return output;
}

//ANIM shadowmap shader
struct ANIM_SHADOWDEPTH_VS_OUT
{
	float4 position		: SV_POSITION;
};
ANIM_SHADOWDEPTH_VS_OUT ANIM_SHADOWDEPTH_VS_main(ANIM_VS_IN input)
{
	ANIM_SHADOWDEPTH_VS_OUT output = (ANIM_SHADOWDEPTH_VS_OUT)0;
	//matrix combinedMatrix = mul(world, mul(lightView, lightProjection));

	output.position = float4(input.Pos, 1);

	//output.position = mul(output.position, combinedMatrix);

	return output;
}






