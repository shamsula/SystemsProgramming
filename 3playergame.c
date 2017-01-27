// Mohammed Shamsul Arefeen

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <wait.h>
#include <fcntl.h>


void action(){};
int ReadNErase(int fd, FILE *fp);


void child(char *,int maxm, int fd);

int main(int argc, char *argv[]){
pid_t pid1, pid2,pid3; char tmp[100];
int maxPoints, fd1,score,num=0; FILE *fp1;
char fifoName1[100]="text.txt";
unlink(fifoName1);

signal(SIGINT, SIG_IGN); //stops Ctr-C
//signal(SIGTSTP, SIG_IGN); //stops Ctr-Z
 //if(mkfifo(fifoName1, 0777)){               // create common score file
   // perror("main could not create fifo");
    //exit(1);
  //}
//chmod(fifoName1, 0777);

printf("This is a 3-players game with a referee\n");
printf("Enter the winning target: ");
scanf("%d",&maxPoints); // gets input from line
fd1= open(fifoName1, O_RDWR|O_CREAT);
if(fd1==-1) printf("error creating file");
//fp1= fdopen(fd1,"r+");

if((pid1=fork()) == 0) {child("TOTO",maxPoints,fd1);}
if((pid2=fork()) == 0) {child("TITI",maxPoints,fd1);}
if((pid3=fork()) == 0) {child("TATA",maxPoints,fd1);}
//if(pid1!=0 &&pid2!=0 && pid3!=0   ) fd1= open(fifoName1, O_RDONLY);

sleep(1);
signal(SIGUSR1, action);
while(1){

printf("\nReferee: TOTO plays\n\n");  // first player plays
kill(pid1, SIGUSR1);
pause();
//if(getpid()!=pid1)printf("we are back\n");
//if(ReadNErase(fd1,fp1)>=maxPoints) printf("Referee: TOTO won!"); printf("current position is %d\n",ftell(fp1));
lseek(fd1,0,SEEK_SET);
read(fd1,tmp,5);
sscanf(tmp,"%d",&num);
if(num>=maxPoints) {printf("Referee: TOTO has won! \n");unlink("text.txt"); return 0;}




printf("\n\nReferee: TITI plays\n\n"); //second player plays
kill(pid2, SIGUSR1);
pause();
read(fd1,tmp,5);
sscanf(tmp,"%d",&num);
if(num>=maxPoints) {printf("Referee: TITI has won! \n");unlink("text.txt"); return 0;}





printf("\n\nReferee: TATA plays\n\n"); //third player added here
kill(pid3, SIGUSR1);
pause();
read(fd1,tmp,5);
sscanf(tmp,"%d",&num);
if(num>=maxPoints) {printf("Referee: TATA has won! \n");unlink("text.txt"); return 0;}

}
}

void child(char *s,int max, int fd){

int points=0; char tmp[99];
int dice;
long int ss=0;
while(1){
signal(SIGUSR1, action); // block myself
pause();
printf("%s: playing my dice\n", s);
dice =(int) time(&ss)%10 + 1;
printf("%s: got %d points\n", s, dice);
points+=dice;
printf("%s: Total so far %d\n\n", s, points);
sleep(1);


//printf("points is %d\n\n",points);
sprintf(tmp,"%d",points );
//printf("2d points is %s\n\n",tmp);
lseek(fd,0,SEEK_SET);
write(fd, tmp,5 );
//lseek(fd,0,SEEK_SET);
//read(fd,tmp,5);
//printf("what we read is %s \n\n\n",tmp);


//if(points >= max){
//printf("%s: game over I won\n", s);
//kill(0, SIGTERM);
//}
kill(getppid(), SIGUSR1);
}
}

int ReadNErase(int fd, FILE *fp){

char buff[99],tmp[100]; int num=0;


lseek(fd,0,SEEK_SET);
read(fd,tmp,5);
printf("what we read in readnerase is %s \n\n\n",tmp);


lseek(fd,0,SEEK_SET);
read(fd,buff,3);
sscanf(buff,"%d",&num);
printf("num is %s\n",buff);
return num;


}
