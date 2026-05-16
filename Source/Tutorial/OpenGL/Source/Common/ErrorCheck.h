#ifndef AENGINE_ERRORCHECK_H
#define AENGINE_ERRORCHECK_H
#include <string>

extern void CheckShaderCompileError(unsigned int shader, const std::string& type);
extern void CheckProgramLinkError(unsigned int program);

#endif //AENGINE_ERRORCHECK_H
