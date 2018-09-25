#ifndef SHADER_H
#define SHADER_H

#include <QOpenGLFunctions_4_1_Core>

//This class is pretty much a copy of the shader class at
//https://github.com/SonarSystems/Modern-OpenGL-Tutorials/blob/master/%5BLIGHTING%5D/%5B8%5D%20Basic%20Lighting/Shader.h

class Shader : protected QOpenGLFunctions_4_1_Core
{
    public:
        //Constructor generates the shader on the fly
        Shader(const std::string vertexName, const std::string fragmentName);
        ~Shader();
        //Uses the current shader
        void Use();

        GLuint getProgram() const;
        std::string getName() const;

    private:
        GLuint program;
        std::string mName;
};

#endif
