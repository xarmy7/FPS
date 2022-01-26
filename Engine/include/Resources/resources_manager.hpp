#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include "singleton.hpp"

#include "character.hpp"
#include "cube_map.hpp"
#include "material.hpp"
#include "texture.hpp"
#include "shader.hpp"
#include "recipe.hpp"
#include "scene.hpp"
#include "mesh.hpp"

namespace Resources
{
	class ResourcesManager final : public Singleton<ResourcesManager>
	{
		friend Singleton<ResourcesManager>;

	private:
		bool initialized = false;

		ResourcesManager();
		~ResourcesManager();

		std::unordered_map<std::string, std::vector<std::string>>		childrenMeshes;
		std::unordered_map<std::string, std::string>		childrenMaterials;

		std::unordered_map<std::string, std::shared_ptr<Texture>>		textures;
		std::unordered_map<std::string, std::shared_ptr<CubeMap>>		cubeMaps;
		std::unordered_map<std::string, std::shared_ptr<Mesh>>			meshes;
		std::unordered_map<std::string, std::shared_ptr<Material>>		materials;
		std::unordered_map<std::string, std::shared_ptr<Font>>			fonts;

		std::unordered_map<std::string, std::shared_ptr<Shader>>		shaders;
		std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> shaderPrograms;

		std::unordered_map<std::string, std::shared_ptr<Recipe>> recipes;

		void setDefaultResources();

		template <class C>
		void clearMap(std::unordered_map<std::string, std::shared_ptr<C>>& map)
		{
			for (auto it = map.begin(); it != map.end();)
			{
				if (it->second.use_count() <= 1)
					it = map.erase(it);
				else
					it++;
			}
		}

	public:
		static void init();

		static void loadObj(const std::string& filePath);
		static void loadMaterialsFromMtl(const std::string& dirPath, const std::string& fileName);

		static void clearResources();

		static std::shared_ptr<Font> loadFont(const std::string& fontPath);
		static std::shared_ptr<Texture> loadTexture(const std::string& texturePath);
		static std::shared_ptr<Texture> loadTexture(const std::string& name, int width, int height, float* data);
		static std::shared_ptr<CubeMap> loadCubeMap(const std::vector<std::string>& cubeMapPaths);
		static std::shared_ptr<Material> loadMaterial(const std::string& materialPath);
		static std::shared_ptr<Recipe> loadRecipe(const std::string& recipePath);
		static std::shared_ptr<Shader> loadShader(const std::string& shaderPath);
		static std::shared_ptr<ShaderProgram> loadShaderProgram(const std::string& programName, const std::string& vertPath = "", const std::string& fragPath = "", const std::string& geomPath = "");

		static std::vector<std::string>* getMeshNames(const std::string& filePath);
		static std::shared_ptr<Mesh> getMeshByName(const std::string& meshName);
		static std::shared_ptr<Material> getMatByMeshName(const std::string& meshName);
	};
}