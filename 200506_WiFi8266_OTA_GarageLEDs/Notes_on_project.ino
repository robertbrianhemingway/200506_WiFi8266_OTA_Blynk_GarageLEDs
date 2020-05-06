/*
### Analog pin A0

connect +3.3V to LDR, to 1K resistor and back to Gnd  
connect A0 to junction LDR to 1K  
Readings range from 15 to 318, with 32 being a good limit for night and day in this project.  
Have to be careful of D1 D2 D3 & D4 when uploading.  Think it is D4 causing the issue

 *  200503 starting to use GitHub as a repository
 * 
 *  200425 trying a Duemilanove as controller
 *  for garage and backyard LEDs
 *
 *  200502 changing board to WiFi ESP8266
 *  in order to get email notifications of triggers
 *  {Notes: No interrupts and do not use D2}
 *
 *  Remember pin ids for arduino are different to those
 *  on the actual board.  See 200501 Notes on WiFi ESP8266.md
 *  In this sketch both
 *  #define sirenPin 13 and #define sirenPin D7
 *  work
 *
 * There is only one analog pin, which I will use for ldrPin
 * and set a time on in the software
 * 
 * DO NOT USE GPIO 2 (D4) - stops uploads and normal functioning
 * V4a is a release for use in our garage. An issue is that there
 *     is one relay for both LEDs, and both PIRs.
 *     Pin assignments
 *      D1 - relay (green tape 7)
 *      D2 - pir input (green tape 2)
 *      D3 - flashing LED that signals loop is running
 *      D4 - do not use
 *      D5 - pir input (gree tape 3)
 *
 *      D7 - siren (not used yet)
 *      A0 - green tape A0
 *         - green tape A1 not connected


*/
