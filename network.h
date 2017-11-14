#include <SDL/SDL_net.h>
#include <iostream>
#include <cstring>

class network{
  SDLNet_SocketSet server;
  TCPsocket connection;
  char tmp[1400];
  public:
    network(const char* ip);
    ~network();
    void send(player* p);
    void sendHit(player* p,int id);
    void recv(std::vector<player*>& players, std::vector::<paddle*> paddle, player* p, std::vector<unsigned int> f);
}
