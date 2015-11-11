#include <gtk/gtk.h>
#include <stdbool.h> //for bools
#include "vars.h"
#include "func.h"
#include "init.h"



void init() {
	init_header();
	init_label();
	init_entry();
	init_login();
	init_clock();
	init_button();
	init_frame();
	init_empty_row();
	init_button_functionality();
}


static void init_header() {
	//header
	label_headline = gtk_label_new("");
	gtk_label_set_markup(GTK_LABEL(label_headline), "<span font_desc=\"20.0\">Anmeldebildschirm\n</span>");

	//worked but to big
	image_it4s 		= gtk_image_new();
	gtk_image_set_from_file(GTK_IMAGE (image_it4s), STR(IMAGE_PATH/IT4S_low.png));
	image_customer 		= gtk_image_new();
	gtk_image_set_from_file(GTK_IMAGE (image_customer), STR(IMAGE_PATH/customer.png));

	//int size  = gtk_image_get_pixel_size (GTK_IMAGE (image_it4s));
	//gtk_image_set_pixel_size(GTK_IMAGE (image_it4s), 10);
}


static void init_empty_row() {
	empty_row_login		= gtk_label_new("");
	empty_row_login_back	= gtk_label_new("");
	empty_row_network	= gtk_label_new("");
	empty_row_network_back	= gtk_label_new("");
}


static void init_label() {
	//network
	label_network		= gtk_label_new("Network");
	label_network_ip	= gtk_label_new("Local IP:");
	label_network_netmask	= gtk_label_new("Netmask:");
	label_network_gateway	= gtk_label_new("Gateway:");
	label_network_type	= gtk_label_new("Typ:");

	//status
	label_status		= gtk_label_new("");


}


static void init_entry() {
	//network
	label_out_network_ip		= gtk_label_new(configuration_output(STR(NET_IP)));
	label_out_network_netmask	= gtk_label_new(configuration_output(STR(NET_NETMASK)));
	label_out_network_gateway	= gtk_label_new(configuration_output(STR(NET_GATEWAY)));
	label_out_network_type		= gtk_label_new(configuration_output(STR(NET_TYPE)));

}


static void init_login() {
	//login
	button_login		= gtk_button_new ();
	//label_button_login 	= gtk_label_new (configuration_output(GET_IP));	
	
	const char *login_type 		= configuration_output(STR(CTXRDP_TYPE));

	printf("%s\n", login_type);
	//if Remote, then label and function //after alex: only RDP 
	if (strcmp(login_type, STR(RDP_ANSWER)) == 0) {
		label_button_login 	= gtk_label_new ("Remotedesktop Login");	
		
	//hier benutzername und kennwort eingeben können		


		g_signal_connect (button_login, 		"clicked", G_CALLBACK (rdp_login), 	NULL);
	}
	else {

		label_button_login = gtk_label_new("");
		gtk_label_set_markup(GTK_LABEL(label_button_login), "<span font_desc=\"20.0\">Citrix Login\n</span>");
		gtk_container_add (GTK_CONTAINER (button_login), label_button_login);	//pair the label with its button
		//label_button_login 	= gtk_label_new ("Citrix Login");	
		g_signal_connect (button_login, 		"clicked", G_CALLBACK (citrix_login), 	NULL);
	}



	gtk_container_add (GTK_CONTAINER (button_login), label_button_login);//pair the label with its button
}

static void init_clock() {
	//time
	//label_time	= gtk_label_new(get_time());
	label_time	= gtk_label_new(" ");
	repaint_time();
}

static void init_button() {
	//quit
						//button_quit 		= gtk_button_new_with_label ("quit");
	button_quit 		= gtk_button_new();
	label_button_quit 	= gtk_label_new_with_mnemonic ("_quit");		//set mnemonic Press ALT+q to press the button
		gtk_label_set_pattern(GTK_LABEL(label_button_quit), "_");		//underline the mnemonic letter
		gtk_container_add (GTK_CONTAINER (button_quit), label_button_quit);	//pair the label with its button

}


static void init_frame() {
	//network
	frame_network		= gtk_frame_new(NULL);
	gtk_frame_set_label_widget(GTK_FRAME(frame_network), label_network);
}



static void init_button_functionality() {
	//it's important that the init of buttons is before the 
	//button functionalities, because so references for the buttons are existing

	//network
	//g_signal_connect (button_network, 		"clicked", G_CALLBACK (quit_window), 	NULL);
	//quit
	g_signal_connect_swapped (button_quit,		"clicked", G_CALLBACK (quit_window), 		NULL);
}
