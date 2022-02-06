#include "utilities.hpp"

using namespace brls::literals; // for _i18n

Result Utilities::OpenSaveData(FsFileSystem* fileSystem, u64 titleID, AccountUid userID) {
    return fsOpen_SaveData(fileSystem, titleID, userID);
}

int Utilities::MountSave(FsFileSystem fs) {
    return fsdevMountDevice("save", fs);
}

void Utilities::UnmountSave(void) {
    fsdevUnmountDevice("save");
}

// from flagbrew's checkpoint
void Utilities::CopyFile(const std::string& srcPath, const std::string& dstPath) {

    FILE* src = fopen(srcPath.c_str(), "rb");
    if (src == NULL) {
        brls::Logger::error("Failed to open source file: {} during copy with errno {}. Skipping", srcPath, errno);
        return;
    }

    FILE* dst = fopen(dstPath.c_str(), "wb");
    if (dst == NULL) {
        brls::Logger::error("Failed to open destination file: {} during copy with errno {}. Skipping", dstPath, errno);
        fclose(src);
        return;
    }

    fseek(src, 0, SEEK_END);
    u64 sz = ftell(src);
    rewind(src);

    u8* buf    = new u8[0x80000];
    u64 offset = 0;

    size_t slashpos = srcPath.rfind("/");
    g_currentFile   = srcPath.substr(slashpos + 1, srcPath.length() - slashpos - 1);

    while (offset < sz) {
        u32 count = fread((char*)buf, 1, 0x80000, src);
        fwrite((char*)buf, 1, count, dst);
        offset += count;
    }

    delete[] buf;
    fclose(src);
    fclose(dst);

    // commit each file to the save
    if (dstPath.rfind("save:/", 0) == 0) {
        brls::Logger::info("Committing file: {} to the save archive.", dstPath);
        fsdevCommitDevice("save");
    }
}

void Utilities::CreateDirectories() {
    if (!std::filesystem::exists(g_defaultPath)) {
        mkdir(g_defaultPath.c_str(), 777);
    }

    if (!std::filesystem::exists(g_savePath)) {
        mkdir(g_savePath.c_str(), 777);
    }

    if (!std::filesystem::exists(g_editedPath)) {
        mkdir(g_editedPath.c_str(), 777);
    }

    if (!std::filesystem::exists(g_defaultPath + "/Cache")) {
        mkdir("sdmc:/SplatEditor/Cache", 777);
    }
}

void Utilities::CopySave(u64 TitleID) {
    Result rc = 0;
    FsFileSystem fs;
    std::error_code err;
    AccountUid accUid;
    try {
        if (!std::filesystem::exists(g_editedPath + "/save.dat") || !std::filesystem::exists(g_savePath + "/save.dat")) {
            rc = accountGetPreselectedUser(&accUid);
            if (R_SUCCEEDED(rc) && accountUidIsValid(&accUid)) {
                rc = fsOpen_SaveData(&fs, TitleID, accUid);
                if (R_SUCCEEDED(rc)) {
                    fsdevMountDevice("save", fs);

                    Utilities::CopyFile("save:/save.dat", g_savePath + "/save.dat");
                    Utilities::CopyFile("save:/main.dat", g_savePath + "/main.dat");

                    if (std::filesystem::file_size(g_savePath + "/save.dat") != std::filesystem::file_size("save:/save.dat")) {
                        brls::Logger::error("Save.dat size mismatch");
                        std::filesystem::remove(g_savePath + "/save.dat");
                    }

                    fsdevCommitDevice("save");

                    if (!std::filesystem::exists(g_savePath + "/save.dat")) {
                        brls::Logger::error("Failed to copy file, due to: {}", err.message());
                    } else {
                        brls::Logger::info("Successfully copied save.dat");
                    }

                    fsdevUnmountDevice("save");
                } else {
                    brls::Logger::error("Failed to open save data, due to: {}", rc);
                }
            } else {
                brls::Logger::error("Failed to get account uid, due to: {}", rc);
            }
        } else {
            brls::Logger::info("Save.dat already exists");
        }

    } catch (std::exception& e) {
        brls::Logger::error("Exception in Utilites::CopySave, {}", e.what());
        brls::Application::crash("Exception occurred in Utilites::CopySave");
    }
    
}

