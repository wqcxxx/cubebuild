#include "UIManager.h"

#include <iostream>

UIManager::UIManager() {}

UIManager::~UIManager() 
{
    if (ImGui::GetCurrentContext() != nullptr) 
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}

void UIManager::setup_imgui_context() 
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
}

void UIManager::set_dark_style()
{
    ImGui::StyleColorsDark();
}

void UIManager::setup_scaling()
{
    float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale);
    style.FontScaleDpi = main_scale;
}

void UIManager::glfw_opengl_init(const Window& window, const char* glsl_version)
{
    ImGui_ImplGlfw_InitForOpenGL(window.get_window(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void UIManager::imgui_glfw_opengl_new_frame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
}

void UIManager::render()
{
    if (ImGui::GetCurrentContext() == nullptr)
    {
        std::cout << "imgui render error!";
        return;
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UIManager::show_player_position(const glm::vec3& player_position)
{
    ImGui::Begin("position");
    ImGui::Text("position: %f.2f, %f.2f, %f.2f", 
                 player_position.x, player_position.y, player_position.z);
    ImGui::End();
}

void UIManager::new_frame()
{
    ImGui::NewFrame();
}

void UIManager::end_frame()
{
    ImGui::EndFrame();
}