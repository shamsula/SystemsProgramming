#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#define BUF_SIZE 8000

//Mohammed Shamsul Arefeen, 104707638
int main( int argc, char* argv[] ) {
	//printf("hello\n");

	int input_fd, output_fd,i;
    ssize_t ret_in, ret_out;
    char buffer[9000],buffer1[9000],cuddle[100],cuddle1[100];
    FILE *fp;
    int nbLines=512,nbCols=512;
    int lines,cols;

    if(argc != 2){
        printf ("enter the image to be edited as a parameter");
        return 1;
    }

    input_fd = open(argv [1],O_RDWR);
    if(input_fd == -1) {
            perror("open");
            return 2;
    }
    //printf("haha lool %d %d\n",lines,cols);

    if((fp=fdopen(input_fd,"r"))==0)
        printf("file opening failed");

    fgets(buffer,20,fp); //get P5
    fgets(buffer,20,fp);
    sscanf(buffer,"%s %s",cuddle,cuddle1);
   // printf("haha scan %s %s \n",cuddle,cuddle1);

       int cud=0,cud1=0;
        for(i=0;cuddle[i]!='\0';i++) {
            if(cuddle[i]>=48 && cuddle[i]<=57)
                cud=cud*10+(cuddle[i]-48);
        }

         for(i=0;cuddle1[i]!='\0';i++) {
            if(cuddle1[i]>=48 && cuddle1[i]<=57)
                cud1=cud1*10+(cuddle1[i]-48);
         }


    //int cud = atoi(cuddle);
    //int cud1 =atoi (cuddle1);
   // printf("haha scan %d %d \n",cud,cud1);
    nbLines=cud;
    nbCols=cud1;

    fgets(buffer,10,fp);//get 255
    int cutoff=ftell(fp);
    //printf("we are at position %d\n",cutoff);


    /* Create output file descriptor */

    /* Copy process */
   for(i=0l; i<(nbLines/2);i++){
    lseek(input_fd,cutoff+(i*nbCols),SEEK_SET);
    read(input_fd,buffer,nbCols);
    //printf("this is what was read %s\n",buffer);

    lseek(input_fd,-((i+1)*nbCols),SEEK_END);
    read(input_fd,buffer1,nbCols);

    lseek(input_fd,cutoff+(i*nbCols),SEEK_SET);
    write(input_fd,buffer1,nbCols);

    lseek(input_fd,-((i+1)*nbCols),SEEK_END);
    write(input_fd,buffer,nbCols);







   }

   /*
    while((ret_in = read (input_fd, &buffer, BUF_SIZE)) > 0){
            ret_out = write (output_fd, &buffer, (ssize_t) ret_in);
            if(ret_out != ret_in){
                /* Write error
                perror("write");
                return 4;
            }
    } */ //this section for just reading

   // /* Close file descriptors */
    fclose (fp);
    //close (output_fd);
//printf("haha end \n");
    return 0;
}
