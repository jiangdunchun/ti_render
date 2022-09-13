#ifndef __GL430PLUS_SHADER_PROGRAM_H__
#define __GL430PLUS_SHADER_PROGRAM_H__

#include "gl430plus_shader.h"
#include <map>

namespace tigine {
	struct shader_program_descriptor {
		gl430plus_shader* vertex_shader = nullptr;
		gl430plus_shader* fragment_shader = nullptr;
		gl430plus_shader* compute_shader = nullptr;
	};
	
	struct uniform_info {
		GLint location;
		GLint type;
	};

	class gl430plus_shader_program {
	private:
		GLuint m_id;
		std::map<std::string, uniform_info> m_uniforms;

	public:
		gl430plus_shader_program(const shader_program_descriptor& desc);
		~gl430plus_shader_program();
		bool has_error() const;
		std::string get_report() const;
		GLuint get_id() const {
			return m_id;
		}
	};
}

#endif // !__GL430PLUS_SHADER_PROGRAM_H__
