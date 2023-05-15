/**
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// INCLUDES
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// HEADER
#ifndef HEX_WIN_GRAPHICS_HPP
    #include <hex/windows/graphics/WinGraphics.hpp>
#endif /// !HEX_WIN_GRAPHICS_HPP

// Include hex::gl::GLRenderer
#ifndef HEX_GL_RENDERER_HPP
    #include <hex/gl/render/GLRenderer.hpp>
#endif /// !HEX_GL_RENDERER_HPP

#ifdef HEX_LOGGING // LOG

    // Include hex::core::debug
    #ifndef HEX_CORE_CFG_DEBUG_HPP
        #include <hex/core/cfg/hex_debug.hpp>
    #endif /// !HEX_CORE_CFG_DEBUG_HPP

#endif // LOG

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// WinGraphics
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace hex
{

    namespace win
    {

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // CONSTRUCTOR & DESTRUCTOR
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        WinGraphics::WinGraphics()
            :
            GraphicsSystem(),
            mWindow(nullptr)
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Debug("WinGraphics::constructor");
#endif // LOG
        }

        WinGraphics::~WinGraphics() noexcept
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Debug("WinGraphics::destructor");
#endif // LOG

            stopGraphics();
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // METHODS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        void WinGraphics::Initialize()
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Debug("WinGraphics::Initialize");
#endif // LOG

#ifdef HEX_DEBUG // DEBUG
            assert(!mInstance.get() && "WinGraphics::Initialize: already initialized");
#endif // DEBUG

            mInstance = new WinGraphics();
        }

        void WinGraphics::stopGraphics() noexcept
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Debug("WinGraphics::stopGraphics");
#endif // LOG

            // Stop GLRenderer
            auto renderer(hexRenderer::getInstance());
            hexGLRenderer* const glRenderer( static_cast<hexGLRenderer*>(renderer.get()) );
            if (glRenderer)
                glRenderer->Stop();

            if (mWindow)
            {
                glfwDestroyWindow(mWindow);
                mWindow = nullptr;
                glfwTerminate();
            }
        }

        void WinGraphics::onError(int error, const char* description)
        {
#ifdef HEX_LOGGING // LOG
            std::string logMsg("WinGraphics::onError: code=");
            logMsg += std::to_string(error);
            logMsg += "; description=";
            logMsg += description;
            hexLog::Error(logMsg.c_str());
#endif // LOG
        }

        void WinGraphics::onKeyInput(GLFWwindow* window, int key, int scanCode, int action, int mods)
        {
            hexShared<hexGraphics> graphics(getInstance());
            WinGraphics* const winGraphics( static_cast<WinGraphics*>(graphics.get()) );

            if (!winGraphics || !winGraphics->isStarted() || winGraphics->isPaused())
                return;

#ifdef HEX_LOGGING // LOG
            std::string logMsg("WinGraphics::onKeyInput: key=");
            logMsg += std::to_string(key);
            logMsg += "; scanCode=";
            logMsg += std::to_string(scanCode);
            logMsg += "; action=";
            logMsg += std::to_string(action);
            logMsg += "; mods=";
            logMsg += std::to_string(mods);
            hexLog::Debug(logMsg.c_str());
#endif // LOG

            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
                glfwSetWindowShouldClose(winGraphics->mWindow, GLFW_TRUE);
        }

        void WinGraphics::Loop()
        {
            // GLRenderer
            hexShared<hexRenderer> renderer(hexRenderer::getInstance());
            hexGLRenderer* const glRenderer( static_cast<hexGLRenderer*>(renderer.get()) );

#ifdef HEX_LOGGING // LOG
            hexLog::Info("WinGraphics::Loop");
            assert(glRenderer && "WinGraphics::Loop: glRenderer is null");
            assert(isStarted() && "WinGraphics::Loop: not started");
            assert(!glfwWindowShouldClose(mWindow) && "WinGraphics::Loop: !glfwWindowShouldClose");
            assert(glRenderer->isStarted() && "WinGraphics::Loop: Render system is not started");
            assert(!glRenderer->isPaused() && "WinGraphics::Loop: Render system is paused");
#endif // LOG

            while (isStarted() && !glfwWindowShouldClose(mWindow))
            {
                if (glRenderer->isStarted() && !glRenderer->isPaused())
                    glRenderer->Draw();

                glfwSwapBuffers(mWindow);

                glfwPollEvents();
            }

            Stop();
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // OVERRIDE.System
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        bool WinGraphics::onStart()
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Debug("WinGraphics::onStart");
#endif // LOG

            glfwSetErrorCallback(WinGraphics::onError);

            if (!glfwInit())
            {
#ifdef HEX_DEBUG // DEBUG
                throw new std::exception("failed to initialize GLFW");
#else // !DEBUG
                return false;
#endif // DEBUG
            }

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, HEX_GL_MAJOR);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, HEX_GL_MINOR);
            mWindow = glfwCreateWindow(640, 480, "Orbit", nullptr, nullptr);
#ifdef HEX_DEBUG // DEBUG
            assert(mWindow && "WinGraphics::onStart: Window or OpenGL context creation failed");
#else // !DEBUG
            return false;
#endif // DEBUG

            glfwMakeContextCurrent(mWindow);

            gladLoadGL(glfwGetProcAddress);

            glfwSetKeyCallback(mWindow, WinGraphics::onKeyInput);

            setState(WinGraphics::STATE_RUNNING);

            // Start GLRenderer
            auto renderer(hexRenderer::getInstance());
            hexGLRenderer* const glRenderer( static_cast<hexGLRenderer*>(renderer.get()) );
            const bool result( glRenderer->Start() );
            if (!result)
            {
#ifdef HEX_DEBUG // DEBUG
                assert(mWindow && "WinGraphics::onStart: Failed to start GLRenderer");
#else // !DEBUG
                return false;
#endif // DEBUG
            }

            return GraphicsSystem::onStart();
        }

        bool WinGraphics::onResume()
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Debug("WinGraphics::onResume");
#endif // LOG

            // Resume GLRenderer
            auto renderer(hexRenderer::getInstance());
            hexGLRenderer* const glRenderer( static_cast<hexGLRenderer*>(renderer.get()) );
            const bool result( glRenderer->Start() );
            if (!result)
            {
#ifdef HEX_DEBUG // DEBUG
                assert(mWindow && "WinGraphics::onStart: Failed to resume GLRenderer");
#else // !DEBUG
                return false;
#endif // DEBUG
            }

            return GraphicsSystem::onResume();
        }

        void WinGraphics::onPause()
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Debug("WinGraphics::onPause");
#endif // LOG

            // Pause GLRenderer
            auto renderer(hexRenderer::getInstance());
            hexGLRenderer* const glRenderer( static_cast<hexGLRenderer*>(renderer.get()) );
            if (glRenderer)
                glRenderer->Pause();

            GraphicsSystem::onPause();
        }

        void WinGraphics::onStop()
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Debug("WinGraphics::onStop");
#endif // LOG

            stopGraphics();

            GraphicsSystem::onStop();
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    }

}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
