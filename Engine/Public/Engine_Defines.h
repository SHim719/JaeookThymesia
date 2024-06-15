#pragma once

#pragma warning (disable : 4005)
#pragma warning (disable : 4251)
#pragma warning (disable : 4828)
#pragma warning (disable : 4819)
#pragma warning (disable : 6262)

#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include <d3dx11effect.h>
#include <directxtk/DDSTextureLoader.h>
#include <directxtk/WICTextureLoader.h>
#include <directxtk/PrimitiveBatch.h>
#include <directxtk/VertexTypes.h>
#include <directxtk/Effects.h>
#include <directxtk/SpriteBatch.h>
#include <directxtk/SpriteFont.h>
#include <DirectXCollision.h>

#include <DirectXMath.h>
using namespace DirectX;

#include <map>
#include <list>
#include <vector>
#include <algorithm>
#include <string>
#include <assert.h>
#include <iostream>
#include <ctime>
#include <random>
#include <unordered_map>
#include <functional>
#include <fstream>
#include <filesystem>


#include "Engine_Enums.h"

#define TEXTURE_TYPE_MAX TextureType_TRANSMISSION


#include "Engine_Macro.h"
#include "Engine_Function.h"
#include "Engine_Typedef.h"
#include "Engine_Struct.h"

using namespace Engine;
using namespace std;
namespace fs = std::filesystem;

