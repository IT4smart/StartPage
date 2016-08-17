Anleitung, wie login per citrix / rdp funktioniert
==================================================

1. Citrix:
----------
- Steuerung über Ressources/settings.ini
	-- key global/citrix_rdp_type muss citrix sein
- USB/Sound ok


2. RDP:
-------
- Steuerung über Ressources/settings.ini	
	-- key global/citrix_rdp_type muss rdp sein
	-- server_url ohne https (bei IP-Adressen)
- USB/SOUND fehlt/nicht getestet (Stand 160817)
	-- Optionserweiterung/Plugins unter 
https://github.com/FreeRDP/FreeRDP/wiki/CommandLineInterface


