#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

#pragma comment (lib, "ws2_32.lib")     // for windows

#include <socket_wrapper/socket_headers.h>
#include <socket_wrapper/socket_wrapper.h>
#include <socket_wrapper/socket_class.h>

// Trim from end (in place).
static inline std::string& rtrim(std::string& s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int c) { return !std::isspace(c); }).base());
    return s;
}


int main(int argc, char const* argv[])
{
    socket_wrapper::SocketWrapper sock_wrap;
    const int port = 1230;
    
    // std::string host_name = "localhost";
    socket_wrapper::Socket sock = { AF_INET, SOCK_DGRAM, IPPROTO_UDP };

    if (!sock)
    {
        std::cerr << sock_wrap.get_last_error_string() << std::endl;
        return EXIT_FAILURE;
    }

    in_addr ip_to_num{};
    int stat = inet_pton(AF_INET, "127.0.0.1", &ip_to_num);
    if (stat <= 0)
    {
        std::cerr << sock_wrap.get_last_error_string() << std::endl;
        return EXIT_FAILURE;
    }

    sockaddr_in addr =
    {
        .sin_family = PF_INET,
        .sin_port = htons(port),
    };
    addr.sin_addr = ip_to_num;

    struct sockaddr_in serv_address = { INADDR_ANY };
    socklen_t address_len = sizeof(sockaddr_in);
    ssize_t recv_len = 0;

    std::cout << "Running client...\n" << std::endl;

    std::string message;
    char buffer[256];
    bool run = true;
    while (run)
    {
        std::getline(std::cin, message);
        sendto(sock, message.c_str(), message.size(), 0, reinterpret_cast<const sockaddr*>(&addr),
            address_len);
       
        std::cout << std::endl;
        recv_len = recvfrom(sock, buffer, sizeof(buffer) - 1, 0,
            reinterpret_cast<sockaddr*>(&addr),
            &address_len);

        if (recv_len > 0)
        {
            buffer[recv_len] = '\0';
            std::cout << buffer << '\n';
        }
        rtrim(message);
        if (message == "exit") run = false;
    }
    sock.close();
    return EXIT_SUCCESS;
}

