#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

static SDL_Window *window = NULL;
static SDL_GPUDevice *device = NULL;

static SDL_GPUGraphicsPipeline *fillPipeline;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
  window = SDL_CreateWindow("Project Dungeon", 1440, 810, SDL_WINDOW_RESIZABLE);
  if (window == NULL)
  {
    SDL_Log("FAILED TO CREATE WINDOW\n%s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  device = SDL_CreateGPUDevice(
      SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_MSL,
      false,
      NULL);
  if (device == NULL)
  {
    SDL_Log("FAILED TO CREATE GPU DEVICE\n%s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  if (!SDL_ClaimWindowForGPUDevice(device, window))
  {
    SDL_Log("FAILED TO CLAIM WINDOW FOR GPU DEVICE\n%s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
  if (event->type == SDL_EVENT_QUIT)
  {
    return SDL_APP_SUCCESS;
  }

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
  SDL_GPUCommandBuffer *cmdBuffer = SDL_AcquireGPUCommandBuffer(device);
  if (cmdBuffer == NULL)
  {
    SDL_Log("FAILED TO CREATE COMMAND BUFFER\n%s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  SDL_GPUTexture *swapchainTexture;
  if (!SDL_WaitAndAcquireGPUSwapchainTexture(cmdBuffer, window, &swapchainTexture, NULL, NULL))
  {
    SDL_Log("FAILED TO ACQUIRE GPU SWAPCHAIN TEXTURE\n%s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  SDL_GPUColorTargetInfo colorTargetInfo = {0};
  colorTargetInfo.texture = swapchainTexture;
  colorTargetInfo.clear_color = (SDL_FColor){0.56f, 0.34f, 0.23f, 1.f};
  colorTargetInfo.load_op = SDL_GPU_LOADOP_CLEAR;
  colorTargetInfo.store_op = SDL_GPU_STOREOP_STORE;

  SDL_GPURenderPass *renderPass = SDL_BeginGPURenderPass(cmdBuffer, &colorTargetInfo, 1, NULL);

  SDL_EndGPURenderPass(renderPass);

  SDL_SubmitGPUCommandBuffer(cmdBuffer);

  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
  SDL_ReleaseWindowFromGPUDevice(device, window);
  SDL_DestroyWindow(window);
  SDL_DestroyGPUDevice(device);
}