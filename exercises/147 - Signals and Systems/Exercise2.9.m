%Exercise 2 - Signal 9

%Read and plot original signal
[y,Fs] = audioread("signal9.wav");
t = 0:1/Fs:((length(y)-1)/Fs);
plot(t,rot90(y));
ylabel('Amplitude');
xlabel('Time(sec)');
sound(y); 

hold on;

%Read and plot modified signal
[yMod,FsMod] = audioread('signal9x.wav');
tMod = 0:1/FsMod:((length(yMod)-1)/FsMod);
plot(tMod,rot90(yMod));
sound(yMod);

%Observations:
%Looking at the plot, the modified signal
%have lower frequency compared to the original.
%Listening to the sounds, the modified signal
%have higher run time and lower bpm.
%No other modifications were observed.
