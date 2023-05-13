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
#ifndef HEX_WIN_CONSOLE_LOGGER_HPP
    #include <hex/windows/metrics/WinConsoleLogger.hpp>
#endif /// !HEX_WIN_CONSOLE_LOGGER_HPP

// Include hex::core::Log
#include <hex/core/metrics/Log.hpp>

// Include STL iostream
#include <iostream>

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// WinConsoleLogger
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace hex
{

    namespace win
    {

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // CONSTRUCTOR & DESTRUCTOR
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        WinConsoleLogger::WinConsoleLogger() HEX_NOEXCEPT = default;

        WinConsoleLogger::~WinConsoleLogger() noexcept = default;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // OVERRIDE.ILogger
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        void WinConsoleLogger::printInfo(const char* const msg) HEX_NOEXCEPT
        {
            std::cout << "INFO: " << msg << "\n";
        }

        void WinConsoleLogger::printDebug(const char* const msg) HEX_NOEXCEPT
        {
            std::cout << "DEBUG: " << msg << "\n";
        }

        void WinConsoleLogger::printWarning(const char* const msg) HEX_NOEXCEPT
        {
            std::cout << "WARNING: " << msg << "\n";
        }

        void WinConsoleLogger::printError(const char* const msg) HEX_NOEXCEPT
        {
            std::cout << "ERROR: " << msg << "\n";
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // METHODS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        void WinConsoleLogger::Initialize() HEX_NOEXCEPT
        {
            hexLog::Initialize( static_cast<hex::core::ILogger*>(new WinConsoleLogger()) );
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    }

}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
