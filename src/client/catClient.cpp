
// Console library. Being a header only only, compiles it ONLY HERE ('OOF_IMPL').
#define OOF_IMPL
#include<oof.h>

// Network.
#include <SFML/Network.hpp>


//______________________________________________________________________________
int main(int argc, char* argv[])
{
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("192.168.0.5", 53000);

    if (status != sf::Socket::Done)
    {
        // error...
    }
}