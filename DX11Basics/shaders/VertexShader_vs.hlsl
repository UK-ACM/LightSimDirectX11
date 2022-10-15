struct VSOut {
	float4 clr : COLOR;
	float4 pos : SV_POSITION;
};

cbuffer CBuf {
	matrix transform;

};

VSOut main( float2 pos : POSITION, float4 clr : COLOR)
{
	VSOut vso;
	vso.pos = mul(transform, float4(pos.x, pos.y, 0.0f, 1.0f));
	vso.clr = clr;
	return vso;
}