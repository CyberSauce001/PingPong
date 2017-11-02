#include <SDL/SDL.h>
#include <SDL/SDL_net.h>
#include <iostream>
#include <vector>
#define SDL_reinterpret_cast(type, expression) reinterpret_cast<type>(expression)

//contain socket for each player and their data
struct data{
        TCPsocket socket;
        Uint32 timeout; // assume disconnection if timeout
        int id; //create an id for each player connected
        data(TCPsocket sock,Uint32 t, int i) : socket(sock),
        timeout(t), id(i) {} //set a constructor for the data of that player
};
int main (int argc, char ** argv){
        //connection
        SDL_Init(SDL_INIT_EVERYTHING);
        SDLNet_Init();
        int currID=0; //current id for unique identifier
        int playerNum=0; //current number of player in game
        SDL_Event event; //handle an event
        IPaddress ip; //IP address of server
        SDLNet_ResolveHost(&ip, NULL, 2222);//Grab IP, not connected to anything port
        std::vector<data> socketvector; // data of all player
        char tmp[2000]; // store incoming and outcoming data
        bool running = true;
        SDLNet_SocketSet sockets=SDLNet_AllocSocketSet(4);
        SDL_SetVideoMode(640,480,32,SDL_SWSURFACE);
        TCPsocket server=SDLNet_TCP_Open(&ip);

 while(running)
        {
           while(SDL_PollEvent(&event))
              if(event.type==SDL_QUIT || event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_ESCAPE)
                running=false;
            TCPsocket tmpsocket =SDLNet_TCP_Accept(server);
            if(tmpsocket)
            {
              if(playerNum<4)
              {
                SDLNet_TCP_AddSocket(sockets,tmpsocket);
                socketvector.push_back(data(tmpsocket,SDL_GetTicks(), currID));
                playerNum++;
                sprintf(tmp, "0 %d \n", currID);
                currID++;
                std::cout << "New Connection: " << currID << '\n';
              }else {
                sprintf(tmp, "Full \n");
                }
SDLNet_TCP_Send(tmpsocket,tmp, strlen(tmp)+1);
            }
            //check for incoming data
            while(SDLNet_CheckSockets(sockets,0)>0)
            {
                for(int i=0; i<socketvector.size(); i++)
                {
                  if(SDLNet_SocketReady(socketvector[i].socket))
                  {
                   socketvector[i].timeout = SDL_GetTicks();
                   SDLNet_TCP_Recv(socketvector[i].socket,tmp,2000);
                   int num=tmp[0]-'0';
                   int j=1;
                   while(tmp[j]>='0' && tmp[j] <= '9')
                   {
                     num*=10;
                     num+=tmp[j]-'0';
                     j++;

                   }
                   if(num==1)
 {
                     for(int k =0; k<socketvector.size(); k++)
                     {
                        if(k==i)
                         continue;
                        SDLNet_TCP_Send(socketvector[k].socket,tmp,strlen(tmp)+1);
                      }
                   }else if (num==2) {
                        for(int k =0; k<socketvector.size();k++)
                        {
                                if(k==i)
                                 continue;
                                SDLNet_TCP_Send(socketvector[k].socket,tmp,strlen(tmp)+1);
                        }
                        SDLNet_TCP_DelSocket(sockets,socketvector[i].socket);
                        SDLNet_TCP_Close(socketvector[i].socket);
                        socketvector.erase(socketvector.begin()+i);
                        playerNum--;
 			}else if (num == 3) {
                        int tmpvar;
			sscanf(tmp, "3 %d", &tmpvar);
                        for(int k=0;k<socketvector.size();k++)
                          if(socketvector[k].id==tmpvar)
                          {
                             SDLNet_TCP_Send(socketvector[k].socket,
                                tmp,strlen(tmp)+1);
                             break;
                          }
                    }
                }
            }
        }
        //disconnet player
        for(int j=0;j<socketvector.size();j++)
          if(SDL_GetTicks()-socketvector[j].timeout>5000)
          {
           for(int k =0; k<socketvector.size();k++)
           {
               SDLNet_TCP_Send(socketvector[k].socket,tmp,strlen(tmp)+1);
  }
               SDLNet_TCP_DelSocket(sockets,socketvector[j].socket);
               SDLNet_TCP_Close(socketvector[j].socket);
               socketvector.erase(socketvector.begin()+j);
               playerNum--;

          }
        SDL_Delay(1);
        }
        for (int i=0; i<socketvector.size();i++)
          SDLNet_TCP_Close(socketvector[i].socket);

        SDLNet_FreeSocketSet(sockets);
        SDLNet_TCP_Close(server);
        SDLNet_Quit();
        SDL_Quit();

}
