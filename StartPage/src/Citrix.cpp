/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "../inc/Citrix.h"
#include <iostream>

// Konstruktor
Citrix::Citrix(std::string netscaler_link, CTX_Mode ctx_mode) {
    // store local variables
    l_netscaler_link = netscaler_link;
    l_ctx_mode = ctx_mode;
    
    // prüfen ob externer (über netscaler) oder interner modus vorliegt (direkt über store)
    if (ctx_mode == EXTERNAL) { // external mode über netscaler
        // get all saved stores
        std::vector<CTX_Element> resultStores; // the stores will be saved in this variable
        CTX_Result resultGS = Citrix::getStores(resultStores);
        if (resultGS.result) {
            // choose store
            // ask which store user wants
            for (int i=0;i<l_stores.size();i++) {
                std::cout << "Store No. " << i << " = " << l_stores.at(i)->name << "\n";
            }
            int snr;
            std::cout << "Which Store do you want? ";
            std::cin >> snr;
            l_store_chosen = l_stores.at(snr);
            std::cout << "You picked store " << l_store_chosen->name << "\n";
    
        } else if (resultGS.status==FILE_EMPTY){ // store empty error
            // let user choose store
            CTX_Result resultAS = Citrix::addStore(resultStores);
            if (!resultAS.result) { // error
std::cout << "ERROR: addStore hat nicht funktioniert\n";
                std::exit(1);
            }
        } else {
            // other error
std::cout << "sonstiger Fehler:" << resultGS.status << "\n";
            std::exit(1);
        }
    }
    
    // get desktops for selected store 
    std::cout << "hole Desktops\n";
    std::vector<CTX_Element> resultDesktops;
    CTX_Result resultGD = getDesktops(resultDesktops); // get desktops
    if (resultGD.result) {
        // choose desktop
        // ask which desktop user wants
        for (int i=0;i<l_desktops.size();i++) {
            std::cout << "Desktop No. " << i << " = " << l_desktops.at(i)->name << "\n";
        }
        int snr;
        std::cout << "Which Desktop do you want? ";
        std::cin >> snr;
        l_desktop_chosen = l_desktops.at(snr);
        std::cout << "You picked desktop " << l_desktop_chosen->name << "\n";

        // start desktop
std::cout << "starte desktop ...\n";        
        CTX_Result resultSD = startDesktop();
    } else {
        // error
std::cout << "ERROR: getDesktops hat nicht funktioniert\n";
        std::exit(1);
    }



// endlosschleife (für tests)
while (true) {   
}
    
std::exit(1);    

}

// private functions

//
// get stores from site
//
CTX_Result Citrix::getStores(std::vector<CTX_Element>& resultStores) {
    std::vector<std::string> resultLines; // all the lines will be stored here
    CTX_Result result = Citrix::execCommand(CTX_STOREBROWSER_EXE + " -l '" + l_netscaler_link + "'", resultLines);

    if (result.result) {
        // speichere Vector mit stores
        for (int i=0;i<resultLines.size();i++) { // führe für alle gelisteten stores durch
            std::vector<std::string> parts;
            parts = Citrix::splitString(resultLines.at(i),"\t"); // teile zeile in spalten auf
            std::string link = parts.at(0); // store link
            std::string name = parts.at(1); // store name
        
            std::string remove = "'"; // remove '-zeichen
            Citrix::removeSubstrs(link, remove); 
            Citrix::removeSubstrs(name, remove);

            CTX_Element* store = new CTX_Element();
            store->link = link;
            store->name = name;
            l_stores.push_back(store);
        }           
    }  
        
    return result;  
};

//
// add new store to citrix
//
CTX_Result Citrix::addStore(std::vector<CTX_Element>& resultStore) {
    std::vector<std::string> resultLines; // all the return lines will be stored here
    CTX_Result result = Citrix::execCommand(CTX_STOREBROWSER_EXE + " -a '" + l_netscaler_link + "'", resultLines);
    
    if (result.result) { // if command returned lines
        // speichere Vector mit einem store lokal
        std::string link = resultLines.at(0); // store link
        std::string name = "default"; // no name is brought back ... // = parts.at(1); // store name
        
        std::string remove = "'"; // remove '-zeichen
        Citrix::removeSubstrs(link, remove); 
        Citrix::removeSubstrs(name, remove); 

        CTX_Element* store = new CTX_Element();
        store->link = link;
        store->name = name;
        l_stores.push_back(store);
        
        // this store is the chosen store
        CTX_Element* chosen = new CTX_Element();
        chosen->link = link;
        chosen->name = name;
        l_store_chosen = chosen;
    }        
        
    return result;   
}

