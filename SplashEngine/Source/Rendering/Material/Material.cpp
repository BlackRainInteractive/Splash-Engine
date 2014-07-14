//============================================================================
// Name        : Material.cpp
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#include "Material.h"
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <vector>

// The Splash Engine Namespace
namespace se{

	// The Rendering Namespace
	namespace rendering{

/*============================================================================================================*/
/*------PUBLIC FUNCTIONS--------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Load A Shader From A File
		bool Material::Load (std::string VertShader, std::string GeomShader, std::string ControlShader,
							 std::string EvalShader, std::string FragShader){

			// Create The Shaders
			unsigned int vertShader = glCreateShader (GL_VERTEX_SHADER);
			unsigned int geomShader = glCreateShader (GL_GEOMETRY_SHADER);
			unsigned int contShader = glCreateShader (GL_TESS_CONTROL_SHADER);
			unsigned int evalShader = glCreateShader (GL_TESS_EVALUATION_SHADER);
			unsigned int fragShader = glCreateShader (GL_FRAGMENT_SHADER);

			Material::shaderID = glCreateProgram ();

			// Load Vertex Shader
			if (VertShader != ""){
				
				// Load Shader Contents
				std::string shaderString = Material::ReadFromFile (VertShader);
				const char* shaderChar   = shaderString.c_str ();

				// Compile The Shader
				glShaderSource  (vertShader, 1, &shaderChar, nullptr);
				glCompileShader (vertShader);

				// Link The Shader
				glAttachShader (Material::shaderID, vertShader);
			}

			// Load Geom Shader
			if (GeomShader != ""){
				
				// Load Shader Contents
				std::string shaderString = Material::ReadFromFile (GeomShader);
				const char* shaderChar   = shaderString.c_str ();

				// Compile The Shader
				glShaderSource  (geomShader, 1, &shaderChar, nullptr);
				glCompileShader (geomShader);

				// Link The Shader
				glAttachShader (Material::shaderID, geomShader);
			}

			// Load Control Shader
			if (ControlShader != ""){
				
				// Load Shader Contents
				std::string shaderString = Material::ReadFromFile (ControlShader);
				const char* shaderChar   = shaderString.c_str ();

				// Compile The Shader
				glShaderSource  (contShader, 1, &shaderChar, nullptr);
				glCompileShader (contShader);

				// Link The Shader
				glAttachShader (Material::shaderID, contShader);
			}

			// Load Evaluation Shader
			if (EvalShader != ""){
				
				// Load Shader Contents
				std::string shaderString = Material::ReadFromFile (EvalShader);
				const char* shaderChar   = shaderString.c_str ();

				// Compile The Shader
				glShaderSource  (evalShader, 1, &shaderChar, nullptr);
				glCompileShader (evalShader);

				// Link The Shader
				glAttachShader (Material::shaderID, evalShader);
			}

			// Load Frag Shader
			if (FragShader != ""){
				
				// Load Shader Contents
				std::string shaderString = Material::ReadFromFile (FragShader);
				const char* shaderChar   = shaderString.c_str ();

				// Compile The Shader
				glShaderSource  (fragShader, 1, &shaderChar, nullptr);
				glCompileShader (fragShader);

				// Link The Shader
				glAttachShader (Material::shaderID, fragShader);
			}

			// Link The Shader
			glLinkProgram (Material::shaderID);

			// Delete Old Shaders
			glDeleteShader (vertShader);
			glDeleteShader (geomShader);
			glDeleteShader (contShader);
			glDeleteShader (evalShader);
			glDeleteShader (fragShader);

			// Check Shader For Errors
			if (Material::GetErrors ())
				return false;

			// Get All Shader Uniforms
			if (VertShader != "")
				Material::AddUniforms (VertShader);

			if (GeomShader != "")
				Material::AddUniforms (GeomShader);

			if (ControlShader != "")
				Material::AddUniforms (ControlShader);

			if (EvalShader != "")
				Material::AddUniforms (EvalShader);

			if (FragShader != "")
				Material::AddUniforms (FragShader);

			return true;
		}

/*============================================================================================================*/

		// Load From List Of Default Materials
		bool Material::Load (DEFAULT_MATERIAL DefaultMaterial){

			switch (DefaultMaterial){

			// Load Post Pass Material
			case DEFAULT_MATERIAL::POSTPASS:
				return (Material::Load ("Shaders/PostPass/PostPass.vert", "", "", "", "Shaders/PostPass/PostPass.frag"));

			// Load Primitive Line Material
			case DEFAULT_MATERIAL::PRIMITIVE_LINE:
				return (Material::Load ("Shaders/Primitive/Primitive.vert", "", "", "", "Shaders/Primitive/Primitive_Lines.frag"));

			// Load Primitive Solid Material
			case DEFAULT_MATERIAL::PRIMITIVE_SOLID:
				return (Material::Load ("Shaders/Primitive/Primitive.vert", "Shaders/Primitive/Primitive_Solid.geom", "", "", "Shaders/Primitive/Primitive_Solid.frag"));

			// Load Skybox Material
			case DEFAULT_MATERIAL::SKYBOX:
				return (Material::Load ("Shaders/Skybox/Skybox.vert", "", "", "", "Shaders/Skybox/Skybox.frag"));

			// Load Text Material
			case DEFAULT_MATERIAL::TEXT:
				return (Material::Load ("Shaders/Text/Text.vert", "", "", "", "Shaders/Text/Text.frag"));
			}

			return false;
		}

/*============================================================================================================*/

