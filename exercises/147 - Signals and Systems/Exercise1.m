%Exercise 1

Fs = 8000; %Sampling Rate
t = 0:1/Fs:(0.5-1/Fs); %Running time of individual signals
T = 0:1/Fs:(3.5-1/Fs); %Running time of total signal

%Initialize Frequencies
f1 = 494;
f2 = 440;
f3 = 392;

%Initialize each signal
e = exp(t);
sig1 = e.*sin(2*pi*f1.*t);
sig2 = e.*sin(2*pi*f2.*t);
sig3 = e.*sin(2*pi*f3.*t);
sig4 = e.*sin(2*pi*f2.*t);
sig5 = e.*sin(2*pi*f1.*t);
sig6 = e.*sin(2*pi*f1.*t);
sig7 = e.*sin(2*pi*f1.*t);

%Concatenate and plot the given signals
S = [sig1 sig2 sig3 sig4 sig5 sig6 sig7];
plot(T,S);
sound(S); %It sounds like some nursery rhyme.
