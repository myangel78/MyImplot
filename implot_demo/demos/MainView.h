#pragma once
#include <imgui.h>

class MainView
{
public:
	void Update(void);

private:
	bool show_imgui_demo_window = false;
	bool show_implot_demo_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

};

