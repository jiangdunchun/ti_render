#ifndef TIGINE_RHI_VULKAN_VULKAN_SURFACE_H_
#define TIGINE_RHI_VULKAN_VULKAN_SURFACE_H_

#include "interface/i_surface.h"

#include "vulkan/vulkan_common.h"

namespace tigine { namespace rhi {
class VulkanSurface : public ISurface {
public:
    VulkanSurface(GLFWwindow *window);
    ~VulkanSurface();

    void setTitle(const TString &name) override;
    void show() override;
    bool processEvents() override;

    GLFWwindow *&getWindow() { return window_; }

private:
    GLFWwindow *window_ = nullptr;
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_VULKAN_VULKAN_SURFACE_H_
