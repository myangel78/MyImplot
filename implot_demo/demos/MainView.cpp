#include "MainView.h"
#include <implot.h>
#include <math.h>
#include <vector>
#include <random>
#include <string>
#include <iostream>


std::vector<float> GetGaussianNoiseData(const float& mean, const float& stdeviation, const int& sampleNum)
{
    std::vector<float> vecData;

#if 0
    std::default_random_engine generator;
#else
    std::random_device rd;
    std::mt19937 generator(rd());
#endif
    std::normal_distribution<double> distribution(mean, stdeviation);

    for (int i = 0; i < sampleNum; ++i) {
        double number = distribution(generator);
        vecData.emplace_back(number);
    }
    return vecData;
}

// utility structure for realtime plot
struct ScrollingBuffer {
    int MaxSize;
    int Offset;
    ImVector<ImVec2> Data;
    ScrollingBuffer(int max_size = 2000) {
        MaxSize = max_size;
        Offset = 0;
        Data.reserve(MaxSize);
    }
    void AddPoint(float x, float y) {
        if (Data.size() < MaxSize)
            Data.push_back(ImVec2(x, y));
        else {
            Data[Offset] = ImVec2(x, y);
            Offset = (Offset + 1) % MaxSize;
        }
    }
    void Erase() {
        if (Data.size() > 0) {
            Data.shrink(0);
            Offset = 0;
        }
    }
};

// utility structure for realtime plot
struct RollingBuffer {
    float Span;
    ImVector<ImVec2> Data;
    RollingBuffer() {
        Span = 10.0f;
        Data.reserve(2000);
    }
    void AddPoint(float x, float y) {
        float xmod = fmodf(x, Span);
        if (!Data.empty() && xmod < Data.back().x)
            Data.shrink(0);
        Data.push_back(ImVec2(xmod, y));
    }
};

void Demo_RealtimePlots() {
    ImGui::BulletText("Move your mouse to change the data!");
    ImGui::BulletText("This example assumes 60 FPS. Higher FPS requires larger buffer size.");
    static ScrollingBuffer sdata1, sdata2;
    static RollingBuffer   rdata1, rdata2;
    ImVec2 mouse = ImGui::GetMousePos();
    static float t = 0;
    t += ImGui::GetIO().DeltaTime;
    sdata1.AddPoint(t, mouse.x * 0.0005f);
    rdata1.AddPoint(t, mouse.x * 0.0005f);
    sdata2.AddPoint(t, mouse.y * 0.0005f);
    rdata2.AddPoint(t, mouse.y * 0.0005f);

    static float history = 10.0f;
    ImGui::SliderFloat("History", &history, 1, 30, "%.1f s");
    rdata1.Span = history;
    rdata2.Span = history;

    static ImPlotAxisFlags flags = ImPlotAxisFlags_NoTickLabels;

    if (ImPlot::BeginPlot("##Scrolling", ImVec2(-1, 150))) {
        ImPlot::SetupAxes(nullptr, nullptr, flags, flags);
        ImPlot::SetupAxisLimits(ImAxis_X1, t - history, t, ImGuiCond_Always);
        ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 1);
        ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL, 0.5f);
        ImPlot::PlotShaded("Mouse X", &sdata1.Data[0].x, &sdata1.Data[0].y, sdata1.Data.size(), -INFINITY, 0, sdata1.Offset, 2 * sizeof(float));
        ImPlot::PlotLine("Mouse Y", &sdata2.Data[0].x, &sdata2.Data[0].y, sdata2.Data.size(), 0, sdata2.Offset, 2 * sizeof(float));
        ImPlot::EndPlot();
    }
    if (ImPlot::BeginPlot("##Rolling", ImVec2(-1, 150))) {
        ImPlot::SetupAxes(nullptr, nullptr, flags, flags);
        ImPlot::SetupAxisLimits(ImAxis_X1, 0, history, ImGuiCond_Always);
        ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 1);
        ImPlot::PlotLine("Mouse X", &rdata1.Data[0].x, &rdata1.Data[0].y, rdata1.Data.size(), 0, 0, 2 * sizeof(float));
        ImPlot::PlotLine("Mouse Y", &rdata2.Data[0].x, &rdata2.Data[0].y, rdata2.Data.size(), 0, 0, 2 * sizeof(float));
        ImPlot::EndPlot();
    }
}


void MainView::Demo_LinePlots(const int &index) {

    const int totalsize = 20000;
    static float ys1[totalsize];

    static double xs2[20], ys2[20];
    for (int i = 0; i < 20; ++i) {
        xs2[i] = i * 1 / 19.0f;
        ys2[i] = xs2[i] * xs2[i];
    }
    std::string name = "Line Plots" + std::to_string(index);

    if (ImPlot::BeginPlot(name.c_str(), ImVec2(300,300))) {
        //ImPlot::SetupAxes("x", "y");
        //ImPlot::PlotLine("f(x)", xs1, ys1, totalsize);
        ImPlot::PlotLine("f(x)", &xs1[0], &data[0], totalsize/4,0,0,4*sizeof(float));
        //ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle);
        ImPlot::PlotLine("g(x)", xs2, ys2, 20, ImPlotLineFlags_Segments);
        ImPlot::EndPlot();
    }
}

void MainView::ShowDemoPlotLine(void)
{
    std::string name = "LinePlot";
    ImGui::Begin(name.c_str());
    data = GetGaussianNoiseData(10, 10.5, totalsize);
    for (int i = 0; i < 256; i++)
    {
        Demo_LinePlots(i);
        if ((i + 1) % 5 != 0)
        {
            ImGui::SameLine();
        }
    }
    ImGui::End();


    //Demo_RealtimePlots();

   /* if (ImPlot::BeginPlot("Scatter Plot")) {
        float x_data[] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };
        float y_data[] = { 10.0f, 15.0f, 8.0f, 12.0f, 20.0f };
        ImPlot::PlotScatter("Scatter Data", x_data, y_data, 5);
        ImPlot::EndPlot();
    }
    if (ImPlot::BeginPlot("Line Plot")) {
        float x_data[] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };
        float y_data[] = { 10.0f, 15.0f, 8.0f, 12.0f, 20.0f };
        ImPlot::PlotLine("Line Data", x_data, y_data, 5, ImPlotLineFlags_None,0, 1 * sizeof(float));
        ImPlot::EndPlot();
    }*/
}

MainView::MainView()
{
    Init();
}

void MainView::Update(void)
{
    static bool opt_fullscreen = true;
    if (opt_fullscreen)
    {
       /* const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);*/
    }

    static bool show_demo_line_plots = true;

    // 1. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Imgui Demo Window", &show_imgui_demo_window);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Implot Demo Window", &show_implot_demo_window);
        ImGui::Checkbox("Demo Plot line Window", &show_demo_line_plots);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
        *m_pClear_color = clear_color;

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

 
    if (show_demo_line_plots)
    {

        ShowDemoPlotLine();

    }
}

void MainView::Init(void)
{
    xs1.resize(totalsize);
    for (int i = 0; i < totalsize; ++i) {
        xs1[i] = i * 0.001f;
        //ys1[i] = 0.5f + 0.5f * sinf(50 * (xs1[i] + (float)ImGui::GetTime() / 10));
    }

    data = GetGaussianNoiseData(10, 10.5, totalsize);
}
