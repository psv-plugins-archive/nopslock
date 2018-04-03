// SilicaAndPina
// noPSLock

#include <taihen.h>
#include <vitasdk.h>
#include <psp2/shellutil.h>

static SceUID hook;
static tai_hook_ref_t ref_hook;

static SceUID hook2;
static tai_hook_ref_t ref_hook2;

int sceShellUtilLock_patched(SceShellUtilLockType type) {
  return 0;
}

int sceShellUtilUnlock_patched(SceShellUtilLockType type) {
  return 0;
}



void _start() __attribute__ ((weak, alias ("module_start")));


int module_start(SceSize argc, const void *args) {
  hook = taiHookFunctionImport(&ref_hook,
                                TAI_MAIN_MODULE,
                                TAI_ANY_LIBRARY,
                                0xA9537233, // sceShellUtilLock
                                sceShellUtilLock_patched);
  
  hook2 = taiHookFunctionImport(&ref_hook2,
                                TAI_MAIN_MODULE,
                                TAI_ANY_LIBRARY,
                                0x21A6CF54, // sceShellUtilUnlock
                                sceShellUtilUnlock_patched);


  return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args) {

  // release hooks
  if (hook >= 0) taiHookRelease(hook, ref_hook);
  if (hook2 >= 0) taiHookRelease(hook2, ref_hook2);

  return SCE_KERNEL_STOP_SUCCESS;
}