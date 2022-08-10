#ifndef EVENT
#define EVENT 0
#define EVENT_IDNUM 5  //最多ID数
#define EVENT_TOUCHNUM 20  //缓冲区大小
#define EVENT_ALLID -1
#define EVENT_OTHER -2
#define EVENT_UP SDL_FINGERUP
#define EVENT_DOWN SDL_FINGERDOWN
#define EVENT_MOTION SDL_FINGERMOTION
#define EVENT_KEYDOWN SDL_KEYDOWN
#define EVENT_TEXTINPUT SDL_TEXTINPUT

typedef SDL_Event EVENT_Event;

struct s_EVENT_queue
{
  unsigned int write;
  unsigned int read;
  unsigned int n;
  unsigned int size;
  SDL_Event lastEvent;
  SDL_Event *eventArray;
};
typedef s_EVENT_queue* EVENT_Queue;

int EVENT_IDNum=0;  //活动ID数
EVENT_Queue EVENT_touch[EVENT_IDNUM];
EVENT_Queue EVENT_other;

//创建队列
EVENT_Queue EVENT_CreateQueue(int n)
{ 
  EVENT_Queue Q=(EVENT_Queue)malloc(sizeof(s_EVENT_queue));
  if(!Q)
    return NULL;
  Q->eventArray=(SDL_Event *)malloc(sizeof(SDL_Event)*n);
  if(!Q->eventArray)
  {
    free(Q);
    return NULL;
  }
  Q->n=0;
  Q->size=n;
  Q->write=0;
  Q->read=0;
  Q->lastEvent.type=SDL_FINGERUP;
  Q->lastEvent.tfinger.x=2;
  Q->lastEvent.tfinger.y=2;
  return Q;
}
//清空队列
void EVENT_MakeQueueEmpty(EVENT_Queue Q)
{
  Q->n=0;
  Q->write=0;
  Q->read=0;
}
//出队
int EVENT_OuQueue(EVENT_Queue Q,SDL_Event *pEvent)
{
  if(!Q->n)
  {
    *pEvent=Q->lastEvent;
    return 0;
  }
  unsigned int i=Q->read;
  Q->read++;
  if(Q->read==Q->size)
    Q->read=0;
  Q->n--;
  if(pEvent)
    *pEvent=Q->eventArray[i];
  return 1;
}
//入队
void EVENT_EnQueue(EVENT_Queue Q,SDL_Event event)
{
  if(Q->n==Q->size)
    EVENT_OuQueue(Q,NULL);
  Q->eventArray[Q->write]=event;
  Q->n++;
  Q->write++;
  if(Q->write==Q->size)
    Q->write=0;
  Q->lastEvent=event;
}
//事件匹配ID
int EVENT_Case(SDL_Event event)
{
  int id=-1,i;
  float diff=1000,t;
  float x1,x2,y1,y2;
  x2=event.tfinger.x;
  y2=event.tfinger.y;
  for(i=0;i<EVENT_IDNUM;i++)
  {
    if(EVENT_touch[i]->lastEvent.type==SDL_FINGERUP)
      continue;
    x1=EVENT_touch[i]->lastEvent.tfinger.x;
    y1=EVENT_touch[i]->lastEvent.tfinger.y;
    t=(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
    if(t<diff)
    {
      id=i;
      diff=t;
    }
  }
  return id;
}
//查找空闲ID
int EVENT_FreeID()
{
  for(int i=0;i<EVENT_IDNUM;i++)
    if(EVENT_touch[i]->lastEvent.type==SDL_FINGERUP)
      return i;
  return -1;
}
//处理事件
void EVENT_DisposeEvent()
{
  SDL_Event event;
  if(!EVENT_touch[0])
  {
    for(int i=0;i<EVENT_IDNUM;i++)
      EVENT_touch[i]=EVENT_CreateQueue(EVENT_TOUCHNUM);
   EVENT_other=EVENT_CreateQueue(EVENT_TOUCHNUM);
  }
  while(SDL_PollEvent(&event))
  {
    if(event.type==SDL_FINGERDOWN)
    {
      if(EVENT_IDNum<EVENT_IDNUM)
        EVENT_IDNum++;
      else
        continue;
      int i=EVENT_FreeID();
      if(i==-1)
        continue;
      EVENT_EnQueue(EVENT_touch[i],event);
    }
    else if(event.type==SDL_FINGERUP&&EVENT_IDNum)
    {
      int i=EVENT_Case(event);
      if(i==-1)
        continue;
      EVENT_EnQueue(EVENT_touch[i],event);
      EVENT_IDNum--;
    }
    else if(event.type==SDL_FINGERMOTION&&EVENT_IDNum)
    {
      int i=EVENT_Case(event);
      if(i==-1)
        continue;
      EVENT_EnQueue(EVENT_touch[i],event);
    }
    else if(event.type==SDL_KEYDOWN||event.type==SDL_TEXTINPUT)
      EVENT_EnQueue(EVENT_other,event);
  }
}
//获取指定ID的事件,非阻塞
int EVENT_Poll(int ID,SDL_Event *pEvent)
{
  EVENT_DisposeEvent();
  if(ID==EVENT_OTHER)
  {
    if(EVENT_OuQueue(EVENT_other,pEvent))
     return 1;
   else
     return 0;
  }
  else
  { if(EVENT_OuQueue(EVENT_touch[ID],pEvent))
    return 1;
  else
    return 0;
  }
}
//获取指定ID的事件,阻塞
void EVENT_Wait(int ID,SDL_Event *pEvent)
{
  EVENT_Queue Q;
  EVENT_DisposeEvent();
  while(1)
  {
    if(ID==EVENT_OTHER)
      Q=EVENT_other;
    else
      Q=EVENT_touch[ID];
    if(EVENT_OuQueue(Q,pEvent))
      break;
    else
      SDL_Delay(10);
    EVENT_DisposeEvent();
  }
}
//清空所有事件
void EVENT_Zero()
{
  SDL_Event event;
  while(SDL_PollEvent(&event));
  for(int i=0;i<EVENT_IDNUM;i++)
  {
    EVENT_touch[i]->n=0;
    EVENT_touch[i]->read=0;
    EVENT_touch[i]->write=0;
    EVENT_touch[i]->lastEvent.type=SDL_FINGERUP;
  }
  EVENT_other->n=0;
  EVENT_other->read=0;
  EVENT_other->write=0;
  EVENT_IDNum=0;
}
//清空指定ID的缓冲区
void EVENT_Empty(int ID)
{
  if(ID==EVENT_ALLID)
  {
    for(int i=0;i<EVENT_TOUCHNUM;i++)
      EVENT_MakeQueueEmpty(EVENT_touch[ID]);
    EVENT_MakeQueueEmpty(EVENT_other);
  }
  if(ID==EVENT_OTHER)
    EVENT_MakeQueueEmpty(EVENT_other);
  else
    EVENT_MakeQueueEmpty(EVENT_touch[ID]);
}
//将事件加入指定ID缓冲区
void EVENT_Push(int ID,SDL_Event event)
{
  if(ID==EVENT_OTHER)
    EVENT_EnQueue(EVENT_other,event);
  else
    EVENT_EnQueue(EVENT_touch[ID],event);
}
//获取ID数量
int EVENT_QueryIDNum()
{
  EVENT_DisposeEvent();
  return EVENT_IDNum;
}

#endif