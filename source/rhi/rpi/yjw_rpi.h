#pragma once
#include "yjw_rpi_define.h"

namespace rpi
{
	void RPIInit(int width, int height, void* window);
	RPIBuffer RPICreateGpuVertexBuffer(int size);
	RPIBuffer RPICreateGpuIndexBuffer(int size);
	RPIBuffer RPICreateGpuIndirectBuffer(int size);
	RPIBuffer RPICreateUploadBuffer(int size);
	RPITexture RPICreateDefaultTexture2D(int width, int height, RPIFormat format,int mipLevels = 1);
	RPITexture RPICreateDepthStencilTexture2D(int width, int height, RPIFormat format);
	RPITexture RPICreateUploadTexture2D(int width, int height, RPIFormat format);
	void RPIDestoryResource(RPIResource resource);

	RPIShader RPICreateShader(const char* name);
	void RPIDestoryShader(RPIShader shader);

	RPIDescriptor RPICreateDescriptor(RPIResource resource, RPIDescriptorType descriptorType, RPIFormat format);
	void RPIDestoryDescriptor(RPIDescriptor descriptor);

	RPIDescriptorSet RPICreateDescriptorSet(RPIPipeline pipeline);
	void RPIDestoryDescriptorSet(RPIDescriptorSet descriptorSet);

	//cmd
	RPICommandBuffer RPICreateCommandBuffer();
	void RPIDestoryCommandBuffer(RPICommandBuffer commandBuffer);
	void RPISubmitCommandBuffer(RPICommandBuffer commandBuffer);
	void RPIResetCommandBuffer(RPICommandBuffer commandBuffer);
	void RPICmdCopyToSwapchainBackTexture(RPICommandBuffer commandBuffer, RPITexture texture);
	void RPIPresent();

	//update
	void RPIUpdateResource(RPIResource resource, void* data,int offset, int size);
}