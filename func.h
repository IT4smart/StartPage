#ifndef func_h
#define func_h


//to expand a token to a string: STR(100)-> "100"
#define STR_EXPAND(tok) #tok
#define STR(tok) STR_EXPAND(tok)
//


//function prototypes

//layout.c
void set_layout();

//init.c
void init();

//time
char* get_time();
gboolean repaint_time();


//rdp
void rdp_login();

//citrix
void citrix_login();




//network
void click_button_network();
void default_network();
char* configuration_output(char *get_info);
void find_ip();
void find_netmask();
void find_gateway();
void change_network ();
void toggle_button_radio_network ();

//wlan
void click_button_wlan();
void default_wlan();
bool test_for_wlan_module();
void delete_configure_wlan();
void configure_wlan();
void find_wlan_savings();
void change_wlan ();
void toggle_button_check_wlan_active();


//citrix
void click_button_citrix();
void find_citrix_link();
void change_citrix ();
void restart_uzbl ();

//other
void analyse_input(FILE *fp, char file_type[MAX_BUFFER]);
bool test_for_wlan_module();
void quit_window ();
#endif
