#ifdef __APPLE__

#include <CoreFoundation/CoreFoundation.h>
#include <unistd.h>
#include <limits.h>

void SetMacAppWorkingDirectoryToResources()
{
    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(CFBundleGetMainBundle());
    if (!resourcesURL) return;

    char path[PATH_MAX];
    Boolean ok = CFURLGetFileSystemRepresentation(resourcesURL, true, (UInt8*)path, PATH_MAX);
    CFRelease(resourcesURL);

    if (ok) {
        chdir(path); // Now relative paths resolve from .../Contents/Resources
    }
}

#endif