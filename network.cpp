#include "network.h"

 network::network(const char* ipchar)
 {
     SDLNet_Init();
     IPaddress ip;
     if(SDLNet_ResolveHost(&ip, ipchar, 2222)==-1)
        std::cout <<"Error Connecting" << srd::endl;
     connection = SDLNet_TCP_Open(&ip);
     if(connection == NULL)
        std::cout <<"Error Bad IP" << std::endl;
        server=SDLNet_AllocSocketSet(1);
        SDLNet_TCP_AddSocket(server,connection);
 }
 network::~network()
 {
    SDLNet_TCP_Send(connection, "2 \n", 4);
    SDLNet_TCP_Close();
    SDLNet_FreeSocketSet(server);
    SDLNet_Quit();
 }
 void network::send(player* p)
 {
    if(p->ready())
    {
      sprintf(tmp, "1 %d \n", p->getID());
      int size = 0;
      int len=strlen(tmp)+1;
      while(size<len)
      {
        size+=SDLNet_TCP_Send(connection,tmp+size,len-size);
        
 }
 void network::sendHit(player* p,int id)
{
    if(p->ready())
    {
    }
 void network::recv(std::vector<player*>& players, std::vector::<paddle*> paddle, player* p, std::vector<unsigned int> f);
