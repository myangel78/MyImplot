// Demo:   demo.cpp
// Author: Evan Pezent (evanpezent.com)
// Date:   3/26/2021

#include "App.h"

struct ImPlotDemo : App {
    using App::App;
    void Update() override {
        ImPlot::ShowDemoWindow();   
    }
};

int main(int argc, char const *argv[])
{
#ifdef IMPLOT_DEBUG
    fprintf(stdout, "**** defined IMPLOT_DEBUG ****\n");
#endif
#ifdef IMPLOT_DLL_EXPORT
    fprintf(stdout, "**** defined IMPLOT_DLL_EXPORT ****\n");
#endif

    

    ImPlotDemo app("ImPlot Demo",1920,1080,argc,argv);
    app.Run();

    return 0;
}
