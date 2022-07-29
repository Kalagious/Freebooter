#include "screenmanager.h"
#include "cheats.h"

extern Cheats* cheatsGlobal;

ImVec4 HSVtoRGB(float H, float S, float V, float A);

void ScreenManager::drawGUI()
{
    static float fFade = 0;
    float fFadeRate = 0.007;

    if (bShowGUI)
    {
        static float iChroma = 0;
        if (fFade < 0.6)
            fFade += fFadeRate;

        float background[4] = { 0.0f, 0.0f, 0.0f, fFade };
        SetupOrtho();
        DrawFilledRect(0, 0, 3000, 3000, background);

        if (iChroma >= 360)
            iChroma = 0;
        else
            iChroma += 0.1;
        if (!imGUIInitialized)
            return;
 
        ImGui::GetStyle().Colors[ImGuiCol_Border] = HSVtoRGB(iChroma, 100, 100, 1);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::ShowDemoWindow();
        ImGui::NewFrame();
        ImGui::Begin("Player");
        ImGui::SetWindowSize(ImVec2((float)250, (float)400));
        ImGui::End();
        ImGui::Begin("Ship");
        ImGui::SetWindowSize(ImVec2((float)250, (float)400));
        ImGui::End();
        ImGui::Begin("Weapon");
        ImGui::SetWindowSize(ImVec2((float)250, (float)400));
        ImGui::End();
        ImGui::Begin("Visual");
        ImGui::SetWindowSize(ImVec2((float)250, (float)400));
        ImGui::End();
        ImGui::Render();


        // Draw the overlay
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
    else
    {
        if (fFade > 0)
            fFade -= fFadeRate;
    }
}



ImVec4 HSVtoRGB(float H, float S, float V, float A) 
{

    float s = S / 100;
    float v = V / 100;
    float C = s * v;
    float X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
    float m = v - C;
    float r, g, b;
    if (H >= 0 && H < 60) {
        r = C, g = X, b = 0;
    }
    else if (H >= 60 && H < 120) {
        r = X, g = C, b = 0;
    }
    else if (H >= 120 && H < 180) {
        r = 0, g = C, b = X;
    }
    else if (H >= 180 && H < 240) {
        r = 0, g = X, b = C;
    }
    else if (H >= 240 && H < 300) {
        r = X, g = 0, b = C;
    }
    else {
        r = C, g = 0, b = X;
    }

    return ImVec4((r + m) * 1.0, (g + m) * 1.0, (b + m) * 1.0, A);

}

void ScreenManager::SetupOrtho()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushMatrix();
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glViewport(0, 0, viewport[2], viewport[3]);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, viewport[2], viewport[3], 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
}

void ScreenManager::RestoreGL()
{
    glPopMatrix();
    glPopAttrib();
}

void ScreenManager::DrawFilledRect(float x, float y, float width, float height, const float color[4])
{
    glDisable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // the default anyway
    glEnable(GL_BLEND);
    glEnable(GL_COLOR_MATERIAL);
    glColor4f(color[0], color[1], color[2], color[3]);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
    glEnable(GL_TEXTURE_2D);
}

void ScreenManager::DrawOutline(float x, float y, float width, float height, float lineWidth, const GLubyte color[3])
{
    glDisable(GL_TEXTURE_2D);
    glLineWidth(lineWidth);
    glBegin(GL_LINE_STRIP);
    glColor3ub(color[0], color[1], color[2]);
    glVertex2f(x - 0.5f, y - 0.5f);
    glVertex2f(x + width + 0.5f, y - 0.5f);
    glVertex2f(x + width + 0.5f, y + height + 0.5f);
    glVertex2f(x - 0.5f, y + height + 0.5f);
    glVertex2f(x - 0.5f, y - 0.5f);
    glEnd();
    glEnable(GL_TEXTURE_2D);
}