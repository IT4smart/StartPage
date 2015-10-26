#include <gtk/gtk.h>
#include <stdbool.h> //for bools
#include "vars.h"
#include "func.h"
#include "layout.h"

void set_layout() { 
	set_layout_order();
	set_headline();
	set_login();
	set_network();
	set_footline();
}


static void set_layout_order() {
	//set optical properties
	gtk_grid_set_row_spacing (GTK_GRID (grid), 3); //set the lines between two sections
	//gtk_grid_set_column_homogeneous (GTK_GRID (grid), FALSE);


	//distance
	//int dist	=	1; //minimum 1; distance between little boxes

	image_height	=	8;
	image_width	=	3;
	left		=	0;
	mid		=	image_width;
	right 		=	3*image_width;		//all buttons are in column right

	//login
	login		=	image_height+1;
	login_height	=	8;
	login_width	=	4;

	//network
	network 	=	image_height+login_height+1;
	ip		=	1;
	netmask		=	2;
	gateway		=	3;
	type		=	4;
	network_height 	=	5;		//the number of columns incl frametitle
	network_width	=	2;


	//quit
	quit		=	25;
}


static void set_headline(){
	//gtk_grid_attach (
	//		GTK_GRID (grid), 
	//			label_headline,		0, 	0,	1, 1);
	gtk_grid_attach (
		GTK_GRID (grid), 
				image_it4s,		0, 	0,	image_width, image_height);
	gtk_grid_attach (
		GTK_GRID (grid), 
				image_customer,		2*image_width+1, 	0,	image_width, image_height);
}

static void set_login(){
	gtk_grid_attach (
		GTK_GRID (grid), 
				empty_row_login,	mid, 	login	,image_width+1, image_height+1);
	gtk_grid_attach (
		GTK_GRID (grid),		//start links, oben, breite , hoehe 
				button_login,		mid, 	login+1, login_width, login_height);
	gtk_widget_set_hexpand (button_login, TRUE);
	
//	gtk_widget_set_halign (button_login, GTK_ALIGN_START);
	gtk_widget_set_halign (button_login, GTK_ALIGN_CENTER);
	gtk_grid_attach (
		GTK_GRID (grid), 
				empty_row_login_back,		right, 	login+login_width+2, 1, 1);
}

static void set_network(){
	//network
	gtk_grid_attach (
		GTK_GRID (grid), 
				empty_row_network,	right-1, 	network	,1, 1);
	gtk_grid_attach ( 
		GTK_GRID (grid), 
				frame_network, 		right-1, 	network, 	
							network_width, network_height); 
	gtk_grid_attach (
		GTK_GRID (grid), 
				label_network_ip,	right-1, 	network+ip, 	1, 1);
	gtk_grid_attach (
		GTK_GRID (grid), 
				label_out_network_ip,	right, 	network+ip, 	1, 1);
	gtk_grid_attach (
		GTK_GRID (grid), 
				label_network_netmask,	right-1, 	network+netmask, 1, 1);
	gtk_grid_attach (
		GTK_GRID (grid), 
				label_out_network_netmask,	right, 	network+netmask, 1, 1);
	gtk_grid_attach (
		GTK_GRID (grid), 
				label_network_gateway,	right-1, 	network+gateway, 1, 1);
	gtk_grid_attach (
		GTK_GRID (grid), 
				label_out_network_gateway,	right, 	network+gateway, 1, 1);
	gtk_grid_attach (
		GTK_GRID (grid), 
				label_network_type,	right-1, 	network+type, 1, 1);
	gtk_grid_attach (
		GTK_GRID (grid), 
				label_out_network_type,	right, 	network+type, 1, 1);
	//gtk_grid_attach (
	//	GTK_GRID (grid), 
	//			button_network,		right, 	network+network_height-1, 1, 1);
	gtk_grid_attach (
		GTK_GRID (grid), 
				empty_row_network_back,		right, 	network+network_height, 3, 1);
//time
	gtk_grid_attach (
		GTK_GRID (grid), 
				label_time,	0, 	network+1, 3, 3);
}




static void set_footline() {
	//statusline
	gtk_grid_attach (
		GTK_GRID (grid), 
				label_status, 		0, quit, 		right-1, 1);
	//quit
	gtk_grid_attach (
		GTK_GRID (grid), 
				button_quit, 		right, quit, 		1, 1);
  gtk_widget_set_halign (button_login, GTK_ALIGN_FILL);	
  gtk_widget_set_halign (grid, GTK_ALIGN_FILL);	

  //rows / colums become all the same size/width
gtk_grid_set_column_homogeneous (GTK_GRID (grid), TRUE);
gtk_grid_set_row_homogeneous (GTK_GRID (grid), TRUE);
}
