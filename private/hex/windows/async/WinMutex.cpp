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
#ifndef HEX_WIN_MUTEX_HPP
    #include <hex/windows/async/WinMutex.hpp>
#endif /// !HEX_WIN_MUTEX_HPP

#ifdef HEX_LOGGING // DEBUG

    // Include hex::core::debug
    #ifndef HEX_CORE_CFG_DEBUG_HPP
        #include <hex/core/cfg/hex_debug.hpp>
    #endif /// !HEX_CORE_CFG_DEBUG_HPP

#endif // DEBUG

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// WinMutex
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace hex
{

    namespace win
    {

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // CONSTRUCTOR
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        WinMutex::WinMutex()
            :
            mLocked(false),
            mLockedFlag(),
            mMutex()
        {
            InitializeCriticalSection(&mMutex);
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // DESTRUCTOR
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        WinMutex::~WinMutex()
        {
            DeleteCriticalSection(&mMutex);
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // GETTERS & SETTERS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        bool WinMutex::isLocked() const noexcept
        {
            const bool result(mLocked);

            return result;
        }

        void* WinMutex::native_handle() noexcept
        {
            return static_cast<void*>(&mMutex);
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // METHODS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        void WinMutex::handleLock()
        {
            unsigned char triesCount(0);

            if (triesCount < WinMutex::MAX_LOCK_TRIES)
            {
                try
                {
                    EnterCriticalSection(&mMutex);
                }
#ifdef HEX_LOGGING // LOGGING
                catch (const std::exception& _exception)
                {
                    
                }
#endif // LOGGING
                catch (...)
                {
                    triesCount++;
                }
            }
            else
                EnterCriticalSection(&mMutex);
        }

        bool WinMutex::try_lock() noexcept
        {
            if (!mLockedFlag.test_and_set())
            {
                mLocked = true;
                return true;
            }

            try
            {
                this->handleLock();
            }
            catch (...)
            {
                return false;
            }

            mLocked = true;

            return true;
        }

        void WinMutex::lock()
        {
            if (!mLockedFlag.test_and_set())
            {
                mLocked = true;
                return;
            }

            this->handleLock();
            mLocked = true;
        }

        void WinMutex::unlock() noexcept
        {
            if (!mLocked)
                return;

            try
            {
                LeaveCriticalSection(&mMutex);
            }
            catch (...)
            {
                // void
            }

            mLockedFlag.clear();
            mLocked = false;
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    }

}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
