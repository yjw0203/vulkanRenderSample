#include "yjw_vulkan_type_conversation.h"
#include <cassert>

namespace rhi
{
    VkShaderStageFlagBits ConvertShaderTypeToVkStage(RHIShaderType shaderType)
    {
        switch (shaderType)
        {
        case RHIShaderType::vertex:return VkShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT;
        case RHIShaderType::fragment:return VkShaderStageFlagBits::VK_SHADER_STAGE_FRAGMENT_BIT;
        case RHIShaderType::compute:return VkShaderStageFlagBits::VK_SHADER_STAGE_COMPUTE_BIT;
        }
        return (VkShaderStageFlagBits)0;
    }

    RHIShaderType ConvertVkStageToShaderType(VkShaderStageFlagBits shaderType)
    {
        switch (shaderType)
        {
        case VkShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT:return  RHIShaderType::vertex;
        case VkShaderStageFlagBits::VK_SHADER_STAGE_FRAGMENT_BIT:return  RHIShaderType::fragment;
        case VkShaderStageFlagBits::VK_SHADER_STAGE_COMPUTE_BIT:return  RHIShaderType::compute;
        }
        return RHIShaderType::count;
    }

    VkDescriptorType ConvertShaderResourceTypeToDescriptorType(VulkanShaderResourceType shaderType)
    {
        switch (shaderType)
        {
        case VulkanShaderResourceType::uniform_buffer:return VkDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        case VulkanShaderResourceType::sampled_image:return VkDescriptorType::VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        }
        return (VkDescriptorType)0;
    }

    VkBufferUsageFlags ConvertBufferUsageToVkBufferUsage(RHIResourceUsage usage)
    {
        VkBufferUsageFlags flag = 0;
        if ((int)RHIResourceUsageBits::allow_unordered_access & usage)
        {
            flag |= VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
        }
        if (!((int)RHIResourceUsageBits::deny_shader_resource & usage))
        {
            flag |= VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
        }
        if ((int)RHIResourceUsageBits::allow_transfer_src & usage)
        {
            flag |= VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
        }
        if ((int)RHIResourceUsageBits::allow_transfer_dst & usage)
        {
            flag |= VK_BUFFER_USAGE_TRANSFER_DST_BIT;
        }
        if ((int)RHIResourceUsageBits::allow_vertex_buffer & usage)
        {
            flag |= VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
        }
        if ((int)RHIResourceUsageBits::allow_index_buffer & usage)
        {
            flag |= VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
        }
        if ((int)RHIResourceUsageBits::allow_indirect_buffer & usage)
        {
            flag |= VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT;
        }
        return flag;
    }

    VkImageUsageFlags ConvertImageUsageToVkImageUsage(RHIResourceUsage usage)
    {
        VkImageUsageFlags flag = 0;
        if ((int)RHIResourceUsageBits::allow_render_target & usage)
        {
            flag |= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
        }
        if ((int)RHIResourceUsageBits::allow_depth_stencil & usage)
        {
            flag |= VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
        }
        if ((int)RHIResourceUsageBits::allow_unordered_access & usage)
        {
            flag |= VK_IMAGE_USAGE_STORAGE_BIT;
        }
        if (!((int)RHIResourceUsageBits::deny_shader_resource & usage))
        {
            flag |= VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT;
        }
        if ((int)RHIResourceUsageBits::allow_transfer_src & usage)
        {
            flag |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
        }
        if ((int)RHIResourceUsageBits::allow_transfer_dst & usage)
        {
            flag |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
        }
        return flag;
    }

    VkMemoryPropertyFlags ConvertMemoryTypeToVkMemoryPropertyFlags(RHIMemoryType memoryType)
    {
        VkMemoryPropertyFlags flag = 0;
        if (memoryType == RHIMemoryType::default_)
        {
            flag |= VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
        }
        else if (memoryType == RHIMemoryType::readback)
        {
            flag |= VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
        }
        else if (memoryType == RHIMemoryType::upload)
        {
            flag |= VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
        }
        return flag;
    }

