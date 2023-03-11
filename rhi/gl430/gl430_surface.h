#ifndef TIGINE_RHI_GL430_GL430_SURFACE_H_
#define TIGINE_RHI_GL430_GL430_SURFACE_H_

#include "gl430/gl430_common.h"
#include "interface/i_surface.h"

namespace tigine { namespace rhi {
class GL430Surface : public ISurface {
public:
    GL430Surface(GLFWwindow *window) : window_(window) {}
    ~GL430Surface() = default;

    void setTitle(const std::string &name) override {
        glfwSetWindowTitle(window_, name.c_str());
    }
    void show() override { 
        glfwShowWindow(window_);
    }
    bool processEvents() override {
        glfwPollEvents();
        return !glfwWindowShouldClose(window_);
    }

private:
    GLFWwindow *window_;
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_GL430_GL430_SURFACE_H_
