#include "Shader.h"


int Shader::loadShaderCode(char **str, char* filename)
{
	FILE	*datei;
	unsigned int filesize;

	if(fopen_s(&datei,filename,"rb")!=0) return 1;
	fseek(datei,0,SEEK_END);
	filesize = ftell(datei);
	rewind(datei);
	*str=new char[filesize+1];
	fread(*str,sizeof(char),filesize,datei);
	(*str)[filesize]='\0';
	fclose(datei);
	return 0;
}

int Shader::loadShaderCode(char *shaderStr, char *filename, char *shadername)
{
	FILE	*datei;	
	char	b;
	char	str[256];	
	int filesize;

	if(fopen_s(&datei,filename,"rb")!=0) return 1;
	fseek(datei,0,SEEK_END);
	filesize = ftell(datei);
	rewind(datei);
	while(ftell(datei)<filesize)
	{
		fread(&b,1,1,datei);
		if(b=='#')
		{
			int i=0;
			b=0;
			while(b!='#')
			{
				fread(&b,1,1,datei);
				str[i]=b;
				i++;
			}
			b=0;
			str[i-1]=0;
			if (!strcmp(str,shadername))
			{
				fseek(datei,2,SEEK_CUR);
				int i=0;
				while(b!='#' && ftell(datei)<filesize)
				{
					fread(&b,1,1,datei);
					shaderStr[i]=b;
					i++;
				}
				if (b=='#') shaderStr[i-1]=0; else shaderStr[i]=0;
				fclose(datei);
				return 0;
			}
		}
	}
		
	fclose(datei);
	return 0;
}

int Shader::strcmp(char *str1, char *str2)
{
	int i=0;
	while(str1[i]!=0)
	{
		if(str1[i]!=str2[i]) return 1;
		i++;
	}
	return 0;
}

GLuint Shader::createShader(GLenum shaderType, char *shaderName)
{
	char	*str;
	GLuint	shader;
	
	loadShaderCode(&str,shaderName);
	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, (const GLchar**)&str, NULL);
	glCompileShader(shader);
	return shader;
}

GLuint Shader::createShader(GLenum shaderType,char *filename, char *shaderName)
{
	char	*str;
	GLuint	shader;
	
	str = new char[0xffff];
	loadShaderCode(str,filename,shaderName);
	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, (const GLchar**)&str, NULL);
	glCompileShader(shader);
	return shader;
}

GLuint Shader::createShaderProgram(GLuint vertShader, GLuint fragShader)
{
	GLuint shaderProg = glCreateProgram();
	glAttachShader(shaderProg, vertShader);
	glAttachShader(shaderProg, fragShader);
	glLinkProgram(shaderProg);		

	return shaderProg;
}

GLuint Shader::createShaderProgram(GLuint vertShader, GLuint geoShader, GLuint fragShader)
{
	GLuint shaderProg = glCreateProgram();
	glAttachShader(shaderProg, vertShader);
	glAttachShader(shaderProg, geoShader);
	glAttachShader(shaderProg, fragShader);	
	glLinkProgram(shaderProg);		

	return shaderProg;
}

GLuint Shader::createShaderProgram(GLuint vertShader, GLuint tessCtrlShader, GLuint tessEvalShader, GLuint fragShader)
{
	GLuint shaderProg = glCreateProgram();
	glAttachShader(shaderProg, vertShader);
	glAttachShader(shaderProg, tessCtrlShader);
	glAttachShader(shaderProg, tessEvalShader);
	glAttachShader(shaderProg, fragShader);	
	glLinkProgram(shaderProg);		

	return shaderProg;
}