#include "exc_handler.hpp"

/* This work was done by WerWolv, see README for details. */

void ExceptionHandler::PrintInfo(ThreadExceptionDump *ctx) {
    u64 stackTrace[0x20] = { 0 };
    s32 stackTraceSize = 0;
    unwindStack(stackTrace, &stackTraceSize, 0x20, ctx->fp.x);

    brls::Logger::error("\n");
    brls::Logger::error(Utilities::format_string("[PC] BASE + 0x%016lx", ctx->pc.x - getHomebrewBaseAddress()));
    brls::Logger::error(Utilities::format_string("[LR] BASE + 0x%016lx", ctx->lr.x - getHomebrewBaseAddress()));
    brls::Logger::error(Utilities::format_string("[SP] BASE + 0x%016lx", ctx->sp.x - getHomebrewBaseAddress()));
    brls::Logger::error(Utilities::format_string("[FP] BASE + 0x%016lx", ctx->fp.x - getHomebrewBaseAddress()));
    brls::Logger::error("== Begin stack trace ==");
    for (s8 i = 0; i < stackTraceSize - 2; i++)
        brls::Logger::error(Utilities::format_string("[%d] BASE + 0x%016lx", stackTraceSize - i - 3, stackTrace[i] - getHomebrewBaseAddress()));
    brls::Logger::error("== End stack trace ==");
    brls::Logger::error("\n");
}

void ExceptionHandler::unwindStack(u64 *outStackTrace, s32 *outStackTraceSize, size_t maxStackTraceSize, u64 currFp) {
    struct StackFrame{
        u64 fp;     // Frame Pointer (Pointer to previous stack frame)
        u64 lr;     // Link Register (Return address)
    };
    for (size_t i = 0; i < maxStackTraceSize; i++) {
        if (currFp == 0 || currFp % sizeof(u64) != 0)
            break;
        
        auto currTrace = reinterpret_cast<StackFrame*>(currFp); 
        outStackTrace[(*outStackTraceSize)++] = currTrace->lr;
        currFp = currTrace->fp;
    }
}

u64 ExceptionHandler::getHomebrewBaseAddress() {
    u32 p;
    MemoryInfo info;
    svcQueryMemory(&info, &p, (u64) &getHomebrewBaseAddress);
    return info.addr;
}

extern "C" {
   
    alignas(16) u8 __nx_exception_stack[0x8000];
    u64 __nx_exception_stack_size = sizeof(__nx_exception_stack);
    void NORETURN __nx_exit(Result rc, LoaderReturnFn retaddr);

    void __libnx_exception_handler(ThreadExceptionDump *ctx) {
        std::string errorDesc;
        static bool alreadyCrashed = false;
        static ThreadExceptionDump ctxBackup;

        appletUnlockExit();

        if (alreadyCrashed) {
            brls::Logger::error("Fatal exception thrown during exception handling. Closing immediately.");
            ExceptionHandler::PrintInfo(ctx);

            // Setup FatalCpuContext to pass on crash information to fatal
            static FatalCpuContext fatalCtx = { 0 };
            for (u8 i = 0; i < 29; i++)
                fatalCtx.aarch64_ctx.x[i] = ctxBackup.cpu_gprs[i].x;

            fatalCtx.aarch64_ctx.pc = ctxBackup.pc.x;
            fatalCtx.aarch64_ctx.lr = ctxBackup.lr.x;
            fatalCtx.aarch64_ctx.sp = ctxBackup.sp.x;
            fatalCtx.aarch64_ctx.fp = ctxBackup.fp.x;
            
            fatalCtx.aarch64_ctx.start_address = ExceptionHandler::getHomebrewBaseAddress();
            ExceptionHandler::unwindStack(fatalCtx.aarch64_ctx.stack_trace, reinterpret_cast<s32*>(&fatalCtx.aarch64_ctx.stack_trace_size), 32, ctxBackup.fp.x);
            fatalCtx.aarch64_ctx.afsr0 = ctxBackup.afsr0;
            fatalCtx.aarch64_ctx.afsr1 = ctxBackup.afsr1;
            fatalCtx.aarch64_ctx.esr = ctxBackup.esr;
            fatalCtx.aarch64_ctx.far = ctxBackup.far.x;
            fatalCtx.aarch64_ctx.register_set_flags = 0xFFFFFFFF;
            fatalCtx.aarch64_ctx.pstate = ctxBackup.pstate;
            
            fatalThrowWithContext(MAKERESULT(337, 4), FatalPolicy_ErrorScreen, &fatalCtx);
            while (true)
                // 20ms svcSleepThread(20E6);
                svcSleepThread(0xFFFFFFFFFFFFFFFF);
        }

        alreadyCrashed = true;
        std::memcpy(&ctxBackup, ctx, sizeof(ThreadExceptionDump));

        switch (ctx->error_desc) {
            case ThreadExceptionDesc_BadSVC:
                errorDesc = "Bad SVC";
                break;
            case ThreadExceptionDesc_InstructionAbort:
                errorDesc = "Instruction Abort";
                break;
            case ThreadExceptionDesc_MisalignedPC:
                errorDesc = "Misaligned Program Counter";
                break;
            case ThreadExceptionDesc_MisalignedSP:
                errorDesc = "Misaligned Stack Pointer";
                break;
            case ThreadExceptionDesc_SError:
                errorDesc = "SError";
                break;
            case ThreadExceptionDesc_Trap:
                errorDesc = "SIGTRAP";
                break;
            case ThreadExceptionDesc_Other:
                errorDesc = "Segmentation Fault";
                break;
            default:
                errorDesc = "Unknown Exception [ 0x" + ExceptionHandler::toHexString<u16>(ctx->error_desc) + " ]";
                break;
        }

        brls::Application::giveFocus(nullptr);
        brls::fatal(Utilities::format_string(
            "%s\n\n%s: %s\nPC: BASE + 0x%016lx",
            "A fatal exception occured!",
            "Reason",
            errorDesc.c_str(),
            ctx->pc.x - ExceptionHandler::getHomebrewBaseAddress())
        );
        ExceptionHandler::PrintInfo(ctx);

        appletRequestExitToSelf();
    }
}
