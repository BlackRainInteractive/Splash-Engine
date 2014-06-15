#pragma once

#include <glm/glm.hpp>
#include <string>
#include <map>

// The Splash Engine Namespace
namespace se{

	// The Rendering Namespace
	namespace rendering{

		// The Material Class
		class Material{
		public:

			// Destructor
			virtual ~Material ();

			// Functions - Shader Loading
			bool Load (std::string VertShader, std::string GeomShader, std::string ControlShader,
					   std::string EvalShader, std::string FragShader);
			void Bind (bool Bind);

			// Functions - Uniforms
			unsigned int GetUniformID (std::string Uniform);
			bool GetUniformExists	  (std::string Uniform);
			void SetUniform			  (std::string Uniform, int Value);
			void SetUniform			  (std::string Uniform, float Value);
			void SetUniform			  (std::string Uniform, double Value);
			void SetUniform			  (std::string Uniform, glm::vec2 Value);
			void SetUniform			  (std::string Uniform, glm::vec3 Value);
			void SetUniform			  (std::string Uniform, glm::vec4 Value);
			void SetUniform			  (std::string Uniform, glm::mat2 Value);
			void SetUniform			  (std::string Uniform, glm::mat3 Value);
			void SetUniform			  (std::string Uniform, glm::mat4 Value);

			// Variables
			unsigned int shaderID;
			std::map <std::string, unsigned int> uniformList;

		private:

			// Functions - Shader Loading
			std::string ReadFromFile (std::string Shader);
			void AddUniforms (std::string Shader);
			bool GetErrors ();
		};
	}
}