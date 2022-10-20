cbuffer LightBuf {
	float3 lightPos;
};

// some constants for light calcs, will be extracted later
static const float3 materialColor = { 0.7f, 0.7f, 0.9f };
static const float3 ambient = { 0.05f, 0.05f, 0.05f };
static const float3 diffuseColor = { 1, 0.2, 0.2 };
static const float diffuseIntensity = 10.0f;
static const float attConst = 1.0f;
static const float attLin = 0.045f;
static const float attQuad = 0.0075f;



float4 main(float3 worldPos : Position, float3 n : normal) : SV_TARGET
{
	// fragment to light vector data
	const float3 vToL = lightPos - worldPos;
	const float distToL = length(vToL);
	const float3 dirToL = vToL / distToL;

	// diffuse attenuation
    const float att = 1.0f / (attConst + attLin * distToL + attQuad * (distToL * distToL));

	// diffuse calc
	const float3 diffuse = diffuseColor * diffuseIntensity * att * max(0.0f, dot(dirToL, n));
	return float4(saturate(diffuse + ambient), 1.0f);
}