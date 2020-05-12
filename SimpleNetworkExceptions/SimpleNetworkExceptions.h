#pragma once
#include <string>  
#include <functional>
#include <WS2tcpip.h>

struct WinSockException : public std::exception
{
public:

    WinSockException(const std::string& msg) : msg{ msg }
    {
        WSACleanup();
    }

    const char* what() const throw ()
    {
        std::string s{ msg + " ERR #" + std::to_string(WSAGetLastError()) };
        return s.c_str();
    }

private:
    const std::string msg;
};


struct SocketException : WinSockException
{
public:

    SocketException(SOCKET socket, const std::string& msg) : WinSockException{ msg }
    {
        closesocket(socket);
    }
};