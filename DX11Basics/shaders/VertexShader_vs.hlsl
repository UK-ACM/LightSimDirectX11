//struct VSOut {
//	uint tid : SV_PrimitiveID;
//	float4 pos : SV_POSITION;
//};

cbuffer CBuf {
	matrix transform;

};

float4 main(float3 pos : POSITION) : SV_POSITION
{
	return mul(transform, float4(pos, 1.0f));
}