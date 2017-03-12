#ifndef HELLO_AWEM_GLUTILZ_H
#define HELLO_AWEM_GLUTILZ_H

#include <GLES2/gl2.h>

#include "../../core/memory.h"
#include "../../core/utils/math.h"
#include "../../log/Log.h"

#define GL_CHECK(x) \
	x; \
	{\
	for (GLint error = glGetError(); error; error = glGetError()) { \
		LOGI("GL error in %s: %s() : line %d", __FILE__, __FUNCTION__ , __LINE__); \
		LOGI("\t after %s : %s", #x, gbox::glutils::getGlErrorString(error)); \
	} \
}

namespace gbox {

	namespace glutils {

		const char* getGlErrorString(GLenum error) {
			switch (error) {
			case GL_NO_ERROR:
				return "GL_NO_ERROR";
			case GL_INVALID_ENUM:
				return "GL_INVALID_ENUM";
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				return "GL_INVALID_FRAMEBUFFER_OPERATION";
			case GL_INVALID_VALUE:
				return "GL_INVALID_VALUE";
			case GL_INVALID_OPERATION:
				return "GL_INVALID_OPERATION";
			case GL_OUT_OF_MEMORY:
				return "GL_OUT_OF_MEMORY";
			default:
				return "UNKNOWN ERROR";
			}
		}

		const char* getShaderTypeString(GLenum type) {
			switch (type) {
			case GL_VERTEX_SHADER:
				return "GL_VERTEX_SHADER";
			case GL_FRAGMENT_SHADER:
				return "GL_FRAGMENT_SHADER";
			default:
				return "UNKNOWN TYPE";
			}
		}

		const char* getGlDataType(GLenum type) {
			switch (type) {
			case GL_FLOAT:
				return "GL_FLOAT";
			case GL_FLOAT_VEC2:
				return "GL_FLOAT_VEC2";
			case GL_FLOAT_VEC3:
				return "GL_FLOAT_VEC3";
			case GL_FLOAT_VEC4:
				return "GL_FLOAT_VEC4";
			case GL_INT:
				return "GL_INT";
			case GL_INT_VEC2:
				return "GL_INT_VEC2";
			case GL_INT_VEC3:
				return "GL_INT_VEC3";
			case GL_INT_VEC4:
				return "GL_INT_VEC4";
			case GL_BOOL:
				return "GL_BOOL";
			case GL_BOOL_VEC2:
				return "GL_BOOL_VEC2";
			case GL_BOOL_VEC3:
				return "GL_BOOL_VEC3";
			case GL_BOOL_VEC4:
				return "GL_BOOL_VEC4";
			case GL_FLOAT_MAT2:
				return "GL_FLOAT_MAT2";
			case GL_FLOAT_MAT3:
				return "GL_FLOAT_MAT3";
			case GL_FLOAT_MAT4:
				return "GL_FLOAT_MAT4";
			case GL_SAMPLER_2D:
				return "GL_SAMPLER_2D";
			case GL_SAMPLER_CUBE:
				return "GL_SAMPLER_CUBE";
			default:
				return "UNKNOWN TYPE";
			}
		}

		void infoCommon() {
			LOGI("==== GL common info ====");
			LOGI("GL Version: %s", glGetString(GL_VERSION));
			LOGI("GL Vendor: %s", glGetString(GL_VENDOR));
			LOGI("GL Renderer: %s", glGetString(GL_RENDERER));
			LOGI("GL Extensions: %s", glGetString(GL_EXTENSIONS));

			int iValue;
			glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &iValue);
			LOGI("GL_MAX_VERTEX_ATTRIBS=%d", iValue);
		}

		void infoShader(GLint shader) {
			GLint isCompile = 0;
			GLint isDelete = 0;
			GLint infoLogLength = 0;
			GLint sourceLength = 0;
			GLint shaderType = 0;
			GL_CHECK(glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompile));
			GL_CHECK(glGetShaderiv(shader, GL_DELETE_STATUS, &isDelete));
			GL_CHECK(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength));
			GL_CHECK(glGetShaderiv(shader, GL_SHADER_SOURCE_LENGTH, &sourceLength));
			GL_CHECK(glGetShaderiv(shader, GL_SHADER_TYPE, &shaderType));

			LOGI("==== GL shader info ====");
			LOGI("ID: %d : %s", shader, getShaderTypeString(shaderType));
			if (isCompile) {
				LOGI("COMPILED");
			}
			if (isDelete) {
				LOGI("DELETED");
			}

			if (sourceLength) {
				core::AutoArray<char> source(new char[sourceLength], sourceLength);
				GL_CHECK(glGetShaderSource(shader, sourceLength, NULL, *source));
				LOGI("\n%s\n", *source);
			}

			if (infoLogLength) {
				core::AutoArray<char> info(new char[infoLogLength], infoLogLength);
				GL_CHECK(glGetShaderInfoLog(shader, infoLogLength, NULL, *info));
				if (isCompile) {
					LOGI("COMPILE INFO:\n%s", *info);
				} else {
					LOGI("COMPILE ERRORS:\n%s", *info);
				}
			}
		}

		void infoProgram(GLint program) {
			GLint activeAttrs = 0;
			GLint activeAttrMaxLen = 0;
			GLint activeUniforms = 0;
			GLint activeUniformMaxLen = 0;
			GLint attachedShaders = 0;
			GLint deleteStatus = 0;
			GLint infoLogLength = 0;
			GLint linkStatus = 0;
			GLint validateStatus = 0;

			GL_CHECK(glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &activeAttrs));
			GL_CHECK(glGetProgramiv(program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &activeAttrMaxLen));
			GL_CHECK(glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &activeUniforms));
			GL_CHECK(glGetProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &activeUniformMaxLen));
			GL_CHECK(glGetProgramiv(program, GL_ATTACHED_SHADERS, &attachedShaders));
			GL_CHECK(glGetProgramiv(program, GL_DELETE_STATUS, &deleteStatus));
			GL_CHECK(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength));
			GL_CHECK(glGetProgramiv(program, GL_LINK_STATUS, &linkStatus));
			GL_CHECK(glGetProgramiv(program, GL_VALIDATE_STATUS, &validateStatus));

			LOGI("==== GL program info ====");
			LOGI("ID:%d\tSHADERS:%d\t%s\t%s", program, attachedShaders, (linkStatus ? "LINKED " : ""),
					(validateStatus ? "VALIDATED " : ""));
			if (linkStatus) {
				int bufferSize = core::max(activeAttrMaxLen, activeUniformMaxLen);
				core::AutoArray<char> buffer(new char[bufferSize], bufferSize);
				GLint size;
				GLenum type;
				GLint location;
				for (int i = 0; i < activeUniforms; i++) {
					GL_CHECK(glGetActiveUniform(program, i, bufferSize, nullptr, &size, &type, *buffer));
					location = GL_CHECK(glGetUniformLocation(program, *buffer));
					LOGI("UNIFORM[%d]: %s %s %d", location, *buffer, getGlDataType(type), size);
				}
				for (int i = 0; i < activeAttrs; i++) {
					GL_CHECK(glGetActiveAttrib(program, i, bufferSize, nullptr, &size, &type, *buffer));
					location = GL_CHECK(glGetAttribLocation(program, *buffer));
					LOGI("ATTRIBUTE[%d]: %s %s %d", location, *buffer, getGlDataType(type), size);
				}
			}
			if (deleteStatus) {
				LOGI("DELETED");
			}

			if (infoLogLength) {
				core::AutoArray<char> info(new char[infoLogLength], infoLogLength);
				GL_CHECK(glGetProgramInfoLog(program, infoLogLength, NULL, *info));
				if (linkStatus) {
					LOGI("LINKING INFO:\n%s", *info);
				} else {
					LOGI("LINKING ERRORS:\n%s", *info);
				}
			}
		}

		GLuint loadShader(GLenum shaderType, const char* source) {
			GLuint shader = GL_CHECK(glCreateShader(shaderType))
			;
			if (shader) {
				GLint compiled = 0;
				GL_CHECK(glShaderSource(shader, 1, &source, nullptr));
				GL_CHECK(glCompileShader(shader));
				GL_CHECK(glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled));
				if (!compiled) {
					infoShader(shader);
					GL_CHECK(glDeleteShader(shader));
					shader = 0;
				}
			}
			return shader;
		}

		GLuint createProgram(GLint verShader, GLint fragShader) {
			GLuint program = GL_CHECK(glCreateProgram())
			;
			if (program) {
				GLint linkStatus = 0;
				GL_CHECK(glAttachShader(program, verShader));
				GL_CHECK(glAttachShader(program, fragShader));
				GL_CHECK(glLinkProgram(program));
				GL_CHECK(glGetProgramiv(program, GL_LINK_STATUS, &linkStatus));
				if (!linkStatus) {
					infoProgram(program);
					GL_CHECK(glDeleteProgram(program));
					program = 0;
				}
			}
			return program;
		}

	}

}

#endif //HELLO_AWEM_GLUTILZ_H
