#include "vulkan/vulkan_render_pass.h"

namespace tigine { namespace rhi {
namespace {
VkAttachmentLoadOp mapVkAttachmentLoadOp(AttachmentLoadOp loadOp) {
    switch (loadOp) {
    case AttachmentLoadOp::DontCare:
        return VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    case AttachmentLoadOp::Load:
        return VK_ATTACHMENT_LOAD_OP_LOAD;
    case AttachmentLoadOp::Clear:
        return VK_ATTACHMENT_LOAD_OP_CLEAR;
    default:
        RHI_VULKAN_THROW("fail to map AttachmentLoadOption!");
    }
}

VkAttachmentStoreOp mapVkAttachmentStoreOp(AttachmentStoreOp storeOp) {
    switch (storeOp) {
    case AttachmentStoreOp::DontCare:
        return VK_ATTACHMENT_STORE_OP_DONT_CARE;
    case AttachmentStoreOp::Store:
        return VK_ATTACHMENT_STORE_OP_STORE;
    default:
        RHI_VULKAN_THROW("fail to map AttachmentStoreOption!");
    }
}

VkFormat getDepthStencilVkFormat(const DataFormat depthFormat, const DataFormat &stencilFormat) {
    if (depthFormat != DataFormat::Undefined && stencilFormat != DataFormat::Undefined) {
        if (depthFormat == stencilFormat) {
            return mapVkFormat(depthFormat);
        } else {
            RHI_VULKAN_THROW("fail to map get DepthStencilFormat, depthFormat and stencilFormat must be same!");
        }
    }

    if (depthFormat != DataFormat::Undefined) {
        return mapVkFormat(depthFormat);
    }

    if (stencilFormat != DataFormat::Undefined) {
        return mapVkFormat(stencilFormat);
    }
    RHI_VULKAN_THROW("fail to map get DepthStencilFormat!");
}
} // namespace

VulkanRenderPass::VulkanRenderPass(const VulkanContextInfo &context, const RenderPassDesc &desc) : vk_device_(context.vk_device) {
    std::uint32_t num_colors = static_cast<std::uint32_t>(desc.color_attachments.size());
    std::uint32_t num_all    = num_colors;
    bool has_ds = false;
    if (desc.depth_attachment.format != DataFormat::Undefined || desc.stencil_attachment.format != DataFormat::Undefined) {
        ++num_all;
        has_ds = true;
    }

    std::vector<VkAttachmentDescription> vk_attachments_desc(desc.samples > 1 ? num_all + num_colors : num_all);
    for (rsize_t i = 0; i < num_colors; ++i) {
        const AttachmentDesc    &attachment_desc    = desc.color_attachments[i];
        VkAttachmentDescription &vk_attachment_desc = vk_attachments_desc[i];
        
        vk_attachment_desc.flags          = 0;
        vk_attachment_desc.format         = mapVkFormat(attachment_desc.format);
        vk_attachment_desc.samples        = VK_SAMPLE_COUNT_1_BIT;
        vk_attachment_desc.loadOp         = mapVkAttachmentLoadOp(attachment_desc.load);
        vk_attachment_desc.storeOp        = mapVkAttachmentStoreOp(attachment_desc.store);
        vk_attachment_desc.stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        vk_attachment_desc.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        vk_attachment_desc.initialLayout  = (attachment_desc.load == AttachmentLoadOp::Load ? VK_IMAGE_LAYOUT_PRESENT_SRC_KHR : VK_IMAGE_LAYOUT_UNDEFINED);
        vk_attachment_desc.finalLayout    = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    }
    if (has_ds) {
        const AttachmentDesc    &depth_attachment_desc   = desc.depth_attachment;
        const AttachmentDesc    &stencil_attachment_desc = desc.stencil_attachment;
        VkAttachmentDescription &vk_attachment_desc      = vk_attachments_desc[num_colors];

        vk_attachment_desc.flags          = 0;
        vk_attachment_desc.format         = getDepthStencilVkFormat(depth_attachment_desc.format, stencil_attachment_desc.format);
        vk_attachment_desc.samples        = VkSampleCountFlagBits(desc.samples);
        vk_attachment_desc.loadOp         = mapVkAttachmentLoadOp(depth_attachment_desc.load);
        vk_attachment_desc.storeOp        = mapVkAttachmentStoreOp(depth_attachment_desc.store);
        vk_attachment_desc.stencilLoadOp  = mapVkAttachmentLoadOp(stencil_attachment_desc.load);
        vk_attachment_desc.stencilStoreOp = mapVkAttachmentStoreOp(stencil_attachment_desc.store);
        vk_attachment_desc.initialLayout  = depth_attachment_desc.load == AttachmentLoadOp::Load || stencil_attachment_desc.load == AttachmentLoadOp::Load ? VK_IMAGE_LAYOUT_PRESENT_SRC_KHR : VK_IMAGE_LAYOUT_UNDEFINED;
        vk_attachment_desc.finalLayout    = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    }
    if (desc.samples > 1) {
        for (size_t i = 0; i < num_colors; ++i) {
            const AttachmentDesc    &attachment_desc = desc.color_attachments[i];
            VkAttachmentDescription    &vk_attachment_desc  = vk_attachments_desc[num_colors + i];

            vk_attachment_desc.flags          = 0;
            vk_attachment_desc.format         = mapVkFormat(attachment_desc.format);
            vk_attachment_desc.samples        = VkSampleCountFlagBits(desc.samples);
            vk_attachment_desc.loadOp         = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
            vk_attachment_desc.storeOp        = mapVkAttachmentStoreOp(attachment_desc.store);
            vk_attachment_desc.stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
            vk_attachment_desc.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
            vk_attachment_desc.initialLayout  = attachment_desc.load == AttachmentLoadOp::Load ? VK_IMAGE_LAYOUT_PRESENT_SRC_KHR :  VK_IMAGE_LAYOUT_UNDEFINED;
            vk_attachment_desc.finalLayout    = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
        }
    }

    std::vector<VkAttachmentReference> color_attachments_refs(num_colors);
    for (size_t i = 0; i < num_colors; ++i) {
        color_attachments_refs[i].attachment = i;
        color_attachments_refs[i].layout     = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    }
    VkAttachmentReference ds_attachment_ref = {};
    if (has_ds) {
        ds_attachment_ref.attachment = num_colors;
        ds_attachment_ref.layout     = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    }
    std::vector<VkAttachmentReference> msaa_attachments_refs;
    if (desc.samples > 1) {
        msaa_attachments_refs.resize(num_colors);

        for (size_t i = 0; i < num_colors; ++i) {
            msaa_attachments_refs[i].attachment = num_all + i;
            msaa_attachments_refs[i].layout     = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        }
    }

    VkSubpassDescription subpass {};
    subpass.pipelineBindPoint    = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = num_colors;
    if (desc.samples > 1) {
        subpass.pColorAttachments   = msaa_attachments_refs.data();
        subpass.pResolveAttachments = color_attachments_refs.data();
    } else {
        subpass.pColorAttachments = color_attachments_refs.data();
    }
    subpass.pDepthStencilAttachment = (has_ds ? &ds_attachment_ref : nullptr);
    
    VkSubpassDependency dependency {};
    dependency.srcSubpass    = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass    = 0;
    dependency.srcStageMask  = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.srcAccessMask = 0;
    dependency.dstStageMask  = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    VkRenderPassCreateInfo render_pass_info {};
    render_pass_info.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    render_pass_info.attachmentCount = desc.samples > 1 ? num_all + num_colors : num_colors;
    render_pass_info.pAttachments    = vk_attachments_desc.data();
    render_pass_info.subpassCount    = 1;
    render_pass_info.pSubpasses      = &subpass;
    render_pass_info.dependencyCount = 1;
    render_pass_info.pDependencies   = &dependency;
    RHI_VULKAN_THROW_IF_FAILD(vkCreateRenderPass(*vk_device_, &render_pass_info, nullptr, &vk_render_pass_),
        "failed to create render pass!");
}

VulkanRenderPass::~VulkanRenderPass() { 
	vkDestroyRenderPass(*vk_device_, vk_render_pass_, nullptr);
}
}} // namespace tigine::rhi
