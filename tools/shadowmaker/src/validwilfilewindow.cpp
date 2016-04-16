// generated by Fast Light User Interface Designer (fluid) version 1.0303

#include "validwilfilewindow.hpp"
#include <string>
#include <algorithm>
#include <FL/fl_ask.H>
#include "misc.hpp"

void ValidWilFileWindow::cb_m_Window_i(Fl_Double_Window*, void*) {
  {
	// disable the close button
};
}
void ValidWilFileWindow::cb_m_Window(Fl_Double_Window* o, void* v) {
  ((ValidWilFileWindow*)(o->user_data()))->cb_m_Window_i(o,v);
}

void ValidWilFileWindow::cb_m_ValidWilFileBrowser_i(Fl_Browser*, void*) {
  {
    if(!Fl::event_clicks()){
        return;
    }
    for(int i = 1; i <= m_ValidWilFileBrowser->size(); ++i){
        if(m_ValidWilFileBrowser->selected(i)){
            std::string szText = m_ValidWilFileBrowser->text(i);
            std::size_t nFind1; // "Mon-"
            std::size_t nFind2; // ".wil"

            std::replace(szText.begin(), szText.end(), '\\', '/');
            nFind1 = szText.rfind("/");
            nFind2 = szText.rfind(".wil");
            // nFind1 = szText.rfind("Mon-");
            // nFind2 = szText.rfind(".wil");

            std::string szPathName  = szText.substr(0, nFind1);
            std::string szFileName0 = szText.substr(nFind1 + 1, nFind2 - nFind1 - 1);
            // std::string szPathName  = szText.substr(0, nFind1 - 1);
            // std::string szFileName0 = szText.substr(nFind1, nFind2 - nFind1);

            // std::string szFileName1 = szFileName0;
            // szFileName1.replace(szFileName1.find("Mon-"), 4, "MonS-");

            extern WilImagePackage g_WilImagePackage[2];


            if(false 
                    || !g_WilImagePackage[0].Load(szPathName.c_str(), szFileName0.c_str(), "wil")
                    // || !g_WilImagePackage[1].Load(szPathName.c_str(), szFileName1.c_str(), "wil")
                    ||  g_WilImagePackage[0].ImageCount() != g_WilImagePackage[0].IndexCount()
                    // ||  g_WilImagePackage[1].ImageCount() != g_WilImagePackage[1].IndexCount()
                    // ||  g_WilImagePackage[0].ImageCount() != g_WilImagePackage[1].ImageCount()
              ){
                fl_alert("Invalid .WIL file set: %s", szFileName0.c_str());
            }else{
                int32_t nCount = g_WilImagePackage[0].IndexCount();
                int32_t nMaxValidIndex = nCount;
                for(int nIndex = 0; nIndex < nCount; ++nIndex){
                    extern ProgressBarWindow *g_ProgressBarWindow;
                    g_ProgressBarWindow->SetValue(nIndex * 100 / nCount);
                    g_ProgressBarWindow->Redraw();
                    g_ProgressBarWindow->ShowAll();
                    Fl::check();

                    if(true
                            && g_WilImagePackage[0].SetIndex(nIndex)
                            && g_WilImagePackage[0].CurrentImageValid()
                            // && g_WilImagePackage[1].SetIndex(nIndex)
                            // && g_WilImagePackage[1].CurrentImageValid()
                      ){
                        nMaxValidIndex = nIndex;
                    }
                }

                // printf("%d\n", nMaxValidIndex);
                extern ProgressBarWindow *g_ProgressBarWindow;
                g_ProgressBarWindow->HideAll();

                extern ValidAnimationWindow *g_ValidAnimationWindow;
                g_ValidAnimationWindow->SetFileIndex(i);
                g_ValidAnimationWindow->CheckValidAnimation(nMaxValidIndex);
                g_ValidAnimationWindow->ShowAll();
                m_Window->hide();
                return;
            }
        }
    }
};
}
void ValidWilFileWindow::cb_m_ValidWilFileBrowser(Fl_Browser* o, void* v) {
  ((ValidWilFileWindow*)(o->parent()->user_data()))->cb_m_ValidWilFileBrowser_i(o,v);
}

ValidWilFileWindow::ValidWilFileWindow() {
  { m_Window = new Fl_Double_Window(510, 400);
    m_Window->labelfont(4);
    m_Window->callback((Fl_Callback*)cb_m_Window, (void*)(this));
    { m_ValidWilFileBrowser = new Fl_Browser(0, 0, 510, 400);
      m_ValidWilFileBrowser->type(2);
      m_ValidWilFileBrowser->labelfont(4);
      m_ValidWilFileBrowser->textfont(4);
      m_ValidWilFileBrowser->callback((Fl_Callback*)cb_m_ValidWilFileBrowser);
      Fl_Group::current()->resizable(m_ValidWilFileBrowser);
    } // Fl_Browser* m_ValidWilFileBrowser
    m_Window->end();
  } // Fl_Double_Window* m_Window
}

void ValidWilFileWindow::ShowAll() {
  {
  	m_Window->show();
  }
}

void ValidWilFileWindow::CheckValidWilFile(const char *szWilFolderName) {
  {
      extern const char *g_MonsterWilFileNameList[];
      const char **szMonsterWilFileNameList = g_MonsterWilFileNameList;
      
      m_ValidWilFileBrowser->clear();
      
      std::string szWilFileName;
      for(int nCnt = 0; std::strlen(szMonsterWilFileNameList[nCnt]) > 0; ++nCnt){
          szWilFileName = szWilFolderName;
          if(szWilFileName.back() != '/'){
              szWilFileName += "/";
          }
          szWilFileName += szMonsterWilFileNameList[nCnt];
          if(FileExist((szWilFileName + ".wil").c_str()) && FileExist((szWilFileName + ".wix").c_str())){
              /*
              auto szWilFileName2 = szWilFileName;
              std::string szKey("Mon-");
              std::size_t nFound = szWilFileName.rfind(szKey);
              if (nFound != std::string::npos){
                  szWilFileName.replace(nFound, szKey.length(), "MonS-");
              }else{
                  continue;
              }
              if(FileExist((szWilFileName + ".wil").c_str()) && FileExist((szWilFileName + ".wix").c_str())){
                  m_ValidWilFileBrowser->add((szWilFileName2 + ".wil").c_str());
              }
              */
               m_ValidWilFileBrowser->add((szWilFileName + ".wil").c_str());
          }
      }
  }
}
