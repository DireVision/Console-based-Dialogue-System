#pragma once

#include "utils.h"

#include <array>

namespace Engine
{
  class Renderer;

  struct Screen
  {
    int width = 80;
    int height = 30;
  };

  struct RenderData
  {
    char** pixels;

    RenderData(int width, int height)
    {
      pixels = new char* [height];
      for (int i = 0; i < height; i++)
      {
        pixels[i] = new char[width];
        for (int j = 0; j < width; j++)
        {
          pixels[i][j] = ' ';
        }
      }
    }
    ~RenderData()
    {
      for (int i = 0; i < GetScreen().height; i++)
      {
        delete[] pixels[i];
      }
      delete[] pixels;
    }
  };

  class Renderer
  {
    static Screen m_screen;
    static RenderData m_frame;
    static void Draw(const RenderData& data);

  public:
    static void RenderThread();

    static void SetScreenSize(int width, int height);
    static void SetFrame(RenderData& frame) { m_frame = frame; }
    static void SetPixel(RenderData& data, int x, int y, char c);

    static Screen GetScreen() { return m_screen; }

    static RenderData CreateNewFrame();
    static void Flush();
  };

}
