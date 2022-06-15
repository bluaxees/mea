%Exercise 2 - Signal 4

%Read and plot original signal
[y,Fs] = audioread("signal4.wav");
t = 0:1/Fs:((length(y)-1)/Fs);
plot(t,rot90(y));
ylabel('Amplitude');
xlabel('Time(sec)');
sound(y); 

hold on;

%Read and plot modified signal
[yMod,FsMod] = audioread('signal4x.wav');
tMod = 0:1/FsMod:((length(yMod)-1)/FsMod);
plot(tMod,rot90(yMod));
sound(yMod);

%Observations:
%Looking at the plot, the modified signal
%have instances where it is zeroed out.
%This is similar to signal 1, except that
%the times where it is zero is random.
%Listening to the sounds, the modified signal
%have instances where it is silent.
%But this time, silence isn't periodic anymore.
