#include "MainView.h"
#include <implot.h>

void MainView::Update(void)
{

    // 1. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Imgui Demo Window", &show_imgui_demo_window);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Implot Demo Window", &show_implot_demo_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }

    // 2. Show imgui demo window.
    if (show_imgui_demo_window)
    {
        ImGui::ShowDemoWindow();
    }
    // 3. Show implot demo window.
    if (show_implot_demo_window)
    {
        ImPlot::ShowDemoWindow();
    }
}