void Utilities::Init() {
    Result rc = 0;
    CreateDirectories();
    Config::CheckCreateConfig();

    rc = appletInitializeGamePlayRecording();

    if (R_FAILED(rc)) {
        brls::Logger::error("Failed to initialize game play recording, due to: {}", rc);
    }

    rc = accountInitialize(AccountServiceType_Administrator);

    if (R_FAILED(rc)) {
        brls::Logger::error("Failed to initialize account, due to: {}", rc);
    }

    rc = nsInitialize();

    if (R_FAILED(rc)) {
        brls::Logger::error("Failed to initialize ns, due to: {}", rc);
    }

    if (HasWifi() && !std::filesystem::is_empty(g_defaultPath + "/Cache")) {
        try {
            Cache::Init();
        } catch (std::exception& e) {
            brls::Logger::error("{}", e.what());
            brls::Dialog* exceptionDialog = new brls::Dialog(brls::getStr("main/Errors/exception"_i18n, e.what()));
            AddokAndOpen(exceptionDialog);
        }

        brls::Logger::debug("Has wifi");
    }
}

void Utilities::AddokAndOpen(brls::Dialog* dialog) {
    dialog->addButton("brls/hints/ok"_i18n, [] {});
    dialog->open();
}

void Utilities::InjectSave() {
    Result rc = 0;
    AccountUid accUid;
    FsFileSystem fs;
    std::error_code err;

    try {
        rc = accountGetPreselectedUser(&accUid);
        if (R_SUCCEEDED(rc) && accountUidIsValid(&accUid)) {
            rc = fsOpen_SaveData(&fs, TitleID, accUid);
            if (R_SUCCEEDED(rc)) {
                fsdevMountDevice("save", fs);
                std::filesystem::remove("save:/save.dat");
                std::filesystem::remove("save:/main.dat");

                Utilities::CopyFile(g_editedPath + "/save.dat", "save:/save.dat");
                Utilities::CopyFile(g_savePath + "/main.dat", "save:/main.dat");

                brls::Dialog *donedg = new brls::Dialog("main/Dialog/done_inject"_i18n);
                donedg->addButton("brls/hints/ok"_i18n, [] {});
                donedg->open();

                if (std::filesystem::file_size(g_savePath + "/save.dat") != std::filesystem::file_size("save:/save.dat")) {
                    brls::Logger::error("Save.dat size mismatch");
                    std::filesystem::remove(g_savePath + "/save.dat");
                }

                fsdevCommitDevice("save");

                if (!std::filesystem::exists(g_savePath + "/save.dat")) {
                    brls::Logger::error("Failed to copy file, due to: {}", err.message());
                } else {
                    brls::Logger::info("Successfully copied save.dat");
                }
                fsdevUnmountDevice("save");
            } else {
                brls::Logger::error("Failed to open save data, due to: {}", rc);
            }
        } else {
            brls::Logger::error("Failed to get account uid, due to: {}", rc);
        }

    } catch (std::exception& e) {
        brls::Logger::error("Exception in Utilites::CopySave, {}", e.what());
        brls::Application::crash("Exception occurred in Utilites::CopySave");
    }
}

// from https://github.com/Random06457/NX-Title-Control-Dumper
std::string Utilities::DumpAppControl(u64 titleId)
{
    size_t outsize = 0;
    Result rc;
    std::string notfoundp = g_defaultPath + "/Cache/unknown.png";

    NsApplicationControlData *buff = new NsApplicationControlData;

    rc = nsGetApplicationControlData(NsApplicationControlSource_Storage, titleId, buff, sizeof(NsApplicationControlData), &outsize);
    if (R_FAILED(rc))
    {
        brls::Logger::error("nsGetApplicationControlData() failed: {}", rc);
        return notfoundp;
    }

    if (outsize < sizeof(buff->nacp))
    {
        brls::Logger::error("Outsize is too small: {}", outsize);
        return notfoundp;
    }
    
    size_t nacpSize = sizeof(buff->nacp);
    size_t iconSize = sizeof(NsApplicationControlData) - nacpSize;
    
    brls::Logger::debug("icon size: {}", iconSize);
    brls::Logger::debug("nacp size: {}", nacpSize);
    
    char* path = new char[255];

    snprintf(path, 255, "sdmc:/SplatEditor/Cache/%016lx.jpg", titleId);
    brls::Logger::debug("writing {}...", path);
    
    std::ofstream outfile (path,std::ofstream::binary);
    outfile.write(((char*)buff)+nacpSize, iconSize);
    outfile.close();
    brls::Logger::debug("{} Done !", titleId);

    delete buff;
    buff = NULL;

    brls::Logger::debug("Path : {}", path);
    return path;
}

