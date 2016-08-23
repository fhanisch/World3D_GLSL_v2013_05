#include "main.h"

class Shader
{
private:
	static int loadShaderCode(char **str, char *filename);
	static int loadShaderCode(char *shaderStr, char *filename, char *shadername);
	static int strcmp(char *str1, char *str2);
public:			
	static GLuint createShader(GLenum shaderType, char *shaderName);	
	static GLuint createShader(GLenum shaderType,char *filename, char *shaderName);	
	static GLuint createShaderProgram(GLuint vertShader, GLuint fragShader);
	static GLuint createShaderProgram(GLuint vertShader, GLuint geoShader, GLuint fragShader);
	static GLuint createShaderProgram(GLuint vertShader, GLuint tessCtrlShader, GLuint tessEvalShader, GLuint fragShader);
};

