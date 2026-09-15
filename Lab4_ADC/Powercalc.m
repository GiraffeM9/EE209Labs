%{
Title: ELECTENG 209 Power Calculation - Using Real Excel ADC Data
Adapted from: Jackman Lin and Patrick Lawton's original DSP script
%}
close all
clear
clc

Marker_Size = 10;
Line_Width = 1.5;

%% ---- Step 1: Load data from Excel ----
filename = 'lab4.xlsx';
data = readmatrix(filename);

Vvf_mV = data(:,1);   % ADC0 samples, in mV 
Vif_mV = data(:,2);   % ADC1 samples, in mV 

N = length(Vvf_mV);   % number of samples per period

% Build a real time axis using the conversion time calculated in Q5.1.
% Each ADC conversion takes 13 clock cycles at 125kHz = 104us. The main
% loop does two conversions per iteration (ADC0 then ADC1),
% so voltage samples are 2x104us apart, and each current sample lags its
% paired voltage sample by exactly one conversion time (104us).
Tconv = 104e-6;          % seconds, one ADC conversion (Q5.1 result)
Tsample_pair = 2*Tconv;  % seconds, time between consecutive voltage samples

T_samples   = (0:N-1)'*Tsample_pair;      % voltage sample timestamps (s)
T_samples_A = T_samples + Tconv;          % current sample timestamps (s), lags voltage by Tconv

%% ---- Step 2: Convert to Volts and equivalent ADC counts ----
Vvf = Vvf_mV/1000;  % volts, includes offset
Vif = Vif_mV/1000;  % volts, includes offset

VADCValue = Vvf*1024/5; % equivalent ADC counts
AADCValue = Vif*1024/5; % equivalent ADC counts

figure('Name', 'Vvf and Vif inputs to ADC as volts and counts')
subplot(1,2,1)
plot(T_samples*1000, Vvf, 'o-','DisplayName','Voltage ADC Input', ...
    LineWidth=Line_Width, MarkerSize=Marker_Size)
title('Vvf and Vif inputs to ADC as VOLTS')
hold on
plot(T_samples_A*1000, Vif, 'x-','DisplayName','Current ADC Input', ...
    LineWidth=Line_Width, MarkerSize=Marker_Size)
xlabel('t (ms)')
ylabel('V')
grid on
legend

subplot(1,2,2)
plot(T_samples*1000, VADCValue, 'o-','DisplayName','Voltage ADC Counts', ...
    LineWidth=Line_Width, MarkerSize=Marker_Size)
title('Vvf and Vif inputs to ADC converted to COUNTS')
hold on
plot(T_samples_A*1000, AADCValue, 'o-','DisplayName','Current ADC Counts', ...
    LineWidth=Line_Width, MarkerSize=Marker_Size)
xlabel('t (ms)')
ylabel('ADC Counts')
grid on
legend

%% ---- Step 3: Calculate the theoretical ("actual") power ----
Vrms = 20;    % real Vrms across the AC source
Arms = 1.4;   % real Arms load current
phaseshift = 30/180*pi; % 30 degree phase lag, in radians

P_actual = Vrms*Arms*cos(phaseshift) % Watts

%% ---- Step 4: Method 1 - power calc WITHOUT aligning ADC values ----
Voff = 2.5;      % volts
Gv_total = 1/14.1; % combined voltage sensing + conditioning gain
Gi_total = 1/2;     % combined current sensing + conditioning gain

P_discrete_waveform = (VADCValue*5/1024-Voff)/Gv_total .* (AADCValue*5/1024-Voff)/Gi_total;

figure('Name', 'Power_discrete without aligning ADC values')
plot(T_samples*1000, P_discrete_waveform, 'o-', LineWidth=Line_Width, MarkerSize=Marker_Size)
title('Power\_discrete without aligning ADC values')
hold on
yline(P_actual, '--', 'Theoretical Average Power')
xlabel('t (ms)')
ylabel('W')
grid on

P_predicted = mean(P_discrete_waveform)
error_percent = abs((P_actual-P_predicted)/P_actual*100)

