#include "vulkan/vulkan_surface.h"

namespace tigine { namespace rhi {
VulkanSurface::VulkanSurface(GLFWwindow *window) : window_(window) {}

VulkanSurface::~VulkanSurface() {
    if (window_) glfwDestroyWindow(window_);
}

void VulkanSurface::setTitle(const TString &name) {
    glfwSetWindowTitle(window_, name.c_str());
}

void VulkanSurface::show() { 
    glfwShowWindow(window_);
}

bool VulkanSurface::processEvents() {
    glfwPollEvents();
    return !glfwWindowShouldClose(window_);
}
}} // namespace tigine::rhi
