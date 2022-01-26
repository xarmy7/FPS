#include "material.hpp"

namespace Resources
{
	std::shared_ptr<Material> Material::defaultMaterial = nullptr;

	void Material::sendToShader(const std::shared_ptr<ShaderProgram>& shaderProgram) const
	{
		// Set the model's material informations 
		shaderProgram->setUniform("material.ambient", &ambient);
		shaderProgram->setUniform("material.diffuse", &diffuse);
		shaderProgram->setUniform("material.specular", &specular);
		shaderProgram->setUniform("material.emissive", &emissive);
		
		shaderProgram->setUniform("material.shininess", &shininess);

		// Set the textures' location of the shader program
		std::vector<std::string> shaderName =
		{ "material.alphaTexture", "material.ambientTexture", "material.diffuseTexture",
			"material.emissiveTexture", "material.specularTexture"};

		for (int i = 0; i < 5; i++)
			shaderProgram->setUniform(shaderName[i], &i);
	}

	void Material::bindTextures() const
	{
		if (alphaTex)
			alphaTex->bind(0);

		if (ambientTex)
			ambientTex->bind(1);

		if (diffuseTex)
			diffuseTex->bind(2);
			
		if (emissiveTex)
			emissiveTex->bind(3);

		if (specularTex)
			specularTex->bind(4);

		glActiveTexture(0);
	}
}