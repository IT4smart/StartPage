//execute with:
//sudo apt-get install libgtk-3-dev
//gcc andi.c $(pkg-config --cflags --libs gtk+-3.0) -o andi.out -Wall -Wextra
//
//start with 
//andi.out >> log
//for logpreparations 
//
//
//image IT4S_small.png must be small enough, 
//because there is no working possibility, of smallen it

//wlan:
//at first activate wlan with right ssid and pw
//and then plug in the wlan stick
//the other hand around is not possible
//then press change wlan to get the new ip, gateway, netmask




#include <gtk/gtk.h>
#include <string.h>		//strlen, strcat, strcpy
//#include <unistd.h> 		//for the exec
#include <stdlib.h> 		//for system()
#include <stdbool.h> 		//for bools
#include <time.h>	//for time
#include "vars.h"
#include "func.h"



//get the local time
char* get_time() {
	time_t now;
	struct tm *now_tm;
	time (&now); //get time
	now_tm = localtime (&now);
	sprintf(time_str, "%02d:%02d:%02d", now_tm->tm_hour, now_tm->tm_min, now_tm->tm_sec);
 	return time_str;
}

gboolean repaint_time(){
	//printf("repaint");
	//gtk_label_set_text(GTK_LABEL(label_time), get_time());
	get_time();
	char temp[MAX_BUFFER];
	sprintf(temp, "<span font_desc=\"20.0\">%s\n</span>", time_str);
	gtk_label_set_markup(GTK_LABEL(label_time), temp);
	return TRUE;
}



// remove linefeed
void remove_lf(char *str) {
   size_t p = strlen(str);
   str[p-1] = '\0';   // '\n' mit '\0' überschreiben
}


// replace a string with another
char *replace_str(char *str, char *orig, char *rep) {
  static char buffer[4096];
  char *p;

  if(!(p = strstr(str, orig)))  // Is 'orig' even in 'str'?
    return str;

  strncpy(buffer, str, p-str); // Copy characters from 'str' start to 'orig' st$
  buffer[p-str] = '\0';

  sprintf(buffer+(p-str), "%s%s", rep, p+strlen(orig));

  return buffer;
}

void rdp_login() {
	printf("%s", "starting rdp...\n");
	char rdp_launch[MAX_BUFFER] = "";

	// read data from config-file into buffer
	char* buffer_ctxrdp_rdp_bin = (char*) configuration_output(STR(CTXRDP_RDP_BIN));
	char* buffer_ctxrdp_rdp_link = (char*) configuration_output(STR(CTXRDP_RDP_LINK));
	char* buffer_ctxrdp_rdp_domain = (char*) configuration_output(STR(CTXRDP_RDP_DOMAIN));	

	// run rdp
	strcat(rdp_launch, buffer_ctxrdp_rdp_bin);
	strcat(rdp_launch, " -d ");
	strcat(rdp_launch, buffer_ctxrdp_rdp_domain);
	strcat(rdp_launch, " -f ");
	strcat(rdp_launch, buffer_ctxrdp_rdp_link);
	fp = popen(rdp_launch, "r");
  	if (fp == NULL) {
    		printf("Failed to run command\n" );
    		exit(1);
  	}
}


void citrix_login() {
	printf("starting ctx ...\n");	

	printf("killing all running processes of citrix...\n");
	system("killall storebrowse AuthManagerDaemon ServiceRecord");

	// try to add the store.	
	FILE *fp;

  	/* Open the command for reading. */
	// declare some variables
	char ctx_launch[MAX_BUFFER] = "";
	char ctx_launch2[MAX_BUFFER] = "";
	char buffer[MAX_BUFFER];
	char* buffer_ctxrdp_ctx_bin = NULL;
	char* buffer_ctxrdp_ctx_link = NULL;
	
	strcpy(buffer, configuration_output(STR(CTXRDP_CTX_BIN)));
	buffer_ctxrdp_ctx_bin = (char *)malloc(strlen(buffer)+1);
	printf("%p\n", buffer_ctxrdp_ctx_bin);
	strcpy(buffer_ctxrdp_ctx_bin, buffer);
	printf("%p\n", buffer_ctxrdp_ctx_bin);

	strcpy(buffer, configuration_output(STR(CTXRDP_CTX_LINK)));
	buffer_ctxrdp_ctx_link = (char *)malloc(strlen(buffer)+1);
	strcpy(buffer_ctxrdp_ctx_link, buffer);
	printf("%p\n", buffer_ctxrdp_ctx_link);
	
	// debugging
	printf("ctx bin: %s\n", buffer_ctxrdp_ctx_bin);
	printf("ctx link: %s\n", buffer_ctxrdp_ctx_link);

	
	strcat(ctx_launch, buffer_ctxrdp_ctx_bin);
	strcat(ctx_launch, " -a ");
	strcat(ctx_launch, buffer_ctxrdp_ctx_link);

	fp = popen(ctx_launch, "r");
  	if (fp == NULL) {
    		printf("Failed to run command\n" );
    		exit(1);
  	}
	
	/* Read the output a line at a time - output it. */
  	char path[MAX_BUFFER] = "";
  	while (fgets(path, sizeof(path)-1, fp) != NULL) {
    		printf("%s", path);
  	}
	remove_lf(path); // entferne linefeed

  	/* close */
  	pclose(fp);

	// find all the desktops
	char ctx_find[MAX_BUFFER] = "";
	strcat(ctx_find, buffer_ctxrdp_ctx_bin);
	strcat(ctx_find, " -E ");
	strcat(ctx_find, path);
	strcat(ctx_find, " -i best > settings_from_store");
	system(ctx_find);

	// launch the desktop if only one exists
	char *desktop;
	FILE *pipe;
	//char buffer[MAX_BUFFER];

	pipe = popen("awk -F\"\\'\" '{print $2}' settings_from_store", "r");
	if (NULL == pipe) {
   		perror("pipe");
    		exit(1);
	} 
	fgets(buffer, sizeof(buffer), pipe);
	desktop = buffer;
	remove_lf(desktop);
	printf("%s\n", desktop);	
	pclose(pipe);  

	//char ctx_launch2[MAX_BUFFER] = "";
	desktop = replace_str(desktop, "$", "\\$"); // replace $ with \$
	strcat(ctx_launch2, buffer_ctxrdp_ctx_bin);
	strcat(ctx_launch2, " -L \"");
	strcat(ctx_launch2, desktop);
	strcat(ctx_launch2, "\" ");
	strcat(ctx_launch2, path);

  	/* Open the command for reading. */
  	fp = popen(ctx_launch2, "r");
  	if (fp == NULL) {
    		printf("Failed to run command\n" );
    		exit(1);
  	}
	
	/* Read the output a line at a time - output it. */
	char do_output[MAX_BUFFER];
  	while (fgets(do_output, sizeof(path)-1, fp) != NULL) {
    		printf("%s", do_output);

		if (strstr(do_output, "Error"))
		{
			printf("Error with launching Session");
		}
  	}

  	/* close */
  	pclose(fp);
	
	// free the allocated space
	free(buffer_ctxrdp_ctx_bin);
	free(buffer_ctxrdp_ctx_link);
	//return;
}









