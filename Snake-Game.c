#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
// #include<random>



struct snakeList
{
  int x,y;
  struct snakeList *next;
};

typedef struct snakeList snake;

int main()
{
  

  int height=28,width=120,currentLength=5;
  int tempX=1,tempY=1,appleX=1,appleY=1;
  int score,ateItself=0,speed=120;
  // speed range = (1,199)
  speed=200-speed;
  score=currentLength;

  char input='l',tempInput='l',prevInput='l';

  snake *tail,*current,*temp,*head;

  for(int i=1;i<=height;i++)
  {
    printf("\033[%d;%dH|",i,width);
  }
  for(int i=1;i<=width;i++)
  {
    printf("\033[%d;%dH-",height,i);
  }
  // printf("\033[%d;%dHL",height+1,width+1);

  tail=(snake*)malloc(sizeof(snake));

  current=tail;

  for(int i=1;i<=currentLength;i++)
  {
    current->x=i;
    current->y=1;
    if(i==currentLength)
    {
      current->next=NULL;
    }else{
      current->next=(snake*)malloc(sizeof(snake));
      head=current->next;
    }
    current = current->next;
  }

  srand(time(NULL));
  appleX=1+rand()%(width-1);
  appleY=1+rand()%(height-1);
  printf("\033[%d;%dH@",appleY,appleX);
  

  while(1)
  {
    current=tail;
    while(current!=NULL)
    {
      printf("\033[%d;%dH*",current->y,current->x);
      current=current->next;
    }

    if(head->x==appleX && head->y==appleY)
    {
      srand(time(NULL));
      appleX=1+rand()%(width-1);
      appleY=1+rand()%(height-1);
      printf("\033[%d;%dH@",appleY,appleX);
      temp=tail;
      tail=(snake*)malloc(sizeof(snake));
      tail->next=temp;
      tail->x=0;
      tail->y=0;

      // switch(input)
      // {
      //   case 'j':
      //     current->x=(current->x-1+width)%width;
          
      //     break;

      //   case 'k':
      //     current->y=(current->y+1)%height;
      //     break;

      //   case 'l':
      //     current->x=(current->x+1)%width;
      //     break;

      //   case 'i':
      //     current->y=(current->y-1+height)%height;
      //     break;
        
      //   default:
      //     break;
      // }
      currentLength++;
      score++;
    }

    printf("\033[%d;%dH%d",height,width,score);
    
    if(kbhit())
    {
      tempInput=getch();
    }
    if(tempInput=='l' || tempInput=='j' || tempInput=='i' || tempInput=='k' || tempInput==';')
    {
      if(!(tempInput=='l' && prevInput=='j') && !(tempInput=='j' && prevInput=='l') && !(tempInput=='i' && prevInput=='k') && !(tempInput=='k' && prevInput=='i'))
      {
        prevInput=input;
        input=tempInput;
      }
    }

    if(input=='l' || input=='j')
    {
      Sleep(speed);
    }else{
      Sleep(speed*2);
    }
    
    
    printf("\033[%d;%dH%d",height,width,score);
    // system("cls");

    current=tail;
    while(current!=NULL)
    {
      printf("\033[%d;%dH ",current->y,current->x);
      current=current->next;
    }
    
    current=tail;
    while(current->next!=NULL)
    {
      current->x=current->next->x;
      current->y=current->next->y;
      current=current->next;
    }
    switch(input)
    {
      case 'j':
        current->x=(current->x-1+width)%width;
        
        break;

      case 'k':
        current->y=(current->y+1)%height;
        break;

      case 'l':
        current->x=(current->x+1)%width;
        break;

      case 'i':
        current->y=(current->y-1+height)%height;
        break;
      
      default:
        break;
    }
    current=tail;
    while(current!=NULL && current!=head)
    {
      if(head->x==current->x && head->y==current->y)
      {
        ateItself=1;
        break;
      }
      current=current->next;
    }
    if(ateItself==1)
    {
      printf("\033[%d;%dHU just ate urself XD",height,width);
      break;
    }

  }
  getch();
  return 0;

}