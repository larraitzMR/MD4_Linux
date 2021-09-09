/******************************************************************************
  * @attention
  *
  * COPYRIGHT 2019 STMicroelectronics, all rights reserved
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied,
  * AND SPECIFICALLY DISCLAIMING THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
******************************************************************************/

/** @file
 *
 *  @author ST Microelectronics
 *
 *  @brief
 *
 */

/** @addtogroup Application
  * @{
  */
/** @addtogroup PC_Communication
  * @{
  */

// dllmain.cpp

#include <stuhfl.h>

// Version Information
#define STUHFL_D_VERSION_MAJOR    3
#define STUHFL_D_VERSION_MINOR    0
#define STUHFL_D_VERSION_MICRO    2
#define STUHFL_D_VERSION_NANO    0



#if defined(WIN32) || defined(WIN64)
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
#elif defined(POSIX)
int main(void)
{
    return 0;
}
#else
#endif

// --------------------------------------------------------------------------
STUHFL_T_VERSION CALL_CONV STUHFL_F_GetLibVersion()
{
    return (((uint32_t)STUHFL_D_VERSION_MAJOR << 24) |
            ((uint32_t)STUHFL_D_VERSION_MINOR << 16) |
            ((uint32_t)STUHFL_D_VERSION_MICRO << 8) |
            ((uint32_t)STUHFL_D_VERSION_NANO << 0));
}

/**
  * @}
  */
/**
  * @}
  */
