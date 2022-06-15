%Exercise 2 - Signal 7

%Read and plot original signal
[y,Fs] = audioread("signal7.wav");
t = 0:1/Fs:((length(y)-1)/Fs);
plot(t,rot90(y));
ylabel('Amplitude');
xlabel('Time(sec)');
sound(y); 

hold on;

%Read and plot modified signal
[yMod,FsMod] = audioread('signal7x.wav');
tMod = 0:1/FsMod:((length(yMod)-1)/FsMod);
plot(tMod,rot90(yMod));
sound(yMod);

%Observations:
%Looking at the plot, the modified signal
%is zero during its "negative half cycle".
%Zooming in, the signal is also seen to have
%increased in amplitude.
%Listening to the sounds, the modified signal
%seems to have not changed at all.
%There is no way for me to know that the signal
%had changed by listening to it alone.