//
// get desktops
//
CTX_Result Citrix::getDesktops(std::vector<CTX_Element>& resultDesktops) {
    // get all the desktops for this store
    std::vector<std::string> resultLines;
    CTX_Result result = Citrix::execCommand(CTX_STOREBROWSER_EXE + " -E '" + l_store_chosen->link + "'", resultLines);    

    if (result.result) {
        // speichere Vector mit desktops
        for (int i=0;i<resultLines.size();i++) { // führe für alle gelisteten desktops durch
            std::vector<std::string> parts;
            parts = Citrix::splitString(resultLines.at(i),"\t"); // teile zeile in spalten auf
            std::string link = parts.at(0); // desktop link
            std::string name = parts.at(1); // desktop name
        
            std::string remove = "'"; // remove '-zeichen
            Citrix::removeSubstrs(link, remove); 
            Citrix::removeSubstrs(name, remove);

            CTX_Element* desktop = new CTX_Element();
            desktop->link = link;
            desktop->name = name;
            l_desktops.push_back(desktop);
        }           
    }  

    return result;       
}

   
//
// starte Desktop
// 
CTX_Result Citrix::startDesktop() {
    std::vector<std::string> resultLines;
    CTX_Result result = Citrix::execCommand(CTX_STOREBROWSER_EXE + " -L " 
                    + "'" + l_desktop_chosen->link + "' " 
                    + "'" + l_store_chosen->link + "' "
                    , resultLines);
    
std::cout << "desktop started ... \n";    
    return result;
} // start desktop



//
// execute system command and return a vector of strings in resultCommand
//
CTX_Result Citrix::execCommand(std::string command, std::vector<std::string>& resultLines) {
    CTX_Result result; // result struct

    // execute command on local system
    command += " > "+CTX_RESULT_FILE+" 2> "+CTX_ERROR_FILE;
    FILE* local = popen(command.c_str(), "r"); // open file
    if (local == NULL) {
        // error
        result.result = false;
        result.status = EXECUTION_FAIL;
        return result;
    }
    pclose(local); // close file: important, otherwise files are not ready!!!

    result = Citrix::readCTXFile(CTX_RESULT_FILE, resultLines); // get results from file and save in resultLines
    if (!result.result) { // is there an error?
        result = Citrix::getCTXError(CTX_ERROR_FILE); // yes, get the error from the file
    }
    return result;
}

//
// split string in seperate parts, use delimiter to seperate the parts
//
std::vector<std::string> Citrix::splitString(std::string line, std::string delim) {
    std::vector<std::string> parts; // store the seperate parts of the line
    std::string temp;
    int start = 0;
    int end = line.find(delim);
    while (end != std::string::npos)
    {
        temp = line.substr(start, end - start);
        parts.push_back(temp); 
        start = end + delim.length();
        end = line.find(delim, start);
    }

    temp = line.substr(start, end);
    parts.push_back(temp);

    return parts;
}

//
// print vector of strings
//
void Citrix::printStrVector(std::vector<std::string> v) {
    for (int i=0;i<v.size();i++) {
        std::cout << v.at(i) << std::endl;
    }
}

//
// remove all occurences p from s
//
void Citrix::removeSubstrs(std::string& s, std::string& p) { 
  std::string::size_type n = p.length();
  for (std::string::size_type i=s.find(p); i!=std::string::npos; i=s.find(p))
      s.erase(i, n);
}

//
// get the CTX error from the error file
//
CTX_Result Citrix::getCTXError(std::string ctx_file) {
    std::ifstream infile(ctx_file);

    std::string line;
    CTX_Result result;
    while (std::getline(infile, line)) { // read the file line by line and store in resultLines
        if (line.find("ERROR") != std::string::npos) { // is the word ERROR in the file
            result.result = false;
std::cout << line << "\n";        
            return result;
        } else {
            result.result = false;
            // other error
std::cout << line << "\n";
            return result;
        }
    }
    infile.close(); 
    
    // error file empty
    result.result = false;
    result.status = FILE_EMPTY;
    return result;
}

//
// read the content from the CTX file (error or result)
//
CTX_Result Citrix::readCTXFile(std::string ctx_file, std::vector<std::string>& resultLines) { // read the content from the CTX file (error or result)
    std::ifstream infile(ctx_file);

    std::string line;
    while (std::getline(infile, line)) { // read the file line by line and store in resultLines
        std::istringstream iss(line);
        resultLines.push_back(iss.str());
    }
    infile.close(); 
    
    // return result
    CTX_Result result;
    if (resultLines.size()==0) { // no file or file empty
        result.result = false;
        result.status = FILE_EMPTY;
        return result;
    } else { // there is a result
        result.result = true;
        result.status = OK;
        return result;
    }
}
