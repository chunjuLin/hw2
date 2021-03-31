# hw2


(1) how to setup and run your program 

In homework two, we know we have six different part to implement.I will explain it one 
by one. 

1. switch 

We have three different switches, one for increase the frequency, another one for decrease the 
frequency and the last one for selected the frequency. I set a variable for the current frequency
. When the first button is pushed, which means we get the HIGH signal. We let the variable add by 
20. When the second button is pushed, we decrease the variable by 20. To implement the select 
function we set another variable called done, which is initial as 0. If the selection button is pushed.
We will set the done = 1.This done variable will disable the up and down function.

2. LCD

We have to use the lcd to show the current frequency. I use the bar to make the lcd display more readable.
So first I draw the bar. And the bar will change while the frequency change. I use the variable named 
frequency to adjust the lighted part and I use the black line to  clear the unlighted part.

3. Generate waveform

I use the DAC to implement this part. I cut one wave into 100 parts. Because of my student ID, I have to 
make the peak at S = 8. So the wave will climb up at the first 80 parts, and drop down at the last 20
parts. In order to generate it at correct frequency, we have to use the original frequency to count out the
period. Then, divided it with 100. I use wait_us function to make it workable. I use two for loop to one 
for climb up one for drop down to make it a completed wave.

4. Measure

I connect the out put wave with the low pass filter. My low pass filter's cutoff frequency is at 33Hz. If
 the frequency is larger than that, the amplitude of the wave will drop significanly. I use the picoscope
to connect the out put frequency and get the correct frequency.

5. Sample

Here is a problem, we are generating the wave while sampling. How can I done such thing together without 
affecting the original frequency? So I first generate the 10 waves with out sample anything. After generating 
10 waves, we start to sample while we are generating the wave. Because we want to sample as accurate as possible
so I put sample inside the wave generating loop so it will have equal to the generating rate. We only take 1000
points and store it in the array. After obtaining the wave, we print it out on the screen. After printing it out 
we keep on generating the old frequency.

6. Analysis

Last, we have to use the python to get the FFT. Basically, the FFT is similar to the original one. However our 
sampling rate will change with the frequency, so we have to make the Fs read the current frequency. And calculate 
out the related range of the graph. I make the graph print out 10 waves in the graph. Thus, we can make it change
 with our assigned answer.

(2) what are the results


After we start to use the button to select the frequency, we may get the proper frequency range from 10 - 130
because the cutoff frequency is 33 for my low pass filter. After we push the select button we may see the wave 
start to generate. We start to sample it as soon as the wave are generating. after sampling the wave for one 
second we use the python to plot out the wave form and the result in frequency domain. We may see that if the
 frequency of the wave is higher than the cutoff frequency we may see that the amplitude will decrease. And basically
the result does not have large error.  
