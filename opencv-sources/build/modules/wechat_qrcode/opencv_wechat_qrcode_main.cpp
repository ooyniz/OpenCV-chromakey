// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://opencv.org/license.html.

#ifndef _WIN32
#error "Build configuration error"
#endif
#ifndef CVAPI_EXPORTS
#error "Build configuration error"
#endif

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define OPENCV_MODULE_S "opencv_wechat_qrcode"

namespace cv {
extern __declspec(dllimport) bool __termination;  // Details: #12750
}

#ifdef _WIN32_WCE
#define DLL_MAIN_ARG0 HANDLE
#else
#define DLL_MAIN_ARG0 HINSTANCE
#endif

extern "C"
BOOL WINAPI DllMain(DLL_MAIN_ARG0, DWORD fdwReason, LPVOID lpReserved);

extern "C"
BOOL WINAPI DllMain(DLL_MAIN_ARG0, DWORD fdwReason, LPVOID lpReserved)
{
    if (fdwReason == DLL_THREAD_DETACH || fdwReason == DLL_PROCESS_DETACH)
    {
        if (lpReserved != NULL) // called after ExitProcess() call
        {
            //printf("OpenCV: terminating: " OPENCV_MODULE_S "\n");
            cv::__termination = true;
        }
    }
    return TRUE;
}