		// Bind The Material
		void Material::Bind (bool Bind){

			// If True, Bind
			if (Bind)
				glUseProgram (Material::shaderID);

			// If False, Unbind
			else
				glUseProgram (0);
		}

/*============================================================================================================*/

		// Return The Uniform ID
		unsigned int Material::GetUniformID (std::string Uniform){
			return Material::uniformList [Uniform];
		}

/*============================================================================================================*/

		// Check If Uniform Exists
		bool Material::GetUniformExists (std::string Uniform){

			// Iterate Through Uniform List
			std::map <std::string, unsigned int>::iterator it = uniformList.find (Uniform);

			// Return Uniform Found
			if (it != uniformList.end())
				return true;

			// Return Uniform Not Found
			return false;
		}

/*============================================================================================================*/

		// Set Uniform (int)
		void Material::SetUniform (std::string Uniform, int Value){
			glProgramUniform1i (Material::shaderID, Material::GetUniformID (Uniform), Value);
		}

/*============================================================================================================*/

		// Set Uniform (float)
		void Material::SetUniform (std::string Uniform, float Value){
			glProgramUniform1f (Material::shaderID, Material::GetUniformID (Uniform), Value);
		}

/*============================================================================================================*/

		// Set Uniform (double)
		void Material::SetUniform (std::string Uniform, double Value){
			glProgramUniform1d (Material::shaderID, Material::GetUniformID (Uniform), Value);
		}

/*============================================================================================================*/

		// Set Uniform (vec2)
		void Material::SetUniform (std::string Uniform, glm::vec2 Value){
			glProgramUniform2f (Material::shaderID, Material::GetUniformID (Uniform), Value.x, Value.y);
		}

/*============================================================================================================*/

		// Set Uniform (vec3)
		void Material::SetUniform (std::string Uniform, glm::vec3 Value){
			glProgramUniform3f (Material::shaderID, Material::GetUniformID (Uniform), Value.x, Value.y, Value.z);
		}

/*============================================================================================================*/

		// Set Uniform (vec4)
		void Material::SetUniform (std::string Uniform, glm::vec4 Value){
			glProgramUniform4f (Material::shaderID, Material::GetUniformID (Uniform), Value.x, Value.y, Value.z, Value.w);
		}

/*============================================================================================================*/

		// Set Uniform (mat2)
		void Material::SetUniform (std::string Uniform, glm::mat2 Value){
			glProgramUniformMatrix2fv (Material::shaderID, Material::GetUniformID (Uniform), 1, GL_FALSE, &Value [0][0]);
		}

/*============================================================================================================*/

		// Set Uniform (mat3)
		void Material::SetUniform (std::string Uniform, glm::mat3 Value){
			glProgramUniformMatrix3fv (Material::shaderID, Material::GetUniformID (Uniform), 1, GL_FALSE, &Value [0][0]);
		}

/*============================================================================================================*/

		// Set Uniform (mat4)
		void Material::SetUniform (std::string Uniform, glm::mat4 Value){
			glProgramUniformMatrix4fv (Material::shaderID, Material::GetUniformID (Uniform), 1, GL_FALSE, &Value [0][0]);
		}

/*============================================================================================================*/
/*------PRIVATE FUNCTIONS-------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Read The Contents Of A Shader File
		std::string Material::ReadFromFile (std::string Shader){

			// Create Stream
			std::ifstream shaderStream (Shader, std::ios::in);
			std::string shaderString;

			// Load The Vertex Shader
			if (shaderStream.is_open ()){

				std::string line = "";

				// Loop Through Shader Code And Save To String
				while (std::getline (shaderStream, line))
					shaderString += '\n' + line;

				// Close The Stream
				shaderStream.close ();
			}

			// Display Error If File Not Found
			else{

				std::cout << "\nERROR: The shader '" << Shader << "' could not be found.\n";
				return ("");
			}

			// Return String
			return (shaderString);
		}

/*============================================================================================================*/

		// Add All Shader Uniforms
		void Material::AddUniforms (std::string Shader){

			// Open File Stream
			std::ifstream file (Shader);
			std::string tempString;

			// Go Though File And Search For Uniforms
			while (file >> tempString){

				// Check If Word Is A Uniform
				if (tempString == "uniform"){

					// Move To Uniform Value
					file >> tempString;
					file >> tempString;

					// Remove Semi-Colon From String
					tempString.pop_back ();

					// Add Uniform
					Material::uniformList [tempString] = glGetUniformLocation (Material::shaderID, tempString.c_str ());
				}
			}
		}

/*============================================================================================================*/

		// Get Any Shader Errors
		bool Material::GetErrors (){

			// Check If Program Compiled
			int success = 0;
			glGetProgramiv (Material::shaderID, GL_LINK_STATUS, &success);

			// If Not, Print Error
			if (success == GL_FALSE){

				int maxLength = 0;
				glGetProgramiv (Material::shaderID, GL_INFO_LOG_LENGTH, &maxLength);

				// Get Error Data
				std::vector <char> errorLog (maxLength);
				std::string s;
				glGetProgramInfoLog (Material::shaderID, maxLength, &maxLength, &errorLog [0]);

				// Buffer Error Into String
				for (unsigned int i = 0; i < errorLog.size (); ++i)
					s += errorLog [i];

				std::cout << "\nERROR: The shader program could not be linked: " << s << '\n';

				return true;
			}

			return false;
		}

/*============================================================================================================*/
/*------DESTRUCTOR--------------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Destroy The Material
		Material::~Material (){
			glDeleteProgram (Material::shaderID);
		}
	}
}
