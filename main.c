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




void rdp_login() {

}


void citrix_login() {

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
				//printf("in config_outout: %s\n", configuration_output_return);
	return configuration_output_return;
}


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






//function quit_window
void quit_window () {
	gtk_widget_destroy(window);
//	system("xbindkeys");
}






void activate (GtkApplication *app) {
// create a new window, and set its title
window = gtk_application_window_new (app);
gtk_window_set_title (GTK_WINDOW (window), "Configuration Page");
gtk_container_set_border_width (GTK_CONTAINER (window), 10);
g_signal_connect (G_OBJECT (window), "delete_event", 
		G_CALLBACK(quit_window), NULL);
gtk_window_set_keep_above(GTK_WINDOW(window),TRUE);



//deactivate xbindkeys
//system("killall xbindkeys");
	//execl ("/usr/bin/firefox", "", "firefox",  NULL);



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

gtk_window_set_title (GTK_WINDOW (window), "Configuration Page");

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
