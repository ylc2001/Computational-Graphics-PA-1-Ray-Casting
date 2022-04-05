#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>

#include "scene_parser.hpp"
#include "image.hpp"
#include "camera.hpp"
#include "group.hpp"
#include "light.hpp"

#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    for (int argNum = 1; argNum < argc; ++argNum)
    {
        std::cout << "Argument " << argNum << " is: " << argv[argNum] << std::endl;
    }

    if (argc != 3)
    {
        cout << "Usage: ./bin/PA1 <input scene file> <output bmp file>" << endl;
        return 1;
    }
    string inputFile = argv[1];
    string outputFile = argv[2]; // only bmp is allowed.

    // --V--TODO: Main RayCasting Logic
    // First, parse the scene using SceneParser.
    // Then loop over each pixel in the image, shooting a ray
    // through that pixel and finding its intersection with
    // the scene.  Write the color at the intersection to that
    // pixel in your output image.

    SceneParser sceneParser(argv[1]);
    Camera *camera = sceneParser.getCamera();
    Image renderedImage(camera->getWidth(), camera->getHeight());

    for (int x = 0; x < camera->getWidth(); ++x)
    {
        for (int y = 0; y < camera->getHeight(); ++y)
        {
            // 计 算 当 前 像 素(x,y)处 相 机 出 射 光 线camRay
            Ray camRay = sceneParser.getCamera()->generateRay(Vector2f(x, y));
            Group *baseGroup = sceneParser.getGroup();
            Hit hit;
            // 判 断camRay是 否 和 场 景 有 交 点， 并 返 回 最 近 交 点 的 数 据， 存 储 在hit中
            bool isIntersect = baseGroup->intersect(camRay, hit, 0);
            if (isIntersect)
            {
                Vector3f finalColor = Vector3f::ZERO;
                // 找 到 交 点 之 后， 累 加 来 自 所 有 光 源 的 光 强 影 响
                for (int li = 0; li < sceneParser.getNumLights(); ++li)
                {
                    Light *light = sceneParser.getLight(li);
                    Vector3f L, lightColor;
                    // 获 得 光 照 强 度
                    light->getIllumination(camRay.pointAtParameter(hit.getT()), L, lightColor);
                    // 计 算 局 部 光 强
                    finalColor += hit.getMaterial()->Shade(camRay, hit, L, lightColor);
                }
                renderedImage.SetPixel(x, y, finalColor);
            }
            else
            {
                // 不 存 在 交 点， 返 回 背 景 色
                renderedImage.SetPixel(x, y, sceneParser.getBackgroundColor());
            }

            cout << "Hello! Computer Graphics!" << endl;
            return 0;
        }
    }
}
