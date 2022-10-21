#include "PointLight.h"
#include "imgui.h"

PointLight::PointLight(Graphics& gfx, float radius)
	:
	mesh(gfx, radius),
	cbuf(gfx)
{
	Reset();
}

void PointLight::SpawnControlWindow()
{
	if (ImGui::Begin("Light"))
	{
		ImGui::Text("Position");
		ImGui::SliderFloat("X", &cbData.pos.x, -60.0f, 60.0f, "%.1f");
		ImGui::SliderFloat("Y", &cbData.pos.y, -60.0f, 60.0f, "%.1f");
		ImGui::SliderFloat("Z", &cbData.pos.z, -60.0f, 60.0f, "%.1f");
		ImGui::Text("Intensity/Color");
		ImGui::SliderFloat("Intensity", &cbData.diffuseIntensity, -1.0f, 50.0f, "%.1f");
		ImGui::ColorEdit3("Diffuse Color", &cbData.diffuseColor.x);
		ImGui::ColorEdit3("Ambient", &cbData.ambient.x);

		ImGui::Text("Attenuation");
		ImGui::SliderFloat("Constant", &cbData.attConst, 1.0f, 10.0f, "%.1f");
		ImGui::SliderFloat("Linear", &cbData.attLin, 0.0f, 0.1f, "%.3f");
		ImGui::SliderFloat("Quadratic", &cbData.attQuad, 0.0f, 0.01f, "%.4f");

		if (ImGui::Button("Reset"))
		{
			Reset();
		}
	}
	ImGui::End();
}

void PointLight::Reset()
{
	cbData = {
		{0.0f, 0.0f, 0.0f},
		{0.05f, 0.05f, 0.05f},
		{1.0f, 1.0f, 1.0f},
		1.0f,
		1.0f,
		0.045f,
		0.0075f,
	};
}

void PointLight::Draw(Graphics& gfx) const 
{
	mesh.SetPos(cbData.pos);
	mesh.Draw(gfx);
}

void PointLight::Bind(Graphics& gfx, DirectX::FXMMATRIX view) const 
{
	auto dataCopy = cbData;
	const auto pos = DirectX::XMLoadFloat3(&cbData.pos);
	DirectX::XMStoreFloat3(&dataCopy.pos, DirectX::XMVector3Transform(pos, view));
	cbuf.Update(gfx, dataCopy);
	cbuf.Bind(gfx);
}
