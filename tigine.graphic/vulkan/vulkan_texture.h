#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_TEXTURE_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_TEXTURE_H_

#include "vulkan/vulkan_common.h"
#include "interface/i_texture.h"

namespace tigine { namespace graphic {
class VulkanTexture : public ITexture {
public:
    VulkanTexture(VkDevice *device, const TextureDescriptor &desc);
    ~VulkanTexture();

    VkImageView *getVKImageview() { return &vk_imageview_; }
    VkSampler   *getVKSampler() { return &vk_sampler_; }

private:
    VkDevice   *vk_device_;
    VkImageView vk_imageview_;
    VkSampler   vk_sampler_;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_TEXTURE_H_
