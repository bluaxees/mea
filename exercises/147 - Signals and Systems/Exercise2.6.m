%Exercise 2 - Signal 6

%Read and plot original signal
[y,Fs] = audioread("signal6.wav");
t = 0:1/Fs:((length(y)-1)/Fs);
plot(t,rot90(y));
ylabel('Amplitude');
xlabel('Time(sec)');
sound(y); 

hold on;

%Read and plot modified signal
[yMod,FsMod] = audioread('signal6x.wav');
tMod = 0:1/FsMod:((length(yMod)-1)/FsMod);
plot(tMod,rot90(yMod));
sound(yMod);

%Observations:
%Looking at the plot, the modified signal
%is cut off at a certain amplitude.
%Zooming in, the signal is also seen to have
%increased in amplitude.
%Listening to the sounds, the modified signal
%have higher volume compared to the original.
%There is no way for me to know that the signal
%is cut off at a known amplitude
%by listening to it alone.
