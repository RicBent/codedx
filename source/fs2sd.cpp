#include "nn.h"
#include "string.h"

nn::Result nn_fs_OpenFile_hook(nn::fs::FileHandle* out, const char* path, s32 mode)
{
    nn::Result rc;
    static char redirectPath[nn::fs::PathLengthMax+1];

    enum SdMountStatus { SdNotMounted = 0, SdMounted = 1, SdMountFailed = 2 };
    static SdMountStatus sdMountStatus = SdNotMounted;

    if (sdMountStatus == SdNotMounted)
    {
        nn::Result rc = nn::fs::MountSdCard("sd");

        if (rc.isSuccess())
        {
            sdMountStatus = SdMounted;
            nn::fs::CreateDirectory("sd:/nsmbudx");
            nn::fs::CreateFile("sd:/nsmbudx/savedata.dat", 0);
        }
        else
            sdMountStatus = SdMountFailed;
    }

    if (sdMountStatus != SdMounted)
        return nn::fs::OpenFile(out, path, mode);

    if (strncmp(path, "content:/", 9) == 0)
    {
        nn::util::SNPrintf(redirectPath, nn::fs::PathLengthMax, "sd:/nsmbudx/content/%s", path + 9);

        rc = nn::fs::OpenFile(out, redirectPath, mode);        
        if (rc.isSuccess())
            return rc;
    }

    else if (strncmp(path, "save:/rp_savedata.dat", 21) == 0)
    {
        rc = nn::fs::OpenFile(out, "sd:/nsmbudx/savedata.dat", mode);
        if (rc.isSuccess())
            return rc;
    }

    return nn::fs::OpenFile(out, path, mode);
}
