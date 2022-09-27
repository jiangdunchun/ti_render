#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_RENDER_CONTEXT_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_RENDER_CONTEXT_H_

#include <string>

#include "vulkan/vulkan_common.h"
#include "vulkan/vulkan_surface.h"
#include "vulkan/vulkan_render_pass.h"
#include "interface/i_render_context.h"

namespace tigine { namespace graphic {
class VulkanRenderContext : public IRenderContext {
public:
    VulkanRenderContext(const RenderContextDescriptor &desc);
    ~VulkanRenderContext();

    ISurface    *getSurface() override { return surface_; }
    void         present() override { glfwSwapBuffers(window_); }
    IRenderPass *getRenderPass() override { return render_pass_; }

    Extent2D getResolution() override { return {600, 600}; }       //@TODO
    TUInt    getSamples() override { return 0; }                   // @TODO
    TUInt    getNumColorAttachments() const override { return 0; } // @TODO
    bool     hasDepthAttachment() const override { return 0; }     // @TODO
    bool     hasStencilAttachment() const override { return 0; }   // @TODO

private:
    GLFWwindow       *window_;
    VulkanSurface    *surface_;
    VulkanRenderPass *render_pass_;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_RENDER_CONTEXT_H_