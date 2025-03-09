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
  int score,ateItself=0,changeInputThisFrame=0,slep=100;
  // speed range = (1,199)
  // speed=200-speed;
  score=currentLength;

  char input='l',tempInput='l',prevInput='l';
  char inputDisplay='>';

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
    while(current->next!=NULL)
    {
      printf("\033[%d;%dH*",current->y,current->x);
      current=current->next;
    }
    printf("\033[%d;%dH%c",current->y,current->x,inputDisplay);

    if(head->x==appleX && head->y==appleY)
    {
      srand(time(NULL));
      appleX=1+rand()%(width-2);
      appleY=1+rand()%(height-2);
      printf("\033[%d;%dH@",appleY,appleX);
      temp=tail;
      tail=(snake*)malloc(sizeof(snake));
      tail->next=temp;
      tail->x=0;
      tail->y=0;
      if (!(slep<=60))
      {
        slep-=10;
      }

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


    printf("\033[%d;%dH%c",height,width,inputDisplay);
    changeInputThisFrame=0;
    if(kbhit() && changeInputThisFrame==0)
    {
      tempInput=getch();
      changeInputThisFrame=1;
    }
    if((tempInput=='l' || tempInput=='j' || tempInput=='i' || tempInput=='k' || tempInput==';'))
    {
      if(!(tempInput=='l' && input=='j') && !(tempInput=='j' && input=='l') && !(tempInput=='i' && input=='k') && !(tempInput=='k' && input=='i'))
      {
        
        input=tempInput;
      }
    }

    if(input=='l' || input=='j')
    {
      Sleep(slep);
    }else{
      Sleep(slep*2);
    }
    
    switch(input)
    {
      case 'l':
        inputDisplay='>';
        break;
      
      case 'j':
        inputDisplay='<';
        break;
      
      case 'i':
        inputDisplay='^';
        break;
      
      case 'k':
        inputDisplay='V';
        break;
      case ';':
        inputDisplay='O';
        break;
      default:
        break;
    }
    
    printf("\033[%d;%dH%c",height,width,inputDisplay);
    // system("cls");

    printf("\033[%d;%dH@",appleY,appleX);

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
      printf("\033[%d;%dHGame Over",height/2,width/2-4);
      break;
    }
    printf("\033[%d;%dHScore : %d",height+1,1,score);
    printf("\033[%d;%dHSpeed : %d   ",height+2,1,140-slep);

  }

  printf("\033[1;1H");
  scanf("%d",&width);
  return 0;

}
