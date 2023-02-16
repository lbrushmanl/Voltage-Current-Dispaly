# Voltage-Current-Dispaly
This project was based around using the 11-digit VFD displays that you can buy for cheap at Jaycar 
https://www.jaycar.co.nz/11-digit-fluoro-display-bargain/p/ZD1880?pos=1&queryId=efb51b3d6997d6bc33e34b690ac22e3b&sort=relevance&searchText=11%20Digit%20Fluoro%20Display%20Bargain

As these displays look cool, I came up with the idea of making a voltage current display that I could then use for lots of my other projects. 
The first 5 digits would be voltage and the last 5 for current leaving the centre one blank.

To drive the display, a voltage of around 4.5V is needed for the filament, and 12V is needed for grids and digits. The 4.5V came from an LM317 adjustable voltage regulator.
The board was designed to use an ATMega8, as I had a few from UNI. 

The display was driven via shift registers and a 7seg decoder, as this would only require three GPIO pins on the MCU to be used. It also seemed like a cool idea.

Due to this driver circuitry, the following data structure was formed.

The first 4 bits are the BCD value that the 7seg decoder will read, the 5th bit is the decimal point, and bits 6 to 15 are the grids of the VFD.
A B C D DP G1 G2 G3 G4 G5 G7 G8 G9 G10 G11

I assembled one board fully and found out that a few things were wrong. I also used my ATMegaU4 dev board for testing rather than the ATMega8, as it was easier to use
The main thing I found wrong was the C segment was connected to the comma. I also found out that the Blanking pin of the decoder was connected high rather than low. The biggest issue was that the display was the wrong way around. Flipping it fixed the problem however it no longer looks as good.

View of test setup
![20230209_123035](https://user-images.githubusercontent.com/114579521/219331909-ee1642f7-fa74-4598-823d-415e615510e7.jpg)

Inital Test after fixing the PCB showing 0 and the dot
![20230209_123032](https://user-images.githubusercontent.com/114579521/219331513-a37fdbaa-e529-4029-b8e7-6f42b351792a.jpg)

First numbers quite dim
![20230209_132045](https://user-images.githubusercontent.com/114579521/219332139-29e069a8-0289-42ab-bb41-081f12b3fc36.jpg)

Finaly brighter and the ADC is conected 
![20230211_194458](https://user-images.githubusercontent.com/114579521/219332314-775b31ed-c32c-41af-b44f-056137937bb7.jpg)


