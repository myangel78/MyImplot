// Demo:   demo.cpp
// Author: Evan Pezent (evanpezent.com)
// Date:   3/26/2021

#include "App.h"
#include "MainView.h"

struct ImPlotDemo : App {
    using App::App;

    MainView* m_pMainview = nullptr;
    void InitMainViewPtr(MainView* pmainview, ImVec4 *pClearColor) {
        m_pMainview = pmainview;
        m_pMainview->SetClearColorPtr(pClearColor);
    }

    void Update() override {
#if 0
        ImPlot::ShowDemoWindow();   
#else
        if (m_pMainview)
        {
            m_pMainview->Update();
        }
#endif

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

    MainView* m_pMainview = new MainView();
    app.InitMainViewPtr(m_pMainview,&app.ClearColor);

    app.Run();

    return 0;
}
