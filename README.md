# PROTOTYPE LIBRARY

**Last release ver. *May 20***

## HARDWARE BASED ON:

Target: ***SPC*** - (**S**)tandard (**P**)rototype (**C**)alculator

- BLE PICKIT rev.B/C/D (*Prototype dev.*) or ETH PICKIT
- Ethernet Starter KIT II (*PIC32MX795F512L*)
- PICAdapter rev.E2 / USD (*Prototype dev.*)


## OPTIMIZATIONS:

Three parameters are available for projet's optimizations (keep in mind that levels **3** & **s** are reserved for PRO version):
* **BLANCK_PROJECT** & **PLIB2**: *Properties / XC32 (Global Options) / xc32-gcc / Optimization / optimization-level*.
* **BLANCK_PROJECT**: *Properties / XC32 (Global Options) / xc32-ld / Libraries / Optimization level of Standard Libraries*.

## HOW TO USE THE LIBRARY:

First, you have to include ***PLIB2.h***, which includes all library's header file, in your project:
* In your project **BLANCK_PROJECT**, open **config.h** and at the top of the file, include the **PLIB2.h** following the directory where it is stored. 
* Then include the file **PLIB2.h** in your **Header folder** project. Right click on the **Header folder** and **Add Existing Item...**. Search and select the file to include it in your project.

Now you have to include the **Library project** in your project:

* Right click on your **project --> Properties --> Conf: [default] --> Libraries**.
* Click on **Add Library Project...** and select **PLIB2.X** (*the MPLABX IDE library project*).
* Remove previous library if present.
