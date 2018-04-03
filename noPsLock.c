// SilicaAndPina
// noPSLock

#include <taihen.h>
#include <vitasdk.h>
#include <psp2/shellutil.h>

static SceUID hook;
static tai_hook_ref_t ref_hook;


int sceShellUtilLock_patched(SceShellUtilLockType type) {
  sceClibPrintf("sceShellUtilLock()");
  return 0;
}



void _start() __attribute__ ((weak, alias ("module_start")));


int module_start(SceSize argc, const void *args) {
  sceClibPrintf("noPSLock Started!");
  hook = taiHookFunctionImport(&ref_hook,
                                TAI_MAIN_MODULE,
                                TAI_ANY_LIBRARY,
                                0xA9537233, // sceShellUtilLock
                                sceShellUtilLock_patched);

  return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args) {

  // release hooks
  if (hook >= 0) taiHookRelease(hook, ref_hook);


  return SCE_KERNEL_STOP_SUCCESS;
}
