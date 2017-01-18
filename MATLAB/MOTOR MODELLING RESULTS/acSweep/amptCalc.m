function [ amptitude ] = amptCalc( y, Tspan, T_zc )
%AMPTCALC signal Y, Tspan and zero-cross time table
start = 1;
fin = 1;
k = 1;
y = y - mean(y);
for i=1:1:length(Tspan)
    if(Tspan(i) == T_zc(k+1)) % zero cross point
        fin = i;
        Ampt(k) = max(abs(y(start:fin)));
        plot(y(start:fin))
        start = fin;
        
        k = k + 1;
        if k>length(T_zc)-1
            break;
        end 
    end
end
%hold on
%stem(Ampt);
amptitude = mean(Ampt);
end