    VkFormat ConvertFormatToVkFormat(RHIFormat format)
    {
        switch (format)
        {
        case RHIFormat::unknow: return VkFormat::VK_FORMAT_UNDEFINED;
        case RHIFormat::R8G8B8A8_unorm: return VkFormat::VK_FORMAT_R8G8B8A8_UNORM;
        case RHIFormat::R8G8B8A8_snorm: return VkFormat::VK_FORMAT_R8G8B8A8_SNORM;
        case RHIFormat::R8G8B8A8_srgb: return VkFormat::VK_FORMAT_R8G8B8A8_SRGB;
        case RHIFormat::R8G8B8A8_sfloat: return VkFormat::VK_FORMAT_R8G8B8A8_SSCALED;
        case RHIFormat::B8G8R8A8_srgb: return VkFormat::VK_FORMAT_B8G8R8A8_SRGB;
        case RHIFormat::R32G32B32_sfloat: return VkFormat::VK_FORMAT_R32G32B32_SFLOAT;
        case RHIFormat::R32G32B32A32_sfloat: return VkFormat::VK_FORMAT_R32G32B32A32_SFLOAT;
        case RHIFormat::R32G32_sfloat: return VkFormat::VK_FORMAT_R32G32_SFLOAT;
        case RHIFormat::D24_unorm_S8_uint: return VkFormat::VK_FORMAT_D24_UNORM_S8_UINT;
        }
        assert(0);
        return VkFormat::VK_FORMAT_UNDEFINED;
    }

    VkCompareOp ConvertCompareOpToVkCompareOp(RHICompareOp compareOp)
    {
        switch (compareOp)
        {
        case RHICompareOp::compare_op_never: return VkCompareOp::VK_COMPARE_OP_NEVER;
        case RHICompareOp::compare_op_less: return VkCompareOp::VK_COMPARE_OP_LESS;
        case RHICompareOp::compare_op_equal: return VkCompareOp::VK_COMPARE_OP_EQUAL;
        case RHICompareOp::compare_op_less_or_equal: return VkCompareOp::VK_COMPARE_OP_LESS_OR_EQUAL;
        case RHICompareOp::compare_op_greater: return VkCompareOp::VK_COMPARE_OP_GREATER;
        case RHICompareOp::compare_op_not_equal: return VkCompareOp::VK_COMPARE_OP_NOT_EQUAL;
        case RHICompareOp::compare_op_greater_or_equal: return VkCompareOp::VK_COMPARE_OP_GREATER_OR_EQUAL;
        case RHICompareOp::compare_op_always: return VkCompareOp::VK_COMPARE_OP_ALWAYS;
        }
        assert(0);
        return VkCompareOp::VK_COMPARE_OP_NEVER;
    }

    VkStencilOp ConvertStencilOpToVkStencilOp(RHIStencilOp stencilOp)
    {
        switch (stencilOp)
        {
        case RHIStencilOp::stencil_op_keep: return VkStencilOp::VK_STENCIL_OP_KEEP;
        case RHIStencilOp::stencil_op_zero: return VkStencilOp::VK_STENCIL_OP_ZERO;
        case RHIStencilOp::stencil_op_replace: return VkStencilOp::VK_STENCIL_OP_REPLACE;
        case RHIStencilOp::stencil_op_increment_and_clamp: return VkStencilOp::VK_STENCIL_OP_INCREMENT_AND_CLAMP;
        case RHIStencilOp::stencil_op_decrement_and_clamp: return VkStencilOp::VK_STENCIL_OP_DECREMENT_AND_CLAMP;
        case RHIStencilOp::stencil_op_invert: return VkStencilOp::VK_STENCIL_OP_INVERT;
        case RHIStencilOp::stencil_op_increment_and_wrap: return VkStencilOp::VK_STENCIL_OP_INCREMENT_AND_WRAP;
        case RHIStencilOp::stencil_op_decrement_and_wrap: return VkStencilOp::VK_STENCIL_OP_DECREMENT_AND_WRAP;
        }
        assert(0);
        return VkStencilOp::VK_STENCIL_OP_KEEP;
    }

    VkStencilOpState ConvertStencilOpStateToVkStencilOpState(RHIStencilOpState stencilOpState)
    {
        VkStencilOpState state{};
        state.failOp = ConvertStencilOpToVkStencilOp(stencilOpState.failOp);
        state.passOp = ConvertStencilOpToVkStencilOp(stencilOpState.passOp);
        state.depthFailOp = ConvertStencilOpToVkStencilOp(stencilOpState.depthFailOp);
        state.compareOp = ConvertCompareOpToVkCompareOp(stencilOpState.compareOp);
        state.compareMask = stencilOpState.compareMask;
        state.writeMask = stencilOpState.writeMask;
        state.reference = stencilOpState.reference;
        return state;
    }
}