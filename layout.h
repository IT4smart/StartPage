#ifndef layout_h
#define layout_h


//vars
	//distance
	//int dist;			 //minimum 1; distance between little boxes

	int left;			//all buttons are in column left
	int mid;			//all buttons are in column mid
	int right;			//all buttons are in column right
	int image_height;			//is for the number of cells one image inherits
	int image_width;			//is for the number of cells one image inherits

	//login
	int login;
	int login_height;
	int login_width;

	//network
	int network;
	int ip;
	int netmask;
	int gateway;
	int type;
	int network_height;		//the number of columns incl frametitle
	int network_width;


	//quit
	int quit;




//funtions
	static void set_headline();
	static void set_footline();
	static void set_layout_order();
	static void set_login();
	static void set_network();

#endif
