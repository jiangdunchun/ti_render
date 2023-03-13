#ifndef TIGINE_RHI_VULKAN_VULKAN_TEXTURE_H_
#define TIGINE_RHI_VULKAN_VULKAN_TEXTURE_H_

#include "interface/i_texture.h"

#include "vulkan/vulkan_common.h"

namespace tigine { namespace rhi {
class VulkanTexture : public ITexture {
public:
    VulkanTexture(VkPhysicalDevice *vk_physical_device, VkDevice *vk_device, const TextureDesc &desc);
    ~VulkanTexture();

    VkImageView *getVKImageview() { return &vk_imageview_; }
    VkSampler   *getVKSampler() { return &vk_sampler_; }

private:
    VkPhysicalDevice *vk_physical_device_;
    VkDevice         *vk_device_;

    VkImage        vk_image_;
    VkDeviceMemory vk_device_memory_;
    VkImageView    vk_imageview_;
    VkSampler      vk_sampler_;
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_VULKAN_VULKAN_TEXTURE_H_
