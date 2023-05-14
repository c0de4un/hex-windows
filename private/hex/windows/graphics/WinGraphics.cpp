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
            GraphicsSystem()
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
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // OVERRIDE.System
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        bool WinGraphics::onStart()
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Debug("WinGraphics::onStart");
#endif // LOG

            return GraphicsSystem::onStart();
        }

        bool WinGraphics::onResume()
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Debug("WinGraphics::onResume");
#endif // LOG

            return GraphicsSystem::onResume();
        }

        void WinGraphics::onPause()
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Debug("WinGraphics::onPause");
#endif // LOG

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
