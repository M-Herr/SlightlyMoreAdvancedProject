#include "UI/MainWindow.hpp"
#include "Core/Logging.hpp"


namespace UI {

    static void glfw_error_callback(int error, const char* description)
    {
       ConsoleLogger::getInstance()->error("GLFW Error: {}, {}", error, description);
    }

    MainWindow::MainWindow(WindowProperties in_properties)
    : properties(in_properties), running(true)
    {

    }

    MainWindow::~MainWindow()
    {   

    }

    void MainWindow::InitializeGLFW()
    {   
        glfwSetErrorCallback(glfw_error_callback);

        if(!glfwInit())
        {   
            ConsoleLogger::getInstance()->error("GLFW failed to initialize!");
            return;
                    }
        window = glfwCreateWindow(properties.width, properties.height, properties.name.c_str(), nullptr, nullptr);
    }

    void MainWindow::SetupImgui()
    {   
        //Figure out GL + GLSL version
    #if defined(IMGUI_IMPL_OPENGL_ES2)
        // GL ES 2.0 + GLSL 100
        const char* glsl_version = "#version 100";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    #elif defined(__APPLE__)
        // GL 3.2 + GLSL 150
        const char* glsl_version = "#version 150";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
    #else
        // GL 3.0 + GLSL 130
        const char* glsl_version = "#version 130";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
    #endif

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1); // Enable vsync


        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        
        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

    }

    void MainWindow::BeginFrame()
    {   
        glfwPollEvents();

        //Imgui Frame stuff
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        
    }

    void MainWindow::EndFrame()
    {
        
        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(properties.clear_color.x * properties.clear_color.w, 
            properties.clear_color.y * properties.clear_color.w, 
            properties.clear_color.z * properties.clear_color.w, 
            properties.clear_color.w);

        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        if(glfwWindowShouldClose(window)) 
        {
            running = false;
        }
    }


    void MainWindow::CleanUp()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(window);
        glfwTerminate();

    }

    
}