%% ---- Step 5: Method 2 - linear approximation (current realigned) ----
% For each voltage sample, estimate what the current would have been at
% that same instant by averaging the two adjacent raw current samples.
AADCValue_realigned = zeros(N,1);
for i = 1:N
    if i == 1
        AADCValue_realigned(i) = (AADCValue(N) + AADCValue(1))/2;
    else
        AADCValue_realigned(i) = (AADCValue(i-1) + AADCValue(i))/2;
    end
end

figure('Name', 'ADC realigned')
plot(T_samples*1000, VADCValue, 'o-','DisplayName','Voltage ADC Counts', ...
    LineWidth=Line_Width, MarkerSize=Marker_Size)
title('Vvf and Vif inputs to ADC converted to COUNTS')
hold on
plot(T_samples_A*1000, AADCValue, 'o-','DisplayName','Current ADC Counts', ...
    LineWidth=Line_Width, MarkerSize=Marker_Size)
plot(T_samples*1000, AADCValue_realigned, 'x-','DisplayName','Adjusted Current ADC Counts', ...
    'Color',"#FF00FF", LineWidth=Line_Width, MarkerSize=Marker_Size)
xlabel('t (ms)')
ylabel('ADC Counts')
grid on
legend

P_predicted_corrected = mean((VADCValue*5/1024-Voff)/Gv_total .* (AADCValue_realigned*5/1024-Voff)/Gi_total)
error_percent_correct = abs((P_actual-P_predicted_corrected)/P_actual*100)

%% ---- Step 6: Bonus - also realign voltage (completing the exercise) ----
% aligning voltage not just current, and see if it improves accuracy further.
VADCValue_realigned = zeros(N,1);
for i = 1:N
    if i == N
        VADCValue_realigned(i) = (VADCValue(N) + VADCValue(1))/2;
    else
        VADCValue_realigned(i) = (VADCValue(i) + VADCValue(i+1))/2;
    end
end

figure('Name', 'ADC realigned - both channels')
plot(T_samples*1000, VADCValue, 'o-','DisplayName','Voltage ADC Counts', ...
    LineWidth=Line_Width, MarkerSize=Marker_Size)
title('Both Voltage and Current Realigned')
hold on
plot(T_samples_A*1000, VADCValue_realigned, 'x-','DisplayName','Adjusted Voltage ADC Counts', ...
    'Color',"#00CCFF", LineWidth=Line_Width, MarkerSize=Marker_Size)
plot(T_samples_A*1000, AADCValue, 'o-','DisplayName','Current ADC Counts', ...
    LineWidth=Line_Width, MarkerSize=Marker_Size)
plot(T_samples*1000, AADCValue_realigned, 'x-','DisplayName','Adjusted Current ADC Counts', ...
    'Color',"#FF00FF", LineWidth=Line_Width, MarkerSize=Marker_Size)
xlabel('t (ms)')
ylabel('ADC Counts')
grid on
legend

% Average the two possible pairings (real V with realigned I, and
% realigned V with real I), same approach as slide 17's formula.
P_both_realigned = mean(0.5*( ...
    (VADCValue*5/1024-Voff)/Gv_total .* (AADCValue_realigned*5/1024-Voff)/Gi_total + ...
    (VADCValue_realigned*5/1024-Voff)/Gv_total .* (AADCValue*5/1024-Voff)/Gi_total ...
    ))
error_percent_both = abs((P_actual-P_both_realigned)/P_actual*100)

%% ---- Summary ----
fprintf('\n--- Summary ---\n')
fprintf('Theoretical power:                 %.4f W\n', P_actual)
fprintf('Method 1 (without alignment):      %.4f W  (%.2f%% error)\n', P_predicted, error_percent)
fprintf('Method 2 (current realigned):      %.4f W  (%.2f%% error)\n', P_predicted_corrected, error_percent_correct)
fprintf('Method 3 (both realigned, bonus):  %.4f W  (%.2f%% error)\n', P_both_realigned, error_percent_both)