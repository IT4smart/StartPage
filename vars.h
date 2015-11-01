
#ifndef vars_h
#define vars_h

#define MAX_BUFFER 255							//this is the buffer for all popen output streams

//test
/*
#define PATH /home/andreas/Dokumente/my_it4s/gtk/configuration/settings	//the path to the file of the configuration
#define IMAGE_PATH /home/andreas/Dokumente/my_it4s/gtk/startpage	//the path to the image_file
#define CITRIX_PATH /home/andreas/link_citrix 				//the path to the url of the citrix url
*/

// rapha test
#define PATH /home/test/IT4S/ConfigurationPage/settings
#define IMAGE_PATH /home/test/IT4S/StartPage
#define CITRIX_PATH /home/test/IT4S/link_citrix

#define CONFIGURATION /home/test/IT4S/ConfigurationPage/configuration //the path to the configurationfile
//set of Input for the configuration_page
//#define GET_LOGIN 	"get login"
//#define GET_IP 		"get ip"
//#define GET_NETMASK 	"get netmask"
//#define GET_GATEWAY 	"get gateway"
//#define GET_TYPE	"get type"

// config content
#define NET_TYPE NET_TYPE
#define NET_IP NET_IP	
#define NET_NETMASK NET_NETMASK
#define NET_GATEWAY NET_GATEWAY
#define CTXRDP_TYPE CTXRDP_TYPE
#define CTXRDP_CTX_LINK CTXRDP_CTX_LINK
#define CTXRDP_RDP_LINK CTXRDP_RDP_LINK
#define CTXRDP_RDP_DOMAIN CTXRDP_RDP_DOMAIN
#define CTXRDP_RDP_BIN CTXRDP_RDP_BIN
//set of possible outputs of the configuration_page for the Login-demand 
//config answers
#define RDP_ANSWER RDP


//pi
/*
#define PATH /home/pi/gtk/configuration/settings			//the path to the file of the configuration
#define IMAGE_PATH /home/pi/gtk/startpage				//the path to the image_file
#define CITRIX_PATH /home/pi/link_citrix				//the path to the url of the citrix url
*/


GtkWidget *window;
GtkWidget *grid;
//GtkWidget *emtpy_row;//empty row in the grid


//header
GtkWidget *label_headline;
GtkWidget *image_it4s;
GtkWidget *image_customer;


//frame
GtkWidget *frame_network;
GtkWidget *frame_wlan;
GtkWidget *frame_citrix;


//empty_row		in the grid
GtkWidget *empty_row_login;
GtkWidget *empty_row_login_back;	//back is under the section
GtkWidget *empty_row_network;
GtkWidget *empty_row_network_back;	//back is under the section

//label network
GtkWidget *label_network;
GtkWidget *label_network_ip;
GtkWidget *label_network_netmask;
GtkWidget *label_network_gateway;
GtkWidget *label_network_type;
GtkWidget *label_button_network;			//for mnemonic useage

//login
GtkWidget *label_login;
GtkWidget *label_button_login;
GtkWidget *label_rdp_username;
GtkWidget *label_rdp_pwd;
GtkWidget *entry_rdp_username;
GtkWidget *entry_rdp_pwd;


//label status
GtkWidget *label_status;

//label quit button
GtkWidget *label_button_quit;				//for mnemonic useage
GtkWidget *label_button_login;			






//time
GtkWidget *label_time;


//label_output network
GtkWidget *label_out_network_ip;
GtkWidget *label_out_network_netmask;
GtkWidget *label_out_network_gateway;
GtkWidget *label_out_network_type;




//buttons
GtkWidget *button_login;
GtkWidget *button_network;


GtkWidget *button_quit;

//files
FILE *fp;                          // pointer to stdin/out file pipe
FILE *file_network;			//for storage of the information entries
FILE *file_wlan;	
FILE *file_wlan_savings;		//only for the login information
FILE *file_citrix;
FILE *file_interfaces;

char configuration_output_return[MAX_BUFFER];
char time_str[MAX_BUFFER];


#endif
