/**
 * @file main.c
 * @author Alejandro Mejia (alejandro.mejia@groupe-arcom.com)
 * @brief 
 * @version 0.1
 * @date 27-09-2020
 * 
 * @copyright Copyright Arcom 2020
 * 
 */
#include <time.h>
#include <pthread.h>
#include <stdio.h>
#include <ctype.h>
#include <arpa/inet.h> //inet_addr
#include <net/if.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <unistd.h> /* close */
#include <string.h>
#include <stdbool.h>
#include <signal.h>

#include "Fifo.h"
#include "Osal.h"

#define  MYSIGNAL 47

static  File MaFile;
static bool taskRunning = true;

void sig_handler(int signo)
{
  if (signo == MYSIGNAL ){
    printf("received MYSIGNAL [47]  \r\n");
    taskRunning = false;
  }
}

void task_1_app(int taskIndex){
	unsigned int cpt_task_1 = 0;
	while(1){
		sleep(1);
		printf("compteur task 1 = %i\r\n",cpt_task_1);
		cpt_task_1 ++;
		if(cpt_task_1 == 10){
			enfiler(MaFile,1000);
		}
	}

}

void task_2_app(int taskIndex){
	unsigned int cpt_task_2 = 0;
	while(1){
		sleep(2);
		printf("task 2 = %i\r\n",cpt_task_2);
		cpt_task_2 ++;
		if(longueur(MaFile)!=0){
			printf("*********************************************\r\n");
			cpt_task_2 = defilement(MaFile);
		}

	}

}

int main(int argc, char* argv[])
{
	OsalHandle task_1_Handle;
	OsalTaskId task_1_Id;

	OsalHandle task_2_Handle;
	OsalTaskId task_2_Id;

	MaFile = fileVide();

	if (signal(MYSIGNAL, sig_handler)){
		  printf("ERROR:can't catch SIGINT\r\n");
	}

	if ((OsalCreateTask(task_1_app, 0 /* Not used */, 64*1024, 11, &task_1_Handle, &task_1_Id) == OSALSTS_SUCCESS)
			&&(OsalCreateTask(task_2_app, 0 /* Not used */, 64*1024, 11, &task_2_Handle, &task_2_Id) == OSALSTS_SUCCESS))
	{
		while (taskRunning)
		{
			OsalSleep(10);
		}
		OsalCloseTaskHandle(task_1_Handle);
		OsalCloseTaskHandle(task_2_Handle);
	}
	return(0);
}


#if 0
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include "zmq.h"
#include "zhelpers.h"
/* Global variables -------------------------------------------*/

/* Private defines --------------------------------------------*/

/* Private typedef --------------------------------------------*/

/* Private macros ---------------------------------------------*/

/* Private variables ------------------------------------------*/

/* Private function prototype ---------------------------------*/


int main (int argc, char * argv[])
{
    void *context = zmq_ctx_new ();
    void *publisher = zmq_socket (context, ZMQ_PUB);
    int rc = zmq_bind (publisher, "tcp://*:5556");
    assert (rc == 0);
    //  Socket to talk to clients
    srandom ((unsigned) time (NULL));
    while (1) {
        //  Get values that will fool the boss
        int zipcode, temperature, relhumidity;
        zipcode     = randof (100000);
        temperature = randof (215) - 80;
        relhumidity = randof (50) + 10;

        //  Send message to all subscribers
        char update [20];
        sprintf (update, "%05d %d %d", zipcode, temperature, relhumidity);
        s_send (publisher, update);
    }
    zmq_close (publisher);
    zmq_ctx_destroy (context);
    return 0;
}

#endif