//function analyse_input
//analyses the stream of a command
void analyse_input(FILE *fp, char file_type[MAX_BUFFER]) {
	char file_type_size[MAX_BUFFER];
	if (fp == NULL) {
		printf("Failed to run command\n" );
		//exit -1;
	}
	while (fgets(file_type, sizeof(file_type_size), fp) != NULL) {
		//printf("%s", file_type);
	}
	strtok(file_type, "\n");
}



//function 
//input: parameter for the configuration_page
//output: return string of the configuration_page
char* configuration_output(char *get_info) {
	//the command will be prepared	
	char* info_request	= get_info;
	int size_request	= strlen(info_request);
				//g_print("size %d\n", size);
	char config_path[]	= STR(CONFIGURATION);
	int size_config_path	= strlen(config_path);
	int size		= size_request + size_config_path + 3;// +3 for ' &'
	char config_command[size];
	strcpy (config_command, config_path);
	strcat (config_command, " ");
	strcat (config_command, info_request);

	const char* comment	= config_command;
	//get back the output of what is wanted to be tested
				//printf("comment: %s\n\n", comment);
	
	fp = popen(comment, "r");
	//store the output
	analyse_input(fp, configuration_output_return);
				//g_print("output %s", configuration_output_return);
				//gtk_entry_set_text(GTK_ENTRY(entry_network_ip), file_type);
	pclose(fp);
				printf("in config_output: %s\n", configuration_output_return);

	return configuration_output_return;
}

/*
//function test for existing wlan0 module 
bool test_for_wlan_module() {
	//test for wlan-module
	char file_type_wlan[MAX_BUFFER];
	fp = popen("ifconfig |grep wlan0 | awk '{print $1}'", "r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
		//exit -1;
	}
	while (fgets(file_type_wlan, sizeof(file_type_wlan), fp) != NULL) {
		printf("%s", file_type_wlan);
	}
	pclose(fp);
	strtok(file_type_wlan, "\n");
	if (strcmp(file_type_wlan, "wlan0") == 0) {
		return TRUE;
	}
	return FALSE;
}
*/





//function quit_window
void quit_window () {
	gtk_widget_destroy(window);
//	system("xbindkeys");
}






void activate (GtkApplication *app) {
// create a new window, and set its title
window = gtk_application_window_new (app);
gtk_window_set_title (GTK_WINDOW (window), "Start Page");
gtk_container_set_border_width (GTK_CONTAINER (window), 10);
g_signal_connect (G_OBJECT (window), "delete_event", 
		G_CALLBACK(quit_window), NULL);
gtk_window_set_keep_above(GTK_WINDOW(window),TRUE);




//create grid
grid = gtk_grid_new();
gtk_container_add (GTK_CONTAINER (window), grid); 


//init.c
init();

//layout.c
set_layout();






//neu
}
int main (int argc, char **argv) {

gtk_init(&argc, &argv);

window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

gtk_window_set_title (GTK_WINDOW (window), "Start Page");

gtk_container_set_border_width (GTK_CONTAINER (window), 10);
g_signal_connect (G_OBJECT (window), "delete_event", 
		G_CALLBACK(quit_window), NULL);
gtk_window_set_keep_above(GTK_WINDOW(window),TRUE);

grid = gtk_grid_new();
gtk_container_add (GTK_CONTAINER (window), grid); 


//init.c
init();

//layout.c
set_layout();

gtk_widget_show_all (window);

g_timeout_add (1000,  repaint_time, NULL);
gtk_main();



return 0;
}

/* 
// show all widgets
gtk_widget_show_all (window);

}

int main (int argc, char **argv) {
	GtkApplication *app;
	int status;

	app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);
	
	//every 1000ms the time will be redrawn
	g_timeout_add (1000,  repaint_time, NULL);
	
	gtk_main();
	return status;
}

*/
