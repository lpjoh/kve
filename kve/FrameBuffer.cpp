#include "FrameBuffer.h"

using namespace kve;

Texture* FrameBuffer::GetTexture() {
	return &texture;
}

void FrameBuffer::PreRender() {
	Bind();
	PreRenderGraphics();
}