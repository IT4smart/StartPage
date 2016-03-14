/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Citrix.h
 * Author: test
 *
 * Created on 11. Februar 2016, 13:50
 */

#ifndef CITRIX_H
#define CITRIX_H

#include <vector>
#include <sstream>
#include <string>
#include <fstream>

// constants
const std::string CTX_ERROR_FILE = "/tmp/CTX_ERRORS"; // errors of storebrowse exe
const std::string CTX_RESULT_FILE = "/tmp/CTX_RESULTS"; // result of storebrowse exe
const std::string CTX_STOREBROWSER_EXE = "/opt/Citrix/ICAClient/util/storebrowse"; // storebrowse binary

// enumeration types
enum CTX_Mode {EXTERNAL, INTERNAL}; // citrix started from intern (behind netscaler) or extern (with netscaler)
enum CTX_Status {OK, FILE_DELETE, FILE_EMPTY, MISSING_CERTIFICATE, EXECUTION_FAIL, NO_EXECUTION_RETURN, OTHER}; // possible errors from execution 

// element struct of citrix
typedef struct {
    std::string name;
    std::string link;
} CTX_Element;

// result struct of citrix
typedef struct {
    bool result;
    CTX_Status status;
} CTX_Result;


class Citrix {
    private: 
        // internal variables
        CTX_Mode l_ctx_mode; // ctx mode (EXTERNAL = over netscaler, INTERNAL = ovoer storebrowser)
        std::string l_netscaler_link; // link to netscaler
        std::vector<CTX_Element*> l_stores; // possible stores
        CTX_Element* l_store_chosen; // chosen store
        std::vector<CTX_Element*> l_desktops; // possible desktops
        CTX_Element* l_desktop_chosen; // chosen desktop
           
        // main functions
        CTX_Result getStores(std::vector<CTX_Element>& resultStores); // get stores
        CTX_Result addStore(std::vector<CTX_Element>& resultStore); // add new store
        CTX_Result getDesktops(std::vector<CTX_Element>& resultDesktops); // get desktops
        CTX_Result startDesktop(); // start desktop
        
        // Hilfsfunktionen
        CTX_Result execCommand(std::string command, std::vector<std::string>& resultCommand); // execute system command mit popen()
        std::vector<std::string> splitString(std::string line, std::string delim); // split string into parts
        void removeSubstrs(std::string& s, std::string& p); // remove all occurences of p from s
        void printStrVector(std::vector<std::string> v); // print vector for test
        CTX_Result readCTXFile(std::string ctx_file, std::vector<std::string>& resultLines); // read the content from the CTX file (error or result)
        CTX_Result getCTXError(std::string ctx_file);
        
    public:
        // constructors
        Citrix(std::string netscaler_link, CTX_Mode mode);
        
    
};


#endif /* CITRIX_H */

