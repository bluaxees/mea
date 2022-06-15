%Exercise 2 - Signal 1

%Read and plot original signal
[y,Fs] = audioread("signal1.wav");
t = 0:1/Fs:((length(y)-1)/Fs);
plot(t,rot90(y));
ylabel('Amplitude');
xlabel('Time(sec)');
sound(y); 

hold on;

%Read and plot modified signal
[yMod,FsMod] = audioread('signal1x.wav');
tMod = 0:1/FsMod:((length(yMod)-1)/FsMod);
plot(tMod,rot90(yMod));
sound(yMod);

%Observations:
%Looking at the plot, the modified signal
%have instances where it is zeroed out every x seconds.
%Listening to the sounds, the modified signal
%have instances where it is (periodically) silent.
%No other modifications were observed.
