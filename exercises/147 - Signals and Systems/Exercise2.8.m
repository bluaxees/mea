%Exercise 2 - Signal 8

%Read and plot original signal
[y,Fs] = audioread("signal8.wav");
t = 0:1/Fs:((length(y)-1)/Fs);
plot(t,rot90(y));
ylabel('Amplitude');
xlabel('Time(sec)');
sound(y); 

hold on;

%Read and plot modified signal
[yMod,FsMod] = audioread('signal8x.wav');
tMod = 0:1/FsMod:((length(yMod)-1)/FsMod);
plot(tMod,rot90(yMod));
sound(yMod);

%Observations:
%Looking at the plot, the modified signal
%have an increase in frequency.
%Listening to the sounds, the modified signal
%has lower run time and have higher bpm.
%No other modifications were observed.
