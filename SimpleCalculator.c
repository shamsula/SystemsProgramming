// Mohammed Shamsul Arefeen

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


void childFunction(char * line) {

printf("I am a child working for my parent\n");

float a, b;
  char op,str[100];

int scansres = sscanf(line, "%f %c %f", &a, &op, &b);
if(scansres==-1 || scansres!=3)
exit(50);
 //printf("%f %c %f \n",a,op,b); 
if(b==0 && op =='/')
exit(100);
if(op!='+'&& op!='-'&& op!='/'&& op!='*')
exit(200); 

switch (op){
	case '+':
	  sprintf(str,"%f %c %f = %f\n\n", a, op, b, a+b);
	  break;
	case '-':
	  sprintf(str,"%f %c %f = %f\n\n", a, op, b, a-b);
	  break;
	case '*':
	  sprintf(str,"%f %c %f = %f\n\n", a, op, b, a*b);
	  break;
	case '/':
	  sprintf(str,"%f %c %f = %f\n\n", a, op, b, a/b);
	  break;
	default:
	  printf("\n Operation impossible: nonvalid operator %c passed by parent\n\n", op);
	}

write(1,str,strlen(str)); 

exit(0);


}

int main(){
  pid_t pid,waitstat;
  FILE *f;
  float a, b;
  char op, line[100],str[100];
  int status,es;

	printf("This program makes simple arithmetics\n");

while(1){

printf("Enter an arithmetic statement, e.g., 34 + 132 > ");
fgets(line, 99, stdin); // gets input from line

if(pid = fork()>0) {

printf("Created a child to make your operation, waiting\n");
waitstat= wait(&status); 

//printf(" %d %d \n",waitstat,status);
 if ( WIFEXITED(status) ) {
         es = WEXITSTATUS(status);
        //printf("Exit status was %d\n", es);
    }

if(es==50)
printf("Wrong statement\n");
else if(es==100)
printf("Division by zero\n");
else if(es==200)
printf("Wrong operator\n");


} // end of parent

else {

childFunction(line);




}







} //end of infinite loop 





}
