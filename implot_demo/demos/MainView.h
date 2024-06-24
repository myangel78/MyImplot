#pragma once
#include <imgui.h>
#include <vector>

class MainView
{
public:
	MainView();
	void Update(void);
	void SetClearColorPtr(ImVec4* pclearColor) { m_pClear_color = pclearColor; }


private:
	void Init(void);
	void Demo_LinePlots(const int& index);
	void ShowDemoPlotLine(void);

private:
	bool show_imgui_demo_window = false;
	bool show_implot_demo_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	ImVec4* m_pClear_color = nullptr;

	const int totalsize = 20000;
	std::vector<float> xs1;
	std::vector<float> data;

};

