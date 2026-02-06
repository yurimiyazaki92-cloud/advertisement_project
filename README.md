# LCD Advertisement System (AVR / Embedded)

## **Project Summary**

This project is an embedded advertisement display system built on an AVR microcontroller using an HD44780-compatible LCD.
Multiple advertisers are displayed randomly and fairly based on their paid amount. The system ensures that the same advertiser is never shown twice in a row and supports multiple text display effects.

<img width="911" height="393" alt="Image" src="https://github.com/user-attachments/assets/81c49976-71e8-4071-b127-a6872a2568a7" />


## **Key Features**

•	Weighted random selection of advertisers

•	No consecutive duplicate ads

•	Multiple message variants per advertiser

•	Text effects: normal, blinking, scrolling

•	Custom support for Swedish characters (å, ä, ö)





## **Technical Implementation**

•	Advertisers are modeled as objects containing payment data and messages.

•	Selection is performed using a weighted random algorithm.

•	Random seeding uses ADC noise due to AVR limitations.

•	LCD is driven in 4-bit mode using an HD44780-compatible controller.

•	Swedish characters are implemented via custom CGRAM definitions and a dedicated WriteSwedish() function.

•	Timing is handled using _delay_ms().





## **Challenges & Learnings**

•	Standard time functions are unavailable on AVR.

•	Real-time based advertisement switching could not be fully implemented.

•	Scroll timing could not be synchronized to end exactly at 20 seconds.

•	The project emphasized the importance of hardware-aware design.





## **Future Improvements**

•	Add real-time tracking using an RTC or timer-based solution

•	Improve scroll timing precision

•	Further modularize display-related code





## **Technologies Used**

•	AVR-GCC (C / C++)

•	HD44780 LCD

•	Git & GitHub

