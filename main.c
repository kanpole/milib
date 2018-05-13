#include"head.h"
int main(int argc,char **argv){
  int sock,ctsock;
  pid_t pid;
  int pips[2];
  FILE *fpw,fpr;
  int meglen;
  int maxfd;
  int selectlen;
  fd_set fds,cpfd;
  int epolllen;
  int epollsize;
  int epollid;
  struct epoll_event event;
  struct epoll_event* events;
  struct sockaddr_in svaddr,ctaddr;
  struct timeval timeout;
  struct iovec iov[2];
  struct ip_mreq mreq;
  struct sigaction sigactc,sigactm;
  int brocast=1;
  int nodelay=1;
  int reuseaddr=1;
  int ttl=64;
  int addrlen=sizeof(struct sockaddr_in);
  char buf[MSZIE];
  char buf1[MSIZE];
  char msg[XXSIZE];
  sigactc.sa_handler=childexit;
  sigactc.sa_flags=0;
  sigemptyset(&sigact.sa_mask);
  //...
  sigaction(SIGCHLD,&sigactc,NULL);
  sigaction(SIGURG,&sigactm,NULL);
  

  if(argc<3){puts("argc error");exit(1);}
  sock=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
  svaddr.sa_family=AF_INET;
  svaddr.sa_addr.s_addr=htonl(INADDR_ANY);
  svaddr.sa_port=htons(atoi(argv[2]));
  fcntl(sock,F_SETOWN,getpid());
  mreq.imr_interface=htonl(INADDR_ANY);
  mreq.imr_multiaddr=inet_addr(argv[1]);

  setsockopt(sock,IPPROTO_TCP,TCP_NODELAY,(void *)&nodelay,sizeof(nodelay));
  setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(void *)&reuseaddr,sizeof(reuseaddr));
  setsockopt(sock,IPPROTO_IP,IP_ADD_MEMBERSHIP,(void *)&mreq,sizeof(mreq));
  setsockopt(ctsock,IPPROTO_IP,IP_MULTICAST_TTL,(void *)ttl,sizeof(ttl));
  setsockopt(ctsock,SOL_SOCKET,SO_BROADCAST,(void *)broad,sizeof(broad));
  int flag=fcntl(sock,F_GETFL,0);
  fcntl(sock,F_SETFL,flag|O_NONBLOCK);
  int temp=dup(sock);
  fpw=fdopen(temp,"w");
  temp=dup2(sock,17);
  fpr=fdopen(temp,"r");
  pipe(pips);
  bind(sock,(struct sockaddr*)&svaddr,sizeof(svaddr));
  FD_ZERO(&fds);
  FD_SET(sock,&fds);
  maxfd=sock;
  
  iov[0].base=buf;
  iov[0].len=sizeof(buf);
  //...
  epollid=epoll_create(epollsize);
  events=malloc(sizeof(struct epoll_event)*epollsize);
  event.data.fd=sock;
  event.event=EPOLLIN|EPOLLET;
  epoll_ctl(epollid,EPOLL_CTL_ADD,sock,&event);
  epoll_ctl(epollid,EPOLL_CTL_DEL,sock,&event);
  epoll_ctl(epollid,EPOLL_CTL_MOD,sock,&event);

  epollen=epoll_wait(epollid,events,epollsize,-1);
  
  for(int i=0;i<epollen;i++){
    if(events[i].data.fd==sock)
      printf("events:%d",events[i].events);
    if(errno==EAGAIN)


  }


  while(1){
    cpfd=fds;
    timeout.tv_sec=5;
    timeout.tv_usec=0;
    selectlen=select(maxfd,&fds,NULL,NULL,&timeout);
    if(selectlen==0)continue;
    if(selectlen==-1)break;
    else{
      for(int i=0;i<selectlen+1;i++){
	if(!FD_ISSET(i,&fds)){
	  continue;

	}
	if((meglen=readv(i,&iov,2))==-1){
	  

	}else
	  shutdown(fileno(i),SHUT_WR);
	  close(i);
      }


    }
  }
  close(sock);
  return 0;
}
