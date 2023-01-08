#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_COMMAND_QUEUE_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_COMMAND_QUEUE_H_

#include "interface/i_command_queue.h"

#include "vulkan/vulkan_common.h"


namespace tigine { namespace graphic {
class VulkanCommandQueue : public ICommandQueue {
public:
    VulkanCommandQueue();
    ~VulkanCommandQueue();

    void submit(ICommandBuffer *command_buffer) override;

private:
    VkCommandPool *vk_command_pool_ = nullptr;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_COMMAND_QUEUE_H_
