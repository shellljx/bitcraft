//
// Created by 李金祥 on 2022/6/4.
//

#include "McRenderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <stdlib.h>
#include "Atlas.h"
#include "AssetManager.h"
#include "model/Model.h"
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include "gpu/opengl/GLRenderTarget.h"
#include "gpu/Surface.h"

namespace bitcraft {

McRenderer::McRenderer() {

}

McRenderer::~McRenderer() {

}

glm::vec3 cameraPos = glm::vec3(-154.0f, 100.0f, -81.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
void errorcallback(int error, const char *msg) {
  std::string s = msg;
}

void framebuffer_size_callback(int width, int height) {
}
const std::vector<float> color_day({0.6f, 0.85f, 0.9f});
const std::vector<float> color_night({0.1f, 0.1f, 0.1f});
std::atomic<bool> load = false;
int count = 0;
std::unique_ptr<Model> createModel(int id) {
  switch (id) {
    case 9916:return nullptr;
    case 0:return nullptr;
    case 1:return Model::MakeBlockWithName("stone");
    case 2:return Model::MakeBlockWithName("granite");
    case 4:return Model::MakeBlockWithName("diorite");
    case 6:return Model::MakeBlockWithName("andesite");
    case 7:return Model::MakeBlockWithName("polished_andesite");
    case 8:return Model::MakeBlockWithName("grass_block");
    case 9:return Model::MakeBlockWithName("grass_block");
    case 10:return Model::MakeBlockWithName("dirt");
    case 14:return Model::MakeBlockWithName("cobblestone");
    case 15:return Model::MakeBlockWithName("oak_planks");
    case 16:return Model::MakeBlockWithName("spruce_planks");
    case 33:return Model::MakeBlockWithName("bedrock");
    case 34:
      //water
      return Model::MakeBlockWithName("water");
    case 35:return Model::MakeBlockWithName("water");
    case 36:return Model::MakeBlockWithName("water");
    case 37:return Model::MakeBlockWithName("water");
    case 38:return Model::MakeBlockWithName("water");
    case 39:return Model::MakeBlockWithName("water");
    case 40:return Model::MakeBlockWithName("water");
    case 41:return Model::MakeBlockWithName("water");
    case 42:return Model::MakeBlockWithName("water");
    case 50:return Model::MakeBlockWithName("lava");
    case 52:return Model::MakeBlockWithName("lava");
    case 54:return Model::MakeBlockWithName("lava");
    case 56:return Model::MakeBlockWithName("lava");
    case 66:return Model::MakeBlockWithName("sand");
    case 69:return Model::MakeBlockWithName("gold_ore");
    case 58:return Model::MakeBlockWithName("lava");
    case 71:return Model::MakeBlockWithName("iron_ore");
    case 73:return Model::MakeBlockWithName("coal_ore");
    case 77:return Model::MakeBlockWithName("oak_log");
    case 89:return Model::MakeBlockWithName("acacia_log");
    case 113:return Model::MakeBlockWithName("oak_wood");
    case 136:return Model::MakeBlockWithName("stripped_birch_wood");
    case 140:return Model::MakeBlockWithName("stripped_jungle_wood");
    case 149:return Model::MakeBlockWithName("oak_leaves");
    case 151:return Model::MakeBlockWithName("oak_leaves");
    case 153:return Model::MakeBlockWithName("oak_leaves");
    case 155:return Model::MakeBlockWithName("oak_leaves");
    case 200:return Model::MakeBlockWithName("jungle_leaves");
    case 205:return Model::MakeBlockWithName("acacia_leaves");
    case 207:return Model::MakeBlockWithName("acacia_leaves");
    case 209:return Model::MakeBlockWithName("acacia_leaves");
    case 263:return Model::MakeBlockWithName("lapis_ore");
    case 264:return Model::MakeBlockWithName("deepslate_lapis_ore");
    case 18684:return Model::MakeBlockWithName("deepslate");
    case 17714:return Model::MakeBlockWithName("tuff");
    case 3411:return Model::MakeBlockWithName("deepslate_diamond_ore");
    case 3955:return Model::MakeBlockWithName("deepslate_redstone_ore");
    case 70:return Model::MakeBlockWithName("deepslate_gold_ore");
    case 68:return Model::MakeBlockWithName("gravel");
    case 72:return Model::MakeBlockWithName("deepslate_iron_ore");
    case 128:return Model::MakeBlockWithName("dark_oak_wood");
    case 211:return Model::MakeBlockWithName("acacia_leaves");
    case 213:return Model::MakeBlockWithName("acacia_leaves");
    case 214:return Model::MakeBlockWithName("acacia_leaves");
    case 256:return Model::MakeBlockWithName("flowering_azalea_leaves");
    case 272:return Model::MakeBlockWithName("dispenser");
    case 273:return Model::MakeBlockWithName("dispenser");
    case 281:return Model::MakeBlockWithName("note_block");
    case 420:return Model::MakeBlockWithName("note_block");
    case 512:return Model::MakeBlockWithName("note_block");
    case 513:return Model::MakeBlockWithName("note_block");
    case 516:return Model::MakeBlockWithName("note_block");
    case 544:return Model::MakeBlockWithName("note_block");
    case 546:return Model::MakeBlockWithName("note_block");
    case 721:return Model::MakeBlockWithName("note_block");
    case 802:return Model::MakeBlockWithName("note_block");
    case 804:return Model::MakeBlockWithName("note_block");
    case 826:return Model::MakeBlockWithName("note_block");
    case 977:return Model::MakeBlockWithName("note_block");
    case 1022:return Model::MakeBlockWithName("note_block");
    case 1028:return Model::MakeBlockWithName("note_block");
    case 1030:return Model::MakeBlockWithName("note_block");
    case 1397:return Model::MakeBlockWithName("cobweb");
    case 1398:return Model::MakeBlockWithName("grass");
    case 1401:return Model::MakeBlockWithName("seagrass");
    case 1402:return Model::MakeBlockWithName("seagrass");
    case 1403:return Model::MakeBlockWithName("seagrass");
    case 1468:return Model::MakeBlockWithName("dandelion");
    case 1469:return Model::MakeBlockWithName("poppy");
    case 1472:return Model::MakeBlockWithName("azure_bluet");
    case 1478:return Model::MakeBlockWithName("cornflower");
    case 1617:return Model::MakeBlockWithName("fire_up0");
    case 1672:return Model::MakeBlockWithName("fire_up0");
    case 1860:return Model::MakeBlockWithName("fire_up0");
    case 1092:return Model::MakeBlockWithName("bed");
    case 1290:return Model::MakeBlockWithName("bed");
    case 1307:return Model::MakeBlockWithName("bed");
    case 1380:return Model::MakeBlockWithName("detector_rail");
    case 1493:return Model::MakeBlockWithName("wall_torch");
    case 1696:return Model::MakeBlockWithName("fire_up0");
    case 1993:return Model::MakeBlockWithName("fire_up0");
    case 1996:return Model::MakeBlockWithName("fire_up0");
    case 2044:return Model::MakeBlockWithName("oak_stairs");
    case 3410:return Model::MakeBlockWithName("diamond_ore");
    case 3705:return Model::MakeBlockWithName("rail");
    case 3953:return Model::MakeBlockWithName("redstone_ore");
    case 4016:return Model::MakeBlockWithName("clay");
    case 4050:return Model::MakeBlockWithName("oak_fence_gate");
    case 4058:return Model::MakeBlockWithName("oak_fence_gate");
    case 4062:return Model::MakeBlockWithName("oak_fence_gate");
    case 4065:return Model::MakeBlockWithName("oak_fence_gate");
    case 4066:return Model::MakeBlockWithName("oak_fence_gate");
    case 4938:return Model::MakeBlockWithName("glow_lichen");
    case 4988:return Model::MakeBlockWithName("glow_lichen");
    case 5004:return Model::MakeBlockWithName("glow_lichen");
    case 5010:return Model::MakeBlockWithName("glow_lichen");
    case 5012:return Model::MakeBlockWithName("glow_lichen");
    case 5015:return Model::MakeBlockWithName("glow_lichen");
    case 5016:return Model::MakeBlockWithName("glow_lichen");
    case 5017:return Model::MakeBlockWithName("glow_lichen");
    case 5019:return Model::MakeBlockWithName("glow_lichen");
    case 8143:return Model::MakeBlockWithName("tall_grass_bottom");
    case 8144:return Model::MakeBlockWithName("tall_grass_bottom");
    case 17818:return Model::MakeBlockWithName("copper_ore");
    case 17819:return Model::MakeBlockWithName("deepslate_copper_ore");
    default:int i = 0;
      return Model::MakeBlockWithName("bedrock");
  }
}

const char* vertexShaderSource = R"(
#version 300 es
layout (location = 0) in vec3 aPos;
void main() {
    gl_Position = vec4(aPos, 1.0);
}
)";

// 片段着色器
const char* fragmentShaderSource = R"(
#version 300 es
precision mediump float;
out vec4 FragColor;
void main() {
    FragColor = vec4(1.0, 0.5, 0.2, 1.0);
}
)";


