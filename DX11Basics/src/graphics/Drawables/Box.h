#pragma once
#include "TestObject.h"

class Box : public TestObject<Box>
{
public:
	Box(Graphics& gfx, std::mt19937& rng,
		std::uniform_real_distribution<float>& adist,
		std::uniform_real_distribution<float>& ddist,
		std::uniform_real_distribution<float>& odist,
		std::uniform_real_distribution<float>& rdist,
		std::uniform_real_distribution<float>& bdist,
		DirectX::XMFLOAT3 materialColor);

	DirectX::XMMATRIX GetTransformXM() const noexcept override{
		return DirectX::XMLoadFloat3x3(&mt) * TestObject::GetTransformXM();
	}
private:
	DirectX::XMFLOAT3X3 mt;
};
