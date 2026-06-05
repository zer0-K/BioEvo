#pragma once

#include <GL/glew.h>    // must precede any other OpenGL header
#include <vector>
#include <stdexcept>
#include <string>

#include "imgui.h"

namespace back::grid_fbo
{

    // ── shaders ──────────────────────────────────────────────────────────────────
    //
    // Pixel-space coords (y=0 at top-left) → NDC, rendered into an FBO whose
    // attached texture is then displayed by ImGui::Image with default UVs.
    // The Y-axis is kept as-is (y_pixel=0 → ndc.y=-1 → texture row 0) which
    // means the texture is "upside-down" in GL convention, but ImGui samples
    // row 0 first (top of the image) so the grid appears right-side-up.

    static const char* VERT_SRC = R"(
    #version 330 core
    layout(location = 0) in vec2 aPos;
    uniform vec2 u_resolution;
    void main() {
        vec2 ndc = (aPos / u_resolution) * 2.0 - 1.0;
        gl_Position = vec4(ndc.x, ndc.y, 0.0, 1.0);
    }
    )";

    static const char* FRAG_SRC = R"(
    #version 330 core
    uniform vec4 u_color;
    out vec4 FragColor;
    void main() { FragColor = u_color; }
    )";

    // ── helpers ───────────────────────────────────────────────────────────────────

    static GLuint compile_shader(GLenum type, const char* src)
    {
        GLuint s = glCreateShader(type);
        glShaderSource(s, 1, &src, nullptr);
        glCompileShader(s);
        GLint ok = 0;
        glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
        if (!ok) {
            char buf[512] = {};
            glGetShaderInfoLog(s, 512, nullptr, buf);
            glDeleteShader(s);
            throw std::runtime_error(std::string("Shader compile error: ") + buf);
        }
        return s;
    }

    static GLuint build_program()
    {
        GLuint v = compile_shader(GL_VERTEX_SHADER,   VERT_SRC);
        GLuint f = compile_shader(GL_FRAGMENT_SHADER, FRAG_SRC);
        GLuint p = glCreateProgram();
        glAttachShader(p, v);
        glAttachShader(p, f);
        glLinkProgram(p);
        glDeleteShader(v);
        glDeleteShader(f);
        GLint ok = 0;
        glGetProgramiv(p, GL_LINK_STATUS, &ok);
        if (!ok) {
            char buf[512] = {};
            glGetProgramInfoLog(p, 512, nullptr, buf);
            glDeleteProgram(p);
            throw std::runtime_error(std::string("Shader link error: ") + buf);
        }
        return p;
    }

    // ── GridFBO ───────────────────────────────────────────────────────────────────

    struct GridFBO
    {
        GLuint fbo  = 0;
        GLuint tex  = 0;
        GLuint prog = 0;
        GLuint vao  = 0;
        GLuint vbo  = 0;
        int    w    = 0;
        int    h    = 0;

        void init()
        {
            prog = build_program();

            glGenVertexArrays(1, &vao);
            glGenBuffers(1, &vbo);
            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
            glEnableVertexAttribArray(0);
            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glGenFramebuffers(1, &fbo);
            glGenTextures(1, &tex);
            glBindTexture(GL_TEXTURE_2D, tex);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        void destroy()
        {
            if (fbo)  { glDeleteFramebuffers(1,  &fbo);  fbo  = 0; }
            if (tex)  { glDeleteTextures(1,      &tex);  tex  = 0; }
            if (prog) { glDeleteProgram(prog);            prog = 0; }
            if (vao)  { glDeleteVertexArrays(1,  &vao);  vao  = 0; }
            if (vbo)  { glDeleteBuffers(1,       &vbo);  vbo  = 0; }
            w = h = 0;
        }

        // Render the grid into the FBO.
        // cells: row-major bool vector, row 0 = top row of the grid.
        // cs: cell size in pixels (integer).
        void render(const std::vector<bool>& cells, int grid_w, int grid_h, int cs)
        {
            int new_w = grid_w * cs;
            int new_h = grid_h * cs;

            // Re-allocate texture + re-attach when dimensions change
            if (new_w != w || new_h != h) {
                w = new_w;
                h = new_h;
                glBindTexture(GL_TEXTURE_2D, tex);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0,
                            GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
                glBindTexture(GL_TEXTURE_2D, 0);

                glBindFramebuffer(GL_FRAMEBUFFER, fbo);
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                    GL_TEXTURE_2D, tex, 0);
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
            }

            // Build quad geometry (2 triangles = 6 verts × 2 floats per alive cell).
            // A 1-pixel inset per side creates implicit grid lines from the bg colour.
            float inset = (cs >= 4) ? 1.0f : 0.0f;
            verts.clear();
            auto quad = [&](float x0, float y0, float x1, float y1) {
                verts.insert(verts.end(), {
                    x0, y0,   x1, y0,   x0, y1,
                    x1, y0,   x1, y1,   x0, y1,
                });
            };

            for (int cy = 0; cy < grid_h; ++cy)
                for (int cx = 0; cx < grid_w; ++cx)
                    if (cells[(size_t)(cy * grid_w + cx)])
                        quad(cx*cs + inset,       cy*cs + inset,
                            (cx+1)*cs - inset,   (cy+1)*cs - inset);

            int alive_verts = (int)verts.size() / 2;

            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER,
                        (GLsizeiptr)(verts.size() * sizeof(float)),
                        verts.empty() ? nullptr : verts.data(),
                        GL_DYNAMIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            // ── Save GL state that ImGui depends on ───────────────────────────
            GLint prev_fbo, prev_prog, prev_vao;
            GLint prev_vp[4];
            glGetIntegerv(GL_FRAMEBUFFER_BINDING,  &prev_fbo);
            glGetIntegerv(GL_CURRENT_PROGRAM,      &prev_prog);
            glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &prev_vao);
            glGetIntegerv(GL_VIEWPORT,              prev_vp);

            // ── Render into FBO ───────────────────────────────────────────────
            glBindFramebuffer(GL_FRAMEBUFFER, fbo);
            glViewport(0, 0, w, h);
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_BLEND);

            // Clear to background (dead-cell) colour
            glClearColor(0.07f, 0.13f, 0.16f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // Draw alive cells
            if (alive_verts > 0) {
                glUseProgram(prog);
                glUniform2f(glGetUniformLocation(prog, "u_resolution"),
                            (float)w, (float)h);
                glUniform4f(glGetUniformLocation(prog, "u_color"),
                            0.31f, 0.78f, 0.47f, 1.0f);   // green
                glBindVertexArray(vao);
                glDrawArrays(GL_TRIANGLES, 0, alive_verts);
                glBindVertexArray(0);
                glUseProgram(0);
            }

            // ── Restore ───────────────────────────────────────────────────────
            glBindFramebuffer(GL_FRAMEBUFFER, (GLuint)prev_fbo);
            glUseProgram((GLuint)prev_prog);
            glBindVertexArray((GLuint)prev_vao);
            glViewport(prev_vp[0], prev_vp[1], prev_vp[2], prev_vp[3]);
        }

        // The texture ID ready to pass to ImGui::Image.
        ImTextureID imgui_id()  const { return (ImTextureID)(intptr_t)tex; }
        ImVec2      imgui_size() const { return {(float)w, (float)h};       }

    private:
        std::vector<float> verts;
    };

} // namespace back::grid_fbo