void McRenderer::draw(tgfx::Canvas *canvas) const {
  float vertices[] = {
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.0f,  0.5f, 0.0f
  };

  GLuint VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // 编译着色器
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);

  // 创建着色器程序
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  auto renderTarget = std::static_pointer_cast<tgfx::GLRenderTarget>(canvas->getSurface()->getRenderTarget());
  glUseProgram(shaderProgram);
  glBindFramebuffer(GL_FRAMEBUFFER, renderTarget->glFrameBuffer().id);
  glViewport(0,0,canvas->getSurface()->width(),canvas->getSurface()->height());
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void McRenderer::setData(const ServerChunkDataPacket *packet, int cx, int cz) {
  if (count >= 4) {
    return;
  }
  count++;
  auto chunkData = packet->getChunkData();
  for (int sectionY = 0; sectionY < 256 / 16; ++sectionY) {
    short blockCount = chunkData.readInt16();
    unsigned char bits_per_block = chunkData.readUint8();
    auto palette_type = (bits_per_block == 0 ? 0 : (bits_per_block <= 8 ? 1 : 2));
    auto palette_length = 0;
    auto palette_value = 0;
    std::vector<int> palette;
    switch (palette_type) {
      case 0:palette_value = chunkData.readVarInt();
        break;
      case 1:
        if (bits_per_block < 4) {
          bits_per_block = 4;
        }
        palette_length = chunkData.readVarInt();
        palette = std::vector<int>(palette_length);
        for (int p = 0; p < palette_length; ++p) {
          palette[p] = chunkData.readVarInt();
        }
        break;
      case 2:break;
    }
    unsigned int individual_value_mask = (unsigned int) ((1 << bits_per_block) - 1);
    int data_array_size = chunkData.readVarInt();
    std::vector<unsigned long long int> data_array(data_array_size);
    for (int d = 0; d < data_array_size; ++d) {
      data_array[d] = chunkData.readUint64();
    }

    int bit_offset = 0;
    if (blockCount != 0) {
      Point3D position;

      for (int y = 0; y < 16; ++y) {
        position.y = y + sectionY * 16;
        for (int z = 0; z < 16; ++z) {
          position.z = z + cz * 16;
          for (int x = 0; x < 16; ++x) {
            position.x = x + cx * 16;
            if (palette_type == 0) {
              //single
              auto model = createModel(palette_value);
              auto v = model->generateFaces(position);
              faces_.insert(faces_.end(), v.begin(), v.end());
              continue;
            }

            if (64 - (bit_offset % 64) < bits_per_block) {
              bit_offset += 64 - (bit_offset % 64);
            }
            int start_long_index = bit_offset / 64;
            int end_long_index = start_long_index;
            int start_offset = bit_offset % 64;
            bit_offset += bits_per_block;
            unsigned int raw_id;
            if (start_long_index == end_long_index) {
              raw_id = (unsigned int) (data_array[start_long_index] >> start_offset);
            } else {
              int end_offset = 64 - start_offset;
              raw_id = (unsigned int) (data_array[start_long_index] >> start_offset | data_array[end_long_index] << end_offset);
            }
            raw_id &= individual_value_mask;

            if (palette_type == 1) {
              raw_id = palette[raw_id];
            }

            auto model = createModel(raw_id);
            if (model != nullptr) {
              auto v = model->generateFaces(position);
              faces_.insert(faces_.end(), v.begin(), v.end());
            }
          }
        }
      }
    }

    unsigned char bits_per_biome = chunkData.readUint8();
    palette_type = (bits_per_biome == 0 ? 0 : (bits_per_biome <= 3 ? 1 : 2));
    switch (palette_type) {
      case 0:palette_value = chunkData.readVarInt();
        break;
      case 1:palette_length = chunkData.readVarInt();
        palette = std::vector<int>(palette_length);
        for (int j = 0; j < palette_length; ++j) {
          palette[j] = chunkData.readVarInt();
        }
        break;
      case 2:break;
    }
    individual_value_mask = (unsigned int) ((1 << bits_per_biome) - 1);
    data_array_size = chunkData.readVarInt();
    data_array = std::vector<unsigned long long int>(data_array_size);
    for (int j = 0; j < data_array_size; ++j) {
      data_array[j] = chunkData.readUint64();
    }

    bit_offset = 0;
    for (int y = 0; y < 16 / 4; ++y) {
      for (int z = 0; z < 16 / 4; ++z) {
        for (int x = 0; x < 16 / 4; ++x) {
          const int biome_index = sectionY * 64 + y * 16 + z * 4 + x;
          if (palette_type == 0) {
            continue;
          }
          if (64 - (bit_offset % 64) < bits_per_biome) {
            bit_offset += 64 - (bit_offset % 64);
          }
          int start_long_index = bit_offset / 64;
          int end_long_index = start_long_index;
          int start_offset = bit_offset % 64;
          bit_offset += bits_per_biome;

          unsigned int raw_id;
          if (start_long_index == end_long_index) {
            raw_id = (unsigned int) (data_array[start_long_index] >> start_offset);
          } else {
            int end_offset = 64 - start_offset;
            raw_id = (unsigned int) (data_array[start_long_index] >> start_offset | data_array[end_long_index] << end_offset);
          }
          raw_id &= individual_value_mask;
          if (palette_type == 1) {
            raw_id = palette[raw_id];
          }
        }
      }
    }
  }
  load = true;
}
}