bool Utilities::isValidInRangeString(std::unordered_map<std::string, int> map, std::string key) {
    if (map.find(key) == map.end())
        return false;
    else
        return true;
}

bool Utilities::HasWifi() {
    NifmInternetConnectionType ctype;
    u32 strength = 0;
    NifmInternetConnectionStatus status;

    if (R_SUCCEEDED(nifmGetInternetConnectionStatus(&ctype, &strength, &status))) {
        if (status == NifmInternetConnectionStatus_Connected)
            return true;
        else
            return false;
    }

    return false;
}

void Utilities::splatsave(std::string path) {
    try {
        SaveDataFactory svFactory(path);

        const uint8_t* save_write = nullptr;
        size_t save_write_size = 0;
        std::string save_output_path;
        bool isDecode = false;
        if (svFactory.getInitialEncodeState() == SaveDataFactory::ENCODED) {
            isDecode = true;
            save_output_path = path + ".dec";
            save_write = svFactory.getSaveDecodedPtr();
            save_write_size = svFactory.getDecodedSaveFileSize();
        } else {
            save_output_path = path + ".enc";
            save_write = svFactory.getSaveEncodedPtr();
            save_write_size = svFactory.getEncodedSaveFileSize();
        }

        std::ofstream fileos(save_output_path, std::fstream::binary);
        if (!fileos) {
            std::cout << "Could not open " << save_output_path << std::endl;
        }

        fileos.write((char*)save_write, save_write_size);
        fileos.close();

        if (isDecode) {
            std::cout << "Decrypted " << path << " to " << save_output_path
                      << "!" << std::endl;
        } else {
            std::cout << "Encrypted " << path << " to " << save_output_path
                      << "!" << std::endl;
        }
    } catch (SaveDataFactory::SaveSizeUnknown& e) {
        if (e.m_version == 6) {
            std::cout << "Save version 6 was never seen before. If your save "
                         "was previously unmodified, please submit an issue "
                         "on the project's GitHub page or send me an email at "
                         "contact@the3096.com! Thank you."
                      << std::endl;
        } else {
            std::cout << "Save size incorrect: 0x" << std::hex << e.m_size
                  << std::endl;
        }
    } catch (SaveDataFactory::UnsupportedSaveVersion& e) {
        std::cout << "Save version unsupported: " << e.m_version << std::endl;
    } catch (SaveDataFactory::DecodeFailToVerify& e) {
        std::cout << "Cannot verify save. If you believe this is a mistake, "
                     "and your save is intact, please submit an issue "
                     "on the project's GitHub page or send me an email at "
                     "contact@the3096.com! Thank you."
                  << std::endl;
    } catch (SaveDataFactory::CouldNotOpenFile& e) {
        std::cout << "Could not open " << path << std::endl;
    }
}

void Utilities::UpdateApp() {
    if (!HasWifi()) {
        return;
    }

    bool needupd = false;
    std::string fpath = g_defaultPath + "/splatsave.nro";
    std::string ver_url = "https://github.com/CrustySean/SplatEditorNX/tree/master/ver.txt";

    // firstly let's check the version number from the repo
    try {
        Downloader* dwfile = new Downloader();
        brls::Logger::info("Downloading file... ({})", ver_url);

        dwfile->DownloadFile(ver_url, g_defaultPath + "/ver.txt");
        brls::Logger::info("File downloaded");
        
        dwfile->~Downloader();
    } catch (std::exception& exc) {
        brls::Logger::error("Exception while downloading icon, {}", exc.what());
    }

    // read the string
    std::ifstream txt(g_defaultPath + "/ver.txt");
    std::string ver, upd;
    while (std::getline(txt, ver))
    {
        if (ver != "1.0.0") {
            upd = ver;
            needupd = true;
        }
    }

    if (needupd) {
        std::string app = format_string("https://github.com/CrustySean/SplatEditorNX/releases/download/%s/splatsave.nro", upd);
        try {
            Downloader* dwfile = new Downloader();
            brls::Logger::info("Downloading image... ({})", app);
            while (HasWifi()) {
                dwfile->DownloadFile(app, fpath);
            }
        
            dwfile->~Downloader();
        } catch (std::exception& exc) {
            brls::Logger::error("Exception while downloading icon, {}", exc.what());
        }

        // reload app
        envSetNextLoad(fpath.c_str(), fpath.c_str());
    }
}

void Utilities::RemoveFromString(std::string &p, const std::string &remove) {
    size_t pos = p.find(remove);
    if (pos != std::string::npos) {
        p.erase(pos, remove.length());
    }
}
