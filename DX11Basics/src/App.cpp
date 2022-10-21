#include "App.h"
#include "SolidSphere.h"
#include "Box.h"
#include "Pyramid.h"
#include "Surface.h"
#include "WhalenMath.h"
#include "GDIPlusManager.h"
#include "imgui.h"
#include <memory>
#include <algorithm>
#include <sstream>

GDIPlusManager gdipm;

App::App(int width, int height)
	: wnd(width, height, "The fattest window ever"), // create the window
	light(wnd.Gfx())
{
	class Factory
	{
	public:
		Factory(Graphics& gfx)
			:
			gfx(gfx)
		{}
		std::unique_ptr<Drawable> operator()()
		{
			const DirectX::XMFLOAT3 mat = { cdist(rng), cdist(rng), cdist(rng) };
			return std::make_unique<Box>(
				gfx, rng, adist, ddist,
				odist, rdist, bdist, mat
				);
		}
	private:
		Graphics& gfx;
		std::mt19937 rng{ std::random_device{}() };
		std::uniform_real_distribution<float> adist{ 0.0f,PI * 2.0f };
		std::uniform_real_distribution<float> ddist{ 0.0f,PI * 0.5f };
		std::uniform_real_distribution<float> odist{ 0.0f,PI * 0.08f };
		std::uniform_real_distribution<float> rdist{ 6.0f,20.0f };
		std::uniform_real_distribution<float> bdist{ 0.4f,3.0f };
		std::uniform_real_distribution<float> cdist{ 0.0f, 1.0f };
	};

	Factory f(wnd.Gfx());
	drawables.reserve(nDrawables);
	std::generate_n(std::back_inserter(drawables), nDrawables, f);
	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
}

App::~App()
{}

// run one loop of message processing
int App::Run() {
	while (true) {
		// process all messages pending, but to not block for new messages
		if (const auto ecode = Window::ProcessMessages())
		{
			// if return optional has value, means we're quitting so return exit code
			return *ecode;
		}
		DoFrame();
	}

}

void App::DoFrame() {
	auto dt = timer.Mark() * speed_factor; // gets delta time to update scene
	
	wnd.Gfx().BeginFrame(0.07f, 0.0f, 0.12f);
	wnd.Gfx().SetCamera(cam.GetMatrix());
	light.Bind(wnd.Gfx(), cam.GetMatrix());
	for (auto& b : drawables)
	{
		// update position and draw all drawable objects: Box, Sheet, Pyramid, SolidSphere
		b->Update(wnd.kbd.KeyIsPressed(VK_SPACE) ? 0.0f : dt);
		b->Draw(wnd.Gfx());
	}
	light.Draw(wnd.Gfx());

	if (wnd.Gfx().GetImguiEnable()) {
		if (ImGui::Begin("Simulation Speed")) {
			ImGui::SliderFloat("Speed Factor", &speed_factor, 0.0f, 4.0f);
			ImGui::Text("Application Average %.3f ms/frame (%.1f FPS)", 1000.0f/ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::Text("Status: %s", wnd.kbd.KeyIsPressed(VK_SPACE) ? "PAUSED" : "RUNNING (hold spacebar to pause)");
			if (ImGui::Button("Reset Speed", ImVec2(100, 20))) {
				speed_factor = 1.0f;
			}

		}
		ImGui::End();
			
		cam.SpawnControlWindow();
		light.SpawnControlWindow();
		
	}

	wnd.Gfx().EndFrame(); // ends frame and clears depth buffer
}