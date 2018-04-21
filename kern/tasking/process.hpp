/*
process.hpp

Copyright (c) 05 Yann BOUCHER (yann)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/
#ifndef PROCESS_HPP
#define PROCESS_HPP

#include "config.hpp"

#include <string.hpp>
#include <vector.hpp>

#include "mem/memmap.hpp"

#include "fdinfo.hpp"

#include "utils/gsl/gsl_span.hpp"
#include "utils/noncopyable.hpp"

#include <sys/types.h>
#include <signal.h>

struct ProcessCreatedEvent
{
    pid_t pid;
};

struct ProcessDestroyedEvent
{
    pid_t pid;
    int err_code;
};

class SharedMemorySegment;
struct ProcessArchContext;
struct ProcessData;

class Process : NonCopyable
{
public:

    enum AccessRequestPerm : uint16_t
    {
        ReadRequest,
        WriteRequest,
        ExecRequest
    };

    static constexpr size_t root_uid = 0;
    static constexpr size_t user_stack_top = KERNEL_VIRTUAL_BASE - (1*Memory::page_size()) - sizeof(uintptr_t);
    static constexpr std::array<uintptr_t, 64> default_sighandler_actions
    {{
        SIG_ACTION_TERM, // 0
        SIG_ACTION_TERM, // SIGHUP
        SIG_ACTION_TERM, // SIGINT
        SIG_ACTION_CORE, // SIGQUIT
        SIG_ACTION_CORE, // SIGILL
        SIG_ACTION_CORE, // SIGABRT
        SIG_ACTION_CORE, // SIGFPE
        SIG_ACTION_TERM, // SIGKILL
        SIG_ACTION_CORE, // SIGSEGV
        SIG_ACTION_TERM, // SIGPIPE
        SIG_ACTION_TERM, // SIGALRM
        SIG_ACTION_TERM, // SIGTERM
        SIG_ACTION_TERM, // SIGUSR1
        SIG_ACTION_TERM, // SIGUSR2
        SIG_ACTION_IGN , // SIGCHLD
        SIG_ACTION_CONT, // SIGCONT
        SIG_ACTION_STOP, // SIGSTOP
        SIG_ACTION_STOP, // SIGTSTP
        SIG_ACTION_STOP, // SIGTTIN
        SIG_ACTION_STOP  // SIGTTOU
        // The rest is filled with zeroes which are equal to SIG_ACTION_TERM
    }};

public:
    static bool enabled();

    static Process* create(const std::vector<std::string> &args);
    static Process* clone(Process& proc, uint32_t flags = 0);
    static Process& current();
    static size_t   count();
    static void     kill(pid_t pid, int err_code);
    static Process* by_pid(pid_t pid);
    static std::vector<pid_t> process_list();

    static bool check_args_size(const std::vector<std::string> &args);

public:
    Process& operator=(Process&&) noexcept = default;
    Process(Process&& other) noexcept = default;

    ~Process();

    void reset(gsl::span<const uint8_t> code_to_copy, size_t allocated_size = 0);
    void set_instruction_pointer(unsigned int value);

    void set_args(const std::vector<std::string> &args);

    size_t add_fd(const tasking::FDInfo& info);
    tasking::FDInfo *get_fd(size_t fd);
    void close_fd(size_t fd);

    bool is_waiting() const;
    void wait_for(pid_t pid, int* wstatus);

    void switch_to();
    void unswitch();

    bool check_perms(uint16_t perms, uint16_t tgt_uid, uint16_t tgt_gid, uint16_t type);

    uintptr_t allocate_pages(size_t pages);
    bool      release_pages(uintptr_t ptr, size_t pages);

private:
    Process();

public:
    pid_t pid { 0 };
    pid_t tgid { 0 };
    pid_t parent { 0 };
    std::unique_ptr<ProcessData> data;
    ProcessArchContext* arch_context { nullptr };

private:
    static pid_t find_free_pid();

private:
    void arch_init(gsl::span<const uint8_t> code_to_copy, size_t allocated_size);
    void init_default_fds();
    void init_sig_handlers();

    void map_code();
    void map_stack();
#ifdef LUDOS_HAS_SHM
    void map_shm();
#endif

    void create_mappings();
    void release_mappings();

    void map_address_space();
    void unmap_address_space();

    void cleanup();
    void wake_up(pid_t child, int err_code);
    void copy_allocated_pages(Process& target);

private:
    static inline Process* m_current_process { nullptr };
    static inline std::vector<std::unique_ptr<Process>> m_processes;
    static inline size_t m_process_count { 0 };
};

extern "C" void test_task();

#endif // PROCESS_HPP
