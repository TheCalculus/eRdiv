#ifndef SHADERS_H
#define SHADERS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLuint loadShaders(const char* vertex_file_path, const char* fragment_file_path) {
    // https://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
    GLuint VertexShaderID   = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    FILE* VertexShaderStream = fopen(vertex_file_path, "r");

    if (VertexShaderStream != NULL) {
        fseek(VertexShaderStream, 0, SEEK_END);
        long size = ftell(VertexShaderStream);
        fseek(VertexShaderStream, 0, SEEK_SET);

        char* VertexShaderCode = (char*)malloc(size + 1);
        fread(VertexShaderCode, 1, size, VertexShaderStream);
        fclose(VertexShaderStream);

        VertexShaderCode[size] = '\0';

        printf("compiling shader: %s\n", vertex_file_path);

        glShaderSource(VertexShaderID, 1, (const GLchar**)&VertexShaderCode, NULL);
        glCompileShader(VertexShaderID);

        GLint Result = GL_FALSE;
        int   InfoLogLength;

        glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        
        if (InfoLogLength > 0) {
            char* VertexShaderErrorMessage = (char*)malloc(InfoLogLength + 1);
            glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, VertexShaderErrorMessage);
            printf("%s\n", VertexShaderErrorMessage);
            free(VertexShaderErrorMessage);
        }

        free(VertexShaderCode);
    } else {
        printf("unable to open %s\n", vertex_file_path);
        getchar();
        return 0;
    }

    FILE* FragmentShaderStream = fopen(fragment_file_path, "r");

    if (FragmentShaderStream != NULL) {
        fseek(FragmentShaderStream, 0, SEEK_END);
        long size = ftell(FragmentShaderStream);
        fseek(FragmentShaderStream, 0, SEEK_SET);

        char* FragmentShaderCode = (char*)malloc(size + 1);

        fread(FragmentShaderCode, 1, size, FragmentShaderStream);
        fclose(FragmentShaderStream);

        FragmentShaderCode[size] = '\0';

        printf("compiling shader: %s\n", fragment_file_path);
        glShaderSource(FragmentShaderID, 1, (const GLchar **)&FragmentShaderCode, NULL);
        glCompileShader(FragmentShaderID);

        GLint Result = GL_FALSE;
        int   InfoLogLength;

        glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        
        if (InfoLogLength > 0) {
            char* FragmentShaderErrorMessage = (char*)malloc(InfoLogLength + 1);
            glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, FragmentShaderErrorMessage);
            printf("%s\n", FragmentShaderErrorMessage);
            free(FragmentShaderErrorMessage);
        }

        free(FragmentShaderCode);
    }

    printf("linking program\n");

    GLuint ProgramID = glCreateProgram();
    
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    GLint Result = GL_FALSE;
    int   InfoLogLength;

    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    
    if (InfoLogLength > 0) {
        char* ProgramErrorMessage = (char*)malloc(InfoLogLength + 1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, ProgramErrorMessage);
        printf("%s\n", ProgramErrorMessage);
        free(ProgramErrorMessage);
    }

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

#endif
