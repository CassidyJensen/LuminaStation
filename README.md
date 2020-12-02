# LuminaStation

Lumina Station is the Barbie Dream House of space stations that uses an interactive physical display to engage and inform the public. 

The code presented here controls the station. It is organized based on the different interactive systems we chose to represent. The full project can be found on cassidyajensen.wordpress.com.
All of the systems are controlled by one control panel and the systems are spread across a physical model

## Carbon Dioxide Removal: Zeolites
This system shows the absorption of carbon dioxide layer by layer. The neopixels light up green, and then 4 at a time they slowly turn red. When a slider is pushed to the side to expose the zeolites to vacuum, the lights turn red and then fade to off to indicate they released the carbon dioxide. Sliding the slider back returns everything to the initial green and begins the process again.

## Water Recyling & Electrolysis
This system shows the use of water on the space station. There are three separate neopixel displays: one for dirty water, clean water, and oxygen. The dirty water accumulates overtime as water is produced by astronauts. This shown by the neopixels increasing in number. Then - the user can push two buttons. The clean water button decreases the dirty water and increases the clean water. The same interaction occurs for the oxygen supply. Water is used for both breathing and human consumption in a closed loop on the space station. 

## Trash Removal: Heat Melt Compactor (HMC)
This system represents trash. It slowly turns red over time showing the accumulation of trash. Once it is full, the user must push the force sensor to compact the trash down, turning the lights green. 

## Solar Panels
To represent power we used light sensors and a neopixel strip. The light sensor determine how much light is being received and then based on that value, controls the number of neopixels that light up. More light received, indicates more power, which shows more neopixels lighting up. 

## Greenhouse
The greenhouse is a strip of neopixel lights that shine with a purple light - similar to UV. When the user pushes the button, it lights up and then fades for a random amount of time between ~ 5-45 seconds.  

## Radiators
Radiators are a long strip of neopixels - divided into three rows of 10. The neopixels light up red one at a time for each row, showing the accumulation of heat. Once they are full the user presses a button to release the heat into vaccuum and resetting the process. Due to the layout on our model, the middle row actually counts backwards so that they appear on the same side. 

## Fire Control
The fire system is represented on our model using a series of individual neopixel lights. After about 30 seconds, a random light is selected to glow orange. To extinguish the fire, the user must press a button.  
