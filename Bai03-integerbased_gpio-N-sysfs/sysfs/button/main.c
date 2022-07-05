#include <stdio.h>
#include <string.h>
#include <unistd.h>
 #include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	//if (argc < 2) {
		//printf("Enter command\n");
		//return 0;
	//}

	FILE *file_connected_pipe;
	char gpio[100] = {0};
	char buffer[1024] = {0};
	char buffer1[1024] = "export";
	int count = 0;

	printf("Starting system call...\n");
	file_connected_pipe = popen("ls /sys/class/gpio/", "r");
	
	if (file_connected_pipe == NULL) {
		printf("failed to open file pipe\n");
		return 0;
	}	

	sprintf(gpio, "gpio%d", 31);
	char* check = buffer1;
	while (check != NULL) {
		memset(buffer, 0, sizeof(buffer));
		check = fgets(buffer, 1024, file_connected_pipe);
		if (count == 0) {
			printf("Data recieve from command through pipe is:\n%s", buffer);
			count++;
		} else {
			// for(int i = 0; i < sizeof(buffer); i++) {
			// 	if (buffer[i] == '\n') 
			// 		buffer[i] = 0;
			// }
			buffer[strlen(buffer) - 1] = 0;
			printf("%s", buffer);
			//printf("vlon");

			if (strcmp("gpio31", buffer) == 0) {
				printf("vlon dau cat moi\n");
			}
		}
	}
	wait(NULL);
	printf("end\n");
	pclose(file_connected_pipe);

	return 0;
}	
