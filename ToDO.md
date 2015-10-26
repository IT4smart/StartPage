1.
bisher erhalte ich bei init.c in init_login bei strcmp eine warnung. funktionieren tut es aber




die bildgroesse sollte dynamisch angepasst werden, sodass sie immer den gleichen prozentsatz benötigt



Man muss den Zeilenbreite definitive Breiten geben können, wie zB 5% der gesamten Breite




Ist in MainPage-configuration:

bei der Config muss bei der nachfrage nach der ip netmask und gateway immer das system ueber ifconfig 
abfragen und nicht aus der settingsdatei. 
typ muss aus den settings herausgelesen werden, zb DHCP oder static


bei rdp: 
felder für die benutzernamen und kennwort anlegen


status zum reinschreiben anbieten direkt als funktion mit string als übergabewert


breite von frame networks verkleinern. statt right+1 muss right einen sinnvollenwert annehmen, wie einfach 1 breiter.
