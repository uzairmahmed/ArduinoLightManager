<p><strong>Overview</strong></p>
<p style="text-indent: .5in;"><span style="line-height: 107%; font-family: 'Roboto Slab';">This shield is made for the Arduino UNO which allows the user to control an Addressable RGB LED Strip using a Nintendo Nunchuck. The module consists of 3 built-in functions, that are easily changeable through a user interface on a 16x2 LCD screen. The shield also has Serial Bluetooth capabilities to allow changing settings through an Android phone. </span></p>
<p><strong>Materials </strong><span style="font-family: 'Roboto Slab';">(Entire project costs around $50.00)</span></p>
<ul>
<li style="text-indent: -.25in;"><span style="font-family: 'Roboto Slab';">Arduino UNO R3</span></li>
<li style="text-indent: -.25in;"><span style="font-family: 'Roboto Slab';">Addressable RGB LED Strip</span>
<ul>
<li style="margin-left: 1.0in; text-indent: -.25in;"><span style="font-family: 'Roboto Slab';">For best results, 60 LED should be used</span></li>
</ul>
</li>
<li style="text-indent: -.25in;"><span style="font-family: 'Roboto Slab';">LCD Screen 16x2</span></li>
<li style="text-indent: -.25in;"><span style="font-family: 'Roboto Slab';">Nintendo Nunchuck</span></li>
<li style="text-indent: -.25in;"><span style="font-family: 'Roboto Slab';">Bluetooth HC-05 Module</span></li>
<li style="text-indent: -.25in;"><span style="font-family: 'Roboto Slab';">Bidirectional Logic Level Converter</span></li>
<li style="text-indent: -.25in;"><span style="font-family: 'Roboto Slab';">10K Ohm Potentiometer</span></li>
<li style="text-indent: -.25in;"><span style="font-family: 'Roboto Slab';">220 Ohm Resistor</span></li>
<li style="text-indent: -.25in;"><span style="font-family: 'Roboto Slab';">Screw Terminals</span></li>
<li style="text-indent: -.25in;"><span style="font-family: 'Roboto Slab';">Male-Male and Male-Female Jumper Cables</span></li>
<li style="text-indent: -.25in;"><span style="font-family: 'Roboto Slab';">Extra Long Pin Headers</span></li>
<li style="text-indent: -.25in;"><span style="font-family: 'Roboto Slab';">Female Pin Headers</span></li>
</ul>
<p><strong>Procedure</strong></p>
<p><span style="text-decoration: underline;">Prepare PCB.</span></p>
<ol>
<li style="margin-right: 135.0pt; text-indent: -.25in;"><span style="font-family: 'Roboto Slab';">Using Fritzing, design the circuit diagram shown below and export for production.</span></li>
<li style="margin-right: 135.0pt; text-indent: -.25in;"><span style="font-family: 'Roboto Slab';">Print your design&rsquo;s copper bottom on plain paper for size testing.</span></li>
<li style="margin-right: 135.0pt; text-indent: -.25in;"><span style="font-family: 'Roboto Slab';">Cut a piece of copper the size of your paper prototype</span></li>
<li style="margin-right: 135.0pt; text-indent: -.25in;"><span style="font-family: 'Roboto Slab';">Remove the oxide layer on the board by scrubbing the board until it&rsquo;s shiny. </span></li>
<li style="margin-right: 135.0pt; text-indent: -.25in;"><span style="font-family: 'Roboto Slab';">After removing the oxide layer, wash the board with acetone and isopropyl alcohol, and wait for it to completely dry. Do not touch the board.</span></li>
<li style="margin-right: 135.0pt; text-indent: -.25in;"><span style="font-family: 'Roboto Slab';">Reprint the copper bottom onto photo paper making sure not to touch the glossy side at all. </span></li>
<li style="margin-right: 135.0pt; text-indent: -.25in;"><span style="font-family: 'Roboto Slab';">Cut the paper to the size of the copper board and hold the glossy side down on the copper side of the board. </span></li>
<li style="margin-right: 135.0pt; text-indent: -.25in;"><span style="font-family: 'Roboto Slab';">Run the paper/copper through a laminator 20-25 times.</span></li>
<li style="margin-right: 135.0pt; text-indent: -.25in;"><span style="font-family: 'Roboto Slab';">After the lamination procedure is done, and the board has cooled, leave the board in a water bath for 24 hours. </span></li>
<li style="margin-right: 135.0pt; text-indent: -.25in;"><span style="font-family: 'Roboto Slab';">Slowly take the paper layer off the board, making sure not to pull any trace off. (If too many traces are removed, repeat steps d-g, otherwise use a sharpie to redraw the trace). </span></li>
<li style="margin-right: 135.0pt; text-indent: -.25in;"><span style="font-family: 'Roboto Slab';">Wait for the board to dry, and leave it in an Ammonium Persulfate tank until all the extra copper is gone. </span></li>
<li style="margin-right: 135.0pt; text-indent: -.25in;"><span style="font-family: 'Roboto Slab';">Using a paintbrush, dunk the board in acetone and carefully brush the toner off the traces. </span></li>
<li style="margin-right: 135.0pt; text-indent: -.25in;"><span style="font-family: 'Roboto Slab';">Using a drill press, drill holes into all the copper pads on the board. Make sure to keep header holes straight for easier installation. The board is now ready for soldering.</span></li>
</ol>
<p><span style="text-decoration: underline;">Attach parts to PCB</span></p>
<ol>
<li>Use the fritzing diagram for reference to where the parts go.</li>
<li>Solder female pin headers to the Bluetooth shield holes and the LCD holes to avoid making the parts permanently attached.</li>
<li>Solder permanent parts such as the 10k pot, screw terminals, jumper wire, and the logic level converter.</li>
<li>Solder extra-long pins to the LCD (bent at a 45 angle inwards), and the Arduino holes.</li>
<li>Insert Male-Female Jumper into screw terminals and connect to corresponding light strip pin.</li>
</ol>
<p><span style="text-decoration: underline;">Run code.</span></p>
<p><span style="font-size: 11.0pt; line-height: 107%; font-family: 'Calibri',sans-serif;">Make sure the Nunchuck Library is installed, along with the AdaFruit NeoPixel Library. Links below.</span></p>
